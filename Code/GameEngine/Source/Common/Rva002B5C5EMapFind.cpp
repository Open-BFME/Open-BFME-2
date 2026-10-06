// ?rva002B5C5E@Rva002B5C5E@@QAEPAURva002B5C5EVal@@H@Z @0x002B5C5E 53B.
// Linear search over an _Rb_tree map at +0x130 via rowed _M_increment at 0x00024250.
// Each node +0x14 holds a value pointer whose int at +0x18 is compared to the id.
// Caller at 0x00576A64 uses the 0x00DFEF10 singleton like the LivingWorld vector finds.
// TU-local honest-address views; offsets prove operations not original type names.
// cl: /DNDEBUG /MD /EHsc /Ob2
namespace _STL { struct _Rb_tree_node_base { bool _M_color; _Rb_tree_node_base *_M_parent; _Rb_tree_node_base *_M_left; _Rb_tree_node_base *_M_right; }; template <class D> class _Rb_global { public: static _Rb_tree_node_base *__cdecl _M_increment(_Rb_tree_node_base *); }; }
struct Rva002B5C5EVal { char pad[0x18]; int id; };
struct Rva002B5C5E {
    char pad[0x130];
    _STL::_Rb_tree_node_base *header130;
    Rva002B5C5EVal *rva002B5C5E(int id);
};
Rva002B5C5EVal *Rva002B5C5E::rva002B5C5E(int id)
{
    _STL::_Rb_tree_node_base *node = header130->_M_left;
    if (node == header130)
        return 0;
    do {
        Rva002B5C5EVal *v = *(Rva002B5C5EVal **)((char *)node + 0x14);
        if (v->id == id)
            return v;
        node = _STL::_Rb_global<bool>::_M_increment(node);
    } while (node != header130);
    return 0;
}
