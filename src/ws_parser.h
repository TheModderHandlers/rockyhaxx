#pragma once
#include <cstdint>
#include <cstring>
#include <functional>
#include <string>
#include <vector>
#include <zlib.h>

enum WsOpcode : uint8_t {
  WS_CONTINUATION = 0x0,
  WS_TEXT = 0x1,
  WS_BINARY = 0x2,
  WS_CLOSE = 0x8,
  WS_PING = 0x9,
  WS_PONG = 0xA,
};

struct WsMessage {
  WsOpcode opcode;
  std::vector<uint8_t> payload;
};

// this genuinely sucks, why is there no decent library to do this for me
static const uint8_t DEFLATE_TAIL[] = {0x00, 0x00, 0xFF, 0xFF};

class WsParser {
  std::vector<uint8_t> buf_;
  bool handshake_done_ = false;
  bool in_fragment_ = false;
  bool fragment_compressed_ = false;
  WsOpcode fragment_opcode_ = WS_BINARY;
  std::vector<uint8_t> fragment_payload_;

  z_stream inflate_strm_;
  bool inflate_init_ = false;

public:
  using MessageCallback = std::function<void(const WsMessage &)>;

  WsParser() { memset(&inflate_strm_, 0, sizeof(inflate_strm_)); }

  ~WsParser() {
    if (inflate_init_)
      inflateEnd(&inflate_strm_);
  }

  WsParser(const WsParser &) = delete;
  WsParser &operator=(const WsParser &) = delete;
  WsParser(WsParser &&o) noexcept {
    buf_ = std::move(o.buf_);
    handshake_done_ = o.handshake_done_;
    in_fragment_ = o.in_fragment_;
    fragment_compressed_ = o.fragment_compressed_;
    fragment_opcode_ = o.fragment_opcode_;
    fragment_payload_ = std::move(o.fragment_payload_);
    inflate_strm_ = o.inflate_strm_;
    inflate_init_ = o.inflate_init_;
    o.inflate_init_ = false;
  }
  WsParser &operator=(WsParser &&o) noexcept {
    if (this != &o) {
      if (inflate_init_)
        inflateEnd(&inflate_strm_);
      buf_ = std::move(o.buf_);
      handshake_done_ = o.handshake_done_;
      in_fragment_ = o.in_fragment_;
      fragment_compressed_ = o.fragment_compressed_;
      fragment_opcode_ = o.fragment_opcode_;
      fragment_payload_ = std::move(o.fragment_payload_);
      inflate_strm_ = o.inflate_strm_;
      inflate_init_ = o.inflate_init_;
      o.inflate_init_ = false;
    }
    return *this;
  }

  void feed(const uint8_t *data, size_t len, MessageCallback on_message) {
    buf_.insert(buf_.end(), data, data + len);

    if (!handshake_done_) {
      if (!try_skip_http_handshake())
        return;
    }

    while (parse_one_frame(on_message)) {
    }
  }

  void reset() {
    buf_.clear();
    handshake_done_ = false;
    in_fragment_ = false;
    fragment_payload_.clear();
    if (inflate_init_) {
      inflateEnd(&inflate_strm_);
      inflate_init_ = false;
    }
  }

private:
  bool ensure_inflate() {
    if (inflate_init_)
      return true;
    memset(&inflate_strm_, 0, sizeof(inflate_strm_));

    int ret = inflateInit2(&inflate_strm_, -15);
    inflate_init_ = (ret == Z_OK);
    return inflate_init_;
  }

  bool decompress(std::vector<uint8_t> &data) {
    if (!ensure_inflate())
      return false;

    data.insert(data.end(), DEFLATE_TAIL, DEFLATE_TAIL + 4);

    std::vector<uint8_t> out;
    out.resize(data.size() * 4 + 4096);

    inflate_strm_.next_in = data.data();
    inflate_strm_.avail_in = (uInt)data.size();

    size_t total = 0;
    const size_t MAX_OUTPUT = 16 * 1024 * 1024; // 16 MB safety cap
    int ret;
    do {
      inflate_strm_.next_out = out.data() + total;
      inflate_strm_.avail_out = (uInt)(out.size() - total);
      ret = inflate(&inflate_strm_, Z_SYNC_FLUSH);
      if (ret == Z_NEED_DICT || ret == Z_DATA_ERROR || ret == Z_MEM_ERROR) {
        return false;
      }
      total = out.size() - inflate_strm_.avail_out;
      if (inflate_strm_.avail_out == 0) {
        if (out.size() >= MAX_OUTPUT)
          break;
        out.resize(out.size() * 2);
      }
      if (ret == Z_BUF_ERROR)
        break; // no progress possible
    } while (inflate_strm_.avail_in > 0 || ret == Z_OK);

    out.resize(total);
    data = std::move(out);
    return true;
  }

  bool try_skip_http_handshake() {
    if (buf_.size() < 4)
      return false;

    bool looks_http =
        (buf_[0] == 'H' && buf_[1] == 'T' && buf_[2] == 'T' &&
         buf_[3] == 'P') ||
        (buf_[0] == 'G' && buf_[1] == 'E' && buf_[2] == 'T' && buf_[3] == ' ');

    if (!looks_http) {
      handshake_done_ = true;
      return true;
    }

    std::string s(reinterpret_cast<const char *>(buf_.data()), buf_.size());
    size_t pos = s.find("\r\n\r\n");
    if (pos == std::string::npos)
      return false;

    buf_.erase(buf_.begin(), buf_.begin() + pos + 4);
    handshake_done_ = true;
    return true;
  }

  bool parse_one_frame(MessageCallback &on_message) {
    size_t pos = 0;
    size_t avail = buf_.size();
    if (avail < 2)
      return false;

    uint8_t b0 = buf_[pos++];
    uint8_t b1 = buf_[pos++];

    bool fin = (b0 & 0x80) != 0;
    bool rsv1 = (b0 & 0x40) != 0; // permessage-deflate compressed
    uint8_t opcode = b0 & 0x0F;
    bool masked = (b1 & 0x80) != 0;
    uint64_t payload_len = b1 & 0x7F;

    if (payload_len == 126) {
      if (avail < pos + 2)
        return false;
      payload_len = ((uint64_t)buf_[pos] << 8) | buf_[pos + 1];
      pos += 2;
    } else if (payload_len == 127) {
      if (avail < pos + 8)
        return false;
      payload_len = 0;
      for (int i = 0; i < 8; i++)
        payload_len = (payload_len << 8) | buf_[pos + i];
      pos += 8;
    }

    uint8_t mask_key[4] = {};
    if (masked) {
      if (avail < pos + 4)
        return false;
      memcpy(mask_key, &buf_[pos], 4);
      pos += 4;
    }

    if (avail < pos + payload_len)
      return false;

    std::vector<uint8_t> payload(buf_.begin() + pos,
                                 buf_.begin() + pos + payload_len);
    if (masked) {
      for (size_t i = 0; i < payload.size(); i++)
        payload[i] ^= mask_key[i & 3];
    }
    pos += (size_t)payload_len;
    buf_.erase(buf_.begin(), buf_.begin() + pos);

    if (opcode >= 0x8) {
      WsMessage msg;
      msg.opcode = (WsOpcode)opcode;
      msg.payload = std::move(payload);
      on_message(msg);
      return true;
    }

    if (opcode != WS_CONTINUATION) {
      fragment_opcode_ = (WsOpcode)opcode;
      fragment_payload_ = std::move(payload);
      fragment_compressed_ = rsv1;
      in_fragment_ = !fin;
    } else {
      fragment_payload_.insert(fragment_payload_.end(), payload.begin(),
                               payload.end());
      in_fragment_ = !fin;
    }

    if (fin) {
      // Decompress if RSV1 was set on the first frame
      if (fragment_compressed_) {
        if (!decompress(fragment_payload_)) {
          // Decompression failed, deliver raw
          fragment_compressed_ = false;
        }
      }

      WsMessage msg;
      msg.opcode = fragment_opcode_;
      msg.payload = std::move(fragment_payload_);
      fragment_payload_.clear();
      in_fragment_ = false;
      fragment_compressed_ = false;
      on_message(msg);
    }

    return true;
  }
};
