// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ??0Rva0057ACEB@@QAE@PBURva0057ACEBData@@@Z @0x0057ACEB 59B
// Refcounted holder ctor: news 0x10 impl with vtable 0x0086F090 and copies 8B arg.
// Evidence: stores vtable at new obj, callers pass 8B struct ptr with ecx=temp.
extern const void *const g_00C6F090[];
void *__cdecl operator new(unsigned int);
struct Rva0057ACEBData
{
	int m_0;
	int m_4;
};
class Rva0057ACEBImpl
{
public:
	void *m_vtbl;
	int m_ref;
	int m_a;
	int m_b;
	Rva0057ACEBImpl(const Rva0057ACEBData *d)
	{
		m_ref = 0;
		*(const void * *)this = g_00C6F090;
		m_a = d->m_0;
		m_b = d->m_4;
	}
};
class Rva0057ACEB
{
public:
	Rva0057ACEB(const Rva0057ACEBData *d);
private:
	Rva0057ACEBImpl *m_impl;
};
Rva0057ACEB::Rva0057ACEB(const Rva0057ACEBData *d)
{
	Rva0057ACEBImpl *p = new Rva0057ACEBImpl(d);
	m_impl = p;
	if (p)
		++p->m_ref;
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?g_00C6F090@@3QBQBXB=??_7Rva0057AA1F@@6B@")
