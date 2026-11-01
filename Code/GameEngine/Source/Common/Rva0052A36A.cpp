// cl: /MD
// ?rva0052A36A@Rva0052A36A@@QAEXPAUOut0052A36A@@@Z @0x0052A36A 29B leaf: array element fetch (base+((idx+4)*20)), float@+8 int@+12 to out; caller 0x0052A628
struct Elem0052A36A {
    void *m_ptr0;
    char m_pad0[4];
    float m_f;
    int m_i;
    char m_pad1[4];
};
struct Out0052A36A {
    float m_f;
    int m_i;
};
class GameWindow;
#include "../../Include/GameClient/ControlBar.h"
extern ControlBar *TheControlBar;

class Rva0052A36A {
public:
    void rva0052A36A(Out0052A36A *out);
    void rva0052A387(int unused);
private:
    void *m_base;
    int m_index;
};
void Rva0052A36A::rva0052A36A(Out0052A36A *out)
{
    char *base = (char *)m_base;
    int off = (m_index + 4) * 20;
    Elem0052A36A *e = (Elem0052A36A *)(base + off);
    int tmpi = e->m_i;
    float tmpf = e->m_f;
    out->m_f = tmpf;
    out->m_i = tmpi;
}

// ?rva0052A387@Rva0052A36A@@QAEXH@Z @0x0052A387 (35B)
void Rva0052A36A::rva0052A387(int)
{
    char *base = (char *)m_base;
    int off = (m_index + 4) * 20;
    void *val = ((Elem0052A36A *)(base + off))->m_ptr0;
    if (val)
        TheControlBar->rva004C1B60(0, val);
}
