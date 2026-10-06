// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/Common
//
// ?get@Rva007AECC0Slot@@QAEHI@Z 0x00108980, 22 bytes.
//
// Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/Rva007AECC0Slot.cpp
// (reference/open-bfme-1 @ 6d943426), recompiled /Os. The body is
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text), where BFME 1's own flags do not.
//
// A sibling file Code/GameEngine/Source/Common/Rva007AECC0Slot.cpp already
// holds the matched ?set@Rva007AECC0Slot@@QAEXIH@Z at 0x0010896A, so this is a
// separate TU rather than an edit to a file this work does not own. It carries
// the same private view of the class; only this one body is defined here, since
// defining the donor's other two members again would duplicate ?set and leave
// ?getPair undeclared in the ledger.
//
// The slot holds an array of item pointers at +0x58; each item carries its
// value at +0x68. Identity is not recovered; the name is address-derived.

struct Rva007AECC0Item
{
	char m_pad[0x68];
	int m_value;
	int m_6c;
	int m_70;
};

class Rva007AECC0Slot
{
public:
	void set(unsigned int index, int value);
	int get(unsigned int index);
	void getPair(unsigned int index, int *a, int *b);

	char m_pad[0x58];
	Rva007AECC0Item *m_items[1];
};

// ?get@Rva007AECC0Slot@@QAEHI@Z 0x00108980
int Rva007AECC0Slot::get(unsigned int index)
{
	Rva007AECC0Item *item = m_items[index];
	if (item)
		return item->m_value;
	return 0;
}