// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?readDict@DataChunkInput@@QAE?AVDict@@XZ @0x00307833 397B
// DataChunkInput readDict: reads u16 len, Dict d(len), loops reading keyAndType
// via readInt, getName via m_contents, nameToKey via generator, switches on
// type calling readByte/readInt/readReal/rva ascii/rva unicode plus set calls,
// throws DEAD0005 via CxxThrow on bad type, returns Dict by value.
// Evidence: chain lane calls just-landed rva003075A3 plus sibling ascii,
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
};
extern NameKeyGenerator *TheNameKeyGenerator;

class DataChunkTableOfContents
{
public:
    AsciiString getName(UnsignedInt id);

private:
    void *m_list;
    Int m_listLength;
    UnsignedInt m_nextID;
    unsigned char m_headerOpened;
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
    enum DataType
    {
        DICT_NONE = -1,
        DICT_BOOL,
        DICT_INT,
        DICT_REAL,
        DICT_ASCIISTRING,
        DICT_UNICODESTRING
    };

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

    struct DictPairData
    {
        UnsignedShort m_refCount;
        UnsignedShort m_numPairsAllocated;
        UnsignedShort m_numPairsUsed;
    };

    DictPairData *m_data;
};

class DataChunkInput
{
public:
    Dict readDict(void);
    AsciiString rva0030750A(void);
    UnicodeString rva003075A3(void);
    Int readInt(void);
    float readReal(void);
    unsigned char readByte(void);

protected:
    void decrementDataLeft(Int size);

private:
    ChunkInputStream *m_file;
    DataChunkTableOfContents m_contents;
    Int m_fileposOfFirstChunk;
    void *m_parserList;
    void *m_chunkStack;
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
                d.setAsciiString((int)k, rva0030750A());
                break;
            case Dict::DICT_UNICODESTRING:
                d.setUnicodeString((int)k, rva003075A3());
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
