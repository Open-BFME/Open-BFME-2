// ?rva00579CD4@Rva00579AB7@@QAEXUIntPair579CD4@@@Z
// partial score=0.93 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?rva00579CD4@Rva00579AB7@@QAEXUIntPair579CD4@@@Z @0x00579CD4 105B: vslot 1 of 0x0086ED64, two-int setter at +0x24 with change detection via 8B compare 0x0007E394, fetch via rowed Rva00579868Get 0x00579868, set index 0 via rowed rva00579B17 0x00579B17.
// Evidence: vtable 0x0086ED64 class of ??1Rva00579AB7 0x00579AB7 plus sibling setters rva00579D3D/rva00579D96 same Get/Set pattern plus releaseBuffer 0x00036E70.
#include "ascii_string.h"
#include "unicode_string.h"

UnicodeString __cdecl Rva00579868Get(int a, int b);

class Rva00579B17
{
public:
	void rva00579B17(int index, const UnicodeString &text);
};

struct IntPair579CD4
{
	int a;
	int b;
};
extern "C" bool __cdecl rva0007E394CursorEqual(const IntPair579CD4 &, const IntPair579CD4 &);

class Rva00579AB7
{
public:
	void rva00579CD4(IntPair579CD4 p);

private:
	void *m_vptr;
	int m_level;
	char m_name[4];
	char m_pad0C[0x24 - 0x0C];
	IntPair579CD4 m_pair;
	int m_2C[2];
	char m_pad34[0x38 - 0x34];
	float m_38;
};

// ?rva00579CD4@Rva00579AB7@@QAEXUIntPair579CD4@@@Z present-unmatched
void Rva00579AB7::rva00579CD4(IntPair579CD4 p)
{
	IntPair579CD4 *slot = &m_pair;
	if (rva0007E394CursorEqual(p, *slot))
		return;
	int b = p.b;
	int a = p.a;
	((Rva00579B17 *)this)->rva00579B17(0, Rva00579868Get(a, b));
	slot->b = b;
	slot->a = a;
}
