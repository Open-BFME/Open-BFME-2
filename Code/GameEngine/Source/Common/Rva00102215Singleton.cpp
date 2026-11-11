// cl: /MD /EHs-c-
//
// ?Rva00102215Get@@YAPAVRva001021F7@@XZ @0x00102215 38B: chain singleton getter
// for Rva001021F7 (0x20) via global g_00DEC268; new + ctor 0x001021F7.
// Evidence: packet disassembly; calls landed ctor; 8 callers.

class ObjectCreationList
{
public:
    ObjectCreationList();
private:
    char m_pad[12];
};

class Rva001021F7
{
public:
    Rva001021F7();
    // Native 0x00102188 (rowed as the address-named ??1Rva00102188): the
    // non-virtual destructor the teardown below runs through delete.
    ~Rva001021F7();
    void *m_a;
    ObjectCreationList m_list1;
    void *m_b;
    ObjectCreationList m_list2;
};

// Singleton pointer (data_ledger RVA 0x9EC268, zero .data, unowned);
// defined here, nothing else defines it.
Rva001021F7 *g_00DEC268 = 0;

Rva001021F7 *Rva00102215Get()
{
    if (g_00DEC268)
        return g_00DEC268;
    Rva001021F7 *p = new Rva001021F7;
    g_00DEC268 = p;
    return p;
}

// Native 0x001022C4..0x001022F5 (49B, RET0), the getter's counterpart: run the
// rowed 0x0010223B on the live instance, delete it (non-virtual destructor
// 0x00102188, operator delete 0x0002FD60) and clear the pointer. No direct
// caller reaches it in retail; the name is address-derived.
#include "../../Include/Common/Rva0010223B.h"

void Rva001022C4Shutdown()
{
    if (g_00DEC268)
        ((Rva0010223B *)g_00DEC268)->rva0010223B();
    delete g_00DEC268;
    g_00DEC268 = 0;
}

// The retail call in this body reads 0x00102188, an address the ledger already
// carries as ??1Rva00102188@@UAE@XZ. Bind the donor spelling to that rowed owner so one
// address keeps one definition and the unit links.
#pragma comment(linker, "/alternatename:??1Rva001021F7@@QAE@XZ=??1Rva00102188@@UAE@XZ")
