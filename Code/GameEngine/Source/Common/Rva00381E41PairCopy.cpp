// cl: /O1 /arch:SSE /G7 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfmealloc
// stlport
// STLport 4.5.3 pair copy (381E41, 21B), clone (3834AF, 30B), and node
// creator (382BA1, 34B). Emit only these members. The old whole-map
// instantiations also emitted unrelated, non-retail allocation helpers.
// The creator allocates a measured 20B node through 307F0 and copies the
// byte/word value at +16 through the rowed 3821A0 helper. Its member name is
// already identified by the clone and the uchar-map insertion call sites.
// It replaces the address-named free-function view at the same native RVA;
// its receiver is unused. Short remains a stand-in with unproved signedness.
#include <map>

typedef _STL::pair<const unsigned char, short> BfmeByteWordNodeValue;
typedef _STL::_Rb_tree<unsigned char, BfmeByteWordNodeValue,
    _STL::_Select1st<BfmeByteWordNodeValue>, _STL::less<unsigned char>,
    _STL::allocator<BfmeByteWordNodeValue> > BfmeByteWordNodeTree;
void Rva003821A0Copy(void *, void *);
// ?_M_create_node@?$_Rb_tree@EU?$pair@$$CBEF@_STL@@U?$_Select1st@U?$pair@$$CBEF@_STL@@@2@U?$less@E@2@V?$allocator@U?$pair@$$CBEF@_STL@@@2@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBEF@_STL@@@2@ABU?$pair@$$CBEF@2@@Z
template <> __declspec(noinline) inline _STL::_Rb_tree_node<BfmeByteWordNodeValue> *
BfmeByteWordNodeTree::_M_create_node(const BfmeByteWordNodeValue &value)
{
    _STL::_Rb_tree_node<BfmeByteWordNodeValue> *node =
        (_STL::_Rb_tree_node<BfmeByteWordNodeValue> *)_STL::allocator<char>::allocate(
            sizeof(_STL::_Rb_tree_node<BfmeByteWordNodeValue>), 0);
    Rva003821A0Copy(&node->_M_value_field, (void *)&value);
    return node;
}

// ?_M_clone_node@?$_Rb_tree@EU?$pair@$$CBEF@_STL@@U?$_Select1st@U?$pair@$$CBEF@_STL@@@2@U?$less@E@2@V?$allocator@U?$pair@$$CBEF@_STL@@@2@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBEF@_STL@@@2@PAU32@@Z
template <> inline _STL::_Rb_tree_node<BfmeByteWordNodeValue> *
BfmeByteWordNodeTree::_M_clone_node(_STL::_Rb_tree_node<BfmeByteWordNodeValue> *node)
{
    _STL::_Rb_tree_node<BfmeByteWordNodeValue> *copy = _M_create_node(node->_M_value_field);
    // Save color before clearing the links; the new clone has distinct storage.
    _STL::_Rb_tree_Color_type color = node->_M_color;
    copy->_M_left = 0;
    copy->_M_right = 0;
    copy->_M_color = color;
    return copy;
}

template struct _STL::pair<const unsigned char, short>;
template _STL::_Rb_tree_node<BfmeByteWordNodeValue> *
BfmeByteWordNodeTree::_M_clone_node(_STL::_Rb_tree_node<BfmeByteWordNodeValue> *node);
