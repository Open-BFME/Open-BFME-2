// cl: /MD
// ?rva002EB416@Rva002EB416@@QAEXPAU_Rva002EB416Node@@@Z, retail 0x002EB416, 50 bytes.
// Recursive free-list release: depth-first via +0xC, chain via +0x8, push onto head at 0x00DBD4B8.
// Evidence: self-call with [esi+0xC]; caller 0x002EE9E0 passes [eax+4]; ret 4 one-arg thiscall; unblocks 0x002EE9E0.
struct _Rva002EB416Node {
    void *_m_link;
    int _m_unk4;
    _Rva002EB416Node *_m_next;
    _Rva002EB416Node *_m_child;
};
extern _Rva002EB416Node *g_Va00DBD4B8;
struct Rva002EB416 {
    void rva002EB416(_Rva002EB416Node *p);
};
void Rva002EB416::rva002EB416(_Rva002EB416Node *p)
{
    if (!p)
        return;
    do {
        rva002EB416(p->_m_child);
        _Rva002EB416Node *next = p->_m_next;
        p->_m_link = g_Va00DBD4B8;
        g_Va00DBD4B8 = p;
        p = next;
    } while (p);
}
