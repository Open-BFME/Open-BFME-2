// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// BFME2 STLport tree: AsciiString key and opaque 28-byte mapped value.
// hint 0x5b3a2a -> insert 0x5b381a -> _M_insert 0x5B3786 -> node 0x5B3609.
// The node allocates 48 bytes and constructs its 32-byte value at node+16.
// _Construct 0x5B303D calls pair copy 0x5B2A37: AsciiString copy 0x365F0,
// followed by a raw 28-byte copy of the mapped value at pair offset +4.
// Comparison reaches the established AsciiString operator< at 0x5598C.
// Semantic donor: BFME1 RvaTreeInsertUniqueHint.cpp and STLport pair/tree.
#include <stl/_prolog.h>
#include <stl/type_traits.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#undef _STLP_DEFAULT_CONSTRUCTED
#define _STLP_DEFAULT_CONSTRUCTED(_TTp) _TTp()
#include <map>
template <class T> class StringBase
{
	friend class AsciiString;
	void releaseBuffer();
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
    ~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }
private:
    void *m_data;
};
bool operator<(const AsciiString &, const AsciiString &);
// Retail pair copying transfers this 28-byte mapped value without further calls.
// Its original application type and the meanings of these fields are unknown.
// Native subscript 0x005B4023 initializes exactly these bytes before passing
// the value to the rowed pair constructor 0x005B2F20. Preserve the untouched
// three padding bytes at +21..23. Its temporary cleanup at 0x005B40A2 calls
// only the AsciiString destructor, proving no mapped-value cleanup here.
struct TreeHintPayload005B3786 {
    unsigned int words[7];
    TreeHintPayload005B3786() {
        words[0] = 0;
        words[1] = ~0u;
        words[2] = ~0u;
        words[3] = ~0u;
        words[4] = ~0u;
        *(unsigned char *)&words[5] = 0;
        words[6] = 0;
    }
};

typedef _STL::pair<const AsciiString, TreeHintPayload005B3786> TreeHintPair005B3786;
typedef _STL::_Rb_tree<AsciiString, TreeHintPair005B3786, _STL::_Select1st<TreeHintPair005B3786>, _STL::less<AsciiString>, _STL::allocator<TreeHintPair005B3786> > TreeHint005B3786;
// Retail uses its static byte allocator and has no node cleanup catch block.
namespace _STL {
template <> class allocator<char> {
public:
    static char *allocate(unsigned int bytes, const void *hint);
};
}
// ?_M_create_node@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@UTreeHintPayload005B3786@@@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@UTreeHintPayload005B3786@@@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@UTreeHintPayload005B3786@@@_STL@@@3@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@UTreeHintPayload005B3786@@@_STL@@@2@ABU?$pair@$$CBVAsciiString@@UTreeHintPayload005B3786@@@2@@Z
template <>
TreeHint005B3786::_Link_type TreeHint005B3786::_M_create_node(const TreeHintPair005B3786 &value)
{
    _Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<TreeHintPair005B3786>), 0);
    _STL::_Construct(&node->_M_value_field, value);
    return node;
}
template TreeHint005B3786::iterator TreeHint005B3786::insert_unique(TreeHint005B3786::iterator, const TreeHintPair005B3786 &);

// The map wrapper directly calls this tree's verified hinted insertion.
typedef _STL::map<AsciiString,TreeHintPayload005B3786,_STL::less<AsciiString >,_STL::allocator<TreeHintPair005B3786> > MapInsert005b3a2a;
template MapInsert005b3a2a::iterator MapInsert005b3a2a::insert(MapInsert005b3a2a::iterator, const TreeHintPair005B3786 &);

// This two-argument pair constructor is reached by the map temporary at 0x005B4023.
template TreeHintPair005B3786::pair(const AsciiString &, const TreeHintPayload005B3786 &);

// Native [0x005B4023,0x005B40BA), RET4, returns node+20 (mapped value).
// Calls the key-only lower_bound at 0x00221B8D, established AsciiString
// comparator 0x0005598C, this pair constructor, and map insertion 0x005B3CC9.
// These calls establish the existing tree instantiation independently of
// the OptionPreferences equal_range drift candidate that served this address.
template TreeHintPayload005B3786 &MapInsert005b3a2a::operator[](const AsciiString &);
