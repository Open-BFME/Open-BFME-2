// cl: /O1

// Capped 36-item list at 0x00548FD4 (45 bytes, ghidra FUN_00948fd4).
// Leaf thiscall: clears the item's state word, appends the item while fewer
// than 36 are stored, then marks the list dirty. Retail emits `and [esi+0x410],0`
// (not a folded mov) plus `lea eax,[ecx+0x120]` for the count access, which is
// the /O1 shape; /O2 folds the AND and re-derives the count address directly.

struct Rva00548FD4Item
{
	char m_pad[0x410];				// +0x000..+0x410 unknown
	int m_state;					// +0x410 cleared on insert
};

class Rva00548FD4ItemList
{
public:
	void add(Rva00548FD4Item *item);

private:
	char m_pad0[0x120];				// +0x000..+0x120 unknown
	int m_count;					// +0x120
	Rva00548FD4Item *m_items[36];	// +0x124
	char m_pad1[4];					// +0x1B4..+0x1B8 unknown
	bool m_dirty;					// +0x1B8
};

// ?add@Rva00548FD4ItemList@@QAEXPAURva00548FD4Item@@@Z
void Rva00548FD4ItemList::add(Rva00548FD4Item *item)
{
	item->m_state &= 0;

	if (m_count < 36)
	{
		m_items[m_count] = item;
		++m_count;
	}

	m_dirty = false;
}
