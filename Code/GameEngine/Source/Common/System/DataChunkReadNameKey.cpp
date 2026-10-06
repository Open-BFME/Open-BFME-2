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
};
extern NameKeyGenerator *TheNameKeyGenerator;

class DataChunkTableOfContents
{
public:
	AsciiString getName(UnsignedInt id);
	~DataChunkTableOfContents();
	void *m_list;
	Int m_listLength;
	UnsignedInt m_nextID;
	unsigned char m_headerOpened;
};

class ChunkInputStream;
class DataChunkInput
{
protected:
	ChunkInputStream *m_file;
	DataChunkTableOfContents m_contents;
public:
	Int readInt(void);
	NameKeyType readNameKey(void);
};
NameKeyType DataChunkInput::readNameKey(void)
{
	Int keyAndType = readInt();
	keyAndType >>= 8;
	AsciiString kname = m_contents.getName((UnsignedInt)keyAndType);
	NameKeyType k = TheNameKeyGenerator->nameToKey(kname);
	return k;
}
