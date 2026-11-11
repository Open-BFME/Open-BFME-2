// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Address-derived recovery of 0x0015B110 (136B), a ref-counted object factory.
// Retail: operator new(0x34) 0x002FDA0, copy-construct this via FXShaderSetup's
// copy ctor 0x00152DE9 (vtable 0x00BD3B1C, refcount at +4), store into the hidden
// return pointer, then the smart pointer's copy AddRef ([p+4]+=1) and
// temporary Release ([p+4]-=1, deleting through vtable[0] on zero). The
// hidden-pointer ret 4 and AssetReference-style temp match the rowed
// sharebuf/RefCount family. Ctor and class names are address-derived.

#include "FXShaderSetup.h"

class RefPtr
{
public:
    RefCountClass *m_ptr;

    RefPtr(RefCountClass *refCount) : m_ptr(refCount) {}
    RefPtr(const RefPtr &other) : m_ptr(other.m_ptr)
    {
        if (m_ptr)
            m_ptr->Add_Ref();
    }
    // Release through the pointer already loaded: retail's one out-of-line
    // copy is 0x0007B724 (17 B, as MeshMatDescUniqueArrays.cpp builds it);
    // re-reading m_ptr after the decrement emitted a 19-byte copy.
    ~RefPtr()
    {
        RefCountClass *refCount = m_ptr;
        if (refCount)
            refCount->Release_Ref();
    }
};

class Rva0015B110Owner
{
public:
    RefPtr rva0015b110();
};

RefPtr Rva0015B110Owner::rva0015b110()
{
    RefPtr temp(new FXShaderSetup(*reinterpret_cast<const FXShaderSetup *>(this)));
    return temp;
}
