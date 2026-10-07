// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva0007300F@Rva00072FE6@@QAEXU?$_Rb_tree_iterator@U?$pair@$$CBHPAX@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHPAX@_STL@@@2@@_STL@@0@Z @0x0007300F 68B via STLPort range erase plus rowed clear
// Evidence: vendor/stlport/stl/_tree.h erase(first last) calls clear on full range else loops via increment plus single erase
// Retail calls clear 0x00072FE6 plus increment 0x00024250 plus single erase 0x005530A8 for map int to voidptr
// Same 68B shape as rowed range erase 0x004ABC85 in stlport_map_int_ptr_o1.cpp modulo clear callee
// Contiguous with clear 0x00072FE6 and set insert 0x00073053 and unblocks caller 0x000733D8
#include <map>

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
struct Rva00072FE6 {
  Rva00072F7CNode *header00;
  unsigned count04;
  char unknown08[16];
  void rva00072FE6();
  typedef _STL::pair<const int, void*> V;
  typedef _STL::_Rb_tree_iterator<V, _STL::_Nonconst_traits<V> > iterator;
  // ?begin@Rva00072FE6@@QAE?AU?$_Rb_tree_iterator@U?$pair@$$CBHPAX@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHPAX@_STL@@@2@@_STL@@XZ present-unmatched
  iterator begin() {
    iterator it;
    it._M_node = (::_STL::_Rb_tree_node_base*)header00->left08;
    return it;
  }
  // ?end@Rva00072FE6@@QAE?AU?$_Rb_tree_iterator@U?$pair@$$CBHPAX@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHPAX@_STL@@@2@@_STL@@XZ present-unmatched
  iterator end() {
    iterator it;
    it._M_node = (::_STL::_Rb_tree_node_base*)header00;
    return it;
  }
  void rva0007300F(iterator first, iterator last);
  unsigned int rva000733D8(const int &key);
};
void Rva00072FE6::rva0007300F(iterator first, iterator last) {
  typedef V VV;
  typedef _STL::_Rb_tree<int, VV, _STL::_Select1st<VV>, _STL::less<int>, _STL::allocator<VV> > Tree;
  if (first == begin() && last == end())
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
