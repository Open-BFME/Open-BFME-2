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

#include "../../../Include/Common/DataChunk.h"

enum NameKeyType
{
	NAMEKEY_INVALID = 0
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
