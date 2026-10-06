// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?remove@Rva00432F23@@QAEXPAVRva00432F23Node@@@Z @0x00432F23 90B
// Doubly-linked removal across two head/tail pairs with shared count:
// refreshes any of +0x0C +0x10 +0x14 +0x18 that points at the node, splices
// neighbours, clears the node links and decrements +0x1C. Evidence: single
// caller at 0x004C9DF6, layout with next at +0x14 and prev at +0x18 read off
// retail offsets. Honest address-derived name: identity unproven from 90B.

class Rva00432F23Node
{
public:
    char m_pad[0x14];
    Rva00432F23Node *m_next; // +14
    Rva00432F23Node *m_prev; // +18
};

class Rva00432F23
{
public:
    void remove(Rva00432F23Node *node);
    void rva00432F7D(Rva00432F23Node *node);
    void rva00432EC0(Rva00432F23Node *node);
    void rva00432E5D(Rva00432F23Node *node);

private:
    char m_pad[0xC];
    Rva00432F23Node *m_head1; // +C
    Rva00432F23Node *m_tail1; // +10
    Rva00432F23Node *m_head2; // +14
    Rva00432F23Node *m_tail2; // +18
    int m_count; // +1C
};

void Rva00432F23::remove(Rva00432F23Node *node)
{
    if (m_head1 == node)
        m_head1 = node->m_next;
    if (m_tail1 == node)
        m_tail1 = node->m_prev;
    if (m_head2 == node)
        m_head2 = node->m_next;
    if (m_tail2 == node)
        m_tail2 = node->m_prev;
    if (node->m_next)
        node->m_next->m_prev = node->m_prev;
    if (node->m_prev)
        node->m_prev->m_next = node->m_next;
    node->m_next = 0;
    node->m_prev = 0;
    --m_count;
}

void Rva00432F23::rva00432F7D(Rva00432F23Node *node)
{
    if (m_head1)
        m_head1->m_prev = node;
    Rva00432F23Node *head = m_head1;
    node->m_prev = 0;
    node->m_next = head;
    m_head1 = node;
    if (!m_tail1)
        m_tail1 = node;
    ++m_count;
}

void Rva00432F23::rva00432EC0(Rva00432F23Node *node)
{
    if (m_head2 == node)
        return;
    if (m_tail2 == node)
        return;
    if (m_head1 == node)
        m_head1 = node->m_next;
    if (m_tail1 == node)
        m_tail1 = node->m_prev;
    if (node->m_next)
        node->m_next->m_prev = node->m_prev;
    if (node->m_prev)
        node->m_prev->m_next = node->m_next;
    if (m_head2)
        m_head2->m_prev = node;
    node->m_next = m_head2;
    m_head2 = node;
    node->m_prev = 0;
    if (!m_tail2)
        m_tail2 = node;
}
void Rva00432F23::rva00432E5D(Rva00432F23Node *node)
{
    if (m_head1 == node)
        return;
    if (m_tail1 == node)
        return;
    if (m_head2 == node)
        m_head2 = node->m_next;
    if (m_tail2 == node)
        m_tail2 = node->m_prev;
    if (node->m_next)
        node->m_next->m_prev = node->m_prev;
    if (node->m_prev)
        node->m_prev->m_next = node->m_next;
    if (m_head1)
        m_head1->m_prev = node;
    node->m_next = m_head1;
    m_head1 = node;
    node->m_prev = 0;
    if (!m_tail1)
        m_tail1 = node;
}
