// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// BFME2 STLport tree: AsciiString key and opaque 0x100-byte mapped object.
// hint 0x304BEF -> insert 0x304607 -> _M_insert 0x304573 -> node 0x3044C3.
// The node allocates 0x114 bytes and constructs its 0x104-byte value at node+16.
// _Construct 0x304357 calls pair copy 0x303DDF: AsciiString copy 0x365F0,
// then the mapped object copy constructor 0x3039E8 on the second pair field.
// Comparison reaches the established AsciiString operator< at 0x5598C.
// Semantic donor: BFME1 RvaTreeInsertUniqueHint.cpp and STLport pair/tree.
#include <map>
template <class T> class StringBase
{
    void *m_data;
    StringBase(const StringBase<T> &);
    friend class AsciiString;
};
class AsciiString
{
public:
    __forceinline AsciiString(const AsciiString &that)
    {
        ((StringBase<char> *)this)->StringBase<char>::StringBase(*(const StringBase<char> *)&that);
    }
    ~AsciiString();
private:
    void *m_data;
};
bool operator<(const AsciiString &, const AsciiString &);
// Distinct 0x100-byte mapped object. The original application type is unknown.
// Pair copying passes destination+4 and source+4 to its copy constructor.
// Preserve its out-of-line copy and destruction; do not assume trivial ownership.
struct TreeHintOpaque00304573 {
    unsigned char m_body[0x100];
    TreeHintOpaque00304573(const TreeHintOpaque00304573 &);
    ~TreeHintOpaque00304573();
};

typedef _STL::pair<const AsciiString, TreeHintOpaque00304573> TreeHintPair00304573;
typedef _STL::_Rb_tree<AsciiString, TreeHintPair00304573, _STL::_Select1st<TreeHintPair00304573>, _STL::less<AsciiString>, _STL::allocator<TreeHintPair00304573> > TreeHint00304573;
// Retail uses its static byte allocator and has no node cleanup catch block.
namespace _STL {
template <> class allocator<char> {
public:
    static char *allocate(unsigned int bytes, const void *hint);
};
}
// ?_M_create_node@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@UTreeHintOpaque00304573@@@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@UTreeHintOpaque00304573@@@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@UTreeHintOpaque00304573@@@_STL@@@3@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@UTreeHintOpaque00304573@@@_STL@@@2@ABU?$pair@$$CBVAsciiString@@UTreeHintOpaque00304573@@@2@@Z
template <>
TreeHint00304573::_Link_type TreeHint00304573::_M_create_node(const TreeHintPair00304573 &value)
{
    _Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<TreeHintPair00304573>), 0);
    _STL::_Construct(&node->_M_value_field, value);
    return node;
}
template TreeHint00304573::iterator TreeHint00304573::insert_unique(TreeHint00304573::iterator, const TreeHintPair00304573 &);

// The map wrapper directly calls this tree's verified hinted insertion.
typedef _STL::map<AsciiString,TreeHintOpaque00304573,_STL::less<AsciiString >,_STL::allocator<TreeHintPair00304573> > MapInsert00304bef;
template MapInsert00304bef::iterator MapInsert00304bef::insert(MapInsert00304bef::iterator, const TreeHintPair00304573 &);
