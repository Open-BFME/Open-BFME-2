// cl: /DNDEBUG /MD /EHsc /Od /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep

// Retail 0x0082B970 is STLport's
//   _STL::_Rb_global<bool>::_Rotate_left(_Rb_tree_node_base*,
//                                        _Rb_tree_node_base*&)
// (?_Rotate_left@?$_Rb_global@_N@_STL@@SAXPAU_Rb_tree_node_base@2@AAPAU32@@Z).
// The body below is verbatim from vendor/stlport/stl/_tree.c; it is emitted
// under the object symbol the ledger pins for this row.
//
// Retail built the STLport tree helpers unoptimised, hence /Od above: __y
// lives on the stack ([ebp-4]) rather than in a register.

namespace _STL {

typedef bool _Rb_tree_Color_type;

struct _Rb_tree_node_base
{
  typedef _Rb_tree_Color_type _Color_type;
  typedef _Rb_tree_node_base* _Base_ptr;

  _Color_type _M_color;
  _Base_ptr _M_parent;
  _Base_ptr _M_left;
  _Base_ptr _M_right;
};

}

extern "C" void __cdecl
bfme_RbGlobalBoolRotateLeft_82B970(_STL::_Rb_tree_node_base* __x,
                                   _STL::_Rb_tree_node_base*& __root)
{
  _STL::_Rb_tree_node_base* __y = __x->_M_right;
  __x->_M_right = __y->_M_left;
  if (__y->_M_left !=0)
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
