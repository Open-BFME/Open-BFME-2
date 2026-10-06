// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?insert@?$list@FV?$allocator@F@_STL@@@_STL@@QAE?AU?$_List_iterator@FU?$_Nonconst_traits@F@_STL@@@2@U32@ABF@Z @0x002ABB61 (37B)
// Evidence: identical 37B shape to list<int>::insert at 0x005925E2 calling rowed _M_create_node;
// here calls rowed short _M_create_node at 0x002AAC55 then list hook insertion; caller 0x002AC01D.
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}

template class _STL::list<short, _STL::allocator<short> >;
