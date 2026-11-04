// ?rva00056DA2@Rva00056DA2@@QAEXXZ
// partial score=0.97 date=2026-09-28
// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// BFME 1 STLport deque algorithms, instantiated for the target-supported 4-byte
// owning-reference element view; original class names are unknown. Its release and assignment members are defined in
// OpaqueRefOwnership.cpp; this TU provides the inline target-observed destructor.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <deque>
#include <vector>
// Suppress this TU's non-retail copy of ??$copy_backward@U?$_Deque_iterator@UOpaqueRefElement4@@U?$_Nonconst_traits@UOpaqueRefElem:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct OpaqueRefElement4;
namespace _STL { template <> _Deque_iterator<OpaqueRefElement4,_Nonconst_traits<OpaqueRefElement4> > copy_backward<_Deque_iterator<OpaqueRefElement4,_Nonconst_traits<OpaqueRefElement4> >,_Deque_iterator<OpaqueRefElement4,_Nonconst_traits<OpaqueRefElement4> > >(_Deque_iterator<OpaqueRefElement4,_Nonconst_traits<OpaqueRefElement4> >,_Deque_iterator<OpaqueRefElement4,_Nonconst_traits<OpaqueRefElement4> >,_Deque_iterator<OpaqueRefElement4,_Nonconst_traits<OpaqueRefElement4> >); }
#include <windows.h>
#include "OpaqueRefCounted.h"
struct OpaqueRefElement4 {
    OpaqueRefCounted *referent;
    ~OpaqueRefElement4() { if (referent) referent->Release_Ref(); }
    OpaqueRefElement4 &operator=(const OpaqueRefElement4 &);
};
typedef _STL::_Deque_iterator<OpaqueRefElement4, _STL::_Nonconst_traits<OpaqueRefElement4> > OpaqueRefDequeIterator;
template OpaqueRefDequeIterator _STL::uninitialized_copy<OpaqueRefDequeIterator, OpaqueRefDequeIterator>(
    OpaqueRefDequeIterator, OpaqueRefDequeIterator, OpaqueRefDequeIterator);

struct Rva00055864Node
{
    void *m_next;
};

// Rva00055864Free at 0x55864 is a __stdcall free function, but the caller
// sets ecx=his before the call, indicating a __thiscall member call.
// Alias the __thiscall mangled name to the __stdcall definition.
#pragma comment(linker, "/alternatename:?Rva00055864Free@Rva00056DA2@@AAEXPAURva00055864Node@@@Z=?Rva00055864Free@@YGXPAURva00055864Node@@@Z")

class Rva00056DA2
{
public:
    void rva00056DA2();

private:
    char pad00_04[4];
    _STL::vector<Rva00055864Node *> m_vec; // +0x04 start +0x08 finish
    int m_10; // +0x10 dword-cleared at end
    void Rva00055864Free(Rva00055864Node *p);
};

void Rva00056DA2::rva00056DA2()
{
    for (unsigned int i = 0; i < m_vec.size(); ++i) {
        Rva00055864Node *p = m_vec[i];
        while (p) {
            Rva00055864Node *next = (Rva00055864Node *)p->m_next;
            Rva00055864Free(p);
            p = next;
        }
        m_vec[i] = 0;
    }
    m_10 = 0;
}
