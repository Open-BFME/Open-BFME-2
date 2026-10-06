// cl: /MD
// ?rva006CDBD0@Rva006CDBD0@@QAEXXZ @0x006CDBD0 32B evidence calls rowed freeBlock size 8 via g_pChainBlockAllocator plus head link at +4
class Rva006DB270
{
public:
    void freeBlock(void *block, int blockSize);
};
extern Rva006DB270 *g_pChainBlockAllocator; // 0x00E176E8
struct Rva006CDBD0Node {
    int m_unk00;
    Rva006CDBD0Node *m_next;
};
class Rva006CDBD0 {
    Rva006CDBD0Node *m_head;
public:
    void rva006CDBD0();
};
void Rva006CDBD0::rva006CDBD0()
{
    Rva006CDBD0Node *head = m_head;
    if (head == 0)
        return;
    Rva006CDBD0Node *next = head->m_next;
    g_pChainBlockAllocator->freeBlock(head, 8);
    m_head = next;
}
