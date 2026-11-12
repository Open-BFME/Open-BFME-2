// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?insert@?$list@UBfmeFloat4Record00469C61@@V?$allocator@UBfmeFloat4Record00469C61@@@_STL@@@_STL@@QAE?AU?$_List_iterator@UBfmeFloat4Record00469C61@@U?$_Nonconst_traits@UBfmeFloat4Record00469C61@@@_STL@@@2@U32@ABUBfmeFloat4Record00469C61@@@Z @0x001DD86F 37B single-node insert via rowed create_node 0x001DD6ED.
// Evidence: unlock lane every callee rowed; same 37B shape as 0x001EBD16 0x001FD72C 0x00280A68.
#include <list>
// Suppress this TU's non-retail copy of ?_M_create_node@?$list@UBfmeFloat4Record00469C61@@V?$allocator@UBfmeFloat4Record00469C61@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeFloat4Record00469C61;
namespace _STL { template <> _List_node<BfmeFloat4Record00469C61> * list<BfmeFloat4Record00469C61,allocator<BfmeFloat4Record00469C61> >::_M_create_node(BfmeFloat4Record00469C61 const &); }
// Suppress this TU's non-retail copy of ??$_Construct@UBfmeFloat4Record00469C61@@U1@@_STL@@YAXPAUBfmeFloat4Record00469C61@@ABU1@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeFloat4Record00469C61;
namespace _STL { template <> void _Construct<BfmeFloat4Record00469C61,BfmeFloat4Record00469C61>(BfmeFloat4Record00469C61 *,BfmeFloat4Record00469C61 const &); }

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}

#include "../../../../GameEngine/Include/GameLogic/BfmeFloat4Record00469C61.h"
bool operator==(const BfmeFloat4Record00469C61 &, const BfmeFloat4Record00469C61 &);
bool operator<(const BfmeFloat4Record00469C61 &, const BfmeFloat4Record00469C61 &);
// Instantiate only the rowed members: the whole-class instantiation also emitted
// merge/unique/remove, which need the record's undefined comparisons.
template _STL::list<BfmeFloat4Record00469C61, _STL::allocator<BfmeFloat4Record00469C61> >::iterator _STL::list<BfmeFloat4Record00469C61, _STL::allocator<BfmeFloat4Record00469C61> >::insert(_STL::list<BfmeFloat4Record00469C61, _STL::allocator<BfmeFloat4Record00469C61> >::iterator, const BfmeFloat4Record00469C61 &);
template void _STL::list<BfmeFloat4Record00469C61, _STL::allocator<BfmeFloat4Record00469C61> >::push_back(const BfmeFloat4Record00469C61 &);
