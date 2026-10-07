// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?_M_erase@?$_Rb_tree@HU?$pair@$$CBHUBfmePod52@@@_STL@@U?$_Select1st@U?$pair@$$CBHUBfmePod52@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHUBfmePod52@@@_STL@@@2@@_STL@@AAEXPAU?$_Rb_tree_node@U?$pair@$$CBHUBfmePod52@@@_STL@@@2@@Z
// retail 0x00425EA6, 45 bytes. Recursive subtree eraser for the trivial
// int->BfmePod52 map tree: recurses into the right child, releases the node
// through rowed _free at 0x00030830, then walks left. Evidence: unlock lane
// (unblocks 0x00425F69); sits in the Pod52 value-utility cluster between the
// rowed pair ctor 0x00425E68 and the rowed _Construct 0x00425EF0 with the
// same // cl:; caller 0x00425F77 clears the same tree that the rowed
// Pod52 _M_create_node 0x00425F92 feeds; same 45B trivial shape as the rowed
// int-ptr erase 0x004ABAD6.
//
// ?clear@?$_Rb_tree@HU?$pair@$$CBHUBfmePod52@@@_STL@@U?$_Select1st@U?$pair@$$CBHUBfmePod52@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHUBfmePod52@@@_STL@@@2@@_STL@@QAEXXZ
// retail 0x00425F69, 41 bytes. Tree clear for the same int->BfmePod52 map:
// erases the rooted subtree through 0x00425EA6, relinks the header to
// itself and zeroes the node count. Evidence: chain lane (calls 0x00425EA6
// just landed); unblocks 0x00425FB4.
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
struct BfmePod52 { int a[13]; };
template class _STL::map<int, BfmePod52, _STL::less<int>, _STL::allocator<_STL::pair<const int, BfmePod52> > >;
