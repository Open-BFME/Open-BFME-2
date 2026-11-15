// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?clear@?$_List_base@URva001EA443@@V?$allocator@URva001EA443@@@_STL@@@_STL@@QAEXXZ @0x001EA529 49B: list clear of Rva001EA443 via rowed dtor 0x001EA443 and _free 0x00030830; empty-check plus sentinel reset match list<int> and TreeHintOpaque 0x00434EC9 precedent.
// Value is the two-string record at node+8 shared with BfmeStringRecord001EA478; dtor identity proven by callers at 0x001EA821 and 0x001EA980 and the _M_create_node row for that layout.
#include <list>

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

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


#include "../../../../../reference/shims/bfme2_ascii/string_base.h"

struct Rva001EA443
{
	StringBase<char> m_text0;
	StringBase<char> m_text1;
	Rva001EA443();
	Rva001EA443(const Rva001EA443 &);
	~Rva001EA443();
};

inline bool operator==(const Rva001EA443 &x, const Rva001EA443 &y) { return false; }
inline bool operator<(const Rva001EA443 &x, const Rva001EA443 &y) { return false; }

template void _STL::_List_base<Rva001EA443, _STL::allocator<Rva001EA443> >::clear();
template _STL::_List_base<Rva001EA443, _STL::allocator<Rva001EA443> >::~_List_base();
