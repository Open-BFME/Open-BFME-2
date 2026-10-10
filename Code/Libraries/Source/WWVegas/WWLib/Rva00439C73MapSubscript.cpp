// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfmelist /EHs /D_STLP_USE_MALLOC /D_BFME_RETAIL_TREE_INSERT_LAYOUT /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
//
// map<int, Rva004393D6>::operator[] at retail 0x00439C73 (132B): banked by an
// earlier seat, closed once its callees (_M_lower_bound 0x00382A92, insert
// 0x00439C56, pair ctor 0x004395EC, record ctor/dtor 0x00438FA7/0x00438FC5)
// were pinned from retail. The record's other members live in
// Rva004393D6Copy.cpp.
// stlport
// ??0Rva004393D6@@QAE@ABU0@@Z @0x004393D6 39B
// Copy ctor over _STL::list<BfmePod196> base via rowed 0x004392CD plus three
// ints at +4 +8 +0xc. Unlocks 0x004395EC 0x0043964D.
// Evidence: push edi mov esi ecx base-copy call then three eax movs ret 4.
#include <list>
#include <map>

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

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
struct Rva004395EC
{
	void *m_00;
	Rva004393D6 m_04;
	Rva004395EC(void **p, const Rva004393D6 &o);
	Rva004395EC(const Rva004395EC &o);
};
typedef _STL::map<int, Rva004393D6, _STL::less<int>,
    _STL::allocator<_STL::pair<const int, Rva004393D6> > > InvisibilityRecordMap;
template <> Rva004393D6 &InvisibilityRecordMap::operator[](const int &key)
{
    iterator it = lower_bound(key);
    if (it == end() || key_comp()(key, (*it).first))
        it = insert(it, value_type(key, Rva004393D6()));
    return (*it).second;
}


// Takes the specialization address so cl emits it (an unreferenced explicit
// specialization of an inline STLport member is otherwise discarded).
Rva004393D6 &(InvisibilityRecordMap::*keepSubscript)(const int &) = &InvisibilityRecordMap::operator[];
