// A ctor through an init helper and a queue pop.
//
// BFME1 byte-identical donor (reference/open-bfme-1
// Code/GameEngine/Source/Common/BfmeConv881.cpp); trimmed to the two T1
// bodies the sweep places.

struct BfmeThingEOE
{
	BfmeThingEOE *bfmeCtorEOE();
};

void __stdcall bfmeInitEOE(BfmeThingEOE *o, int a, int b, void (*ca)(), void (*cb)());
extern "C" void bfmeCbEOEa();
extern "C" void bfmeCbEOEb();

BfmeThingEOE *BfmeThingEOE::bfmeCtorEOE()
{
	bfmeInitEOE(this, 0x14, 8, bfmeCbEOEa, bfmeCbEOEb);
	return this;
}

struct BfmeQueueEOF
{
	unsigned char m_bfmeHead[4];
	void **m_bfmeEnd;
	unsigned char m_bfmePad[4];
	void **volatile m_bfmeCur;
};

class Object;

// The partition manager's range-query handle (iterateObjectsInRange
// 0x00625610 returns it): next() yields the payload's next hit, stepping
// the +0x0C cursor over 8-byte entries up to +0x04, or 0 when done. 43
// matched callers reference it by this name (pin 0x00045623).
struct BfmeWideResult
{
	Object *next();
	BfmeQueueEOF *m_bfmeQ;
};

Object *BfmeWideResult::next()
{
	BfmeQueueEOF *q = m_bfmeQ;
	if (q->m_bfmeCur == q->m_bfmeEnd)
		return 0;
	void **cur = q->m_bfmeCur;
	Object *v = (Object *)*cur;
	q->m_bfmeCur = cur + 2;
	return v;
}

// Retail's call sites in this unit's matched rows land on bodies rowed under
// other spellings at the same addresses (same ABI). Bind the spellings used here.
#pragma comment(linker, "/alternatename:?bfmeInitEOE@@YGXPAUBfmeThingEOE@@HHP6AXXZ1@Z=??_L@YGXPAXIHP6EX0@Z1@Z")
