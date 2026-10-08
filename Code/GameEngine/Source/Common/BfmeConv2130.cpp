// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Ported from Open-BFME-1 GameEngine/Source/Common/BfmeConv2130.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?bfmeVisitABG@BfmeHostABG@@QAEXPAX0@Z 0x0036E22F (58B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
class BfmeR1094;

// The probe is the rowed Object::getControllingPlayer.
class Player;
class Object
{
public:
	Player *getControllingPlayer() const;
};

class BfmeK1094
{
public:
	void bfmeApplyABG(void *a, void *b);
};

struct BfmeNodeABG
{
	BfmeNodeABG *m_bfmeNextABG;
	BfmeNodeABG *m_bfmePrevABG;
	BfmeK1094 *m_bfme08ABG;
};

class BfmeHostABG
{
public:
	void bfmeVisitABG(void *a, void *b);

	unsigned char m_bfmeHeadABG[4];
	BfmeNodeABG *m_bfme04ABG;
};

void BfmeHostABG::bfmeVisitABG(void *a, void *b)
{
	for (BfmeNodeABG *n = m_bfme04ABG->m_bfmeNextABG; n != m_bfme04ABG; n = n->m_bfmeNextABG)
	{
		BfmeK1094 *it = n->m_bfme08ABG;

		if (((const Object *)it)->getControllingPlayer() != 0)
		{
			it->bfmeApplyABG(a, b);
			return;
		}
	}
}
