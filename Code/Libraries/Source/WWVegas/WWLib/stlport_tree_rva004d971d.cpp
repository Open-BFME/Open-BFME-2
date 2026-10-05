// cl: /O1 /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// STLport 4.5.3 _tree.c is the semantic guide for the target's insertion.
// Retail 4DA0B7..4DA13F: unsigned comparison of the first payload dword,
// links at +4/+8/+C, header at receiver +0 and count at +4. The original
// container/key name is unknown. Allocation 4D9CD1 reserves 56 bytes and
// constructs the already-rowed 40-byte Rva004D971D payload at node +16.
#define _STLP_NO_EXCEPTIONS 1
#include <map>
class Rva004D971D {
    char m_opaque[40];
public:
    __declspec(nothrow) Rva004D971D(const Rva004D971D &);
    ~Rva004D971D();
};
struct Rva004DA0B7OrderKey {
    const unsigned &operator()(const Rva004D971D &v) const {
        return *reinterpret_cast<const unsigned *>(&v);
    }
};
typedef _STL::_Rb_tree<unsigned, Rva004D971D, Rva004DA0B7OrderKey,
    _STL::less<unsigned>, _STL::allocator<Rva004D971D> > Rva004DA0B7Tree;
namespace _STL {
template <> void _Construct<Rva004D971D, Rva004D971D>(Rva004D971D *, const Rva004D971D &);
template <> _Rb_tree_node<Rva004D971D> *Rva004DA0B7Tree::_M_create_node(const Rva004D971D &value) {
    _Rb_tree_node<Rva004D971D> *node = (_Rb_tree_node<Rva004D971D> *)allocator<char>::allocate(56, 0);
    _Construct(&node->_M_value_field, value);
    return node;
}
}

template _STL::_Rb_tree_node<Rva004D971D> *Rva004DA0B7Tree::_M_create_node(const Rva004D971D &);

// Retail unsigned compare at +0x23 distinguishes this from the served
// map<int,bool> source. Both create-node calls reach the row above.
// ?_M_insert@?$_Rb_tree@IVRva004D971D@@URva004DA0B7OrderKey@@U?$less@I@_STL@@V?$allocator@VRva004D971D@@@4@@_STL@@AAE?AU?$_Rb_tree_iterator@VRva004D971D@@U?$_Nonconst_traits@VRva004D971D@@@_STL@@@2@PAU_Rb_tree_node_base@2@0ABVRva004D971D@@0@Z
template Rva004DA0B7Tree::iterator Rva004DA0B7Tree::_M_insert(
    _STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *, const Rva004D971D &,
    _STL::_Rb_tree_node_base *);
