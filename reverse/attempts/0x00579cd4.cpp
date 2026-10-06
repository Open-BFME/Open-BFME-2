// ?rva00579CD4@Rva00579AB7@@QAEXHH@Z
// partial score=0.92 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva00579D96@Rva00579AB7@@QAEXM@Z @0x00579D96 98B slot 5 of 0x0086ED64.
// Float setter with change detection: if arg != m_38, fetch UnicodeString via
// rowed Rva00579995Get 0x00579995, set indexed text via rowed rva00579B17
// 0x00579B17 with index 4, then store arg to m_38. Callees rowed, vtable slot
// evidence, neighbours Rva00579AB7Dtor and Rva00579E47Delegate share /O1.
// ?rva00579D3D@Rva00579AB7@@QAEXHH@Z @0x00579D3D 89B slot 3 of same vtable.
// Int array setter at +0x2C with same Get/Set pattern via rowed Rva00579900Get
// 0x00579900 and index+1.
// ?rva00579CD4@Rva00579AB7@@QAEXURva00579CD4CommandPoints@@@Z @0x00579CD4
// 105B slot 1: the command-points pair at +0x24, compared through the folded
// two-dword equality 0x0007E394 and shown on line 0 via rowed Rva00579868Get.
// ?rva00579DF8@Rva00579AB7@@QAEXH@Z @0x00579DF8 79B slot 7: the power points
// at +0x3C, line 5 via rowed Rva00579A2FGet 0x00579A2F.
#include "ascii_string.h"
#include "unicode_string.h"

UnicodeString __cdecl Rva00579995Get(float value);
UnicodeString __cdecl Rva00579900Get(int value);
UnicodeString __cdecl Rva00579868Get(int used, int max);
UnicodeString __cdecl Rva00579A2FGet(int value);

struct Rva00579CD4CommandPoints
{
	int used;
	int max;
};

bool operator==(const Rva00579CD4CommandPoints &a, const Rva00579CD4CommandPoints &b);

class Rva00579B17
{
public:
	void rva00579B17(int index, const UnicodeString &text);
};

class Rva00579AB7
{
public:
	void rva00579D96(float value);
	void rva00579D3D(int index, int value);
	void rva00579CD4(int used, int max);
	void rva00579DF8(int value);

private:
	void *m_vptr;
	int m_level;
	char m_name[4];
	char m_pad0C[0x24 - 0x0C];
	Rva00579CD4CommandPoints m_24;
	int m_2C[2];
	char m_pad34[0x38 - 0x34];
	float m_38;
	int m_3C;
};

void Rva00579AB7::rva00579D96(float value)
{
	if (value != m_38)
	{
		((Rva00579B17 *)this)->rva00579B17(4, Rva00579995Get(value));
		m_38 = value;
	}
}

void Rva00579AB7::rva00579D3D(int index, int value)
{
	int *slot = &m_2C[index];
	if (value != *slot)
	{
		((Rva00579B17 *)this)->rva00579B17(index + 1, Rva00579900Get(value));
		*slot = value;
	}
}

void Rva00579AB7::rva00579CD4(int used, int max)
{
	Rva00579CD4CommandPoints *cur = &m_24;
	if (!(*(Rva00579CD4CommandPoints *)&used == *cur))
	{
		int u = used;
		int m = max;
		((Rva00579B17 *)this)->rva00579B17(0, Rva00579868Get(u, m));
		cur->max = m;
		cur->used = u;
	}
}

void Rva00579AB7::rva00579DF8(int value)
{
	if (value != m_3C)
	{
		((Rva00579B17 *)this)->rva00579B17(5, Rva00579A2FGet(value));
		m_3C = value;
	}
}
