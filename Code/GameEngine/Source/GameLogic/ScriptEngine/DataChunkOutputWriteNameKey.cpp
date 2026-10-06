// cl: /Ireference/shims/bfme2_ascii /EHsc
//
// DataChunkOutput::writeNameKey, retail 0x00307D29 (true 92 bytes; the 10B
// reloc row covers only the SEH-prologue head: mov eax,cookie + call
// __EH_prolog, so that row size is a misbound).
// ZH DataChunk.cpp writeNameKey ported with one BFME2 delta proven by the
// retail bodies: keyToName returns a reference to the generator's interned
// string (retail 0x00148C95 returns the bucket/global AsciiString pointer in
// eax with ret 4: no hidden pointer, no copy on the return path), so the
// declaration here returns const AsciiString &. kname copy-constructs from
// it through AsciiString's inline forwarder, which routes directly to the
// StringBase<char> copy body at 0x365F0 (the push eax + lea ecx + call shape
// at all 61 keyToName call sites, cf. BFME1 ascii_string.h for the same
// delegation evidence). Teardown inlines to the folded releaseBuffer at
// 0x36410.

struct BfmeStringData
{
	unsigned short m_refCount;
	unsigned short m_numCharsAllocated;
	unsigned short m_len;
	unsigned short m_pad;
};

class AsciiString;
#include "ascii_string.h"


enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	const AsciiString &keyToName(NameKeyType key);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class DataChunkTableOfContents
{
public:
	unsigned int allocateID(const AsciiString &name);
};

class Dict
{
public:
	enum DataType
	{
		DICT_BOOL = 0,
		DICT_INT = 1,
		DICT_REAL = 2,
		DICT_ASCIISTRING = 3
	};
};

class DataChunkOutput
{
public:
	void writeNameKey(NameKeyType key);
	void writeInt(int value);

private:
	char m_pad[8];
	DataChunkTableOfContents m_contents;
};

// ?writeNameKey@DataChunkOutput@@QAEXW4NameKeyType@@@Z
void DataChunkOutput::writeNameKey(NameKeyType key)
{
	AsciiString kname = TheNameKeyGenerator->keyToName(key);
	int keyAndType = m_contents.allocateID(kname);
	keyAndType <<= 8;
	Dict::DataType t = Dict::DICT_ASCIISTRING;
	keyAndType |= (t & 0xff);
	writeInt(keyAndType);
}
