// cl: /MD
// ?rva0021AD5D@Rva0021AD5D@@QAEPAXI@Z @0x0021AD5D 43B
// Indexed Rb_tree accessor: size at +0x28 bounds-checks the index, header at
// +0x24 provides begin via +8 (leftmost), then _M_increment walks the index
// steps through rowed 0x00024250, returning the payload pointer at node+0x10.
// Proven by caller 0x00409ABE looping indices against [esi+0x28].
namespace _STL {
struct _Rb_tree_node_base {
    bool _M_color;
    _Rb_tree_node_base *_M_parent;
    _Rb_tree_node_base *_M_left;
    _Rb_tree_node_base *_M_right;
};
template <class D> class _Rb_global {
public:
    static _Rb_tree_node_base *__cdecl _M_increment(_Rb_tree_node_base *);
};
}
class Rva0021AD5D {
    char m_pad[0x24];
    _STL::_Rb_tree_node_base *m_header;
    unsigned m_size;
public:
    void *rva0021AD5D(unsigned int index);
};
void *Rva0021AD5D::rva0021AD5D(unsigned int index)
{
    if (index < m_size) {
        _STL::_Rb_tree_node_base *node = m_header->_M_left;
        if (index > 0) {
            for (unsigned int i = index; i != 0; --i)
                node = _STL::_Rb_global<bool>::_M_increment(node);
        }
        return *(void **)((char *)node + 0x10);
    }
    return 0;
}
