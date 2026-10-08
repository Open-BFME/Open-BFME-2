// cl: /MD
// ?rva002EB46E@Rva002EB46E@@QAEXPAU_Rva002EB46ENode@@@Z, retail 0x002EB46E, 50 bytes.
// Recursive free-list release: depth-first via +0xC, chain via +0x8, push onto head at 0x00DBD4D0.
// Evidence: twin of 0x002EB416 differing only by pool head; self-call with [esi+0xC]; ret 4 one-arg thiscall; unblocks 0x002EEA1D.
struct _Rva002EB46ENode {
    void *_m_link;
    int _m_unk4;
    _Rva002EB46ENode *_m_next;
    _Rva002EB46ENode *_m_child;
};
#include "../../../../GameEngine/Include/Common/Rva002E8548Pool.h"
struct Rva002EB46E {
    void rva002EB46E(_Rva002EB46ENode *p);
};
void Rva002EB46E::rva002EB46E(_Rva002EB46ENode *p)
{
    if (!p)
        return;
    do {
        rva002EB46E(p->_m_child);
        _Rva002EB46ENode *next = p->_m_next;
        p->_m_link = g_Va00DBD4C8.m_head;
        g_Va00DBD4C8.m_head = p;
        p = next;
    } while (p);
}
