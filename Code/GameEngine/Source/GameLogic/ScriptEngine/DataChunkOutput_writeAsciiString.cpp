// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// DataChunkOutput::writeAsciiString, retail 0x00307033, 91 bytes.
//
// Ported from the Zero Hour reference
// (GameEngine/Source/Common/System/DataChunk.cpp, writeAsciiString).
// Retail inlines AsciiString::getLength/str the way the BFME string header
// does: the shared buffer keeps a 16-bit length at offset 4 and the
// characters at offset 8, with a null buffer reading as empty.

typedef unsigned short UnsignedShort;

struct _iobuf;
extern "C" __declspec(dllimport) unsigned int __cdecl fwrite(
	const void *chunkBuffer, unsigned int elementSize, unsigned int elementCount, struct _iobuf *file);

#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"


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
// ?writeAsciiString@DataChunkOutput@@QAEXABVAsciiString@@@Z
void DataChunkOutput::writeAsciiString(const AsciiString &textValue) throw()
{
	UnsignedShort textLength = textValue.getLength();
	::fwrite((const char *)&textLength, sizeof(UnsignedShort), 1, file);
	::fwrite(textValue.str(), textLength, 1, file);
}
