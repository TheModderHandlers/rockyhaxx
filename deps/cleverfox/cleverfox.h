// ===================================================================
// cleverfox.h - SmartFoxServer 2X Binary Protocol
//
// Single-header library for serialization/deserialization of
// SmartFoxServer 2X binary packets.
//
// Dependencies: zlib (link with -lz or compile zlib sources alongside)
//
// Usage:
//   In exactly ONE .cpp file, before including this header:
//     #define CLEVERFOX_IMPLEMENTATION
//     #include "cleverfox.h"
//
//   In all other files:
//     #include "cleverfox.h"
// ===================================================================
#ifndef CLEVERFOX_H
#define CLEVERFOX_H

#include <memory>
#include <stdexcept>
#include <cstdint>
#include <cstring>
#include <cmath>
#include <climits>
#include <bitset>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <stdio.h>
#include <zlib.h>

// --- Util/Common.h ---
#if defined(WIN32) && defined(SMARTFOXCLIENTAPI_EXPORTS)
    #define DLLImportExport __declspec(dllexport)
#else
    #define DLLImportExport
#endif

template<typename T>
struct array_deleter {
    void operator()(T const* p) { delete[] p; }
};

// Forward declarations for circular dependency resolution
namespace Sfs2X {
namespace Entities {
namespace Data {
    class ISFSObject;
    class ISFSArray;
}
}
}

// --- Entities/Data/SFSDataType.h ---
// ===================================================================
//
// Description		
//		Contains the definition of SFSDataType
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================

namespace Sfs2X {
namespace Entities {
namespace Data {

    enum SFSDataType 
    {
		/// <summary>
		/// Null value
		/// </summary>
		SFSDATATYPE_NULL = 0,
		
		/// <summary>
		/// Boolean
		/// </summary>
		SFSDATATYPE_BOOL = 1,
		
		/// <summary>
		/// Byte, signed 8 bit
		/// </summary>
		SFSDATATYPE_BYTE = 2,
		
		/// <summary>
		/// Short integer, signed 16 bit
		/// </summary>
		SFSDATATYPE_SHORT = 3,
		
		/// <summary>
		/// Integer, signed 32 bit
		/// </summary>
		SFSDATATYPE_INT = 4,
		
		/// <summary>
		/// Long integer, signed 64 bit
		/// </summary>
		SFSDATATYPE_LONG = 5,

		/// <summary>
		/// Floating point decimal, signed 32 bit
		/// </summary>
		SFSDATATYPE_FLOAT = 6,
		
		/// <summary>
		/// Double precision decimal, signed 64 bit
		/// </summary>
		SFSDATATYPE_DOUBLE = 7,
		
		/// <summary>
		/// UTF-8 Encoded string, with length up to 32 KBytes.
		/// </summary>
		SFSDATATYPE_UTF_STRING = 8,
		
		/// <summary>
		/// Array of Booleans
		/// </summary>
		SFSDATATYPE_BOOL_ARRAY = 9,
		
		/// <summary>
		/// Array of Bytes (treated as ByteArray)
		/// </summary>
		SFSDATATYPE_BYTE_ARRAY = 10,
		
		/// <summary>
		/// Array of Shorts
		/// </summary>
		SFSDATATYPE_SHORT_ARRAY = 11,
		
		/// <summary>
		/// Array of Integers
		/// </summary>
		SFSDATATYPE_INT_ARRAY = 12,
		
		/// <summary>
		/// Array of Long integers
		/// </summary>
		SFSDATATYPE_LONG_ARRAY = 13,
		
		/// <summary>
		/// Array of Floats
		/// </summary>
		SFSDATATYPE_FLOAT_ARRAY = 14,
		
		/// <summary>
		/// Array of Doubles
		/// </summary>
		SFSDATATYPE_DOUBLE_ARRAY = 15,
		
		/// <summary>
		/// Array of UTF-8 Strings
		/// </summary>
		SFSDATATYPE_UTF_STRING_ARRAY = 16,
		
		/// <summary>
		/// SFSArray
		/// </summary>
		/// <seealso cref="SFSArray"/>
		SFSDATATYPE_SFS_ARRAY = 17,
		
		/// <summary>
		/// SFSObject
		/// </summary>
		/// <seealso cref="SFSObject"/>
		SFSDATATYPE_SFS_OBJECT = 18,
		
		/// <summary>
		/// Uses SFSObject to serialize Class instances
		/// </summary>
		SFSDATATYPE_CLASS = 19,

		/// <summary>
		/// UTF-8 encoded string, with length up to 2 GBytes.
		/// </summary>
		SFSDATATYPE_TEXT = 20
    };

}	// namespace Data
}	// namespace Entities
}	// namespace Sfs2X


// --- Util/StringFormatter.h ---
// ===================================================================
//
// Description		
//		Contains the utility to format strings
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================


#if defined(_MSC_VER)
#endif
using namespace std;					// STL library: declare the STL namespace

namespace Sfs2X {
namespace Util {

	// -------------------------------------------------------------------
	// StringFormatter
	// -------------------------------------------------------------------
	template<class Type1>
	static void StringFormatter (std::shared_ptr<string> stringToFormat, std::shared_ptr<string> stringFormat, Type1 p1)
	{
		long int previousStringSize = (long int)stringToFormat->size();
		stringToFormat->resize(previousStringSize + 4096);
		long int addedStringSize = sprintf ((char*)(stringToFormat->c_str()), (const char*)(stringFormat->c_str()), p1);
		if (addedStringSize > -1) 
		{
			stringToFormat->resize(previousStringSize + addedStringSize);
		}
		else
		{
			stringToFormat->resize(previousStringSize);
		}
	}

	// -------------------------------------------------------------------
	// StringFormatter
	// -------------------------------------------------------------------
	template<class Type1, class Type2>
	static void StringFormatter (std::shared_ptr<string> stringToFormat, std::shared_ptr<string> stringFormat, Type1 p1, Type2 p2)
	{
		long int previousStringSize = (long int)stringToFormat->size();
		stringToFormat->resize(previousStringSize + 4096);
		long int addedStringSize = sprintf ((char*)(stringToFormat->c_str()), (const char*)(stringFormat->c_str()), p1, p2);
		if (addedStringSize > -1) 
		{
			stringToFormat->resize(previousStringSize + addedStringSize);
		}
		else
		{
			stringToFormat->resize(previousStringSize);
		}
	}

	// -------------------------------------------------------------------
	// StringFormatter
	// -------------------------------------------------------------------
	template<class Type1, class Type2, class Type3>
	static void StringFormatter (std::shared_ptr<string> stringToFormat, std::shared_ptr<string> stringFormat, Type1 p1, Type2 p2, Type3 p3)
	{
		long int previousStringSize = (long int)stringToFormat->size();
		stringToFormat->resize(previousStringSize + 4096);
		long int addedStringSize = sprintf ((char*)stringToFormat->c_str(), (char*)stringFormat->c_str(), p1, p2, p3);
		if (addedStringSize > -1) 
		{
			stringToFormat->resize(previousStringSize + addedStringSize);
		}
		else
		{
			stringToFormat->resize(previousStringSize);
		}
	}

	// -------------------------------------------------------------------
	// StringFormatter
	// -------------------------------------------------------------------
	template<class Type1, class Type2, class Type3, class Type4>
	static void StringFormatter (std::shared_ptr<string> stringToFormat, std::shared_ptr<string> stringFormat, Type1 p1, Type2 p2, Type3 p3, Type4 p4)
	{
		long int previousStringSize = stringToFormat->size();
		stringToFormat->resize(previousStringSize + 4096);
		long int addedStringSize = sprintf ((char*)stringToFormat->c_str(), (char*)stringFormat->c_str(), p1, p2, p3, p4);
		if (addedStringSize > -1) 
		{
			stringToFormat->resize(previousStringSize + addedStringSize);
		}
		else
		{
			stringToFormat->resize(previousStringSize);
		}
	}

	// -------------------------------------------------------------------
	// Utf8toWStr
	// -------------------------------------------------------------------
	static void Utf8toWStr(std::shared_ptr<string> src, std::shared_ptr<wstring> dest)
	{
		dest->clear();
		wchar_t w = 0;
		int bytes = 0;
		wchar_t err = L'?';
		for (size_t i = 0; i < src->size(); i++)
		{
			unsigned char c = (unsigned char)(*src)[i];
			if (c <= 0x7f)
			{
				//first byte
				if (bytes)
				{
					dest->push_back(err);
					bytes = 0;
				}
				dest->push_back((wchar_t)c);
			}
			else if (c <= 0xbf)
			{
				//second/third/etc byte
				if (bytes){
					w = ((w << 6)|(c & 0x3f));
					bytes--;
					if (bytes == 0)
						dest->push_back(w);
				}
				else
					dest->push_back(err);
			}
			else if (c <= 0xdf)
			{
				//2byte sequence start
				bytes = 1;
				w = c & 0x1f;
			}
			else if (c <= 0xef)
			{
				//3byte sequence start
				bytes = 2;
				w = c & 0x0f;
			}
			else if (c <= 0xf7)
			{
				//3byte sequence start
				bytes = 3;
				w = c & 0x07;
			}
			else
			{
				dest->push_back(err);
				bytes = 0;
			}
		}
		if (bytes)
			dest->push_back(err);
	}

	// -------------------------------------------------------------------
	// WStrToUtf8
	// -------------------------------------------------------------------
	static void WStrToUtf8(std::shared_ptr<wstring> src, std::shared_ptr<string> dest)
	{
		dest->clear();
		for (size_t i = 0; i < src->size(); i++)
		{
			wchar_t w = (*src)[i];
			if (w <= 0x7f)
				dest->push_back((char)w);
			else if (w <= 0x7ff)
			{
				dest->push_back(0xc0 | ((w >> 6)& 0x1f));
				dest->push_back(0x80| (w & 0x3f));
			}
			else if (w <= 0xffff)
			{
				dest->push_back(0xe0 | ((w >> 12)& 0x0f));
				dest->push_back(0x80| ((w >> 6) & 0x3f));
				dest->push_back(0x80| (w & 0x3f));
			}
			else if (w <= 0x10ffff)
			{
				dest->push_back(0xf0 | (((unsigned long int)w >> 18) & 0x07));
				dest->push_back(0x80| ((w >> 12) & 0x3f));
				dest->push_back(0x80| ((w >> 6) & 0x3f));
				dest->push_back(0x80| (w & 0x3f));
			}
			else
				dest->push_back('?');
		}
	}

}	// namespace Util
}	// namespace Sfs2X


// --- Util/ByteArray.h ---
// ===================================================================
//
// Description		
//		Contains the definition of ByteArray
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================


#if defined(_MSC_VER)
#endif
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X::Entities::Data;

#define ZlibChunk 1024			// Chunk size (bytes) for Zlib buffers

namespace Sfs2X {
namespace Util {

	// -------------------------------------------------------------------
	// Class ByteArray
	// -------------------------------------------------------------------
	class DLLImportExport ByteArray
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		ByteArray();
		ByteArray(std::shared_ptr<vector<unsigned char> > buf);
		~ByteArray();

		std::shared_ptr<vector<unsigned char> > Bytes();
		void Bytes(std::shared_ptr<vector<unsigned char> > value);

		long int Length();
		long int Position();
		void Position(long int value);

		long int BytesAvailable();

		bool Compressed();
		void Compressed(bool value);

		void Compress();
		void Uncompress();
		void CheckCompressedWrite();
		void CheckCompressedRead();

		void ReverseOrder(vector<unsigned char>& dt);

		void WriteByte(std::shared_ptr<SFSDataType> tp);
		void WriteByte(unsigned char b);
		void WriteBytes(std::shared_ptr<vector<unsigned char> > data);
		void WriteBytes(std::shared_ptr<vector<unsigned char> > data, long int ofs, long int count);
		void WriteBool(bool b);
		void WriteInt(int32_t i);
		void WriteUShort(unsigned short int us);
		void WriteShort(short int s);
		void WriteLong(long long l);
		void WriteFloat(float f);
		void WriteDouble(double d);
		void WriteUTF(std::shared_ptr<string> str);
		void WriteUTF(string str);
		void WriteText(std::shared_ptr<string> str);
		void WriteText(string str);

		void ReadByte(unsigned char&);
		void ReadBytes(long int count, vector<unsigned char>&);
		void ReadBytes(long int offset, long int count, vector<unsigned char>&);
		void ReadBool(bool&);
		void ReadInt(int32_t&);
		void ReadUShort(unsigned short int&);
		void ReadShort(short int&);
		void ReadLong(long long&);
		void ReadFloat(float&);
		void ReadDouble(double&);
		void ReadUTF(string&);
		void ReadText(string&);

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------

	protected:

		// -------------------------------------------------------------------
		// Protected methods
		// -------------------------------------------------------------------

		// -------------------------------------------------------------------
		// Protected members
		// -------------------------------------------------------------------


	private:

		// -------------------------------------------------------------------
		// Private methods
		// -------------------------------------------------------------------

		bool IsLittleEndian();

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------

		std::shared_ptr<vector<unsigned char> > buffer;
		long int position;
		bool compressed;

		bool zLibIsInitialized;
		z_stream zlibStrm;
	    unsigned char zlibIn[ZlibChunk];
	    unsigned char zlibOut[ZlibChunk];
	};

}	// namespace Util
}	// namespace Sfs2X


// --- Entities/Data/SFSDataWrapper.h ---
// ===================================================================
//
// Description		
//		Contains the definition of SFSDataWrapper
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================


#if defined(_MSC_VER)
#endif
using namespace std;					// STL library: declare the STL namespace

namespace Sfs2X {
namespace Entities {
namespace Data {

	/// <summary>
	/// A wrapper object used by SFSObject and SFSArray to encapsulate data and relative types
	/// </summary>
	class DLLImportExport SFSDataWrapper
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		SFSDataWrapper(long int type, std::shared_ptr<void> data);
		SFSDataWrapper(SFSDataType tp, std::shared_ptr<void> data);
		~SFSDataWrapper();

		long int Type();
		std::shared_ptr<void> Data();

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------

	protected:

		// -------------------------------------------------------------------
		// Protected methods
		// -------------------------------------------------------------------

		// -------------------------------------------------------------------
		// Protected members
		// -------------------------------------------------------------------

	private:

		// -------------------------------------------------------------------
		// Private methods
		// -------------------------------------------------------------------
		
		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------

		long int type;
		std::shared_ptr<void> data;
	};

}	// namespace Data
}	// namespace Entities
}	// namespace Sfs2X


// --- Protocol/Serialization/SerializableSFSType.h ---
// ===================================================================
//
// Description		
//		Contains the definition of SerializableSFSType interface
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================

namespace Sfs2X {
namespace Protocol {
namespace Serialization {

	// -------------------------------------------------------------------
	// Class SerializableSFSType
	// -------------------------------------------------------------------
	class SerializableSFSType
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------
		
	protected:

		// -------------------------------------------------------------------
		// Protected methods
		// -------------------------------------------------------------------

		// -------------------------------------------------------------------
		// Protected members
		// -------------------------------------------------------------------

	private:

		// -------------------------------------------------------------------
		// Private methods
		// -------------------------------------------------------------------

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------
	};

}	// namespace Serialization
}	// namespace Protocol
}	// namespace Sfs2X


// --- Entities/Data/ISFSObject.h ---
// ===================================================================
//
// Description		
//		Contains the definition of ISFSObject interface
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================

// Forward class declaration
namespace Sfs2X {
namespace Entities {
namespace Data {
	class ISFSObject;
}	// namespace Data
}	// namespace Entities
}	// namespace Sfs2X


#if defined(_MSC_VER)
#endif
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X::Util;

namespace Sfs2X {
namespace Entities {
namespace Data {

	/// <summary>
	/// SFSObject interface
	/// </summary>
	class DLLImportExport ISFSObject
	{
	public:
		/// <summary>
		/// Indicates if the value mapped by the specified key is <c>null</c>.
		/// </summary>
		/// 
		/// <param name="key">The key to be checked.</param>
		/// 
		/// <returns><c>true</c> if the value mapped by the passed key is <c>null</c> or the mapping doesn't exist for that key.</returns>
		virtual bool IsNull(string key) = 0;

		/// <summary>
		/// Indicates if the value mapped by the specified key is <c>null</c>.
		/// </summary>
		/// 
		/// <param name="key">The key to be checked.</param>
		/// 
		/// <returns><c>true</c> if the value mapped by the passed key is <c>null</c> or the mapping doesn't exist for that key.</returns>
		virtual bool IsNull(std::shared_ptr<string> key) = 0;

		/// <summary>
		/// Indicates whether this object contains a mapping for the specified key or not.
		/// </summary>
		/// 
		/// <param name="key">The key whose presence in this object is to be tested.</param>
		/// 
		/// <returns><c>true</c> if this object contains a mapping for the specified key.</returns>
		virtual bool ContainsKey(string key) = 0;

		/// <summary>
		/// Indicates whether this object contains a mapping for the specified key or not.
		/// </summary>
		/// 
		/// <param name="key">The key whose presence in this object is to be tested.</param>
		/// 
		/// <returns><c>true</c> if this object contains a mapping for the specified key.</returns>
		virtual bool ContainsKey(std::shared_ptr<string> key) = 0;

		/// <summary>
		/// Removes the element corresponding to the passed key from this object.
		/// </summary>
		/// 
		/// <param name="key">The key of the element to be removed.</param>
		virtual void RemoveElement(string key) = 0;

		/// <summary>
		/// Removes the element corresponding to the passed key from this object.
		/// </summary>
		/// 
		/// <param name="key">The key of the element to be removed.</param>
		virtual void RemoveElement(std::shared_ptr<string> key) = 0;

		/// <summary>
		/// Retrieves a list of all the keys contained in this object.
		/// </summary>
		/// 
		/// <returns>The list of all the keys in this object.</returns>
		virtual std::shared_ptr<vector<string> > GetKeys() = 0;
		
		/// <summary>
		/// Indicates the number of elements in this object.
		/// </summary>
		/// 
		/// <returns>The number of elements in this object.</returns>
		virtual long int Size() = 0;
		
		/// <summary>
		/// Provides the binary form of this object.
		/// </summary>
		/// 
		/// <returns>The binary data representing this object.</returns>
		virtual std::shared_ptr<ByteArray> ToBinary() = 0;
		
		/// <summary>
		/// Provides a formatted string representing this object.
		/// </summary>
		/// 
		/// <remarks>
		/// The returned string can be logged or traced in the console for debugging purposes.
		/// </remarks>
		/// 
		/// <param name="format">If <c>true</c>, the output is formatted in a human-readable way.</param>
		/// 
		/// <returns>The string representation of this object.</returns>
		virtual std::shared_ptr<string> GetDump(bool format) = 0; 
		
		/// <summary>
		/// See <see cref="GetDump(bool)"/>.
		/// </summary>
		virtual std::shared_ptr<string> GetDump() = 0;  // default to true

		/// <summary>
		/// Provides a detailed hexadecimal representation of this object.
		/// </summary>
		/// 
		/// <remarks>
		/// The returned string can be logged or traced in the console for debugging purposes.
		/// </remarks>
		/// 
		/// <returns>The hexadecimal string representation of this object.</returns>
		virtual std::shared_ptr<string> GetHexDump() = 0;

		/*
		* :::::::::::::::::::::::::::::::::::::::::
		* Type getters
		* :::::::::::::::::::::::::::::::::::::::::	
		*/

		/// <exclude />
		virtual std::shared_ptr<SFSDataWrapper> GetData(string key) = 0;
		virtual std::shared_ptr<SFSDataWrapper> GetData(std::shared_ptr<string> key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as a boolean.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object associated with the specified key; <c>false</c> if a mapping for the passed key doesn't exist.</returns>
		virtual std::shared_ptr<bool> GetBool(string key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as a boolean.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object associated with the specified key; <c>false</c> if a mapping for the passed key doesn't exist.</returns>
		virtual std::shared_ptr<bool> GetBool(std::shared_ptr<string> key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as a signed byte (8 bits).
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object associated with the specified key; <c>0</c> if a mapping for the passed key doesn't exist.</returns>
		virtual std::shared_ptr<unsigned char> GetByte(string key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as a signed byte (8 bits).
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object associated with the specified key; <c>0</c> if a mapping for the passed key doesn't exist.</returns>
		virtual std::shared_ptr<unsigned char> GetByte(std::shared_ptr<string> key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as a short integer (16 bits).
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object associated with the specified key; <c>0</c> if a mapping for the passed key doesn't exist.</returns>
		virtual std::shared_ptr<short int> GetShort(string key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as a short integer (16 bits).
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object associated with the specified key; <c>0</c> if a mapping for the passed key doesn't exist.</returns>
		virtual std::shared_ptr<short int> GetShort(std::shared_ptr<string> key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an integer (32 bits).
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object associated with the specified key; <c>0</c> if a mapping for the passed key doesn't exist.</returns>
		virtual std::shared_ptr<long int> GetInt(string key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an integer (32 bits).
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object associated with the specified key; <c>0</c> if a mapping for the passed key doesn't exist.</returns>
		virtual std::shared_ptr<long int> GetInt(std::shared_ptr<string> key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as a long integer (64 bits).
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object associated with the specified key; <c>0</c> if a mapping for the passed key doesn't exist.</returns>
		virtual std::shared_ptr<long long> GetLong(string key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as a long integer (64 bits).
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object associated with the specified key; <c>0</c> if a mapping for the passed key doesn't exist.</returns>
		virtual std::shared_ptr<long long> GetLong(std::shared_ptr<string> key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as a floating point number.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object associated with the specified key; <c>0</c> if a mapping for the passed key doesn't exist.</returns>
		virtual std::shared_ptr<float> GetFloat(string key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as a floating point number.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object associated with the specified key; <c>0</c> if a mapping for the passed key doesn't exist.</returns>
		virtual std::shared_ptr<float> GetFloat(std::shared_ptr<string> key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as a double precision number.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object associated with the specified key; <c>0</c> if a mapping for the passed key doesn't exist.</returns>
		virtual std::shared_ptr<double> GetDouble(string key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as a double precision number.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object associated with the specified key; <c>0</c> if a mapping for the passed key doesn't exist.</returns>
		virtual std::shared_ptr<double> GetDouble(std::shared_ptr<string> key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an UTF-8 string, with max length of 32 KBytes.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object associated with the specified key; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		virtual std::shared_ptr<string> GetUtfString(string key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an UTF-8 string, with max length of 32 KBytes.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object associated with the specified key; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		virtual std::shared_ptr<string> GetUtfString(std::shared_ptr<string> key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an UTF-8 string, with max length of 2 GBytes.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object associated with the specified key; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		virtual std::shared_ptr<string> GetText(string key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an UTF-8 string, with max length of 2 GBytes.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object associated with the specified key; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		virtual std::shared_ptr<string> GetText(std::shared_ptr<string> key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an array of booleans.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object as an array of booleans; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		virtual std::shared_ptr<vector<bool> > GetBoolArray(string key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an array of booleans.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object as an array of booleans; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		virtual std::shared_ptr<vector<bool> > GetBoolArray(std::shared_ptr<string> key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as a ByteArray object.
		/// </summary>
		/// 
		/// <remarks>
		/// <b>IMPORTANT</b>: ByteArrays transmission is not supported in Unity WebGL.
		/// </remarks>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object as a ByteArray object; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		virtual std::shared_ptr<ByteArray> GetByteArray(string key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as a ByteArray object.
		/// </summary>
		/// 
		/// <remarks>
		/// <b>IMPORTANT</b>: ByteArrays transmission is not supported in Unity WebGL.
		/// </remarks>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object as a ByteArray object; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		virtual std::shared_ptr<ByteArray> GetByteArray(std::shared_ptr<string> key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an array of shorts.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object as an array of shorts; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		virtual std::shared_ptr<vector<short int> > GetShortArray(string key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an array of shorts.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object as an array of shorts; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		virtual std::shared_ptr<vector<short int> > GetShortArray(std::shared_ptr<string> key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an array of integers.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object as an array of integers; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		virtual std::shared_ptr<vector<long int> > GetIntArray(string key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an array of integers.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object as an array of integers; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		virtual std::shared_ptr<vector<long int> > GetIntArray(std::shared_ptr<string> key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an array of longs.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object as an array of longs; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		virtual std::shared_ptr<vector<long long> > GetLongArray(string key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an array of longs.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object as an array of longs; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		virtual std::shared_ptr<vector<long long> > GetLongArray(std::shared_ptr<string> key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an array of floats.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object as an array of floats; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		virtual std::shared_ptr<vector<float> > GetFloatArray(string key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an array of floats.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object as an array of floats; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		virtual std::shared_ptr<vector<float> > GetFloatArray(std::shared_ptr<string> key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an array of doubles.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object as an array of doubles; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		virtual std::shared_ptr<vector<double> > GetDoubleArray(string key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an array of doubles.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object as an array of doubles; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		virtual std::shared_ptr<vector<double> > GetDoubleArray(std::shared_ptr<string> key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an array of UTF-8 strings.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object as an array of UTF-8 strings; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		virtual std::shared_ptr<vector<string> > GetUtfStringArray(string key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an array of UTF-8 strings.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object as an array of UTF-8 strings; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		virtual std::shared_ptr<vector<string> > GetUtfStringArray(std::shared_ptr<string> key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an ISFSArray object.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object as an object implementing the ISFSArray interface; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		/// 
		/// <seealso cref="SFSArray"/>
		virtual std::shared_ptr<ISFSArray> GetSFSArray(string key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an ISFSArray object.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object as an object implementing the ISFSArray interface; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		/// 
		/// <seealso cref="SFSArray"/>
		virtual std::shared_ptr<ISFSArray> GetSFSArray(std::shared_ptr<string> key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an ISFSObject object.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object as an object implementing the ISFSObject interface; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		/// 
		/// <seealso cref="SFSObject"/>
		virtual std::shared_ptr<ISFSObject> GetSFSObject(string key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an ISFSObject object.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object as an object implementing the ISFSObject interface; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		/// 
		/// <seealso cref="SFSObject"/>
		virtual std::shared_ptr<ISFSObject> GetSFSObject(std::shared_ptr<string> key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an instance of a custom class.
		/// </summary>
		/// <remarks>
		/// This advanced feature allows the transmission of specific object instances between client-side C++ and server-side Java provided that:<br/>
		/// - the respective class definitions on both sides have the same package name<br/>
		/// - the following code is executed right after creating the SmartFox object: <c>DefaultSFSDataSerializer.RunningAssembly = Assembly.GetExecutingAssembly();</c> (requires <c>System.Reflection</c> and <c>Sfs2X.Protocol.Serialization</c>)
		/// </remarks>
		/// <example>
		/// This is an example of the same class on the server and client side:
		/// 
		/// <b>Server Java code:</b>
		///			\code{.cpp}
		/// 			package my.game.spacecombat
		/// 
		/// 			public class SpaceShip
		/// 			{
		/// 				private String type;
		/// 				private String name;
		/// 				private int firePower;
		/// 				private int maxSpeed;
		/// 				private List<String> weapons;
		/// 
		/// 				public SpaceShip(String name, String type)
		/// 				{
		/// 					this.name = name;
		/// 					this.type = type;
		/// 				}
		/// 
		/// 				// ... Getters / Setters ...
		/// 			}
		/// 		\endcode
		/// 
		/// <b>Client AS3 code:</b>
		///			\code{.cpp}
		/// 		package my.game.spacecombat
		/// 		{
		/// 			public class SpaceShip
		/// 			{
		/// 				private var _type:String
		/// 				private var _name:String
		/// 				private var _firePower:int;
		/// 				private var _maxSpeed:int;
		/// 				private var _weapons:Array;
		/// 
		/// 				public SpaceShip(name:String, type:Strig)
		/// 				{
		/// 					_name = name
		/// 					_type = type
		/// 				}
		/// 
		/// 				// ... Getters / Setters ...
		/// 			}
		/// 		}	
		/// 			
		/// 		\endcode
		/// 
		/// 	A SpaceShip instance from server side is sent to the client. This is how you get it: 
		///		\code{.cpp}
		///			std::shared_ptr<string> name (new string("spaceShip"));
		///			std::shared_ptr<SpaceShip> mySpaceShip = (std::static_pointer_cast<SpaceShip>)sfsObject->getClass(name) 
		/// 	\endcode
		/// </example>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <returns>
		/// A void pointer
		/// </returns>
		virtual std::shared_ptr<void> GetClass(string key) = 0;
		virtual std::shared_ptr<void> GetClass(std::shared_ptr<string> key) = 0;

		/*
		* :::::::::::::::::::::::::::::::::::::::::
		* Type setters
		* :::::::::::::::::::::::::::::::::::::::::	
		*/

		/// <exclude />
		virtual void PutNull(string key) = 0;
		virtual void PutNull(std::shared_ptr<string> key) = 0;
		
		/// <summary>
		/// Associates the passed boolean value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutBool(string key, std::shared_ptr<bool> val) = 0;

		/// <summary>
		/// Associates the passed boolean value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutBool(std::shared_ptr<string> key, std::shared_ptr<bool> val) = 0;

		/// <summary>
		/// Associates the passed boolean value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutBool(string key, bool val) = 0;

		/// <summary>
		/// Associates the passed boolean value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutBool(std::shared_ptr<string> key, bool val) = 0;

		/// <summary>
		/// Associates the passed byte value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutByte(string key, std::shared_ptr<unsigned char> val) = 0;

		/// <summary>
		/// Associates the passed byte value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutByte(std::shared_ptr<string> key, std::shared_ptr<unsigned char> val) = 0;

		/// <summary>
		/// Associates the passed byte value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutByte(string key, unsigned char val) = 0;

		/// <summary>
		/// Associates the passed byte value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutByte(std::shared_ptr<string> key, unsigned char val) = 0;

		/// <summary>
		/// Associates the passed short value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutShort(string key, std::shared_ptr<short int> val) = 0;

		/// <summary>
		/// Associates the passed short value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutShort(std::shared_ptr<string> key, std::shared_ptr<short int> val) = 0;

		/// <summary>
		/// Associates the passed short value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutShort(string key, short int val) = 0;

		/// <summary>
		/// Associates the passed short value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutShort(std::shared_ptr<string> key, short int val) = 0;

		/// <summary>
		/// Associates the passed integer value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutInt(string key, std::shared_ptr<long int> val) = 0;

		/// <summary>
		/// Associates the passed integer value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutInt(std::shared_ptr<string> key, std::shared_ptr<long int> val) = 0;

		/// <summary>
		/// Associates the passed integer value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutInt(string key, long int val) = 0;

		/// <summary>
		/// Associates the passed integer value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutInt(std::shared_ptr<string> key, long int val) = 0;

		/// <summary>
		/// Associates the passed long value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutLong(string key, std::shared_ptr<long long> val) = 0;

		/// <summary>
		/// Associates the passed long value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutLong(std::shared_ptr<string> key, std::shared_ptr<long long> val) = 0;

		/// <summary>
		/// Associates the passed long value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutLong(string key, long long val) = 0;

		/// <summary>
		/// Associates the passed long value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutLong(std::shared_ptr<string> key, long long val) = 0;

		/// <summary>
		/// Associates the passed float value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutFloat(string key, std::shared_ptr<float> val) = 0;

		/// <summary>
		/// Associates the passed float value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutFloat(std::shared_ptr<string> key, std::shared_ptr<float> val) = 0;

		/// <summary>
		/// Associates the passed float value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutFloat(string key, float val) = 0;

		/// <summary>
		/// Associates the passed float value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutFloat(std::shared_ptr<string> key, float val) = 0;

		/// <summary>
		/// Associates the passed double value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutDouble(string key, std::shared_ptr<double> val) = 0;

		/// <summary>
		/// Associates the passed double value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutDouble(std::shared_ptr<string> key, std::shared_ptr<double> val) = 0;

		/// <summary>
		/// Associates the passed double value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutDouble(string key, double val) = 0;

		/// <summary>
		/// Associates the passed double value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutDouble(std::shared_ptr<string> key, double val) = 0;

		/// <summary>
		/// Associates the passed UTF-8 string value (max length: 32 KBytes) with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutUtfString(string key, std::shared_ptr<string> val) = 0;

		/// <summary>
		/// Associates the passed UTF-8 string value (max length: 32 KBytes) with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutUtfString(std::shared_ptr<string> key, std::shared_ptr<string> val) = 0;

		/// <summary>
		/// Associates the passed UTF-8 string value (max length: 32 KBytes) with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutUtfString(string key, string val) = 0;

		/// <summary>
		/// Associates the passed UTF-8 string value (max length: 32 KBytes) with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutUtfString(std::shared_ptr<string> key, string val) = 0;

		/// <summary>
		/// Associates the passed UTF-8 string value (max length: 2 GBytes) with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutText(string key, std::shared_ptr<string> val) = 0;

		/// <summary>
		/// Associates the passed UTF-8 string value (max length: 2 GBytes) with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutText(std::shared_ptr<string> key, std::shared_ptr<string> val) = 0;

		/// <summary>
		/// Associates the passed UTF-8 string value (max length: 2 GBytes) with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutText(string key, string val) = 0;

		/// <summary>
		/// Associates the passed UTF-8 string value (max length: 2 GBytes) with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutText(std::shared_ptr<string> key, string val) = 0;

		/// <summary>
		/// Associates the passed array of booleans with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified array is to be associated.</param>
		/// <param name="val">The array of booleans to be associated with the specified key.</param>
		virtual void PutBoolArray(string key, std::shared_ptr<vector<bool> > val) = 0;

		/// <summary>
		/// Associates the passed array of booleans with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified array is to be associated.</param>
		/// <param name="val">The array of booleans to be associated with the specified key.</param>
		virtual void PutBoolArray(std::shared_ptr<string> key, std::shared_ptr<vector<bool> > val) = 0;

		/// <summary>
		/// Associates the passed ByteArray object with the specified key in this object.
		/// </summary>
		/// 
		/// <remarks>
		/// <b>IMPORTANT</b>: ByteArrays transmission is not supported in Unity WebGL.
		/// </remarks>
		/// 
		/// <param name="key">The key with which the specified object is to be associated.</param>
		/// <param name="val">The object to be associated with the specified key.</param>
		virtual void PutByteArray(string key, std::shared_ptr<ByteArray> val) = 0;

		/// <summary>
		/// Associates the passed ByteArray object with the specified key in this object.
		/// </summary>
		/// 
		/// <remarks>
		/// <b>IMPORTANT</b>: ByteArrays transmission is not supported in Unity WebGL.
		/// </remarks>
		/// 
		/// <param name="key">The key with which the specified object is to be associated.</param>
		/// <param name="val">The object to be associated with the specified key.</param>
		virtual void PutByteArray(std::shared_ptr<string> key, std::shared_ptr<ByteArray> val) = 0;

		/// <summary>
		/// Associates the passed array of shorts with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified array is to be associated.</param>
		/// <param name="val">The array of shorts to be associated with the specified key.</param>
		virtual void PutShortArray(string key, std::shared_ptr<vector<short int> > val) = 0;

		/// <summary>
		/// Associates the passed array of shorts with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified array is to be associated.</param>
		/// <param name="val">The array of shorts to be associated with the specified key.</param>
		virtual void PutShortArray(std::shared_ptr<string> key, std::shared_ptr<vector<short int> > val) = 0;

		/// <summary>
		/// Associates the passed array of integers with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified array is to be associated.</param>
		/// <param name="val">The array of integers to be associated with the specified key.</param>
		virtual void PutIntArray(string key, std::shared_ptr<vector<long int> > val) = 0;

		/// <summary>
		/// Associates the passed array of integers with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified array is to be associated.</param>
		/// <param name="val">The array of integers to be associated with the specified key.</param>
		virtual void PutIntArray(std::shared_ptr<string> key, std::shared_ptr<vector<long int> > val) = 0;

		/// <summary>
		/// Associates the passed array of longs with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified array is to be associated.</param>
		/// <param name="val">The array of longs to be associated with the specified key.</param>
		virtual void PutLongArray(string key, std::shared_ptr<vector<long long> > val) = 0;

		/// <summary>
		/// Associates the passed array of longs with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified array is to be associated.</param>
		/// <param name="val">The array of longs to be associated with the specified key.</param>
		virtual void PutLongArray(std::shared_ptr<string> key, std::shared_ptr<vector<long long> > val) = 0;

		/// <summary>
		/// Associates the passed array of floats with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified array is to be associated.</param>
		/// <param name="val">The array of floats to be associated with the specified key.</param>
		virtual void PutFloatArray(string key, std::shared_ptr<vector<float> > val) = 0;

		/// <summary>
		/// Associates the passed array of floats with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified array is to be associated.</param>
		/// <param name="val">The array of floats to be associated with the specified key.</param>
		virtual void PutFloatArray(std::shared_ptr<string> key, std::shared_ptr<vector<float> > val) = 0;

		/// <summary>
		/// Associates the passed array of doubles with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified array is to be associated.</param>
		/// <param name="val">The array of doubles to be associated with the specified key.</param>
		virtual void PutDoubleArray(string key, std::shared_ptr<vector<double> > val) = 0;

		/// <summary>
		/// Associates the passed array of doubles with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified array is to be associated.</param>
		/// <param name="val">The array of doubles to be associated with the specified key.</param>
		virtual void PutDoubleArray(std::shared_ptr<string> key, std::shared_ptr<vector<double> > val) = 0;

		/// <summary>
		/// Associates the passed array of UTF-8 strings with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified array is to be associated.</param>
		/// <param name="val">The array of UTF-8 strings to be associated with the specified key.</param>
		virtual void PutUtfStringArray(string key, std::shared_ptr<vector<string> > val) = 0;

		/// <summary>
		/// Associates the passed array of UTF-8 strings with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified array is to be associated.</param>
		/// <param name="val">The array of UTF-8 strings to be associated with the specified key.</param>
		virtual void PutUtfStringArray(std::shared_ptr<string> key, std::shared_ptr<vector<string> > val) = 0;

		/// <summary>
		/// Associates the passed ISFSArray object with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified object is to be associated.</param>
		/// <param name="val">The object to be associated with the specified key.</param>
		virtual void PutSFSArray(string key, std::shared_ptr<ISFSArray> val) = 0;

		/// <summary>
		/// Associates the passed ISFSArray object with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified object is to be associated.</param>
		/// <param name="val">The object to be associated with the specified key.</param>
		virtual void PutSFSArray(std::shared_ptr<string> key, std::shared_ptr<ISFSArray> val) = 0;

		/// <summary>
		/// Associates the passed ISFSObject object with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified object is to be associated.</param>
		/// <param name="val">The object to be associated with the specified key.</param>
		virtual void PutSFSObject(string key, std::shared_ptr<ISFSObject> val) = 0;

		/// <summary>
		/// Associates the passed ISFSObject object with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified object is to be associated.</param>
		/// <param name="val">The object to be associated with the specified key.</param>
		virtual void PutSFSObject(std::shared_ptr<string> key, std::shared_ptr<ISFSObject> val) = 0;

		/// <summary>
		/// Associates the passed custom class instance with the specified key in this object.
		/// </summary>
		/// 
		/// <remarks>
		/// Read the <see cref="GetClass"/> method description for more informations.
		/// <para/>
		/// </remarks>
		/// 
		/// <param name="key">The key with which the specified custom class instance is to be associated.</param>
		/// <param name="val">The custom class instance to be associated with the specified key.</param>
		/// 
		/// <seealso cref="GetClass"/>
		virtual void PutClass(string key, std::shared_ptr<void> val) = 0;

		/// <summary>
		/// Associates the passed custom class instance with the specified key in this object.
		/// </summary>
		/// 
		/// <remarks>
		/// Read the <see cref="GetClass"/> method description for more informations.
		/// <para/>
		/// </remarks>
		/// 
		/// <param name="key">The key with which the specified custom class instance is to be associated.</param>
		/// <param name="val">The custom class instance to be associated with the specified key.</param>
		/// 
		/// <seealso cref="GetClass"/>
		virtual void PutClass(std::shared_ptr<string> key, std::shared_ptr<void> val) = 0;

		/// <exclude/>
		virtual void Put(string key, std::shared_ptr<SFSDataWrapper> val) = 0;

		/// <exclude/>
		virtual void Put(std::shared_ptr<string> key, std::shared_ptr<SFSDataWrapper> val) = 0;
	};

}	// namespace Data
}	// namespace Entities
}	// namespace Sfs2X


// --- Entities/Data/ISFSArray.h ---
// ===================================================================
//
// Description		
//		Contains the definition of ISFSArray interface
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================

// Forward class declaration
namespace Sfs2X {
namespace Entities {
namespace Data {
	class ISFSArray;
}	// namespace Data
}	// namespace Entities
}	// namespace Sfs2X


#if defined(_MSC_VER)
#endif
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X::Util;

namespace Sfs2X {
namespace Entities {
namespace Data {

	/// <summary>
	/// SFSArray interface
	/// </summary>
	class DLLImportExport ISFSArray
	{
	public:
		/// <summary>
		/// Returns true if the passed object is contained in the Array
		/// </summary>
		/// <param name="obj">
		/// A void pointer
		/// </param>
		/// <returns>
		/// A boolean
		/// </returns>
		virtual bool Contains(std::shared_ptr<void> obj) = 0;
		
		/// <summary>
		/// Returns the element at the specified index
		/// </summary>
		/// <param name="index">
		/// A long integer
		/// </param>
		/// <returns>
		/// A void pointer
		/// </returns>
		virtual std::shared_ptr<void> GetElementAt(long int index) = 0;
		
		virtual std::shared_ptr<SFSDataWrapper> GetWrappedElementAt(long int index) = 0;
		
		/// <summary>
		/// Remove the element at the specified index
		/// </summary>
		/// <param name="index">
		/// An unsigned long integer
		/// </param>
		/// <returns>
		/// A void pointer
		/// </returns>
		virtual std::shared_ptr<void> RemoveElementAt(unsigned long int index) = 0;
		
		/// <summary>
		/// Return the number of elements in the Array
		/// </summary>
		/// <returns>
		/// A long integer
		/// </returns>
		virtual long int Size() = 0;
		
		/// <summary>
		/// Return the binary form of the object
		/// </summary>
		/// <returns>
		/// Pointer to a <see cref="ByteArray"/> instance
		/// </returns>
		virtual std::shared_ptr<ByteArray> ToBinary() = 0;
		
		/// <summary>
		/// Return a formatted dump of the object that can logged or traced in the console for debugging purposes.
		/// </summary>
		/// <param name="format">
		/// turns the "pretty print" on/off
		/// </param>
		/// <returns>
		/// A string pointer
		/// </returns>
		virtual std::shared_ptr<string> GetDump(bool format) = 0;

		/// <summary>
		/// Return a formatted dump of the object that can logged or traced in the console for debugging purposes.
		/// </summary>
		/// <returns>
		/// A string pointer
		/// </returns>
		virtual std::shared_ptr<string> GetDump() = 0; // Default to true
		
		/// <summary>
		/// Returns a detailed hex-dump of the object that can logged or traced in the console for debugging purposes.
		/// </summary>
		/// <returns>
		/// A string pointer
		/// </returns>
		virtual std::shared_ptr<string> GetHexDump() = 0;

		/*
		* :::::::::::::::::::::::::::::::::::::::::
		* Type setters
		* :::::::::::::::::::::::::::::::::::::::::	
		*/
		
		// Primitives
		/// <summary>
		/// Add a null element
		/// </summary>
		virtual void AddNull() = 0;
		
		/// <summary>
		/// Add a Boolean value
		/// </summary>
		/// <param name="val">
		/// A boolean
		/// </param>
		virtual void AddBool(std::shared_ptr<bool> val) = 0;

		/// <summary>
		/// Add a Boolean value
		/// </summary>
		/// <param name="val">
		/// A boolean
		/// </param>
		virtual void AddBool(bool val) = 0;

		/// <summary>
		/// Add a byte value (8 bit)
		/// </summary>
		/// <param name="val">
		/// An unsigned char
		/// </param>
		virtual void AddByte(std::shared_ptr<unsigned char> val) = 0;

		/// <summary>
		/// Add a byte value (8 bit)
		/// </summary>
		/// <param name="val">
		/// An unsigned char
		/// </param>
		virtual void AddByte(unsigned char val) = 0;

		/// <summary>
		/// Add a short int value (16 bit)
		/// </summary>
		/// <param name="val">
		/// A short integer
		/// </param>
		virtual void AddShort(std::shared_ptr<short int> val) = 0;

		/// <summary>
		/// Add a short int value (16 bit)
		/// </summary>
		/// <param name="val">
		/// A short integer
		/// </param>
		virtual void AddShort(short int val) = 0;

		/// <summary>
		/// Add an int value (32 bit)
		/// </summary>
		/// <param name="val">
		/// A long integer
		/// </param>
		virtual void AddInt(std::shared_ptr<long int> val) = 0;

		/// <summary>
		/// Add an int value (32 bit)
		/// </summary>
		/// <param name="val">
		/// A long integer
		/// </param>
		virtual void AddInt(long int val) = 0;

		/// <summary>
		/// Add a long int value (64 bit)
		/// </summary>
		/// <param name="val">
		/// A long
		/// </param>
		virtual void AddLong(std::shared_ptr<long long> val) = 0;

		/// <summary>
		/// Add a long int value (64 bit)
		/// </summary>
		/// <param name="val">
		/// A long
		/// </param>
		virtual void AddLong(long long val) = 0;

		/// <summary>
		/// Add a float value (32 bit)
		/// </summary>
		/// <param name="val">
		/// A float
		/// </param>
		virtual void AddFloat(std::shared_ptr<float> val) = 0;

		/// <summary>
		/// Add a float value (32 bit)
		/// </summary>
		/// <param name="val">
		/// A float
		/// </param>
		virtual void AddFloat(float val) = 0;

		/// <summary>
		/// Add a dobule value (64 bit)
		/// </summary>
		/// <param name="val">
		/// A double
		/// </param>
		virtual void AddDouble(std::shared_ptr<double> val) = 0;

		/// <summary>
		/// Add a dobule value (64 bit)
		/// </summary>
		/// <param name="val">
		/// A double
		/// </param>
		virtual void AddDouble(double val) = 0;

		/// <summary>
		/// Appends a UTF-8 string (with max length of 32 KBytes) value to the end of this array.
		/// </summary>
		/// <param name="val">
		/// A string pointer
		/// </param>
		virtual void AddUtfString(std::shared_ptr<string> val) = 0;

		/// <summary>
		/// Appends a UTF-8 string (with max length of 32 KBytes) value to the end of this array.
		/// </summary>
		/// <param name="val">
		/// A string pointer
		/// </param>
		virtual void AddUtfString(string val) = 0;

		/// <summary>
		/// Appends a UTF-8 string (with max length of 2 GBytes) value to the end of this array.
		/// </summary>
		/// <param name="val">
		/// The value to be appended to this array.
		/// </param>
		virtual void AddText(std::shared_ptr<string> val) = 0;

		/// <summary>
		/// Appends a UTF-8 string (with max length of 2 GBytes) value to the end of this array.
		/// </summary>
		/// <param name="val">
		/// The value to be appended to this array.
		/// </param>
		virtual void AddText(string val) = 0;

		/// <summary>
		/// Add an array of Booleans
		/// </summary>
		/// <param name="val">
		/// A bool[]
		/// </param>
		virtual void AddBoolArray(std::shared_ptr<vector<std::shared_ptr<bool> > > val) = 0;
		
		/// <summary>
		/// Add an array of bytes
		/// </summary>
		/// <param name="val">
		/// Pointer to a <see cref="ByteArray"/> instance
		/// </param>
		virtual void AddByteArray(std::shared_ptr<ByteArray> val) = 0;
		
		/// <summary>
		/// Add an array of short ints 
		/// </summary>
		/// <param name="val">
		/// A short[]
		/// </param>
		virtual void AddShortArray(std::shared_ptr<vector<std::shared_ptr<short int> > > val) = 0;
		
		/// <summary>
		/// Add an array of ints
		/// </summary>
		/// <param name="val">
		/// A int[]
		/// </param>
		virtual void AddIntArray(std::shared_ptr<vector<std::shared_ptr<long int> > > val) = 0;
		
		/// <summary>
		/// Add an array of long ints
		/// </summary>
		/// <param name="val">
		/// A long[]
		/// </param>
		virtual void AddLongArray(std::shared_ptr<vector<std::shared_ptr<long long> > > val) = 0;
		
		/// <summary>
		/// Add an array of floats
		/// </summary>
		/// <param name="val">
		/// A float[]
		/// </param>
		virtual void AddFloatArray(std::shared_ptr<vector<std::shared_ptr<float> > > val) = 0;
		
		/// <summary>
		/// Add an array of doubles
		/// </summary>
		/// <param name="val">
		/// A double[]
		/// </param>
		virtual void AddDoubleArray(std::shared_ptr<vector<std::shared_ptr<double> > > val) = 0;
		
		/// <summary>
		/// Add an array of UTF-8 String
		/// </summary>
		/// <param name="val">
		/// A string[]
		/// </param>
		virtual void AddUtfStringArray(std::shared_ptr<vector<std::shared_ptr<string> > > val) = 0;

		/// <summary>
		/// Add an SFSArray
		/// </summary>
		/// <param name="val">
		/// Pointer to a <see cref="ISFSArray"/> instance
		/// </param>
		virtual void AddSFSArray(std::shared_ptr<ISFSArray> val) = 0;

		/// <summary>
		/// Add an SFSObject
		/// </summary>
		/// <param name="val">
		/// Pointer to a <see cref="ISFSObject"/> instance
		/// </param>
		/// <seealso cref="SFSObject"/>
		virtual void AddSFSObject(std::shared_ptr<ISFSObject> val) = 0;

		/// <summary>
		/// Add an instance of a custom Class.
		/// </summary>
		/// <remarks>
		/// This is an advanced feature that allows to transmit object instances between Actionscript and Java provided that both classes are definined under the same package name.
		/// </remarks>
		/// <example>
		/// This is an example of the same class on the server and client side:
		/// 
		/// <b>Server Java code:</b>
		///			\code{.cpp}
		/// 			package my.game.spacecombat
		/// 
		/// 			public class SpaceShip
		/// 			{
		/// 				private String type;
		/// 				private String name;
		/// 				private int firePower;
		/// 				private int maxSpeed;
        /// 				private List<String> weapons;
		/// 
		/// 				public SpaceShip(String name, String type)
		/// 				{
		/// 					this.name = name;
		/// 					this.type = type;
		/// 				}
		/// 
		/// 				// ... Getters / Setters ...
		/// 			}
		/// 		\endcode
		/// 
		/// <b>Client AS3 code:</b>
		///			\code{.cpp}
		/// 		package my.game.spacecombat
		/// 		{
		/// 			public class SpaceShip
		/// 			{
		/// 				private var _type:String
		/// 				private var _name:String
		/// 				private var _firePower:int;
		/// 				private var _maxSpeed:int;
		/// 				private var _weapons:Array;
		/// 
		/// 				public SpaceShip(name:String, type:Strig)
		/// 				{
		/// 					_name = name
		/// 					_type = type
		/// 				}
		/// 
		/// 				// ... Getters / Setters ...
		/// 			}
		/// 		}	
		/// 			
		/// 		\endcode
		/// 
		/// 	A SpaceShip instance from server side is sent to the client. This is how you get it: 
		///		\code{.cpp}
		/// 		std::shared_ptr<SpaceShip> mySpaceShip = (std::shared_ptr<SpaceShip>)sfsArray->getClass(0) 
		/// 	\endcode
		/// 
		/// </example>
		/// <param name="val">
		/// A void pointer
		/// </param>
		virtual void AddClass(std::shared_ptr<void> val) = 0;

		virtual void Add(std::shared_ptr<SFSDataWrapper> val) = 0;
	
		/*
		* :::::::::::::::::::::::::::::::::::::::::
		* Type getters
		* :::::::::::::::::::::::::::::::::::::::::	
		*/

		/// <summary>
		/// Checks if a certain element in the Array is null
		/// </summary>
		/// <param name="index">
		/// An unsigned long integer
		/// </param>
		/// <returns>
		/// A boolean
		/// </returns>
		virtual bool IsNull(unsigned long int index) = 0;

		/// <summary>
		/// Get a Boolean element at the provided index
		/// </summary>
		/// <param name="index">
		/// An unsigned long integer
		/// </param>
		/// <returns>
		/// A boolean
		/// </returns>
		virtual bool GetBool(unsigned long int index) = 0;
		
		/// <summary>
		/// Get a byte element at the provided index
		/// </summary>
		/// <param name="index">
		/// An unsigned long integer
		/// </param>
		/// <returns>
		/// An unsigned char
		/// </returns>
		virtual unsigned char GetByte(unsigned long int index) = 0;
		
		/// <summary>
		/// Get a short int element at the provided index
		/// </summary>
		/// <param name="index">
		/// An unsigned long integer
		/// </param>
		/// <returns>
		/// A short integer
		/// </returns>
		virtual short int GetShort(unsigned long int index) = 0;
		
		/// <summary>
		/// Get an int element at the provided index 
		/// </summary>
		/// <param name="index">
		/// An unsigned long integer
		/// </param>
		/// <returns>
		/// A long integer
		/// </returns>
		virtual long int GetInt(unsigned long int index) = 0;
		
		/// <summary>
		/// Get a long int element at the provided index
		/// </summary>
		/// <param name="index">
		/// An unsigned long integer
		/// </param>
		/// <returns>
		/// A long
		/// </returns>
		virtual long long GetLong(unsigned long int index) = 0;
		
		/// <summary>
		/// Get a float element at the provided index
		/// </summary>
		/// <param name="index">
		/// An unsigned long integer
		/// </param>
		/// <returns>
		/// A float
		/// </returns>
		virtual float GetFloat(unsigned long int index) = 0;
		
		/// <summary>
		/// Get a double element at the provided index
		/// </summary>
		/// <param name="index">
		/// An unsigned long integer
		/// </param>
		/// <returns>
		/// A double
		/// </returns>
		virtual double GetDouble(unsigned long int index) = 0;
		
		/// <summary>
		/// Returns the element at the specified position as an UTF-8 string, with max length of 32 KBytes.
		/// </summary>
		/// <param name="index">
		/// An unsigned long integer
		/// </param>
		/// <returns>
		/// A string pointer
		/// </returns>
		virtual std::shared_ptr<string> GetUtfString(unsigned long int index) = 0;
		
		/// <summary>
		/// Returns the element at the specified position as an UTF-8 string, with max length of 2 GBytes.
		/// </summary>
		/// <param name="index">
		///	The position of the element to return.
		///	</param>
		/// <returns>
		///	The element of this array at the specified index.
		///	</returns>
		virtual std::shared_ptr<string> GetText(unsigned long int index) = 0;

		/// <summary>
		/// Get a Boolean Array element at the provided index
		/// </summary>
		/// <param name="index">
		/// An unsigned long integer
		/// </param>
		/// <returns>
		/// A bool[]
		/// </returns>
		virtual std::shared_ptr<vector<bool> > GetBoolArray(unsigned long int index) = 0;
		
		/// <summary>
		/// Get a byte Array element at the provided index
		/// </summary>
		/// <param name="index">
		/// An unsigned long integer
		/// </param>
		/// <returns>
		/// Pointer to a <see cref="ByteArray"/> instance
		/// </returns>
		virtual std::shared_ptr<ByteArray> GetByteArray(unsigned long int index) = 0;
		
		/// <summary>
		/// Get a short Array element at the provided index
		/// </summary>
		/// <param name="index">
		/// An unsigned long integer
		/// </param>
		/// <returns>
		/// A short[]
		/// </returns>
		virtual std::shared_ptr<vector<short int> > GetShortArray(unsigned long int index) = 0;
		
		/// <summary>
		/// Get a int Array element at the provided index
		/// </summary>
		/// <param name="index">
		/// An unsigned long integer
		/// </param>
		/// <returns>
		/// A int[]
		/// </returns>
		virtual std::shared_ptr<vector<long int> > GetIntArray(unsigned long int index) = 0;
		
		/// <summary>
		/// Get a lomg Array element at the provided index
		/// </summary>
		/// <param name="index">
		/// An unsigned long integer
		/// </param>
		/// <returns>
		/// A long[]
		/// </returns>
		virtual std::shared_ptr<vector<long long> > GetLongArray(unsigned long int index) = 0;
		
		/// <summary>
		/// Get a float Array element at the provided index
		/// </summary>
		/// <param name="index">
		/// An unsigned long integer
		/// </param>
		/// <returns>
		/// A float[]
		/// </returns>
		virtual std::shared_ptr<vector<float> > GetFloatArray(unsigned long int index) = 0;
		
		/// <summary>
		/// Get a double Array element at the provided index
		/// </summary>
		/// <param name="index">
		/// An unsigned long integer
		/// </param>
		/// <returns>
		/// A double[]
		/// </returns>
		virtual std::shared_ptr<vector<double> > GetDoubleArray(unsigned long int index) = 0;
		
		/// <summary>
		/// Get a String Array element at the provided index
		/// </summary>
		/// <param name="index">
		/// An unsigned long integer
		/// </param>
		/// <returns>
		/// A string[]
		/// </returns>
		virtual std::shared_ptr<vector<string> > GetUtfStringArray(unsigned long int index) = 0;
		
		/// <summary>
		/// Get an SFSArray element at the provided index
		/// </summary>
		/// <param name="index">
		/// An unsigned long integer
		/// </param>
		/// <returns>
		/// Pointer to a <see cref="ISFSArray"/> instance
		/// </returns>
		virtual std::shared_ptr<ISFSArray> GetSFSArray(unsigned long int index) = 0;
		
		/// <summary>
		/// Get an SFSObject element at the provided index
		/// </summary>
		/// <param name="index">
		/// An unsigned long integer
		/// </param>
		/// <returns>
		/// Pointer to a <see cref="ISFSObject"/> instance
		/// </returns>
		virtual std::shared_ptr<ISFSObject> GetSFSObject(unsigned long int index) = 0;
		
		/// <summary>
		/// Get a class instance at the provided index.
		/// </summary>
		/// <param name="index">
		/// An unsigned long integer
		/// </param>
		/// <returns>
		/// A void pointer
		/// </returns>
		/// <seealso cref="AddClass"/>
		virtual std::shared_ptr<void> GetClass(unsigned long int index) = 0;
	};

}	// namespace Data
}	// namespace Entities
}	// namespace Sfs2X


// --- Exceptions/SFSError.h ---
// ===================================================================
//
// Description		
//		Contains the definition of SFSError
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================


#if defined(_MSC_VER)
#endif
using namespace std;					// STL library: declare the STL namespace

namespace Sfs2X {
namespace Exceptions {

	// ------------------------------------------------------------------- 
	// Class SFSError
	// -------------------------------------------------------------------
	class SFSError : public std::runtime_error
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		SFSError(std::shared_ptr<string> message);
		const char* what() const noexcept override { return message ? message->c_str() : ""; }
		std::shared_ptr<string> Message() {return message;};
		~SFSError() throw () {};

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------

	protected:

		// -------------------------------------------------------------------
		// Protected methods
		// -------------------------------------------------------------------

		// -------------------------------------------------------------------
		// Protected members
		// -------------------------------------------------------------------

	private:

		// -------------------------------------------------------------------
		// Private methods
		// -------------------------------------------------------------------

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------

		std::shared_ptr<string> message;
	};

}	// namespace Exceptions
}	// namespace Sfs2X


// --- Exceptions/SFSCodecError.h ---
// ===================================================================
//
// Description		
//		Contains the definition of SFSCodecError
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================


#if defined(_MSC_VER)
#endif
using namespace std;					// STL library: declare the STL namespace

namespace Sfs2X {
namespace Exceptions {

	// ------------------------------------------------------------------- 
	// Class SFSCodecError
	// -------------------------------------------------------------------
	class SFSCodecError : public std::runtime_error
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------
		
		SFSCodecError(std::shared_ptr<string> message);
		const char* what() const noexcept override { return message ? message->c_str() : ""; }
		std::shared_ptr<string> Message() {return message;};
		~SFSCodecError () throw () {};
		
		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------

	protected:

		// -------------------------------------------------------------------
		// Protected methods
		// -------------------------------------------------------------------

		// -------------------------------------------------------------------
		// Protected members
		// -------------------------------------------------------------------

	private:

		// -------------------------------------------------------------------
		// Private methods
		// -------------------------------------------------------------------

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------

		std::shared_ptr<string> message;
	};

}	// namespace Exceptions
}	// namespace Sfs2X


// --- Protocol/Serialization/ISFSDataSerializer.h ---
// ===================================================================
//
// Description		
//		Contains the definition of ISFSDataSerializer interface
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================


using namespace Sfs2X::Entities::Data;
using namespace Sfs2X::Util;

namespace Sfs2X {
namespace Protocol {
namespace Serialization {

	class ISFSDataSerializer
	{
	public:
		virtual std::shared_ptr<ByteArray> Object2Binary(std::shared_ptr<ISFSObject> obj) = 0;
		virtual std::shared_ptr<ByteArray> Array2Binary(std::shared_ptr<ISFSArray> array) = 0;
		virtual std::shared_ptr<ISFSObject> Binary2Object(std::shared_ptr<ByteArray> data) = 0;
		virtual std::shared_ptr<ISFSArray> Binary2Array(std::shared_ptr<ByteArray> data) = 0;
	};

}	// namespace Serialization
}	// namespace Protocol
}	// namespace Sfs2X


// --- Protocol/Serialization/DefaultObjectDumpFormatter.h ---
// ===================================================================
//
// Description		
//		Contains the definition of DefaultObjectDumpFormatter
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================


#if defined(_MSC_VER)
#endif
using namespace std;			// Declare the STL namespace

using namespace Sfs2X::Util;
using namespace Sfs2X::Exceptions;

namespace Sfs2X {
namespace Protocol {
namespace Serialization {

	// -------------------------------------------------------------------
	// Class DefaultObjectDumpFormatter
	// -------------------------------------------------------------------
	class DefaultObjectDumpFormatter
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------
		virtual ~DefaultObjectDumpFormatter();

		static std::shared_ptr<string> PrettyPrintDump(std::shared_ptr<string> rawDump);
		static std::shared_ptr<string> HexDump(std::shared_ptr<ByteArray> ba);
		static std::shared_ptr<string> HexDump(std::shared_ptr<ByteArray> ba, long int bytesPerLine);

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------

		static const char TOKEN_INDENT_OPEN = '{'; //(char) 0x01;
		static const char TOKEN_INDENT_CLOSE = '}'; //(char) 0x02;
		static const char TOKEN_DIVIDER = ';'; //(char) 0x03;
		static const char NEW_LINE = '\n';
		static const char TAB = '\t';
		static const char DOT = '.';
		
		static const int HEX_BYTES_PER_LINE = 16;

		static const int MAX_DUMP_LENGTH = 1024;

	protected:

		// -------------------------------------------------------------------
		// Protected methods
		// -------------------------------------------------------------------

		// -------------------------------------------------------------------
		// Protected members
		// -------------------------------------------------------------------

	private:

		// -------------------------------------------------------------------
		// Private methods
		// -------------------------------------------------------------------

		static std::shared_ptr<string> GetFormatTabs(long int howMany);
		static std::shared_ptr<string> StrFill(char ch, long int howMany);

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------
	};

}	// namespace Serialization
}	// namespace Protocol
}	// namespace Sfs2X


// --- Protocol/Serialization/DefaultSFSDataSerializer.h ---
// ===================================================================
//
// Description		
//		Contains the definition of DefaultSFSDataSerializer
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================


#if defined(_MSC_VER)
#endif
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X::Entities::Data;
using namespace Sfs2X::Util;
using namespace Sfs2X::Exceptions;

namespace Sfs2X {
namespace Protocol {
namespace Serialization {

	// -------------------------------------------------------------------
	// Class DefaultSFSDataSerializer
	// -------------------------------------------------------------------
	class DefaultSFSDataSerializer : public ISFSDataSerializer
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		static std::shared_ptr<DefaultSFSDataSerializer> Instance();

		DefaultSFSDataSerializer();
		virtual ~DefaultSFSDataSerializer();

		// SFSObject ==> Binary

		std::shared_ptr<ByteArray> Object2Binary(std::shared_ptr<ISFSObject> obj);

		// SFSArray ==> Binary

		std::shared_ptr<ByteArray> Array2Binary(std::shared_ptr<ISFSArray> arrayobj);

		// Binary ==> SFSObject

		std::shared_ptr<ISFSObject> Binary2Object(std::shared_ptr<ByteArray> data);

		// Binary ==> SFSArray

		std::shared_ptr<ISFSArray> Binary2Array(std::shared_ptr<ByteArray> data);


		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------

		static std::shared_ptr<string> CLASS_MARKER_KEY;
		static std::shared_ptr<string> CLASS_FIELDS_KEY;
		static std::shared_ptr<string> FIELD_NAME_KEY;
		static std::shared_ptr<string> FIELD_VALUE_KEY;

	protected:

		// -------------------------------------------------------------------
		// Protected methods
		// -------------------------------------------------------------------

		// -------------------------------------------------------------------
		// Protected members
		// -------------------------------------------------------------------
	
	private:

		// -------------------------------------------------------------------
		// Private methods
		// -------------------------------------------------------------------

		std::shared_ptr<ByteArray> Obj2bin(std::shared_ptr<ISFSObject> obj, std::shared_ptr<ByteArray> buffer);
		std::shared_ptr<ByteArray> Arr2bin(std::shared_ptr<ISFSArray> arrayobj, std::shared_ptr<ByteArray> buffer);
		std::shared_ptr<ISFSObject> DecodeSFSObject(std::shared_ptr<ByteArray> buffer);
		std::shared_ptr<ISFSArray> DecodeSFSArray(std::shared_ptr<ByteArray> buffer);
		std::shared_ptr<ByteArray> EncodeObject(std::shared_ptr<ByteArray> buffer, int typeId, std::shared_ptr<void> data);

		/*
	 	* The buffer pointer (position) must located on the 1st byte of the object to decode
	 	* Throws SFSCodecException
	 	*/
		std::shared_ptr<SFSDataWrapper> DecodeObject(std::shared_ptr<ByteArray> buffer);

		// Binary Entities Decoding Methods

		std::shared_ptr<SFSDataWrapper> BinDecode_NULL(std::shared_ptr<ByteArray> buffer);
		std::shared_ptr<SFSDataWrapper> BinDecode_BOOL(std::shared_ptr<ByteArray> buffer);
		std::shared_ptr<SFSDataWrapper> BinDecode_BYTE(std::shared_ptr<ByteArray> buffer);
		std::shared_ptr<SFSDataWrapper> BinDecode_SHORT(std::shared_ptr<ByteArray> buffer);
		std::shared_ptr<SFSDataWrapper> BinDecode_INT(std::shared_ptr<ByteArray> buffer);
		std::shared_ptr<SFSDataWrapper> BinDecode_LONG(std::shared_ptr<ByteArray> buffer);
		std::shared_ptr<SFSDataWrapper> BinDecode_FLOAT(std::shared_ptr<ByteArray> buffer);
		std::shared_ptr<SFSDataWrapper> BinDecode_DOUBLE(std::shared_ptr<ByteArray> buffer);
		std::shared_ptr<SFSDataWrapper> BinDecode_UTF_STRING(std::shared_ptr<ByteArray> buffer);
		std::shared_ptr<SFSDataWrapper> BinDecode_TEXT(std::shared_ptr<ByteArray> buffer);
		std::shared_ptr<SFSDataWrapper> BinDecode_BOOL_ARRAY(std::shared_ptr<ByteArray> buffer);
		std::shared_ptr<SFSDataWrapper> BinDecode_BYTE_ARRAY(std::shared_ptr<ByteArray> buffer);
		std::shared_ptr<SFSDataWrapper> BinDecode_SHORT_ARRAY(std::shared_ptr<ByteArray> buffer);
		std::shared_ptr<SFSDataWrapper> BinDecode_INT_ARRAY(std::shared_ptr<ByteArray> buffer);
		std::shared_ptr<SFSDataWrapper> BinDecode_LONG_ARRAY(std::shared_ptr<ByteArray> buffer);
		std::shared_ptr<SFSDataWrapper> BinDecode_FLOAT_ARRAY(std::shared_ptr<ByteArray> buffer);
		std::shared_ptr<SFSDataWrapper> BinDecode_DOUBLE_ARRAY(std::shared_ptr<ByteArray> buffer);
		std::shared_ptr<SFSDataWrapper> BinDecode_UTF_STRING_ARRAY(std::shared_ptr<ByteArray> buffer);
		int32_t GetTypedArraySize(std::shared_ptr<ByteArray> buffer);

		// Binary Entities Encoding Methods

		std::shared_ptr<ByteArray> BinEncode_NULL(std::shared_ptr<ByteArray> buffer);
		std::shared_ptr<ByteArray> BinEncode_BOOL(std::shared_ptr<ByteArray> buffer, std::shared_ptr<bool> val);
		std::shared_ptr<ByteArray> BinEncode_BYTE(std::shared_ptr<ByteArray> buffer, std::shared_ptr<unsigned char> val);
		std::shared_ptr<ByteArray> BinEncode_SHORT(std::shared_ptr<ByteArray> buffer, std::shared_ptr<short int> val);
		std::shared_ptr<ByteArray> BinEncode_INT(std::shared_ptr<ByteArray> buffer, std::shared_ptr<long int> val);
		std::shared_ptr<ByteArray> BinEncode_LONG(std::shared_ptr<ByteArray> buffer, std::shared_ptr<long long> val);
		std::shared_ptr<ByteArray> BinEncode_FLOAT(std::shared_ptr<ByteArray> buffer, std::shared_ptr<float> val);
		std::shared_ptr<ByteArray> BinEncode_DOUBLE(std::shared_ptr<ByteArray> buffer, std::shared_ptr<double> val);
		std::shared_ptr<ByteArray> BinEncode_INT(std::shared_ptr<ByteArray> buffer, std::shared_ptr<double> val);
		std::shared_ptr<ByteArray> BinEncode_UTF_STRING(std::shared_ptr<ByteArray> buffer, std::shared_ptr<string> val);
		std::shared_ptr<ByteArray> BinEncode_TEXT(std::shared_ptr<ByteArray> buffer, std::shared_ptr<string> val);
		std::shared_ptr<ByteArray> BinEncode_BOOL_ARRAY(std::shared_ptr<ByteArray> buffer, std::shared_ptr<vector<bool> > val);
		std::shared_ptr<ByteArray> BinEncode_BYTE_ARRAY(std::shared_ptr<ByteArray> buffer, std::shared_ptr<ByteArray> val);
		std::shared_ptr<ByteArray> BinEncode_SHORT_ARRAY(std::shared_ptr<ByteArray> buffer, std::shared_ptr<vector<short int> > val);
		std::shared_ptr<ByteArray> BinEncode_INT_ARRAY(std::shared_ptr<ByteArray> buffer, std::shared_ptr<vector<long int> > val);
		std::shared_ptr<ByteArray> BinEncode_LONG_ARRAY(std::shared_ptr<ByteArray> buffer, std::shared_ptr<vector<long long> > val);
		std::shared_ptr<ByteArray> BinEncode_FLOAT_ARRAY(std::shared_ptr<ByteArray> buffer, std::shared_ptr<vector<float> > val);
		std::shared_ptr<ByteArray> BinEncode_DOUBLE_ARRAY(std::shared_ptr<ByteArray> buffer, std::shared_ptr<vector<double> > val);
		std::shared_ptr<ByteArray> BinEncode_UTF_STRING_ARRAY(std::shared_ptr<ByteArray> buffer, std::shared_ptr<vector<string> > val);
		std::shared_ptr<ByteArray> EncodeSFSObjectKey(std::shared_ptr<ByteArray> buffer, std::shared_ptr<string> val);

		/*
		* Returns the same buffer
		* (could be used also to create copies)
		*/
		std::shared_ptr<ByteArray> AddData(std::shared_ptr<ByteArray> buffer, std::shared_ptr<ByteArray> newData);

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------

		static std::shared_ptr<DefaultSFSDataSerializer> instance;
	};

}	// namespace Serialization
}	// namespace Protocol
}	// namespace Sfs2X


// --- Entities/Data/SFSObject.h ---
// ===================================================================
//
// Description		
//		Contains the definition of SFSObject
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================


#if defined(_MSC_VER)
#endif
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X::Exceptions;
using namespace Sfs2X::Protocol::Serialization;
using namespace Sfs2X::Util;

namespace Sfs2X {
namespace Entities {
namespace Data {

	/// <summary>
	/// SFSObject
	/// </summary>
	/// <remarks>
	/// <b>SFSObject</b> is used from server and client side to exchange data. It can be thought of a specialized Dictionary/Map object that can contain any type of data. <br/>
	/// The advantage of using SFSObject is that you can fine tune the way your data will be transmitted over the network.<br/>
	/// For instance, a number like 100 can be transmitted as a normal <b>integer</b> (which takes 32 bits) but also a <b>short</b> (16 bit) or even a <b>byte</b> (8 bit)
	/// <para/>
	/// <b>SFSObject</b> supports many primitive data types and related arrays of primitives. It also allows to serialize class instances and rebuild them on the Java side. <br/>
	/// This is explained in greater detail in a separate document.
	/// </remarks>
	/// <seealso cref="SFSArray"/>
	class DLLImportExport SFSObject : public ISFSObject, public std::enable_shared_from_this<SFSObject>
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------
		
		/// <summary>
		/// Alternative static constructor that builds an SFSObject populated with the data found in the passed Object
		/// </summary>
		/// <param name="o">
		/// A void pointer
		/// </param>
		/// <returns>
		/// Pointer to a <see cref="SFSObject"/> instance
		/// </returns>
		static std::shared_ptr<SFSObject> NewFromObject(std::shared_ptr<void> o);

		/// <summary>
		/// Alternative static constructor that builds an SFSObject from a valid SFSObject binary representation
		/// </summary>
		/// <param name="ba">
		/// Pointer to a <see cref="ByteArray"/> instance
		/// </param>
		/// <returns>
		/// Pointer to a <see cref="SFSObject"/> instance
		/// </returns>
		static std::shared_ptr<SFSObject> NewFromBinaryData(std::shared_ptr<ByteArray> ba);

		/// <summary>
		/// Alternative static constructor
		/// </summary>
		/// <returns>
		/// Pointer to a <see cref="SFSObject"/> instance
		/// </returns>
		static std::shared_ptr<SFSObject> NewInstance();

		/// <summary>
        /// 
        /// </summary>
        /// <summary>
        /// 
        /// </summary>
		SFSObject();
		virtual ~SFSObject();

		std::shared_ptr<SFSDataWrapper> GetData(string key);
		std::shared_ptr<SFSDataWrapper> GetData(std::shared_ptr<string> key);
		//T GetValue<T>(string key);
		std::shared_ptr<bool> GetBool(string key);
		std::shared_ptr<bool> GetBool(std::shared_ptr<string> key);
		std::shared_ptr<unsigned char> GetByte(string key);
		std::shared_ptr<unsigned char> GetByte(std::shared_ptr<string> key);
		std::shared_ptr<short int> GetShort(string key);
		std::shared_ptr<short int> GetShort(std::shared_ptr<string> key);
		std::shared_ptr<long int> GetInt(string key);
		std::shared_ptr<long int> GetInt(std::shared_ptr<string> key);
		std::shared_ptr<long long> GetLong(string key);
		std::shared_ptr<long long> GetLong(std::shared_ptr<string> key);
		std::shared_ptr<float> GetFloat(string key);
		std::shared_ptr<float> GetFloat(std::shared_ptr<string> key);
		std::shared_ptr<double> GetDouble(string key);
		std::shared_ptr<double> GetDouble(std::shared_ptr<string> key);
		std::shared_ptr<string> GetUtfString(string key);
		std::shared_ptr<string> GetUtfString(std::shared_ptr<string> key);
		std::shared_ptr<string> GetText(string key);
		std::shared_ptr<string> GetText(std::shared_ptr<string> key);
		std::shared_ptr<vector<unsigned char> > GetArray(string key);
		std::shared_ptr<vector<unsigned char> > GetArray(std::shared_ptr<string> key);
		std::shared_ptr<vector<bool> > GetBoolArray(string key);
		std::shared_ptr<vector<bool> > GetBoolArray(std::shared_ptr<string> key);
		std::shared_ptr<ByteArray> GetByteArray(string key);
		std::shared_ptr<ByteArray> GetByteArray(std::shared_ptr<string> key);
		std::shared_ptr<vector<short int> > GetShortArray(string key);
		std::shared_ptr<vector<short int> > GetShortArray(std::shared_ptr<string> key);
		std::shared_ptr<vector<long int> > GetIntArray(string key);
		std::shared_ptr<vector<long int> > GetIntArray(std::shared_ptr<string> key);
		std::shared_ptr<vector<long long> > GetLongArray(string key);
		std::shared_ptr<vector<long long> > GetLongArray(std::shared_ptr<string> key);
		std::shared_ptr<vector<float> > GetFloatArray(string key);
		std::shared_ptr<vector<float> > GetFloatArray(std::shared_ptr<string> key);
		std::shared_ptr<vector<double> > GetDoubleArray(string key);
		std::shared_ptr<vector<double> > GetDoubleArray(std::shared_ptr<string> key);
		std::shared_ptr<vector<string> > GetUtfStringArray(string key);
		std::shared_ptr<vector<string> > GetUtfStringArray(std::shared_ptr<string> key);
		std::shared_ptr<ISFSArray> GetSFSArray(string key);
		std::shared_ptr<ISFSArray> GetSFSArray(std::shared_ptr<string> key);
		std::shared_ptr<ISFSObject> GetSFSObject(string key);
		std::shared_ptr<ISFSObject> GetSFSObject(std::shared_ptr<string> key);

		void PutNull(string key);
		void PutNull(std::shared_ptr<string> key);
		void PutBool(string key, std::shared_ptr<bool> val);
		void PutBool(std::shared_ptr<string> key, std::shared_ptr<bool> val);
		void PutBool(string key, bool val);
		void PutBool(std::shared_ptr<string> key, bool val);
		void PutByte(string key, std::shared_ptr<unsigned char> val);
		void PutByte(std::shared_ptr<string> key, std::shared_ptr<unsigned char> val);
		void PutByte(string key, unsigned char val);
		void PutByte(std::shared_ptr<string> key, unsigned char val);
		void PutShort(string key, std::shared_ptr<short int> val);
		void PutShort(std::shared_ptr<string> key, std::shared_ptr<short int> val);
		void PutShort(string key, short int val);
		void PutShort(std::shared_ptr<string> key, short int val);
		void PutInt(string key, std::shared_ptr<long int> val);
		void PutInt(std::shared_ptr<string> key, std::shared_ptr<long int> val);
		void PutInt(string key, long int val);
		void PutInt(std::shared_ptr<string> key, long int val);
		void PutLong(string key, std::shared_ptr<long long> val);
		void PutLong(std::shared_ptr<string> key, std::shared_ptr<long long> val);
		void PutLong(string key, long long val);
		void PutLong(std::shared_ptr<string> key, long long val);
		void PutFloat(string key, std::shared_ptr<float> val);
		void PutFloat(std::shared_ptr<string> key, std::shared_ptr<float> val);
		void PutFloat(string key, float val);
		void PutFloat(std::shared_ptr<string> key, float val);
		void PutDouble(string key, std::shared_ptr<double> val);
		void PutDouble(std::shared_ptr<string> key, std::shared_ptr<double> val);
		void PutDouble(string key, double val);
		void PutDouble(std::shared_ptr<string> key, double val);
		void PutUtfString(string key, std::shared_ptr<string> val);
		void PutUtfString(std::shared_ptr<string> key, std::shared_ptr<string> val);
		void PutUtfString(string key, string val);
		void PutUtfString(std::shared_ptr<string> key, string val);
		void PutText(string key, std::shared_ptr<string> val);
		void PutText(std::shared_ptr<string> key, std::shared_ptr<string> val);
		void PutText(string key, string val);
		void PutText(std::shared_ptr<string> key, string val);

		void PutBoolArray(string key, std::shared_ptr<vector<bool> > val);
		void PutBoolArray(std::shared_ptr<string> key, std::shared_ptr<vector<bool> > val);
		void PutByteArray(string key, std::shared_ptr<ByteArray> val);
		void PutByteArray(std::shared_ptr<string> key, std::shared_ptr<ByteArray> val);
		void PutShortArray(string key, std::shared_ptr<vector<short int> > val);
		void PutShortArray(std::shared_ptr<string> key, std::shared_ptr<vector<short int> > val);
		void PutIntArray(string key, std::shared_ptr<vector<long int> > val);
		void PutIntArray(std::shared_ptr<string> key, std::shared_ptr<vector<long int> > val);
		void PutLongArray(string key, std::shared_ptr<vector<long long> > val);
		void PutLongArray(std::shared_ptr<string> key, std::shared_ptr<vector<long long> > val);
		void PutFloatArray(string key, std::shared_ptr<vector<float> > val);
		void PutFloatArray(std::shared_ptr<string> key, std::shared_ptr<vector<float> > val);
		void PutDoubleArray(string key, std::shared_ptr<vector<double> > val);
		void PutDoubleArray(std::shared_ptr<string> key, std::shared_ptr<vector<double> > val);
		void PutUtfStringArray(string key, std::shared_ptr<vector<string> > val);
		void PutUtfStringArray(std::shared_ptr<string> key, std::shared_ptr<vector<string> > val);
		void PutSFSArray(string key, std::shared_ptr<ISFSArray> val);
		void PutSFSArray(std::shared_ptr<string> key, std::shared_ptr<ISFSArray> val);
		void PutSFSObject(string key, std::shared_ptr<ISFSObject> val);
		void PutSFSObject(std::shared_ptr<string> key, std::shared_ptr<ISFSObject> val);

		void Put(string key, std::shared_ptr<SFSDataWrapper> val);
		void Put(std::shared_ptr<string> key, std::shared_ptr<SFSDataWrapper> val);
		bool ContainsKey(string key);
		bool ContainsKey(std::shared_ptr<string> key);
		std::shared_ptr<void> GetClass(string key);
		std::shared_ptr<void> GetClass(std::shared_ptr<string> key);
		std::shared_ptr<string> GetDump(bool format); 
		std::shared_ptr<string> GetDump();
		std::shared_ptr<string> GetHexDump();

		std::shared_ptr<vector<string> > GetKeys();
		bool IsNull(std::shared_ptr<string> key);
		bool IsNull(string key);
		void PutClass(string key, std::shared_ptr<void> val);
		void PutClass(std::shared_ptr<string> key, std::shared_ptr<void> val);
        void RemoveElement(string key);
        void RemoveElement(std::shared_ptr<string> key);
		long int Size();
		std::shared_ptr<ByteArray> ToBinary();

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------

	protected:

		// -------------------------------------------------------------------
		// Protected methods
		// -------------------------------------------------------------------

		// -------------------------------------------------------------------
		// Protected members
		// -------------------------------------------------------------------

	private:

		// -------------------------------------------------------------------
		// Private methods
		// -------------------------------------------------------------------

		std::shared_ptr<string> Dump();

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------

		std::shared_ptr<map<string, std::shared_ptr<SFSDataWrapper> > > dataHolder;
		std::shared_ptr<ISFSDataSerializer> serializer;
	};

}	// namespace Data
}	// namespace Entities
}	// namespace Sfs2X


// --- Entities/Data/SFSArray.h ---
// ===================================================================
//
// Description		
//		Contains the definition of SFSArray
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================


#if defined(_MSC_VER)
#endif
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X::Protocol::Serialization;
using namespace Sfs2X::Util;

namespace Sfs2X {
namespace Entities {
namespace Data {

	/// <summary>
	/// SFSArray
	/// </summary>
	/// <remarks>
	/// <b>SFSArray</b> is used from server and client side to exchange data. It can be thought of a specialized Array/List object that can contain any type of data. The advantage of using SFSArray is that you can fine tune the way your data will be transmitted over the network.
	/// For instance, a number like 100 can be transmitted as a normal <b>integer</b> (which takes 32 bits) but also a <b>short</b> (16 bit) or even a <b>byte</b> (8 bit)
	/// <para/>
	/// <b>SFSArray</b> supports many primitive data types and related arrays of primitives. It also allows to serialize class instances and rebuild them on the Java side. This is explained in greater detail in a separate document.
	/// </remarks>
	/// <seealso cref="SFSObject"/>
	class DLLImportExport SFSArray : public ISFSArray, public std::enable_shared_from_this<SFSArray>
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		/// <summary>
		/// Alternative static constructor that builds an SFSArray populated with the data found in the passed Array
		/// </summary>
		/// <param name="o">
		/// A vector of <see cref="SFSDataWrapper"/> pointers
		/// </param>
		/// <returns>
		/// Pointer to an <see cref="SFSArray"/> instance
		/// </returns>
		static std::shared_ptr<SFSArray> NewFromArray(vector<std::shared_ptr<SFSDataWrapper> > o);

		/// <summary>
		/// Alternative static constructor that builds an SFSArray from a valid SFSArray binary representation
		/// </summary>
		/// <param name="ba">
		/// Pointer to a <see cref="ByteArray"/> instance
		/// </param>
		/// <returns>
		/// Pointer to a <see cref="SFSArray"/> instance
		/// </returns>
		static std::shared_ptr<SFSArray> NewFromBinaryData(std::shared_ptr<ByteArray> ba);

		/// <summary>
		/// Alternative static constructor
		/// </summary>
		/// <returns>
		/// Pointer to a <see cref="SFSArray"/> instance
		/// </returns>
		static std::shared_ptr<SFSArray> NewInstance();

		SFSArray();
		virtual ~SFSArray();

		bool Contains(std::shared_ptr<void> obj);
		std::shared_ptr<SFSDataWrapper> GetWrappedElementAt(long int index);
		std::shared_ptr<void> GetElementAt(long int index);
		std::shared_ptr<void> RemoveElementAt(unsigned long int index);
		long int Size();
		std::shared_ptr<ByteArray> ToBinary();
		std::shared_ptr<string> GetDump();
		std::shared_ptr<string> GetDump(bool format);
		std::shared_ptr<string> GetHexDump();

		/*
		* :::::::::::::::::::::::::::::::::::::::::
		* Type setters
		* :::::::::::::::::::::::::::::::::::::::::	
		*/
		 void AddNull();
		 void AddBool(std::shared_ptr<bool> val);
		 void AddBool(bool val);
		 void AddByte(std::shared_ptr<unsigned char> val);
		 void AddByte(unsigned char val);
		 void AddShort(std::shared_ptr<short int> val);
		 void AddShort(short int val);
		 void AddInt(std::shared_ptr<long int> val);
		 void AddInt(long int val);
		 void AddLong(std::shared_ptr<long long> val);
		 void AddLong(long long val);
		 void AddFloat(std::shared_ptr<float> val);
		 void AddFloat(float val);
		 void AddDouble(std::shared_ptr<double> val);
		 void AddDouble(double val);
		 void AddUtfString(std::shared_ptr<string> val);
		 void AddUtfString(string val);
		 void AddText(std::shared_ptr<string> val);
		 void AddText(string val);
		 void AddBoolArray(std::shared_ptr<vector<std::shared_ptr<bool> > > val);
		 void AddByteArray(std::shared_ptr<ByteArray> val);
		 void AddShortArray(std::shared_ptr<vector<std::shared_ptr<short int> > > val);
		 void AddIntArray(std::shared_ptr<vector<std::shared_ptr<long int> > > val);
		 void AddLongArray(std::shared_ptr<vector<std::shared_ptr<long long> > > val);
 		 void AddFloatArray(std::shared_ptr<vector<std::shared_ptr<float> > > val);
 		 void AddDoubleArray(std::shared_ptr<vector<std::shared_ptr<double> > > val);
		 void AddUtfStringArray(std::shared_ptr<vector<std::shared_ptr<string> > > val);
		 void AddSFSArray(std::shared_ptr<ISFSArray> val);
		 void AddSFSObject(std::shared_ptr<ISFSObject> val);
		 void AddClass(std::shared_ptr<void> val);
		 void Add(std::shared_ptr<SFSDataWrapper> wrappedObject);
		 void AddObject(std::shared_ptr<void> val, SFSDataType tp);

		/*
		* :::::::::::::::::::::::::::::::::::::::::
		* Type getters
		* :::::::::::::::::::::::::::::::::::::::::	
		*/
		 bool IsNull(unsigned long int index);
		 // T GetValue<T>(int index)
		 bool GetBool(unsigned long int index);
		 unsigned char GetByte(unsigned long int index);
		 short int GetShort(unsigned long int index);
		 long int GetInt(unsigned long int index);
		 long long GetLong(unsigned long int index);
		 float GetFloat(unsigned long int index);
		 double GetDouble(unsigned long int index);
		 std::shared_ptr<string> GetUtfString(unsigned long int index);
		 std::shared_ptr<string> GetText(unsigned long int index);
		 std::shared_ptr<vector<std::shared_ptr<void> > > GetArray(unsigned long int index);
		 std::shared_ptr<vector<bool> > GetBoolArray(unsigned long int index);
		 std::shared_ptr<ByteArray> GetByteArray(unsigned long int index);
		 std::shared_ptr<vector<short int> > GetShortArray(unsigned long int index);
		 std::shared_ptr<vector<long int> > GetIntArray(unsigned long int index);
		 std::shared_ptr<vector<long long> > GetLongArray(unsigned long int index);
		 std::shared_ptr<vector<float> > GetFloatArray(unsigned long int index);
		 std::shared_ptr<vector<double> > GetDoubleArray(unsigned long int index);
		 std::shared_ptr<vector<string> > GetUtfStringArray(unsigned long int index);
		 std::shared_ptr<ISFSArray> GetSFSArray(unsigned long int index);
		 std::shared_ptr<void> GetClass(unsigned long int index);
		 std::shared_ptr<ISFSObject> GetSFSObject(unsigned long int index);

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------

	protected:

		// -------------------------------------------------------------------
		// Protected methods
		// -------------------------------------------------------------------

		// -------------------------------------------------------------------
		// Protected members
		// -------------------------------------------------------------------

	private:

		// -------------------------------------------------------------------
		// Private methods
		// -------------------------------------------------------------------
		
		std::shared_ptr<string> Dump();

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------

		std::shared_ptr<ISFSDataSerializer> serializer;
		std::shared_ptr<vector<std::shared_ptr<SFSDataWrapper> > > dataHolder; 
	};

}	// namespace Data
}	// namespace Entities
}	// namespace Sfs2X


// --- Core/PacketHeader.h ---
// ===================================================================
//
// Description		
//		Contains the definition of PacketHeader
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================


#if defined(_MSC_VER)
#endif
using namespace std;					// STL library: declare the STL namespace

namespace Sfs2X {
namespace Core {
	
	// -------------------------------------------------------------------
	// Class PacketHeader
	// -------------------------------------------------------------------
	class PacketHeader
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		PacketHeader(bool encrypted, bool compressed, bool blueBoxed, bool bigSized);
		static std::shared_ptr<PacketHeader> FromBinary(long int headerByte);

		long int ExpectedLength();
		void ExpectedLength(long int value);

		bool Encrypted();
		void Encrypted(bool value);

		bool Compressed();
		void Compressed(bool value);

		bool BlueBoxed();
		void BlueBoxed(bool value);

		bool Binary();
		void Binary(bool value);

		bool BigSized();
		void BigSized(bool value);

		unsigned char Encode();

		std::shared_ptr<string> ToString();

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------

	protected:

		// -------------------------------------------------------------------
		// Protected methods
		// -------------------------------------------------------------------

		// -------------------------------------------------------------------
		// Protected members
		// -------------------------------------------------------------------

	private:

		// -------------------------------------------------------------------
		// Private methods
		// -------------------------------------------------------------------

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------

		long int expectedLength;
		bool binary;
		bool compressed;
		bool encrypted;
		bool blueBoxed;
		bool bigSized;
	};

}	// namespace Core
}	// namespace Sfs2X


// ===================================================================
// IMPLEMENTATION
// ===================================================================
#ifdef CLEVERFOX_IMPLEMENTATION

// --- Exceptions/SFSError.cpp ---
namespace Sfs2X {
namespace Exceptions {

SFSError::SFSError(std::shared_ptr<string> message)
    : std::runtime_error(message ? *message : ""), message(message)
{
}

}
}


// --- Exceptions/SFSCodecError.cpp ---
namespace Sfs2X {
namespace Exceptions {

SFSCodecError::SFSCodecError(std::shared_ptr<string> message)
    : std::runtime_error(message ? *message : ""), message(message)
{
}

}
}


// --- Entities/Data/SFSDataWrapper.cpp ---
// ===================================================================
//
// Description		
//		Contains the implementation of SFSDataWrapper
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================

namespace Sfs2X {
namespace Entities {
namespace Data {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSDataWrapper::SFSDataWrapper(long int type, std::shared_ptr<void> data)
{
	this->type = type;
	this->data = data;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSDataWrapper::SFSDataWrapper(SFSDataType tp, std::shared_ptr<void> data)
{
	this->type = (long int)tp;
	this->data = data;
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
SFSDataWrapper::~SFSDataWrapper()
{
	this->data = std::shared_ptr<void>();
}

// -------------------------------------------------------------------
// Type
// -------------------------------------------------------------------
long int SFSDataWrapper::Type()
{
	return type;
}

// -------------------------------------------------------------------
// Data
// -------------------------------------------------------------------
std::shared_ptr<void> SFSDataWrapper::Data()
{
	return data;
}


}	// namespace Data
}	// namespace Entities
}	// namespace Sfs2X


// --- Util/ByteArray.cpp ---
// ===================================================================
//
// Description		
//		Contains the implementation of ByteArray
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// =================================================================== 
#if defined(_MSC_VER)
#endif


namespace Sfs2X {
namespace Util {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
ByteArray::ByteArray()
{
	buffer = std::shared_ptr<vector<unsigned char> >(new vector<unsigned char>());
	position = 0;
	compressed = false;
	zLibIsInitialized = false;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
ByteArray::ByteArray(std::shared_ptr<vector<unsigned char> > buf)
{
	buffer = buf;
	position = 0;
	compressed = false;
	zLibIsInitialized = false;
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
ByteArray::~ByteArray()
{
}

// -------------------------------------------------------------------
// IsLittleEndian
// -------------------------------------------------------------------
bool ByteArray::IsLittleEndian()
{
    short int number = 0x1;
    char *numPtr = (char*)&number;
    return (numPtr[0] == 1);
}

// -------------------------------------------------------------------
// Bytes
// -------------------------------------------------------------------
std::shared_ptr<vector<unsigned char> > ByteArray::Bytes()
{
	return buffer;
}

// -------------------------------------------------------------------
// Bytes
// -------------------------------------------------------------------
void ByteArray::Bytes(std::shared_ptr<vector<unsigned char> > value)
{
	buffer = value;
	compressed = false;
}

// -------------------------------------------------------------------
// Length
// -------------------------------------------------------------------
long int ByteArray::Length()
{
	return (long int)buffer->size();
}

// -------------------------------------------------------------------
// Position
// -------------------------------------------------------------------
long int ByteArray::Position()
{
	return position;
}

// -------------------------------------------------------------------
// Position
// -------------------------------------------------------------------
void ByteArray::Position(long int value)
{
	position = value;
}

// -------------------------------------------------------------------
// BytesAvailable
// -------------------------------------------------------------------
long int ByteArray::BytesAvailable()
{
	long int val = (long int)buffer->size() - position;
	if (((unsigned long int)val) > buffer->size() || val < 0) val = 0;
	return val;
}

// -------------------------------------------------------------------
// BytesAvailable
// -------------------------------------------------------------------
bool ByteArray::Compressed()
{
	return compressed;
}

// -------------------------------------------------------------------
// BytesAvailable
// -------------------------------------------------------------------
void ByteArray::Compressed(bool value)
{
	compressed = value;
}

// -------------------------------------------------------------------
// Compress
// -------------------------------------------------------------------
void ByteArray::Compress()
{
	if (compressed) {
		throw std::runtime_error("Buffer is already compressed"); 
	}

	// Destination buffer must be at least 0.1% larger than sourceLen plus 12 bytes
	// We set destination buffer length to 1% of source + 12 bytes
	unsigned long sizeCompressed = (long int)buffer->size() + (buffer->size() / 100) + 12;
	std::shared_ptr<unsigned char> dataCompressed (new unsigned char[sizeCompressed], array_deleter<unsigned char>());
	memset (dataCompressed.get(), 0x00, sizeCompressed);

	std::shared_ptr<unsigned char> dataToCompress (new unsigned char[buffer->size()], array_deleter<unsigned char>());
	memset (dataToCompress.get(), 0x00, buffer->size());

	std::copy(buffer->begin(), buffer->end(), dataToCompress.get());

	compress(dataCompressed.get(), &sizeCompressed, dataToCompress.get(), (uLong)buffer->size());

	buffer->clear();
	buffer->insert(buffer->end(), &dataCompressed.get()[0], &dataCompressed.get()[sizeCompressed]);

	this->position = 0;
	this->compressed = true;
}

// -------------------------------------------------------------------
// Uncompress
// -------------------------------------------------------------------
void ByteArray::Uncompress()
{
	// We set destination buffer length as double of source
	unsigned long sizeAreaUncompressed = (unsigned long)(buffer->size() * 2);
	unsigned long sizeUncompressed = 0;
	std::shared_ptr<unsigned char> dataUncompressed;

	std::shared_ptr<unsigned char> dataToUncompress = std::shared_ptr<unsigned char>(new unsigned char[buffer->size()], array_deleter<unsigned char>());
	memset (dataToUncompress.get(), 0x00, buffer->size());

	std::copy(buffer->begin(), buffer->end(), dataToUncompress.get());

	// Loop up to destination buffer is large enough to hold the entire uncompressed data
	do 
	{
		dataUncompressed = std::shared_ptr<unsigned char>(new unsigned char[sizeAreaUncompressed], array_deleter<unsigned char>());
		memset (dataUncompressed.get(), 0x00, sizeAreaUncompressed);

		sizeUncompressed = sizeAreaUncompressed;
		long int result = uncompress(dataUncompressed.get(), &sizeUncompressed, dataToUncompress.get(), (uLong)buffer->size());

		if (result == Z_BUF_ERROR) 
		{
			sizeAreaUncompressed += (unsigned long)buffer->size();
			continue;
		}

		break;

	} while (true);

	buffer->clear();
	buffer->insert(buffer->end(), &dataUncompressed.get()[0], &dataUncompressed.get()[sizeUncompressed]);

	this->position = 0;
	this->compressed = false;
}

// -------------------------------------------------------------------
// CheckCompressedWrite
// -------------------------------------------------------------------
void ByteArray::CheckCompressedWrite()
{
	if (compressed) 
	{
		throw std::runtime_error("Only raw bytes can be written to a compressed array. Call Uncompress first."); 
	}
}

// -------------------------------------------------------------------
// CheckCompressedRead
// -------------------------------------------------------------------
void ByteArray::CheckCompressedRead()
{
	if (compressed) 
	{
		throw std::runtime_error("Only raw bytes can be read from a compressed array."); 
	}
}

// -------------------------------------------------------------------
// ReverseOrder
// -------------------------------------------------------------------
void ByteArray::ReverseOrder(vector<unsigned char>& dt)
{
	// if BitCOnverter becomes BigEndian in future MONO/.NET implementations, use this to work correctly
	if (!IsLittleEndian()) return;

	std::reverse(dt.begin(), dt.end());
}

// -------------------------------------------------------------------
// WriteByte
// -------------------------------------------------------------------
void ByteArray::WriteByte(std::shared_ptr<SFSDataType> tp)
{
	WriteByte((unsigned char)((int)(*tp)));
}

// -------------------------------------------------------------------
// WriteByte
// -------------------------------------------------------------------
void ByteArray::WriteByte(unsigned char b)
{
	std::shared_ptr<vector<unsigned char> > buf (new vector<unsigned char>());
	buf->push_back(b);
	WriteBytes(buf);
}

// -------------------------------------------------------------------
// WriteBytes
// -------------------------------------------------------------------
void ByteArray::WriteBytes(std::shared_ptr<vector<unsigned char> > data)
{
	WriteBytes(data, 0, (long int)data->size());
}

// -------------------------------------------------------------------
// WriteBytes
// -------------------------------------------------------------------
void ByteArray::WriteBytes(std::shared_ptr<vector<unsigned char> > data, long int ofs, long int count)
{
	buffer->insert(buffer->end(), data->begin() + ofs, data->begin() + ofs + count);
}

// -------------------------------------------------------------------
// WriteBool
// -------------------------------------------------------------------
void ByteArray::WriteBool(bool b)
{
	CheckCompressedWrite();

	std::shared_ptr<vector<unsigned char> > buf (new vector<unsigned char>());
	buf->push_back(b ? (unsigned char)1 : (unsigned char)0);
	WriteBytes(buf);
}

// -------------------------------------------------------------------
// WriteInt
// -------------------------------------------------------------------
void ByteArray::WriteInt(int32_t i)
{
	CheckCompressedWrite();

	unsigned char bytes[4];

	bytes[0] = (i >> 24) & 0xFF;
	bytes[1] = (i >> 16) & 0xFF;
	bytes[2] = (i >> 8) & 0xFF;
	bytes[3] = i & 0xFF;

	std::shared_ptr<vector<unsigned char> > buf (new vector<unsigned char>());
	buf->push_back(bytes[0]);
	buf->push_back(bytes[1]);
	buf->push_back(bytes[2]);
	buf->push_back(bytes[3]);
	WriteBytes(buf);
}

// -------------------------------------------------------------------
// WriteUShort
// -------------------------------------------------------------------
void ByteArray::WriteUShort(unsigned short int us)
{
	CheckCompressedWrite();

	unsigned char bytes[2];

	bytes[0] = (us >> 8) & 0xFF;
	bytes[1] = us & 0xFF;

	std::shared_ptr<vector<unsigned char> > buf (new vector<unsigned char>());
	buf->push_back(bytes[0]);
	buf->push_back(bytes[1]);
	WriteBytes(buf);
}

// -------------------------------------------------------------------
// WriteShort
// -------------------------------------------------------------------
void ByteArray::WriteShort(short int s)
{
	CheckCompressedWrite();

	unsigned char bytes[2];

	bytes[0] = (s >> 8) & 0xFF;
	bytes[1] = s & 0xFF;

	std::shared_ptr<vector<unsigned char> > buf (new vector<unsigned char>());
	buf->push_back(bytes[0]);
	buf->push_back(bytes[1]);
	WriteBytes(buf);
}

// -------------------------------------------------------------------
// WriteLong
// -------------------------------------------------------------------
void ByteArray::WriteLong(long long l)
{
	CheckCompressedWrite();

	unsigned char bytes[8];

	bytes[0] = (l >> 56) & 0xFF;
	bytes[1] = (l >> 48) & 0xFF;
	bytes[2] = (l >> 40) & 0xFF;
	bytes[3] = (l >> 32) & 0xFF;
	bytes[4] = (l >> 24) & 0xFF;
	bytes[5] = (l >> 16) & 0xFF;
	bytes[6] = (l >> 8) & 0xFF;
	bytes[7] = l & 0xFF;

	std::shared_ptr<vector<unsigned char> > buf (new vector<unsigned char>());
	buf->push_back(bytes[0]);
	buf->push_back(bytes[1]);
	buf->push_back(bytes[2]);
	buf->push_back(bytes[3]);
	buf->push_back(bytes[4]);
	buf->push_back(bytes[5]);
	buf->push_back(bytes[6]);
	buf->push_back(bytes[7]);
	WriteBytes(buf);
}

// -------------------------------------------------------------------
// WriteFloat
// -------------------------------------------------------------------
void ByteArray::WriteFloat(float f)
{
	CheckCompressedWrite();

	unsigned char bytes[4];

	union  
    {  
         float input;   
         long int output;  
    }    data;  
  
    data.input = f;  
  
    std::bitset<sizeof(float) * CHAR_BIT> bits(data.output);  

	bytes[0] = ((long int)data.output >> 24) & 0xFF;
	bytes[1] = ((long int)data.output >> 16) & 0xFF;
	bytes[2] = ((long int)data.output >> 8) & 0xFF;
	bytes[3] = (long int)data.output & 0xFF;
  
	std::shared_ptr<vector<unsigned char> > buf (new vector<unsigned char>());
	buf->push_back(bytes[0]);
	buf->push_back(bytes[1]);
	buf->push_back(bytes[2]);
	buf->push_back(bytes[3]);
	WriteBytes(buf);
}

// -------------------------------------------------------------------
// WriteDouble
// -------------------------------------------------------------------
void ByteArray::WriteDouble(double d)
{
	CheckCompressedWrite();

	unsigned char bytes[8];

	union  
    {  
         double input;   
         unsigned long long output;  
    }    data;  
  
    data.input = d;  
  
    std::bitset<sizeof(double) * CHAR_BIT> bits(data.output);  

	bytes[0] = ((unsigned long long)data.output >> 56) & 0xFF;
	bytes[1] = ((unsigned long long)data.output >> 48) & 0xFF;
	bytes[2] = ((unsigned long long)data.output >> 40) & 0xFF;
	bytes[3] = ((unsigned long long)data.output >> 32) & 0xFF;
	bytes[4] = ((unsigned long long)data.output >> 24) & 0xFF;
	bytes[5] = ((unsigned long long)data.output >> 16) & 0xFF;
	bytes[6] = ((unsigned long long)data.output >> 8) & 0xFF;
	bytes[7] = (unsigned long long)data.output & 0xFF;

	std::shared_ptr<vector<unsigned char> > buf (new vector<unsigned char>());
	buf->push_back(bytes[0]);
	buf->push_back(bytes[1]);
	buf->push_back(bytes[2]);
	buf->push_back(bytes[3]);
	buf->push_back(bytes[4]);
	buf->push_back(bytes[5]);
	buf->push_back(bytes[6]);
	buf->push_back(bytes[7]);
	WriteBytes(buf);
}

// -------------------------------------------------------------------
// WriteUTF
// -------------------------------------------------------------------
void ByteArray::WriteUTF(string str)
{
	std::shared_ptr<string> value (new string(str));
	WriteUTF(value);
}

void ByteArray::WriteUTF(std::shared_ptr<string> str)
{
	CheckCompressedWrite();
	
	// Incoming string must be encoded as UTF8 by API user
	// No additional conversion to UTF8 is required 
	/*
	unsigned long int utfLen = 0;
	for (unsigned long int i = 0; i < str->size(); i++) 
	{
		unsigned long int c = (*str)[i];
        if ((c >= (unsigned long int)0x0001) && (c <= (unsigned long int)0x007F)) 
		{
			utfLen++;
        }
        else if (c > (unsigned long int)0x07FF) 
		{
			utfLen += 3;
        }
        else 
		{
			utfLen += 2;
        }
	}
			
	if (utfLen > 32768) 
	{
		throw std::runtime_error("String length cannot be greater then 32768 !"); 
	}
	
	WriteUShort((unsigned short int)(utfLen));

	std::shared_ptr<wstring> src (new wstring());
	src->assign(str->begin(), str->end());

	std::shared_ptr<string> dest (new string());
	WStrToUtf8(src, dest);

	vector<unsigned char>utfBuffer;

	const char* utfStringArray = dest->c_str();
	for (unsigned long int enumerator = 0; enumerator < dest->size(); enumerator++)
	{
		utfBuffer.push_back((const unsigned char)(*(utfStringArray + enumerator)));
	}

	std::shared_ptr<vector<unsigned char> > data (new vector<unsigned char>(utfBuffer));
	WriteBytes(data);
	*/

	/* 
	if (str->size() > 32768) 
	{
		throw std::runtime_error("String length cannot be greater then 32768 !"); 
	}
	
	WriteUShort((unsigned short int)(str->size()));

	vector<unsigned char>utfBuffer;

	const char* utfStringArray = str->c_str();
	for (unsigned long int enumerator = 0; enumerator < str->size(); enumerator++)
	{
		utfBuffer.push_back((const unsigned char)(*(utfStringArray + enumerator)));
	}

	std::shared_ptr<vector<unsigned char> > data (new vector<unsigned char>(utfBuffer));
	WriteBytes(data);
	*/

	vector<unsigned char>utfBuffer;
	const char* utfStringArray = str->c_str();
	for (unsigned long int enumerator = 0; enumerator < str->size(); enumerator++)
	{
		utfBuffer.push_back((const unsigned char)(*(utfStringArray + enumerator)));
	}

	if (utfBuffer.size() > 32767)
	{
		throw std::runtime_error("String length cannot be greater than 32767 bytes!");
	}

	WriteUShort((unsigned short int)(utfBuffer.size()));

	std::shared_ptr<vector<unsigned char> > data(new vector<unsigned char>(utfBuffer));
	WriteBytes(data);
}

// -------------------------------------------------------------------
// WriteText
// -------------------------------------------------------------------
void ByteArray::WriteText(string str)
{
	std::shared_ptr<string> value(new string(str));
	WriteText(value);
}

void ByteArray::WriteText(std::shared_ptr<string> str)
{
	CheckCompressedWrite();

	vector<unsigned char>utfBuffer;
	const char* utfStringArray = str->c_str();
	for (unsigned long int enumerator = 0; enumerator < str->size(); enumerator++)
	{
		utfBuffer.push_back((const unsigned char)(*(utfStringArray + enumerator)));
	}

	// SIZE CHECK NOT NEEDED: byte[] length can't be more than Int32.MaxValue

	WriteInt((int32_t)(utfBuffer.size()));

	std::shared_ptr<vector<unsigned char> > data(new vector<unsigned char>(utfBuffer));
	WriteBytes(data);
}

// -------------------------------------------------------------------
// ReadByte
// -------------------------------------------------------------------
void ByteArray::ReadByte(unsigned char& returnedValue)
{
	CheckCompressedRead();
			
	returnedValue = buffer->at(position++);

	return;
}

// -------------------------------------------------------------------
// ReadBytes
// -------------------------------------------------------------------
void ByteArray::ReadBytes(long int count, vector<unsigned char>& returnedValue)
{
	for (long int enumerator = 0; enumerator < count; enumerator++)
	{
		returnedValue.push_back(buffer->at(position + enumerator));
	}

	position += count;
	
	return;
}

// -------------------------------------------------------------------
// ReadBytes
// -------------------------------------------------------------------
void ByteArray::ReadBytes(long int offset, long int count, vector<unsigned char>& returnedValue)
{
	for (long int enumerator = offset; enumerator < count + offset; enumerator++)
	{
		returnedValue.push_back(buffer->at(position + enumerator));
	}

	position += count;
	
	return;
}

// -------------------------------------------------------------------
// ReadBool
// -------------------------------------------------------------------
void ByteArray::ReadBool(bool& returnedValue)
{
	CheckCompressedRead();
	returnedValue = buffer->at(position++) == 1;
	return;
}

// -------------------------------------------------------------------
// ReadInt
// -------------------------------------------------------------------
void ByteArray::ReadInt(int32_t& returnedValue)
{
	CheckCompressedRead();
	vector<unsigned char> data;
	ReadBytes(4, data);

	returnedValue = (((long int)data.at(0)) << 24) |
				    (((long int)data.at(1) << 16)) |
				    (((long int)data.at(2) << 8)) |
				    (((long int)data.at(3)));
			
	return;
}

// -------------------------------------------------------------------
// ReadUShort
// -------------------------------------------------------------------
void ByteArray::ReadUShort(unsigned short int& returnedValue)
{
	CheckCompressedRead();
	vector<unsigned char> data;
	ReadBytes(2, data);

	returnedValue = (((unsigned short int)data.at(0) << 8)) |
				    (((unsigned short int)data.at(1)));
			
	return;
}

// -------------------------------------------------------------------
// ReadShort
// -------------------------------------------------------------------
void ByteArray::ReadShort(short int& returnedValue)
{
	CheckCompressedRead();
	vector<unsigned char> data;
	ReadBytes(2, data);

	returnedValue = (((short int)data.at(0) << 8)) |
				    (((short int)data.at(1)));
			
	return;
}

// -------------------------------------------------------------------
// ReadLong
// -------------------------------------------------------------------
void ByteArray::ReadLong(long long& returnedValue)
{
	CheckCompressedRead();
	vector<unsigned char> data;
	ReadBytes(8, data);

	returnedValue = (((unsigned long long)data.at(0)) << 56) |
				    (((unsigned long long)data.at(1)) << 48) |
				    (((unsigned long long)data.at(2)) << 40) |
				    (((unsigned long long)data.at(3)) << 32) |
				    (((unsigned long long)data.at(4)) << 24) |
				    (((unsigned long long)data.at(5)) << 16) |
				    (((unsigned long long)data.at(6)) << 8) |
				    (((unsigned long long)data.at(7)));
			
	return;
}

// -------------------------------------------------------------------
// ReadFloat
// -------------------------------------------------------------------
void ByteArray::ReadFloat(float& returnedValue)
{
	CheckCompressedRead();
	vector<unsigned char> data;
	ReadBytes(4, data);

	long int readNumber = ((((long int)data.at(0)) << 24) |
					       (((long int)data.at(1)) << 16) |
					       (((long int)data.at(2)) << 8) |
					       (((long int)data.at(3))));
		
//    std::bitset<32> set(readNumber);        
//    long int hexNumber = set.to_ulong();  
  
//    bool negative = !!(hexNumber & 0x80000000);  
//    long int exponent = (hexNumber & 0x7f800000) >> 23;      
    bool negative = !!(readNumber & 0x80000000);  
    long int exponent = (readNumber & 0x7f800000) >> 23;      
    long int sign = negative ? -1 : 1;  
  
    // Subtract 127 from the exponent  
    exponent -= 127;  
  
    // Convert the mantissa into decimal using the last 23 bits  
    long int power = -1;  
    float total = 0.0;  
    for (int i = 0; i < 23; i++)  
    {  
        long int c = (readNumber & (0x80000000 >> (9 + i))) != 0 ? 1 : 0;  
        total += (float)c * (float)pow(2.0, power);  
        power--;  
    }  
    total += 1.0;  
  
    returnedValue = sign * (float)pow(2.0, exponent) * total;  

	return;
}

// -------------------------------------------------------------------
// ReadDouble
// -------------------------------------------------------------------
void ByteArray::ReadDouble(double& returnedValue)
{
	CheckCompressedRead();
	vector<unsigned char> data;
	ReadBytes(8, data);

	unsigned long long readNumber = ((((unsigned long long)data.at(0)) << 56) |
									(((unsigned long long)data.at(1)) << 48) |
									(((unsigned long long)data.at(2)) << 40) |
									(((unsigned long long)data.at(3)) << 32) |
									(((unsigned long long)data.at(4)) << 24) |
									(((unsigned long long)data.at(5)) << 16) |
									(((unsigned long long)data.at(6)) << 8) |
									(((unsigned long long)data.at(7))));
		
//    std::bitset<64> set(readNumber);        
//    unsigned long long hexNumber = set.to_ullong();  
  
//    bool negative = !!(hexNumber & 0x8000000000000000);  
//    long int exponent = (hexNumber & 0x7ff0000000000000) >> 52;      
    bool negative = !!(readNumber & 0x8000000000000000);  
    long int exponent = (readNumber & 0x7ff0000000000000) >> 52;      
    long int sign = negative ? -1 : 1;  
  
    // Subtract 1023 from the exponent  
    exponent -= 1023;  
  
    // Convert the mantissa into decimal using the last 52 bits  
    long int power = -1;  
    double total = 0.0;  
    for (int i = 0; i < 52; i++)  
    {  
        long int c = (readNumber & (0x8000000000000000 >> (12 + i))) != 0 ? 1 : 0;  
        total += (double)c * (double)pow(2.0, power);  
        power--;  
    }  
    total += 1.0;  
  
    returnedValue = sign * (double)pow(2.0, exponent) * total;  

	return;
}

// -------------------------------------------------------------------
// ReadUTF
// -------------------------------------------------------------------
void ByteArray::ReadUTF(string& returnedValue)
{
	CheckCompressedRead();

	// Incoming string must be encoded as UTF8 by API user
	// No additional conversion to UTF8 is required 
	/*
	unsigned short int size;
	ReadUShort(size);

	std::shared_ptr<string> src (new string());

	for (long int enumerator = 0; enumerator < size; enumerator++)
	{
		src->push_back(buffer->at(position + enumerator));
	}

	std::shared_ptr<wstring> dest (new wstring());
	Utf8toWStr(src, dest);

	returnedValue.assign(dest->begin(), dest->end()); 
	position += size;
	*/
	unsigned short int size;
	ReadUShort(size);

	std::shared_ptr<string> src (new string());

	for (long int enumerator = 0; enumerator < size; enumerator++)
	{
		src->push_back(buffer->at(position + enumerator));
	}

	returnedValue.assign(src->begin(), src->end()); 
	position += size;

	return;
}

// -------------------------------------------------------------------
// ReadText
// -------------------------------------------------------------------
void ByteArray::ReadText(string& returnedValue)
{
	CheckCompressedRead();

	int32_t size;
	ReadInt(size);

	std::shared_ptr<string> src(new string());

	for (int32_t enumerator = 0; enumerator < size; enumerator++)
	{
		src->push_back(buffer->at(position + enumerator));
	}

	returnedValue.assign(src->begin(), src->end());
	position += size;
}

}	// namespace Util
}	// namespace Sfs2X


// --- Protocol/Serialization/DefaultObjectDumpFormatter.cpp ---
// ===================================================================
//
// Description		
//		Contains the implementation of DefaultObjectDumpFormatter
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================

namespace Sfs2X {
namespace Protocol {
namespace Serialization {

/*
const char DefaultObjectDumpFormatter::TOKEN_INDENT_OPEN = '{'; //(char) 0x01;
const char DefaultObjectDumpFormatter::TOKEN_INDENT_CLOSE = '}'; //(char) 0x02;
const char DefaultObjectDumpFormatter::TOKEN_DIVIDER = ';'; //(char) 0x03;
const char DefaultObjectDumpFormatter::NEW_LINE = '\n';
const char DefaultObjectDumpFormatter::TAB = '\t';
const char DefaultObjectDumpFormatter::DOT = '.';
*/

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
DefaultObjectDumpFormatter::~DefaultObjectDumpFormatter()
{
}

// -------------------------------------------------------------------
// PrettyPrintDump
// -------------------------------------------------------------------
std::shared_ptr<string> DefaultObjectDumpFormatter::PrettyPrintDump(std::shared_ptr<string> rawDump)
{
	std::shared_ptr<string> strBuf (new string());

	long int indentPos = 0;
	for (unsigned int i = 0; i < rawDump->size(); i++) 
	{
		char ch = rawDump->at(i);
				
		if (ch == TOKEN_INDENT_OPEN) 
		{
			indentPos++;
			strBuf->append(NEW_LINE + (*GetFormatTabs(indentPos)));
		}
		else if (ch == TOKEN_INDENT_CLOSE) 
		{
			indentPos--;
			if (indentPos < 0) 
			{
				std::shared_ptr<string> message(new string("DumpFormatter: the indentPos is negative. TOKENS ARE NOT BALANCED!"));
				std::shared_ptr<SFSError> exception(new SFSError(message));
				throw exception;
			}	
			
			strBuf->append(NEW_LINE + (*(GetFormatTabs(indentPos))));
		}
		else if (ch == TOKEN_DIVIDER) 
		{
			strBuf->append(NEW_LINE + (*(GetFormatTabs(indentPos))));
		}
		else 
		{
			std::shared_ptr<string> temporaryString (new string());

			std::shared_ptr<string> format (new string("%c"));
			StringFormatter<char> (temporaryString, format, ch);

			strBuf->append(*temporaryString.get());
		}
	}
			
	if (indentPos != 0) 
	{
		std::shared_ptr<string> message (new string("DumpFormatter: the indentPos is not == 0. TOKENS ARE NOT BALANCED!"));
		std::shared_ptr<SFSError> exception(new SFSError(message));
		throw exception;
	}
					
	return strBuf;
}

// -------------------------------------------------------------------
// GetFormatTabs
// -------------------------------------------------------------------
std::shared_ptr<string> DefaultObjectDumpFormatter::GetFormatTabs(long int howMany)
{
	return StrFill(TAB, howMany);
}

// -------------------------------------------------------------------
// StrFill
// -------------------------------------------------------------------
std::shared_ptr<string> DefaultObjectDumpFormatter::StrFill(char ch, long int howMany)
{
	std::shared_ptr<string> strBuf (new string());

	for (int i = 0; i < howMany; i++) 
	{
		std::shared_ptr<string> temporaryString (new string());
		std::shared_ptr<string> format (new string("%c"));
		StringFormatter<char> (temporaryString, format, ch);

		strBuf->append(*temporaryString.get());
	}
			
	return strBuf;
}

// -------------------------------------------------------------------
// HexDump
// -------------------------------------------------------------------
std::shared_ptr<string> DefaultObjectDumpFormatter::HexDump(std::shared_ptr<ByteArray> ba)
{
	return HexDump(ba, HEX_BYTES_PER_LINE);
}

// -------------------------------------------------------------------
// HexDump
// -------------------------------------------------------------------
std::shared_ptr<string> DefaultObjectDumpFormatter::HexDump(std::shared_ptr<ByteArray> ba, long int bytesPerLine)
{
	std::shared_ptr<string> sb (new string());
	std::shared_ptr<string> temporaryString (new string());
	
	std::shared_ptr<string> format (new string("Binary Size: %d%c"));
	StringFormatter<long int, char> (temporaryString, format, ba->Length(), NEW_LINE);
	
	sb->append(*temporaryString.get());
	temporaryString->clear();

	if (ba->Length() > MAX_DUMP_LENGTH) 
	{
		std::shared_ptr<string> format (new string("** Data larger than max dump size of %d. Data not displayed"));
		StringFormatter<long int> (temporaryString, format, MAX_DUMP_LENGTH);
		
		sb->append(*temporaryString.get());
		return sb;
	}

	string hexLine;
	string chrLine;

	long int index = 0;
	long int count = 0;
	char currChar;
	unsigned char currByte;
						
	do 
	{
		std::shared_ptr<vector<unsigned char> > vectorBaBytes = ba->Bytes();
		currByte = vectorBaBytes->at(index);

		std::shared_ptr<string> format (new string("%02x"));
		StringFormatter<unsigned char> (temporaryString, format, currByte);
		
		string hexByte(*temporaryString.get());
		temporaryString->clear();
								
		if (hexByte.size() == 1) 
		{
			hexByte = "0" + hexByte;
		}
				
		hexLine.append(hexByte);
		hexLine.append(" ");
				
		if (currByte >= 33 && currByte <= 126) 
		{
			currChar = (unsigned char)(currByte);
		}
		else 
		{
			currChar = DOT;
		}

		format = std::shared_ptr<string>(new string("%c"));
		StringFormatter<char> (temporaryString, format, currChar);
		
		chrLine.append(*temporaryString.get());
		temporaryString->clear();
				
		if (++count == bytesPerLine) 
		{
			count = 0;
			sb->append(hexLine);

			std::shared_ptr<string> format (new string("%c"));
			StringFormatter<char> (temporaryString, format, TAB);
		
			sb->append(*temporaryString.get());
			sb->append(chrLine);
			temporaryString->clear();

			format = std::shared_ptr<string>(new string("%c"));
			StringFormatter<char> (temporaryString, format, NEW_LINE);
		
			sb->append(*temporaryString.get());
			temporaryString->clear();
					
			hexLine.clear();
			chrLine.clear();
		}
				
	} 
	while(++index < ba->Length());
			
	// Add last incomplete line
	if (count != 0) 	
	{
		for (int j = bytesPerLine - count; j > 0; j--)
		{
			hexLine.append("   ");
			chrLine.append(" ");
		}
				
		sb->append(hexLine);

		std::shared_ptr<string> format (new string("%c"));
		StringFormatter<char> (temporaryString, format, TAB);

		sb->append(*temporaryString.get());
		sb->append(chrLine);
		temporaryString->clear();

		format = std::shared_ptr<string>(new string("%c"));
		StringFormatter<char> (temporaryString, format, NEW_LINE);

		sb->append(*temporaryString.get());
	}

	return sb;
}


}	// namespace Serialization
}	// namespace Protocol
}	// namespace Sfs2X


// --- Protocol/Serialization/DefaultSFSDataSerializer.cpp ---
// ===================================================================
//
// Description		
//		Contains the definition of DefaultSFSDataSerializer
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================

namespace Sfs2X {
namespace Protocol {
namespace Serialization {

std::shared_ptr<string> DefaultSFSDataSerializer::CLASS_MARKER_KEY (new string("$C"));
std::shared_ptr<string> DefaultSFSDataSerializer::CLASS_FIELDS_KEY (new string("$F"));
std::shared_ptr<string> DefaultSFSDataSerializer::FIELD_NAME_KEY (new string("N"));
std::shared_ptr<string> DefaultSFSDataSerializer::FIELD_VALUE_KEY (new string("V"));

std::shared_ptr<DefaultSFSDataSerializer> DefaultSFSDataSerializer::instance = std::shared_ptr<DefaultSFSDataSerializer>();

// -------------------------------------------------------------------
// Instance
// -------------------------------------------------------------------
std::shared_ptr<DefaultSFSDataSerializer> DefaultSFSDataSerializer::Instance()
{
	if (instance == NULL)
	{
		instance = std::shared_ptr<DefaultSFSDataSerializer>(new DefaultSFSDataSerializer());
	}

	return instance;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
DefaultSFSDataSerializer::DefaultSFSDataSerializer()
{
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
DefaultSFSDataSerializer::~DefaultSFSDataSerializer()
{
}

// SFSObject ==> Binary

// -------------------------------------------------------------------
// Object2Binary
// -------------------------------------------------------------------
std::shared_ptr<ByteArray> DefaultSFSDataSerializer::Object2Binary(std::shared_ptr<ISFSObject> obj)
{
	std::shared_ptr<ByteArray> buffer (new ByteArray());
	buffer->WriteByte((unsigned char)SFSDATATYPE_SFS_OBJECT);
	buffer->WriteShort((short int)obj->Size());
			
	return Obj2bin(obj, buffer);
}

std::shared_ptr<ByteArray> DefaultSFSDataSerializer::Obj2bin(std::shared_ptr<ISFSObject> obj, std::shared_ptr<ByteArray> buffer)
{
	std::shared_ptr<vector<string> > keys = obj->GetKeys();
	std::shared_ptr<SFSDataWrapper> wrapper;

	vector<string>::iterator iterator;
	for(iterator = keys->begin(); iterator != keys->end(); ++iterator)
	{
		std::shared_ptr<string> key (new string(*iterator));

		wrapper = obj->GetData(*key);

		// Store the key
		buffer = EncodeSFSObjectKey(buffer, key);
																
		// Convert 2 binary
		buffer = EncodeObject(buffer, wrapper->Type(), wrapper->Data());
	}

	keys->clear();

	return buffer;
}


// SFSArray ==> Binary

std::shared_ptr<ByteArray> DefaultSFSDataSerializer::Array2Binary(std::shared_ptr<ISFSArray> arrayobj)
{
	std::shared_ptr<ByteArray> buffer (new ByteArray());
	buffer->WriteByte((unsigned char) SFSDATATYPE_SFS_ARRAY);
	buffer->WriteShort((short)arrayobj->Size());
	return Arr2bin(arrayobj, buffer);
}

std::shared_ptr<ByteArray> DefaultSFSDataSerializer::Arr2bin(std::shared_ptr<ISFSArray> arrayobj, std::shared_ptr<ByteArray> buffer)
{
	std::shared_ptr<SFSDataWrapper> wrapper;

	for (int i = 0; i < arrayobj->Size(); i++)	
	{
		wrapper = arrayobj->GetWrappedElementAt(i);
		buffer = EncodeObject(buffer, wrapper->Type(), wrapper->Data());
	}
			
	return buffer;
}


// Binary ==> SFSObject

std::shared_ptr<ISFSObject> DefaultSFSDataSerializer::Binary2Object(std::shared_ptr<ByteArray> data)
{
	if (data->Length() < 3) 
	{
		std::shared_ptr<string> err (new string());

		std::shared_ptr<string> format (new string("Can't decode an SFSObject. Byte data is insufficient. Size: %d byte(s)"));
		StringFormatter<long int> (err, format, data->Length());
		
		std::shared_ptr<SFSCodecError> exception(new SFSCodecError(err));
		throw exception;
	}
			
	data->Position(0);
	return DecodeSFSObject(data);
}

std::shared_ptr<ISFSObject> DefaultSFSDataSerializer::DecodeSFSObject(std::shared_ptr<ByteArray> buffer)
{
	std::shared_ptr<SFSObject> sfsObject (SFSObject::NewInstance());
						
	// Get tpyeId
	unsigned char headerByte;
	buffer->ReadByte(headerByte);
						
	// Validate typeId
	if (headerByte != (unsigned char)SFSDATATYPE_SFS_OBJECT) 
	{
		std::shared_ptr<string> err (new string());

		std::shared_ptr<string> format (new string("Invalid SFSDataType. Expected: %d, found: %d"));
		StringFormatter<long int, unsigned char> (err, format, SFSDATATYPE_SFS_OBJECT, headerByte);

		std::shared_ptr<SFSCodecError> exception(new SFSCodecError(err));
		throw exception;
	}
	
	short int size;
	buffer->ReadShort(size);
			
	// Validate size
	if (size < 0) 
	{
		std::shared_ptr<string> err (new string());

		std::shared_ptr<string> format (new string("Can't decode SFSObject. Size is negative: %d"));
		StringFormatter<long int> (err, format, size);

		std::shared_ptr<SFSCodecError> exception(new SFSCodecError(err));
		throw exception;
	}		
			
	/*
     * NOTE: we catch codec exceptions OUTSIDE of the loop
     * meaning that any exception of that type will stop the process of looping through the
     * object data and immediately discard the whole packet of data. 
     */

	try 
	{
		for (int i = 0; i < size; i++) 
		{
			// Decode object key
	     	string key;
			buffer->ReadUTF(key);
		     		
			//Console.WriteLine("Decoding object "+key);
					
	     	// Decode the next object
	     	std::shared_ptr<SFSDataWrapper> decodedObject = DecodeObject(buffer);
		     		
	     	// Store decoded object and keep going
	     	if (decodedObject != NULL) 
			{
				std::shared_ptr<string> keyRef (new string(key));
	     		sfsObject->Put(keyRef, decodedObject);
			}		
	     	else 
			{
				std::shared_ptr<string> err (new string());

				std::shared_ptr<string> format (new string("Could not decode value for SFSObject with key: %s"));
				StringFormatter<const char*> (err, format, key.c_str());

				std::shared_ptr<SFSCodecError> exception(new SFSCodecError(err));
				throw exception;
			}
	    }	
	}
	catch (SFSCodecError err) 
	{
		throw err;
	}
		
	return sfsObject;
}


// Binary ==> SFSArray

std::shared_ptr<ISFSArray> DefaultSFSDataSerializer::Binary2Array(std::shared_ptr<ByteArray> data)
{
	if (data->Length() < 3) 
	{
		std::shared_ptr<string> err (new string());

		std::shared_ptr<string> format (new string("Can't decode an SFSArray. Byte data is insufficient. Size:: %d byte(s)"));
		StringFormatter<long int> (err, format, data->Length());
		
		std::shared_ptr<SFSCodecError> exception(new SFSCodecError(err));
		throw exception;
	}
			
	data->Position(0);
	return DecodeSFSArray(data);
}

std::shared_ptr<ISFSArray> DefaultSFSDataSerializer::DecodeSFSArray(std::shared_ptr<ByteArray> buffer)
{
	std::shared_ptr<ISFSArray> sfsArray (SFSArray::NewInstance());

	// Get tpyeId
	unsigned char type;
	buffer->ReadByte(type);
	SFSDataType headerType = (SFSDataType)(long int)(type);
			
	// Validate typeId
	if (headerType != SFSDATATYPE_SFS_ARRAY) 
	{
		std::shared_ptr<string> err (new string());

		std::shared_ptr<string> format (new string("Invalid SFSDataType. Expected: %d, found: %d"));
		StringFormatter<long int, long int> (err, format, SFSDATATYPE_SFS_ARRAY, headerType);

		std::shared_ptr<SFSCodecError> exception(new SFSCodecError(err));
		throw exception;
	}
				
	short int size;
	buffer->ReadShort(size);
			
	// Validate size
	if (size < 0) 
	{
		std::shared_ptr<string> err (new string());

		std::shared_ptr<string> format (new string("Can't decode SFSArray. Size is negative: %d"));
		StringFormatter<long int> (err, format, size);

		std::shared_ptr<SFSCodecError> exception(new SFSCodecError(err));
		throw exception;
	}
				
	/*
	 * NOTE: we catch codec exceptions OUTSIDE of the loop
	 * meaning that any exception of that type will stop the process of looping through the
	 * object data and immediately discard the whole packet of data. 
	 */

	try
	{
		for (long int i = 0; i < size; i++) 
		{
			// Decode the next object
		    std::shared_ptr<SFSDataWrapper> decodedObject = DecodeObject(buffer);

		     // Store decoded object and keep going
		     if (decodedObject != NULL) 
			 {
				sfsArray->Add(decodedObject);
			}
		    else 
			{
				std::shared_ptr<string> err (new string());

				std::shared_ptr<string> format (new string("Could not decode SFSArray item at index: %d"));
				StringFormatter<long int> (err, format, i);

				std::shared_ptr<SFSCodecError> exception(new SFSCodecError(err));
				throw exception;
			}
		}	
	}
	catch (SFSCodecError err)
	{
		throw err;
	}
		     
	return sfsArray;
}

std::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::DecodeObject(std::shared_ptr<ByteArray> buffer)
{
	std::shared_ptr<SFSDataWrapper> decodedObject;
	unsigned char headerValue;
	buffer->ReadByte(headerValue);
	SFSDataType headerByte = (SFSDataType)(long int)(headerValue);
			
	// Console.WriteLine(headerByte);
	if (headerByte == SFSDATATYPE_NULL)
	 	decodedObject = BinDecode_NULL(buffer);
	else if (headerByte == SFSDATATYPE_BOOL)
		decodedObject = BinDecode_BOOL(buffer);
	else if (headerByte == SFSDATATYPE_BOOL_ARRAY)
		decodedObject = BinDecode_BOOL_ARRAY(buffer);
	else if (headerByte == SFSDATATYPE_BYTE)
		decodedObject = BinDecode_BYTE(buffer);
	else if (headerByte == SFSDATATYPE_BYTE_ARRAY)
		decodedObject = BinDecode_BYTE_ARRAY(buffer);
	else if (headerByte == SFSDATATYPE_SHORT)
		decodedObject = BinDecode_SHORT(buffer);
	else if (headerByte == SFSDATATYPE_SHORT_ARRAY)
		decodedObject = BinDecode_SHORT_ARRAY(buffer);
	else if (headerByte == SFSDATATYPE_INT)
		decodedObject = BinDecode_INT(buffer);
	else if (headerByte == SFSDATATYPE_INT_ARRAY)
		decodedObject = BinDecode_INT_ARRAY(buffer);
	else if (headerByte == SFSDATATYPE_LONG)
		decodedObject = BinDecode_LONG(buffer);
	else if (headerByte == SFSDATATYPE_LONG_ARRAY)
		decodedObject = BinDecode_LONG_ARRAY(buffer);
	else if (headerByte == SFSDATATYPE_FLOAT)
		decodedObject = BinDecode_FLOAT(buffer);
	else if (headerByte == SFSDATATYPE_FLOAT_ARRAY)
		decodedObject = BinDecode_FLOAT_ARRAY(buffer);
	else if (headerByte == SFSDATATYPE_DOUBLE)
		decodedObject = BinDecode_DOUBLE(buffer);
	else if (headerByte == SFSDATATYPE_DOUBLE_ARRAY)
		decodedObject = BinDecode_DOUBLE_ARRAY(buffer);
	else if (headerByte == SFSDATATYPE_UTF_STRING)
		decodedObject = BinDecode_UTF_STRING(buffer);
	else if (headerByte == SFSDATATYPE_TEXT)
		decodedObject = BinDecode_TEXT(buffer);
	else if (headerByte == SFSDATATYPE_UTF_STRING_ARRAY)
		decodedObject = BinDecode_UTF_STRING_ARRAY(buffer);
	else if (headerByte == SFSDATATYPE_SFS_ARRAY) {
		// pointer goes back 1 position
		buffer->Position(buffer->Position() - 1);
		decodedObject = std::shared_ptr<SFSDataWrapper>(new SFSDataWrapper((long int)SFSDATATYPE_SFS_ARRAY, DecodeSFSArray(buffer)));
	}
	else if (headerByte == SFSDATATYPE_SFS_OBJECT)
	{
		// pointer goes back 1 position
		buffer->Position(buffer->Position() - 1);
				
		/*
		* See if this is a special type of SFSObject, the one that actually describes a Class
		*/
		std::shared_ptr<ISFSObject> sfsObj = DecodeSFSObject(buffer);
		unsigned char type = (unsigned char)((long int)SFSDATATYPE_SFS_OBJECT);
		std::shared_ptr<void> finalSfsObj = sfsObj;
				
		if (sfsObj->ContainsKey(CLASS_MARKER_KEY) && sfsObj->ContainsKey(CLASS_FIELDS_KEY)) 
		{   
			type = (unsigned char)((long int)SFSDATATYPE_CLASS);
		}
				
		decodedObject = std::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(type, finalSfsObj));
	}
	// What is this typeID??
	else 
	{
		std::shared_ptr<string> err (new string());

		std::shared_ptr<string> format (new string("Unknow SFSDataType ID: %d"));
		StringFormatter<long int> (err, format, headerByte);

		std::shared_ptr<SFSCodecError> exception(new SFSCodecError(err));
		throw exception;
	}
			
	return decodedObject;
}

std::shared_ptr<ByteArray> DefaultSFSDataSerializer::EncodeObject(std::shared_ptr<ByteArray> buffer, int typeId, std::shared_ptr<void> data)
{
	switch((SFSDataType)typeId) 
	{
	case SFSDATATYPE_NULL:
		buffer = BinEncode_NULL(buffer);
		break;
	case SFSDATATYPE_BOOL:
		buffer = BinEncode_BOOL(buffer, (std::static_pointer_cast<bool>)(data));
		break;
	case SFSDATATYPE_BYTE:
		buffer = BinEncode_BYTE(buffer, (std::static_pointer_cast<unsigned char>)(data));
		break;
	case SFSDATATYPE_SHORT:
		buffer = BinEncode_SHORT(buffer, (std::static_pointer_cast<short int>)(data));
		break;
	case SFSDATATYPE_INT:
		buffer = BinEncode_INT(buffer, (std::static_pointer_cast<long int>)(data));
		break;
	case SFSDATATYPE_LONG:
		buffer = BinEncode_LONG(buffer, (std::static_pointer_cast<long long>)(data));
		break;
	case SFSDATATYPE_FLOAT:
		buffer = BinEncode_FLOAT(buffer, (std::static_pointer_cast<float>)(data));
		break;
	case SFSDATATYPE_DOUBLE:
		buffer = BinEncode_DOUBLE(buffer, (std::static_pointer_cast<double>)(data));
		break;
	case SFSDATATYPE_UTF_STRING:
		buffer = BinEncode_UTF_STRING(buffer, (std::static_pointer_cast<string>)(data));
		break;
	case SFSDATATYPE_TEXT:
		buffer = BinEncode_TEXT(buffer, (std::static_pointer_cast<string>)(data));
		break;
	case SFSDATATYPE_BOOL_ARRAY:
		buffer = BinEncode_BOOL_ARRAY(buffer, (std::static_pointer_cast<vector<bool> >)(data));
		break;
	case SFSDATATYPE_BYTE_ARRAY:
		buffer = BinEncode_BYTE_ARRAY(buffer, (std::static_pointer_cast<ByteArray>)(data)); 
		break;
	case SFSDATATYPE_SHORT_ARRAY:
		buffer = BinEncode_SHORT_ARRAY(buffer, (std::static_pointer_cast<vector<short int> >)(data));
		break;
	case SFSDATATYPE_INT_ARRAY:
		buffer = BinEncode_INT_ARRAY(buffer, (std::static_pointer_cast<vector<long int> >)(data));
		break;
	case SFSDATATYPE_LONG_ARRAY:
		buffer = BinEncode_LONG_ARRAY(buffer, (std::static_pointer_cast<vector<long long> >)(data));
		break;
	case SFSDATATYPE_FLOAT_ARRAY:
		buffer = BinEncode_FLOAT_ARRAY(buffer, (std::static_pointer_cast<vector<float> >)(data));
		break;
	case SFSDATATYPE_DOUBLE_ARRAY:
		buffer = BinEncode_DOUBLE_ARRAY(buffer, (std::static_pointer_cast<vector<double> >)(data));
		break;
	case SFSDATATYPE_UTF_STRING_ARRAY:
		buffer = BinEncode_UTF_STRING_ARRAY(buffer, (std::static_pointer_cast<vector<string> >)(data));
		break;
	case SFSDATATYPE_SFS_ARRAY:
		buffer = AddData(buffer, Array2Binary((std::static_pointer_cast<ISFSArray>)(data)));
		break;
	case SFSDATATYPE_SFS_OBJECT:
		buffer = AddData(buffer, Object2Binary((std::static_pointer_cast<SFSObject>)(data)));
		break;
	case SFSDATATYPE_CLASS:
		buffer = AddData(buffer, Object2Binary((std::static_pointer_cast<SFSObject>)(data)));
		break;
	default:
		{
			std::shared_ptr<string> err (new string());

			std::shared_ptr<string> format (new string("Unrecognized type in SFSObject serialization: %d"));
			StringFormatter<long int> (err, format, typeId);

			std::shared_ptr<SFSCodecError> exception(new SFSCodecError(err));
			throw exception;
		}
	}
			
	return buffer;
}


// Binary Entities Decoding Methods

std::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::BinDecode_NULL(std::shared_ptr<ByteArray> buffer)
{
	return std::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDATATYPE_NULL, std::shared_ptr<void>()));
}

std::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::BinDecode_BOOL(std::shared_ptr<ByteArray> buffer)
{
	std::shared_ptr<bool> value (new bool());
	buffer->ReadBool(*value);
	return std::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDATATYPE_BOOL, (std::static_pointer_cast<void>)(value)));
}
std::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::BinDecode_BYTE(std::shared_ptr<ByteArray> buffer)
{
	std::shared_ptr<unsigned char> value (new unsigned char());
	buffer->ReadByte(*value);
	return std::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDATATYPE_BYTE, (std::static_pointer_cast<void>)(value)));
}

std::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::BinDecode_SHORT(std::shared_ptr<ByteArray> buffer)
{
	std::shared_ptr<short int> value (new short int());
	buffer->ReadShort(*value);
	return std::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDATATYPE_SHORT, (std::static_pointer_cast<void>)(value)));
}

std::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::BinDecode_INT(std::shared_ptr<ByteArray> buffer)
{
	int32_t tmp;
	buffer->ReadInt(tmp);
	std::shared_ptr<long int> value (new long int((long int)tmp));
	return std::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDATATYPE_INT, (std::static_pointer_cast<void>)(value)));
}

std::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::BinDecode_LONG(std::shared_ptr<ByteArray> buffer)
{
	std::shared_ptr<long long> value (new long long());
	buffer->ReadLong(*value);
	return std::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDATATYPE_LONG, (std::static_pointer_cast<void>)(value)));
}

std::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::BinDecode_FLOAT(std::shared_ptr<ByteArray> buffer)
{
	std::shared_ptr<float> value (new float());
	buffer->ReadFloat(*value);
	return std::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDATATYPE_FLOAT, (std::static_pointer_cast<void>)(value)));
}

std::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::BinDecode_DOUBLE(std::shared_ptr<ByteArray> buffer)
{
	std::shared_ptr<double> value (new double());
	buffer->ReadDouble(*value);
	return std::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDATATYPE_DOUBLE, (std::static_pointer_cast<void>)(value)));
}

std::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::BinDecode_UTF_STRING(std::shared_ptr<ByteArray> buffer)
{
	std::shared_ptr<string> value (new string()); 
	buffer->ReadUTF(*value);
	return std::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDATATYPE_UTF_STRING, (std::static_pointer_cast<void>)(value)));
}

std::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::BinDecode_TEXT(std::shared_ptr<ByteArray> buffer) 
{
	std::shared_ptr<string> value(new string());
	buffer->ReadText(*value);
	return std::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDATATYPE_TEXT, (std::static_pointer_cast<void>)(value)));
}

std::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::BinDecode_BOOL_ARRAY(std::shared_ptr<ByteArray> buffer)
{
	long int size = GetTypedArraySize(buffer);
	std::shared_ptr<vector<bool> > arrayobj (new vector<bool>());
			
	for (int j = 0; j < size; j++) 
	{
		std::shared_ptr<bool> value (new bool);
		buffer->ReadBool(*value);
		arrayobj->push_back(*value);
	}
			
	return std::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDATATYPE_BOOL_ARRAY, arrayobj));
}

std::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::BinDecode_BYTE_ARRAY(std::shared_ptr<ByteArray> buffer)
{
	int32_t size;
	buffer->ReadInt(size);
			
	if (size < 0) 
	{
		std::shared_ptr<string> err (new string());
		 
		std::shared_ptr<string> format (new string("Array negative size: %d"));
		StringFormatter<int32_t> (err, format, size);

		std::shared_ptr<SFSCodecError> exception(new SFSCodecError(err));
		throw exception;
	}
	
	// copy bytes
	std::shared_ptr<vector<unsigned char> > values (new vector<unsigned char>());
	buffer->ReadBytes(size, *values.get());
	std::shared_ptr<ByteArray> arrayobj (new ByteArray());
	arrayobj->WriteBytes(values);
						
	return std::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDATATYPE_BYTE_ARRAY, arrayobj));
}

std::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::BinDecode_SHORT_ARRAY(std::shared_ptr<ByteArray> buffer)
{
	int32_t size = GetTypedArraySize(buffer);
	std::shared_ptr<vector<short int> > arrayobj (new vector<short int>());
			
	for (int32_t j = 0; j < size; j++)
	{
		short int value;
		buffer->ReadShort(value);
		arrayobj->push_back(value);
	}
			
	return std::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDATATYPE_SHORT_ARRAY, arrayobj));
}

std::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::BinDecode_INT_ARRAY(std::shared_ptr<ByteArray> buffer)
{
	int32_t size = GetTypedArraySize(buffer);
	std::shared_ptr<vector<long int> > arrayobj (new vector<long int>());
			
	for (int32_t j = 0; j < size; j++)
	{
		int32_t value;
		buffer->ReadInt(value);
		arrayobj->push_back(value);
	}
			
	return std::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDATATYPE_INT_ARRAY, arrayobj));
}

std::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::BinDecode_LONG_ARRAY(std::shared_ptr<ByteArray> buffer)
{
	int32_t size = GetTypedArraySize(buffer);
	std::shared_ptr<vector<long long> > arrayobj (new vector<long long>());
			
	for (int j = 0; j < size; j++) 
	{
		long long value;
		buffer->ReadLong(value);
		arrayobj->push_back(value);
	}
			
	return std::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDATATYPE_LONG_ARRAY, arrayobj));
}

std::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::BinDecode_FLOAT_ARRAY(std::shared_ptr<ByteArray> buffer)
{
	int32_t size = GetTypedArraySize(buffer);
			
	std::shared_ptr<vector<float> > arrayobj (new vector<float>());
			
	for (int32_t j = 0; j < size; j++)
	{
		float value;
		buffer->ReadFloat(value);
		arrayobj->push_back(value);
	}
			
	return std::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDATATYPE_FLOAT_ARRAY, arrayobj));
}

std::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::BinDecode_DOUBLE_ARRAY(std::shared_ptr<ByteArray> buffer)
{
	int32_t size = GetTypedArraySize(buffer);
			
	std::shared_ptr<vector<double> > arrayobj (new vector<double>());
			
	for (int32_t j = 0; j < size; j++)
	{
		double value;
		buffer->ReadDouble(value);
		arrayobj->push_back(value);
	}
			
	return std::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDATATYPE_DOUBLE_ARRAY, arrayobj));
}

std::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::BinDecode_UTF_STRING_ARRAY(std::shared_ptr<ByteArray> buffer)
{
	int32_t size = GetTypedArraySize(buffer);
			
	std::shared_ptr<vector<string> > arrayobj (new vector<string>());
			
	for (int32_t j = 0; j < size; j++)
	{
		string value;
		buffer->ReadUTF(value);
		arrayobj->push_back(value);
	}
			
	return std::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDATATYPE_UTF_STRING_ARRAY, arrayobj));
}

int32_t DefaultSFSDataSerializer::GetTypedArraySize(std::shared_ptr<ByteArray> buffer)
{
	short int size;
	buffer->ReadShort(size);
			
	if (size < 0) 
	{
		std::shared_ptr<string> err (new string());

		std::shared_ptr<string> format (new string("Array negative size: %d"));
		StringFormatter<short int> (err, format, size);

		std::shared_ptr<SFSCodecError> exception(new SFSCodecError(err));
		throw exception;
	}
				
	return size;
}


// Binary Entities Encoding Methods

std::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_NULL(std::shared_ptr<ByteArray> buffer)
{
	std::shared_ptr<ByteArray> data (new ByteArray());
	data->WriteByte((unsigned char)0x00);
	return AddData(buffer, data);
}

std::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_BOOL(std::shared_ptr<ByteArray> buffer, std::shared_ptr<bool> val)
{
	std::shared_ptr<ByteArray> data (new ByteArray());
	data->WriteByte(SFSDATATYPE_BOOL);
	data->WriteBool(*val);
	return AddData(buffer, data);
}

std::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_BYTE(std::shared_ptr<ByteArray> buffer, std::shared_ptr<unsigned char> val)
{
	std::shared_ptr<ByteArray> data (new ByteArray());
	data->WriteByte(SFSDATATYPE_BYTE);
	data->WriteByte(*val);
	return AddData(buffer, data);
}

std::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_SHORT(std::shared_ptr<ByteArray> buffer, std::shared_ptr<short int> val)
{
	std::shared_ptr<ByteArray> data (new ByteArray());
	data->WriteByte(SFSDATATYPE_SHORT);
	data->WriteShort(*val);
	return AddData(buffer, data);
}

std::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_INT(std::shared_ptr<ByteArray> buffer, std::shared_ptr<long int> val)
{
	std::shared_ptr<ByteArray> data (new ByteArray());
	data->WriteByte(SFSDATATYPE_INT);
	data->WriteInt((int32_t)*val);
	return AddData(buffer, data);
}

std::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_LONG(std::shared_ptr<ByteArray> buffer, std::shared_ptr<long long> val)
{
	std::shared_ptr<ByteArray> data (new ByteArray());
	data->WriteByte(SFSDATATYPE_LONG);
	data->WriteLong(*val);
	return AddData(buffer, data);
}

std::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_FLOAT(std::shared_ptr<ByteArray> buffer, std::shared_ptr<float> val)
{
	std::shared_ptr<ByteArray> data (new ByteArray());
	data->WriteByte(SFSDATATYPE_FLOAT);
	data->WriteFloat(*val);
	return AddData(buffer, data);
}

std::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_DOUBLE(std::shared_ptr<ByteArray> buffer, std::shared_ptr<double> val)
{
	std::shared_ptr<ByteArray> data (new ByteArray());
	data->WriteByte(SFSDATATYPE_DOUBLE);
	data->WriteDouble(*val);
	return AddData(buffer, data);
}

std::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_INT(std::shared_ptr<ByteArray> buffer, std::shared_ptr<double> val)
{
	std::shared_ptr<ByteArray> data (new ByteArray());
	data->WriteByte(SFSDATATYPE_DOUBLE);
	data->WriteDouble(*val);
	return AddData(buffer, data);
}

std::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_UTF_STRING(std::shared_ptr<ByteArray> buffer, std::shared_ptr<string> val)
{
	std::shared_ptr<ByteArray> data (new ByteArray());
	data->WriteByte(SFSDATATYPE_UTF_STRING);
	data->WriteUTF(val);
	return AddData(buffer, data);
}

std::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_TEXT(std::shared_ptr<ByteArray> buffer, std::shared_ptr<string> val)
{
	std::shared_ptr<ByteArray> data(new ByteArray());
	data->WriteByte(SFSDATATYPE_TEXT);
	data->WriteText(val);
	return AddData(buffer, data);
}

std::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_BOOL_ARRAY(std::shared_ptr<ByteArray> buffer, std::shared_ptr<vector<bool> > val)
{
	std::shared_ptr<ByteArray> data (new ByteArray());
	data->WriteByte(SFSDATATYPE_BOOL_ARRAY);
	data->WriteShort((short int)(val->size()));
			
	vector<bool>::iterator iterator;
	for(iterator = val->begin(); iterator != val->end(); ++iterator)
	{
		data->WriteBool(*iterator);
	}
			
	return AddData(buffer, data);
}

std::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_BYTE_ARRAY(std::shared_ptr<ByteArray> buffer, std::shared_ptr<ByteArray> val)
{
	std::shared_ptr<ByteArray> data (new ByteArray());
	data->WriteByte(SFSDATATYPE_BYTE_ARRAY);
	data->WriteInt(val->Length());
	data->WriteBytes(val->Bytes());
	return AddData(buffer, data);
}

std::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_SHORT_ARRAY(std::shared_ptr<ByteArray> buffer, std::shared_ptr<vector<short int> > val)
{
	std::shared_ptr<ByteArray> data (new ByteArray());
	data->WriteByte(SFSDATATYPE_SHORT_ARRAY);
	data->WriteShort((short int)(val->size()));

	vector<short int>::iterator iterator;
	for(iterator = val->begin(); iterator != val->end(); ++iterator)
	{
		data->WriteShort(*iterator);
	}
			
	return AddData(buffer, data);
}

std::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_INT_ARRAY(std::shared_ptr<ByteArray> buffer, std::shared_ptr<vector<long int> > val)
{
	std::shared_ptr<ByteArray> data (new ByteArray());
	data->WriteByte(SFSDATATYPE_INT_ARRAY);
	data->WriteShort((short int)(val->size()));

	vector<long int>::iterator iterator;
	for(iterator = val->begin(); iterator != val->end(); ++iterator)
	{
		data->WriteInt((int32_t)(*iterator));
	}
			
	return AddData(buffer, data);
}

std::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_LONG_ARRAY(std::shared_ptr<ByteArray> buffer, std::shared_ptr<vector<long long> > val)
{
	std::shared_ptr<ByteArray> data (new ByteArray());
	data->WriteByte(SFSDATATYPE_LONG_ARRAY);
	data->WriteShort((short int)(val->size()));

	vector<long long>::iterator iterator;
	for(iterator = val->begin(); iterator != val->end(); ++iterator)
	{
		data->WriteLong(*iterator);
	}
			
	return AddData(buffer, data);
}

std::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_FLOAT_ARRAY(std::shared_ptr<ByteArray> buffer, std::shared_ptr<vector<float> > val)
{
	std::shared_ptr<ByteArray> data (new ByteArray());
	data->WriteByte(SFSDATATYPE_FLOAT_ARRAY);
	data->WriteShort((short int)(val->size()));
			
	vector<float>::iterator iterator;
	for(iterator = val->begin(); iterator != val->end(); ++iterator)
	{
		data->WriteFloat(*iterator);
	}
			
	return AddData(buffer, data);
}

std::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_DOUBLE_ARRAY(std::shared_ptr<ByteArray> buffer, std::shared_ptr<vector<double> > val)
{
	std::shared_ptr<ByteArray> data (new ByteArray());
	data->WriteByte(SFSDATATYPE_DOUBLE_ARRAY);
	data->WriteShort((short int)(val->size()));

	vector<double>::iterator iterator;
	for(iterator = val->begin(); iterator != val->end(); ++iterator)
	{
		data->WriteDouble(*iterator);
	}
			
	return AddData(buffer, data);
}

std::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_UTF_STRING_ARRAY(std::shared_ptr<ByteArray> buffer, std::shared_ptr<vector<string> > val)
{
	std::shared_ptr<ByteArray> data (new ByteArray());
	data->WriteByte(SFSDATATYPE_UTF_STRING_ARRAY);
	data->WriteShort((short int)(val->size()));

	vector<string>::iterator iterator;
	for(iterator = val->begin(); iterator != val->end(); ++iterator)
	{
		data->WriteUTF(*iterator);
	}
			
	return AddData(buffer, data);
}

std::shared_ptr<ByteArray> DefaultSFSDataSerializer::EncodeSFSObjectKey(std::shared_ptr<ByteArray> buffer, std::shared_ptr<string> val)
{
	buffer->WriteUTF(val);	
	return buffer;
}

std::shared_ptr<ByteArray> DefaultSFSDataSerializer::AddData(std::shared_ptr<ByteArray> buffer, std::shared_ptr<ByteArray> newData)
{
	buffer->WriteBytes(newData->Bytes());
	return buffer;
}


}	// namespace Serialization
}	// namespace Protocol
}	// namespace Sfs2X


// --- Entities/Data/SFSObject.cpp ---
// ===================================================================
//
// Description		
//		Contains the implementation of SFSObject
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================

namespace Sfs2X {
namespace Entities {
namespace Data {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSObject::SFSObject()
{
	dataHolder = std::shared_ptr<map<string, std::shared_ptr<SFSDataWrapper> > >(new map<string, std::shared_ptr<SFSDataWrapper> >());
	serializer = DefaultSFSDataSerializer::Instance();
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
SFSObject::~SFSObject()
{
	dataHolder->clear();
	dataHolder = std::shared_ptr<map<string, std::shared_ptr<SFSDataWrapper> > >();
}

// -------------------------------------------------------------------
// NewFromObject
// -------------------------------------------------------------------
std::shared_ptr<SFSObject> SFSObject::NewFromObject(std::shared_ptr<void> o)
{
	throw std::runtime_error("Not implemented"); 
}


// -------------------------------------------------------------------
// NewFromBinaryData
// -------------------------------------------------------------------
std::shared_ptr<SFSObject> SFSObject::NewFromBinaryData(std::shared_ptr<ByteArray> ba)
{
	return (std::static_pointer_cast<SFSObject>)(DefaultSFSDataSerializer::Instance()->Binary2Object(ba));
}

// -------------------------------------------------------------------
// NewInstance
// -------------------------------------------------------------------
std::shared_ptr<SFSObject> SFSObject::NewInstance()
{
	std::shared_ptr<SFSObject> returned (new SFSObject());
	return returned;
}

// -------------------------------------------------------------------
// Dump
// -------------------------------------------------------------------
std::shared_ptr<string> SFSObject::Dump()
{
	std::shared_ptr<string> strDump (new string());
	strDump->append(1, DefaultObjectDumpFormatter::TOKEN_INDENT_OPEN);
	std::shared_ptr<SFSDataWrapper> wrapper;

	long int type;

	map<string, std::shared_ptr<SFSDataWrapper> >::iterator iterator;
	for(iterator = dataHolder->begin(); iterator != dataHolder->end(); ++iterator)
	{
		wrapper = iterator->second;
		string key = iterator->first;
		type = wrapper->Type();

		strDump->append("(");
		
		switch (type)
		{
		case SFSDATATYPE_NULL: strDump->append("null"); break;
		case SFSDATATYPE_BOOL: strDump->append("bool"); break;
		case SFSDATATYPE_BYTE: strDump->append("byte"); break;
		case SFSDATATYPE_SHORT: strDump->append("short"); break;
		case SFSDATATYPE_INT: strDump->append("int"); break;
		case SFSDATATYPE_LONG: strDump->append("long"); break;
		case SFSDATATYPE_FLOAT: strDump->append("float"); break;
		case SFSDATATYPE_DOUBLE: strDump->append("double"); break;
		case SFSDATATYPE_UTF_STRING: strDump->append("utf_string"); break;
		case SFSDATATYPE_BOOL_ARRAY: strDump->append("bool_array"); break;
		case SFSDATATYPE_BYTE_ARRAY: strDump->append("byte_array"); break;
		case SFSDATATYPE_SHORT_ARRAY: strDump->append("short_array"); break;
		case SFSDATATYPE_INT_ARRAY: strDump->append("int_array"); break;
		case SFSDATATYPE_LONG_ARRAY: strDump->append("long_array"); break;
		case SFSDATATYPE_FLOAT_ARRAY: strDump->append("float_array"); break;
		case SFSDATATYPE_DOUBLE_ARRAY: strDump->append("double_array"); break;
		case SFSDATATYPE_UTF_STRING_ARRAY: strDump->append("utf_string_array"); break;
		case SFSDATATYPE_SFS_ARRAY: strDump->append("sfs_array"); break;
		case SFSDATATYPE_SFS_OBJECT: strDump->append("sfs_object"); break;
		case SFSDATATYPE_CLASS: strDump->append("class"); break;
		}

		strDump->append(")");

		strDump->append(" ");
		strDump->append(key);
		strDump->append(": ");

		switch (type)
		{
		case SFSDATATYPE_NULL: break;
		case SFSDATATYPE_BOOL: 
			{
				std::shared_ptr<string> temporaryString (new string());
		
				std::shared_ptr<string> format (new string("[%d]"));
				StringFormatter<bool> (temporaryString, format, *((bool*)(wrapper->Data().get())));

				strDump->append(*temporaryString);

				break;
			}
		case SFSDATATYPE_BYTE:
			{
				std::shared_ptr<string> temporaryString (new string());
		
				std::shared_ptr<string> format (new string("[%d]"));
				StringFormatter<unsigned char> (temporaryString, format, *((unsigned char*)wrapper->Data().get()));

				strDump->append(*temporaryString);

				break;
			}
		case SFSDATATYPE_SHORT: 
			{
				std::shared_ptr<string> temporaryString (new string());
		
				std::shared_ptr<string> format (new string("[%d]"));
				StringFormatter<short int> (temporaryString, format, *((short int*)wrapper->Data().get()));

				strDump->append(*temporaryString);

				break;
			}
		case SFSDATATYPE_INT: 
			{
				std::shared_ptr<string> temporaryString (new string());
		
				std::shared_ptr<string> format (new string("[%ld]"));
				StringFormatter<long int> (temporaryString, format, *((long int*)wrapper->Data().get()));

				strDump->append(*temporaryString);

				break;
			}
		case SFSDATATYPE_LONG: 
			{
				std::shared_ptr<string> temporaryString (new string());
		
				std::shared_ptr<string> format (new string("[%ld]"));
				StringFormatter<long long> (temporaryString, format, *((long long*)wrapper->Data().get()));

				strDump->append(*temporaryString);

				break;
			}
		case SFSDATATYPE_FLOAT: 
			{
				std::shared_ptr<string> temporaryString (new string());
		
				std::shared_ptr<string> format (new string("[%f]"));
				StringFormatter<float> (temporaryString, format, *((float*)wrapper->Data().get()));

				strDump->append(*temporaryString);

				break;
			}
		case SFSDATATYPE_DOUBLE:
			{
				std::shared_ptr<string> temporaryString (new string());
		
				std::shared_ptr<string> format (new string("[%f]"));
				StringFormatter<double> (temporaryString, format, *((double*)wrapper->Data().get()));

				strDump->append(*temporaryString);

				break;
			}
		case SFSDATATYPE_UTF_STRING: 
			{
				strDump->append("[");
				strDump->append(*((string*)wrapper->Data().get()));
				strDump->append("]");

				break;
			}
		case SFSDATATYPE_BOOL_ARRAY: 
			{
				strDump->append("[");

				vector<bool>::iterator iteratorWrapperData;
				for(iteratorWrapperData = ((vector<bool>*)wrapper->Data().get())->begin(); iteratorWrapperData != ((vector<bool>*)wrapper->Data().get())->end(); ++iteratorWrapperData)
				{
					std::shared_ptr<string> temporaryString (new string());
		
					std::shared_ptr<string> format (new string("[%d]"));
					StringFormatter<bool> (temporaryString, format, *iteratorWrapperData);

					strDump->append(*temporaryString);
				}

				strDump->append("]");

				break;
			}
		case SFSDATATYPE_BYTE_ARRAY: 
			{
				strDump->append("[");

				vector<unsigned char>::iterator iteratorWrapperData;
				for(iteratorWrapperData = ((vector<unsigned char>*)(((ByteArray*)wrapper->Data().get())->Bytes().get()))->begin(); iteratorWrapperData != ((vector<unsigned char>*)(((ByteArray*)wrapper->Data().get())->Bytes().get()))->end(); ++iteratorWrapperData)
				{
					std::shared_ptr<string> temporaryString (new string());
		
					std::shared_ptr<string> format (new string("[%d]"));
					StringFormatter<unsigned char> (temporaryString, format, *iteratorWrapperData);

					strDump->append(*temporaryString);
				}

				strDump->append("]");

				break;
			}
		case SFSDATATYPE_SHORT_ARRAY:
			{
				strDump->append("[");

				vector<short int>::iterator iteratorWrapperData;
				for(iteratorWrapperData = ((vector<short int>*)wrapper->Data().get())->begin(); iteratorWrapperData != ((vector<short int>*)wrapper->Data().get())->end(); ++iteratorWrapperData)
				{
					std::shared_ptr<string> temporaryString (new string());
		
					std::shared_ptr<string> format (new string("[%d]"));
					StringFormatter<short int> (temporaryString, format, *iteratorWrapperData);

					strDump->append(*temporaryString);
				}

				strDump->append("]");

				break;
			}

		case SFSDATATYPE_INT_ARRAY:
			{
				strDump->append("[");

				vector<long int>::iterator iteratorWrapperData;
				for(iteratorWrapperData = ((vector<long int>*)wrapper->Data().get())->begin(); iteratorWrapperData != ((vector<long int>*)wrapper->Data().get())->end(); ++iteratorWrapperData)
				{
					std::shared_ptr<string> temporaryString (new string());
		
					std::shared_ptr<string> format (new string("[%ld]"));
					StringFormatter<long int> (temporaryString, format, *iteratorWrapperData);

					strDump->append(*temporaryString);
				}

				strDump->append("]");

				break;
			}

		case SFSDATATYPE_LONG_ARRAY: 
			{
				strDump->append("[");

				vector<long long>::iterator iteratorWrapperData;
				for(iteratorWrapperData = ((vector<long long>*)wrapper->Data().get())->begin(); iteratorWrapperData != ((vector<long long>*)wrapper->Data().get())->end(); ++iteratorWrapperData)
				{
					std::shared_ptr<string> temporaryString (new string());
		
					std::shared_ptr<string> format (new string("[%lld]"));
					StringFormatter<long long> (temporaryString, format, *iteratorWrapperData);

					strDump->append(*temporaryString);
				}

				strDump->append("]");

				break;
			}
		case SFSDATATYPE_FLOAT_ARRAY: 
			{
				strDump->append("[");

				vector<float>::iterator iteratorWrapperData;
				for(iteratorWrapperData = ((vector<float>*)wrapper->Data().get())->begin(); iteratorWrapperData != ((vector<float>*)wrapper->Data().get())->end(); ++iteratorWrapperData)
				{
					std::shared_ptr<string> temporaryString (new string());
		
					std::shared_ptr<string> format (new string("[%f]"));
					StringFormatter<float> (temporaryString, format, *iteratorWrapperData);

					strDump->append(*temporaryString);
				}

				strDump->append("]");

				break;
			}
		case SFSDATATYPE_DOUBLE_ARRAY:
			{
				strDump->append("[");

				vector<double>::iterator iteratorWrapperData;
				for(iteratorWrapperData = ((vector<double>*)wrapper->Data().get())->begin(); iteratorWrapperData != ((vector<double>*)wrapper->Data().get())->end(); ++iteratorWrapperData)
				{
					std::shared_ptr<string> temporaryString (new string());
		
					std::shared_ptr<string> format (new string("[%f]"));
					StringFormatter<double> (temporaryString, format, *iteratorWrapperData);

					strDump->append(*temporaryString);
				}

				strDump->append("]");

				break;
			}
		case SFSDATATYPE_UTF_STRING_ARRAY: 
			{
				strDump->append("[");

				vector<string>::iterator iteratorWrapperData;
				for(iteratorWrapperData = ((vector<string>*)wrapper->Data().get())->begin(); iteratorWrapperData != ((vector<string>*)wrapper->Data().get())->end(); ++iteratorWrapperData)
				{
					std::shared_ptr<string> temporaryString (new string());
		
					std::shared_ptr<string> format (new string("[%s]"));
					StringFormatter<const char*> (temporaryString, format, iteratorWrapperData->c_str());

					strDump->append(*temporaryString);
				}

				strDump->append("]");

				break;
			}
		case SFSDATATYPE_SFS_ARRAY: strDump->append(*(((SFSArray*)wrapper->Data().get())->GetDump(false))); break;
		case SFSDATATYPE_SFS_OBJECT: strDump->append(*(((SFSObject*)wrapper->Data().get())->GetDump(false))); break;
		case SFSDATATYPE_CLASS:  break;
		}

		strDump->append(1, DefaultObjectDumpFormatter::TOKEN_DIVIDER);
	}

	// We do this only if the object is not empty
	if (Size() > 0) 
	{
		strDump = std::shared_ptr<string>(new string(strDump->substr(0, strDump->size() - 1)));
	}

	strDump->append(1, DefaultObjectDumpFormatter::TOKEN_INDENT_CLOSE);

	return strDump;
}

// Type getters
// Raw

// -------------------------------------------------------------------
// GetData
// -------------------------------------------------------------------
std::shared_ptr<SFSDataWrapper> SFSObject::GetData(string key) 
{
	return dataHolder->at(key);
}

// -------------------------------------------------------------------
// GetData
// -------------------------------------------------------------------
std::shared_ptr<SFSDataWrapper> SFSObject::GetData(std::shared_ptr<string> key) 
{
	return GetData(*key);
}

// -------------------------------------------------------------------
// GetBool
// -------------------------------------------------------------------
std::shared_ptr<bool> SFSObject::GetBool(string key)
{
	map<string, std::shared_ptr<SFSDataWrapper> >::iterator iterator;
	iterator = dataHolder->find(key);
	if (iterator == dataHolder->end())
	{
		return std::shared_ptr<bool>(new bool());
	}

	return (std::static_pointer_cast<bool>)(((*iterator).second)->Data());
}

// -------------------------------------------------------------------
// GetBool
// -------------------------------------------------------------------
std::shared_ptr<bool> SFSObject::GetBool(std::shared_ptr<string> key) 
{
	return GetBool(*key);
}

// -------------------------------------------------------------------
// GetByte
// -------------------------------------------------------------------
std::shared_ptr<unsigned char> SFSObject::GetByte(string key)
{
	map<string, std::shared_ptr<SFSDataWrapper> >::iterator iterator;
	iterator = dataHolder->find(key);
	if (iterator == dataHolder->end())
	{
		return std::shared_ptr<unsigned char>(new unsigned char());
	}

	return (std::static_pointer_cast<unsigned char>)(((*iterator).second)->Data());
}

// -------------------------------------------------------------------
// GetByte
// -------------------------------------------------------------------
std::shared_ptr<unsigned char> SFSObject::GetByte(std::shared_ptr<string> key) 
{
	return GetByte(*key);
}

// -------------------------------------------------------------------
// GetShort
// -------------------------------------------------------------------
std::shared_ptr<short int> SFSObject::GetShort(string key)
{
	map<string, std::shared_ptr<SFSDataWrapper> >::iterator iterator;
	iterator = dataHolder->find(key);
	if (iterator == dataHolder->end())
	{
		return std::shared_ptr<short int>(new short int());
	}

	return (std::static_pointer_cast<short int>)(((*iterator).second)->Data());
}

// -------------------------------------------------------------------
// GetShort
// -------------------------------------------------------------------
std::shared_ptr<short int> SFSObject::GetShort(std::shared_ptr<string> key) 
{
	return GetShort(*key);
}

// -------------------------------------------------------------------
// GetInt
// -------------------------------------------------------------------
std::shared_ptr<long int> SFSObject::GetInt(string key)
{
	map<string, std::shared_ptr<SFSDataWrapper> >::iterator iterator;
	iterator = dataHolder->find(key);
	if (iterator == dataHolder->end())
	{
		return std::shared_ptr<long int>(new long int());
	}

	return (std::static_pointer_cast<long int>)(((*iterator).second)->Data());
}

// -------------------------------------------------------------------
// GetInt
// -------------------------------------------------------------------
std::shared_ptr<long int> SFSObject::GetInt(std::shared_ptr<string> key) 
{
	return GetInt(*key);
}

// -------------------------------------------------------------------
// GetLong
// -------------------------------------------------------------------
std::shared_ptr<long long> SFSObject::GetLong(string key)
{
	map<string, std::shared_ptr<SFSDataWrapper> >::iterator iterator;
	iterator = dataHolder->find(key);
	if (iterator == dataHolder->end())
	{
		return std::shared_ptr<long long>(new long long());
	}

	return (std::static_pointer_cast<long long>)(((*iterator).second)->Data());
}

// -------------------------------------------------------------------
// GetLong
// -------------------------------------------------------------------
std::shared_ptr<long long> SFSObject::GetLong(std::shared_ptr<string> key) 
{
	return GetLong(*key);
}

// -------------------------------------------------------------------
// GetFloat
// -------------------------------------------------------------------
std::shared_ptr<float> SFSObject::GetFloat(string key)
{
	map<string, std::shared_ptr<SFSDataWrapper> >::iterator iterator;
	iterator = dataHolder->find(key);
	if (iterator == dataHolder->end())
	{
		return std::shared_ptr<float>(new float());
	}

	return (std::static_pointer_cast<float>)(((*iterator).second)->Data());
}

// -------------------------------------------------------------------
// GetFloat
// -------------------------------------------------------------------
std::shared_ptr<float> SFSObject::GetFloat(std::shared_ptr<string> key) 
{
	return GetFloat(*key);
}

// -------------------------------------------------------------------
// GetDouble
// -------------------------------------------------------------------
std::shared_ptr<double> SFSObject::GetDouble(string key)
{
	map<string, std::shared_ptr<SFSDataWrapper> >::iterator iterator;
	iterator = dataHolder->find(key);
	if (iterator == dataHolder->end())
	{
		return std::shared_ptr<double>(new double());
	}

	return (std::static_pointer_cast<double>)(((*iterator).second)->Data());
}

// -------------------------------------------------------------------
// GetDouble
// -------------------------------------------------------------------
std::shared_ptr<double> SFSObject::GetDouble(std::shared_ptr<string> key) 
{
	return GetDouble(*key);
}

// -------------------------------------------------------------------
// GetUtfString
// -------------------------------------------------------------------
std::shared_ptr<string> SFSObject::GetUtfString(string key)
{
	map<string, std::shared_ptr<SFSDataWrapper> >::iterator iterator;
	iterator = dataHolder->find(key);
	if (iterator == dataHolder->end())
	{
		return std::shared_ptr<string>();
	}

	return (std::static_pointer_cast<string>)(((*iterator).second)->Data());
}

// -------------------------------------------------------------------
// GetUtfString
// -------------------------------------------------------------------
std::shared_ptr<string> SFSObject::GetUtfString(std::shared_ptr<string> key) 
{
	return GetUtfString(*key);
}

// -------------------------------------------------------------------
// GetText
// -------------------------------------------------------------------
std::shared_ptr<string> SFSObject::GetText(string key)
{
	map<string, std::shared_ptr<SFSDataWrapper> >::iterator iterator;
	iterator = dataHolder->find(key);
	if (iterator == dataHolder->end())
	{
		return std::shared_ptr<string>();
	}

	return (std::static_pointer_cast<string>)(((*iterator).second)->Data());
}

// -------------------------------------------------------------------
// GetText
// -------------------------------------------------------------------
std::shared_ptr<string> SFSObject::GetText(std::shared_ptr<string> key)
{
	return GetText(*key);
}

// -------------------------------------------------------------------
// GetArray
// -------------------------------------------------------------------
std::shared_ptr<vector<unsigned char> > SFSObject::GetArray(string key)
{
	map<string, std::shared_ptr<SFSDataWrapper> >::iterator iterator;
	iterator = dataHolder->find(key);
	if (iterator == dataHolder->end())
	{
		return std::shared_ptr<vector<unsigned char> >();
	}

	return (std::static_pointer_cast<vector<unsigned char> >)(((*iterator).second)->Data());
}

// -------------------------------------------------------------------
// GetArray
// -------------------------------------------------------------------
std::shared_ptr<vector<unsigned char> > SFSObject::GetArray(std::shared_ptr<string> key) 
{
	return GetArray(*key);
}

// Arrays

// -------------------------------------------------------------------
// GetBoolArray
// -------------------------------------------------------------------
std::shared_ptr<vector<bool> > SFSObject::GetBoolArray(string key)
{
	map<string, std::shared_ptr<SFSDataWrapper> >::iterator iterator;
	iterator = dataHolder->find(key);
	if (iterator == dataHolder->end())
	{
		return std::shared_ptr<vector<bool> >();
	}

	return (std::static_pointer_cast<vector<bool> >)(((*iterator).second)->Data());
}

// -------------------------------------------------------------------
// GetBoolArray
// -------------------------------------------------------------------
std::shared_ptr<vector<bool> > SFSObject::GetBoolArray(std::shared_ptr<string> key) 
{
	return GetBoolArray(*key);
}

// -------------------------------------------------------------------
// GetByteArray
// -------------------------------------------------------------------
std::shared_ptr<ByteArray> SFSObject::GetByteArray(string key)
{
	map<string, std::shared_ptr<SFSDataWrapper> >::iterator iterator;
	iterator = dataHolder->find(key);
	if (iterator == dataHolder->end())
	{
		return std::shared_ptr<ByteArray>();
	}

	return (std::static_pointer_cast<ByteArray>)(((*iterator).second)->Data());
}

// -------------------------------------------------------------------
// GetByteArray
// -------------------------------------------------------------------
std::shared_ptr<ByteArray> SFSObject::GetByteArray(std::shared_ptr<string> key) 
{
	return GetByteArray(*key);
}

// -------------------------------------------------------------------
// GetShortArray
// -------------------------------------------------------------------
std::shared_ptr<vector<short int> > SFSObject::GetShortArray(string key)
{
	map<string, std::shared_ptr<SFSDataWrapper> >::iterator iterator;
	iterator = dataHolder->find(key);
	if (iterator == dataHolder->end())
	{
		return std::shared_ptr<vector<short int> >();
	}

	return (std::static_pointer_cast<vector<short int> >)(((*iterator).second)->Data());
}

// -------------------------------------------------------------------
// GetShortArray
// -------------------------------------------------------------------
std::shared_ptr<vector<short int> > SFSObject::GetShortArray(std::shared_ptr<string> key) 
{
	return GetShortArray(*key);
}

// -------------------------------------------------------------------
// GetIntArray
// -------------------------------------------------------------------
std::shared_ptr<vector<long int> > SFSObject::GetIntArray(string key)
{
	map<string, std::shared_ptr<SFSDataWrapper> >::iterator iterator;
	iterator = dataHolder->find(key);
	if (iterator == dataHolder->end())
	{
		return std::shared_ptr<vector<long int> >();
	}
	
	return (std::static_pointer_cast<vector<long int> >)(((*iterator).second)->Data());
}

// -------------------------------------------------------------------
// GetIntArray
// -------------------------------------------------------------------
std::shared_ptr<vector<long int> > SFSObject::GetIntArray(std::shared_ptr<string> key) 
{
	return GetIntArray(*key);
}

// -------------------------------------------------------------------
// GetLongArray
// -------------------------------------------------------------------
std::shared_ptr<vector<long long> > SFSObject::GetLongArray(string key)
{
	map<string, std::shared_ptr<SFSDataWrapper> >::iterator iterator;
	iterator = dataHolder->find(key);
	if (iterator == dataHolder->end())
	{
		return std::shared_ptr<vector<long long> >();
	}

	return (std::static_pointer_cast<vector<long long> >)(((*iterator).second)->Data());
}

// -------------------------------------------------------------------
// GetLongArray
// -------------------------------------------------------------------
std::shared_ptr<vector<long long> > SFSObject::GetLongArray(std::shared_ptr<string> key) 
{
	return GetLongArray(*key);
}

// -------------------------------------------------------------------
// GetFloatArray
// -------------------------------------------------------------------
std::shared_ptr<vector<float> > SFSObject::GetFloatArray(string key)
{
	map<string, std::shared_ptr<SFSDataWrapper> >::iterator iterator;
	iterator = dataHolder->find(key);
	if (iterator == dataHolder->end())
	{
		return std::shared_ptr<vector<float> >();
	}

	return (std::static_pointer_cast<vector<float> >)(((*iterator).second)->Data());
}

// -------------------------------------------------------------------
// GetFloatArray
// -------------------------------------------------------------------
std::shared_ptr<vector<float> > SFSObject::GetFloatArray(std::shared_ptr<string> key) 
{
	return GetFloatArray(*key);
}

// -------------------------------------------------------------------
// GetDoubleArray
// -------------------------------------------------------------------
std::shared_ptr<vector<double> > SFSObject::GetDoubleArray(string key)
{
	map<string, std::shared_ptr<SFSDataWrapper> >::iterator iterator;
	iterator = dataHolder->find(key);
	if (iterator == dataHolder->end())
	{
		return std::shared_ptr<vector<double> >();
	}

	return (std::static_pointer_cast<vector<double> >)(((*iterator).second)->Data());
}

// -------------------------------------------------------------------
// GetDoubleArray
// -------------------------------------------------------------------
std::shared_ptr<vector<double> > SFSObject::GetDoubleArray(std::shared_ptr<string> key) 
{
	return GetDoubleArray(*key);
}

// -------------------------------------------------------------------
// GetUtfStringArray
// -------------------------------------------------------------------
std::shared_ptr<vector<string> > SFSObject::GetUtfStringArray(string key)
{
	map<string, std::shared_ptr<SFSDataWrapper> >::iterator iterator;
	iterator = dataHolder->find(key);
	if (iterator == dataHolder->end())
	{
		return std::shared_ptr<vector<string> >();
	}

	return (std::static_pointer_cast<vector<string> >)(((*iterator).second)->Data());
}

// -------------------------------------------------------------------
// GetUtfStringArray
// -------------------------------------------------------------------
std::shared_ptr<vector<string> > SFSObject::GetUtfStringArray(std::shared_ptr<string> key) 
{
	return GetUtfStringArray(*key);
}

// -------------------------------------------------------------------
// GetSFSArray
// -------------------------------------------------------------------
std::shared_ptr<ISFSArray> SFSObject::GetSFSArray(string key)
{
	map<string, std::shared_ptr<SFSDataWrapper> >::iterator iterator;
	iterator = dataHolder->find(key);
	if (iterator == dataHolder->end())
	{
		return std::shared_ptr<ISFSArray>();
	}

	return (std::static_pointer_cast<ISFSArray>)((*iterator).second->Data());
}

// -------------------------------------------------------------------
// GetSFSArray
// -------------------------------------------------------------------
std::shared_ptr<ISFSArray> SFSObject::GetSFSArray(std::shared_ptr<string> key) 
{
	return GetSFSArray(*key);
}

// -------------------------------------------------------------------
// GetSFSObject
// -------------------------------------------------------------------
std::shared_ptr<ISFSObject> SFSObject::GetSFSObject(string key)
{
	map<string, std::shared_ptr<SFSDataWrapper> >::iterator iterator;
	iterator = dataHolder->find(key);
	if (iterator == dataHolder->end())
	{
		return std::shared_ptr<ISFSObject>();
	}

	return (std::static_pointer_cast<ISFSObject>)((*iterator).second->Data());
}

// -------------------------------------------------------------------
// GetSFSObject
// -------------------------------------------------------------------
std::shared_ptr<ISFSObject> SFSObject::GetSFSObject(std::shared_ptr<string> key) 
{
	return GetSFSObject(*key);
}

// -------------------------------------------------------------------
// PutNull
// -------------------------------------------------------------------
void SFSObject::PutNull(string key)
{
	std::shared_ptr<SFSDataWrapper> wrapper (new SFSDataWrapper(SFSDATATYPE_NULL, std::shared_ptr<void>()));
	dataHolder->insert(pair<string, std::shared_ptr<SFSDataWrapper> >(key, wrapper));
}

// -------------------------------------------------------------------
// PutNull
// -------------------------------------------------------------------
void SFSObject::PutNull(std::shared_ptr<string> key)
{
	PutNull(*key);
}

// -------------------------------------------------------------------
// PutBool
// -------------------------------------------------------------------
void SFSObject::PutBool(string key, std::shared_ptr<bool> val)
{
	std::shared_ptr<SFSDataWrapper> wrapper (new SFSDataWrapper(SFSDATATYPE_BOOL, (std::static_pointer_cast<void>)(val)));
	dataHolder->insert(pair<string, std::shared_ptr<SFSDataWrapper> >(key, wrapper));
}

// -------------------------------------------------------------------
// PutBool
// -------------------------------------------------------------------
void SFSObject::PutBool(std::shared_ptr<string> key, std::shared_ptr<bool> val)
{
	PutBool(*key, val);
}

// -------------------------------------------------------------------
// PutBool
// -------------------------------------------------------------------
void SFSObject::PutBool(string key, bool val)
{
	std::shared_ptr<bool> value (new bool());
	*value = val;
	PutBool(key, value);
}

// -------------------------------------------------------------------
// PutBool
// -------------------------------------------------------------------
void SFSObject::PutBool(std::shared_ptr<string> key, bool val)
{
	PutBool(*key, val);
}

// -------------------------------------------------------------------
// PutByte
// -------------------------------------------------------------------
void SFSObject::PutByte(string key, std::shared_ptr<unsigned char> val)
{
	std::shared_ptr<SFSDataWrapper> wrapper (new SFSDataWrapper(SFSDATATYPE_BYTE, (std::static_pointer_cast<void>)(val)));
	dataHolder->insert(pair<string, std::shared_ptr<SFSDataWrapper> >(key, wrapper));
}

// -------------------------------------------------------------------
// PutByte
// -------------------------------------------------------------------
void SFSObject::PutByte(std::shared_ptr<string> key, std::shared_ptr<unsigned char> val)
{
	PutByte(*key, val);
}

// -------------------------------------------------------------------
// PutByte
// -------------------------------------------------------------------
void SFSObject::PutByte(string key, unsigned char val)
{
	std::shared_ptr<unsigned char> value (new unsigned char());
	*value = val;
	PutByte(key, value);
}

// -------------------------------------------------------------------
// PutByte
// -------------------------------------------------------------------
void SFSObject::PutByte(std::shared_ptr<string> key, unsigned char val)
{
	PutByte(*key, val);
}

// -------------------------------------------------------------------
// PutShort
// -------------------------------------------------------------------
void SFSObject::PutShort(string key, std::shared_ptr<short int> val)
{
	std::shared_ptr<SFSDataWrapper> wrapper (new SFSDataWrapper(SFSDATATYPE_SHORT, (std::static_pointer_cast<void>)(val)));
	dataHolder->insert(pair<string, std::shared_ptr<SFSDataWrapper> >(key, wrapper));
}

// -------------------------------------------------------------------
// PutShort
// -------------------------------------------------------------------
void SFSObject::PutShort(std::shared_ptr<string> key, std::shared_ptr<short int> val)
{
	PutShort(*key, val);
}

// -------------------------------------------------------------------
// PutShort
// -------------------------------------------------------------------
void SFSObject::PutShort(string key, short int val)
{
	std::shared_ptr<short int> value (new short int());
	*value = val;
	PutShort(key, value);
}

// -------------------------------------------------------------------
// PutShort
// -------------------------------------------------------------------
void SFSObject::PutShort(std::shared_ptr<string> key, short int val)
{
	PutShort(*key, val);
}

// -------------------------------------------------------------------
// PutInt
// -------------------------------------------------------------------
void SFSObject::PutInt(string key, std::shared_ptr<long int> val)
{
	std::shared_ptr<SFSDataWrapper> wrapper (new SFSDataWrapper(SFSDATATYPE_INT, (std::static_pointer_cast<void>)(val)));
	dataHolder->insert(pair<string, std::shared_ptr<SFSDataWrapper> >(key, wrapper));
}

// -------------------------------------------------------------------
// PutInt
// -------------------------------------------------------------------
void SFSObject::PutInt(std::shared_ptr<string> key, std::shared_ptr<long int> val)
{
	PutInt(*key, val);
}

// -------------------------------------------------------------------
// PutInt
// -------------------------------------------------------------------
void SFSObject::PutInt(string key, long int val)
{
	std::shared_ptr<long int> value (new long int());
	*value = val;
	PutInt(key, value);
}

// -------------------------------------------------------------------
// PutInt
// -------------------------------------------------------------------
void SFSObject::PutInt(std::shared_ptr<string> key, long int val)
{
	PutInt (*key, val);
}

// -------------------------------------------------------------------
// PutLong
// -------------------------------------------------------------------
void SFSObject::PutLong(string key, std::shared_ptr<long long> val)
{
	std::shared_ptr<SFSDataWrapper> wrapper (new SFSDataWrapper(SFSDATATYPE_LONG, (std::static_pointer_cast<void>)(val)));
	dataHolder->insert(pair<string, std::shared_ptr<SFSDataWrapper> >(key, wrapper));
}

// -------------------------------------------------------------------
// PutLong
// -------------------------------------------------------------------
void SFSObject::PutLong(std::shared_ptr<string> key, std::shared_ptr<long long> val)
{
	PutLong(*key, val);
}

// -------------------------------------------------------------------
// PutLong
// -------------------------------------------------------------------
void SFSObject::PutLong(string key, long long val)
{
	std::shared_ptr<long long> value (new long long());
	*value = val;
	PutLong(key, value);
}

// -------------------------------------------------------------------
// PutLong
// -------------------------------------------------------------------
void SFSObject::PutLong(std::shared_ptr<string> key, long long val)
{
	PutLong(*key, val);
}

// -------------------------------------------------------------------
// PutFloat
// -------------------------------------------------------------------
void SFSObject::PutFloat(string key, std::shared_ptr<float> val)
{
	std::shared_ptr<SFSDataWrapper> wrapper (new SFSDataWrapper(SFSDATATYPE_FLOAT, (std::static_pointer_cast<void>)(val)));
	dataHolder->insert(pair<string, std::shared_ptr<SFSDataWrapper> >(key, wrapper));
}

// -------------------------------------------------------------------
// PutFloat
// -------------------------------------------------------------------
void SFSObject::PutFloat(std::shared_ptr<string> key, std::shared_ptr<float> val)
{
	PutFloat(*key, val);
}

// -------------------------------------------------------------------
// PutFloat
// -------------------------------------------------------------------
void SFSObject::PutFloat(string key, float val)
{
	std::shared_ptr<float> value (new float());
	*value = val;
	PutFloat(key, value);
}

// -------------------------------------------------------------------
// PutFloat
// -------------------------------------------------------------------
void SFSObject::PutFloat(std::shared_ptr<string> key, float val)
{
	PutFloat(*key, val);
}

// -------------------------------------------------------------------
// PutDouble
// -------------------------------------------------------------------
void SFSObject::PutDouble(string key, std::shared_ptr<double> val)
{
	std::shared_ptr<SFSDataWrapper> wrapper (new SFSDataWrapper(SFSDATATYPE_DOUBLE, (std::static_pointer_cast<void>)(val)));
	dataHolder->insert(pair<string, std::shared_ptr<SFSDataWrapper> >(key, wrapper));
}

// -------------------------------------------------------------------
// PutDouble
// -------------------------------------------------------------------
void SFSObject::PutDouble(std::shared_ptr<string> key, std::shared_ptr<double> val)
{
	PutDouble(*key, val);
}

// -------------------------------------------------------------------
// PutDouble
// -------------------------------------------------------------------
void SFSObject::PutDouble(string key, double val)
{
	std::shared_ptr<double> value (new double());
	*value = val;
	PutDouble(key, value);
}

// -------------------------------------------------------------------
// PutDouble
// -------------------------------------------------------------------
void SFSObject::PutDouble(std::shared_ptr<string> key, double val)
{
	PutDouble(*key, val);
}

// -------------------------------------------------------------------
// PutUtfString
// -------------------------------------------------------------------
void SFSObject::PutUtfString(string key, std::shared_ptr<string> val)
{
	std::shared_ptr<SFSDataWrapper> wrapper (new SFSDataWrapper(SFSDATATYPE_UTF_STRING, (std::static_pointer_cast<void>)(val)));
	dataHolder->insert(pair<string, std::shared_ptr<SFSDataWrapper> >(key, wrapper));
}

// -------------------------------------------------------------------
// PutUtfString
// -------------------------------------------------------------------
void SFSObject::PutUtfString(std::shared_ptr<string> key, std::shared_ptr<string> val)
{
	PutUtfString(*key, val);
}

// -------------------------------------------------------------------
// PutUtfString
// -------------------------------------------------------------------
void SFSObject::PutUtfString(string key, string val)
{
	std::shared_ptr<string> value (new string(val));
	PutUtfString(key, value);
}

// -------------------------------------------------------------------
// PutUtfString
// -------------------------------------------------------------------
void SFSObject::PutUtfString(std::shared_ptr<string> key, string val)
{
	PutUtfString(*key, val);
}

// -------------------------------------------------------------------
// PutText
// -------------------------------------------------------------------
void SFSObject::PutText(string key, std::shared_ptr<string> val)
{
	std::shared_ptr<SFSDataWrapper> wrapper(new SFSDataWrapper(SFSDATATYPE_TEXT, (std::static_pointer_cast<void>)(val)));
	dataHolder->insert(pair<string, std::shared_ptr<SFSDataWrapper> >(key, wrapper));
}

// -------------------------------------------------------------------
// PutText
// -------------------------------------------------------------------
void SFSObject::PutText(std::shared_ptr<string> key, std::shared_ptr<string> val)
{
	PutText(*key, val);
}

// -------------------------------------------------------------------
// PutText
// -------------------------------------------------------------------
void SFSObject::PutText(string key, string val)
{
	std::shared_ptr<string> value(new string(val));
	PutText(key, value);
}

// -------------------------------------------------------------------
// PutText
// -------------------------------------------------------------------
void SFSObject::PutText(std::shared_ptr<string> key, string val)
{
	PutText(*key, val);
}

// Arrays

// -------------------------------------------------------------------
// PutBoolArray
// -------------------------------------------------------------------
void SFSObject::PutBoolArray(string key, std::shared_ptr<vector<bool> > val)
{
	std::shared_ptr<SFSDataWrapper> wrapper (new SFSDataWrapper(SFSDATATYPE_BOOL_ARRAY, (std::static_pointer_cast<void>)(val)));
	dataHolder->insert(pair<string, std::shared_ptr<SFSDataWrapper> >(key, wrapper));
}

// -------------------------------------------------------------------
// PutBoolArray
// -------------------------------------------------------------------
void SFSObject::PutBoolArray(std::shared_ptr<string> key, std::shared_ptr<vector<bool> > val)
{
	PutBoolArray(*key, val);
}

// -------------------------------------------------------------------
// PutByteArray
// -------------------------------------------------------------------
void SFSObject::PutByteArray(string key, std::shared_ptr<ByteArray> val)
{
	std::shared_ptr<SFSDataWrapper> wrapper (new SFSDataWrapper(SFSDATATYPE_BYTE_ARRAY, (std::static_pointer_cast<void>)(val)));
	dataHolder->insert(pair<string, std::shared_ptr<SFSDataWrapper> >(key, wrapper));
}

// -------------------------------------------------------------------
// PutByteArray
// -------------------------------------------------------------------
void SFSObject::PutByteArray(std::shared_ptr<string> key, std::shared_ptr<ByteArray> val)
{
	PutByteArray(*key, val);
}

// -------------------------------------------------------------------
// PutShortArray
// -------------------------------------------------------------------
void SFSObject::PutShortArray(string key, std::shared_ptr<vector<short int> > val)
{
	std::shared_ptr<SFSDataWrapper> wrapper (new SFSDataWrapper(SFSDATATYPE_SHORT_ARRAY, (std::static_pointer_cast<void>)(val)));
	dataHolder->insert(pair<string, std::shared_ptr<SFSDataWrapper> >(key, wrapper));
}

// -------------------------------------------------------------------
// PutShortArray
// -------------------------------------------------------------------
void SFSObject::PutShortArray(std::shared_ptr<string> key, std::shared_ptr<vector<short int> > val)
{
	PutShortArray(*key, val);
}

// -------------------------------------------------------------------
// PutIntArray
// -------------------------------------------------------------------
void SFSObject::PutIntArray(string key, std::shared_ptr<vector<long int> > val)
{
	std::shared_ptr<SFSDataWrapper> wrapper (new SFSDataWrapper(SFSDATATYPE_INT_ARRAY, (std::static_pointer_cast<void>)(val)));
	dataHolder->insert(pair<string, std::shared_ptr<SFSDataWrapper> >(key, wrapper));
}

// -------------------------------------------------------------------
// PutIntArray
// -------------------------------------------------------------------
void SFSObject::PutIntArray(std::shared_ptr<string> key, std::shared_ptr<vector<long int> > val)
{
	PutIntArray(*key, val);
}

// -------------------------------------------------------------------
// PutLongArray
// -------------------------------------------------------------------
void SFSObject::PutLongArray(string key, std::shared_ptr<vector<long long> > val)
{
	std::shared_ptr<SFSDataWrapper> wrapper (new SFSDataWrapper(SFSDATATYPE_LONG_ARRAY, (std::static_pointer_cast<void>)(val)));
	dataHolder->insert(pair<string, std::shared_ptr<SFSDataWrapper> >(key, wrapper));
}

// -------------------------------------------------------------------
// PutLongArray
// -------------------------------------------------------------------
void SFSObject::PutLongArray(std::shared_ptr<string> key, std::shared_ptr<vector<long long> > val)
{
	PutLongArray(*key, val);
}

// -------------------------------------------------------------------
// PutFloatArray
// -------------------------------------------------------------------
void SFSObject::PutFloatArray(string key, std::shared_ptr<vector<float> > val)
{
	std::shared_ptr<SFSDataWrapper> wrapper (new SFSDataWrapper(SFSDATATYPE_FLOAT_ARRAY, (std::static_pointer_cast<void>)(val)));
	dataHolder->insert(pair<string, std::shared_ptr<SFSDataWrapper> >(key, wrapper));
}

// -------------------------------------------------------------------
// PutFloatArray
// -------------------------------------------------------------------
void SFSObject::PutFloatArray(std::shared_ptr<string> key, std::shared_ptr<vector<float> > val)
{
	PutFloatArray(*key, val);
}

// -------------------------------------------------------------------
// PutDoubleArray
// -------------------------------------------------------------------
void SFSObject::PutDoubleArray(string key, std::shared_ptr<vector<double> > val)
{
	std::shared_ptr<SFSDataWrapper> wrapper (new SFSDataWrapper(SFSDATATYPE_DOUBLE_ARRAY, (std::static_pointer_cast<void>)(val)));
	dataHolder->insert(pair<string, std::shared_ptr<SFSDataWrapper> >(key, wrapper));
}

// -------------------------------------------------------------------
// PutDoubleArray
// -------------------------------------------------------------------
void SFSObject::PutDoubleArray(std::shared_ptr<string> key, std::shared_ptr<vector<double> > val)
{
	PutDoubleArray(*key, val);
}

// -------------------------------------------------------------------
// PutUtfStringArray
// -------------------------------------------------------------------
void SFSObject::PutUtfStringArray(string key, std::shared_ptr<vector<string> > val)
{
	std::shared_ptr<SFSDataWrapper> wrapper (new SFSDataWrapper(SFSDATATYPE_UTF_STRING_ARRAY, (std::static_pointer_cast<void>)(val)));
	dataHolder->insert(pair<string, std::shared_ptr<SFSDataWrapper> >(key, wrapper));
}

// -------------------------------------------------------------------
// PutUtfStringArray
// -------------------------------------------------------------------
void SFSObject::PutUtfStringArray(std::shared_ptr<string> key, std::shared_ptr<vector<string> > val)
{
	PutUtfStringArray(*key, val);
}

// -------------------------------------------------------------------
// PutSFSArray
// -------------------------------------------------------------------
void SFSObject::PutSFSArray(string key, std::shared_ptr<ISFSArray> val)
{
	std::shared_ptr<SFSDataWrapper> wrapper (new SFSDataWrapper(SFSDATATYPE_SFS_ARRAY, (std::static_pointer_cast<void>)(val)));
	dataHolder->insert(pair<string, std::shared_ptr<SFSDataWrapper> >(key, wrapper));
}

// -------------------------------------------------------------------
// PutSFSArray
// -------------------------------------------------------------------
void SFSObject::PutSFSArray(std::shared_ptr<string> key, std::shared_ptr<ISFSArray> val)
{
	PutSFSArray(*key, val);
}

// -------------------------------------------------------------------
// PutSFSObject
// -------------------------------------------------------------------
void SFSObject::PutSFSObject(string key, std::shared_ptr<ISFSObject> val)
{
	std::shared_ptr<SFSDataWrapper> wrapper (new SFSDataWrapper(SFSDATATYPE_SFS_OBJECT, (std::static_pointer_cast<void>)(val)));
	dataHolder->insert(pair<string, std::shared_ptr<SFSDataWrapper> >(key, wrapper));
}

// -------------------------------------------------------------------
// PutSFSObject
// -------------------------------------------------------------------
void SFSObject::PutSFSObject(std::shared_ptr<string> key, std::shared_ptr<ISFSObject> val)
{
	PutSFSObject(*key, val);
}

// -------------------------------------------------------------------
// Put
// -------------------------------------------------------------------
void SFSObject::Put(string key, std::shared_ptr<SFSDataWrapper> val)
{
	dataHolder->insert(pair<string, std::shared_ptr<SFSDataWrapper> >(key, val));
}

// -------------------------------------------------------------------
// Put
// -------------------------------------------------------------------
void SFSObject::Put(std::shared_ptr<string> key, std::shared_ptr<SFSDataWrapper> val)
{
	Put(*key, val);
}

// -------------------------------------------------------------------
// ContainsKey
// -------------------------------------------------------------------
bool SFSObject::ContainsKey(string key)
{
	map<string, std::shared_ptr<SFSDataWrapper> >::iterator iterator;
	iterator = dataHolder->find(key);
	if (iterator == dataHolder->end())
	{
		return false;
	}

	return true;
}

// -------------------------------------------------------------------
// ContainsKey
// -------------------------------------------------------------------
bool SFSObject::ContainsKey(std::shared_ptr<string> key)
{
	return ContainsKey(*key);
}

// -------------------------------------------------------------------
// GetClass
// -------------------------------------------------------------------
std::shared_ptr<void> SFSObject::GetClass(string key)
{
	if (!ContainsKey(key))
		return NULL;

	std::shared_ptr<SFSDataWrapper> wrapper = dataHolder->at(key);

	if (wrapper->Data() != NULL)
	{
		return wrapper->Data();
	}

	return NULL;
}

// -------------------------------------------------------------------
// GetClass
// -------------------------------------------------------------------
std::shared_ptr<void> SFSObject::GetClass(std::shared_ptr<string> key) 
{
	return GetClass(*key);
}

// -------------------------------------------------------------------
// GetDump
// -------------------------------------------------------------------
std::shared_ptr<string> SFSObject::GetDump(bool format)
{
	if (format == false)
	{
		return Dump();
	}

	return DefaultObjectDumpFormatter::PrettyPrintDump(Dump());
}

// -------------------------------------------------------------------
// GetDump
// -------------------------------------------------------------------
std::shared_ptr<string> SFSObject::GetDump()
{
	return GetDump(true);
}

// -------------------------------------------------------------------
// GetHexDump
// -------------------------------------------------------------------
std::shared_ptr<string> SFSObject::GetHexDump()
{
	return DefaultObjectDumpFormatter::HexDump(this->ToBinary());
}

// -------------------------------------------------------------------
// GetKeys
// -------------------------------------------------------------------
std::shared_ptr<vector<string> > SFSObject::GetKeys()
{
	std::shared_ptr<vector<string> > keyList (new vector<string>());

	map<string, std::shared_ptr<SFSDataWrapper> >::iterator iterator;
	for(iterator = dataHolder->begin(); iterator != dataHolder->end(); ++iterator)
	{
		keyList->push_back(iterator->first);
	}

	return keyList;
}

// -------------------------------------------------------------------
// IsNull
// -------------------------------------------------------------------
bool SFSObject::IsNull(string key)
{
	if (!ContainsKey(key))
		return true;

	std::shared_ptr<SFSDataWrapper> wrapper = dataHolder->at(key);
	return (wrapper->Type() == (int)SFSDataType::SFSDATATYPE_NULL || wrapper->Data() == NULL);
}

// -------------------------------------------------------------------
// IsNull
// -------------------------------------------------------------------
bool SFSObject::IsNull(std::shared_ptr<string> key)
{
	return IsNull(*key);
}

// -------------------------------------------------------------------
// PutClass
// -------------------------------------------------------------------
void SFSObject::PutClass(string key, std::shared_ptr<void> val)
{
	std::shared_ptr<SFSDataWrapper> wrapper (new SFSDataWrapper(SFSDATATYPE_CLASS, val));
	dataHolder->insert(pair<string, std::shared_ptr<SFSDataWrapper> >(key, wrapper));
}

// -------------------------------------------------------------------
// PutClass
// -------------------------------------------------------------------
void SFSObject::PutClass(std::shared_ptr<string> key, std::shared_ptr<void> val)
{
	PutClass(*key, val);
}

// -------------------------------------------------------------------
// RemoveElement
// -------------------------------------------------------------------
void SFSObject::RemoveElement(string key)
{
	map<string, std::shared_ptr<SFSDataWrapper> >::iterator iterator;
	iterator = dataHolder->find(key);
	if (iterator != dataHolder->end())
	{
		dataHolder->erase(iterator);
	}
}

// -------------------------------------------------------------------
// RemoveElement
// -------------------------------------------------------------------
void SFSObject::RemoveElement(std::shared_ptr<string> key)
{
	RemoveElement(*key);
}

// -------------------------------------------------------------------
// Size
// -------------------------------------------------------------------
long int SFSObject::Size()
{
	return (long int)dataHolder->size();
}

// -------------------------------------------------------------------
// ToBinary
// -------------------------------------------------------------------
std::shared_ptr<ByteArray> SFSObject::ToBinary()
{
	return serializer->Object2Binary(shared_from_this());
}

}	// namespace Data
}	// namespace Entities
}	// namespace Sfs2X


// --- Entities/Data/SFSArray.cpp ---
// ===================================================================
//
// Description		
//		Contains the implementation of SFSArray
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================

namespace Sfs2X {
namespace Entities {
namespace Data {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSArray::SFSArray()
{
	dataHolder = std::shared_ptr<vector<std::shared_ptr<SFSDataWrapper> > >(new vector<std::shared_ptr<SFSDataWrapper> >());
	serializer = DefaultSFSDataSerializer::Instance();
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
SFSArray::~SFSArray()
{
	dataHolder->clear();
	dataHolder = std::shared_ptr<vector<std::shared_ptr<SFSDataWrapper> > >();
}

// -------------------------------------------------------------------
// NewFromArray
// -------------------------------------------------------------------
std::shared_ptr<SFSArray> SFSArray::NewFromArray(vector<std::shared_ptr<SFSDataWrapper> > o)
{
	return std::shared_ptr<SFSArray>();
}

// -------------------------------------------------------------------
// NewFromBinaryData
// -------------------------------------------------------------------
std::shared_ptr<SFSArray> SFSArray::NewFromBinaryData(std::shared_ptr<ByteArray> ba)
{
	return (std::static_pointer_cast<SFSArray>)(DefaultSFSDataSerializer::Instance()->Binary2Array(ba));
}

// -------------------------------------------------------------------
// NewInstance
// -------------------------------------------------------------------
std::shared_ptr<SFSArray> SFSArray::NewInstance()
{
	std::shared_ptr<SFSArray> returned (new SFSArray());
	return returned;
}

// -------------------------------------------------------------------
// Contains
// -------------------------------------------------------------------
bool SFSArray::Contains(std::shared_ptr<void> obj)
{

	if ((typeid(obj) == typeid(std::shared_ptr<ISFSArray>)) || (typeid(obj) == typeid(std::shared_ptr<ISFSObject>))) 
	{
		std::shared_ptr<string> message (new string("ISFSArray and ISFSObject are not supported by this method."));
		std::shared_ptr<SFSError> exception (new SFSError(message));
		throw exception;
	}

	for (int j = 0; j < Size(); j++)	
	{
		std::shared_ptr<void> wrappedObj = GetElementAt(j);
				
		if (wrappedObj == obj)
		{
			return true;
		}
	}	
			
	return false;
}

// -------------------------------------------------------------------
// GetWrappedElementAt
// -------------------------------------------------------------------
std::shared_ptr<SFSDataWrapper> SFSArray::GetWrappedElementAt(long int index)
{
	return dataHolder->at(index);
}


// -------------------------------------------------------------------
// GetElementAt
// -------------------------------------------------------------------
std::shared_ptr<void> SFSArray::GetElementAt(long int index)
{
	std::shared_ptr<void> obj = std::shared_ptr<void>();
	//if (index < 0 || dataHolder->size() <= index) return obj;
	if (dataHolder->at(index) != NULL) 
	{
		obj = dataHolder->at(index)->Data();
	}
	
	return obj;
}

// -------------------------------------------------------------------
// RemoveElementAt
// -------------------------------------------------------------------
std::shared_ptr<void> SFSArray::RemoveElementAt(unsigned long int index)
{
	if (index >= dataHolder->size()) return std::shared_ptr<void>();
	std::shared_ptr<SFSDataWrapper> elem = dataHolder->at(index);
	dataHolder->erase (dataHolder->begin() + index);
	return elem->Data();
}

// -------------------------------------------------------------------
// Size
// -------------------------------------------------------------------
long int SFSArray::Size()
{
	return (long int)dataHolder->size();
}

// -------------------------------------------------------------------
// ToBinary
// -------------------------------------------------------------------
std::shared_ptr<ByteArray> SFSArray::ToBinary()
{
	return serializer->Array2Binary(shared_from_this());
}

// -------------------------------------------------------------------
// GetDump
// -------------------------------------------------------------------
std::shared_ptr<string> SFSArray::GetDump()
{
	return GetDump(true);
}

// -------------------------------------------------------------------
// GetDump
// -------------------------------------------------------------------
std::shared_ptr<string> SFSArray::GetDump(bool format)
{
	if (!format) 
	{
		return Dump();
	}		
	else 
	{
		return DefaultObjectDumpFormatter::PrettyPrintDump(Dump());
	}
}

// -------------------------------------------------------------------
// Dump
// -------------------------------------------------------------------
std::shared_ptr<string> SFSArray::Dump()
{
	std::shared_ptr<string> strDump (new string());
	strDump->append(1, DefaultObjectDumpFormatter::TOKEN_INDENT_OPEN);
	std::shared_ptr<SFSDataWrapper> wrapper;

	long int type;

	vector<std::shared_ptr<SFSDataWrapper> >::iterator iterator;
	for(iterator = dataHolder->begin(); iterator != dataHolder->end(); ++iterator)
	{
		wrapper = *iterator;
		type = wrapper->Type();

		switch (type)
		{
		case SFSDATATYPE_NULL: 
			{
				strDump->append("(");
				strDump->append("null");
				strDump->append(") ");

				strDump->append("NULL"); 
				break;
			}
		case SFSDATATYPE_BOOL: 
			{
				strDump->append("(");
				strDump->append("bool");
				strDump->append(") ");

				std::shared_ptr<string> temporaryString (new string());
				std::shared_ptr<string> format (new string("[%d]"));
				StringFormatter<bool> (temporaryString, format, *((std::static_pointer_cast<bool>)(wrapper->Data()).get()));

				strDump->append(*temporaryString);

				break;
			}
		case SFSDATATYPE_BYTE:
			{
				strDump->append("(");
				strDump->append("byte");
				strDump->append(") ");

				std::shared_ptr<string> temporaryString (new string());
				std::shared_ptr<string> format (new string("[%d]"));
				StringFormatter<unsigned char> (temporaryString, format, *((std::static_pointer_cast<unsigned char>)(wrapper->Data()).get()));

				strDump->append(*temporaryString);

				break;
			}
		case SFSDATATYPE_SHORT: 
			{
				strDump->append("(");
				strDump->append("short");
				strDump->append(") ");

				std::shared_ptr<string> temporaryString (new string());
				std::shared_ptr<string> format (new string("[%d]"));
				StringFormatter<short int> (temporaryString, format, *((std::static_pointer_cast<short int>)(wrapper->Data()).get()));

				strDump->append(*temporaryString);

				break;
			}
		case SFSDATATYPE_INT: 
			{
				strDump->append("(");
				strDump->append("int");
				strDump->append(") ");

				std::shared_ptr<string> temporaryString (new string());
				std::shared_ptr<string> format (new string("[%ld]"));
				StringFormatter<long int> (temporaryString, format, *((std::static_pointer_cast<long int>)(wrapper->Data()).get()));

				strDump->append(*temporaryString);

				break;
			}
		case SFSDATATYPE_LONG: 
			{
				strDump->append("(");
				strDump->append("long");
				strDump->append(") ");

				std::shared_ptr<string> temporaryString (new string());
				std::shared_ptr<string> format (new string("[%ld]"));
				StringFormatter<long long> (temporaryString, format, *((std::static_pointer_cast<long long>)(wrapper->Data()).get()));

				strDump->append(*temporaryString);

				break;
			}
		case SFSDATATYPE_FLOAT: 
			{
				strDump->append("(");
				strDump->append("float");
				strDump->append(") ");

				std::shared_ptr<string> temporaryString (new string());
				std::shared_ptr<string> format (new string("[%f]"));
				StringFormatter<float> (temporaryString, format, *((std::static_pointer_cast<float>)(wrapper->Data()).get()));

				strDump->append(*temporaryString);

				break;
			}
		case SFSDATATYPE_DOUBLE:
			{
				strDump->append("(");
				strDump->append("double");
				strDump->append(") ");

				std::shared_ptr<string> temporaryString (new string());
				std::shared_ptr<string> format (new string("[%f]"));
				StringFormatter<double> (temporaryString, format, *((std::static_pointer_cast<double>)(wrapper->Data()).get()));

				strDump->append(*temporaryString);

				break;
			}
		case SFSDATATYPE_UTF_STRING: 
			{
				strDump->append("(");
				strDump->append("utf_string");
				strDump->append(") ");

				strDump->append("[");
				strDump->append(*((std::static_pointer_cast<string>)(wrapper->Data()).get()));
				strDump->append("]");

				break;
			}
		case SFSDATATYPE_BOOL_ARRAY: 
			{
				strDump->append("(");
				strDump->append("bool_array");
				strDump->append(") ");

				strDump->append("[");

				vector<std::shared_ptr<bool> >::iterator iteratorWrapperData;
				for(iteratorWrapperData = ((std::static_pointer_cast<vector<std::shared_ptr<bool> > >)(wrapper->Data()))->begin(); iteratorWrapperData != ((std::static_pointer_cast<vector<std::shared_ptr<bool> > >)(wrapper->Data()))->end(); ++iteratorWrapperData)
				{
					std::shared_ptr<string> temporaryString (new string());
					std::shared_ptr<string> format (new string("[%d]"));
					StringFormatter<bool> (temporaryString, format, *((std::static_pointer_cast<bool>)(*iteratorWrapperData)));

					strDump->append(*temporaryString);
				}

				strDump->append("]");

				break;
			}
		case SFSDATATYPE_BYTE_ARRAY: 
			{
				strDump->append("(");
				strDump->append("byte_array");
				strDump->append(") ");

				strDump->append("[");

				vector<std::shared_ptr<unsigned char> >::iterator iteratorWrapperData;
				for(iteratorWrapperData = ((std::static_pointer_cast<vector<std::shared_ptr<unsigned char> > >)(wrapper->Data()))->begin(); iteratorWrapperData != ((std::static_pointer_cast<vector<std::shared_ptr<unsigned char> > >)(wrapper->Data()))->end(); ++iteratorWrapperData)
				{
					std::shared_ptr<string> temporaryString (new string());
					std::shared_ptr<string> format (new string("[%d]"));
					StringFormatter<unsigned char> (temporaryString, format, *((std::static_pointer_cast<unsigned char>)(*iteratorWrapperData)));

					strDump->append(*temporaryString);
				}

				strDump->append("]");

				break;
			}
		case SFSDATATYPE_SHORT_ARRAY:
			{
				strDump->append("(");
				strDump->append("short_array");
				strDump->append(") ");

				strDump->append("[");

				vector<std::shared_ptr<short int> >::iterator iteratorWrapperData;
				for(iteratorWrapperData = ((std::static_pointer_cast<vector<std::shared_ptr<short int> > >)(wrapper->Data()))->begin(); iteratorWrapperData != ((std::static_pointer_cast<vector<std::shared_ptr<short int> > >)(wrapper->Data()))->end(); ++iteratorWrapperData)
				{
					std::shared_ptr<string> temporaryString (new string());
					std::shared_ptr<string> format (new string("[%d]"));
					StringFormatter<short int> (temporaryString, format, *((std::static_pointer_cast<short int>)(*iteratorWrapperData)));

					strDump->append(*temporaryString);
				}

				strDump->append("]");

				break;
			}
		case SFSDATATYPE_INT_ARRAY:
			{
				strDump->append("(");
				strDump->append("int_array");
				strDump->append(") ");

				strDump->append("[");

				vector<std::shared_ptr<long int> >::iterator iteratorWrapperData;
				for(iteratorWrapperData = ((std::static_pointer_cast<vector<std::shared_ptr<long int> > >)(wrapper->Data()))->begin(); iteratorWrapperData != ((std::static_pointer_cast<vector<std::shared_ptr<long int> > >)(wrapper->Data()))->end(); ++iteratorWrapperData)
				{
					std::shared_ptr<string> temporaryString (new string());
					std::shared_ptr<string> format (new string("[%ld]"));
					StringFormatter<long int> (temporaryString, format, *((std::static_pointer_cast<long int>)(*iteratorWrapperData)));

					strDump->append(*temporaryString);
				}

				strDump->append("]");

				break;
			}
		case SFSDATATYPE_LONG_ARRAY: 
			{
				strDump->append("(");
				strDump->append("long_array");
				strDump->append(") ");

				strDump->append("[");

				vector<std::shared_ptr<long long> >::iterator iteratorWrapperData;
				for(iteratorWrapperData = ((std::static_pointer_cast<vector<std::shared_ptr<long long> > >)(wrapper->Data()))->begin(); iteratorWrapperData != ((std::static_pointer_cast<vector<std::shared_ptr<long long> > >)(wrapper->Data()))->end(); ++iteratorWrapperData)
				{
					std::shared_ptr<string> temporaryString (new string());
					std::shared_ptr<string> format (new string("[%ld]"));
					StringFormatter<long long> (temporaryString, format, *((std::static_pointer_cast<long long>)(*iteratorWrapperData)));

					strDump->append(*temporaryString);
				}

				strDump->append("]");

				break;
			}
		case SFSDATATYPE_FLOAT_ARRAY: 
			{
				strDump->append("(");
				strDump->append("float_array");
				strDump->append(") ");

				strDump->append("[");

				vector<std::shared_ptr<float> >::iterator iteratorWrapperData;
				for(iteratorWrapperData = ((std::static_pointer_cast<vector<std::shared_ptr<float> > >)(wrapper->Data()))->begin(); iteratorWrapperData != ((std::static_pointer_cast<vector<std::shared_ptr<float> > >)(wrapper->Data()))->end(); ++iteratorWrapperData)
				{
					std::shared_ptr<string> temporaryString (new string());
					std::shared_ptr<string> format (new string("[%f]"));
					StringFormatter<float> (temporaryString, format, *((std::static_pointer_cast<float>)(*iteratorWrapperData)));

					strDump->append(*temporaryString);
				}

				strDump->append("]");

				break;
			}
		case SFSDATATYPE_DOUBLE_ARRAY:
			{
				strDump->append("(");
				strDump->append("double_array");
				strDump->append(") ");

				strDump->append("[");

				vector<std::shared_ptr<double> >::iterator iteratorWrapperData;
				for(iteratorWrapperData = ((std::static_pointer_cast<vector<std::shared_ptr<double> > >)(wrapper->Data()))->begin(); iteratorWrapperData != ((std::static_pointer_cast<vector<std::shared_ptr<double> > >)(wrapper->Data()))->end(); ++iteratorWrapperData)
				{
					std::shared_ptr<string> temporaryString (new string());
					std::shared_ptr<string> format (new string("[%f]"));
					StringFormatter<double> (temporaryString, format, *((std::static_pointer_cast<double>)(*iteratorWrapperData)));

					strDump->append(*temporaryString);
				}

				strDump->append("]");

				break;
			}
		case SFSDATATYPE_UTF_STRING_ARRAY: 
			{
				strDump->append("(");
				strDump->append("utf_string_array");
				strDump->append(") ");

				strDump->append("[");

				vector<std::shared_ptr<string> >::iterator iteratorWrapperData;
				for(iteratorWrapperData = ((std::static_pointer_cast<vector<std::shared_ptr<string> > >)(wrapper->Data()))->begin(); iteratorWrapperData != ((std::static_pointer_cast<vector<std::shared_ptr<string> > >)(wrapper->Data()))->end(); ++iteratorWrapperData)
				{
					std::shared_ptr<string> temporaryString (new string());
					std::shared_ptr<string> format (new string("[%s]"));
					StringFormatter<const char*> (temporaryString, format, ((std::static_pointer_cast<string>)(*iteratorWrapperData))->c_str());

					strDump->append(*temporaryString);
				}

				strDump->append("]");

				break;
			}
		case SFSDATATYPE_SFS_ARRAY: 
			{
				strDump->append("(");
				strDump->append("sfs_array");
				strDump->append(") ");

				strDump->append(*(((std::static_pointer_cast<SFSArray>)(wrapper->Data()))->GetDump(false))); 
				break;
			}
		case SFSDATATYPE_SFS_OBJECT: 
			{
				strDump->append("(");
				strDump->append("sfs_object");
				strDump->append(") ");

				strDump->append(*(((std::static_pointer_cast<SFSObject>)(wrapper->Data()))->GetDump(false))); 
				break;
			}
		case SFSDATATYPE_CLASS:  
			{
				strDump->append("(");
				strDump->append("class");
				strDump->append(") ");

				break;
			}
		}

		strDump->append(1, DefaultObjectDumpFormatter::TOKEN_DIVIDER);
	}

	// We do this only if the object is not empty
	if (Size() > 0) 
	{
		strDump = std::shared_ptr<string>(new string(strDump->substr(0, strDump->size() - 1)));
	}

	strDump->append(1, DefaultObjectDumpFormatter::TOKEN_INDENT_CLOSE);

	return strDump;
}

// -------------------------------------------------------------------
// GetHexDump
// -------------------------------------------------------------------
std::shared_ptr<string> SFSArray::GetHexDump()
{
	return DefaultObjectDumpFormatter::HexDump(this->ToBinary());
}

/*
* :::::::::::::::::::::::::::::::::::::::::
* Type setters
* :::::::::::::::::::::::::::::::::::::::::	
*/

void SFSArray::AddNull()
{
	AddObject(std::shared_ptr<void>(), SFSDATATYPE_NULL);
}

void SFSArray::AddBool(std::shared_ptr<bool> val)
{
	AddObject((std::static_pointer_cast<void>)(val), SFSDATATYPE_BOOL);
}

void SFSArray::AddBool(bool val)
{
	std::shared_ptr<bool> value (new bool());
	*value = val;
	AddBool(value);
}

void SFSArray::AddByte(std::shared_ptr<unsigned char> val)
{
	AddObject((std::static_pointer_cast<void>)(val), SFSDATATYPE_BYTE);
}

void SFSArray::AddByte(unsigned char val)
{
	std::shared_ptr<unsigned char> value (new unsigned char());
	*value = val;
	AddByte(value);
}

void SFSArray::AddShort(std::shared_ptr<short int> val)
{
	AddObject((std::static_pointer_cast<void>)(val), SFSDATATYPE_SHORT);
}

void SFSArray::AddShort(short int val)
{
	std::shared_ptr<short int> value (new short int());
	*value = val;
	AddShort(value);
}

void SFSArray::AddInt(std::shared_ptr<long int> val)
{
	AddObject((std::static_pointer_cast<void>)(val), SFSDATATYPE_INT);
}

void SFSArray::AddInt(long int val)
{
	std::shared_ptr<long int> value (new long int());
	*value = val;
	AddInt(value);
}

void SFSArray::AddLong(std::shared_ptr<long long> val)
{
	AddObject((std::static_pointer_cast<void>)(val), SFSDATATYPE_LONG);
}

void SFSArray::AddLong(long long val)
{
	std::shared_ptr<long long> value (new long long());
	*value = val;
	AddLong(value);
}

void SFSArray::AddFloat(std::shared_ptr<float> val)
{
	AddObject((std::static_pointer_cast<void>)(val), SFSDATATYPE_FLOAT);
}

void SFSArray::AddFloat(float val)
{
	std::shared_ptr<float> value (new float());
	*value = val;
	AddFloat(value);
}

void SFSArray::AddDouble(std::shared_ptr<double> val)
{
	AddObject((std::static_pointer_cast<void>)(val), SFSDATATYPE_DOUBLE);
}

void SFSArray::AddDouble(double val)
{
	std::shared_ptr<double> value (new double());
	*value = val;
	AddDouble(value);
}

void SFSArray::AddUtfString(std::shared_ptr<string> val)
{
	AddObject((std::static_pointer_cast<void>)(val), SFSDATATYPE_UTF_STRING);
}

void SFSArray::AddUtfString(string val)
{
	std::shared_ptr<string> value (new string(val));
	AddUtfString(value);
}

void SFSArray::AddText(std::shared_ptr<string> val)
{
	AddObject((std::static_pointer_cast<void>)(val), SFSDATATYPE_TEXT);
}

void SFSArray::AddText(string val)
{
	std::shared_ptr<string> value(new string(val));
	AddText(value);
}

void SFSArray::AddBoolArray(std::shared_ptr<vector<std::shared_ptr<bool> > > val)
{
	AddObject((std::static_pointer_cast<void>)(val), SFSDATATYPE_BOOL_ARRAY);
}

void SFSArray::AddByteArray(std::shared_ptr<ByteArray> val)
{
	AddObject((std::static_pointer_cast<void>)(val), SFSDATATYPE_BYTE_ARRAY);
}

void SFSArray::AddShortArray(std::shared_ptr<vector<std::shared_ptr<short int> > > val)
{
	AddObject((std::static_pointer_cast<void>)(val), SFSDATATYPE_SHORT_ARRAY);
}

void SFSArray::AddIntArray(std::shared_ptr<vector<std::shared_ptr<long int> > > val)
{
	AddObject((std::static_pointer_cast<void>)(val), SFSDATATYPE_INT_ARRAY);
}

void SFSArray::AddLongArray(std::shared_ptr<vector<std::shared_ptr<long long> > > val)
{
	AddObject((std::static_pointer_cast<void>)(val), SFSDATATYPE_LONG_ARRAY);
}
 
void SFSArray::AddFloatArray(std::shared_ptr<vector<std::shared_ptr<float> > > val)
{
	AddObject((std::static_pointer_cast<void>)(val), SFSDATATYPE_FLOAT_ARRAY);
}

void SFSArray::AddDoubleArray(std::shared_ptr<vector<std::shared_ptr<double> > > val)
{
	AddObject((std::static_pointer_cast<void>)(val), SFSDATATYPE_DOUBLE_ARRAY);
}

void SFSArray::AddUtfStringArray(std::shared_ptr<vector<std::shared_ptr<string> > > val)
{
	AddObject((std::static_pointer_cast<void>)(val), SFSDATATYPE_UTF_STRING_ARRAY);
}

void SFSArray::AddSFSArray(std::shared_ptr<ISFSArray> val)
{
	AddObject((std::static_pointer_cast<void>)(val), SFSDATATYPE_SFS_ARRAY);
}
		 
void SFSArray::AddSFSObject(std::shared_ptr<ISFSObject> val)
{
	AddObject((std::static_pointer_cast<void>)(val), SFSDATATYPE_SFS_OBJECT);
}

void SFSArray::AddClass(std::shared_ptr<void> val)
{
	AddObject(val, SFSDATATYPE_CLASS);
}

void SFSArray::Add(std::shared_ptr<SFSDataWrapper> wrappedObject)
{
	dataHolder->push_back(wrappedObject);
}

void SFSArray::AddObject(std::shared_ptr<void> val, SFSDataType tp)
{
	std::shared_ptr<SFSDataWrapper> wrapper (new SFSDataWrapper((long int)tp, val));
	dataHolder->push_back(wrapper);
}

/*
* :::::::::::::::::::::::::::::::::::::::::
* Type getters
* :::::::::::::::::::::::::::::::::::::::::	
*/
bool SFSArray::IsNull(unsigned long int index)
{
	//if (index >= dataHolder->size()) return true;
	std::shared_ptr<SFSDataWrapper> wrapper = dataHolder->at(index);
	return (wrapper->Type() == (long int)SFSDATATYPE_NULL);
}

bool SFSArray::GetBool(unsigned long int index)
{
	//if (index >= dataHolder->size()) return false;
	std::shared_ptr<SFSDataWrapper> wrapper = dataHolder->at(index);
	return (bool)(*((std::static_pointer_cast<bool>)(wrapper->Data())));
}

unsigned char SFSArray::GetByte(unsigned long int index)
{
	//if (index >= dataHolder->size()) return 0;
	std::shared_ptr<SFSDataWrapper> wrapper = dataHolder->at(index);
	return (unsigned char)(*((std::static_pointer_cast<unsigned char>)(wrapper->Data())));
}

short int SFSArray::GetShort(unsigned long int index)
{
	//if (index >= dataHolder->size()) return 0;
	std::shared_ptr<SFSDataWrapper> wrapper = dataHolder->at(index);
	return (short int)(*((std::static_pointer_cast<short int>)(wrapper->Data())));
}

long int SFSArray::GetInt(unsigned long int index)
{
	//if (index >= dataHolder->size()) return 0;
	std::shared_ptr<SFSDataWrapper> wrapper = dataHolder->at(index);
	return (long int)(*((std::static_pointer_cast<long int>)(wrapper->Data())));
}

long long SFSArray::GetLong(unsigned long int index)
{
	//if (index >= dataHolder->size()) return 0;
	std::shared_ptr<SFSDataWrapper> wrapper = dataHolder->at(index);
	return (long long)(*((std::static_pointer_cast<long long>)(wrapper->Data())));
}

float SFSArray::GetFloat(unsigned long int index)
{
	//if (index >= dataHolder->size()) return 0;
	std::shared_ptr<SFSDataWrapper> wrapper = dataHolder->at(index);
	return (float)(*((std::static_pointer_cast<float>)(wrapper->Data())));
}

double SFSArray::GetDouble(unsigned long int index)
{
	//if (index >= dataHolder->size()) return 0;
	std::shared_ptr<SFSDataWrapper> wrapper = dataHolder->at(index);
	return (double)(*((std::static_pointer_cast<double>)(wrapper->Data())));
}

std::shared_ptr<string> SFSArray::GetUtfString(unsigned long int index)
{
	//if (index >= dataHolder->size()) return std::shared_ptr<string>(new string());
	std::shared_ptr<SFSDataWrapper> wrapper = dataHolder->at(index);
	return (std::static_pointer_cast<string>)(wrapper->Data());
}

std::shared_ptr<string> SFSArray::GetText(unsigned long int index)
{
	//if (index >= dataHolder->size()) return std::shared_ptr<string>(new string());
	std::shared_ptr<SFSDataWrapper> wrapper = dataHolder->at(index);
	return (std::static_pointer_cast<string>)(wrapper->Data());
}

std::shared_ptr<vector<std::shared_ptr<void> > > SFSArray::GetArray(unsigned long int index)
{
	//if (index >= dataHolder->size()) return std::shared_ptr<vector<std::shared_ptr<void> > >();
	std::shared_ptr<SFSDataWrapper> wrapper = dataHolder->at(index);
	return (std::static_pointer_cast<vector<std::shared_ptr<void> > >)(wrapper->Data());
}

std::shared_ptr<vector<bool> > SFSArray::GetBoolArray(unsigned long int index)
{
	//if (index >= dataHolder->size()) return std::shared_ptr<vector<bool> >();
	std::shared_ptr<SFSDataWrapper> wrapper = dataHolder->at(index);
	return (std::static_pointer_cast<vector<bool> >)(wrapper->Data());
}

std::shared_ptr<ByteArray> SFSArray::GetByteArray(unsigned long int index)
{
	//if (index >= dataHolder->size()) return std::shared_ptr<ByteArray>();
	std::shared_ptr<SFSDataWrapper> wrapper = dataHolder->at(index);
	return (std::static_pointer_cast<ByteArray>)(wrapper->Data());
}

std::shared_ptr<vector<short int> > SFSArray::GetShortArray(unsigned long int index)
{
	//if (index >= dataHolder->size()) return std::shared_ptr<vector<short int> >();
	std::shared_ptr<SFSDataWrapper> wrapper = dataHolder->at(index);
	return (std::static_pointer_cast<vector<short int> >)(wrapper->Data());
}

std::shared_ptr<vector<long int> > SFSArray::GetIntArray(unsigned long int index)
{
	//if (index >= dataHolder->size()) return std::shared_ptr<vector<long int> >();
	std::shared_ptr<SFSDataWrapper> wrapper = dataHolder->at(index);
	return (std::static_pointer_cast<vector<long int> >)(wrapper->Data());
}

std::shared_ptr<vector<long long> > SFSArray::GetLongArray(unsigned long int index)
{
	//if (index >= dataHolder->size()) return std::shared_ptr<vector<long long> >();
	std::shared_ptr<SFSDataWrapper> wrapper = dataHolder->at(index);
	return (std::static_pointer_cast<vector<long long> >)(wrapper->Data());
}

std::shared_ptr<vector<float> > SFSArray::GetFloatArray(unsigned long int index)
{
	//if (index >= dataHolder->size()) return std::shared_ptr<vector<float> >();
	std::shared_ptr<SFSDataWrapper> wrapper = dataHolder->at(index);
	return (std::static_pointer_cast<vector<float> >)(wrapper->Data());
}

std::shared_ptr<vector<double> > SFSArray::GetDoubleArray(unsigned long int index)
{
	//if (index >= dataHolder->size()) return std::shared_ptr<vector<double> >();
	std::shared_ptr<SFSDataWrapper> wrapper = dataHolder->at(index);
	return (std::static_pointer_cast<vector<double> >)(wrapper->Data());
}

std::shared_ptr<vector<string> > SFSArray::GetUtfStringArray(unsigned long int index)
{
	//if (index >= dataHolder->size()) return std::shared_ptr<vector<string> >();
	std::shared_ptr<SFSDataWrapper> wrapper = dataHolder->at(index);
	return (std::static_pointer_cast<vector<string> >)(wrapper->Data());
}

std::shared_ptr<ISFSArray> SFSArray::GetSFSArray(unsigned long int index)
{
	//if (index >= dataHolder->size()) return std::shared_ptr<ISFSArray>();
	std::shared_ptr<SFSDataWrapper> wrapper = dataHolder->at(index);
	return (std::static_pointer_cast<ISFSArray>)(wrapper->Data());
}

std::shared_ptr<void> SFSArray::GetClass(unsigned long int index)
{
	//if (index >= dataHolder->size()) return std::shared_ptr<void>();
	std::shared_ptr<SFSDataWrapper> wrapper = dataHolder->at(index);
	return wrapper != NULL ? (std::static_pointer_cast<void>)(wrapper->Data()) : NULL;
}

std::shared_ptr<ISFSObject> SFSArray::GetSFSObject(unsigned long int index)
{
	//if (index >= dataHolder->size()) return std::shared_ptr<ISFSObject>();
	std::shared_ptr<SFSDataWrapper> wrapper = dataHolder->at(index);
	return (std::static_pointer_cast<ISFSObject>)(wrapper->Data());
}


}	// namespace Data
}	// namespace Entities
}	// namespace Sfs2X


// --- Core/PacketHeader.cpp ---
// ===================================================================
//
// Description		
//		Contains the implementation of PacketHeader
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================

namespace Sfs2X {
namespace Core {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
PacketHeader::PacketHeader(bool encrypted, bool compressed, bool blueBoxed, bool bigSized)
{
	binary = true;
	expectedLength = -1;
	this->compressed = compressed;
	this->encrypted = encrypted;
	this->blueBoxed = blueBoxed;
	this->bigSized = bigSized;
}

// -------------------------------------------------------------------
// ExpectedLength
// -------------------------------------------------------------------
long int PacketHeader::ExpectedLength()
{
	return expectedLength;
}

// -------------------------------------------------------------------
// ExpectedLength
// -------------------------------------------------------------------
void PacketHeader::ExpectedLength(long int value)
{
	expectedLength = value;
}

// -------------------------------------------------------------------
// Encrypted
// -------------------------------------------------------------------
bool PacketHeader::Encrypted()
{
	return encrypted;
}

// -------------------------------------------------------------------
// Encrypted
// -------------------------------------------------------------------
void PacketHeader::Encrypted(bool value)
{
	encrypted = value;
}

// -------------------------------------------------------------------
// Compressed
// -------------------------------------------------------------------
bool PacketHeader::Compressed()
{
	return compressed;
}

// -------------------------------------------------------------------
// Compressed
// -------------------------------------------------------------------
void PacketHeader::Compressed(bool value)
{
	compressed = value;
}

// -------------------------------------------------------------------
// BlueBoxed
// -------------------------------------------------------------------
bool PacketHeader::BlueBoxed()
{
	return blueBoxed;
}

// -------------------------------------------------------------------
// BlueBoxed
// -------------------------------------------------------------------
void PacketHeader::BlueBoxed(bool value)
{
	blueBoxed = value;
}

// -------------------------------------------------------------------
// Binary
// -------------------------------------------------------------------
bool PacketHeader::Binary()
{
	return binary;
}

// -------------------------------------------------------------------
// Binary
// -------------------------------------------------------------------
void PacketHeader::Binary(bool value)
{
	binary = value;
}

// -------------------------------------------------------------------
// BigSized
// -------------------------------------------------------------------
bool PacketHeader::BigSized()
{
	return bigSized;
}

// -------------------------------------------------------------------
// BigSized
// -------------------------------------------------------------------
void PacketHeader::BigSized(bool value)
{
	bigSized = value;
}

// -------------------------------------------------------------------
// FromBinary
// -------------------------------------------------------------------
std::shared_ptr<PacketHeader> PacketHeader::FromBinary(long int headerByte)
{
	return std::shared_ptr<PacketHeader>(new PacketHeader((headerByte & 0x40) > 0, 
							 (headerByte & 0x20) > 0,
							 (headerByte & 0x10) > 0,
							 (headerByte & 0x8) > 0));
}

// -------------------------------------------------------------------
// Encode
// -------------------------------------------------------------------
unsigned char PacketHeader::Encode()
{
	unsigned char headerByte = 0;
			
	if (binary)	headerByte |= 0x80;
	if (encrypted) headerByte |= 0x40;
	if (compressed)	headerByte |= 0x20;
	if (blueBoxed) headerByte |= 0x10;
	if (bigSized) headerByte |= 0x08;
				
	return headerByte;
}

// -------------------------------------------------------------------
// ToString
// -------------------------------------------------------------------
std::shared_ptr<string> PacketHeader::ToString()
{
	std::shared_ptr<string> buf (new string());
	string temporary;
	char tmpbuffer[100];

	buf->append("---------------------------------------------\n");

	temporary.clear();
	sprintf (tmpbuffer, "Binary:  \t %d \n", binary);
	temporary = tmpbuffer;
	buf->append(temporary);

	temporary.clear();
	sprintf (tmpbuffer, "Compressed:\t %d \n", compressed);
	temporary = tmpbuffer;
	buf->append(temporary);

	temporary.clear();
	sprintf (tmpbuffer, "Encrypted:\t %d \n", encrypted);
	temporary = tmpbuffer;
	buf->append(temporary);

	temporary.clear();
	sprintf (tmpbuffer, "BlueBoxed:\t %d \n", blueBoxed);
	temporary = tmpbuffer;
	buf->append(temporary);

	temporary.clear();
	sprintf (tmpbuffer, "BigSized:\t %d \n", bigSized);
	temporary = tmpbuffer;
	buf->append(temporary);

	buf->append("---------------------------------------------\n");

	return buf;
}


}	// namespace Core
}	// namespace Sfs2X


#endif // CLEVERFOX_IMPLEMENTATION
#endif // CLEVERFOX_H
