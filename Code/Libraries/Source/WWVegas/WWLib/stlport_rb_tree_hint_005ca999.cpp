// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// BFME2 STLport tree: AsciiString key and opaque four-byte mapped object.
// hint 0x5CA999 -> insert 0x5CA881 -> _M_insert 0x5CA7ED -> node 0x5CA291.
// The node allocates 24 bytes and constructs its 8-byte value at node+16.
// _Construct 0x5CA173 calls pair copy 0x5C9F87: AsciiString copy 0x365F0,
// then the mapped object copy constructor 0x54D800 on the second pair field.
// Comparison reaches the established AsciiString operator< at 0x5598C.
// Semantic donor: BFME1 RvaTreeInsertUniqueHint.cpp and STLport pair/tree.
#include <map>
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

template <class T> class StringBase { StringBase(const StringBase<T> &); void releaseBuffer(); friend class AsciiString; };
class AsciiString { public: AsciiString(const AsciiString &that) { ((StringBase<char> *)this)->StringBase<char>::StringBase(*(const StringBase<char> *)&that); } ~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); } private: char *m_text; };
bool operator<(const AsciiString &, const AsciiString &);
// The list's base constructor is provided by the verified shared list family.
extern template _STL::_List_base<AsciiString,_STL::allocator<AsciiString> >::_List_base(const _STL::allocator<AsciiString> &);
// The 4-byte mapped field's copy at 0x54D800 is the matched STLport
// list<AsciiString> copy constructor. Keep the address-derived tree type
// spelling, but let its implicit copy delegate to that verified list operation.
struct TreeHintOpaque005CA7ED : _STL::list<AsciiString> {
    ~TreeHintOpaque005CA7ED();
};

typedef _STL::pair<const AsciiString, TreeHintOpaque005CA7ED> TreeHintPair005CA7ED;
typedef _STL::_Rb_tree<AsciiString, TreeHintPair005CA7ED, _STL::_Select1st<TreeHintPair005CA7ED>, _STL::less<AsciiString>, _STL::allocator<TreeHintPair005CA7ED> > TreeHint005CA7ED;
// Retail uses its static byte allocator and has no node cleanup catch block.
namespace _STL {
template <> class allocator<char> {
public:
    static char *allocate(unsigned int bytes, const void *hint);
};
}
// ?_M_create_node@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@UTreeHintOpaque005CA7ED@@@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@UTreeHintOpaque005CA7ED@@@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@UTreeHintOpaque005CA7ED@@@_STL@@@3@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@UTreeHintOpaque005CA7ED@@@_STL@@@2@ABU?$pair@$$CBVAsciiString@@UTreeHintOpaque005CA7ED@@@2@@Z
template <>
TreeHint005CA7ED::_Link_type TreeHint005CA7ED::_M_create_node(const TreeHintPair005CA7ED &value)
{
    _Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<TreeHintPair005CA7ED>), 0);
    _STL::_Construct(&node->_M_value_field, value);
    return node;
}
template TreeHint005CA7ED::iterator TreeHint005CA7ED::insert_unique(TreeHint005CA7ED::iterator, const TreeHintPair005CA7ED &);

// The map wrapper directly calls this tree's verified hinted insertion.
typedef _STL::map<AsciiString,TreeHintOpaque005CA7ED,_STL::less<AsciiString >,_STL::allocator<TreeHintPair005CA7ED> > MapInsert005ca999;
template MapInsert005ca999::iterator MapInsert005ca999::insert(MapInsert005ca999::iterator, const TreeHintPair005CA7ED &);
