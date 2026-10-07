// ?rva000E1341@Rva000E1341@@QAEXXZ
// partial score=0.99 date=2026-10-07
// cl: /O1 /G7 /DNDEBUG /MD
// ?rva000E1341@Rva000E1341@@QAEXXZ @0x000E1341 102B.
// Clears GlobalData bytes +0x3C and +0x48, then calls FillFourSlots on
// each 0xD4 record. Index is inner * outerCount + outer.

extern void *g_00DFE758;

struct Rva0011216CSlotQuartet
{
	char m_pad[0xD4];
	void FillFourSlots();
};

class Rva000E1341
{
public:
	void rva0006B804();
	void rva000E1341();

	char m_pad[0x3888];
	Rva0011216CSlotQuartet *m_base;
	int m_gap;
	int m_outer;
	int m_inner;
};

void Rva000E1341::rva000E1341()
{
	rva0006B804();
	((unsigned char *)g_00DFE758)[0x3C] = 0;
	unsigned char *globalData = (unsigned char *)*(void *volatile *)&g_00DFE758;
	int outer = 0;
	reinterpret_cast<volatile unsigned char *>(globalData)[0x48] = 0;
	for (; outer < m_outer; ++outer)
	{
		for (int inner = 0; inner < m_inner; ++inner)
			m_base[inner * m_outer + outer].FillFourSlots();
	}
}
