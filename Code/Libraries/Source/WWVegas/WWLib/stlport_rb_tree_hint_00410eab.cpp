// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// BFME2 STLport tree with an AsciiString key and a four-byte opaque mapped value.
// The application's original mapped-type name is not established.
// Identity chain: hinted insert 0x00410EAB -> ordinary insert 0x00410BAB
// and _M_insert 0x00410B17 -> _M_create_node 0x004109F2.
// The node allocator requests 24 bytes: 16 bytes tree links + 8 bytes value.
// _Construct at 0x00410765 calls the independently matched 27-byte pair copy
// at 0x00466EA7: AsciiString copy at offset 0, one raw dword at offset 4.
// The comparisons reach the independently matched AsciiString operator<,
// RVA 0x0005598C, and both iterator-step helpers are already independently matched.
// Semantic reference: reference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib/
// RvaTreeInsertUniqueHint.cpp. Here /O1 leaves the comparator out of line.
#include <map>
#include "ascii_string.h"
bool operator<(const AsciiString &, const AsciiString &);
struct TreeHintPayload00410B17 { char m_body[4]; };
typedef _STL::pair<const AsciiString, TreeHintPayload00410B17> TreeHintPair00410B17;
typedef _STL::_Rb_tree<AsciiString, TreeHintPair00410B17, _STL::_Select1st<TreeHintPair00410B17>, _STL::less<AsciiString>, _STL::allocator<TreeHintPair00410B17> > TreeHint00410B17;
// BFME replaces STLport allocation with a static byte allocator (RVA 0x307F0).
namespace _STL {
template <> class allocator<char> {
public:
    static char *allocate(unsigned int bytes, const void *hint);
};
}

// Retail 0x004109F2 allocates the node, then constructs its value.
// Unlike stock STLport, this retail body has no allocation-cleanup catch path.
// ?_M_create_node@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@UTreeHintPayload00410B17@@@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@UTreeHintPayload00410B17@@@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@UTreeHintPayload00410B17@@@_STL@@@3@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@UTreeHintPayload00410B17@@@_STL@@@2@ABU?$pair@$$CBVAsciiString@@UTreeHintPayload00410B17@@@2@@Z
template <>
TreeHint00410B17::_Link_type TreeHint00410B17::_M_create_node(const TreeHintPair00410B17 &value)
{
    _Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<TreeHintPair00410B17>), 0);
    _STL::_Construct(&node->_M_value_field, value);
    return node;
}

template TreeHint00410B17::iterator TreeHint00410B17::insert_unique(TreeHint00410B17::iterator, const TreeHintPair00410B17 &);

// The map wrapper directly calls this tree's verified hinted insertion.
typedef _STL::map<AsciiString,TreeHintPayload00410B17,_STL::less<AsciiString >,_STL::allocator<TreeHintPair00410B17> > MapInsert00410eab;
template MapInsert00410eab::iterator MapInsert00410eab::insert(MapInsert00410eab::iterator, const TreeHintPair00410B17 &);
