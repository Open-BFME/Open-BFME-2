// cl: /MD
// ?rva006E0DE0@Rva006E0DE0@@QAEHPAVAptValue@@@Z, retail 0x006E0DE0, 142 bytes.
// Word-counted Apt pointer-array remove with mnElements/mnMaxElements guards.
// Evidence: unlock lane unblocking 2 callers; Release virtual slot 4 via
// AptValuePtrStack neighbour; same /O2 shape as Apt neighbours.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
class AptValue {
public:
    virtual void AddRef();
    virtual void Release();
};
class Rva006E0DE0 {
    union {
        struct {
            unsigned short m_nElements;
            unsigned short m_nMaxElements;
        };
        int m_0;
    };
    AptValue **m_ppElements;
    int m_8;
    int m_C;
public:
    int rva006E0DE0(AptValue *p);
    void rva006E0E70();
};
int Rva006E0DE0::rva006E0DE0(AptValue *p)
{
    if (m_nElements == 0)
        return 0;
    if (m_nElements >= m_nMaxElements) {
        g_bfmeAptAssertAtE17734("mnElements < mnMaxElements", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptSet.h", 0x43);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    unsigned short nMax = m_nMaxElements;
    int i = 0;
    for (; i < m_nMaxElements; ++i) {
        if (m_ppElements[i] == p)
            break;
    }
    if (i < nMax) {
        --m_nElements;
        m_ppElements[i]->Release();
        m_ppElements[i] = 0;
        return 1;
    }
    return 0;
}

// ?rva006E0E70@Rva006E0DE0@@QAEXXZ, retail 0x006E0E70, 49 bytes.
// Pool teardown clearing +0/+8/+0xC and freeing array via freeBlock.
// Evidence: gap after 0x6E0DE0; pinned freeBlock 0x6DB270 via pool 0xE176E8;
// same /O2 Apt layout as neighbours.
class Rva006DB270
{
public:
    void freeBlock(void *p, int bytes);
};
// Use the defined freeBlock allocator view, not the same-address allocBlock alias.
extern Rva006DB270 *g_pChainBlockAllocator;
void Rva006E0DE0::rva006E0E70()
{
    AptValue **arr = m_ppElements;
    m_0 = 0;
    m_8 = 0;
    m_C = 0;
    if (arr) {
        arr[0] = 0;
        arr[1] = 0;
        arr[2] = 0;
        g_pChainBlockAllocator->freeBlock(arr, 0x1C);
        m_ppElements = 0;
    }
}
