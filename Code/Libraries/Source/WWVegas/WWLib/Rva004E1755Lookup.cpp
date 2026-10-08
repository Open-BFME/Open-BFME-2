// cl: /Ireference/shims/bfme2_ascii /MD
//
// Dump-range-25 string-keyed lookup trio on Rva00319CED (whose rowed layout
// is pad[0x2C] plus AsciiString m_2C): 0x4E1755 returns the rowed-pinned
// BfmeY1038 int for a non-empty key's lookup hit, 0x4E23C1 returns the
// 0x3B8E89 lookup hit itself when the rowed 0x319CED check passes, and
// 0x4E23E2 maps a wide-enough [m_40..m_44) span through the rowed indexed
// get plus rowed 0x37DC52 tail. Retail 0x004E1755 43B, 0x004E23C1 33B,
// 0x004E23E2 42B. The 0x3B8E89 host lookup is pinned as an honest
// address-derived candidate; the global uses the defined-g_00E02D6C idiom.

#include "ascii_string.h"

class Rva003B8BAA;
class Rva00E02D6C; extern Rva00E02D6C *TheCampaignManager;	// defined once, in Rva002B47B1Get.cpp

class Rva00319CED
{
public:
	bool rva00319CED();

	int rva004E1755();
	void *rva004E23C1();
	void *rva004E23E2();

private:
	unsigned char m_00[0x2C];
	AsciiString m_2C;
};

class Rva003B8E89
{
public:
	void *rva003B8E89(void *key);
};

class BfmeY1038
{
public:
	int bfmeVal1038();
};

class Rva0040CB2CIndexedField
{
public:
	int get(int index) const;
};

class Rva0037DCA5
{
public:
	void *rva0037DC52();
};

struct Rva004E23E2Pair
{
	char m_pad[0x40];
	int m_40;
	int m_44;
};

// ?rva004E1755@Rva00319CED@@QAEHXZ @0x004E1755 43B.
int Rva00319CED::rva004E1755()
{
	AsciiString *s = &m_2C;
	if (s->isEmpty())
		return 0;
	void *found = ((Rva003B8E89 *)((Rva003B8BAA *)TheCampaignManager))->rva003B8E89(s);
	if (found != 0)
		return ((BfmeY1038 *)found)->bfmeVal1038();
	return 0;
}

// ?rva004E23C1@Rva00319CED@@QAEPAXXZ @0x004E23C1 33B.
void *Rva00319CED::rva004E23C1()
{
	char *p = (char *)this;
	if (!rva00319CED())
		return 0;
	p += 0x2C;
	return ((Rva003B8E89 *)((Rva003B8BAA *)TheCampaignManager))->rva003B8E89(p);
}

// ?rva004E23E2@Rva00319CED@@QAEPAXXZ @0x004E23E2 42B.
void *Rva00319CED::rva004E23E2()
{
	Rva004E23E2Pair *p = (Rva004E23E2Pair *)rva004E23C1();
	if (p == 0)
		return 0;
	int diff = p->m_44 - p->m_40;
	if ((diff & ~7) == 0)
		return 0;
	int index = ((Rva0040CB2CIndexedField *)p)->get(0);
	return ((Rva0037DCA5 *)index)->rva0037DC52();
}
