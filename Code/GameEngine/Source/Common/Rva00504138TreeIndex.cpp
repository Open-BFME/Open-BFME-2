// cl: /O1
// Donor: Open-BFME-1 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24,
// game/GameEngine/Source/Common/BfmeConv1105.cpp, bfmeGo1105C, /O1.
// Target Ghidra entry504138/45B, callers2BE9AE and3FD311 recorded by the
// earlier bank. Retail proves header+8 begin, increment worker24250,
// index decrement after increment, and the value address at node+10.
// The value's complete type and the application owner remain unknown.

namespace _STL
{
    struct _Rb_tree_node_base;
    template<class Dummy> class _Rb_global
    {
    public:
        static _Rb_tree_node_base *__cdecl _M_increment(_Rb_tree_node_base *);
    };
}

struct Rva00504138Node
{
    char prefix[8];
    Rva00504138Node *first;
    char gap[4];
    char value[1];
};

class Rva00504138
{
public:
    void *rva00504138(int n);
private:
    Rva00504138Node *header;
};

// ?rva00504138@Rva00504138@@QAEPAXH@Z
void *Rva00504138::rva00504138(int n)
{
    Rva00504138Node *h = header;
    Rva00504138Node *p = h->first;
    while (p != h)
    {
        if (!n)
            return &p->value;
        p = (Rva00504138Node *)_STL::_Rb_global<bool>::_M_increment(
            (_STL::_Rb_tree_node_base *)p);
        h = header;
        n--;
    }
    return 0;
}
