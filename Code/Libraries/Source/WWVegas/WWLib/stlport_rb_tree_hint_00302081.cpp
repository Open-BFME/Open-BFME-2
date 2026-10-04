// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// BFME2 STLport tree: AsciiString key and opaque 1-byte mapped value.
// hint 0x302081 -> insert 0x207a04 -> _M_insert 0x207343 -> node 0x206C76.
// The node allocates 24 bytes and constructs its 8-byte value at node+16.
// _Construct 0x2058E3 calls pair copy 0x5117F6: AsciiString copy 0x365F0,
// followed by a raw 1-byte copy of the mapped value at pair offset +4.
// Comparison reaches the established AsciiString operator< at 0x5598C.
// Semantic donor: BFME1 RvaTreeInsertUniqueHint.cpp and STLport pair/tree.
#include <stl/_prolog.h>
#include <stl/type_traits.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#undef _STLP_DEFAULT_CONSTRUCTED
#define _STLP_DEFAULT_CONSTRUCTED(_TTp) _TTp()
#include <map>
#include "ascii_string.h"
bool operator<(const AsciiString &, const AsciiString &);
// Retail pair copying transfers this 1-byte mapped value without further calls.
// Its original application type and any ownership/destruction behavior are unknown.
struct TreeHintPayload00207343 {
    unsigned char value;
    TreeHintPayload00207343() : value(0) {}
};

typedef _STL::pair<const AsciiString, TreeHintPayload00207343> TreeHintPair00207343;
typedef _STL::_Rb_tree<AsciiString, TreeHintPair00207343, _STL::_Select1st<TreeHintPair00207343>, _STL::less<AsciiString>, _STL::allocator<TreeHintPair00207343> > TreeHint00207343;
// Retail uses its static byte allocator and has no node cleanup catch block.
namespace _STL {
template <> class allocator<char> {
public:
    static char *allocate(unsigned int bytes, const void *hint);
};
}
// ?_M_create_node@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@UTreeHintPayload00207343@@@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@UTreeHintPayload00207343@@@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@UTreeHintPayload00207343@@@_STL@@@3@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@UTreeHintPayload00207343@@@_STL@@@2@ABU?$pair@$$CBVAsciiString@@UTreeHintPayload00207343@@@2@@Z
template <>
TreeHint00207343::_Link_type TreeHint00207343::_M_create_node(const TreeHintPair00207343 &value)
{
    _Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<TreeHintPair00207343>), 0);
    _STL::_Construct(&node->_M_value_field, value);
    return node;
}
template TreeHint00207343::iterator TreeHint00207343::insert_unique(TreeHint00207343::iterator, const TreeHintPair00207343 &);

// The map wrapper directly calls this tree's verified hinted insertion.
typedef _STL::map<AsciiString,TreeHintPayload00207343,_STL::less<AsciiString >,_STL::allocator<TreeHintPair00207343> > MapInsert00302081;
template MapInsert00302081::iterator MapInsert00302081::insert(MapInsert00302081::iterator, const TreeHintPair00207343 &);
template TreeHintPayload00207343 &MapInsert00302081::operator[](const AsciiString &);
