// cl: /MD
// ?rva000F074E@Rva000F26DC@@QAEXHH@Z 0x000F074E 117B single-entry free matching
// dtor 0x000F26DC loop: releases VB at +0x300, IB at +0x580, calls Rva000EFC45
// dtor at +0x80; caller 0x000F2FFA. The index expression `b + a * 0xA0` must stay
// inline in every subscript: a named `idx` local makes MSVC emit add+mov instead
// of retail's `mov ecx,[b]; imul eax,eax,0xA0; lea esi,[eax+ecx]` (one byte short).

class Rva000EFC45 {
public:
    virtual ~Rva000EFC45();
};
class W3DBufferManager {
public:
    struct W3DVertexBufferSlot;
    struct W3DIndexBufferSlot;
    void releaseSlot(W3DVertexBufferSlot *slot);
    void releaseSlot(W3DIndexBufferSlot *slot);
};
extern class W3DBufferManager *TheW3DBufferManager;
class Rva000F26DC {
public:
    void rva000F074E(int a, int b);
private:
    char _pad0[0x80];
    Rva000EFC45 *m_a[160];
    W3DBufferManager::W3DVertexBufferSlot *m_b[160];
    W3DBufferManager::W3DIndexBufferSlot *m_c[160];
};
void Rva000F26DC::rva000F074E(int a, int b)
{
    if (a < 0 || a >= 1)
        return;
    Rva000EFC45 *p = m_a[b + a * 0xA0];
    if (p == 0)
        return;
    W3DBufferManager::W3DVertexBufferSlot *vb = m_b[b + a * 0xA0];
    if (vb != 0) {
        TheW3DBufferManager->releaseSlot(vb);
        m_b[b + a * 0xA0] = 0;
    }
    W3DBufferManager::W3DIndexBufferSlot *ib = m_c[b + a * 0xA0];
    if (ib != 0) {
        TheW3DBufferManager->releaseSlot(ib);
        m_c[b + a * 0xA0] = 0;
    }
    p->Rva000EFC45::~Rva000EFC45();
}
