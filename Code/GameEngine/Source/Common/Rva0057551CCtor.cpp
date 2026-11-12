// cl: /MD
// ??0Rva0057551C@@QAE@PAX00@Z @0x0057551C (36B):
// Ctor with manual vtable: m10=0 via and, m4/m8/mC from args, vtable
// 0x00C6E614 stored 4th (after m10/m4/m8, before mC) to match retail order.
// No virtuals (manual void* vtable, absolute VA per Snapshot precedent) so no
// implicit vptr store. Called after new(0x14) at 0x00575CB3 with (ptr,arg,0);
// result fed to setter @0x00575674. Unblocks 0x00575CAE. Honest-address name.

class Rva0057551C
{
public:
	Rva0057551C(void *a, void *b, void *c);

private:
	void *m_vtable;
	void *m_04;
	void *m_08;
	void *m_0c;
	int m_10;
};

// Retail table 0x00C6E614 (12-byte row): [0x00575700, 0x00575DFE, 0]. Own the
// complete initialized table instead of a zero-filled stand-in (the
// Rva004DF324Dtor.cpp s_10 precedent): slot 0 is the rowed deleting destructor
// reached only from this table, slot 1 the rowed 0x00575DFE body. Both are taken
// by address and never called through these erased signatures; the class
// identity is unknown.
extern "C" {
void __identifier("??_GRva0057571C@@QAEPAXI@Z")();
void __identifier("?rva00575DFE@Rva00575DFE@@QAEXXZ")();
}
void *g_00C6E614[3] = {
	(void *)&__identifier("??_GRva0057571C@@QAEPAXI@Z"),
	(void *)&__identifier("?rva00575DFE@Rva00575DFE@@QAEXXZ"),
	0
};

Rva0057551C::Rva0057551C(void *a, void *b, void *c)
{
	m_10 = 0;
	m_04 = a;
	m_08 = b;
	m_vtable = (void *)g_00C6E614;
	m_0c = c;
}
