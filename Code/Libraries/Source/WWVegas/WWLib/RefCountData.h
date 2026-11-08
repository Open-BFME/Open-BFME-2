// Target facts: ctor RVA 0x00072882 stores vptr VA 0x00BC650C and int +4 = 1; dtor RVA 0x00072892 restores that vptr. The next table at VA 0x00BC6514 bounds this table to two slots: Delete_This at RVA 0x0006CE57 and the protected deleting destructor at RVA 0x00072899. RefCountClass has virtual functions, no base, and an eight-byte release layout (derived FXShaderSetup RVA 0x001525FB starts its own storage at +8).
// Release_Ref RVA 0x005D1A7D decrements int +4 and dispatches slot 0 only at zero; W3DShroud RVA 0x0006F1FE increments the same field. The ShareBufferClass copy at RVA 0x0015ACB0 resets the base count to 1. RVA 0x000728C6 calls the protected destructor out of line. Zero Hour WWLib/refcount.h proves the names NumRefs, Add_Ref, Num_Refs and Delete_This and the count-reset copy semantics; its const accessors differ from the non-const retail Release_Ref ledger name.
// The derived constructor RVA 0x000728B6 installs VA 0x00BC6514, whose deleting wrapper calls the base destructor. MeshModelClass's shader reader increments the count at RVA 0x0018AFE2 and decrements it at RVA 0x0018B027; public NumRefs exposes this field to the reader's verified reference helpers without asserting the original source's access control.

#ifndef BFME2_WWLIB_REFCOUNTDATA_H
#define BFME2_WWLIB_REFCOUNTDATA_H

// One RefCountClass for both header families: Zero Hour's refcount.h (which rendobj.h includes) uses
// REFCOUNT_H, so whichever of the two a unit reaches first defines the class and the other is skipped.
#ifndef REFCOUNT_H
#define REFCOUNT_H

class RefCountClass
{
public:
    RefCountClass() : NumRefs(1) {}
    RefCountClass(const RefCountClass &) : NumRefs(1) {}

    void Add_Ref() { ++NumRefs; }
    void Release_Ref() { --NumRefs; if (NumRefs == 0) Delete_This(); }
    int Num_Refs() { return NumRefs; }
    // Retail keeps this body as a header COMDAT: 0x0006CE57 (every RefCountClass-derived table's slot 0)
    // and an identical unreferenced copy at 0x0030F466 in FXParticleSystem.cpp's region.
    virtual void Delete_This() { delete this; }

protected:
    virtual ~RefCountClass();

public:
    int NumRefs;
};


// refcount.h's pointer macros (NDEBUG forms), for units that reach this header first.
#ifndef NEW_REF
#define NEW_REF( C, P ) ( W3DNEW C P )
#endif
#ifndef SET_REF_OWNER
#define SET_REF_OWNER( P ) P
#endif
#ifndef REF_PTR_SET
#define REF_PTR_SET(dst,src) { if (src) (src)->Add_Ref(); if (dst) (dst)->Release_Ref(); (dst) = (src); }
#endif
#ifndef REF_PTR_RELEASE
#define REF_PTR_RELEASE(x) { if (x) { x->Release_Ref(); x = NULL; } }
#endif

#endif // REFCOUNT_H
#endif
