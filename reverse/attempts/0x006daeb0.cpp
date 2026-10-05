// ?rva006DAEB0@Rva006DAEB0@@QAEPAV1@IHHIEEEEE@Z
// partial score=0.982 date=2026-10-05
// cl: /O2 /MD
// ?rva006DAEB0@Rva006DAEB0@@QAEPAV1@IHHIEEEEE@Z @0x006DAEB0 226B: Dogma pool manager init with table and pool allocs
// Evidence: neighbour DogmaPoolFree 0x006DB090 same layout +0 +4 +8 +C +10 +14 +18; caller 0x006CC380; two g_00E17728 allocs with memset 0 and 0x0D; offsets match Rva006DB270 freeBlock class
#include <string.h>
extern void *(__cdecl *g_00E17728)(unsigned int);
struct _DOGMA_MemPool {
    void *mpNextPool;
    unsigned int mnPoolSize;
    unsigned int mnPoolFree;
};
class Rva006DAEB0 {
    void *m_table;
    void *m_firstPool;
    int m_unk08;
    unsigned int m_maxSize;
    union {
        unsigned int m_cfg;
        struct { unsigned char m_b0; unsigned char m_b1; unsigned char m_b2; unsigned char m_b3; };
    };
    int m_used;
    int m_count;
public:
    Rva006DAEB0 *rva006DAEB0(unsigned int a1, int a2, int dummy, unsigned int maxSize, unsigned char off0, unsigned char flag0, unsigned char off1, unsigned char flag1, unsigned char off2);
};
Rva006DAEB0 *Rva006DAEB0::rva006DAEB0(unsigned int a1, int a2, int dummy, unsigned int maxSize, unsigned char off0, unsigned char flag0, unsigned char off1, unsigned char flag1, unsigned char off2)
{
    m_table = 0;
    m_firstPool = 0;
    m_maxSize = maxSize;
    (void)dummy;
    m_unk08 = a2;
    m_cfg = (m_cfg & 0xcfffffff) | ((((flag1 & 1) << 1) | (flag0 & 1)) << 28);
    m_used = 0;
    m_count = 0;
    m_table = g_00E17728(maxSize + 4);
    m_firstPool = g_00E17728(a1);
    memset(m_table, 0, m_maxSize + 4);
    memset(m_firstPool, 0x0d, a1);
    m_b0 = (unsigned char)(off0 >> 2);
    _DOGMA_MemPool *pool = (_DOGMA_MemPool *)m_firstPool;
    unsigned int inner = a1 - 15;
    m_b1 = (unsigned char)(off1 >> 2);
    m_b2 = (unsigned char)(off2 >> 2);
    pool->mpNextPool = 0;
    pool->mnPoolSize = inner;
    pool->mnPoolFree = inner;
    m_cfg = (m_cfg & ~0x0f000000) | ((maxSize << 24) & 0x0f000000);
    return this;
}
