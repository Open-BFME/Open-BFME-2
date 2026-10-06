// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva004393D6@@QAE@ABU0@@Z @0x004393D6 39B
// Copy ctor over _STL::list<BfmePod196> base via rowed 0x004392CD plus three
// ints at +4 +8 +0xc. Unlocks 0x004395EC 0x0043964D.
// Evidence: push edi mov esi ecx base-copy call then three eax movs ret 4.
#include <list>
struct BfmePod196 { int a[49]; };
inline bool operator==(const BfmePod196 &x, const BfmePod196 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod196 &x, const BfmePod196 &y) { return x.a[0] < y.a[0]; }
struct Rva004393D6 : public _STL::list<BfmePod196>
{
	int m_04;
	int m_08;
	int m_0c;
	Rva004393D6(const Rva004393D6 &o);
	Rva004393D6 &operator=(const Rva004393D6 &o);
};
Rva004393D6::Rva004393D6(const Rva004393D6 &o) : _STL::list<BfmePod196>(o), m_04(o.m_04), m_08(o.m_08), m_0c(o.m_0c)
{
}
Rva004393D6 &Rva004393D6::operator=(const Rva004393D6 &o)
{
	if (&o == this)
		return *this;
	_STL::list<BfmePod196>::operator=(o);
	m_04 = o.m_04;
	m_08 = o.m_08;
	m_0c = o.m_0c;
	return *this;
}
struct Rva004395EC
{
	void *m_00;
	Rva004393D6 m_04;
	Rva004395EC(void **p, const Rva004393D6 &o);
	Rva004395EC(const Rva004395EC &o);
};
Rva004395EC::Rva004395EC(const Rva004395EC &o) : m_00(o.m_00), m_04(o.m_04)
{
}
Rva004395EC::Rva004395EC(void **p, const Rva004393D6 &o) : m_00(*p), m_04(o)
{
}
