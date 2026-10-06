// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?insert@?$list@UTreeKey00242F5E@@V?$allocator@UTreeKey00242F5E@@@_STL@@@_STL@@QAE?AU?$_List_iterator@UTreeKey00242F5E@@U?$_Nonconst_traits@UTreeKey00242F5E@@@_STL@@@2@U32@ABUTreeKey00242F5E@@@Z retail 0x002A1BC6 37B
// Evidence: identical 37B shape to list<int>::insert at 0x005925E2 calling rowed _M_create_node;
// here calls rowed TreeKey _M_create_node at 0x002A1361 then list hook insertion; caller 0x002A3FA6.
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


#include "ascii_string.h"

struct TreeKey00242F5E
{
	int m_id;
	AsciiString m_name;
	TreeKey00242F5E();
	TreeKey00242F5E(const TreeKey00242F5E &);
};
inline TreeKey00242F5E::TreeKey00242F5E() {}

bool operator==(const TreeKey00242F5E &a, const TreeKey00242F5E &b);
bool operator<(const TreeKey00242F5E &a, const TreeKey00242F5E &b);

template class _STL::list<TreeKey00242F5E, _STL::allocator<TreeKey00242F5E> >;
