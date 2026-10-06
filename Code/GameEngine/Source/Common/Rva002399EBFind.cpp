// cl: /DNDEBUG /MD
// ?rva002399EB@Rva002399EB@@QAEPAXG@Z, retail 0x002399EB, 37 bytes.
// Circular-list find: head at this+0xF4, key word at node+0xC, return node+8 else NULL.
// Evidence: caller 0x0023B68C; prev 0x00239435 next 0x00239AF4 same flags.
struct Rva002399EBNode {
    Rva002399EBNode *m_next; // +0
    int m_04; // +4
    int m_08; // +8
    unsigned short m_key; // +0xC
};
class Rva002399EB {
    char m_pad[0xF4];
    Rva002399EBNode *m_head; // +0xF4
public:
    void *rva002399EB(unsigned short key);
};
void *Rva002399EB::rva002399EB(unsigned short key)
{
    Rva002399EBNode *head = m_head;
    Rva002399EBNode *cur = head->m_next;
    while (cur != head) {
        if (cur->m_key == key)
            return (void *)((char *)cur + 8);
        cur = cur->m_next;
    }
    return 0;
}
