// cl: /O1 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /EHs -ICode/Libraries/Source/WWVegas/WW3D2 -ICode/Libraries/Source/WWVegas/WWLib -ICode/Libraries/Source/WWVegas/WWMath -ICode/Libraries/Source/WWVegas/WWSaveLoad -ICode/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil -Ireference/shims/sweep
// stlport
// ??1Rva002CD4A6@@UAE@XZ @0x002CD4A6 314B unlock: vtable 0x00802170 dtor with list plus strings plus refs plus free, caller 0x002CE047 deleting dtor, neighbours WeaponGetStatus and WeaponRva002CDB0E
#include <vector>
#include <list>

// Retain bfmealloc's native null-checked free and proxy forwarding inline.
// The matched bodies already inline these STLport ownership wrappers.
namespace _STL {
template<> __declspec(dllimport) __forceinline
void allocator<_List_node<int> >::deallocate(pointer p, size_type n) const
{ if (p != 0) ::free((void*)p); }
template<> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<int>*, _List_node<int>, allocator<_List_node<int> > >::deallocate(_List_node<int>* p, size_t n)
{ __stl_alloc_rebind(static_cast<_Base&>(*this), (_List_node<int>*)0).deallocate(p, n); }
}
#include "../../../Libraries/Include/Lib/BfmeE16.h"

// The +0x40/+0x4C members are the Ctor's two _STL::vector<BfmeE16> fields; the
// implicit member destruction frees both starts inline (test/push/call free).
namespace _STL {
template<> __declspec(dllimport) __forceinline
void allocator<BfmeE16>::deallocate(pointer p, size_type n) const
{ if (p != 0) ::free((void*)p); }
template<> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<BfmeE16*, BfmeE16, allocator<BfmeE16> >::deallocate(BfmeE16* p, size_t n)
{ __stl_alloc_rebind(static_cast<_Base&>(*this), (BfmeE16*)0).deallocate(p, n); }
}
#include "ascii_string.h"

#include <new>
#include <stdlib.h>

#include "../../../Libraries/Source/WWVegas/WWLib/OpaqueRefCounted.h"

#include "../../Include/GameLogic/Module/Rva003623E5Member.h"

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

// The ref members adopt the Ctor TU's rowed member types: ??1Rva002CD169RefSlot@@QAE@XZ
// at 0x0010F149 and ??1Rva002CD169RefWords@@QAE@XZ at 0x004C9F38 are matched rows
// (fold-proof= the Ctor TU), so both donors spell the same two member types. Retail's
// cleanups destroy these through a destructor that tests the word at +4 (0x004C9F38),
// so the counted reference is the record's second word at +0xD0/+0xD8 and the only
// word at +0xC8.
#include "../../Include/GameLogic/Module/CashHackSpecialPowerModuleData.h"

struct Rva002CD169RefSlot { unsigned address; __forceinline Rva002CD169RefSlot(){} __forceinline Rva002CD169RefSlot(const void *p):address((unsigned)p){} __forceinline ~Rva002CD169RefSlot(){if(address)((OpaqueRefCounted*)address)->Release_Ref();} };

struct Rva002CD169RefWords {
 CashHackSpecialPowerModuleData::Upgrades words;
 __forceinline ~Rva002CD169RefWords(){if(words.m_amountToSteal)((OpaqueRefCounted*)words.m_amountToSteal)->Release_Ref();}
};

class Rva002CD4A6
{
public:
    virtual ~Rva002CD4A6();
private:
    Rva002CD4A6Aux *m_04;
    AsciiString m_08;
    char m_pad0C[0x40 - 0x0C];
    _STL::vector<BfmeE16> m_40;
    _STL::vector<BfmeE16> m_4C;
    char m_pad58[0x90 - 0x58];
    AsciiString m_90;
    char m_pad94[0xC8 - 0x94];
    Rva002CD169RefSlot m_c8;
    char m_padCC[0xD0 - 0xCC];
    Rva002CD169RefWords m_d0;
    Rva002CD169RefWords m_d8;
    void *m_e0;
    char m_padE4[0x120 - 0xE4];
    Rva003623E5Member m_120;
    char m_pad124[0x160 - 0x124];
    bool m_160;
    char m_pad161[0x178 - 0x161];
    AsciiString m_178;
    _STL::list<int> m_list;
};

Rva002CD4A6::~Rva002CD4A6()
{
    if (m_04)
    {
        void *p = ((Rva002CD4A6Aux *)m_04)->Get(0);
        ::operator delete(p);
    }
    if (m_e0)
    {
        void *v = (void *)m_e0;
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
