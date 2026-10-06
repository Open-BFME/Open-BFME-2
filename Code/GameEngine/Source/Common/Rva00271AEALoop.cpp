// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva00271AEA@Rva00271AEA@@QAEXXZ retail 0x00271AEA 25 bytes.
// Null-terminated array loop at +0x14C calling virtual slot 0x3C on each.
// Unblocks 0x00293E64. Prev/next in Common with /O1.
// Evidence: caller 0x00293E9D plus array +0x14C plus slot 0x3C.

class LoopElem
{
public:
	virtual void s00();
	virtual void s04();
	virtual void s08();
	virtual void s0C();
	virtual void s10();
	virtual void s14();
	virtual void s18();
	virtual void s1C();
	virtual void s20();
	virtual void s24();
	virtual void s28();
	virtual void s2C();
	virtual void s30();
	virtual void s34();
	virtual void s38();
	virtual void slot3C();
};

class Rva00271AEA
{
public:
	void rva00271AEA();

private:
	unsigned char m_pre[0x14C];
	LoopElem **m_array;
};

void Rva00271AEA::rva00271AEA()
{
	for (LoopElem **p = m_array; *p; ++p)
		(*p)->slot3C();
}
