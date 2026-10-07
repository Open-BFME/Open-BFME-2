// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Reference: STLport 4.5.3 _tree.h prefix ++/-- algorithms at BF1 ba7,
// inputs/vendor/stlport/stl/_tree.h. Target entries51C89..51C9A and
// 56DDB0..56DDC1 are complete17B leaves. Each passes receiver word0 to
// the independently rowed successor24250 or predecessor242C0, stores the
// returned node, and returns the receiver in EAX. The existing helper's
// decorated declaration determines the node-pointer ABI; it stays opaque.
// Original iterator specialization and enclosing allocation are unknown.
// This view models only the consumed one-pointer prefix. Both native regions
// use O1/G7/SSE. No extra provider bodies, pins, aliases or hatches are emitted.
namespace _STL {
struct _Rb_tree_node_base;
template<class Dummy> class _Rb_global {
public:
    static _Rb_tree_node_base *__cdecl _M_increment(_Rb_tree_node_base *);
    static _Rb_tree_node_base *__cdecl _M_decrement(_Rb_tree_node_base *);
};
}
struct Rva00051C89Iterator {
    _STL::_Rb_tree_node_base *node;
    Rva00051C89Iterator &advance();
    Rva00051C89Iterator &retreat();
};
Rva00051C89Iterator &Rva00051C89Iterator::advance() {
    node=_STL::_Rb_global<bool>::_M_increment(node);
    return *this;
}
Rva00051C89Iterator &Rva00051C89Iterator::retreat() {
    node=_STL::_Rb_global<bool>::_M_decrement(node);
    return *this;
}
