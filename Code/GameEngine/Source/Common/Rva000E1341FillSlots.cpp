// cl: /O1 /G7 /DNDEBUG /MD
// ?rva000E1341@Rva000E1341@@QAEXXZ @0x000E1341 102B.
// Clears GlobalData bytes +0x3C and +0x48, then calls FillFourSlots on
// each 0xD4 record. Index is inner * outerCount + outer.
// The record walk follows the rowed BaseHeightMapRenderObjClass::rva0006B804 setup
// call (0x0006B804), so the class derives from it; the second GlobalData byte is
// cleared with a plain store before the loop counter's own declaration.

class GlobalData;
extern GlobalData *TheWritableGlobalData;

struct Rva0011216CSlotQuartet
{
	char m_pad[0xD4];
	void FillFourSlots();
};

class BaseHeightMapRenderObjClass
{
public:
	void rva0006B804();
	char m_pad[0x3888];
};

class Rva000E1341 : public BaseHeightMapRenderObjClass
{
public:
	void rva000E1341();

	Rva0011216CSlotQuartet *m_base;
	int m_gap;
	int m_outer;
	int m_inner;
};

void Rva000E1341::rva000E1341()
{
	rva0006B804();
	((unsigned char *)TheWritableGlobalData)[0x3C] = 0;
	unsigned char *globalData = (unsigned char *)*(void *volatile *)&TheWritableGlobalData;
	reinterpret_cast<unsigned char *>(globalData)[0x48] = 0;
	for (int outer = 0; outer < m_outer; ++outer)
	{
		for (int inner = 0; inner < m_inner; ++inner)
			m_base[inner * m_outer + outer].FillFourSlots();
	}
}
