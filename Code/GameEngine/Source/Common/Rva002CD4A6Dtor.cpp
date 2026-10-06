// cl: /O1 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /EHs
// stlport
// ??1Rva002CD4A6@@UAE@XZ @0x002CD4A6 314B unlock: vtable 0x00802170 dtor with list plus strings plus refs plus free, caller 0x002CE047 deleting dtor, neighbours WeaponGetStatus and WeaponRva002CDB0E
#include <list>
#include "ascii_string.h"

void __cdecl operator delete(void *p);
extern "C" void __cdecl free(void *p);

class OpaqueRefCounted
{
public:
    void Release_Ref();
};

class Rva00360D26Member
{
public:
    ~Rva00360D26Member();
    char m_data[0x40];
};

struct Rva002CD4A6Aux
{
    virtual void *Get(int x);
};

struct Rva002CD4A6Elem
{
    virtual void *Get(int x);
    char m_pad[0x124 - 4];
    bool m_flag124;
};

struct Rva002CD4A6FreePtr
{
    char *p;
// ?Rva002CD4A6FreePtrDtor present-unmatched
    ~Rva002CD4A6FreePtr() { if (p) free(p); }
};

struct Rva002CD4A6RefPtr
{
    OpaqueRefCounted *p;
// ?Rva002CD4A6RefPtrDtor present-unmatched
    ~Rva002CD4A6RefPtr() { if (p) p->Release_Ref(); }
};

class Rva002CD4A6
{
public:
    virtual ~Rva002CD4A6();
private:
    Rva002CD4A6Aux *m_04;
    AsciiString m_08;
    char m_pad0C[0x40 - 0x0C];
    Rva002CD4A6FreePtr m_40;
    char m_pad44[0x4C - 0x44];
    Rva002CD4A6FreePtr m_4C;
    char m_pad50[0x90 - 0x50];
    AsciiString m_90;
    char m_pad94[0xC8 - 0x94];
    Rva002CD4A6RefPtr m_c8;
    char m_padCC[0xD4 - 0xCC];
    Rva002CD4A6RefPtr m_d4;
    char m_padD8[0xDC - 0xD8];
    Rva002CD4A6RefPtr m_dc;
    void *m_e0;
    char m_padE4[0x120 - 0xE4];
    Rva00360D26Member m_120;
    bool m_160;
    char m_pad161[0x178 - 0x161];
    AsciiString m_178;
    _STL::list<int> m_list;
};

Rva002CD4A6::~Rva002CD4A6()
{
    if (m_04)
    {
        void *p = m_04->Get(0);
        ::operator delete(p);
    }
    if (m_e0)
    {
        void *v = m_e0;
        ::operator delete(v);
    }
    for (_STL::list<int>::iterator it = m_list.begin(); it._M_node != m_list.end()._M_node; ++it)
    {
        if (m_160)
        {
            Rva002CD4A6Elem *o1 = (Rva002CD4A6Elem *)(int)*it;
            if (!o1->m_flag124)
                continue;
        }
        Rva002CD4A6Elem *o2 = (Rva002CD4A6Elem *)(int)*it;
        void *p = 0;
        if (o2 != 0)
            p = o2->Get(0);
        ::operator delete(p);
    }
    m_list.clear();
}
