// cl: /DNDEBUG /MD
// ?rva006CE860@Rva006CE860@@QAEXXZ @0x006CE860 41B evidence pop-front via rowed detach 0x006CD530 plus pool free 8 via rowed 0x006DB270; prev ModuleTagString next ChainDrain
class Rva006DB270
{
public:
    void freeBlock(void *block, int blockSize);
};
extern Rva006DB270 *g_pChainBlockAllocator;
class Rva006CD530
{
public:
    void detach();
    void *m_00;
    Rva006CD530 *m_next;
};
class Rva006CE860
{
public:
    void rva006CE860();
private:
    Rva006CD530 *m_head;
};
void Rva006CE860::rva006CE860()
{
    Rva006CD530 *head = m_head;
    if (head == 0)
        return;
    Rva006CD530 *next = head->m_next;
    head->detach();
    g_pChainBlockAllocator->freeBlock(head, 8);
    m_head = next;
}
