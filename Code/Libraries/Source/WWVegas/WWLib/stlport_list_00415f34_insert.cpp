// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?insert@?$list@UBfmeStringRecord00415F34@@V?$allocator@UBfmeStringRecord00415F34@@@_STL@@@_STL@@QAE?AU?$_List_iterator@UBfmeStringRecord00415F34@@U?$_Nonconst_traits@UBfmeStringRecord00415F34@@@_STL@@@2@U32@ABUBfmeStringRecord00415F34@@@Z @0x004168AE 37B
// list<BfmeStringRecord00415F34>::insert 37B calling rowed _M_create_node at
// 0x00416521 then list hook insertion; identical shape to list<BfmeStringRecord001EA478>::insert
// at 0x001EA958 and list<int>::insert at 0x005925E2; caller 0x0041691F.
#include <list>
// Suppress this TU's non-retail copy of ?_M_create_node@?$list@UBfmeStringRecord00415F34@@V?$allocator@UBfmeStringRecord00415F34@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeStringRecord00415F34;
namespace _STL { template <> _List_node<BfmeStringRecord00415F34> * list<BfmeStringRecord00415F34,allocator<BfmeStringRecord00415F34> >::_M_create_node(BfmeStringRecord00415F34 const &); }
// Suppress this TU's non-retail copy of ??$_Construct@UBfmeStringRecord00415F34@@U1@@_STL@@YAXPAUBfmeStringRecord00415F34@@ABU1@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void _Construct<BfmeStringRecord00415F34,BfmeStringRecord00415F34>(BfmeStringRecord00415F34 *,BfmeStringRecord00415F34 const &); }

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


struct BfmeStringRecord00415F34 { unsigned char m_data[24]; };

bool operator==(const BfmeStringRecord00415F34 &a, const BfmeStringRecord00415F34 &b);
bool operator<(const BfmeStringRecord00415F34 &a, const BfmeStringRecord00415F34 &b);

// remove/unique/merge/sort need element operator==/operator<, which have no
// body; declare them specialized so the class instantiation below emits none.
namespace _STL {
template <> void list<BfmeStringRecord00415F34,allocator<BfmeStringRecord00415F34> >::remove(BfmeStringRecord00415F34 const &);
template <> void list<BfmeStringRecord00415F34,allocator<BfmeStringRecord00415F34> >::unique();
template <> void list<BfmeStringRecord00415F34,allocator<BfmeStringRecord00415F34> >::merge(list<BfmeStringRecord00415F34,allocator<BfmeStringRecord00415F34> > &);
template <> void list<BfmeStringRecord00415F34,allocator<BfmeStringRecord00415F34> >::sort();
}
template class _STL::list<BfmeStringRecord00415F34, _STL::allocator<BfmeStringRecord00415F34> >;
