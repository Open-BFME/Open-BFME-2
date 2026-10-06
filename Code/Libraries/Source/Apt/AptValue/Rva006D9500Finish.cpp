// ?rva006D9500@Rva006D9500@@QAEXH@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Apt array reserve: grow 4-byte elements to next pow2 >= requested (min 8)
// via ChainBlockAllocator, memset new, memcpy old, free old.
// Evidence: 210B __thiscall ret 4; +0x20 ptr +0x24 count; pow2 loop dec/sar;
// allocBlock pin 0x6DB160; asserts "_aArray != NULL" + Apt path + 0xE5;
// freeBlock row 0x6DB270; callers 0x6D95E0 0x6D9780 0x6D9B50 0x6D9CE0 etc.
class Rva006DB160
{
public:
    void *allocBlock(int size);
};

class Rva006DB270
{
public:
    void freeBlock(void *ptr, int size);
};

extern Rva006DB270 *g_pChainBlockAllocator;
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *a, const char *b, int c);
extern int g_bfmeAptBreakOnAssertAtDDC01C;

#include <cstring>

static __forceinline Rva006DB270 *chainAllocOf(void)
{
    return g_pChainBlockAllocator;
}

class Rva006D9500
{
public:
    void rva006D9500(int requested);

private:
    char _pad0[0x20];
    void *m_array20;
    int m_count24;
};

void Rva006D9500::rva006D9500(int requested)
{
    int cmpCap = m_count24;
    int shift = 0;
    if (cmpCap >= requested)
        return;
    int n = requested - 1;
    if (n != 0)
    {
        do
        {
            n >>= 1;
            ++shift;
        } while (n != 0);
    }
    int cap = 1 << shift;
    if (cap < 8)
        cap = 8;
    void *mem = ((Rva006DB160 *)chainAllocOf())->allocBlock(cap * 4);
    if (mem == 0)
    {
        g_bfmeAptAssertAtE17734("_aArray != NULL", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptArray.cpp", 0xE5);
        if (g_bfmeAptBreakOnAssertAtDDC01C != 0)
            __asm int 3;
    }
    ::memset(mem, 0, cap * 4);
    if (m_array20 != 0)
    {
        ::memcpy(mem, m_array20, m_count24 * 4);
        chainAllocOf()->freeBlock(m_array20, m_count24 * 4);
    }
    m_count24 = cap;
    m_array20 = mem;
}
