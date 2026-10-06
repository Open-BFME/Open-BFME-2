// cl: -O1 -GR- -EHsc-
// ?Run@Rva005A8666Box@@QAEXH@Z @0x005A8666 90B: guarded one-shot setter.
// Unless +0x94C already reads 5, resolve m_8[m_14]; a present object with
// its 0x40 flag set and a present m_8[m_18] plus both byte gates leads
// through the pinned 0x5A831E call to the pinned setter with 3, every other
// failing path uses 5. The int parameter is unused (callback shape). Targets
// read from retail REL32; the 0x5A6C90 callee is matched but spelled local.
struct Rva005A8666Obj
{
	char pad[0x40];
	unsigned char m_40;
};

struct Rva005A8666Box
{
	char pad0[8];
	Rva005A8666Obj **m_8;
	int m_C;
	int m_10;
	int m_14;
	int m_18;
	char pad1[0x24 - 0x1c];
	unsigned char m_24;
	unsigned char m_25;
	char pad2[0x942 - 0x26];
	unsigned char m_942;
	char pad3[0x94c - 0x943];
	int m_94C;

	void Check();
	void Run5(int code);
	void Run(int unused);
};

void Rva005A8666Box::Run(int unused)
{
	if (m_94C == 5)
		return;
	Rva005A8666Obj *o = m_8[m_14];
	if (o == 0) {
		Run5(5);
		return;
	}
	if (m_942 != 0)
		return;
	m_942 = 1;
	if ((o->m_40 & 8) == 0)
		return;
	if (m_8[m_18] == 0) {
		Run5(5);
		return;
	}
	if (m_25 == 0)
		return;
	if (m_24 == 0)
		return;
	Check();
	Run5(3);
}
