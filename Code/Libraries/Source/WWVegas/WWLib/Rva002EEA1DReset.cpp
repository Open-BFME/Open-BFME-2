// cl: /MD
// ?rva002EEA1D@Rva002EB46E@@QAEXXZ, retail 0x002EEA1D, 41 bytes.
// Pool-block reset twin: releases list at +4 via 0x002EB46E then self-links +8/+12 and clears flags.
// Evidence: twin of 0x002EE9E0 differing only by callee; calls rowed 0x002EB46E; unblocks 0x002F0BB5.
struct _Rva002EB46ENode {
    void *_m_link;
    _Rva002EB46ENode *_m_list;
    _Rva002EB46ENode *_m_next;
    _Rva002EB46ENode *_m_child;
};
// Native DBD4D0 is the shared pool's free-node field at +8.
#include "../../../../GameEngine/Include/Common/Rva002E8548Pool.h"
struct Rva002EB46E {
    _Rva002EB46ENode *m_head;
    int m_flag;
    void rva002EB46E(_Rva002EB46ENode *p);
    void rva002EEA1D();
    void rva002EEA46();
};
void Rva002EB46E::rva002EEA1D()
{
    if (m_flag == 0)
        return;
    rva002EB46E(m_head->_m_list);
    m_head->_m_next = m_head;
    m_head->_m_list = 0;
    m_head->_m_child = m_head;
    m_flag = 0;
}
void Rva002EB46E::rva002EEA46()
{
    _Rva002EB46ENode *head = m_head;
    if (!head)
        return;
    head->_m_link = g_Va00DBD4C8.m_head;
    g_Va00DBD4C8.m_head = head;
}
