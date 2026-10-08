// cl: /Ireference/shims/bfme2_ascii /MD
#include "ascii_string.h"

// ?rva005C3ACD@Rva005C3ACD@@QAEXXZ @0x005C3ACD 113B
// Hide counterpart to Show 0x005C3EA5: if flag +0x18 set, AptCall Hide via
// rowed 0x00524EF4 with empty fallback g_Rva0107301CEmptyString and manager
// TheRva00222A8BTarget, clears 12B array at +0x20 while count +0x1c > 0,
// clears flags +0x44/+0x18, tail-calls slot 2 of member at +0.
// Evidence: retail cmp [esi+0x18] early ret, AptCall args, imul 12 loop,
// jmp [eax+8]; caller jmp at 0x005C3E7C via +4.
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
int __cdecl Rva00524EF4AptCall(Rva00222A8BTarget *t, void *a1, const char *a2, const char *a3);

class Rva002BED91
{
public:
    void clear();
private:
    void *m_ptr; // +0 holder makes Elem stride 12 like retail imul 12
};

class Rva000AD6F4
{
public:
    void clear();
private:
    void *m_ptr; // +0 holder makes Elem stride 12
};

class Inner005C3ACD
{
public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
};

struct Elem005C3ACD
{
    Rva002BED91 a00;
    Rva000AD6F4 b04;
    Rva002BED91 c08;
};

class Rva005C3ACD
{
public:
    void rva005C3ACD();
private:
    Inner005C3ACD *m_obj00;
    void *m_p04;
    AsciiString m_s08;
    char m_pad0C[0x18 - 0x0C];
    unsigned char m_flag18;
    char m_pad19[3];
    int m_count1C;
    Elem005C3ACD m_arr20[3];
    unsigned char m_flag44;
};

void Rva005C3ACD::rva005C3ACD()
{
    if (!m_flag18)
        return;
    char *t = *(char **)(void *)&m_s08;
    const char *s = t ? t + 8 : "";
    Rva00524EF4AptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_p04, s, "Hide");
    do
    {
        --m_count1C;
        Elem005C3ACD &e = m_arr20[m_count1C];
        e.c08.clear();
        e.b04.clear();
        e.a00.clear();
    } while (m_count1C > 0);
    m_flag44 = 0;
    m_flag18 = 0;
    m_obj00->f2();
}

// ?rva005C3E79@Rva005C3E79@@QAEXXZ @0x005C3E79 8B
// Ptr-chase tail-jmp to rowed ?rva005C3ACD@Rva005C3ACD@@QAEXXZ at 0x005C3ACD:
// retail mov ecx,[ecx+4]; jmp 0x005C3ACD. Holder keeps target pointer at +4.
// Evidence: callers at 0x005D2692 and 0x0056825C call with this in ecx no args.
class Rva005C3E79
{
public:
    void rva005C3E79();
private:
    char m_pad00[4];
    Rva005C3ACD *m_p04;
};

void Rva005C3E79::rva005C3E79()
{
    m_p04->rva005C3ACD();
}
