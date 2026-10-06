// cl: /MD
// ?rva002B43BA@Rva002B43BA@@QAEXPAUNode002B43BA@@@Z @0x002B43BA 45B.
// Unlock lane; sibling of 0x002B4360 identical recursive child (+0xC) plus next (+8) free.
// Calls self and rowed free 0x00030830; unblocks 0x002B5558. ret 4.
// TU-local honest-address class.
extern "C" void __cdecl free(void *block);
struct Node002B43BA {
    char m_pad[8];
    Node002B43BA *m_next8;
    Node002B43BA *m_childC;
};
class Rva002B43BA {
public:
    void rva002B43BA(Node002B43BA *head);
};
void Rva002B43BA::rva002B43BA(Node002B43BA *head)
{
    if (head == 0)
        return;
    for (Node002B43BA *p = head; p != 0;) {
        rva002B43BA(p->m_childC);
        Node002B43BA *next = p->m_next8;
        free(p);
        p = next;
    }
}
