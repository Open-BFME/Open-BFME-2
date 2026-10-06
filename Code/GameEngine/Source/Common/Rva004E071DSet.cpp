// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva004E071D@Rva004E071D@@QAEX_N@Z @0x004E071D 36B
// Setter with vcall side effect: if (v == m_50) return; m_50 = v; p = m_2C;
// if (!p) return; v ? p->v3() (slot 0xC) : p->v4() (slot 0x10).
// Evidence: unlock lane; caller at 0x002B7740 tests al; neighbours share
// +0x2C vcall target (Rva004E0741VCalls /O1) and byte field at +0x50.
class Rva004E071DTarget
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
};

class Rva004E071D
{
public:
	void rva004E071D(bool v);
	char m_pad0[0x2c];
	Rva004E071DTarget *m_ptr;
	char m_pad1[0x20];
	unsigned char m_flag;
};
void Rva004E071D::rva004E071D(bool v)
{
	if ((unsigned char)v == m_flag)
		return;
	m_flag = (unsigned char)v;
	Rva004E071DTarget *p = m_ptr;
	if (p == 0)
		return;
	if (v)
		p->v3();
	else
		p->v4();
}
