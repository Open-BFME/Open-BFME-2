// cl: /O1 /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?_M_create_node@?$_Rb_tree@I... (map<unsigned int, bool> tree), retail
// 0x002D464E (34 bytes). _Rb_tree::_M_create_node for the unsigned-to-bool
// map: allocates a 0x18 node (16-byte links plus the 8-byte pair) through
// the rowed byte allocator at 0x307F0, then constructs the pair value
// through the rowed _Construct at 0x1FF5AC. The pair value type is
// call-proven: retail's own call displacement targets the rowed
// pair<const unsigned,bool> _Construct, and node bytes 0x18 fix the 8-byte
// pair (multimap shares the _Rb_tree name, so map-vs-multimap needs no
// disambiguation). Recipe: stlport_rb_tree_hint_asciistring_set (custom
// No-exceptions MALLOC shape, no allocation-cleanup catch path); the
// _Construct specialization is declared only so the call resolves through
// its row.
#include <map>

typedef _STL::pair<const unsigned int, bool> UIntBoolMapPair;
typedef _STL::_Rb_tree<unsigned int, UIntBoolMapPair,
	_STL::_Select1st<UIntBoolMapPair>, _STL::less<unsigned int>,
	_STL::allocator<UIntBoolMapPair> > UIntBoolMapTree;

namespace _STL {
template <> class allocator<char> {
public:
	static char *allocate(unsigned int bytes, const void *hint);
};
template <> void _Construct<UIntBoolMapTree::value_type>(
	UIntBoolMapTree::value_type *, const UIntBoolMapTree::value_type &);
}

// ?_M_create_node@?$_Rb_tree@IU?$pair@$$CBI_N@_STL@@U?$_Select1st@U?$pair@$$CBI_N@_STL@@@2@U?$less@I@2@V?$allocator@U?$pair@$$CBI_N@_STL@@@2@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBI_N@_STL@@@2@ABU?$pair@$$CBI_N@2@@Z
template <>
UIntBoolMapTree::_Link_type UIntBoolMapTree::_M_create_node(const UIntBoolMapPair &value)
{
	_Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<UIntBoolMapPair>), 0);
	_STL::_Construct(&node->_M_value_field, value);
	return node;
}

template UIntBoolMapTree::_Link_type UIntBoolMapTree::_M_create_node(const UIntBoolMapPair &);
