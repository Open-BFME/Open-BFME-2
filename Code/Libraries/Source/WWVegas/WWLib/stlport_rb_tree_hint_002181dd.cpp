// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS -Ireference/open-bfme-1/game/GameEngine/Source/Common /Ireference/shims/bfme2_ascii -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/shims/bfmealloc
// stlport
// BFME2 STLport tree with an AsciiString key and a four-byte opaque mapped value.
// The application's original mapped-type name is not established.
// Identity chain: hinted insert 0x002181DD -> ordinary insert 0x00217E77
// and _M_insert 0x00217DE3 -> _M_create_node 0x00217A8E.
// The node allocator requests 24 bytes: 16 bytes tree links + 8 bytes value.
// _Construct at 0x002178CB calls the independently matched 27-byte pair copy
// at 0x00466EA7: AsciiString copy at offset 0, one raw dword at offset 4.
// The comparisons reach the independently matched AsciiString operator<,
// RVA 0x0005598C, and both iterator-step helpers are already independently matched.
// Semantic reference: reference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib/
// RvaTreeInsertUniqueHint.cpp. Here /O1 leaves the comparator out of line.
#include <map>
#include "ascii_string.h"
bool operator<(const AsciiString &, const AsciiString &);
struct TreeHintPayload00217DE3 { int m_val; TreeHintPayload00217DE3() : m_val(0) {} TreeHintPayload00217DE3(const TreeHintPayload00217DE3 &o) : m_val(o.m_val) {} };
typedef _STL::pair<const AsciiString, TreeHintPayload00217DE3> TreeHintPair00217DE3;
typedef _STL::_Rb_tree<AsciiString, TreeHintPair00217DE3, _STL::_Select1st<TreeHintPair00217DE3>, _STL::less<AsciiString>, _STL::allocator<TreeHintPair00217DE3> > TreeHint00217DE3;
// BFME replaces STLport allocation with a static byte allocator (RVA 0x307F0).

// Retail 0x00217A8E allocates the node, then constructs its value.
// Unlike stock STLport, this retail body has no allocation-cleanup catch path.
// ?_M_create_node@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@UTreeHintPayload00217DE3@@@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@UTreeHintPayload00217DE3@@@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@UTreeHintPayload00217DE3@@@_STL@@@3@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@UTreeHintPayload00217DE3@@@_STL@@@2@ABU?$pair@$$CBVAsciiString@@UTreeHintPayload00217DE3@@@2@@Z
template <>
TreeHint00217DE3::_Link_type TreeHint00217DE3::_M_create_node(const TreeHintPair00217DE3 &value)
{
    _Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<TreeHintPair00217DE3>), 0);
    _STL::_Construct(&node->_M_value_field, value);
    return node;
}

// Retail 0x00217E77 uses the header node as the first insertion hint.
// ?insert_unique@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@UTreeHintPayload00217DE3@@@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@UTreeHintPayload00217DE3@@@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@UTreeHintPayload00217DE3@@@_STL@@@3@@_STL@@QAE?AU?$pair@U?$_Rb_tree_iterator@U?$pair@$$CBVAsciiString@@UTreeHintPayload00217DE3@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBVAsciiString@@UTreeHintPayload00217DE3@@@_STL@@@2@@_STL@@_N@2@ABU?$pair@$$CBVAsciiString@@UTreeHintPayload00217DE3@@@2@@Z
template <>
_STL::pair<TreeHint00217DE3::iterator, bool>
TreeHint00217DE3::insert_unique(const TreeHintPair00217DE3 &value)
{
	_Link_type parent = this->_M_header._M_data;
	_Link_type node = _M_root();
	bool before = true;
	while (node != 0)
	{
		parent = node;
		before = _M_key_compare(_STL::_Select1st<TreeHintPair00217DE3>()(value), _S_key(node));
		node = before ? _S_left(node) : _S_right(node);
	}
	iterator hint = iterator(parent);
	if (before && hint == begin())
		return _STL::pair<iterator, bool>(_M_insert(parent, parent, value), true);
	if (before)
		--hint;
	if (_M_key_compare(_S_key(hint._M_node), _STL::_Select1st<TreeHintPair00217DE3>()(value)))
		return _STL::pair<iterator, bool>(_M_insert(node, parent, value), true);
	return _STL::pair<iterator, bool>(hint, false);
}

template TreeHint00217DE3::iterator TreeHint00217DE3::insert_unique(TreeHint00217DE3::iterator, const TreeHintPair00217DE3 &);

// The map wrapper directly calls this tree's verified hinted insertion.
typedef _STL::map<AsciiString,TreeHintPayload00217DE3,_STL::less<AsciiString >,_STL::allocator<TreeHintPair00217DE3> > MapInsert002181dd;
template MapInsert002181dd::iterator MapInsert002181dd::insert(MapInsert002181dd::iterator, const TreeHintPair00217DE3 &);
