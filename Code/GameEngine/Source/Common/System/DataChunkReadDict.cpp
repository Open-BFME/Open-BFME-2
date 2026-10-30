// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?readDict@DataChunkInput@@QAE?AVDict@@XZ @0x00307833 397B
// DataChunkInput readDict: reads u16 len, Dict d(len), loops reading keyAndType
// via readInt, getName via m_contents, nameToKey via generator, switches on
// type calling readByte/readInt/readReal/rva ascii/rva unicode plus set calls,
// throws DEAD0005 via CxxThrow on bad type, returns Dict by value.
// Evidence: chain lane calls just-landed readUnicodeString plus sibling ascii,
// donor BFME1 DataChunk.cpp readDict, callers 7 including ParseWorldDict.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;

// Zero Hour's Common/Errors.h (ERROR_BASE 0xDEAD0001 + 4). Retail throws the enum:
// its ThrowInfo is __TI1?AW4ErrorCode@@ (0x00CFEEE4), not int's __TI1H (0x00CFE2C8).
enum ErrorCode
{
	ERROR_CORRUPT_FILE_FORMAT = 0xDEAD0005
};

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
class ChunkInputStream
{
public:
    virtual Int read(void *pData, Int numBytes);
    virtual Int tell(void);
    virtual void absoluteSeek(Int pos);
    virtual Bool eof(void);
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

struct InputChunk;
class Dict;
class UnicodeString;

class DataChunkInput
{
public:
	DataChunkInput(ChunkInputStream *stream);
	unsigned short getChunkVersion();
	unsigned int getChunkDataSizeLeft();
	bool atEndOfFile();
	void clearChunkStack();
	float readReal();
	unsigned char readByte();
	void readArrayOfBytes(char *buffer, int length);
	AsciiString getChunkLabel();
	AsciiString readAsciiString();
	UnicodeString readUnicodeString();
	int readInt();
	NameKeyType readNameKey();
	Dict readDict();

protected:
	void decrementDataLeft(int size);

private:
	ChunkInputStream *m_file;
	DataChunkTableOfContents m_contents;	// +0x04
	int m_fileposOfFirstChunk;	// +0x14
	void *m_parserList;			// +0x18
	InputChunk *m_chunkStack;	// +0x1C
	void *m_currentObject;		// +0x20
	void *m_userData;			// +0x24
};

Dict DataChunkInput::readDict(void)
{
    UnsignedShort len;
    m_file->read(&len, sizeof(UnsignedShort));
    decrementDataLeft(sizeof(UnsignedShort));

    Dict d(len);

    for (int i = 0; i < len; i++)
    {
        Int keyAndType = readInt();
        Int t = keyAndType & 0xff;
        keyAndType >>= 8;

        AsciiString kname = m_contents.getName((UnsignedInt)keyAndType);
        NameKeyType k = TheNameKeyGenerator->nameToKey(kname);

        switch (t)
        {
            case Dict::DICT_BOOL:
                d.setBool((int)k, readByte() ? true : false);
                break;
            case Dict::DICT_INT:
                d.setInt((int)k, readInt());
                break;
            case Dict::DICT_REAL:
                d.setReal((int)k, readReal());
                break;
            case Dict::DICT_ASCIISTRING:
                d.setAsciiString((int)k, readAsciiString());
                break;
            case Dict::DICT_UNICODESTRING:
                d.setUnicodeString((int)k, readUnicodeString());
                break;
            default:
            {
                throw ERROR_CORRUPT_FILE_FORMAT;
                break;
            }
        }
    }

    return d;
}
