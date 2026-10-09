// ?writeDict@DataChunkOutput@@QAEXABVDict@@@Z
// partial score=0.93 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?writeDict@DataChunkOutput@@QAEXABVDict@@@Z
// DataChunkOutput::writeDict, retail 0x00307D85, 343 bytes. Semantic donor:
// Zero Hour Common/System/DataChunk.cpp writeDict (the BFME1 donor has the same
// body): a u16 pair count (fwrite to the temp file), then per pair the key's
// table-of-contents id shifted by 8 or'd with the type byte, then the value by
// type. Retail writes a Real through writeInt (the float's bits) rather than
// fwrite, and the Unicode value as a by-value temp (writeUnicodeString 0x0030708E).
// Evidence: caller of the rowed Dict getNth* accessors, allocateID 0x00307A6A,
// writeInt 0x00306CFF, writeByte 0x00306D17, writeAsciiString 0x00307033.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;

#include "ascii_string.h"
#include "unicode_string.h"

extern "C" __declspec(dllimport) unsigned int __cdecl fwrite(
	const void *chunkBuffer, unsigned int elementSize, unsigned int elementCount, void *outputFile) throw();

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	const AsciiString &keyToName(NameKeyType key);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class DataChunkTableOfContents
{
public:
	UnsignedInt allocateID(const AsciiString &name);

private:
	void *m_list;
	Int m_listLength;
	UnsignedInt m_nextID;
	unsigned char m_headerOpened;
};

class Dict
{
public:
	enum DataType
	{
		DICT_NONE = -1,
		DICT_BOOL,
		DICT_INT,
		DICT_REAL,
		DICT_ASCIISTRING,
		DICT_UNICODESTRING
	};

	UnsignedShort getPairCount() const { return m_data ? m_data->m_numPairsUsed : 0; }
	NameKeyType getNthKey(Int n) const;
	DataType getNthType(Int n) const;
	Bool getNthBool(Int n) const;
	Int getNthInt(Int n) const;
	float getNthReal(Int n) const;
	AsciiString getNthAsciiString(Int n) const;
	UnicodeString getNthUnicodeString(Int n) const;

private:
	struct DictPairData
	{
		UnsignedShort m_refCount;
		UnsignedShort m_numPairsAllocated;
		UnsignedShort m_numPairsUsed;
	};

	DictPairData *m_data;
};

class DataChunkOutput
{
public:
	void writeDict(const Dict &d);
	void writeInt(Int value);
	void writeByte(unsigned char value);
	void writeAsciiString(const AsciiString &value);
	void writeUnicodeString(UnicodeString value);
	void writeReal(float value) { writeInt(*(Int *)&value); }

private:
	void *m_outputStream;			// +0x00
	void *m_tmp_file;			// +0x04
	DataChunkTableOfContents m_contents;	// +0x08
};

void DataChunkOutput::writeDict(const Dict &d)
{
	UnsignedShort len = d.getPairCount();
	::fwrite((const char *)&len, sizeof(UnsignedShort), 1, m_tmp_file);
	for (int i = 0; i < len; i++)
	{
		NameKeyType k = d.getNthKey(i);
		AsciiString kname = TheNameKeyGenerator->keyToName(k);

		Int keyAndType = m_contents.allocateID(kname);
		keyAndType <<= 8;
		Dict::DataType t = d.getNthType(i);
		keyAndType |= (t & 0xff);
		writeInt(keyAndType);

		switch (t)
		{
			case Dict::DICT_BOOL:
				writeByte(d.getNthBool(i) ? 1 : 0);
				break;
			case Dict::DICT_INT:
				writeInt(d.getNthInt(i));
				break;
			case Dict::DICT_REAL:
				writeReal(d.getNthReal(i));
				break;
			case Dict::DICT_ASCIISTRING:
				writeAsciiString(d.getNthAsciiString(i));
				break;
			case Dict::DICT_UNICODESTRING:
				writeUnicodeString(d.getNthUnicodeString(i));
				break;
			default:
				break;
		}
	}
}
