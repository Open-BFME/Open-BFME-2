// flags: region default (reverse/retail_inventory/flag_regions.csv)
// Retail RVA 0x0053FC81, 24 bytes.
// ?rva0053FC81@Rva0053FC81@@QAEPAV1@PAVRva0053F8E5DwordCounter@@@Z
// Ref-store setter at this+0x0 via rowed inc 0x0053F8E5: store new pointer
// then inc ref on non-null and return this. Callers 0x00540A88 0x005421AA.
// Prev disp8 inc / next div-avg getter. Honest address name.
class Rva0053F8E5DwordCounter
{
public:
	void inc();
};

class Rva0053FC81
{
public:
	Rva0053FC81 *rva0053FC81(Rva0053F8E5DwordCounter *p);

private:
	Rva0053F8E5DwordCounter *m_ptr;
};

Rva0053FC81 *Rva0053FC81::rva0053FC81(Rva0053F8E5DwordCounter *p)
{
	m_ptr = p;
	if (p)
		p->inc();
	return this;
}

// Retail RVA 0x0053FC99, 26 bytes.
// ?rva0053FC99@Rva0053FC99@@QAEPAV1@PAURva0053FC99Src@@@Z
// Ref-store from wrapper at this+0x0 via rowed inc 0x0053F8E5: load src+0,
// store, inc ref on non-null and return this. Callers 0x00540A88 0x005421AA.
// Sibling of 0x0053FC81 in the same /O1 TU. Honest address name.
struct Rva0053FC99Src
{
	Rva0053F8E5DwordCounter *m_ptr;
};

class Rva0053FC99
{
public:
	Rva0053FC99 *rva0053FC99(Rva0053FC99Src *s);

private:
	Rva0053F8E5DwordCounter *m_ptr;
};

Rva0053FC99 *Rva0053FC99::rva0053FC99(Rva0053FC99Src *s)
{
	Rva0053F8E5DwordCounter *p = s->m_ptr;
	m_ptr = p;
	if (p)
		p->inc();
	return this;
}
