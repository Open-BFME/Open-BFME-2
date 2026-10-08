// cl: /Ireference/shims/bfme2_ascii /MD
#include "ascii_string.h"

// ?rva005C3EA5@Rva005C3EA5@@QAEXXZ @ 0x005C3EA5 59B.
// Gap between 0x005C3E89 and 0x005C3EE8 in OpaqueScalarDeletingDtors.cpp.
// Fires Show via rowed Fire 0x0052519D with target plus Show, empty fallback
// g_Rva0107301CEmptyString, manager TheRva00222A8BTarget, sets +0x18 to 1,
// tail-calls slot 1 of member at +0. Caller jmp at 0x005C3EE3.
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
int __cdecl Rva0052519DFire(void *a1, void *a2, const char *a3, const char *a4, int *a5);

class Inner005C3EA5
{
public:
    virtual void f0();
    virtual void tail();
};

class Rva005C3EA5
{
public:
    void rva005C3EA5();
private:
    Inner005C3EA5 *m_obj00;
    void *m_p04;
    AsciiString m_s08;
    char m_pad0C[0x18 - 0x0C];
    unsigned char m_flag18;
    char m_pad19[3];
    int m_i1C;
};

void Rva005C3EA5::rva005C3EA5()
{
    char *t = *(char **)(void *)&m_s08;
    const char *s = t ? t + 8 : "";
    Rva0052519DFire((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_p04, s, "Show", &m_i1C);
    m_flag18 = 1;
    m_obj00->tail();
}

// ?rva005C3EE0@Rva005C3EE0@@QAEXXZ @ 0x005C3EE0 8B.
// Forwarder via member at +4 tail-jmp to rowed 0x005C3EA5. Caller call at 0x005680C3.
class Rva005C3EE0
{
public:
    void rva005C3EE0();
private:
    char m_pad00[4];
    Rva005C3EA5 *m_p04;
};

void Rva005C3EE0::rva005C3EE0()
{
    m_p04->rva005C3EA5();
}
