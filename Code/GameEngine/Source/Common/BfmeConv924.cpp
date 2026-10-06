// Open-BFME5 conversions (trimmed; only GadgetTextEntrySetMaxChars is placed, the rest is
// declared-only).

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

void bfmeGo924A(BfmeKeyLC *k, char v);
int bfmeGo924B(BfmeKeyLC *k);
int bfmeGo924C(BfmeKeyLC *k);
void bfmeGo924D(BfmeKeyLC *k, unsigned int mask);
void bfmeGo924E(BfmeKeyLC *k, unsigned int mask);

// ?GadgetTextEntrySetMaxChars@@YAXPAVBfmeKeyLC@@G@Z
void GadgetTextEntrySetMaxChars(BfmeKeyLC *k, unsigned short w)
{
	if (k) {
		BfmeNodeLC *o = k->bfmeFindLC();
		if (o)
			o->m_bfmeW = w;
	}
}

void bfmeGo924G(void);
