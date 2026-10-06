// cl: /O2 /MD
// May2006 Xbox release APT0.19.03 donor supplies AptMath method and static-field
// names; GUID46a11dfd-96b7-4859-900b-d1c12429eda5 age126. Target assertions name
// AptStd/AptMath.h and both count/capacity expressions. Target establishes
// unsigned16 count VA E18100 / capacity E180FC / base pointer E180F4 and stride96.
// ClipTransform_t fields accessed by MakeUnit are independently established
// by native stores: matrix64B at0; four-float mul at64 and add at80.
// Full Ghidra boundaries6CBD10+78 and6DFDF0+82 agree with donor and final returns.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *,const char *,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
class AptMath {
public:
    struct Color4 { float a,b,c,d; };
    struct ClipTransform_t { float m[16]; Color4 mul,add; };
    static ClipTransform_t *ClipStackPush();
    static ClipTransform_t *ClipStackPop();
    static void ClipStackShutdown();
    static void ClipStackPushUnit();
    static void ClipStackInit(unsigned int);
    static void ClipStackMakeUnit();
private:
    static ClipTransform_t *m_pStackBase;
    static unsigned short m_nStackCapacity;
    static unsigned short m_nStackCount;
};

class Rva006DB270
{
public:
    void freeBlock(void *pBlock, int size);
};

void *g_00E180F8;
extern Rva006DB270 *g_pChainBlockAllocator;

AptMath::ClipTransform_t *AptMath::m_pStackBase;
unsigned short AptMath::m_nStackCapacity;
unsigned short AptMath::m_nStackCount;
// The unusual pop assertion is present in retail: preserve it literally.
AptMath::ClipTransform_t *AptMath::ClipStackPop()
{
    if (!(m_nStackCount < m_nStackCapacity)) {
        g_bfmeAptAssertAtE17734("m_nStackCount < m_nStackCapacity", "..\\..\\include\\apt\\AptStd/AptMath.h",91);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    return &m_pStackBase[--m_nStackCount];
}
AptMath::ClipTransform_t *AptMath::ClipStackPush()
{
    if (!((m_nStackCount+1) < m_nStackCapacity)) {
        g_bfmeAptAssertAtE17734("(m_nStackCount+1) < m_nStackCapacity", "..\\..\\include\\apt\\AptStd/AptMath.h",86);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    return &m_pStackBase[++m_nStackCount];
}

// retail 0x006E0020, 55 bytes. Frees the clip-stack allocation via the
// DOGMA deallocator at 0x006DB270 when the base is non-null, then clears
// the base. Size is capacity*96+16. Evidence: same TU owns ClipStackPush
// and ClipStackPop with identical statics (base E180F4 capacity E180FC)
// and stride96; donor JSON labels this address ClipStackShutdown6E0020;
// sole caller 0x006CFAB0 is Apt shutdown; freeBlock resolves via its pin.
void AptMath::ClipStackShutdown()
{
    if (m_pStackBase == 0) {
        m_pStackBase = 0;
        return;
    }
    unsigned short capacity = m_nStackCapacity;
    void *ptr = g_00E180F8;
    int size = capacity * 96 + 16;
    Rva006DB270 *pool = g_pChainBlockAllocator;
    pool->freeBlock(ptr, size);
    m_pStackBase = 0;
}

// Readable7717f8b385e16d10-AptMath.cpp guides all three additions.
// Native6DFFA0..6DFFAA is exactly call Push then tail MakeUnit; static void
// ABI follows both source and no-argument native callee. Native6DFFB0..6E001E
// verifies the unsigned capacity argument, assertion, 96-byte stride and
// 16-byte aligned allocation. Existing pool provider and storage are reused.
class Rva006DB160 { public: void *allocBlock(int); };
#pragma comment(linker, "/alternatename:?rva006dffa0@@YAXXZ=?ClipStackPushUnit@AptMath@@SAXXZ")
void AptMath::ClipStackPushUnit()
{
    ClipStackPush();
    ClipStackMakeUnit();
}
void AptMath::ClipStackInit(unsigned int count)
{
    if (!(count <= 0xFFFF)) {
        g_bfmeAptAssertAtE17734("nMaxTransforms <= 0xFFFF && \"Max Transforms is currently bounded by a uint 16.\"", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptMath.cpp",160);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    g_00E180F8 = reinterpret_cast<Rva006DB160 *>(g_pChainBlockAllocator)->allocBlock(count*96+16);
    unsigned int ptr = reinterpret_cast<unsigned int>(g_00E180F8);
    if (ptr & 15) { ptr += 16; ptr &= ~15; }
    m_pStackBase = reinterpret_cast<ClipTransform_t *>(ptr);
    m_nStackCapacity = count;
    m_nStackCount = 0;
    ClipStackMakeUnit();
}

// Native6DFEA0..6DFF9E establishes this complete254B body and aggregate
// copies. Unlike later packed color helpers, retail stores float vectors.
// Ordinary aggregate assignment preserves the observed stack temporaries.
void AptMath::ClipStackMakeUnit()
{
    Color4 mul={1,1,1,1};
    Color4 add={0,0,0,0};
    if (!(m_nStackCount < m_nStackCapacity)) {
        g_bfmeAptAssertAtE17734("m_nStackCount < m_nStackCapacity", "..\\..\\include\\apt\\AptStd/AptMath.h",96);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    ClipTransform_t *p=&m_pStackBase[m_nStackCount];
    p->m[0]=1.0f; p->m[5]=1.0f; p->m[10]=1.0f; p->m[15]=1.0f;
    p->m[1]=0.0f; p->m[2]=0.0f; p->m[3]=0.0f; p->m[4]=0.0f; p->m[6]=0.0f; p->m[7]=0.0f; p->m[8]=0.0f; p->m[9]=0.0f; p->m[11]=0.0f; p->m[12]=0.0f; p->m[13]=0.0f; p->m[14]=0.0f;
    p->mul=mul;
    p->add=add;
}
