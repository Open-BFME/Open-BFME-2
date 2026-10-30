// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// DataChunkOutput::writeDict, retail 0x00307D85, 343 bytes. Semantic donor:
// Zero Hour Common/System/DataChunk.cpp writeDict (the BFME1 donor has the same
// body): a u16 pair count (fwrite to the temp file), then per pair the key's
// table-of-contents id shifted by 8 or'd with the type byte, then the value by
// type. writeReal is its own out-of-line call (ICF-folded onto writeInt), the
// Unicode value goes as a by-value temp (writeUnicodeString 0x0030708E), and
// retail stores no EH state around the AsciiString value temp, which is what
// a nothrow writeAsciiString gives; that also restores retail's register
// roles (the Dict in EBX, the index in the argument slot).
// Evidence: caller of the rowed Dict getNth* accessors, allocateID 0x00307A6A,
// writeInt 0x00306CFF, writeByte 0x00306D17, writeAsciiString 0x00307033.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;

extern "C" __declspec(dllimport) unsigned int __cdecl fwrite(
    const void *ptr, unsigned int size, unsigned int count, struct _iobuf *file);
#include "ascii_string.h"
#include "unicode_string.h"

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &nameString);
	const AsciiString &keyToName(NameKeyType key);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class Mapping;
class ChunkInputStream;
class OutputStream;
class AsciiString;

class DataChunkTableOfContents
{
public:
    DataChunkTableOfContents() : m_list(0), m_nextID(1), m_listLength(0), m_headerOpened(false) {}
    ~DataChunkTableOfContents();
    void read(ChunkInputStream &s);
    void write(OutputStream &stream);
    unsigned int allocateID(const AsciiString &name);
    AsciiString getName(unsigned int id);

    Mapping *m_list;
    int m_listLength;
    unsigned int m_nextID;
    bool m_headerOpened;

private:
    Mapping *findMapping(const AsciiString &name);
};
class Dict
{
public:
	enum DataType { DICT_NONE = -1, DICT_BOOL, DICT_INT, DICT_REAL, DICT_ASCIISTRING, DICT_UNICODESTRING };
private:
	struct DictPairData { unsigned short m_refCount; unsigned short m_numPairsAllocated; unsigned short m_numPairsUsed; };
public:
	Dict(int numPairsToPreAllocate);
	Dict(const Dict &other) : m_data(other.m_data)
	{
	    if (m_data)
	        ++m_data->m_refCount;
	}
	~Dict() { releaseData(); }
	void setBool(int key, bool value);
	void setInt(int key, int value);
	void setReal(int key, float value);
	void setAsciiString(int key, const AsciiString &value);
	void setUnicodeString(int key, const UnicodeString &value);
private:
	void releaseData();
public:
	int getPairCount() const { return m_data ? m_data->m_numPairsUsed : 0; }
	NameKeyType getNthKey(int n) const;
	DataType getNthType(int n) const;
	bool getNthBool(int n) const;
	int getNthInt(int n) const;
	float getNthReal(int n) const;
	AsciiString getNthAsciiString(int n) const;
	UnicodeString getNthUnicodeString(int n) const;
private:
	DictPairData *m_data; // +0x00
};

struct _iobuf;
class OutputStream;
class OutputChunk;
class AsciiString;
class UnicodeString;
class Dict;

class DataChunkOutput
{
public:
    void writeInt(int intValue);
    void writeReal(float realValue);
    void writeByte(unsigned char byteValue);
    DataChunkOutput(OutputStream *pOut);
    ~DataChunkOutput();
    void writeAsciiString(const AsciiString &textValue) throw();
    void writeUnicodeString(UnicodeString textValue);
    void writeNameKey(NameKeyType key);
    void writeDict(const Dict &d);

private:
    OutputStream *m_pOut;
    _iobuf *file;
    DataChunkTableOfContents m_contents;
    OutputChunk *m_chunkStack;
};
void DataChunkOutput::writeDict(const Dict &dict)
{
	UnsignedShort len = dict.getPairCount();
	::fwrite((const char *)&len, sizeof(UnsignedShort), 1, file);
	for (int i = 0; i < len; i++)
	{
		NameKeyType k = dict.getNthKey(i);
		AsciiString kname = TheNameKeyGenerator->keyToName(k);

		Int keyAndType = m_contents.allocateID(kname);
		keyAndType <<= 8;
		Dict::DataType t = dict.getNthType(i);
		keyAndType |= (t & 0xff);
		writeInt(keyAndType);

		switch (t)
		{
			case Dict::DICT_BOOL:
				writeByte(dict.getNthBool(i) ? 1 : 0);
				break;
			case Dict::DICT_INT:
				writeInt(dict.getNthInt(i));
				break;
			case Dict::DICT_REAL:
				writeReal(dict.getNthReal(i));
				break;
			case Dict::DICT_ASCIISTRING:
				writeAsciiString(dict.getNthAsciiString(i));
				break;
			case Dict::DICT_UNICODESTRING:
				writeUnicodeString(dict.getNthUnicodeString(i));
				break;
			default:
				break;
		}
	}
}
