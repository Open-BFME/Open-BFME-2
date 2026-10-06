// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0006933D@Rva0006933D@@QAEHXZ @0x0006933D 113B
// Chain from 0x000687B8: calls rowed 0x00067878 then 0x000687B8 on same this,
// releases holder at +0x3818, clears BfmeResetTextureRef at +0x381C/+0x3828/
// +0x3838/+0x3844, releases holder at +0x37C0. Evidence: chain lane; callees
// rowed Rva00067878Clear Rva000687B8 BfmeResetTextureRefClear; neighbours
// share /O1; layout extends Rva000686F2/Rva000687B8 class to 0x3848.
struct RefObj0006933D
{
	virtual void v0();
	int m_ref;
};
struct BfmeResetResource;
struct BfmeResetTextureRef
{
	BfmeResetResource *pointer;
	void clear();
};
class Rva00067878
{
public:
	void rva00067878();
};
class Rva000687B8
{
public:
	void rva000687B8();
};
class Rva0006933D
{
public:
	int rva0006933D();
private:
	unsigned char m_pad0[0x37C0];
	RefObj0006933D *m_37c0;
	unsigned char m_pad1[0x54];
	RefObj0006933D *m_3818;
	BfmeResetTextureRef m_381c;
	unsigned char m_pad2[0x8];
	BfmeResetTextureRef m_3828;
	unsigned char m_pad3[0xC];
	BfmeResetTextureRef m_3838;
	unsigned char m_pad4[0x8];
	BfmeResetTextureRef m_3844;
};
int Rva0006933D::rva0006933D()
{
	((Rva00067878 *)this)->rva00067878();
	((Rva000687B8 *)this)->rva000687B8();
	RefObj0006933D *a = m_3818;
	if (a)
	{
		if (--a->m_ref == 0)
			a->v0();
		m_3818 = 0;
	}
	m_381c.clear();
	m_3828.clear();
	m_3838.clear();
	m_3844.clear();
	RefObj0006933D *b = m_37c0;
	if (b)
	{
		if (--b->m_ref == 0)
			b->v0();
		m_37c0 = 0;
	}
	return 0;
}
