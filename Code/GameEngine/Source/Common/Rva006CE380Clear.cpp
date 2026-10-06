// cl: /MD
// ?rva006CE380@Rva006CE380@@QAEXXZ @0x006CE380 49B evidence chain via 0x006DB270 freeBlock plus pool 0x00A176E8 size 8 plus next-at-+4 list clear plus callers 0x006D10DD and 0x006CE560
class Rva006DB270 {
public:
    void freeBlock(void *p, int size);
};
extern Rva006DB270 *g_pChainBlockAllocator;
struct Rva006CE380Node {
    int m00;
    Rva006CE380Node *m04;
};
struct Rva006CE380 {
    Rva006CE380Node *m_head;
    void rva006CE380();
};
void Rva006CE380::rva006CE380()
{
    while (m_head != 0) {
        Rva006CE380Node *cur = m_head;
        if (cur != 0) {
            Rva006CE380Node *next = cur->m04;
            g_pChainBlockAllocator->freeBlock(cur, 8);
            m_head = next;
        }
    }
}
