// cl: /MD
// ?rva006FE0B0@AptBasePtrStack@@QAEXH@Z @0x006FE0B0 105B capacity init over pool allocator.
// Retail asserts m_nSize==0 (_AptBasePtrStack.h:0x59), stores arg to +4, allocs
// size*4 via pool 0x00E176E8 (rowed/pinned allocBlock 0x006DB160), stores to +8,
// asserts non-null (:0x5E). Evidence: unlock lane; layout/flags/assert triple
// shared with AptBasePtrStackPopAndPush TU; callers at 0x006FEB08/14/20.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

class Rva006DB160
{
public:
    void *allocBlock(int blockSize);
};
extern class Rva006DB270 *g_pChainBlockAllocator;

class AptBasePtrStack
{
public:
    void rva006FE0B0(int nSize);

    int m_nElements;
    int m_nSize;
    void **m_aElements;
};

void AptBasePtrStack::rva006FE0B0(int nSize)
{
    if (m_nSize != 0) {
        g_bfmeAptAssertAtE17734("m_nSize == 0", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptValuePtrStack.h", 0x59);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    m_nSize = nSize;
    m_aElements = (void **)(*(Rva006DB160 **)&g_pChainBlockAllocator)->allocBlock(nSize * 4);
    if (m_aElements == 0) {
        g_bfmeAptAssertAtE17734("m_aElements != NULL", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptValuePtrStack.h", 0x5E);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
}
