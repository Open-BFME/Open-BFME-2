// cl: /DNDEBUG /MD
// ?rva0030750A@DataChunkInput@@QAE?AVAsciiString@@XZ @0x0030750A 153B
// DataChunkInput counted-string reader (readAsciiString shape): reads u16 len
// via virtual read, decrements, getBufferForRead, reads bytes, null terms,
// returns AsciiString by value via StringBase copy plus releaseBuffer.
// Evidence: unlock lane, prev getChunkLabel 0x3074D7 same /O1, callees rowed
// decrement 0x306E40 releaseBuffer 0x36410 plus pins getBufferForRead 0x36640
// StringBase copy 0x365F0, 40+ callers, donor ZH DataChunk.cpp readAsciiString
// without yield under NDEBUG (BFME2 yield absent here).

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;

class AsciiString;

template <typename T>
class StringBase
{
    friend class AsciiString;

public:
    StringBase(void) : m_data(0) {}
    T *getBufferForRead(Int len);

protected:
    void *m_data;

private:
    StringBase(const StringBase &other);
};

class AsciiString : public StringBase<char>
{
public:
    AsciiString(void) : StringBase<char>() {}
    AsciiString(const AsciiString &other) : StringBase<char>(other) {}
    AsciiString(const char *text);
    ~AsciiString();

private:
    // keep 4-byte layout via base only
};

class ChunkInputStream
{
public:
    virtual Int read(void *pData, Int numBytes);
    virtual Int tell(void);
    virtual void absoluteSeek(Int pos);
    virtual Bool eof(void);
};

class InputChunk
{
public:
    virtual ~InputChunk();

    InputChunk *next;
    UnsignedInt id;
    UnsignedShort version;
    UnsignedShort padding;
    Int chunkStart;
    Int dataSize;
    Int dataLeft;
};

class DataChunkTableOfContents
{
public:
    void *m_list;
    Int m_listLength;
    UnsignedInt m_nextID;
    Bool m_headerOpened;
};

class DataChunkInput
{
public:
    AsciiString rva0030750A();

protected:
    void decrementDataLeft(Int size);

private:
    ChunkInputStream *m_file;
    DataChunkTableOfContents m_contents;
    Int m_fileposOfFirstChunk;
    void *m_parserList;
    InputChunk *m_chunkStack;
};

AsciiString DataChunkInput::rva0030750A(void)
{
    UnsignedShort len;
    m_file->read(&len, sizeof(UnsignedShort));
    decrementDataLeft(sizeof(UnsignedShort));

    AsciiString theString;
    if (len > 0)
    {
        char *str = theString.getBufferForRead(len);
        m_file->read(str, len);
        decrementDataLeft(len);
        str[len] = '\0';
    }

    return theString;
}
