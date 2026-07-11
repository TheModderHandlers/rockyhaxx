#pragma once

#define CLEVERFOX_IMPLEMENTATION
#include "cleverfox.h"

#include "logger.h"
#include <cmath>
#include <iomanip>
#include <sstream>
#include <string>

using namespace Sfs2X::Entities::Data;
using namespace Sfs2X::Core;
using namespace Sfs2X::Util;

// this may be the wrost code ive ever written just fyi
class SfsDumper {
public:
  void dump_packet(const char *direction, const uint8_t *data, size_t len) {
    if (len < 3)
      return;
    try {
      if (looks_like_ws_noseq(data, len))
        dump_ws_noseq(direction, data, len);
      else if (looks_like_ws_seq(data, len))
        dump_ws_seq(direction, data, len);
      else if (data[0] == 0x12)
        dump_raw_obj(direction, data, len);
      else if ((data[0] & 0x80) != 0)
        dump_tcp(direction, data, len);
      else {
        g_log.write(0x08, "\n--- %s (%zu bytes, unknown) ---\n", direction,
                    len);
        g_log.hex_dump(data, len > 512 ? 512 : len);
      }
    } catch (const std::exception &e) {
      g_log.err("\n--- %s DECODE ERROR: %s ---\n", direction, e.what());
      g_log.hex_dump(data, len > 256 ? 256 : len);
    } catch (...) {
      g_log.err("\n--- %s DECODE ERROR ---\n", direction);
      g_log.hex_dump(data, len > 256 ? 256 : len);
    }
  }

private:
  static bool ascii_ok(const uint8_t *p, size_t n) {
    for (size_t i = 0; i < n; i++)
      if (p[i] < 0x20 || p[i] > 0x7E)
        return false;
    return true;
  }
  static bool looks_like_ws_noseq(const uint8_t *d, size_t len) {
    if (len < 5)
      return false;
    uint16_t cl = ((uint16_t)d[0] << 8) | d[1];
    if (cl == 0 || cl > 255 || (size_t)(2 + cl) >= len)
      return false;
    return ascii_ok(d + 2, cl) && d[2 + cl] == 0x12;
  }
  static bool looks_like_ws_seq(const uint8_t *d, size_t len) {
    if (len < 12)
      return false;
    uint16_t cl = ((uint16_t)d[8] << 8) | d[9];
    if (cl == 0 || cl > 255 || (size_t)(10 + cl) > len)
      return false;
    return ascii_ok(d + 10, cl);
  }
  void dump_ws_noseq(const char *dir, const uint8_t *d, size_t len) {
    size_t pos = 0;
    uint16_t cl = ((uint16_t)d[0] << 8) | d[1];
    pos += 2;
    std::string cmd(reinterpret_cast<const char *>(d + pos), cl);
    pos += cl;
    g_log.write(0x0B, "\n--- %s ", dir);
    g_log.write(0x0F, "%s", cmd.c_str());
    g_log.write(0x08, " (%zu bytes) ---\n", len);
    if (pos < len)
      emit_obj(d + pos, len - pos);
  }
  void dump_ws_seq(const char *dir, const uint8_t *d, size_t len) {
    long long seq = 0;
    for (int i = 0; i < 8; i++)
      seq = (seq << 8) | d[i];
    size_t pos = 8;
    uint16_t cl = ((uint16_t)d[pos] << 8) | d[pos + 1];
    pos += 2;
    std::string cmd(reinterpret_cast<const char *>(d + pos), cl);
    pos += cl;
    g_log.write(0x0B, "\n--- %s #%lld ", dir, seq);
    g_log.write(0x0F, "%s", cmd.c_str());
    g_log.write(0x08, " (%zu bytes) ---\n", len);
    if (pos < len)
      emit_obj(d + pos, len - pos);
    else
      g_log.info("{}\n");
  }
  void dump_raw_obj(const char *dir, const uint8_t *d, size_t len) {
    g_log.write(0x0B, "\n--- %s ", dir);
    g_log.write(0x08, "(%zu bytes) ---\n", len);
    emit_obj(d, len);
  }
  void dump_tcp(const char *dir, const uint8_t *d, size_t len) {
    size_t pos = 0;
    auto hdr = PacketHeader::FromBinary(d[pos++]);
    int32_t sz;
    if (hdr->BigSized()) {
      if (len < pos + 4)
        return;
      sz = ((int32_t)d[pos] << 24) | ((int32_t)d[pos + 1] << 16) |
           ((int32_t)d[pos + 2] << 8) | d[pos + 3];
      pos += 4;
    } else {
      if (len < pos + 2)
        return;
      sz = ((int32_t)d[pos] << 8) | d[pos + 1];
      pos += 2;
    }
    if ((size_t)(pos + sz) > len)
      return;
    g_log.write(0x0B, "\n--- %s ", dir);
    g_log.write(0x08, "(%d bytes) ---\n", sz);
    auto vec =
        std::make_shared<std::vector<unsigned char>>(d + pos, d + pos + sz);
    auto ba = std::make_shared<ByteArray>(vec);
    if (hdr->Compressed())
      ba->Uncompress();
    auto obj = SFSObject::NewFromBinaryData(ba);
    g_log.info("%s\n", to_json_obj(obj, 0).c_str());
  }
  void emit_obj(const uint8_t *d, size_t len) {
    auto vec = std::make_shared<std::vector<unsigned char>>(d, d + len);
    auto ba = std::make_shared<ByteArray>(vec);
    auto obj = SFSObject::NewFromBinaryData(ba);
    g_log.info("%s\n", to_json_obj(obj, 0).c_str());
  }
  static std::string ind(int d) { return std::string(d * 2, ' '); }
  static std::string json_escape(const std::string &s) {
    std::string out;
    out.reserve(s.size() + 8);
    for (unsigned char c : s) {
      switch (c) {
      case '"':
        out += "\\\"";
        break;
      case '\\':
        out += "\\\\";
        break;
      case '\n':
        out += "\\n";
        break;
      case '\r':
        out += "\\r";
        break;
      case '\t':
        out += "\\t";
        break;
      default:
        if (c < 0x20 || c >= 0x7F) {
          char buf[8];
          snprintf(buf, sizeof(buf), "\\u%04x", c);
          out += buf;
        } else {
          out += (char)c;
        }
      }
    }
    return out;
  }
  static const char *type_tag(int t) {
    switch ((SFSDataType)t) {
    case SFSDATATYPE_NULL:
      return "$null";
    case SFSDATATYPE_BOOL:
      return "$bool";
    case SFSDATATYPE_BYTE:
      return "$byte";
    case SFSDATATYPE_SHORT:
      return "$short";
    case SFSDATATYPE_INT:
      return "$int";
    case SFSDATATYPE_LONG:
      return "$long";
    case SFSDATATYPE_FLOAT:
      return "$float";
    case SFSDATATYPE_DOUBLE:
      return "$double";
    case SFSDATATYPE_UTF_STRING:
      return "$str";
    case SFSDATATYPE_TEXT:
      return "$text";
    case SFSDATATYPE_BOOL_ARRAY:
      return "$bool[]";
    case SFSDATATYPE_BYTE_ARRAY:
      return "$byte[]";
    case SFSDATATYPE_SHORT_ARRAY:
      return "$short[]";
    case SFSDATATYPE_INT_ARRAY:
      return "$int[]";
    case SFSDATATYPE_LONG_ARRAY:
      return "$long[]";
    case SFSDATATYPE_FLOAT_ARRAY:
      return "$float[]";
    case SFSDATATYPE_DOUBLE_ARRAY:
      return "$double[]";
    case SFSDATATYPE_UTF_STRING_ARRAY:
      return "$str[]";
    case SFSDATATYPE_SFS_ARRAY:
      return "$arr";
    case SFSDATATYPE_SFS_OBJECT:
      return "$obj";
    case SFSDATATYPE_CLASS:
      return "$class";
    default:
      return "";
    }
  }
  std::string to_json_obj(std::shared_ptr<ISFSObject> obj, int d) {
    auto keys = obj->GetKeys();
    if (keys->empty())
      return "{}";
    std::ostringstream ss;
    ss << "{\n";
    bool first = true;
    for (auto &k : *keys) {
      auto w = obj->GetData(k);
      if (!w)
        continue;
      if (!first)
        ss << ",\n";
      first = false;
      ss << ind(d + 1) << "\"" << json_escape(k) << type_tag((int)w->Type())
         << "\": " << to_json_val(w, d + 1);
    }
    ss << "\n" << ind(d) << "}";
    return ss.str();
  }
  std::string to_json_arr(std::shared_ptr<ISFSArray> arr, int d) {
    if (arr->Size() == 0)
      return "[]";
    std::ostringstream ss;
    ss << "[\n";
    for (long int i = 0; i < arr->Size(); i++) {
      if (i > 0)
        ss << ",\n";
      ss << ind(d + 1) << to_json_val(arr->GetWrappedElementAt(i), d + 1);
    }
    ss << "\n" << ind(d) << "]";
    return ss.str();
  }
  std::string to_json_val(std::shared_ptr<SFSDataWrapper> w, int d) {
    std::ostringstream ss;
    switch ((SFSDataType)(int)w->Type()) {
    case SFSDATATYPE_NULL:
      ss << "null";
      break;
    case SFSDATATYPE_BOOL: {
      auto v = std::static_pointer_cast<bool>(w->Data());
      ss << (*v ? "true" : "false");
      break;
    }
    case SFSDATATYPE_BYTE: {
      auto v = std::static_pointer_cast<unsigned char>(w->Data());
      ss << (int)*v;
      break;
    }
    case SFSDATATYPE_SHORT: {
      auto v = std::static_pointer_cast<short int>(w->Data());
      ss << *v;
      break;
    }
    case SFSDATATYPE_INT: {
      auto v = std::static_pointer_cast<long int>(w->Data());
      ss << *v;
      break;
    }
    case SFSDATATYPE_LONG: {
      auto v = std::static_pointer_cast<long long>(w->Data());
      ss << *v;
      break;
    }
    case SFSDATATYPE_FLOAT: {
      auto v = std::static_pointer_cast<float>(w->Data());
      if (std::isfinite(*v))
        ss << *v;
      else
        ss << "null";
      break;
    }
    case SFSDATATYPE_DOUBLE: {
      auto v = std::static_pointer_cast<double>(w->Data());
      if (std::isfinite(*v))
        ss << std::setprecision(15) << *v;
      else
        ss << "null";
      break;
    }
    case SFSDATATYPE_UTF_STRING:
    case SFSDATATYPE_TEXT: {
      auto v = std::static_pointer_cast<std::string>(w->Data());
      ss << "\"" << json_escape(*v) << "\"";
      break;
    }
    case SFSDATATYPE_BOOL_ARRAY: {
      auto v = std::static_pointer_cast<std::vector<bool>>(w->Data());
      ss << "[";
      for (size_t i = 0; i < v->size(); i++) {
        if (i)
          ss << ", ";
        ss << ((*v)[i] ? "true" : "false");
      }
      ss << "]";
      break;
    }
    case SFSDATATYPE_BYTE_ARRAY: {
      auto v = std::static_pointer_cast<ByteArray>(w->Data());
      ss << "\"<" << v->Length() << " bytes>\"";
      break;
    }
    case SFSDATATYPE_SHORT_ARRAY: {
      auto v = std::static_pointer_cast<std::vector<short int>>(w->Data());
      ss << "[";
      for (size_t i = 0; i < v->size(); i++) {
        if (i)
          ss << ", ";
        ss << (*v)[i];
      }
      ss << "]";
      break;
    }
    case SFSDATATYPE_INT_ARRAY: {
      auto v = std::static_pointer_cast<std::vector<long int>>(w->Data());
      ss << "[";
      for (size_t i = 0; i < v->size(); i++) {
        if (i)
          ss << ", ";
        ss << (*v)[i];
      }
      ss << "]";
      break;
    }
    case SFSDATATYPE_LONG_ARRAY: {
      auto v = std::static_pointer_cast<std::vector<long long>>(w->Data());
      ss << "[";
      for (size_t i = 0; i < v->size(); i++) {
        if (i)
          ss << ", ";
        ss << (*v)[i];
      }
      ss << "]";
      break;
    }
    case SFSDATATYPE_FLOAT_ARRAY: {
      auto v = std::static_pointer_cast<std::vector<float>>(w->Data());
      ss << "[";
      for (size_t i = 0; i < v->size(); i++) {
        if (i)
          ss << ", ";
        ss << (*v)[i];
      }
      ss << "]";
      break;
    }
    case SFSDATATYPE_DOUBLE_ARRAY: {
      auto v = std::static_pointer_cast<std::vector<double>>(w->Data());
      ss << "[";
      for (size_t i = 0; i < v->size(); i++) {
        if (i)
          ss << ", ";
        ss << std::setprecision(15) << (*v)[i];
      }
      ss << "]";
      break;
    }
    case SFSDATATYPE_UTF_STRING_ARRAY: {
      auto v = std::static_pointer_cast<std::vector<std::string>>(w->Data());
      ss << "[";
      for (size_t i = 0; i < v->size(); i++) {
        if (i)
          ss << ", ";
        ss << "\"" << json_escape((*v)[i]) << "\"";
      }
      ss << "]";
      break;
    }
    case SFSDATATYPE_SFS_ARRAY: {
      auto v = std::static_pointer_cast<ISFSArray>(w->Data());
      ss << to_json_arr(v, d);
      break;
    }
    case SFSDATATYPE_SFS_OBJECT: {
      auto v = std::static_pointer_cast<ISFSObject>(w->Data());
      ss << to_json_obj(v, d);
      break;
    }
    default:
      ss << "null";
      break;
    }
    return ss.str();
  }
};
inline SfsDumper g_dumper;
