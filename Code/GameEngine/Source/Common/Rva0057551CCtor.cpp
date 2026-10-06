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

Rva0057551C::Rva0057551C(void *a, void *b, void *c)
{
	m_10 = 0;
	m_04 = a;
	m_08 = b;
	m_vtable = (void *)0x00C6E614;
	m_0c = c;
}
