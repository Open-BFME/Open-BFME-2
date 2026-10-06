// cl: /MD
// ?rva002EADB4@Rva002EADB4@@QAEXPAU_Rva002EADB4Node@@@Z retail 0x002EADB4 45 bytes.
// Recursive release depth-first via +0xC chain via +0x8 free via rowed 0x00030830.
// Evidence: self-call with [esi+0xC] plus caller 0x002EE9B7 passes [eax+0x4] plus sibling Rva002EB416Release shape.
extern "C" void __cdecl free(void *);

struct _Rva002EADB4Node {
    void *_m_link;
    int _m_unk4;
    _Rva002EADB4Node *_m_next;
    _Rva002EADB4Node *_m_child;
};

struct Rva002EADB4 {
    void rva002EADB4(_Rva002EADB4Node *p);
};

void Rva002EADB4::rva002EADB4(_Rva002EADB4Node *p)
{
    if (!p)
        return;
    do {
        rva002EADB4(p->_m_child);
        _Rva002EADB4Node *next = p->_m_next;
        free(p);
        p = next;
    } while (p);
}
