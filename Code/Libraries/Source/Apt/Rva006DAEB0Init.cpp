// cl: /O2 /MD
// ??0Rva006DAEB0@@QAE@IHHIEEEEE@Z @0x006DAEB0 226B
// Native6CC380 allocates28B and invokes this in two EH-protected new
// expressions. WB174D320 calls constructor1776790 and its derived wrapper.
// Re-expressing the former method as a real constructor preserves all226B.
// Target evidence: two calls through the allocator at 0x00E17728 followed by
// table zero-fill, a 0x0D pool fill and initialization of the pool header.
// Structural inference: the state prefix agrees with matched allocBlock
// 0x006DB160 and freeBlock 0x006DB270. The real owner name is not pinned by
// target evidence, so this method keeps its address-derived identifier.
#include <string.h>
extern void *(__cdecl *g_bfmeAptAllocAtE17728)(unsigned int);
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
    Rva006DAEB0(unsigned int a1, int a2, int dummy, unsigned int maxSize, unsigned char off0, unsigned char flag0, unsigned char off1, unsigned char flag1, unsigned char off2);
};
// Keep the pool byte stores ordered as retail before computing the pool size.
// The volatile lvalues preserve the two ordered writes without changing the field layout.
Rva006DAEB0::Rva006DAEB0(unsigned int a1, int a2, int dummy, unsigned int maxSize, unsigned char off0, unsigned char flag0, unsigned char off1, unsigned char flag1, unsigned char off2)
{
    m_table = 0;
    m_firstPool = 0;
    m_maxSize = maxSize;
    (void)dummy;
    m_unk08 = a2;
    m_cfg = (m_cfg & 0xcfffffff) | ((((flag1 & 1) << 1) | (flag0 & 1)) << 28);
    m_used = 0;
    m_count = 0;
    m_table = g_bfmeAptAllocAtE17728(maxSize + 4);
    m_firstPool = g_bfmeAptAllocAtE17728(a1);
    memset(m_table, 0, m_maxSize + 4);
    memset(m_firstPool, 0x0d, a1);
    m_b0 = (unsigned char)(off0 >> 2);
    _DOGMA_MemPool *pool = (_DOGMA_MemPool *)m_firstPool;
    unsigned char b1 = (unsigned char)(off1 >> 2);
    *reinterpret_cast<volatile unsigned char *>(&m_b1) = b1;
    unsigned char b2 = (unsigned char)(off2 >> 2);
    *reinterpret_cast<volatile unsigned char *>(&m_b2) = b2;
    unsigned int inner = a1 - 15;
    pool->mpNextPool = 0;
    pool->mnPoolSize = inner;
    pool->mnPoolFree = inner;
    m_cfg = (m_cfg & ~0x0f000000) | ((maxSize << 24) & 0x0f000000);
}