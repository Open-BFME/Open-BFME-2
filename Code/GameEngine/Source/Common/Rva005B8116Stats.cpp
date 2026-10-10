// cl: /O1 /Oy- /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs
//
// Native 0x005B8116..0x005B87ED, RET8, including the 24-entry jump table.
// WB01582480, callers and the matched Rva005C1BDEView::call establish the
// six-side statistics-table builder; original method name remains unknown.
// Field/map offsets, word/float payloads and 37-row switch come from target
// bytes. Lookup5B8053 is a fully owned leaf with no call or throw path, so its
// nothrow contract is target-backed; exposing it closes all eleven stack-home
// differences without duplicating that provider. Static word/float helpers
// use the native ESI/XMM0 internal ABI in this actual consuming TU.
// Prior reconstruction retained from the bank; canonical ASCII/Wide headers.
#include "ascii_string.h"
#include "unicode_string.h"

class Rva005B8053
{
	void *m_header;
public:
	__declspec(nothrow) void *rva005B8053(unsigned char const *key);
};

static int rva005B808D(unsigned char key, Rva005B8053 *self)
{
	((unsigned char *)&key)[3] = key;
	void *node = self->rva005B8053((unsigned char const *)((char *)&key + 3));
	if (node == *(void **)self)
		return 0;
	return *(unsigned short *)((char *)node + 0x12);
}

static float rva005B80D0(unsigned char key, Rva005B8053 *self)
{
	((unsigned char *)&key)[3] = key;
	void *node = self->rva005B8053((unsigned char const *)((char *)&key + 3));
	if (node == *(void **)self)
		return 0.0f;
	return *(float *)((char *)node + 0x14);
}

static __forceinline float rva005B80F2Inline(int side, float def, Rva005B8053 *self)
{
	unsigned char key = (unsigned char)side;
	void *node = self->rva005B8053(&key);
	if (node == *(void **)self)
		return def;
	return *(float *)((char *)node + 0x14);
}

struct BfmeStringRecord005DDD40 { UnicodeString text; unsigned int word; };
class Rva005DD822 : public BfmeStringRecord005DDD40 { public: Rva005DD822(unsigned int); };
class Rva005DD8E0 : public BfmeStringRecord005DDD40 { public: Rva005DD8E0(float, float); };
class Rva005DDE01 { public: void rva005DDE01(unsigned int, unsigned int, const BfmeStringRecord005DDD40 &, bool); };

struct Rva005B8116Map { Rva005B8053 m_tree; int m_pad[2]; };

struct Rva005B8116Stats
{
	int m_pad00;
	Rva005B8053 m_04; int m_pad08[2];
	Rva005B8053 m_10; int m_pad14[2];
	Rva005B8053 m_1C; int m_pad20[2];
	Rva005B8053 m_28; int m_pad2C[2];
	Rva005B8053 m_34; int m_pad38[2];
	Rva005B8053 m_40; int m_pad44[2];
	char m_pad4C[0xDC - 0x4C];
	Rva005B8053 m_DC; int m_padE0[2];
	Rva005B8053 m_E8; int m_padEC[2];
	Rva005B8053 m_F4; int m_padF8[2];
	Rva005B8053 m_100; int m_pad104[2];
	Rva005B8053 m_10C; int m_pad110[2];
	Rva005B8053 m_118; int m_pad11C[2];
	Rva005B8053 m_124; int m_pad128[2];
	Rva005B8053 m_130; int m_pad134[2];
	char m_pad13C[0x146 - 0x13C];
	unsigned short m_146;
	unsigned short m_148;
	unsigned short m_14A;
	unsigned short m_14C;
};

class Rva005B8116
{
public:
	void rva005B8116(Rva005B8116Stats *stats, int *total);

private:
	char m_pad00[0x60];
	Rva005DDE01 m_table; // +0x60
};

void Rva005B8116::rva005B8116(Rva005B8116Stats *stats, int *total)
{
	for (int side = 0; side < 6; ++side)
	{
		unsigned int a = rva005B808D(side, &stats->m_04);
		unsigned int b = rva005B808D(side, &stats->m_10);
		unsigned int c = (unsigned int)rva005B80D0(side, &stats->m_F4);
		unsigned int d = (unsigned int)rva005B80D0(side, &stats->m_E8);
		unsigned int e = (unsigned int)rva005B80D0(side, &stats->m_DC);
		unsigned int f = (unsigned int)rva005B80D0(side, &stats->m_100);
		unsigned int g = (unsigned int)rva005B80D0(side, &stats->m_124);
		int h = (int)rva005B80F2Inline(side, -1.0f, &stats->m_130);
		if (h == -1)
			h = g;
		*total += h;
		for (int row = 0; row < 37; ++row)
		{
			switch (row)
			{
			case 0: m_table.rva005DDE01(0, side, Rva005DD822(rva005B808D(side, &stats->m_1C)), true); break;
			case 1: m_table.rva005DDE01(1, side, Rva005DD822(rva005B808D(side, &stats->m_28)), true); break;
			case 2: m_table.rva005DDE01(2, side, Rva005DD822(rva005B808D(side, &stats->m_40)), true); break;
			case 3: m_table.rva005DDE01(3, side, Rva005DD822(rva005B808D(side, &stats->m_34)), true); break;
			case 4: m_table.rva005DDE01(4, side, Rva005DD822(a), true); break;
			case 5: m_table.rva005DDE01(5, side, Rva005DD822(b), true); break;
			case 6: m_table.rva005DDE01(6, side, Rva005DD8E0((float)a, (float)b), true); break;
			case 7: m_table.rva005DDE01(7, side, Rva005DD822(a + b), true); break;
			case 14: m_table.rva005DDE01(14, side, Rva005DD822((unsigned int)rva005B80D0(side, &stats->m_118)), true); break;
			case 15: m_table.rva005DDE01(15, side, Rva005DD822((unsigned int)rva005B80D0(side, &stats->m_10C)), true); break;
			case 16: m_table.rva005DDE01(16, side, Rva005DD822(f), true); break;
			case 17: m_table.rva005DDE01(17, side, Rva005DD822(c), true); break;
			case 18: m_table.rva005DDE01(18, side, Rva005DD822(d), true); break;
			case 19: m_table.rva005DDE01(19, side, Rva005DD8E0((float)e, (float)d), true); break;
			case 20: m_table.rva005DDE01(20, side, Rva005DD822(e), true); break;
			case 21: m_table.rva005DDE01(21, side, Rva005DD822(g), true); break;
			case 22: m_table.rva005DDE01(22, side, Rva005DD8E0((float)((f + e) * 100), (float)h), true); break;
			case 23: m_table.rva005DDE01(23, side, Rva005DD8E0((float)c, (float)d), true); break;
			}
		}
	}
	m_table.rva005DDE01(0, 6, Rva005DD822(stats->m_146), false);
	m_table.rva005DDE01(1, 6, Rva005DD822(stats->m_14A), false);
	m_table.rva005DDE01(2, 6, Rva005DD822(stats->m_148), false);
	m_table.rva005DDE01(3, 6, Rva005DD822(stats->m_14C), false);
}
