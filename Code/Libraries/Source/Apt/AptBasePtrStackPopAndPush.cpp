// cl: /MD
// ?PopAndPush@AptBasePtrStack@@QAEXHPAVBfmeAptValue006DCD20@@@Z @0x006FDFA0 162B
// Pop-and-push single value: asserts nItems >= 0 (_AptBasePtrStack.h:201),
// returns early when popping more than contained (:205 via shared Apt assert
// triple), else AddRefs the new value, Releases the top nItems in order,
// stores the value and nets the count. Evidence: unlock lane; callers
// 0x006FE910 0x007066AD; layout/flags/assert file shared with
// AptBasePtrStackPush.cpp; Bitwise PopAndPush decl names the method.
// ??1AptBasePtrStack@@QAE@XZ @0x006FDD40 110B dtor: asserts empty (:78),
// asserts pfnMemFreeSize (:84), frees backing array via pool freeBlock.
// Evidence: same TU/class/flags/triple; unwind caller; unblocks 0x006FE9C0.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
extern void (__cdecl *g_bfmeAptFreeSizeAtE17730)(void *, unsigned int);
extern void *(__cdecl *g_bfmeAptAllocAtE17728)(unsigned int);
void __debugbreak();
#pragma intrinsic(__debugbreak)

class Rva006DB270
{
public:
    void freeBlock(void *p, int bytes);
};
class Rva006DB160
{
public:
    void *allocBlock(int blockSize);
};
extern Rva006DB270 *g_pChainBlockAllocator; // 0x00E176E8

class BfmeAptValue006DCD20
{
public:
    virtual void AddRef();
    virtual void Release();
    int isLookup() const;
    int isRegister() const;
};

class AptBasePtrStack
{
public:
    void PopAndPush(int nItems, BfmeAptValue006DCD20 *pValue);
    void rva006FE050(int nItems);
    void rva006FE880(int nItems, BfmeAptValue006DCD20 *pValue);
    void rva006FDE50();
    void rva006FE120();
    void rva006FDDB0(int nCapacity);
    void rva006FDF30(BfmeAptValue006DCD20 *pValue);
    void rva006FDEE0(BfmeAptValue006DCD20 *pValue);
    void rva006FE920();
    ~AptBasePtrStack();

    int m_nElements;
    int m_nCapacity;
    BfmeAptValue006DCD20 **m_aElements;
};

void AptBasePtrStack::PopAndPush(int nItems, BfmeAptValue006DCD20 *pValue)
{
    if (nItems < 0) {
        g_bfmeAptAssertAtE17734("nItems >= 0", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptBasePtrStack.h", 201);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    if (m_nElements < nItems) {
        g_bfmeAptAssertAtE17734("false && \"[APT] Error, Popping more elements than the stack contains. Please contact the Apt Team for Support.\"", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptBasePtrStack.h", 205);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __asm int 3
        return;
    }
    pValue->AddRef();
    for (int i = 1; i <= nItems; ++i) {
        m_aElements[m_nElements - i]->Release();
    }
    m_aElements[m_nElements - nItems] = pValue;
    m_nElements = m_nElements + 1 - nItems;
}

void AptBasePtrStack::rva006FE880(int nItems, BfmeAptValue006DCD20 *pValue)
{
    if (!pValue) {
        g_bfmeAptAssertAtE17734("pValue", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptActionInterpreter.inl", 200);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    if (static_cast<unsigned char>(pValue->isLookup())) {
        g_bfmeAptAssertAtE17734("pValue->isLookup() == false", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptActionInterpreter.inl", 201);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    if (static_cast<unsigned char>(pValue->isRegister())) {
        g_bfmeAptAssertAtE17734("pValue->isRegister() == false", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptActionInterpreter.inl", 202);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    PopAndPush(nItems, pValue);
}

void AptBasePtrStack::rva006FE050(int nItems)
{
    if (nItems > 0) {
        if (m_nElements < nItems) {
            g_bfmeAptAssertAtE17734("false && \"[APT] Error, Popping more elements than the stack contains. Please contact the Apt Team for Support.\"", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptBasePtrStack.h", 240);
            if (g_bfmeAptBreakOnAssertAtDDC01C)
                __asm int 3
            return;
        }
        for (int i = 1; i <= nItems; ++i) {
            m_aElements[m_nElements - i]->Release();
        }
        m_nElements -= nItems;
    }
}

AptBasePtrStack::~AptBasePtrStack()
{
    if (m_nElements != 0) {
        g_bfmeAptAssertAtE17734("m_nElements == 0", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptBasePtrStack.h", 0x4E);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    if (m_aElements) {
        if (!g_bfmeAptFreeSizeAtE17730) {
            g_bfmeAptAssertAtE17734("gAptFuncs.pfnMemFreeSize", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptBasePtrStack.h", 0x54);
            if (g_bfmeAptBreakOnAssertAtDDC01C)
                __debugbreak();
        }
        g_pChainBlockAllocator->freeBlock(m_aElements, m_nCapacity * 4);
    }
}

void AptBasePtrStack::rva006FDE50()
{
    if (m_nElements != 0) {
        g_bfmeAptAssertAtE17734("m_nElements == 0", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptBasePtrStack.h", 0x68);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    if (m_aElements) {
        if (!g_bfmeAptFreeSizeAtE17730) {
            g_bfmeAptAssertAtE17734("gAptFuncs.pfnMemFreeSize", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptBasePtrStack.h", 0x6B);
            if (g_bfmeAptBreakOnAssertAtDDC01C)
                __debugbreak();
        }
        g_pChainBlockAllocator->freeBlock(m_aElements, m_nCapacity * 4);
    }
    m_nCapacity = 0;
    m_nElements = 0;
    m_aElements = 0;
}

// ?rva006FE120@AptBasePtrStack@@QAEXXZ, retail 0x006FE120, 51 bytes.
// No-assert teardown of AptBasePtrStack: frees backing array via rowed
// freeBlock 0x006DB270 through g_pChainBlockAllocator 0x00E176E8 then zeroes
// +4/+0/+8. Evidence: same TU/class/flags/layout as rva006FDE50 Shutdown
// sibling minus its two asserts; chain lane via 0x006DB270; prev/next
// 0x006FE0B0/0x006FE160 same /O2 Apt stack family.
void AptBasePtrStack::rva006FE120()
{
    if (m_aElements) {
        g_pChainBlockAllocator->freeBlock(m_aElements, m_nCapacity * 4);
    }
    m_nCapacity = 0;
    m_nElements = 0;
    m_aElements = 0;
}

void AptBasePtrStack::rva006FDDB0(int nCapacity)
{
    if (m_nCapacity != 0) {
        g_bfmeAptAssertAtE17734("m_nCapacity == 0", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptBasePtrStack.h", 0x5C);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    m_nCapacity = nCapacity;
    if (!g_bfmeAptAllocAtE17728) {
        g_bfmeAptAssertAtE17734("gAptFuncs.pfnMemAlloc", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptBasePtrStack.h", 0x5F);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    m_aElements = (BfmeAptValue006DCD20 **)((Rva006DB160 *)g_pChainBlockAllocator)->allocBlock(nCapacity * 4);
    if (!m_aElements) {
        g_bfmeAptAssertAtE17734("m_aElements != NULL", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptBasePtrStack.h", 0x63);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
}

void AptBasePtrStack::rva006FDF30(BfmeAptValue006DCD20 *pValue)
{
    if (m_nElements >= m_nCapacity) {
        g_bfmeAptAssertAtE17734("m_nElements < m_nCapacity", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptBasePtrStack.h", 0x90);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    m_aElements[m_nElements] = pValue;
    ++m_nElements;
}

void AptBasePtrStack::rva006FDEE0(BfmeAptValue006DCD20 *pValue)
{
    if (m_nElements >= m_nCapacity) {
        g_bfmeAptAssertAtE17734("m_nElements < m_nCapacity", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptBasePtrStack.h", 0x80);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    m_aElements[m_nElements] = pValue;
    ++m_nElements;
    pValue->AddRef();
}

void AptBasePtrStack::rva006FE920()
{
    if (m_nElements <= 0) {
        g_bfmeAptAssertAtE17734("false && \"[APT] Error, Popping from Stack with 0 elements. Please contact the Apt Team for Support.\"", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptBasePtrStack.h", 0x98);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __asm int 3
        return;
    }
    m_aElements[m_nElements - 1]->Release();
    --m_nElements;
}
