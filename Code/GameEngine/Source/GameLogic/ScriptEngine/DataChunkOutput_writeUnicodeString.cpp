// cl: /Ireference/shims/bfme2_ascii
//
// DataChunkOutput::writeUnicodeString, retail 0x0030708E, 99 bytes.
//
// Ported from the Zero Hour reference
// (GameEngine/Source/Common/System/DataChunk.cpp, writeUnicodeString)
// and the BFME1 donor DataChunk.cpp.
// Retail writes a U16 length then len*2 wide bytes, destroying the by-value
// UnicodeString temp via the pinned wide releaseBuffer at 0x00036E70.
// Evidence: caller at 0x00307E46 in writeDict passes the Dict Unicode temp;
// empty wide path corresponds to retail VA 0x00BBB5C4.

typedef unsigned short UnsignedShort;
typedef unsigned short WideChar;

struct _iobuf;
extern "C" __declspec(dllimport) unsigned int __cdecl fwrite(
	const void *chunkBuffer, unsigned int elementSize, unsigned int elementCount, struct _iobuf *file) throw();

#include "unicode_string.h"

struct _iobuf;
class OutputStream;
class OutputChunk;
class AsciiString;
class UnicodeString;
class Dict;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class Mapping;
class ChunkInputStream;

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
void DataChunkOutput::writeUnicodeString(UnicodeString textValue)
{
	UnsignedShort textLength = (UnsignedShort)textValue.getLength();
	::fwrite((const char *)&textLength, sizeof(UnsignedShort), 1, file);
	::fwrite(textValue.str(), textLength * sizeof(WideChar), 1, file);
}
