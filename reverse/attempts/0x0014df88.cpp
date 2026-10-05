// ?rva0014DF88@Rva0014DF88Holder@@QAEXPAURva0014DF88ArgHead@@PAX@Z
// partial score=0.75 date=2026-10-05
// cl: /O1 /DNDEBUG /MD
//
// ?rva0014DF88@Rva0014DF88Holder@@QAEXPBV2@0@Z placeholder (renamed below).
// @0x0014DF88 93B void, 3 virtual slot68 (idx26) paths, idiv/sar math.
// Retail (this=ecx Holder, 2 args ret 8): edx=m_1C; if (edx) { q=([edx+4]-
// [edx])/48; slot68([a1],a1,a2,q); } else if (m_10 && (c=m_14)) { s=
// ([c+4]-[c])/2; slot68([a1],a1,a2,s); } else slot68([a1],a1,a2,1).
// One 27-virtual iface (idx26, 3 args), no pins (all virtual).
// Names opaque.
class Rva0014DF88Iface
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void slot26(void *a, void *b, int c);
};

struct Rva0014DF88ArgHead
{
	Rva0014DF88Iface *m_iface00; // +0x00
};

struct Rva0014DF88Size
{
	int m_00; // +0x00
	int m_04; // +0x04
};

class Rva0014D440HolderPlaceholder {};

class Rva0014DF88Holder
{
public:
	void rva0014DF88(Rva0014DF88ArgHead *a1, void *a2);
private:
	char m_pad00[0x10];
	int m_10; // +0x10
	Rva0014DF88Size *m_14; // +0x14
	int m_18; // +0x18 gap (retail reads +0x1C next)
	Rva0014DF88Size *m_1C; // +0x1C
};

void Rva0014DF88Holder::rva0014DF88(Rva0014DF88ArgHead *a1, void *a2)
{
	Rva0014DF88Size *edx = m_1C;
	if (edx != 0) {
		int q = (edx->m_04 - edx->m_00) / 48;
		a1->m_iface00->slot26(a1, a2, q);
		return;
	}
	if (m_10 != 0) {
		Rva0014DF88Size *c = m_14;
		if (c != 0) {
			int s = (c->m_04 - c->m_00) / 2;
			a1->m_iface00->slot26(a1, a2, s);
			return;
		}
	}
	a1->m_iface00->slot26(a1, a2, 1);
}
