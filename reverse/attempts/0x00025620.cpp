// ?_Rebalance_for_erase@?$_Rb_global@_N@_STL@@SAPAU_Rb_tree_node_base@2@PAU32@AAPAU32@11@Z
// partial score=0.95 date=2026-09-03
// cl: /Od /GX- /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 _Rb_global<bool>'s two rotations and the red-black delete
// fixup, all three verbatim from vendor/stlport/stl/_tree.c.
//
// The rotations were already landed here under C-linkage placeholder names
// carrying an Open-BFME-1 address; the ported file itself records the real
// STLport symbol, so the rows are repointed at this unit under it.
//
// What the fixup calls decides the shape, and retail is explicit about it:
// _S_minimum and _S_maximum are called out of line at 0x000237F0 and
// 0x00023810, both rotations are called three times each, and swap is NOT
// called. So the colour exchange is written out with its own temporary, and
// that temporary is the sixth stack slot - the frame is 0x18, and with the
// upstream swap() call it comes out 0x14 and nothing after it lines up.
//
// _M_color is bool, not int, which is what the ported rotate unit already
// carried and what keeps the exchange a byte copy.
//
// /Od throughout: retail built the tree helpers unoptimised.

namespace _STL
{

typedef bool _Rb_tree_Color_type;

const _Rb_tree_Color_type _S_rb_tree_red = false;
const _Rb_tree_Color_type _S_rb_tree_black = true;

struct _Rb_tree_node_base
{
	typedef _Rb_tree_Color_type _Color_type;
	typedef _Rb_tree_node_base *_Base_ptr;

	_Color_type _M_color;
	_Base_ptr _M_parent;
	_Base_ptr _M_left;
	_Base_ptr _M_right;

	static _Base_ptr __cdecl _S_minimum(_Base_ptr __x);
	static _Base_ptr __cdecl _S_maximum(_Base_ptr __x);
};

// STLport's int swap, at 0x00024750. It is NOT what this fixup uses for the
// colour exchange - retail inlines that - but it belongs to the same header
// and placed here by byte-scan, so it stays.
void swap(int &a, int &b)
{
	int t = a;
	a = b;
	b = t;
}

template <class _Dummy>
class _Rb_global
{
public:
	static void __cdecl _Rotate_left(_Rb_tree_node_base *__x,
			_Rb_tree_node_base *&__root);
	static void __cdecl _Rotate_right(_Rb_tree_node_base *__x,
			_Rb_tree_node_base *&__root);
	static _Rb_tree_node_base *__cdecl _Rebalance_for_erase(
			_Rb_tree_node_base *__z, _Rb_tree_node_base *&__root,
			_Rb_tree_node_base *&__leftmost, _Rb_tree_node_base *&__rightmost);
};

template <class _Dummy>
void __cdecl _Rb_global<_Dummy>::_Rotate_left(_Rb_tree_node_base *__x,
		_Rb_tree_node_base *&__root)
{
	_Rb_tree_node_base *__y = __x->_M_right;
	__x->_M_right = __y->_M_left;
	if (__y->_M_left != 0)
		__y->_M_left->_M_parent = __x;
	__y->_M_parent = __x->_M_parent;

	if (__x == __root)
		__root = __y;
	else if (__x == __x->_M_parent->_M_left)
		__x->_M_parent->_M_left = __y;
	else
		__x->_M_parent->_M_right = __y;
	__y->_M_left = __x;
	__x->_M_parent = __y;
}

template <class _Dummy>
void __cdecl _Rb_global<_Dummy>::_Rotate_right(_Rb_tree_node_base *__x,
		_Rb_tree_node_base *&__root)
{
	_Rb_tree_node_base *__y = __x->_M_left;
	__x->_M_left = __y->_M_right;
	if (__y->_M_right != 0)
		__y->_M_right->_M_parent = __x;
	__y->_M_parent = __x->_M_parent;

	if (__x == __root)
		__root = __y;
	else if (__x == __x->_M_parent->_M_right)
		__x->_M_parent->_M_right = __y;
	else
		__x->_M_parent->_M_left = __y;
	__y->_M_right = __x;
	__x->_M_parent = __y;
}

template <class _Dummy>
_Rb_tree_node_base *__cdecl _Rb_global<_Dummy>::_Rebalance_for_erase(
		_Rb_tree_node_base *__z, _Rb_tree_node_base *&__root,
		_Rb_tree_node_base *&__leftmost, _Rb_tree_node_base *&__rightmost)
{
  _Rb_tree_node_base* __y = __z;
  _Rb_tree_node_base* __x = 0;
  _Rb_tree_node_base* __x_parent = 0;
  if (__y->_M_left == 0)     // __z has at most one non-null child. y == z.
    __x = __y->_M_right;     // __x might be null.
  else
    if (__y->_M_right == 0)  // __z has exactly one non-null child. y == z.
      __x = __y->_M_left;    // __x is not null.
    else {                   // __z has two non-null children.  Set __y to
      __y = __y->_M_right;   //   __z's successor.  __x might be null.
      while (__y->_M_left != 0)
        __y = __y->_M_left;
      __x = __y->_M_right;
    }
  if (__y != __z) {          // relink y in place of z.  y is z's successor
    __z->_M_left->_M_parent = __y; 
    __y->_M_left = __z->_M_left;
    if (__y != __z->_M_right) {
      __x_parent = __y->_M_parent;
      if (__x) __x->_M_parent = __y->_M_parent;
      __y->_M_parent->_M_left = __x;      // __y must be a child of _M_left
      __y->_M_right = __z->_M_right;
      __z->_M_right->_M_parent = __y;
    }
    else
      __x_parent = __y;  
    if (__root == __z)
      __root = __y;
    else if (__z->_M_parent->_M_left == __z)
      __z->_M_parent->_M_left = __y;
    else 
      __z->_M_parent->_M_right = __y;
    __y->_M_parent = __z->_M_parent;
    _Rb_tree_Color_type __c = __y->_M_color;
    __y->_M_color = __z->_M_color;
    __z->_M_color = __c;
    __y = __z;
    // __y now points to node to be actually deleted
  }
  else {                        // __y == __z
    __x_parent = __y->_M_parent;
    if (__x) __x->_M_parent = __y->_M_parent;   
    if (__root == __z)
      __root = __x;
    else 
      if (__z->_M_parent->_M_left == __z)
        __z->_M_parent->_M_left = __x;
      else
        __z->_M_parent->_M_right = __x;
    if (__leftmost == __z) 
      if (__z->_M_right == 0)        // __z->_M_left must be null also
        __leftmost = __z->_M_parent;
    // makes __leftmost == _M_header if __z == __root
      else
        __leftmost = _Rb_tree_node_base::_S_minimum(__x);
    if (__rightmost == __z)  
      if (__z->_M_left == 0)         // __z->_M_right must be null also
        __rightmost = __z->_M_parent;  
    // makes __rightmost == _M_header if __z == __root
      else                      // __x == __z->_M_left
        __rightmost = _Rb_tree_node_base::_S_maximum(__x);
  }
  if (__y->_M_color != _S_rb_tree_red) { 
    while (__x != __root && (__x == 0 || __x->_M_color == _S_rb_tree_black))
      if (__x == __x_parent->_M_left) {
        _Rb_tree_node_base* __w = __x_parent->_M_right;
        if (__w->_M_color == _S_rb_tree_red) {
          __w->_M_color = _S_rb_tree_black;
          __x_parent->_M_color = _S_rb_tree_red;
          _Rotate_left(__x_parent, __root);
          __w = __x_parent->_M_right;
        }
        if ((__w->_M_left == 0 || 
             __w->_M_left->_M_color == _S_rb_tree_black) && (__w->_M_right == 0 || 
             __w->_M_right->_M_color == _S_rb_tree_black)) {
          __w->_M_color = _S_rb_tree_red;
          __x = __x_parent;
          __x_parent = __x_parent->_M_parent;
        } else {
          if (__w->_M_right == 0 || 
              __w->_M_right->_M_color == _S_rb_tree_black) {
            if (__w->_M_left) __w->_M_left->_M_color = _S_rb_tree_black;
            __w->_M_color = _S_rb_tree_red;
            _Rotate_right(__w, __root);
            __w = __x_parent->_M_right;
          }
          __w->_M_color = __x_parent->_M_color;
          __x_parent->_M_color = _S_rb_tree_black;
          if (__w->_M_right) __w->_M_right->_M_color = _S_rb_tree_black;
          _Rotate_left(__x_parent, __root);
          break;
        }
      } else {                  // same as above, with _M_right <-> _M_left.
        _Rb_tree_node_base* __w = __x_parent->_M_left;
        if (__w->_M_color == _S_rb_tree_red) {
          __w->_M_color = _S_rb_tree_black;
          __x_parent->_M_color = _S_rb_tree_red;
          _Rotate_right(__x_parent, __root);
          __w = __x_parent->_M_left;
        }
        if ((__w->_M_right == 0 || 
             __w->_M_right->_M_color == _S_rb_tree_black) && (__w->_M_left == 0 || 
             __w->_M_left->_M_color == _S_rb_tree_black)) {
          __w->_M_color = _S_rb_tree_red;
          __x = __x_parent;
          __x_parent = __x_parent->_M_parent;
        } else {
          if (__w->_M_left == 0 || 
              __w->_M_left->_M_color == _S_rb_tree_black) {
            if (__w->_M_right) __w->_M_right->_M_color = _S_rb_tree_black;
            __w->_M_color = _S_rb_tree_red;
            _Rotate_left(__w, __root);
            __w = __x_parent->_M_left;
          }
          __w->_M_color = __x_parent->_M_color;
          __x_parent->_M_color = _S_rb_tree_black;
          if (__w->_M_left) __w->_M_left->_M_color = _S_rb_tree_black;
          _Rotate_right(__x_parent, __root);
          break;
        }
      }
    if (__x) __x->_M_color = _S_rb_tree_black;
  }
  return __y;
}

template void __cdecl _Rb_global<bool>::_Rotate_left(
		_Rb_tree_node_base *, _Rb_tree_node_base *&);
template void __cdecl _Rb_global<bool>::_Rotate_right(
		_Rb_tree_node_base *, _Rb_tree_node_base *&);
template _Rb_tree_node_base *__cdecl _Rb_global<bool>::_Rebalance_for_erase(
		_Rb_tree_node_base *, _Rb_tree_node_base *&, _Rb_tree_node_base *&,
		_Rb_tree_node_base *&);

}
