// A state reset plus sink send (trimmed from a five-body donor; the other
// four are declared-only here).
//
// The T2 body needs one ledger pin (bfmeSend1028 at 0x0066F170).

class BfmeSink1028
{
public:
	void bfmeSend1028(int a, int *b, int *c);
};

struct BfmeOwn1028
{
	char m_bfmePad[0x20];
	BfmeSink1028 *m_bfmeSink;
};

class BfmeH1028
{
public:
	void bfmeGo1028H(void);

	char m_bfmePad[4];
	BfmeOwn1028 *m_bfmeOwner;
	int m_bfmeA;
	int m_bfmeB;
	char m_bfmePad2[0x3c];
	int m_bfmeState;
	char m_bfmePad3[0x10];
	int m_bfmeArg;
};

// ?bfmeGo1028H@BfmeH1028@@QAEXXZ
void BfmeH1028::bfmeGo1028H(void)
{
	m_bfmeState = -2;
	m_bfmeOwner->m_bfmeSink->bfmeSend1028(m_bfmeArg, &m_bfmeB, &m_bfmeA);
}

void __stdcall bfmeGo1028B(int a);
