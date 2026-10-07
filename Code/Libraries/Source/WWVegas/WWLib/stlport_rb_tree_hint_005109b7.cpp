// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// BFME2 STLport tree: AsciiString key and opaque reference-counted pointer.
// hint 0x5109b7 -> insert 0x51030C -> _M_insert 0x510278 -> node 0x50F81F.
// The node allocates 24 bytes and constructs its 8-byte value at node+16.
// _Construct 0x50F263 calls pair copy 0x358B43: AsciiString copy 0x365F0,
// followed by copying a pointer and incrementing its non-null pointee at +4.
// Comparison reaches the established AsciiString operator< at 0x5598C.
// Semantic donor: BFME1 RvaTreeInsertUniqueHint.cpp and STLport pair/tree.
#include <stl/_prolog.h>
#include <stl/type_traits.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#undef _STLP_DEFAULT_CONSTRUCTED
#define _STLP_DEFAULT_CONSTRUCTED(_TTp) _TTp()
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
class AsciiString { public: AsciiString(const AsciiString &); ~AsciiString(); protected: void releaseBuffer(); private: void *m_data; };
bool operator<(const AsciiString &, const AsciiString &);
// Retail pair destructor 0x0050ED1F releases its non-null mapped pointer
// through the shared rowed fastcall 0x0007DEEF before destroying the
// AsciiString key, identical to 0x002175CE except its EH scopetable.
// The pointee carries a virtual destroy slot and a reference count at +4.
struct TargetRef00217D4C { virtual void *destroy(unsigned flags); int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct TreeHintRef0051030C {
    TargetRef00217D4C *m_ptr;
    TreeHintRef0051030C() : m_ptr(0) {}
    TreeHintRef0051030C(const TreeHintRef0051030C &other) : m_ptr(other.m_ptr) {
        if (m_ptr) ++m_ptr->references;
    }
    __forceinline ~TreeHintRef0051030C() {
        if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr);
    }
};

typedef _STL::pair<const AsciiString, TreeHintRef0051030C> TreeHintPair0051030C;
typedef _STL::_Rb_tree<AsciiString, TreeHintPair0051030C, _STL::_Select1st<TreeHintPair0051030C>, _STL::less<AsciiString>, _STL::allocator<TreeHintPair0051030C> > TreeHint0051030C;
// Retail uses its static byte allocator and has no node cleanup catch block.
namespace _STL {
template <> class allocator<char> {
public:
    static char *allocate(unsigned int bytes, const void *hint);
};
}
// ?_M_create_node@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@UTreeHintRef0051030C@@@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@UTreeHintRef0051030C@@@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@UTreeHintRef0051030C@@@_STL@@@3@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@UTreeHintRef0051030C@@@_STL@@@2@ABU?$pair@$$CBVAsciiString@@UTreeHintRef0051030C@@@2@@Z
template <>
TreeHint0051030C::_Link_type TreeHint0051030C::_M_create_node(const TreeHintPair0051030C &value)
{
    _Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<TreeHintPair0051030C>), 0);
    _STL::_Construct(&node->_M_value_field, value);
    return node;
}
template TreeHint0051030C::iterator TreeHint0051030C::insert_unique(TreeHint0051030C::iterator, const TreeHintPair0051030C &);

// The map wrapper directly calls this tree's verified hinted insertion.
typedef _STL::map<AsciiString,TreeHintRef0051030C,_STL::less<AsciiString >,_STL::allocator<TreeHintPair0051030C> > MapInsert005109b7;
template MapInsert005109b7::iterator MapInsert005109b7::insert(MapInsert005109b7::iterator, const TreeHintPair0051030C &);

// Retail 0x00511087: subscript over this map. The key-only lower_bound and the
// pair temporary reach the shared 00217D4C rows at 0x00221B8D/0x0050EDB3 (see
// pins); insert 0x00510FBE and pair dtor 0x0050ED1F are this tree's.
template TreeHintRef0051030C &MapInsert005109b7::operator[](const AsciiString &);

template void _STL::_Destroy<TreeHintPair0051030C>(TreeHintPair0051030C *);

template TreeHint0051030C::~_Rb_tree();

template void TreeHint0051030C::erase(TreeHint0051030C::iterator);

// Whole-class instantiation of this tree. It reproduces clear (retail 0x0051024F)
// byte for byte; their calls read the tree's matched STL helpers.
template class _STL::_Rb_tree<AsciiString,_STL::pair<AsciiString const ,TreeHintRef0051030C>,_STL::_Select1st<_STL::pair<AsciiString const ,TreeHintRef0051030C> >,_STL::less<AsciiString>,_STL::allocator<_STL::pair<AsciiString const ,TreeHintRef0051030C> > >;
