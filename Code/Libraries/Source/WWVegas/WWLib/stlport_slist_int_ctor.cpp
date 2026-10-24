// cl: -EHsc /Os
// stlport
// STLport 4.5.3 slist<int>(const allocator_type &), retail 0x00071233
// (18B), unreferenced: hands the allocator to the rowed out-of-line
// _Slist_base<int> constructor (0x0006FA99) and returns this. The
// declaration-only specialisation keeps that call out of line, as in retail.
// The payload is int as in the rowed base (SceneNodeListProviders.cpp).
#include <slist>
// bfme link decl-only begin
namespace _STL { template <> _Slist_node_base * _Slist_base<int, allocator<int> >::_M_erase_after(_Slist_node_base *, _Slist_node_base *); }
// bfme link decl-only end

namespace _STL {
template <> _Slist_base<int, allocator<int> >::_Slist_base(const allocator<int> &);
}

template _STL::slist<int>::slist(const _STL::allocator<int> &);
