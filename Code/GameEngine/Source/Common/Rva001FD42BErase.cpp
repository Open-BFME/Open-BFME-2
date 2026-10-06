// cl: /MD
// ?rva001FD42B@Rva001FD42B@@QAEXPAURva001FD42BNode@@@Z @0x001FD42B 45B.
// Tree erase: recurse right via +0xC, free the node via rowed _free 0x00030830,
// walk left via +0x8, ret 4. Same 45B shape as Rva002CF32FErase precedent.
// Caller at 0x001FD63E unblocks 0x001FD630.
extern "C" void __cdecl free(void *block);

struct Rva001FD42BNode
{
	unsigned char m_pad00[8];
	Rva001FD42BNode *m_left;
	Rva001FD42BNode *m_right;
};

struct Rva001FD42B
{
	void rva001FD42B(Rva001FD42BNode *x);
};

void Rva001FD42B::rva001FD42B(Rva001FD42BNode *x)
{
	while (x != 0) {
		rva001FD42B(x->m_right);
		Rva001FD42BNode *y = x->m_left;
		free(x);
		x = y;
	}
}
