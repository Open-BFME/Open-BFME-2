// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
//
// ?bfmeGoLD@@YAXPAVBfmeKeyLC@@I@Z
// retail 0x003226BF, 40 bytes. Dedicated TU ported from the Open-BFME-1
// donor game/GameEngine/Source/Common/BfmeConv903.cpp. Recompiled /Os the
// donor body is byte-identical to retail once relocations are masked (unique
// hit on unclaimed .text). Only the placed body is defined here; the donor's
// other definitions are omitted.
struct BfmeNodeLC;

struct BfmeNodeLC
{
	char m_bfmePad[0xc];
	unsigned int m_bfmeBits;
	char m_bfmePad2[4];
	BfmeNodeLC *m_bfmeLink;
};

class BfmeKeyLC
{
public:
	BfmeNodeLC *bfmeFindLC();
};

void bfmeGoLD(BfmeKeyLC *k, unsigned int mask)
{
	if (k) {
		BfmeNodeLC *o = k->bfmeFindLC();
		if (o) {
			unsigned int m = ~mask;
			o->m_bfmeBits = o->m_bfmeBits & m;
			BfmeNodeLC *p = o->m_bfmeLink;
			if (p)
				p->m_bfmeBits = o->m_bfmeBits;
		}
	}
}