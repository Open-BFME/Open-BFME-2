// cl: /EHs /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// BFME2 STLport tree: AsciiString key and opaque twelve-byte mapped value.
// hint 0x301883 -> insert 0x301384 -> _M_insert 0x3012F0 -> node 0x3012CE.
// The node allocates 32 bytes and constructs its 16-byte value at node+16.
// _Construct 0x3008E5 calls pair copy 0x52BEC9: AsciiString copy 0x365F0,
// followed by raw four-byte copies at pair offsets +4, +8 and +12.
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
// Retail pair copy preserves three four-byte fields without ownership calls.
// Their application meaning and original mapped-type name are unknown.
struct TreeHintPayload003012F0 {
    unsigned int a, b, c;
    TreeHintPayload003012F0(const TreeHintPayload003012F0 &other)
        : a(other.a), b(other.b), c(other.c) {}
};

typedef _STL::pair<const AsciiString, TreeHintPayload003012F0> TreeHintPair003012F0;
typedef _STL::_Rb_tree<AsciiString, TreeHintPair003012F0, _STL::_Select1st<TreeHintPair003012F0>, _STL::less<AsciiString>, _STL::allocator<TreeHintPair003012F0> > TreeHint003012F0;
// Retail uses its static byte allocator and has no node cleanup catch block.
namespace _STL {
template <> class allocator<char> {
public:
    static char *allocate(unsigned int bytes, const void *hint);
};
}
// ?_M_create_node@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@UTreeHintPayload003012F0@@@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@UTreeHintPayload003012F0@@@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@UTreeHintPayload003012F0@@@_STL@@@3@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@UTreeHintPayload003012F0@@@_STL@@@2@ABU?$pair@$$CBVAsciiString@@UTreeHintPayload003012F0@@@2@@Z
template <>
TreeHint003012F0::_Link_type TreeHint003012F0::_M_create_node(const TreeHintPair003012F0 &value)
{
    _Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<TreeHintPair003012F0>), 0);
    _STL::_Construct(&node->_M_value_field, value);
    return node;
}
template TreeHint003012F0::iterator TreeHint003012F0::insert_unique(TreeHint003012F0::iterator, const TreeHintPair003012F0 &);

// The map wrapper directly calls this tree's verified hinted insertion.
typedef _STL::map<AsciiString,TreeHintPayload003012F0,_STL::less<AsciiString >,_STL::allocator<TreeHintPair003012F0> > MapInsert00301883;
template MapInsert00301883::iterator MapInsert00301883::insert(MapInsert00301883::iterator, const TreeHintPair003012F0 &);

// Clone301BBF calls this proven node constructor3012CE before copying color
// and clearing both child links; copy301F9B belongs to the same typed chain.
template TreeHint003012F0::_Link_type TreeHint003012F0::_M_clone_node(TreeHint003012F0::_Link_type);
template TreeHint003012F0::_Link_type TreeHint003012F0::_M_copy(TreeHint003012F0::_Link_type, TreeHint003012F0::_Link_type);
template TreeHint003012F0::_Rb_tree(const TreeHint003012F0 &);
