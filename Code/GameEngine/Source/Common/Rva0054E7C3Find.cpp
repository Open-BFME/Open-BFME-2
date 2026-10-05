// cl: /O1
// stlport
//
// ??$__find@U?$_Rb_tree_iterator@HU?$_Const_traits@H@_STL@@@_STL@@H@_STL@@YA?AU?$_Rb_tree_iterator@HU?$_Const_traits@H@_STL@@@0@U10@0ABHABUinput_iterator_tag@0@@Z @0x0054E7C3 39B
// ??$find@U?$_Rb_tree_iterator@HU?$_Const_traits@H@_STL@@@_STL@@H@_STL@@YA?AU?$_Rb_tree_iterator@HU?$_Const_traits@H@_STL@@@0@U10@0ABH@Z @0x0054E82C 32B
// _STL::find / __find over set<int> const iterators (linear scan via rowed _M_increment 0x00024250).
// Evidence: retail loop cmp [eax+0x10] vs [edx] then increment matches input-iterator __find;
// forwarder at 0x0054E82C pushes dummy tag via lea [ebp+0xB] and calls 0x0054E7C3; chain 0x0054E86D
// calls find(begin at [header+8] end header) and tests != end; callers rowed; prev/next share /O1.
// Link: minimal _STL view (no <set>) emits only the two rows; the full header also emitted
// operator!=/* /++ COMDATs that lost against the first copy in link order.
namespace _STL {

struct _Rb_tree_node_base {
  int _M_color;
  struct _Rb_tree_node_base *_M_parent;
  struct _Rb_tree_node_base *_M_left;
  struct _Rb_tree_node_base *_M_right;
};

struct _Rb_tree_base_iterator {
  _Rb_tree_node_base *_M_node;
};

template <class _Tp>
struct _Const_traits {
  typedef _Tp value_type;
  typedef const _Tp &reference;
  typedef const _Tp *pointer;
};

template <class _Value, class _Traits>
struct _Rb_tree_iterator : public _Rb_tree_base_iterator {
};

struct input_iterator_tag {
};

template <class _Dummy>
struct _Rb_global {
  static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *);
};

template <class _InputIter, class _Tp>
_InputIter __find(_InputIter __first, _InputIter __last, const _Tp &__val, const input_iterator_tag &) {
  while (__first._M_node != __last._M_node && *(int *)((char *)__first._M_node + 0x10) != __val)
    __first._M_node = _Rb_global<bool>::_M_increment(__first._M_node);
  return __first;
}

template <class _InputIter, class _Tp>
_InputIter find(_InputIter __first, _InputIter __last, const _Tp &__val) {
  return __find(__first, __last, __val, input_iterator_tag());
}

typedef _Rb_tree_iterator<int, _Const_traits<int> > _SetIntConstIter;

template _SetIntConstIter __find(_SetIntConstIter, _SetIntConstIter, const int &, const input_iterator_tag &);
template _SetIntConstIter find(_SetIntConstIter, _SetIntConstIter, const int &);

}
