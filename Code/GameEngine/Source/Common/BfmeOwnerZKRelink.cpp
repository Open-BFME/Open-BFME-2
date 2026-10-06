// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/Common/BfmeOwnerZKRelink.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// BfmeOwnerZK::bfmeRelinkZK 0x003B8556 (51B). Callee addresses are read off
// retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.
// Retail RVA 0x0035DCF0. The body walks a singly linked list to find the slot
// that points at one node and then forwards to BfmeOwnerZK::bfmeMoveZK at
// 0x0035D940, which is what places it on that class.

class BfmeKeyZK;

struct BfmeNodeZK
{
	BfmeNodeZK *m_bfmeNextZK;
};

struct BfmeHeadZK
{
	int m_bfmePadZK;
	BfmeNodeZK *m_bfmeFirstZK;
};

class BfmeOwnerZK
{
public:
	void bfmeRelinkZK(BfmeKeyZK *key, BfmeHeadZK *list, BfmeNodeZK *node,
		BfmeHeadZK *fallback, BfmeNodeZK **where);
	void bfmeMoveZK(BfmeKeyZK *key, BfmeNodeZK **from, BfmeNodeZK **to);
};

void BfmeOwnerZK::bfmeRelinkZK(BfmeKeyZK *key, BfmeHeadZK *list, BfmeNodeZK *node,
	BfmeHeadZK *fallback, BfmeNodeZK **where)
{
	BfmeNodeZK **slot = &list->m_bfmeFirstZK;

	while (*slot != node)
	{
		if (*slot == 0)
			return;

		slot = &(*slot)->m_bfmeNextZK;
	}

	bfmeMoveZK(key, slot, where != 0 ? where : &fallback->m_bfmeFirstZK);
}
