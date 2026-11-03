// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?insert@?$list@VRva0036CA00Str@@V?$allocator@VRva0036CA00Str@@@_STL@@@_STL@@QAE?AU?$_List_iterator@VRva0036CA00Str@@U?$_Nonconst_traits@VRva0036CA00Str@@@_STL@@@2@U32@ABVRva0036CA00Str@@@Z retail 0x00054B75 37B
// Evidence: identical 37B insert shape to list<AsciiString>::insert at 0x001FD72C and list<TreeKey00242F5E>::insert at 0x002A1BC6;
// here calls rowed Rva0036CA00Str _M_create_node at 0x00053DA3 then list hook insertion; caller 0x00055486.
#include <list>
// Suppress this TU's non-retail copy of ?_M_create_node@?$list@VRva0036CA00Str@@V?$allocator@VRva0036CA00Str@@@_STL@@@_STL@@IAEPAU:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class Rva0036CA00Str;
namespace _STL { template <> _List_node<Rva0036CA00Str> * list<Rva0036CA00Str,allocator<Rva0036CA00Str> >::_M_create_node(Rva0036CA00Str const &); }
// Suppress this TU's non-retail copy of ??$_Construct@VRva0036CA00Str@@V1@@_STL@@YAXPAVRva0036CA00Str@@ABV1@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class Rva0036CA00Str;
namespace _STL { template <> void _Construct<Rva0036CA00Str,Rva0036CA00Str>(Rva0036CA00Str *,Rva0036CA00Str const &); }

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


#include "../../../../GameEngine/Include/Common/Rva0036CA00Str.h"

bool operator==(const Rva0036CA00Str &a, const Rva0036CA00Str &b);
bool operator<(const Rva0036CA00Str &a, const Rva0036CA00Str &b);

// remove/unique/merge/sort need element operator==/operator<, which have no
// body; declare them specialized so the class instantiation below emits none.
namespace _STL {
template <> void list<Rva0036CA00Str,allocator<Rva0036CA00Str> >::remove(Rva0036CA00Str const &);
template <> void list<Rva0036CA00Str,allocator<Rva0036CA00Str> >::unique();
template <> void list<Rva0036CA00Str,allocator<Rva0036CA00Str> >::merge(list<Rva0036CA00Str,allocator<Rva0036CA00Str> > &);
template <> void list<Rva0036CA00Str,allocator<Rva0036CA00Str> >::sort();
}
template class _STL::list<Rva0036CA00Str, _STL::allocator<Rva0036CA00Str> >;
