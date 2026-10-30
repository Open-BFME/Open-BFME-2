// cl: /DNDEBUG /MD /EHsc
// ?rva0039B1F9@BfmeThingEFC@@QAEXXZ @0x0039B1F9 19B refresh from source object
// at +0x04 via bfmeCalcEFC of its +0x24 into m_f8. Evidence: sole caller
// 0x0039B21F with no stack args; pin bfmeCalcEFC at 0x0039B145.

float __stdcall bfmeCalcEFC(int val);

struct BfmeEFCSource
{
	char m_pad00[0x24];
	int m_val24;
};

class BfmeThingEFC
{
public:
	void rva0039B1F9(void);
	void bfmeUpdate(int);
	char m_pad00[0x4];
	BfmeEFCSource *m_src04;
	float m_f8;
	int level;
};

void BfmeThingEFC::rva0039B1F9(void)
{
	m_f8 = bfmeCalcEFC(m_src04->m_val24);
}

// The retail call in this body reads 0x0039B145, an address the ledger already
// carries as ?bfmeAt@Rva0039AE75@@QBEMH@Z. Bind the donor spelling to that rowed owner so one
// address keeps one definition and the unit links.
#pragma comment(linker, "/alternatename:?bfmeCalcEFC@@YGMH@Z=?bfmeAt@Rva0039AE75@@QBEMH@Z")
