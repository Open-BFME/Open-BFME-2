// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
//
// Three bodies from the Open-BFME-1 donor
// game/GameEngine/Source/Common/BfmeConv924.cpp, each recompiled /Os
// byte-identical to retail once relocations are masked (each a unique hit on
// unclaimed .text):
//
//   ?bfmeGo924E@@YAXPAVBfmeKeyLC@@I@Z  retail 0x00320626, 27 bytes
//   ?bfmeGo924A@@YAXPAVBfmeKeyLC@@D@Z  retail 0x00324894, 29 bytes
//   ?bfmeGo924B@@YAHPAVBfmeKeyLC@@@Z    retail 0x00327D1B, 30 bytes
//
// One TU for all three rather than three: they are the same shape over the
// same BfmeNodeLC, they share one preamble and one // cl: line, and splitting
// them would duplicate that preamble three times for no gain. The donor's
// other definitions (bfmeGo924C, bfmeGo924D, bfmeGo924F, bfmeGo924G and
// BfmeOne924G::bfmeCall924G) are omitted.
struct BfmeNodeLC
{
	char m_bfmeA;
	char m_bfmePad0[3];
	int m_bfmeB;
	char m_bfmePad1[4];
	unsigned int m_bfmeBits;
	unsigned short m_bfmeW;
	char m_bfmePad2[0x16];
	char m_bfmeC;
	char m_bfmePad3[3];
	int m_bfmeD;
};

class BfmeKeyLC
{
public:
	BfmeNodeLC *bfmeFindLC();
};

void bfmeGo924E(BfmeKeyLC *k, unsigned int mask)
{
	if (k) {
		BfmeNodeLC *o = k->bfmeFindLC();
		if (o) {
			unsigned int m = ~mask;
			o->m_bfmeBits = o->m_bfmeBits & m;
		}
	}
}

void bfmeGo924A(BfmeKeyLC *k, char v)
{
	if (k) {
		BfmeNodeLC *o = k->bfmeFindLC();
		if (o)
			*((char *)&o->m_bfmeBits + 3) = (v == 0);
	}
}

int bfmeGo924B(BfmeKeyLC *k)
{
	if (k) {
		BfmeNodeLC *o = k->bfmeFindLC();
		if (o && o->m_bfmeA)
			return o->m_bfmeB;
	}
	return 0x64;
}