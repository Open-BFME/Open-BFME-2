// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?Rva005F066CSet@@YAXHPAURva005F066COuter@@ABVUnicodeString@@@Z @0x005F066C 103B caller 0x005F0C54, format APT:_level BuildingName via 0x00038150
template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"

#include "unicode_string.h"

struct Rva005F066CInner
{
	char m_pad8[8];
	char m_name[1];
};

struct Rva005F066COuter
{
	Rva005F066CInner *m_ptr;
};

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &, const UnicodeString &, bool);
};

extern BfmeAptWindowManager *g_bfmeAptWindowManager;

void __cdecl Rva005F066CSet(int level, Rva005F066COuter *outer, const UnicodeString &text)
{
	AsciiString key;
	const char *mid = outer->m_ptr ? outer->m_ptr->m_name : "";
	key.format("APT:_level%u.%s_BuildingName", level, mid);
	g_bfmeAptWindowManager->bfmeSetText(key, text, true);
}
