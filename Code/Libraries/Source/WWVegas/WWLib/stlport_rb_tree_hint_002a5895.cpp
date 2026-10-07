// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// BFME2 STLport tree: AsciiString key and opaque four-byte mapped object.
// hint 0x2A5895 -> insert 0x2A48DE -> _M_insert 0x2A484A -> node 0x2A42B6.
// The node allocates 24 bytes and constructs its 8-byte value at node+16.
// _Construct 0x2A1EC8 calls pair copy 0x2A1538: AsciiString copy 0x365F0,
// then the mapped object copy constructor 0x2A1383 on the second pair field.
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
// The 4-byte mapped field's copy at 0x2A1383 is the matched STLport
// list<int> copy constructor. Keep the address-derived tree type spelling,
// but let its implicit copy delegate to that verified list operation.
// Declaration-only receiver view of the existing four-byte integer list.
// Its native provider is emitted by stlport_list_int_o1.cpp under its own flags.
namespace _STL {
template<class T,class A=allocator<T> > class list { public: list(const list &); };
}
struct TreeHintOpaque002A484A {
    void *node;
    __forceinline TreeHintOpaque002A484A(const TreeHintOpaque002A484A &v) {
        reinterpret_cast<_STL::list<int> *>(this)->_STL::list<int>::list(*reinterpret_cast<const _STL::list<int> *>(&v));
    }
    ~TreeHintOpaque002A484A();
};

typedef _STL::pair<const AsciiString, TreeHintOpaque002A484A> TreeHintPair002A484A;
typedef _STL::_Rb_tree<AsciiString, TreeHintPair002A484A, _STL::_Select1st<TreeHintPair002A484A>, _STL::less<AsciiString>, _STL::allocator<TreeHintPair002A484A> > TreeHint002A484A;
// Retail uses its static byte allocator and has no node cleanup catch block.
namespace _STL {
template <> class allocator<char> {
public:
    static char *allocate(unsigned int bytes, const void *hint);
};
}
// ?_M_create_node@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@UTreeHintOpaque002A484A@@@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@UTreeHintOpaque002A484A@@@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@UTreeHintOpaque002A484A@@@_STL@@@3@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@UTreeHintOpaque002A484A@@@_STL@@@2@ABU?$pair@$$CBVAsciiString@@UTreeHintOpaque002A484A@@@2@@Z
template <>
TreeHint002A484A::_Link_type TreeHint002A484A::_M_create_node(const TreeHintPair002A484A &value)
{
    _Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<TreeHintPair002A484A>), 0);
    _STL::_Construct(&node->_M_value_field, value);
    return node;
}
template TreeHint002A484A::iterator TreeHint002A484A::insert_unique(TreeHint002A484A::iterator, const TreeHintPair002A484A &);

// The map wrapper directly calls this tree's verified hinted insertion.
typedef _STL::map<AsciiString,TreeHintOpaque002A484A,_STL::less<AsciiString >,_STL::allocator<TreeHintPair002A484A> > MapInsert002a5895;
template MapInsert002a5895::iterator MapInsert002a5895::insert(MapInsert002a5895::iterator, const TreeHintPair002A484A &);

// Native 0x002A1CC9: construct the key and copy the proven integer list.
// Delegate to the declared-only list copy: retail calls its complete 88B provider
// at 0x2A1383 rather than a new five-byte derived-class forwarding body.
template TreeHintPair002A484A::pair(const AsciiString &,const TreeHintOpaque002A484A &);
