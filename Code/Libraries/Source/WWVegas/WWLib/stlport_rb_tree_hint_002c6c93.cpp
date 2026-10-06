// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// BFME2 STLport tree with an AsciiString key and a four-byte opaque mapped value.
// The application's original mapped-type name is not established.
// Identity chain: hinted insert 0x002C6C93 -> ordinary insert 0x001F8E93
// and _M_insert 0x001F8ACB -> _M_create_node 0x001F8485.
// The node allocator requests 24 bytes: 16 bytes tree links + 8 bytes value.
// _Construct at 0x001F6882 calls the independently matched 27-byte pair copy
// at 0x00466EA7: AsciiString copy at offset 0, one raw dword at offset 4.
// The comparisons reach the independently matched AsciiString operator<,
// RVA 0x0005598C, and both iterator-step helpers are already independently matched.
// Semantic reference: reference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib/
// RvaTreeInsertUniqueHint.cpp. Here /O1 leaves the comparator out of line.
#include <map>
class AsciiString { public: AsciiString(const AsciiString &); ~AsciiString(); private: void *m_data; };
bool operator<(const AsciiString &, const AsciiString &);
struct TreeHintPayload001F8ACB { char m_body[4]; };
typedef _STL::pair<const AsciiString, TreeHintPayload001F8ACB> TreeHintPair001F8ACB;
typedef _STL::_Rb_tree<AsciiString, TreeHintPair001F8ACB, _STL::_Select1st<TreeHintPair001F8ACB>, _STL::less<AsciiString>, _STL::allocator<TreeHintPair001F8ACB> > TreeHint001F8ACB;
// BFME replaces STLport allocation with a static byte allocator (RVA 0x307F0).
namespace _STL {
template <> class allocator<char> {
public:
    static char *allocate(unsigned int bytes, const void *hint);
};
}

// Retail 0x001F8485 allocates the node, then constructs its value.
// Unlike stock STLport, this retail body has no allocation-cleanup catch path.
// ?_M_create_node@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@UTreeHintPayload001F8ACB@@@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@UTreeHintPayload001F8ACB@@@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@UTreeHintPayload001F8ACB@@@_STL@@@3@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@UTreeHintPayload001F8ACB@@@_STL@@@2@ABU?$pair@$$CBVAsciiString@@UTreeHintPayload001F8ACB@@@2@@Z
template <>
TreeHint001F8ACB::_Link_type TreeHint001F8ACB::_M_create_node(const TreeHintPair001F8ACB &value)
{
    _Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<TreeHintPair001F8ACB>), 0);
    _STL::_Construct(&node->_M_value_field, value);
    return node;
}

template TreeHint001F8ACB::iterator TreeHint001F8ACB::insert_unique(TreeHint001F8ACB::iterator, const TreeHintPair001F8ACB &);

// The map wrapper directly calls this tree's verified hinted insertion.
typedef _STL::map<AsciiString,TreeHintPayload001F8ACB,_STL::less<AsciiString >,_STL::allocator<TreeHintPair001F8ACB> > MapInsert002c6c93;
template MapInsert002c6c93::iterator MapInsert002c6c93::insert(MapInsert002c6c93::iterator, const TreeHintPair001F8ACB &);

// Retail node1F8485 is called by clone407DC2, then recursive copy407FF7.
// These direct calls establish this typed copy family beyond masked shape.
template TreeHint001F8ACB::_Rb_tree(const TreeHint001F8ACB &);
