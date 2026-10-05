// cl: /O2 /MD
// ?allocBlock@Rva006DB160@@QAEPAXH@Z @0x006DB160 263B
// DOGMA pool allocator allocate, the partner of freeBlock 0x006DB270
// (DogmaPoolFreeBlock.cpp): round the request to 4 (minimum from the low
// nibble of the config byte at +0x13); oversized requests go to the global
// allocator at 0xE17728; sizes with a free-list head use 0x006DAFE0;
// otherwise carve from the first pool with room, creating a 0x0D-filled pool
// at the head of the list when none has room ("pPool->CanFitBytes( nSize )",
// DogmaAllocator.cpp line 441). The new pool is set up by an inline Init
// taking the whole allocation size: computing size-15 there is what makes
// MSVC emit retail's add eax,-15 and load the old head first.
#include <string.h>
inline void *operator new(unsigned int, void *p) { return p; }
extern void *(__cdecl *g_00E17728)(unsigned int);
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
struct _DOGMA_MemPool {
    _DOGMA_MemPool *mpNextPool;
    unsigned int mnPoolSize;
    unsigned int mnPoolFree;
    void Init(_DOGMA_MemPool *next, unsigned int nTotal)
    {
        mnPoolSize = nTotal - sizeof(_DOGMA_MemPool) - 3;
        mnPoolFree = mnPoolSize;
        mpNextPool = next;
    }
    bool CanFitBytes(unsigned int n) const { return mnPoolFree >= n; }
    void *AllocateBytes(unsigned int n)
    {
        unsigned int oldFree = mnPoolFree;
        mnPoolFree = oldFree - n;
        return (unsigned char *)this + sizeof(_DOGMA_MemPool) + (mnPoolSize - oldFree);
    }
};
class Rva006DB160 {
    void **m_table;
    _DOGMA_MemPool *m_firstPool;
    unsigned int m_poolSize;
    unsigned int m_maxSize;
    union {
        unsigned int m_cfg;
        struct { unsigned char m_nextIdx; unsigned char m_sizeIdx; unsigned char m_prevIdx; unsigned char m_minByte; };
    };
    int m_used;
    int m_count;
public:
    void *rva006DAFE0(unsigned int nSize);
    void *allocBlock(int blockSize);
};
void *Rva006DB160::allocBlock(int blockSize)
{
    unsigned int nSize = blockSize;
    if ((nSize & 3) != 0)
        nSize = (nSize & ~3) + 4;
    unsigned int low = (unsigned int)m_minByte & 0xf;
    if (nSize < low)
        nSize = low;
    if (nSize > m_maxSize)
        return g_00E17728(blockSize);
    ++m_used;
    if (m_table[nSize >> 2] != 0)
        return rva006DAFE0(nSize);
    _DOGMA_MemPool *pool = m_firstPool;
    do {
        if (pool->CanFitBytes(nSize))
            return pool->AllocateBytes(nSize);
        pool = pool->mpNextPool;
    } while (pool != 0);
    pool = (_DOGMA_MemPool *)g_00E17728(m_poolSize);
    memset(pool, 0x0d, m_poolSize);
    pool->Init(m_firstPool, m_poolSize); m_firstPool = pool;
    if (!pool->CanFitBytes(nSize)) {
        g_bfmeAptAssertAtE17734("pPool->CanFitBytes( nSize )", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\DogmaAllocator.cpp", 441);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    return pool->AllocateBytes(nSize);
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_00E17728@@3P6APAXI@ZA=?g_bfmeAptAllocAtE17728@@3P6APAXI@ZA")
