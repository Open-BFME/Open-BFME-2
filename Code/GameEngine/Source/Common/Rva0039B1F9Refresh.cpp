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

private:
	char m_pad00[0x4];
	BfmeEFCSource *m_src04;
	float m_f8;
};

void BfmeThingEFC::rva0039B1F9(void)
{
	m_f8 = bfmeCalcEFC(m_src04->m_val24);
}
