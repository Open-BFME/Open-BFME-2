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
    friend void *__cdecl rva006F73A0(void *, void *, int);
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


// Target evidence: 0x006F73A0 is the callback selected beside 0x006F7330 by
// the retail traversal at 0x006F7720 when flag bit 2 is set. Its body checks
// the AptMath clip-stack count/capacity (globals 0x00E18100/0x00E180FC), pushes
// one 96-byte ClipTransform_t, composes its matrix through the rowed
// bfmeCombine1236 helper, folds the four multiplier/add vectors, updates the
// input object through 0x006E15C0, and tail-returns ClipStackPop at 0x006CBD10.
// The six affine floats, color vectors, and field +0x48 are target-observed
// offsets; the callback's owner/name and the two address-derived callee views
// remain structural inferences, so the exported callback name stays RVA-based.
struct Rva006F73A0Input
{
    unsigned char prefix00[0x0c];
    float a, b, c, d, tx, ty;
    AptMath::Color4 mul, add;
    unsigned char pad44[4];
    void *field48;
};

class Rva006DBB30SarDwordField
{
public:
    int get() const;
};
class BfmeAptValue006DCD20
{
public:
    bool isUndefined() const;
};
class Rva006E1260
{
public:
    void call(void *);
};
class Rva006E15C0
{
public:
    void call(void *, void *, int);
};
struct BfmeTransform1236
{
    float m[16];
    float mul[4];
    float add[4];
};
void __cdecl bfmeCombine1236(BfmeTransform1236 *, BfmeTransform1236 *, BfmeTransform1236 *);

void *__cdecl rva006F73A0(void *argument1, void *argument2, int argument3)
{
    const Rva006F73A0Input *input = (const Rva006F73A0Input *)argument2;
    if (input == 0) {
        g_bfmeAptAssertAtE17734("this",
            "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0xC4);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    if (((const Rva006DBB30SarDwordField *)input)->get() == 15 &&
        !((const BfmeAptValue006DCD20 *)input)->isUndefined()) {
        ((Rva006E1260 *)input)->call(input->field48);
    }
    if (!(AptMath::m_nStackCount < AptMath::m_nStackCapacity)) {
        g_bfmeAptAssertAtE17734("m_nStackCount < m_nStackCapacity",
            "..\\..\\include\\apt\\AptStd/AptMath.h", 0x60);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    AptMath::ClipTransform_t *parent = AptMath::m_pStackBase + AptMath::m_nStackCount;
    AptMath::ClipTransform_t *current = AptMath::ClipStackPush();

    current->m[0] = input->a;
    current->m[1] = input->b;
    current->m[2] = 0.0f;
    current->m[3] = 0.0f;
    current->m[4] = input->c;
    current->m[5] = input->d;
    current->m[6] = 0.0f;
    current->m[7] = 0.0f;
    current->m[8] = 0.0f;
    current->m[9] = 0.0f;
    current->m[11] = 0.0f;
    current->m[10] = 1.0f;
    current->m[12] = input->tx;
    current->m[13] = input->ty;
    current->m[15] = 1.0f;
    current->m[14] = 0.0f;
    current->mul = input->mul;
    current->add = input->add;

    bfmeCombine1236((BfmeTransform1236 *)current,
                    (BfmeTransform1236 *)parent,
                    (BfmeTransform1236 *)current);
    current->mul.a = parent->mul.a * current->mul.a;
    current->mul.b = parent->mul.b * current->mul.b;
    current->mul.c = parent->mul.c * current->mul.c;
    current->mul.d = parent->mul.d * current->mul.d;
    current->add.a = parent->add.a + current->add.a;
    current->add.b = parent->add.b + current->add.b;
    current->add.c = parent->add.c + current->add.c;
    current->add.d = parent->add.d + current->add.d;
    ((Rva006E15C0 *)input)->call(argument1, current, argument3);
    return AptMath::ClipStackPop();
}
