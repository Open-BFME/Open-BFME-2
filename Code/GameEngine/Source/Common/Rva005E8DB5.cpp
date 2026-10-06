// cl: /O1 /arch:SSE /G7 /Ob2 /EHsc /MD
// ?rva005E8DB5@Rva005E8DB5@@QAEPAXXZ retail 0x005E8DB5 26B
// evidence: VTABLE slot 2 of 0x00877F88 class of ??1Rva005E8D71 caller 0x005E8DCF globals g_00E06734 g_00E06748

struct Rva005E8DB5Param
{
	char m_pad0[0x20];
	int m_20;
	char m_pad1[0x10];
	unsigned char m_34;
};

extern int g_00E06734;
extern int g_00E06748;

class Rva005E8DB5
{
	char m_pad[0x20];
	Rva005E8DB5Param *m_20;
public:
	void *rva005E8DB5();
};

void *Rva005E8DB5::rva005E8DB5()
{
	Rva005E8DB5Param *p = m_20;
	if (p->m_20 == 0)
		return &g_00E06748;
	return p->m_34 == 0 ? &g_00E06734 : &g_00E06748;
}
