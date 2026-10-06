// cl: /MD
// ?rva001F416C@Rva001F416C@@QAEXPAUNode001F416C@@H@Z @0x001F416C 67B.
// Insert node at head of slot list when flag clear; mirrors unlink at
// 0x001F4882 which uses same +0x10 +0x2c +0x50 and +0x6c +0x70 +0x75.
// Evidence: unlock lane plus matching offsets plus ret-8 two-arg shape.
struct Node001F416C
{
    char m_pad[0x6c];
    Node001F416C *m_prev;
    Node001F416C *m_next;
    char m_gap;
    unsigned char m_flag;
};
class Rva001F416C
{
public:
    void rva001F416C(Node001F416C *node, int slot);
private:
    char m_pad0[0x10];
    Node001F416C *m_arr1[7];
    Node001F416C *m_arr2[9];
    int m_count;
};
void Rva001F416C::rva001F416C(Node001F416C *node, int slot)
{
    if (node->m_flag != 0)
        return;
    if (m_arr1[slot] == 0)
        m_arr1[slot] = node;
    Node001F416C **pp = &m_arr2[slot];
    if (*pp != 0) {
        (*pp)->m_prev = node;
        node->m_next = *pp;
    } else {
        node->m_next = 0;
    }
    *pp = node;
    node->m_prev = 0;
    node->m_flag = 1;
    ++m_count;
}
