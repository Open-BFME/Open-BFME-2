// cl: /MD
// ?rva002EE9E0@Rva002EB416@@QAEXXZ, retail 0x002EE9E0, 41 bytes.
// Pool-block reset: releases list at +4 via 0x002EB416 then self-links +8/+12 and clears flags.
// Evidence: calls rowed 0x002EB416 with [eax+4]; and [eax+4]/[esi+4] zeroing; caller 0x002F0B8A EH prolog; unblocks 0x002F0B8A.
struct _Rva002EB416Node {
    void *_m_link;
    _Rva002EB416Node *_m_list;
    _Rva002EB416Node *_m_next;
    _Rva002EB416Node *_m_child;
};
// g_Va00DBD4B8: VA 0x00dbd4b8 (.data); retail initial bytes 00 00 00 00.
_Rva002EB416Node *g_Va00DBD4B8;
struct Rva002EB416 {
    _Rva002EB416Node *m_head;
    int m_flag;
    void rva002EB416(_Rva002EB416Node *p);
    void rva002EE9E0();
    void rva002EEA09();
};
void Rva002EB416::rva002EE9E0()
{
    if (m_flag == 0)
        return;
    rva002EB416(m_head->_m_list);
    m_head->_m_next = m_head;
    m_head->_m_list = 0;
    m_head->_m_child = m_head;
    m_flag = 0;
}
void Rva002EB416::rva002EEA09()
{
    _Rva002EB416Node *head = m_head;
    if (!head)
        return;
    head->_m_link = g_Va00DBD4B8;
    g_Va00DBD4B8 = head;
}
