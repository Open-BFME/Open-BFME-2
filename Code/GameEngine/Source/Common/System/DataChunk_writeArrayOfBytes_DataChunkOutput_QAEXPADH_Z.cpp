// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?writeArrayOfBytes@DataChunkOutput@@QAEXPADH@Z, retail 0x00306D2F (25 bytes):
// Zero Hour's DataChunkOutput::writeArrayOfBytes, a plain fwrite of len bytes
// from ptr into the temporary file at +0x04 (the CRT fwrite import). Spelled on
// DataChunk.cpp's DataChunkOutput view, the TU retail built it in; it replaces
// the Zero Hour donor compile (Common/DataChunk.h through PreRTS.h) this body
// was first placed with.

struct _iobuf;
extern "C" __declspec(dllimport) unsigned int __cdecl fwrite(
	const void *ptr, unsigned int size, unsigned int count, struct _iobuf *file);

class ChunkInputStream;
class AsciiString;
class UnicodeString;
class Mapping;
class OutputStream;
class Dict;
class OutputChunk;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class DataChunkTableOfContents
{
public:
    DataChunkTableOfContents() : m_list(0), m_nextID(1), m_listLength(0), m_headerOpened(false) {}
    ~DataChunkTableOfContents();
    void read(ChunkInputStream &s);
    void write(OutputStream &stream);
    unsigned int allocateID(const AsciiString &name);
    unsigned int getID(const AsciiString &name);
    AsciiString getName(unsigned int id);

    Mapping *m_list;
    int m_listLength;
    unsigned int m_nextID;
    bool m_headerOpened;

private:
    Mapping *findMapping(const AsciiString &name);
};

class DataChunkOutput
{
public:
    void writeInt(int intValue);
    void writeReal(float realValue);
    void writeByte(unsigned char byteValue);
    void writeArrayOfBytes(char *ptr, int len);
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

void DataChunkOutput::writeArrayOfBytes(char *ptr, int len)
{
	::fwrite(ptr, 1, len, file);
}
