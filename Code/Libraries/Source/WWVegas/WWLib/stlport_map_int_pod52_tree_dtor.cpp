// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1?$_Rb_tree@HU?$pair@$$CBHUBfmePod52@@@_STL@@U?$_Select1st@U?$pair@$$CBHUBfmePod52@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHUBfmePod52@@@_STL@@@2@@_STL@@QAE@XZ
// retail 0x00425FB4, 56 bytes. Tree dtor for the int->BfmePod52 map: clears
// through the rowed 0x00425F69 body, then frees the header node through
// rowed _free at 0x00030830 when non-null. Evidence: chain lane (calls
// 0x00425F69 just landed); same 56B EH shell as the rowed int-int tree dtor
// 0x0021B775 and color-tree dtor 0x0038103F. Shard, not graft: the /EHs flag
// the EH state store needs would perturb the /EHsc erase/clear home TU.
// Companion to stlport_map_int_pod52_o1.cpp.
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
