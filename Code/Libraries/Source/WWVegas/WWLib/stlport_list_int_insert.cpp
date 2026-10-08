// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Dedicated unit without the bfmelist __forceinline _M_create_node shim so
// list<int>::insert can call the already-landed create_node at 0xB6447.
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}

namespace _STL {
// Instantiate the rowed insertion and const iterator, keeping the complete
// node-creation provider and nonconst iterator in their canonical units.
template <> list<int>::_Node *list<int>::_M_create_node(const int &);
template list<int>::iterator list<int>::insert(list<int>::iterator, const int &);
template class _List_iterator<int, _Const_traits<int> >;
}
