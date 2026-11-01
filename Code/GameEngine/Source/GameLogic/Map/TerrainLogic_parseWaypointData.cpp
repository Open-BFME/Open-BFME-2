// cl: /DNDEBUG /MD /EHsc
// ?readInt@DataChunkInput@@QAEHXZ, retail 0x00306E78 (34 bytes): Zero Hour's
// DataChunkInput::readInt. One four-byte read through the input stream
// (vslot 0 of the stream at +0x00), then decrementDataLeft(4) (0x00306E40),
// then the value. Spelled on DataChunk.cpp's views of the stream, the table of
// contents and DataChunkInput, the TU retail built it in.

class ChunkInputStream;
class AsciiString;
class UnicodeString;
class Mapping;
class OutputStream;
struct InputChunk;
class Dict;

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

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

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

// Zero Hour's ChunkInputStream: read is vslot 0, eof vslot 3.
class ChunkInputStream
{
public:
	virtual int read(void *buf, int numBytes) = 0;
	virtual unsigned int tell(void) = 0;
	virtual bool absoluteSeek(unsigned int pos) = 0;
	virtual bool eof(void) = 0;
};

// ?readInt@DataChunkInput@@QAEHXZ @0x00306E78
int DataChunkInput::readInt()
{
	int value;
	m_file->read(&value, 4);
	decrementDataLeft(4);
	return value;
}
