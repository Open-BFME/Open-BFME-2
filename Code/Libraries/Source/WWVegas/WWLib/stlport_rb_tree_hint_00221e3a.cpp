// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// BFME2 STLport tree: AsciiString key and opaque reference-counted pointer.
// hint 0x221e3a -> insert 0x221D6B -> _M_insert 0x221CD7 -> node 0x221BF3.
// The node allocates 24 bytes and constructs its 8-byte value at node+16.
// _Construct 0x221AE0 calls pair copy 0x358B43: AsciiString copy 0x365F0,
// followed by copying a pointer and incrementing its non-null pointee at +4.
// Comparison reaches the established AsciiString operator< at 0x5598C.
// Semantic donor: BFME1 RvaTreeInsertUniqueHint.cpp and STLport pair/tree.
#include <stl/_alloc.h>
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *, size_t); }
#include <stl/_prolog.h>
#include <stl/type_traits.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#undef _STLP_DEFAULT_CONSTRUCTED
#define _STLP_DEFAULT_CONSTRUCTED(_TTp) _TTp()
#include <map>
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
bool operator<(const AsciiString &, const AsciiString &);
// Retail pair destructor 0x0022187B releases its non-null mapped pointer
// through the shared rowed fastcall 0x0007DEEF before destroying the
// AsciiString key, identical to 0x002175CE except its EH scopetable.
// The pointee carries a virtual destroy slot and a reference count at +4.
struct TargetRef00217D4C { virtual void *destroy(unsigned flags); int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct TreeHintRef00221D6B {
    TargetRef00217D4C *m_ptr;
    TreeHintRef00221D6B() : m_ptr(0) {}
    TreeHintRef00221D6B(const TreeHintRef00221D6B &other) : m_ptr(other.m_ptr) {
        if (m_ptr) ++m_ptr->references;
    }
    __forceinline ~TreeHintRef00221D6B() {
        if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr);
    }
};

typedef _STL::pair<const AsciiString, TreeHintRef00221D6B> TreeHintPair00221D6B;

// Preserve retail's inline node/buffer free; the public allocator is supplied by its verified owner.
namespace _STL {
#pragma optimize("gsy", on)
template <> __forceinline void allocator<_Rb_tree_node< ::TreeHintPair00221D6B > >::deallocate(_Rb_tree_node< ::TreeHintPair00221D6B > *p, size_t) const { if (p != 0) free(p); }
#pragma optimize("", on)
}

typedef _STL::_Rb_tree<AsciiString, TreeHintPair00221D6B, _STL::_Select1st<TreeHintPair00221D6B>, _STL::less<AsciiString>, _STL::allocator<TreeHintPair00221D6B> > TreeHint00221D6B;
// Retail uses its static byte allocator and has no node cleanup catch block.
namespace _STL {
template <> class allocator<char> {
public:
    static char *allocate(unsigned int bytes, const void *hint);
};
}
// ?_M_create_node@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@UTreeHintRef00221D6B@@@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@UTreeHintRef00221D6B@@@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@UTreeHintRef00221D6B@@@_STL@@@3@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@UTreeHintRef00221D6B@@@_STL@@@2@ABU?$pair@$$CBVAsciiString@@UTreeHintRef00221D6B@@@2@@Z
template <>
TreeHint00221D6B::_Link_type TreeHint00221D6B::_M_create_node(const TreeHintPair00221D6B &value)
{
    _Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<TreeHintPair00221D6B>), 0);
    _STL::_Construct(&node->_M_value_field, value);
    return node;
}
template TreeHint00221D6B::iterator TreeHint00221D6B::insert_unique(TreeHint00221D6B::iterator, const TreeHintPair00221D6B &);

// The map wrapper directly calls this tree's verified hinted insertion.
typedef _STL::map<AsciiString,TreeHintRef00221D6B,_STL::less<AsciiString>,_STL::allocator<TreeHintPair00221D6B> > MapInsert00221e3a;
template MapInsert00221e3a::iterator MapInsert00221e3a::insert(MapInsert00221e3a::iterator, const TreeHintPair00221D6B &);

template void _STL::_Destroy<TreeHintPair00221D6B>(TreeHintPair00221D6B *);

// Anchor the destruction chain through clear (which reaches _M_erase)
// instead of instantiating ~_Rb_tree: the tree dtor row 0x00221E02 belongs
// to stlport_rb_tree_hint_00221e02_dtor.cpp, and a copy here would lose the
// COMDAT fold while this TU still comes first in link order.
template void TreeHint00221D6B::clear();

// Retail 0x002221F7: subscript over this map. The key-only lower_bound and the
// pair temporary reach the shared 00217D4C rows at 0x00221B8D/0x0050EDB3 (see
// pins); insert pair-dtor and the node+0x14 mapped reference are this tree's.
template TreeHintRef00221D6B &MapInsert00221e3a::operator[](const AsciiString &);
