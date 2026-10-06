// cl: /DNDEBUG /MD
// ?rva002150CE@Rva002150CE@@QAEXXZ @0x002150CE 51B reset.
// Evidence: leaf lane, called from 2 unclaimed Unwind sites, neighbours Rva00214D59Pack and Open2Destructors, SSE plus int zeros per disassembly.
class Rva002150CE
{
public:
	Rva002150CE *rva002150CE();
private:
	int m_00;
	int m_04;
	int m_08;
	char _pad0c[8];
	int m_14;
	char _pad18[72];
	int m_60;
	float m_64;
	float m_68;
	char _pad6c[4];
	int m_70;
	float m_74;
	float m_78;
	char _pad7c[24];
	int m_94;
};
Rva002150CE *Rva002150CE::rva002150CE()
{
	Rva002150CE *p = this;
	p->m_00 = 0;
	p->m_04 = 0;
	p->m_08 = 0;
	p->m_14 = 0;
	p->m_60 = 0;
	p->m_64 = 0.0f;
	p->m_68 = 0.0f;
	p->m_70 = 0;
	p->m_74 = 0.0f;
	p->m_78 = 0.0f;
	p->m_94 = 0;
	return p;
}
