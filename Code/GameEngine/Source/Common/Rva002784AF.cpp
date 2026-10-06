// cl: /MD
class Rva002784AFVirt
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0C();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1C();
	virtual int v20();
};
struct Rva002784AFInner
{
	Rva002784AFVirt *m_vtab;
	unsigned char m_pad[0x254 - 4];
	Rva002784AFVirt *m_254holder;
};
// Actually inner at +0xFC points to struct with m_254 at +0x254? No.
// Simplify: Mid is at +0xFC, Inner is Mid->m_254? Let's define directly:
struct Rva002784AFMid
{
	unsigned char m_pad[0x254];
	Rva002784AFVirt *m_254obj;
};
class Rva00278440Host
{
public:
	void rva00278440(int v);
};
class Rva002784AFHost : public Rva00278440Host
{
public:
	void rva002784AF();
private:
	unsigned char m_padFC[0xFC];
	Rva002784AFMid *m_FC;
	unsigned char m_pad447[0x447 - 0x100];
	unsigned char m_447;
	unsigned char m_448;
	unsigned char m_449;
	unsigned char m_44A;
};
// ?rva002784AF@Rva002784AFHost@@QAEXXZ
void Rva002784AFHost::rva002784AF()
{
	if (m_447 == 0 || m_448 == 0 || m_44A == 0)
		return;
	int v = 0;
	Rva002784AFMid *p = m_FC;
	if (p != 0)
		v = p->m_254obj->v20();
	rva00278440(v);
}
