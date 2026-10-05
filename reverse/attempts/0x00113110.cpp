// ?rva00113110@Rva00113110Holder@@QAEXH@Z
// partial score=0.85 date=2026-10-05
// cl: /O1 /DNDEBUG /MD
//
// ?rva00113110@Rva00113110Holder@@QAEXH@Z @0x00113110 65B.
// Retail (this=esi, 1 int arg v -> edi): if (m_5C==0) return; if (v)
// ++[v+4]; cur=m_5C; if (cur) { if (--[cur+4]==0) cur->~Rva (slot0);
// m_5C=(Ref*)v; } if (m_60) this->rva00112898(0,0,m_58) via pin 0x00112898.
// Refcount at +4, dtor slot0, no free. Names opaque; pin proves nothing.
class Rva00113110Ref
{
public:
	virtual ~Rva00113110Ref();
	int m_ref04; // +0x04
};

class Rva00113110Holder
{
public:
	void rva00113110(int v);
	void rva00112898(int a, int b, void *c);
private:
	char m_pad00[0x58];
	void *m_58; // +0x58
	Rva00113110Ref *m_5C; // +0x5C
	unsigned char m_60; // +0x60
};

void Rva00113110Holder::rva00113110(int v)
{
	if (!m_5C)
		return;
	Rva00113110Ref *nv = (Rva00113110Ref *)v;
	if (nv)
		++nv->m_ref04;
	Rva00113110Ref *cur = m_5C;
	if (cur) {
		if (--cur->m_ref04 == 0)
			cur->~Rva00113110Ref();
		m_5C = nv;
	}
	if (m_60)
		rva00112898(0, 0, m_58);
}
