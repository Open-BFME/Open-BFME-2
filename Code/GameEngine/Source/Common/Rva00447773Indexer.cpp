// cl: /O1 /MD
// ?rva00447773@Rva00447773@@QAEPAXH@Z, retail 0x00447773, 33 bytes.
// Bounds-checked indexer returning &m_items[index] for 8 x 0x1D0 records at
// +0xDC else null. Evidence: unlock lane; __thiscall ret 4; callers at
// 0x00248DF1 0x00249950 0x004477A7 0x004483DA 0x004492E4; unblocks 0x00447794.
struct Rva00447773Elem { char data[0x1D0]; };
class Rva00447773 {
	char m_pad[0xDC];
	Rva00447773Elem m_items[8];
public:
	void *rva00447773(int index);
	void *rva00449522(int index);
};
void *Rva00447773::rva00447773(int index)
{
	if (index < 0 || index >= 8)
		return 0;
	return &m_items[index];
}

typedef bool Bool;

class GameSlot
{
public:
	Bool isHuman() const;
};

// Retail 0x00449522, 43 bytes. Human-gated row pointer over 0x1D0 records:
// the GameSlot at row+0xDC must be human, then the pointer at row+0x2A8 is
// returned, else null. Same stride family as the indexer above; callers in
// unclaimed 0x0044AAED. Unlock lane.

void *Rva00447773::rva00449522(int index)
{
	const volatile int &rowIndex = index;
	int off = rowIndex * 0x1D0;
	char *row = (char *)(off + (char *)this);
	GameSlot *slot = (GameSlot *)(row + 0xDC);
	if (slot->isHuman())
		return *(void **)(row + 0x2A8);
	return 0;
}
