// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?rva00603C0F@Rva00603C0F@@QAEPBXPBD0@Z @ 0x00603C0F (67B).
// Two-level C-string keyed lookup in the 0x00600854-0x00604518 strcmp-keyed family.
// Evidence: chain lane calls rowed _M_find 0x00603A2D twice (first for outer map at this+4 with key1 then inner map at first-node+0x14 with key2); empty-string fallback to the "" literal at 0x00BBAC1C when key1==key2; callers 0x00603C93 0x00603CD7 0x00603D40 unblock on landing; prev/next are unrelated TUs so new file reuses the _M_find TU flags and pins.
#pragma optimize("t", on)
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator==(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node == b._M_node; }
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#pragma optimize("", on)


struct Rva00603A00Mapped
{
	unsigned int m_bits;
};

struct Rva006038D4Less
{
	bool operator()(const char *a, const char *b) const;
};

typedef _STL::pair<const char* const, Rva00603A00Mapped> Rva00603C0FInnerPair;
typedef _STL::map<const char*, Rva00603A00Mapped, Rva006038D4Less> Rva00603C0FInnerMap;
typedef _STL::pair<const char* const, Rva00603C0FInnerMap> Rva00603C0FOuterPair;
typedef _STL::map<const char*, Rva00603C0FInnerMap, Rva006038D4Less> Rva00603C0FOuterMap;

struct Rva00603C0F
{
	char m_pad[4];
	Rva00603C0FOuterMap m_map;
	const void *rva00603C0F(const char *a, const char *b);
};

const void *Rva00603C0F::rva00603C0F(const char *a, const char *b)
{
	if (a == b)
		a = (char *)"";
	Rva00603C0FOuterMap::iterator it1 = m_map.find(a);
	if (it1 == m_map.end())
		return 0;
	Rva00603C0FInnerMap &inner = (*it1).second;
	Rva00603C0FInnerMap::iterator it2 = inner.find(b);
	if (it2 != inner.end())
		return &(*it2).second;
	return 0;
}
