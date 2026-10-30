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

// list<CreditsLine *>::insert is the same folded body (0x5925E2). Credits.cpp's
// own copy inlines the bfmelist node creator; this one, first in link order,
// calls Credits.cpp's retail _M_create_node (0xB6447) as retail does.
class CreditsLine;
namespace _STL {
template <> list<CreditsLine *>::_Node *list<CreditsLine *>::_M_create_node(CreditsLine *const &);
template list<CreditsLine *>::iterator list<CreditsLine *>::insert(list<CreditsLine *>::iterator, CreditsLine *const &);
}

// list<HeaderTemplate *>::insert folds into 0x5925E2 too; HeaderTemplate.cpp's
// copy inlines node creation, this one calls the 0xB6447 twin rowed in
// stlport_list_int_o1.cpp.
class HeaderTemplate;
namespace _STL {
template <> list<HeaderTemplate *>::_Node *list<HeaderTemplate *>::_M_create_node(HeaderTemplate *const &);
template list<HeaderTemplate *>::iterator list<HeaderTemplate *>::insert(list<HeaderTemplate *>::iterator, HeaderTemplate *const &);
}

// list<AnimateWindow *>::insert, which AnimateWindowManager.cpp declares only.
class AnimateWindow;
namespace _STL {
template <> list<AnimateWindow *>::_Node *list<AnimateWindow *>::_M_create_node(AnimateWindow *const &);
template list<AnimateWindow *>::iterator list<AnimateWindow *>::insert(list<AnimateWindow *>::iterator, AnimateWindow *const &);
}
