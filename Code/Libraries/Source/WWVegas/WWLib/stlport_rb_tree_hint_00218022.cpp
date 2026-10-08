// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// BFME2 STLport tree: AsciiString key and opaque reference-counted pointer.
// hint 0x218022 -> insert 0x217D4C -> _M_insert 0x217CB8 -> node 0x217A6C.
// The node allocates 24 bytes and constructs its 8-byte value at node+16.
// _Construct 0x21789E calls pair copy 0x358B43: AsciiString copy 0x365F0,
// followed by copying a pointer and incrementing its non-null pointee at +4.
// Comparison reaches the established AsciiString operator< at 0x5598C.
// Semantic donor: BFME1 RvaTreeInsertUniqueHint.cpp and STLport pair/tree.
// Retail directly default-constructs the mapped handle. Its explicit default
// constructor initializes the pointer to null; no scalar workaround is needed.
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
protected:
    void releaseBuffer();
private:
    void *m_data;
};
bool operator<(const AsciiString &, const AsciiString &);
// Retail map temporary destruction0x2175CE releases its non-null mapped
// pointer through0x7DEEF before destroying the AsciiString key. The pointee
// has a virtual destroy slot and a reference count at+4; its application
// identity remains unknown.
struct TargetRef00217D4C { virtual void *destroy(unsigned flags); int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct TreeHintRef00217D4C {
    TargetRef00217D4C *m_ptr;
    TreeHintRef00217D4C() : m_ptr(0) {}
    TreeHintRef00217D4C(const TreeHintRef00217D4C &other) : m_ptr(other.m_ptr) {
        if (m_ptr) ++m_ptr->references;
    }
    TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
    __forceinline ~TreeHintRef00217D4C() {
        if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr);
    }
};

// ??4TreeHintRef00217D4C@@QAEAAU0@ABU0@@Z, retail 0x002174A4, 43 bytes.
// Honest refcounted-handle assignment over the map mapped value: self-check,
// AddRef the incoming referent at +4, Release the held referent through the
// rowed fastcall 0x0007DEEF, then copy the pointer. 40+ callers; sole callee
// rowed. Probed exact via build/probe before landing here.
TreeHintRef00217D4C &TreeHintRef00217D4C::operator=(const TreeHintRef00217D4C &other)
{
    if (this != &other) {
        if (other.m_ptr)
            ++other.m_ptr->references;
        if (m_ptr)
            ReleaseTreeHintRef00217D4C(m_ptr);
        m_ptr = other.m_ptr;
    }
    return *this;
};

typedef _STL::pair<const AsciiString, TreeHintRef00217D4C> TreeHintPair00217D4C;
typedef _STL::_Rb_tree<AsciiString, TreeHintPair00217D4C, _STL::_Select1st<TreeHintPair00217D4C>, _STL::less<AsciiString>, _STL::allocator<TreeHintPair00217D4C> > TreeHint00217D4C;
// Retail uses its static byte allocator and has no node cleanup catch block.
namespace _STL {
template <> class allocator<char> {
public:
    static char *allocate(unsigned int bytes, const void *hint);
};
}
// ?_M_create_node@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@UTreeHintRef00217D4C@@@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@UTreeHintRef00217D4C@@@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@UTreeHintRef00217D4C@@@_STL@@@3@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@UTreeHintRef00217D4C@@@_STL@@@2@ABU?$pair@$$CBVAsciiString@@UTreeHintRef00217D4C@@@2@@Z
template <>
TreeHint00217D4C::_Link_type TreeHint00217D4C::_M_create_node(const TreeHintPair00217D4C &value)
{
    _Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<TreeHintPair00217D4C>), 0);
    _STL::_Construct(&node->_M_value_field, value);
    return node;
}
template TreeHint00217D4C::iterator TreeHint00217D4C::insert_unique(TreeHint00217D4C::iterator, const TreeHintPair00217D4C &);

// The map wrapper directly calls this tree's verified hinted insertion.
typedef _STL::map<AsciiString,TreeHintRef00217D4C,_STL::less<AsciiString>,_STL::allocator<TreeHintPair00217D4C> > MapInsert00218022;
template MapInsert00218022::iterator MapInsert00218022::insert(MapInsert00218022::iterator, const TreeHintPair00217D4C &);

template TreeHint00217D4C::_Link_type TreeHint00217D4C::_M_lower_bound(const AsciiString &) const;

// This two-argument pair constructor is reached by the same map temporary.
template TreeHintPair00217D4C::pair(const AsciiString &, const TreeHintRef00217D4C &);

template void _STL::_Destroy<TreeHintPair00217D4C>(TreeHintPair00217D4C *);

template TreeHintRef00217D4C &MapInsert00218022::operator[](const AsciiString &);
