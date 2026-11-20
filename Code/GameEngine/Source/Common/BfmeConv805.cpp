// Two tiny accessors through held sub-objects, plus the ECMa factory.
//
// BFME1 byte-identical donor (reference/open-bfme-1
// Code/GameEngine/Source/Common/BfmeConv805.cpp); trimmed to the three
// bodies the sweep places. The donor's ECJ defs are omitted.

class Rva007EAA70Owner
{
public:
	void prepare();
};
struct BfmeHeldECKa
{
	unsigned char m_bfmeHead[0x280];
	void *m_bfmeX;
};

struct BfmeThingECKa
{
	void *bfmeGoECKa();
	unsigned char m_bfmeHead[4];
	BfmeHeldECKa *m_bfmeP;
};

void *BfmeThingECKa::bfmeGoECKa()
{
	((Rva007EAA70Owner *)m_bfmeP)->prepare();
	return m_bfmeP->m_bfmeX;
}

class Rva007EAB40Owner
{
public:
	void prepare();
};
struct BfmeHeldECKb
{
	unsigned char m_bfmeHead[0x29c];
	void *m_bfmeX;
};

struct BfmeThingECKb
{
	void *bfmeGoECKb();
	unsigned char m_bfmeHead[4];
	BfmeHeldECKb *m_bfmeP;
};

void *BfmeThingECKb::bfmeGoECKb()
{
	((Rva007EAB40Owner *)m_bfmeP)->prepare();
	return m_bfmeP->m_bfmeX;
}

class BfmeThingECMa
{
public:
	BfmeThingECMa *bfmeCtorECMa();
};

void *__cdecl bfmeAllocECMa(unsigned int n);

BfmeThingECMa *bfmeGoECMa()
{
	void *p = bfmeAllocECMa(0x48);
	if (p)
		return ((BfmeThingECMa *)p)->bfmeCtorECMa();
	return 0;
}
