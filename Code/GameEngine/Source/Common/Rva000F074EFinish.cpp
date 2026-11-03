// cl: /MD
// ?rva000F074E@Rva000F26DC@@QAEXHH@Z 0x000F074E 117B single-entry free matching
// dtor 0x000F26DC loop: releases VB at +0x300, IB at +0x580, calls Rva000EFC45
// dtor at +0x80; caller 0x000F2FFA. The index expression `b + a * 0xA0` must stay
// inline in every subscript: a named `idx` local makes MSVC emit add+mov instead
// of retail's `mov ecx,[b]; imul eax,eax,0xA0; lea esi,[eax+ecx]` (one byte short).

// The +0x80 entries' dtor 0x000EFC45 is rowed as Geometry::~Geometry; the
// call below is a direct one.
class Geometry {
public:
    ~Geometry();
};
#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/W3DBufferManagerClass.h"
extern class W3DBufferManager *TheW3DBufferManager;
class Rva000F26DC {
public:
    void rva000F074E(int a, int b);
private:
    char _pad0[0x80];
    Geometry *m_a[160];
    W3DBufferManager::W3DVertexBufferSlot *m_b[160];
    W3DBufferManager::W3DIndexBufferSlot *m_c[160];
};
void Rva000F26DC::rva000F074E(int a, int b)
{
    if (a < 0 || a >= 1)
        return;
    Geometry *geometry = m_a[b + a * 0xA0];
    if (geometry == 0)
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
    geometry->Geometry::~Geometry();
}
