// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Ported from Open-BFME-1 GameEngine/Source/Common/BfmeConv511.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?bfmeGoBQA@BfmeThingBQA@@QAEHXZ 0x0045A199 (29B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
class BfmeThingBQA
{
public:
	void bfmeStepBQA();
	int bfmeGoBQA();
	unsigned char m_bfmeHead[0x24];
	int *m_bfmeBegin;
	int *m_bfmeEnd;
	unsigned char m_bfmeGap[4];
	bool m_bfmeReady;
};

int BfmeThingBQA::bfmeGoBQA()
{
	if (!m_bfmeReady)
	{
		bfmeStepBQA();
		m_bfmeReady = true;
	}
	return m_bfmeEnd - m_bfmeBegin;
}
