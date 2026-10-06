// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva000687B8@Rva000687B8@@QAEXXZ retail 0x000687B8 55B unlock lane.
// Evidence: releases ref-counted holders at +0x37A4/+0x37A8 (dec ref at +4,
// virtual slot0 if zero, then and-zero); caller at 0x00069347 unclaimed.
struct RefObj000687B8
{
	virtual void v0();
	int m_ref;
};

class Rva000687B8
{
public:
	void rva000687B8();
private:
	unsigned char m_pad[0x37A4];
	RefObj000687B8 *m_a;
	RefObj000687B8 *m_b;
};

void Rva000687B8::rva000687B8()
{
	RefObj000687B8 *a = m_a;
	if (a)
	{
		if (--a->m_ref == 0)
			a->v0();
		m_a = 0;
	}
	RefObj000687B8 *b = m_b;
	if (b)
	{
		if (--b->m_ref == 0)
			b->v0();
		m_b = 0;
	}
}
