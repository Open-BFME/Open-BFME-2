// cl: /O1 /arch:SSE /G7 /Ob2 /EHsc /MD
// ?rva005E8DB5@Rva005E8D71@@UAEPAXXZ retail 0x005E8DB5 26B
// evidence: VTABLE slot 2 of 0x00877F88 class of ??1Rva005E8D71 caller 0x005E8DCF globals g_00E06734 g_00E06748

struct Rva005E8DB5Param
{
	char m_pad0[0x20];
	int m_20;
	char m_pad1[0x10];
	unsigned char m_34;
};

int g_00E06734[5];	// retail RVA 0x00A06734 (.bss), defined here
int g_00E06748[5];	// retail RVA 0x00A06748 (.bss), defined here

// Slot 2 of Rva005E8D71's primary vftable (retail 0x00C77F88, installed by
// its constructor in Rva005E8D71Ctor.cpp and destructor 0x005E8D71); slot 1
// is rva005E8CF8 (Rva005E8D71Method.cpp).
class Rva005E8D71
{
public:
	virtual void *rva005E8DB5();
private:
	char m_pad[0x1C];
	Rva005E8DB5Param *m_20;
};

void *Rva005E8D71::rva005E8DB5()
{
	Rva005E8DB5Param *p = m_20;
	if (p->m_20 == 0)
		return g_00E06748;
	return p->m_34 == 0 ? g_00E06734 : g_00E06748;
}
