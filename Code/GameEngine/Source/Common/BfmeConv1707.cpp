// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Ported from Open-BFME-1 GameEngine/Source/Common/BfmeConv1707.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?bfmeShutdownFY@BfmeOwnerFY@@QAEXXZ 0x004CF8D5 (49B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
class BfmeSlotFY
{
public:
	void bfmeCloseFY(int flag);
};

class BfmeExtraFY
{
public:
	void bfmeFinishFY(void);
};

class BfmeOwnerFY
{
public:
	void bfmeShutdownFY(void);

	unsigned char m_bfmeHeadFY[4];
	BfmeSlotFY *m_bfmeSlotsFY[8];
	unsigned char m_bfmeMidFY[0x12000];
	BfmeExtraFY *m_bfmeExtraFY;
};

void BfmeOwnerFY::bfmeShutdownFY(void)
{
	for (int i = 0; i < 8; ++i)
	{
		if (m_bfmeSlotsFY[i] != 0)
			m_bfmeSlotsFY[i]->bfmeCloseFY(0);
	}

	if (m_bfmeExtraFY != 0)
		m_bfmeExtraFY->bfmeFinishFY();
}
