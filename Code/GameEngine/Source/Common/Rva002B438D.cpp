// cl: /MD
// ?rva002B438D@Rva002B438D@@QAEXPAUNode002B438D@@@Z @0x002B438D 45B.
// Unlock lane; sibling of 0x002B4360 identical recursive child (+0xC) plus next (+8) free.
// Calls self and rowed free 0x00030830; unblocks 0x002B5522. ret 4.
// TU-local honest-address class.
extern "C" void __cdecl free(void *block);
struct Node002B438D {
    char m_pad[8];
    Node002B438D *m_next8;
    Node002B438D *m_childC;
};
class Rva002B438D {
public:
    void rva002B438D(Node002B438D *head);
};
void Rva002B438D::rva002B438D(Node002B438D *head)
{
    if (head == 0)
        return;
    for (Node002B438D *p = head; p != 0;) {
        rva002B438D(p->m_childC);
        Node002B438D *next = p->m_next8;
        free(p);
        p = next;
    }
}
