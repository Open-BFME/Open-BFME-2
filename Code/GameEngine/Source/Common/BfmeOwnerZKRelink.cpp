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

// Measured target prefixes used by the move helper below. These Bfme names
// are donor ABI views, not recovered original class identities.
class BfmeKeyZK
{
public:
	unsigned char m_head[0x2C];
	unsigned char m_table[4];
};

struct BfmeEntryZK
{
	unsigned char m_head[0x0E];
	short m_references;
	unsigned char m_tail[4];
};

class Rva003B573E
{
public:
	int rva003B820D(Rva003B573E *other, int index);
	unsigned char m_head[0x0C];
	BfmeEntryZK *m_records;
};

struct BfmeNodeZK
{
	BfmeNodeZK *m_bfmeNextZK;
	int m_bfmeIdZK;
	int m_bfmeKindZK;
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
private:
	unsigned char m_head[0x2C];
	Rva003B573E m_table;
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

// From BFME 1 BfmeConv1878.cpp at verified donor revision
// 968ca36c3265b295297e6aed45a6bd89ffe59c40. Target boundary is independently
// 0x003B847B..0x003B84C9 (RET 12); the existing relink body calls it.
// Native reads prove the table at +0x2C, its records at +0x38, the 0x14
// record stride and the signed short at +0x0E. The native first call is the
// independently verified 0x003B820D transfer; only that donor callee view
// changes here. Node words at +0/+4/+8 follow the three native stores.
void BfmeOwnerZK::bfmeMoveZK(BfmeKeyZK *key, BfmeNodeZK **from, BfmeNodeZK **to)
{
	int id = (*from)->m_bfmeIdZK;
	int index = m_table.rva003B820D((Rva003B573E *)key->m_table, id);
	if (index == -1)
		return;
	(*from)->m_bfmeIdZK = index;
	(*from)->m_bfmeKindZK = m_table.m_records[index].m_references;
	BfmeNodeZK *next = (*from)->m_bfmeNextZK;
	(*from)->m_bfmeNextZK = *to;
	*to = *from;
	*from = next;
}
