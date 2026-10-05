// cl: /O2 /MD /EHsc
// BfmeThingCGD::bfmeOneCGD, retail 0x00758D10, 193B. Sibling definition lives
// in BfmeConv597.cpp, which already carries the rowed 41B bfmeGoCGD driver
// (0x0075A490) that calls this; the two units agree on one class layout.
//
// The class declares bfmeOneCGD and bfmeTwoCGD but defines neither. This file
// supplies bfmeOneCGD only; bfmeTwoCGD remains the missing 333B provider that
// keeps the home unlinked, and it is NOT claimed here.
//
// Target proof: Ghidra entry 0x00758D10/193, and the only observed native
// entry call at 0x0075A49F lies inside that already byte-verified driver.
// The receiver table at +0xAE10 with 0x493 buckets, the active list at
// +0xC05C, index +0xC064, cursor +0xC068, node links +0x2C/+0x30 and the
// subobject flags at +0x04/+0x10 are target instruction facts, read straight
// off the native body.
//
// BfmeThingCGD and the node/sub-object names are address-derived placeholders:
// retail ties no string, vtable slot or BFME helper to them. The original
// subsystem, class and flag meanings stay unproven. Only the two list links
// carry a role name, being the intrusive-hash-chain idiom already landed in
// Rva009A3770HashChainInsert.cpp and Rva009A2BE0HashIterNext.cpp.
//
// Whole clean BFME1 donor game/Libraries/Source/collisionmanager/
// BfmeConv597.cpp at revision 6583b3c1ff21db4a561285717028fdafc780b7db,
// final /O2. Donor comments describe BFME1 addresses, not target facts.

struct Rva009A2FE0Node;

struct Rva009A2FE0Sub
{
	unsigned char m_pad0[4];
	unsigned m_bfme04;
	unsigned char m_pad8[8];
	unsigned m_bfme10;
};

struct Rva009A2FE0Node
{
	Rva009A2FE0Sub *m_bfme00;
	Rva009A2FE0Sub *m_bfme04;
	unsigned char m_pad8[8];
	unsigned m_bfme10;
	unsigned char m_pad14[0x18];
	Rva009A2FE0Node **m_backSlot;
	Rva009A2FE0Node *m_next;
};

class BfmeThingCGD
{
public:
	void bfmeOneCGD();
	void bfmeTwoCGD();
	void bfmeGoCGD();
	void *m_bfmeFirst;
	unsigned char m_bfmeGap[0xae10 - 4];
	Rva009A2FE0Node *m_buckets[0x493];
	Rva009A2FE0Node *m_active;
	int m_index;
	Rva009A2FE0Node *m_cur;
	unsigned char m_bfmeGap1[0xc06d - 0xc068];
	bool m_bfmeBusy;
};

void bfmeGlobalCGD();

// Walk the 0x493-slot table at this+0xAE10 from the cursor at this+0xC064 and
// move every node out of its bucket chain and onto the second list at this+0xC05C
// according to the two sub-object flags.
void BfmeThingCGD::bfmeOneCGD()
{
	Rva009A2FE0Node *nil = 0;
	Rva009A2FE0Node **curp = &m_cur;

	m_index = 0;
	m_cur = m_buckets[0];
	for (;;)
	{
		while (m_cur == nil)
		{
			int i = m_index + 1;

			if (i == 0x493)
				return;
			m_index = i;
			m_cur = m_buckets[i];
		}

		Rva009A2FE0Node *n = m_cur;

		m_cur = m_cur->m_next;
		if (n == nil)
			return;

		if (n->m_bfme00->m_bfme10 == 0 && n->m_bfme04->m_bfme10 == 0)
			continue;

		if (n->m_bfme00->m_bfme04 == 0 || n->m_bfme04->m_bfme04 == 0)
		{
			if (*curp == n)
				*curp = (*curp)->m_next;
			if (n->m_next != nil)
				n->m_next->m_backSlot = n->m_backSlot;
			*n->m_backSlot = n->m_next;
			n->m_backSlot = (Rva009A2FE0Node **)nil;
			n->m_next = m_active;
			m_active = n;
		}
		else
		{
			n->m_bfme10 = 0;
		}
	}
}
