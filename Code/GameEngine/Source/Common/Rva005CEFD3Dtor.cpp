// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// ??1Rva005CEFD3@@UAE@XZ @0x005CEFD3 115B. Opaque dtor the owning-pointer reset
// 0x005CF363 calls (the pin keeps the non-virtual spelling). Target facts: the
// +0x10 ptr-chase field answers an object told through its slot 4; the object
// unregisters from the parent's observer list at +0x18 (+4) via rowed erase
// 0x002B7250 and, when TheLivingWorldManager+0x268 exists, 0x003EE966 gets the
// parent; the +0x1C holder clears; the empty base dtor is inline. Pattern from
// Rva0056B2DDDtor.cpp. Identity of the class is unproven.
class CreateAHeroData;
#include "../../Include/Common/Rva002B7250.h"
struct Parent005CEFD3 {
    char pad[4];
    Rva002B7250 holder;
};
#include "../../Include/Common/Rva0042D6FDPtrChaseField.h"
class VirtObj005CEFD3 {
public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
    virtual void f4();
};
// The holder's destructor is 0x000AD6F4, the body clear shares.
#include "../../Include/Common/Rva000AD6F4.h"
#include "../../Include/Common/Rva003EE966.h"
class Rva0021294A {
public:
    char m_pad[0x268];
    Rva003EE966 *m_268;
};
class LivingWorldManager; extern LivingWorldManager *TheLivingWorldManager;
class Base005CEFD3 {
public:
    virtual ~Base005CEFD3() {}
};
class Rva005CEFD3 : public Base005CEFD3 {
public:
    virtual ~Rva005CEFD3();
private:
    char m_pad04[0x0C];
    Rva0042D6FDPtrChaseField *m_10;
    int m_14;
    Parent005CEFD3 *m_parent18;
    Rva000AD6F4 m_1c;
};
Rva005CEFD3::~Rva005CEFD3()
{
    VirtObj005CEFD3 *o = (VirtObj005CEFD3 *)m_10->get();
    if (o)
        o->f4();
    m_parent18->holder.rva002B7250((CreateAHeroData *)this);
    Rva003EE966 *p = ((Rva0021294A *)TheLivingWorldManager)->m_268;
    if (p != 0)
        p->rva003EE966((int)m_parent18);
}
