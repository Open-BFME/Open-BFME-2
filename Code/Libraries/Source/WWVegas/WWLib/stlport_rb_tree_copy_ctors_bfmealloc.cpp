// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 _Rb_tree copy constructors for two POD-valued trees,
// dedicated TU: map<int, BfmePod8> (retail 0x003A299C) and map<int, BfmePod24>
// (0x00418066), 165B each.
// Element layouts are carried from stlport_pod_map_mcopy.cpp and
// stlport_rb_tree_create_nodes.cpp.
//
// Target evidence: each body is the unowned retail caller of that tree's
// matched _M_copy row; its other callees are the ICF get_allocator and the
// _Rb_tree_base(const allocator &) header-node ctor, pinned to the matched
// bodies they reproduce. /Ireference/shims/bfmealloc is what makes the
// header-node allocation in _Rb_tree_base match retail; the owning TUs' stock
// allocator emits a different 33-byte base ctor.
#include <map>

struct BfmePod8 { int a[2]; };
struct BfmePod24 { int a[6]; };

template _STL::_Rb_tree<int, _STL::pair<const int, BfmePod8>, _STL::_Select1st<_STL::pair<const int, BfmePod8> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, BfmePod8> > >::_Rb_tree(
    const _STL::_Rb_tree<int, _STL::pair<const int, BfmePod8>, _STL::_Select1st<_STL::pair<const int, BfmePod8> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, BfmePod8> > > &);
template _STL::_Rb_tree<int, _STL::pair<const int, BfmePod24>, _STL::_Select1st<_STL::pair<const int, BfmePod24> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, BfmePod24> > >::_Rb_tree(
    const _STL::_Rb_tree<int, _STL::pair<const int, BfmePod24>, _STL::_Select1st<_STL::pair<const int, BfmePod24> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, BfmePod24> > > &);
