// cl: /GX-
// ?rva00358D62@Rva00358D62@@QAEXPAURva00358D62Node@@@Z @0x00358D62 (53B):
// List clear with recursion on +0xc: for each node recurse on child, destroy
// embedded Rva0027EA49 at +0x10 via rowed dtor, free node via rowed _free,
// step to +0x8 next. Same this preserved in ebx across calls.
// Evidence: self-call 0x00358D74; callees rowed 0x0027EA49 0x00030830;
// callers 0x00358D74 0x00358E0B; unblocks 0x00358DFD.
extern "C" void __cdecl free(void *block);
struct Rva0027EA49
{
	~Rva0027EA49();
	int m_00;
	void *m_04;
};
struct Rva00358D62Node
{
	char m_00[8];
	Rva00358D62Node *m_08;
	Rva00358D62Node *m_0c;
	Rva0027EA49 m_10;
};
struct Rva00358D62Header
{
	char m_00[4];
	Rva00358D62Node *m_04;
	Rva00358D62Header *m_08;
	Rva00358D62Header *m_0c;
};
class Rva00358D62
{
public:
	void rva00358D62(Rva00358D62Node *node);
	void rva00358DFD();
private:
	Rva00358D62Header *m_00;
	int m_04;
};
void Rva00358D62::rva00358D62(Rva00358D62Node *node)
{
	if (node == 0)
		return;
	Rva00358D62Node *cur = node;
	do {
		rva00358D62(cur->m_0c);
		Rva00358D62Node *next = cur->m_08;
		cur->m_10.~Rva0027EA49();
		free(cur);
		cur = next;
	} while (cur != 0);
}
// ?rva00358DFD@Rva00358D62@@QAEXXZ @0x00358DFD (41B):
// Guarded reset: if count nonzero clear header list via rowed 0x00358D62 then
// self-link header and zero counts.
// Evidence: caller of rowed 0x00358D62 at 0x00358E0B; unblocks 0x00358F44 0x00358E26.
void Rva00358D62::rva00358DFD()
{
	if (m_04 == 0)
		return;
	rva00358D62(m_00->m_04);
	m_00->m_08 = m_00;
	m_00->m_04 = 0;
	m_00->m_0c = m_00;
	m_04 = 0;
}
