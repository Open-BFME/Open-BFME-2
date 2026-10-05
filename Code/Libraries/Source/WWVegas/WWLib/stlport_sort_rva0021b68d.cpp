// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// STLport sort<Rva0021B68DKey*, Rva0021B68DCmp> family, 0x0021B8F2-0x0021F13C.
// Shape twin of the rowed stlport_sort_rva004ebe74.cpp family with two
// differences that fix the element model: (1) every comparison is a thiscall
// to the out-of-line Rva0021B68DCmp::operator() at 0x0021B68D (198B, EH
// frame, string compareNoCase calls; unrowed, declared-only here) taking both
// elements by const reference; (2) __linear_insert calls copy_backward out of
// line (ICF-folded with copy_backward<ObjectID*> at 0x005E42D3) instead of
// __copy_trivial_backward, so the 4-byte element is not a pointer to STLport's
// type traits -- an enum, as ObjectID is. Key and functor keep address-derived
// names. The 3 members ICF-folded with the rowed Rva00204BB8 int sort
// (__pop_heap_aux, pop_heap, sort_heap) are pinned, not rowed.
#include <algorithm>

enum Rva0021B68DKey
{
	RVA0021B68D_KEY_INVALID = -1
};

struct Rva0021B68DCmp
{
	bool operator()(const Rva0021B68DKey &a, const Rva0021B68DKey &b) const;
};

template void _STL::sort<Rva0021B68DKey *, Rva0021B68DCmp>(Rva0021B68DKey *, Rva0021B68DKey *, Rva0021B68DCmp);
