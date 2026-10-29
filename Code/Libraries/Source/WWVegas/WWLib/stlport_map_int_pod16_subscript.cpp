// cl: /EHs /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?rva00257252@Rva00257252@@QAEAAUBfmePod16@@ABH@Z @0x00257252 92B
// Pod16 get-or-create via lower_bound plus hint insert with zero Pod16.
// Evidence: chain lane (calls our 0x00256F67 insert); caller 0x0025740B
// passes key at +0x14 and fills 16B at returned pointer; unblocks 0x002573EE.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}
struct BfmePod16 { int a[4]; };
// The node allocator otherwise instantiates a non-retail allocate COMDAT; since
// Rva0041355DParse.cpp moved to STLport 4.6 no unit provides the 4.5.3 copy, so
// an explicit dllimport+forceinline specialization takes the call inline.
namespace _STL {
template <> __declspec(dllimport) __forceinline
_Rb_tree_node<pair<const int, BfmePod16> > *allocator<_Rb_tree_node<pair<const int, BfmePod16> > >::allocate(size_t __n, const void *) const
{ return __n != 0 ? (_Rb_tree_node<pair<const int, BfmePod16> > *)__sgi_alloc::allocate(__n * sizeof(_Rb_tree_node<pair<const int, BfmePod16> >)) : 0; }
}
typedef _STL::pair<const int, BfmePod16> Pod16MapValue;
typedef _STL::map<int, BfmePod16, _STL::less<int>, _STL::allocator<Pod16MapValue> > Pod16Map;
class Rva00257252
{
public:
	BfmePod16 &rva00257252(const int &key);
private:
	Pod16Map m_map;
};
BfmePod16 &Rva00257252::rva00257252(const int &key)
{
	Pod16Map::iterator i = m_map.lower_bound(key);
	if (i == m_map.end() || m_map.key_comp()(key, (*i).first))
	{
		BfmePod16 zero = { 0, 0, 0, 0 };
		i = m_map.insert(i, Pod16MapValue(key, zero));
	}
	return (*i).second;
}
