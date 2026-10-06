// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?rva005FD8E5@Rva005FD788@@QAEXHHH@Z retail 0x005FD8E5 113B
// Evidence: chain from 0x005FD53E you landed; calls Get 0x005FD53E and rva005FD788 0x005FD788 and releaseBuffer 0x00036E70; entry stride 0x18 base 0x1C offsets 0x10 0x14; string CP literal; /G7 for retail imul 0x18; caller 0x005FD959 jmp
template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};
#include "ascii_string.h"
#include "unicode_string.h"
struct Rva005FD788Inner
{
	char m_pad8[8];
	char m_name[1];
};
class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &, const UnicodeString &, bool);
};
UnicodeString Rva005FD53EGet(int a, int b);
extern BfmeAptWindowManager *g_Va009FE4CC;
extern const char *g_Va0087A290[];
struct Rva005FD8E5Entry
{
	char m_pad[16];
	int m_a16;
	int m_b20;
};
struct Rva005FD788
{
	char m_pad0[4];
	int m_level4;
	Rva005FD788Inner *m_inner8;
	char m_padC[16];
	Rva005FD8E5Entry m_entries[1];
	void rva005FD788(int index, const char *suffix, const UnicodeString &text);
	void rva005FD8E5(int index, int a, int b);
};
void Rva005FD788::rva005FD8E5(int index, int a, int b)
{
	Rva005FD8E5Entry *entry = &m_entries[index];
	if (a == entry->m_a16 && b == entry->m_b20)
		return;
	rva005FD788(index, "CP", Rva005FD53EGet(a, b));
	entry->m_a16 = a;
	entry->m_b20 = b;
}

struct Rva005FD956
{
	char m_pad0[4];
	Rva005FD788 *m_p4;
	void rva005FD956(int index, int a, int b);
};

void Rva005FD956::rva005FD956(int index, int a, int b)
{
	m_p4->rva005FD8E5(index, a, b);
}
