// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// BFME2 STLport tree with an AsciiString key and a four-byte opaque mapped value.
// The application's original mapped-type name is not established.
// Identity chain: hinted insert 0x002A40C6 -> ordinary insert 0x002A1E31
// and _M_insert 0x002A1D9D -> _M_create_node 0x002A1516.
// The node allocator requests 24 bytes: 16 bytes tree links + 8 bytes value.
// _Construct at 0x0029FC87 calls the independently matched 27-byte pair copy
// at 0x00466EA7: AsciiString copy at offset 0, one raw dword at offset 4.
// The comparisons reach the independently matched AsciiString operator<,
// RVA 0x0005598C, and both iterator-step helpers are already independently matched.
// Semantic reference: reference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib/
// RvaTreeInsertUniqueHint.cpp. Here /O1 leaves the comparator out of line.
#include <map>
#include "ascii_string.h"
bool operator<(const AsciiString &, const AsciiString &);
struct TreeHintPayload002A1D9D { char m_body[4]; };
typedef _STL::pair<const AsciiString, TreeHintPayload002A1D9D> TreeHintPair002A1D9D;
typedef _STL::_Rb_tree<AsciiString, TreeHintPair002A1D9D, _STL::_Select1st<TreeHintPair002A1D9D>, _STL::less<AsciiString>, _STL::allocator<TreeHintPair002A1D9D> > TreeHint002A1D9D;
// BFME replaces STLport allocation with a static byte allocator (RVA 0x307F0).
namespace _STL {
template <> class allocator<char> {
public:
    static char *allocate(unsigned int bytes, const void *hint);
};
}

// Retail 0x002A1516 allocates the node, then constructs its value.
// Unlike stock STLport, this retail body has no allocation-cleanup catch path.
// ?_M_create_node@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@UTreeHintPayload002A1D9D@@@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@UTreeHintPayload002A1D9D@@@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@UTreeHintPayload002A1D9D@@@_STL@@@3@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@UTreeHintPayload002A1D9D@@@_STL@@@2@ABU?$pair@$$CBVAsciiString@@UTreeHintPayload002A1D9D@@@2@@Z
template <>
TreeHint002A1D9D::_Link_type TreeHint002A1D9D::_M_create_node(const TreeHintPair002A1D9D &value)
{
    _Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<TreeHintPair002A1D9D>), 0);
    _STL::_Construct(&node->_M_value_field, value);
    return node;
}

template TreeHint002A1D9D::iterator TreeHint002A1D9D::insert_unique(TreeHint002A1D9D::iterator, const TreeHintPair002A1D9D &);

// The map wrapper directly calls this tree's verified hinted insertion.
typedef _STL::map<AsciiString,TreeHintPayload002A1D9D,_STL::less<AsciiString >,_STL::allocator<TreeHintPair002A1D9D> > MapInsert002a40c6;
template MapInsert002a40c6::iterator MapInsert002a40c6::insert(MapInsert002a40c6::iterator, const TreeHintPair002A1D9D &);
