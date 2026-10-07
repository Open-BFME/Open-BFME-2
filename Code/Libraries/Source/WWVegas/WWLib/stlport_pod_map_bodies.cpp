// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
//
// Pristine STLport 4.5.3 map members for placeholder POD values. BfmePod8
// stands for the real 8-byte mapped type; the key is int (the placed body
// compares signed).
// Scoped explicit instantiations emit only the nine rowed members, so calls
// reach the retail tree/allocation helpers instead of emitting competing
// COMDAT copies. _M_create_node/_M_copy are declared only; their rowed
// bodies live in the sibling pod-map units.
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
struct BfmePod8 { int a[2]; };
typedef _STL::pair<const int, BfmePod8> PodMapValue;
typedef _STL::_Rb_tree<int, PodMapValue, _STL::_Select1st<PodMapValue>, _STL::less<int>, _STL::allocator<PodMapValue> > PodMapTree;
typedef _STL::map<int, BfmePod8, _STL::less<int>, _STL::allocator<PodMapValue> > PodMapTreeMap;
template <> PodMapTree::_Link_type PodMapTree::_M_create_node(const PodMapValue &);
template <> PodMapTree::_Link_type PodMapTree::_M_copy(PodMapTree::_Link_type, PodMapTree::_Link_type);
template <> _STL::pair<PodMapTree::iterator, bool> PodMapTree::insert_unique(const PodMapValue &);
template PodMapValue::pair(const int &, const BfmePod8 &);
template BfmePod8 &PodMapTreeMap::operator[](const int &);
template PodMapTreeMap::iterator PodMapTreeMap::insert(PodMapTreeMap::iterator, const PodMapValue &);
template PodMapTree::iterator PodMapTree::insert_unique(PodMapTree::iterator, const PodMapValue &);
template PodMapTree::iterator PodMapTree::_M_insert(_STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *, const PodMapValue &, _STL::_Rb_tree_node_base *);
template PodMapTree::_Link_type PodMapTree::_M_clone_node(PodMapTree::_Link_type);
template PodMapTreeMap::map(const PodMapTreeMap &);
template PodMapTree::_Rb_tree(const _STL::less<int> &, const _STL::allocator<PodMapValue> &);
template PodMapTreeMap::map();
