// cl: /O2 /MD
// May2006 Xbox release APT0.19.03 donor supplies AptMath method and static-field
// names; GUID46a11dfd-96b7-4859-900b-d1c12429eda5 age126. Target assertions name
// AptStd/AptMath.h and both count/capacity expressions. Target establishes
// unsigned16 count VA E18100 / capacity E180FC / base pointer E180F4 and stride96.
// ClipTransform_t is an opaque stride view; no internal donor layout is claimed.
// Full Ghidra boundaries6CBD10+78 and6DFDF0+82 agree with donor and final returns.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *,const char *,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
class AptMath {
public:
    struct ClipTransform_t { unsigned char unaccessed[96]; };
    static ClipTransform_t *ClipStackPush();
    static ClipTransform_t *ClipStackPop();
    static void ClipStackShutdown();
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

extern void *g_00E180F8;
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
