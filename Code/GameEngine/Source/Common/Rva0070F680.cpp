// cl: (none -- build.py base flags)
//
// ?rva0070F680@Rva0070F680@@QAEXPAXH@Z @0x0070F680 96B. Iterates the indexed
// bucket at this+4 (8-byte entries {count, array}) and for each element whose
// first dword is 1 enqueues a type-1 Apt action via rowed AptActionQueueC
// 0x006E4B80 with (elem+1, pArg, 0x200000, g_00E17704) and this taken from
// g_bfmeAptPtrAtE176D0+0xA0. Evidence: chain lane (callee just landed);
// callers 0x006E2C10 0x006E2D60; globals E176D0 (extern name in use) E17704.
class AptCIH;
class AptActionQueueC
{
public:
    void rva006E4B80(void *pArg1, AptCIH *pCIH, int iArg3, int iArg4);
};
class Rva006E34D0
{
public:
    char _pad[0xA0];
    AptActionQueueC *m_queue;
};
extern Rva006E34D0 *g_bfmeAptPtrAtE176D0;
extern int g_00E17704;
struct Rva0070F680Entry
{
    int count;
    int **items;
};
class Rva0070F680
{
public:
    int m_0;
    Rva0070F680Entry *m_table;
    void rva0070F680(void *pArg, int idx);
};
void Rva0070F680::rva0070F680(void *pArg, int idx)
{
    for (int i = 0; i < m_table[idx].count; ++i) {
        int *q = m_table[idx].items[i];
        if (*q == 1)
            g_bfmeAptPtrAtE176D0->m_queue->rva006E4B80(q + 1, (AptCIH *)pArg, 0x200000, g_00E17704);
    }
}
