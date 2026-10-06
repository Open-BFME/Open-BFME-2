// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Ported from Open-BFME-1 GameEngine/Source/Common/BfmeOneHundredSixteen.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?bfmeReset@Gen_00490F00@@QAEXXZ 0x00355F75 (48B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
// One more: the five-row reset, three rows cleared and two set to nothing
// found.

class Gen_00490F00
{
public:
	void bfmeReset(void);
private:
	int m_bfmeGap[2];							// +0x00
	int m_bfmeCount;							// +0x08
	int m_bfmeGap2;								// +0x0c
	int m_bfmeFirst[8];							// +0x10
	int m_bfmeSecond[8];						// +0x30
	int m_bfmeThird[8];							// +0x50
	int m_bfmeFourth[8];						// +0x70
	int m_bfmeFifth[8];							// +0x90
	int m_bfmeA;								// +0xb0
	int m_bfmeB;								// +0xb4
};

void Gen_00490F00::bfmeReset(void)
{
	m_bfmeCount = 0;

	for (int index = 0; index < 8; ++index)
	{
		m_bfmeFirst[index] = 0;
		m_bfmeSecond[index] = 0;
		m_bfmeThird[index] = 0;
		m_bfmeFourth[index] = -1;
		m_bfmeFifth[index] = -1;
	}

	m_bfmeA = 0;
	m_bfmeB = 0;
}
