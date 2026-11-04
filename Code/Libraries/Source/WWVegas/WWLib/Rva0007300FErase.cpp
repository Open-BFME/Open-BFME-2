// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva0007300F@Rva00072FE6@@QAEXU?$_Rb_tree_iterator@U?$pair@$$CBHPAX@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHPAX@_STL@@@2@@_STL@@0@Z @0x0007300F 68B via STLPort range erase plus rowed clear
// Evidence: vendor/stlport/stl/_tree.h erase(first last) calls clear on full range else loops via increment plus single erase
// Retail calls clear 0x00072FE6 plus increment 0x00024250 plus single erase 0x005530A8 for map int to voidptr
// Same 68B shape as rowed range erase 0x004ABC85 in stlport_map_int_ptr_o1.cpp modulo clear callee
// Contiguous with clear 0x00072FE6 and set insert 0x00073053 and unblocks caller 0x000733D8
#include <map>

#include "../../../../GameEngineDevice/Include/W3DDevice/GameClient/BfmeShroudTreeCompare.h"

namespace _STL {
// Keep the vendor bodies inline without emitting additional int/int tree
// COMDAT copies. The matched callers already inline these two helpers.
typedef pair<const int, int> EraseIntPair;
typedef _Rb_tree_iterator<EraseIntPair, _Nonconst_traits<EraseIntPair> > EraseIntIterator;
typedef _Rb_tree<int, EraseIntPair, _Select1st<EraseIntPair>, less<int>, allocator<EraseIntPair> > EraseIntTree;

// ?_STL::EraseIntIterator::_Rb_tree_iterator present-unmatched
template <> __declspec(dllimport) __forceinline
EraseIntIterator::_Rb_tree_iterator(const EraseIntIterator &it)
{ _M_node = it._M_node; }

// ?_STL::EraseIntTree::upper_bound present-unmatched
template <> __declspec(dllimport) __forceinline
EraseIntTree::iterator EraseIntTree::upper_bound(const int &key)
{ return iterator(_M_upper_bound(key)); }
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
struct Rva00072F7CNode {
  unsigned _M_color;
  Rva00072F7CNode *parent04;
  Rva00072F7CNode *left08;
  Rva00072F7CNode *right0C;
};
#include "../../../../GameEngine/Include/Common/Rva00072FE6.h"
// The single-iterator erase provider is rowed at 0x005530A8 in
// stlport_map_int_ptr_o1.cpp. Keep calls to that body when this donor joins
// the shroud TU, whose /G7 flags would emit a different COMDAT copy.
namespace _STL {
template <> void _Rb_tree<int, Rva00072FE6::V,
    _Select1st<Rva00072FE6::V>, less<int>, allocator<Rva00072FE6::V> >::erase(iterator);
}
void Rva00072FE6::rva0007300F(iterator first, iterator last) {
  typedef V VV;
  typedef _STL::_Rb_tree<int, VV, _STL::_Select1st<VV>, _STL::less<int>, _STL::allocator<VV> > Tree;
  if (first._M_node == reinterpret_cast<_STL::_Rb_tree_node_base *>(header00->left08) &&
      last._M_node == reinterpret_cast<_STL::_Rb_tree_node_base *>(header00))
    rva00072FE6();
  else
    while (first != last)
      ((Tree*)this)->erase(first++);
}
unsigned int Rva00072FE6::rva000733D8(const int &key) {
  typedef _STL::pair<const int, int> V2;
  typedef _STL::_Rb_tree<int, V2, _STL::_Select1st<V2>, _STL::less<int>, _STL::allocator<V2> > TreeIntInt;
  typedef _STL::_Rb_tree_iterator<V2, _STL::_Nonconst_traits<V2> > IterIntInt;
  _STL::pair<IterIntInt, IterIntInt> p = ((TreeIntInt*)this)->equal_range(key);
  unsigned int n = _STL::distance(*(iterator*)&p.first, *(iterator*)&p.second);
  rva0007300F(*(iterator*)&p.first, *(iterator*)&p.second);
  return n;
}
