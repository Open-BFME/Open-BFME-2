// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
//
// Ported from reference/open-bfme-1/Code/GameEngine/Source/Common/MultiplayerColorMapOperator.cpp.
// Retail 0x003812E6 (141B) is the color-list miss-path body: lower_bound over
// the map, default-constructed insertion value on miss, pair construction plus
// hinted insert, twin member-teardown cleanups. Served as lookup@PAH (the key
// travels by address, dereferenced inside); the expansion below is
// map<Int, MCD>::operator[] reached through the RetailColorList wrapper.
// BFME2 value model is 0x40 bytes (see MultiplayerColorPairConstructor.cpp),
// not the reference's 0x24-byte shape.

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

typedef int Int;

#include "ascii_string.h"


#include "../../../Libraries/Include/Lib/RGBColor.h"

#include "../../Include/GameNetwork/MultiplayerColorDefinition.h"

typedef char MultiplayerColorMapValueMatchesRetail[(sizeof(MultiplayerColorDefinition) == 0x40) ? 1 : -1];

typedef std::map<Int, MultiplayerColorDefinition> MultiplayerColorList;

namespace _STL
{
	// Declared (never defined here) so the subscript calls out of line to the
	// landed pair body instead of inlining it.
	template <>
	__declspec(noinline) pair<const Int, MultiplayerColorDefinition>::pair(
		const Int &firstValue, const MultiplayerColorDefinition &secondValue);
}

// Retail shares one ret and one NULL store for all getColor paths; the list
// itself lives at settings+0x34 (node count at +0x34 per the rowed getColor).
struct RetailColorList
{
	MultiplayerColorList m_list;
	MultiplayerColorDefinition *lookup(int *which);
};

// Hand-expanded miss path (the header's operator[] lowers the insertion value
// through a __default_constructed helper retail never calls): fully nested
// temporaries so each construction feeds the next call straight out of eax,
// with twin member-teardown cleanups for the two temps.
MultiplayerColorDefinition *RetailColorList::lookup(int *which)
{
	MultiplayerColorList::iterator it = m_list.lower_bound(*which);
	if (it == m_list.end() || *which < it->first)
		it = m_list.insert(it, MultiplayerColorList::value_type(*which, MultiplayerColorDefinition()));
	return &it->second;
}
// bfme link decl-only begin
namespace _STL { template <> _STL::_Rb_tree_node<_STL::pair<int const,MultiplayerColorDefinition> > * _Rb_tree<int,_STL::pair<int const,MultiplayerColorDefinition>,_STL::_Select1st<_STL::pair<int const,MultiplayerColorDefinition> >,_STL::less<int>,_STL::allocator<_STL::pair<int const,MultiplayerColorDefinition> > >::_M_create_node(_STL::pair<int const,MultiplayerColorDefinition> const &); }
namespace _STL { template <> _STL::_Rb_tree_node<_STL::pair<int const,MultiplayerColorDefinition> > * allocator<_STL::_Rb_tree_node<_STL::pair<int const,MultiplayerColorDefinition> > >::allocate(unsigned int,void const *) const; }
namespace _STL { template <> _STL::pair<_STL::_Rb_tree_iterator<_STL::pair<int const,MultiplayerColorDefinition>,_STL::_Nonconst_traits<_STL::pair<int const,MultiplayerColorDefinition> > >,bool> _Rb_tree<int,_STL::pair<int const,MultiplayerColorDefinition>,_STL::_Select1st<_STL::pair<int const,MultiplayerColorDefinition> >,_STL::less<int>,_STL::allocator<_STL::pair<int const,MultiplayerColorDefinition> > >::insert_unique(_STL::pair<int const,MultiplayerColorDefinition> const &); }
// bfme link decl-only end
