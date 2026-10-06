// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_NO_EXCEPTIONS
// stlport
// ?_M_copy@?$_Rb_tree@HU?$pair@$$CBHUBfmePod8@@@_STL@@U?$_Select1st@U?$pair@$$CBHUBfmePod8@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHUBfmePod8@@@_STL@@@2@@_STL@@AAEPAU?$_Rb_tree_node@U?$pair@$$CBHUBfmePod8@@@_STL@@@2@PAU32@0@Z @ 0x003A24C6 115B
// _Rb_tree<int,pair<const int,BfmePod8>>::_M_copy beside stlport_pod_map_bodies.
// Target evidence: 115B retail, rowed _M_clone_node 0x39FD75 plus self-recursion,
// unlocks 0x3A299C. Whole-class probe with NO_EXCEPTIONS emits 115B exact;
// single-member instantiation keeps the TU claim-free. Flags copy the
// NO_EXCEPTIONS shape from stlport_rb_tree_create_nodes.
#include <map>
struct BfmePod8 { int a[2]; };
typedef _STL::_Rb_tree<int, _STL::pair<const int, BfmePod8>, _STL::_Select1st<_STL::pair<const int, BfmePod8> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, BfmePod8> > > PodMapTree;
template PodMapTree::_Link_type PodMapTree::_M_copy(PodMapTree::_Link_type, PodMapTree::_Link_type);
