// cl: /MD
// ?rva001FD458@Rva001FD458@@QAEXPAURva001FD458Node@@@Z @0x001FD458 45B.
// Tree erase for a second RB-tree family: recurse right via +0xC, free the
// node via rowed _free 0x00030830, walk left via +8, ret 4. Same 45B shape
// as the rowed Rva001FD42B erase 0x001FD42B (Rva001FD42BErase.cpp precedent).
// Self-recursive plus caller at 0x001FD667 in 0x001FD659; unblocks 0x001FD659.
extern "C" void __cdecl free(void *block);

struct Rva001FD458Node
{
	unsigned char m_color;
	unsigned char m_pad01[3];
	Rva001FD458Node *m_parent;
	Rva001FD458Node *m_left;
	Rva001FD458Node *m_right;
};

struct Rva001FD458
{
	void rva001FD458(Rva001FD458Node *x);
	void rva001FD659();
	Rva001FD458Node *m_header;
	unsigned int m_count;
};

void Rva001FD458::rva001FD458(Rva001FD458Node *x)
{
	while (x != 0) {
		rva001FD458(x->m_right);
		Rva001FD458Node *y = x->m_left;
		free(x);
		x = y;
	}
}

void Rva001FD458::rva001FD659()
{
	if (m_count != 0) {
		rva001FD458(m_header->m_parent);
		m_header->m_left = m_header;
		m_header->m_parent = 0;
		m_header->m_right = m_header;
		m_count = 0;
	}
}
