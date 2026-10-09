// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /EHsc /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// BFME2 STLport tree: AsciiString key and opaque 0xDF4-byte mapped object.
// ??1TreeHintOpaque0043671B@@QAE@XZ @0x00229840 53B destroys UnicodeString +0 and 0xDE8 subobject +4; deleting dtor 0x002DDE27 and list clear 0x00434EC9 prove identity; layout from copy 0x0022D106.
// hint 0x436E3B -> insert 0x4367AF -> _M_insert 0x43671B -> node 0x436234.
// The node allocates 0xE08 bytes and constructs its 0xDF8-byte value at node+16.
// _Construct 0x43616A calls pair copy 0x435DAA: AsciiString copy 0x365F0,
// then the mapped object copy constructor 0x22D106 on the second pair field.
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
// The mapped copy at 0x22D106 proves a UnicodeString, a 0xDE8-byte
// subobject, and two final words. Its original application type is unknown.
#include "unicode_string.h"
// Full 216-byte retail constructor 0x22CE19 installs vptr 0xBE7560,
// copies string/scalar members and nested subobjects. Keep its ownership
// operations out of line; its application class and virtual slots are unknown.
struct BfmeSubobject0022CE19 {
    virtual ~BfmeSubobject0022CE19();
    unsigned char m_opaque[0xDE4];
    BfmeSubobject0022CE19(const BfmeSubobject0022CE19 &);
};
struct TreeHintOpaque0043671B {
    UnicodeString m_text;
    BfmeSubobject0022CE19 m_subobject;
    unsigned int m_wordDEC, m_wordDF0;
    TreeHintOpaque0043671B();
    TreeHintOpaque0043671B(const TreeHintOpaque0043671B &);
    ~TreeHintOpaque0043671B();
};
TreeHintOpaque0043671B::TreeHintOpaque0043671B(const TreeHintOpaque0043671B &other)
    : m_text(other.m_text), m_subobject(other.m_subobject),
      m_wordDEC(other.m_wordDEC), m_wordDF0(other.m_wordDF0) {}

TreeHintOpaque0043671B::~TreeHintOpaque0043671B() {}

typedef _STL::pair<const AsciiString, TreeHintOpaque0043671B> TreeHintPair0043671B;
typedef _STL::_Rb_tree<AsciiString, TreeHintPair0043671B, _STL::_Select1st<TreeHintPair0043671B>, _STL::less<AsciiString>, _STL::allocator<TreeHintPair0043671B> > TreeHint0043671B;
// Cleanup owns the verified 56-byte destructor. This /EHsc insertion unit
// would otherwise emit a 52-byte copy without the allocator unwind transition.
extern template TreeHint0043671B::~_Rb_tree();
// Retail uses its static byte allocator and has no node cleanup catch block.
// ?_M_create_node@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@UTreeHintOpaque0043671B@@@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@UTreeHintOpaque0043671B@@@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@UTreeHintOpaque0043671B@@@_STL@@@3@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@UTreeHintOpaque0043671B@@@_STL@@@2@ABU?$pair@$$CBVAsciiString@@UTreeHintOpaque0043671B@@@2@@Z
template <>
TreeHint0043671B::_Link_type TreeHint0043671B::_M_create_node(const TreeHintPair0043671B &value)
{
    _Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<TreeHintPair0043671B>), 0);
    _STL::_Construct(&node->_M_value_field, value);
    return node;
}
template TreeHint0043671B::iterator TreeHint0043671B::insert_unique(TreeHint0043671B::iterator, const TreeHintPair0043671B &);

// The map wrapper directly calls this tree's verified hinted insertion.
typedef _STL::map<AsciiString,TreeHintOpaque0043671B,_STL::less<AsciiString >,_STL::allocator<TreeHintPair0043671B> > MapInsert00436e3b;
template MapInsert00436e3b::iterator MapInsert00436e3b::insert(MapInsert00436e3b::iterator, const TreeHintPair0043671B &);

template void _STL::_Construct<TreeHintOpaque0043671B,TreeHintOpaque0043671B>(TreeHintOpaque0043671B*, const TreeHintOpaque0043671B&);

template TreeHintOpaque0043671B &MapInsert00436e3b::operator[](const AsciiString &);

// Retail Ghidra entry 0x00435CE0 is 25 bytes and ends at RET. Its REL32 at
// +0xF calls the rowed tree constructor 0x00434C3D. The neighboring 0x00436E3B
// insertion chain supports the AsciiString to TreeHint map specialization.
template _STL::map<AsciiString, TreeHintOpaque0043671B,
    _STL::less<AsciiString>,
    _STL::allocator<TreeHintPair0043671B> >::map();
// Retail 0x004360B3 looks up the printed saved-game digest in the tree
// whose address is owned as g_Va00E032EC. Its caller passes MD5 text;
// the returned node with the tree header and returns the mapped value at +0x14.
// The insert chain establishes the value type. The key-only worker at
// 0x001F8437 has an independently evidenced address-derived thiscall
// signature; this shim makes no claim about its concrete tree class.
extern unsigned g_Va00E032EC;

class Rva001F8437
{
public:
    void *rva001F8437(const AsciiString &key) throw();
};

TreeHintOpaque0043671B *Rva004360B3(AsciiString key)
{
    void *node = ((Rva001F8437 *)&g_Va00E032EC)->rva001F8437(key);
    if (node != *(void **)&g_Va00E032EC)
        return (TreeHintOpaque0043671B *)((char *)node + 0x14);
    return 0;
}
