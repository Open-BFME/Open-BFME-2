// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?readNameKey@DataChunkInput@@QAE?AW4NameKeyType@@XZ 0x003077E0 83B evidence: readInt sar 8 then m_contents getName then TheNameKeyGenerator nameToKey AsciiString overload; callers 0x0032CED9 0x0032F67F 0x003B5EF4 0x003B6DE0 0x0041ED9C; unblocks 5
typedef int Int;
typedef unsigned int UnsignedInt;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

#include "ascii_string.h"


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
class ChunkInputStream;
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
NameKeyType DataChunkInput::readNameKey(void)
{
	Int keyAndType = readInt();
	keyAndType >>= 8;
	AsciiString kname = m_contents.getName((UnsignedInt)keyAndType);
	NameKeyType k = TheNameKeyGenerator->nameToKey(kname);
	return k;
}
