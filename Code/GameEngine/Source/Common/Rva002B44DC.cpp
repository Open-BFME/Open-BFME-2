// cl: /MD
// ?rva002B44DC@Rva002B44DC@@QAEXPAUNode002B44DC@@@Z @0x002B44DC 45B.
// Unlock lane; sibling of 0x002B4360 identical recursive child (+0xC) plus next (+8) free.
// Calls self and rowed free 0x00030830; unblocks 0x002B57AC. ret 4.
// TU-local honest-address class.
extern "C" void __cdecl free(void *block);
struct Node002B44DC {
    char m_pad[8];
    Node002B44DC *m_next8;
    Node002B44DC *m_childC;
};
class Rva002B44DC {
public:
    void rva002B44DC(Node002B44DC *head);
};
void Rva002B44DC::rva002B44DC(Node002B44DC *head)
{
    if (head == 0)
        return;
    for (Node002B44DC *p = head; p != 0;) {
        rva002B44DC(p->m_childC);
        Node002B44DC *next = p->m_next8;
        free(p);
        p = next;
    }
}
