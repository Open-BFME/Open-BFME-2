// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// BFME2 STLport tree with an AsciiString key and a four-byte opaque mapped value.
// The application's original mapped-type name is not established.
// Identity chain: hinted insert 0x00058EAD -> ordinary insert 0x00058CB3
// and _M_insert 0x0005808E -> _M_create_node 0x00056F9E.
// The node allocator requests 24 bytes: 16 bytes tree links + 8 bytes value.
// _Construct at 0x00055924 calls the independently matched 27-byte pair copy
// at 0x00466EA7: AsciiString copy at offset 0, one raw dword at offset 4.
// The comparisons reach the independently matched AsciiString operator<,
// RVA 0x0005598C, and both iterator-step helpers are already independently matched.
// Semantic reference: reference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib/
// RvaTreeInsertUniqueHint.cpp. Here /O1 leaves the comparator out of line.
#include <map>
#include "ascii_string.h"
bool operator<(const AsciiString &, const AsciiString &);
struct TreeHintPayload0005808E { char m_body[4]; };
typedef _STL::pair<const AsciiString, TreeHintPayload0005808E> TreeHintPair0005808E;
typedef _STL::_Rb_tree<AsciiString, TreeHintPair0005808E, _STL::_Select1st<TreeHintPair0005808E>, _STL::less<AsciiString>, _STL::allocator<TreeHintPair0005808E> > TreeHint0005808E;
// BFME replaces STLport allocation with a static byte allocator (RVA 0x307F0).
namespace _STL {
template <> class allocator<char> {
public:
    static char *allocate(unsigned int bytes, const void *hint);
};
}

// Retail 0x00056F9E allocates the node, then constructs its value.
// Unlike stock STLport, this retail body has no allocation-cleanup catch path.
// ?_M_create_node@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@UTreeHintPayload0005808E@@@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@UTreeHintPayload0005808E@@@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@UTreeHintPayload0005808E@@@_STL@@@3@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@UTreeHintPayload0005808E@@@_STL@@@2@ABU?$pair@$$CBVAsciiString@@UTreeHintPayload0005808E@@@2@@Z
template <>
TreeHint0005808E::_Link_type TreeHint0005808E::_M_create_node(const TreeHintPair0005808E &value)
{
    _Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<TreeHintPair0005808E>), 0);
    _STL::_Construct(&node->_M_value_field, value);
    return node;
}

template TreeHint0005808E::iterator TreeHint0005808E::insert_unique(TreeHint0005808E::iterator, const TreeHintPair0005808E &);

// The map wrapper directly calls this tree's verified hinted insertion.
typedef _STL::map<AsciiString,TreeHintPayload0005808E,_STL::less<AsciiString >,_STL::allocator<TreeHintPair0005808E> > MapInsert00058ead;
template MapInsert00058ead::iterator MapInsert00058ead::insert(MapInsert00058ead::iterator, const TreeHintPair0005808E &);
