// cl: /D_STLP_NO_EXCEPTIONS /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ?insert@?$map@HV?$vector@IV?$allocator@I@_STL@@@_STL@@U?$less@H@2@V?$allocator@U?$pair@$$CBHV?$vector@IV?$allocator@I@_STL@@@_STL@@@_STL@@@2@@_STL@@QAE?AU?$_Rb_tree_iterator@U?$pair@$$CBHV?$vector@IV?$allocator@I@_STL@@@_STL@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHV?$vector@IV?$allocator@I@_STL@@@_STL@@@_STL@@@2@@2@U32@ABU?$pair@$$CBHV?$vector@IV?$allocator@I@_STL@@@_STL@@@2@@Z @0x0021DB74 29B
// Hinted map::insert forwarder to rowed hinted _Rb_tree::insert_unique 0x0021D6A9. Same 29B shape as Locomotor map::insert 0x001E9066. Evidence: caller 0x0021E0BB passes hidden+pos+pair with this=map; callee rowed.
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#include <vector>
typedef _STL::vector<unsigned int, _STL::allocator<unsigned int> > HeroInsertVector;
typedef _STL::map<int, HeroInsertVector, _STL::less<int>, _STL::allocator<_STL::pair<const int, HeroInsertVector> > > HeroInsertMap;
template class _STL::map<int, HeroInsertVector, _STL::less<int>, _STL::allocator<_STL::pair<const int, HeroInsertVector> > >;
