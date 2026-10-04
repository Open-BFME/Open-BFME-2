// cl: /O1 /arch:SSE /MD
// ?rva00417AB8@Rva00417AB8@@QAEPAV1@XZ @0x00417AB8 43B.
// Unlock lane: thiscall init (ret, no args) writing +0x00=0 (and [m],0 under
// /O1), +0x04=0xF4240, +0x08=0x0A, +0x0c/+0x10/+0x14=float from global
// g_Va00BBB8D8 via single movss load. Evidence: caller at 0x00417FFB in
// FUN_00817ff0; movss needs /arch:SSE; landing unblocks 0x00417FF0.
extern float g_Va00BBB8D8; // ?g_Va00BBB8D8@@3MA

class Rva00417AB8
{
public:
	Rva00417AB8 *rva00417AB8();
private:
	int m_00; // +0x00
	int m_04; // +0x04
	int m_08; // +0x08
	float m_0c; // +0x0c
	float m_10; // +0x10
	float m_14; // +0x14
};

Rva00417AB8 *Rva00417AB8::rva00417AB8()
{
	float v = g_Va00BBB8D8;
	Rva00417AB8 *p = this;
	p->m_00 = 0;
	p->m_04 = 0xF4240;
	p->m_08 = 0x0A;
	p->m_0c = v;
	p->m_10 = v;
	p->m_14 = v;
	return p;
}
