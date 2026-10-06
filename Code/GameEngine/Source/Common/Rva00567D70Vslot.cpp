// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD
// ?rva00567D70@Rva00567960@@QAEXXZ @0x00567D70 38B
// vslot 3 (offset 0xC) of vtable 0x0086CEF0 (class Rva00567960).
// Evidence: ret no args thiscall; pin ?rva00567A6E@Rva00525E55@@QAEXH@Z 0x00567A6E; row ?rva005C394D@Rva005C394D@@QAEXXZ 0x005C394D; this+8 ptr plus this+0xC int then inner +0xC slot 0x18 returning target for tail jmp.
class Rva005C394D
{
public:
	void rva005C394D();
};

class Rva00567D70Inner
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual Rva005C394D *v18();
};

class Rva00525E55
{
public:
	void rva00567A6E(int a);
	char m_pad[12];
	Rva00567D70Inner *m_0c;
};

class Rva00567960
{
public:
	void rva00567D70();
	char m_pad00[8];
	Rva00525E55 *m_08;
	int m_0c;
};

void Rva00567960::rva00567D70()
{
	m_08->rva00567A6E(m_0c);
	Rva005C394D *p = m_08->m_0c->v18();
	if (p)
		p->rva005C394D();
}
