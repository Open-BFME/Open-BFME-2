// ??A?$map@HURva004393D6@@U?$less@H@_STL@@V?$allocator@U?$pair@$$CBHURva004393D6@@@_STL@@@3@@_STL@@QAEAAURva004393D6@@ABH@Z
// partial score=0.84 date=2026-10-08
// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfmelist /EHs /D_STLP_USE_MALLOC /D_BFME_RETAIL_TREE_INSERT_LAYOUT /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva004393D6@@QAE@ABU0@@Z @0x004393D6 39B
// Copy ctor over _STL::list<BfmePod196> base via rowed 0x004392CD plus three
// ints at +4 +8 +0xc. Unlocks 0x004395EC 0x0043964D.
// Evidence: push edi mov esi ecx base-copy call then three eax movs ret 4.
#include <list>
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}

struct BfmePod196 { int a[49]; };
inline bool operator==(const BfmePod196 &x, const BfmePod196 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod196 &x, const BfmePod196 &y) { return x.a[0] < y.a[0]; }
struct Rva004393D6 : public _STL::list<BfmePod196>
{
	int m_04;
	int m_08;
	int m_0c;
	__declspec(noinline) Rva004393D6();
	__declspec(noinline) ~Rva004393D6();
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

typedef _STL::map<int, Rva004393D6, _STL::less<int>,
    _STL::allocator<_STL::pair<const int, Rva004393D6> > > InvisibilityRecordMap;
template <> Rva004393D6 &InvisibilityRecordMap::operator[](const int &key)
{
    iterator it = lower_bound(key);
    if (it == end() || key_comp()(key, (*it).first))
        it = insert(it, value_type(key, Rva004393D6()));
    return (*it).second;
}
Rva004393D6 &(InvisibilityRecordMap::*keepSubscript)(const int &) = &InvisibilityRecordMap::operator[];

Rva004393D6::Rva004393D6() : _STL::list<BfmePod196>(_STL::allocator<BfmePod196>())
{
    m_04 = 0;
    m_08 = 0;
    m_0c = 0;
}
Rva004393D6::~Rva004393D6()
{
    clear();
}

