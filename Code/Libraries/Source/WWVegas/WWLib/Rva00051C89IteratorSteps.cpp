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

// Whole clean BF1 f989 ScoreScreenGrabMultiPlayerInfo.cpp emits two
// reverse-tree dereference operations at this same complete target. The
// donor Player-map specialization and original operator name stay unknown.
// Native170A31..170A3D follows RET8 and precedes a fresh prologue: pass
// receiver word0 to the independently matched cdecl predecessor242C0,
// then return its pointer +16. This uses the existing opaque provider ABI;
// only the consumed pointer prefix and payload displacement are observed.
struct Rva00170A31Iterator
{
    _STL::_Rb_tree_node_base *node;
    void *previousPayload() const;
};
void *Rva00170A31Iterator::previousPayload() const
{
    return reinterpret_cast<char *>(_STL::_Rb_global<bool>::_M_decrement(node)) + 16;
}

// Whole clean BF1 f989 Map/Rva0019F890FillHelper.cpp supplies reverse-pointer
// iterator leads. Native329D28..329D2E and329D2E..329D34 are separate complete
// six-byte entries between RET boundaries; the following entry has a fresh
// stack-argument prologue. Their only observed state is receiver word0.
// The first returns that word minus four; the second subtracts four in place
// and returns the receiver. Original specializations, pointer types and owner
// identities remain unknown. Separate prefix views avoid assuming adjacency
// establishes a shared class; unsigned arithmetic models the raw32-bit result.
struct Rva00329D28WordPrefix {
    unsigned word;
    unsigned previousAddressBits() const;
};
unsigned Rva00329D28WordPrefix::previousAddressBits() const {
    return word - 4u;
}

struct Rva00329D2EWordPrefix {
    unsigned word;
    Rva00329D2EWordPrefix &retreat();
};
Rva00329D2EWordPrefix &Rva00329D2EWordPrefix::retreat() {
    word -= 4u;
    return *this;
}
