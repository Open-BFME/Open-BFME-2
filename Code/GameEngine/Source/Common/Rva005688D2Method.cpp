// cl: /O1 /G7 /arch:SSE
// ?rva005688D2@Rva005688D2@@QAEXPAMH@Z @0x005688D2 78B: two-float out at [esp+4] gated by mode at [esp+8]; base float at [ecx+0x3C]+0x10 scaled by g_00BC6C50; callers 0x005689C3 0x00569B03; same +0x2C/+0x3C layout as Rva00568920/Rva005686C1
//
// ?rva00568991@Rva005688D2@@QAEHXZ @0x00568991 116B: slot-weighted sum.
// Over the four +0x2C slots: non-null slots contribute the rowed 0x005C83C0
// get(); null slots run rva005688D2(tmp, i) then the pinned 0x005C80D1
// five-arg helper on (base+0xE8, tmp, scale, &a, &b) and add a*b. The
// scale fld sits before the rva005688D2 call, which MSVC only keeps in
// ST(0) across the call for a same-TU (visible) callee.
extern float g_00BC6C50;

void rva005C80D1(void *p, float *tmp, float scale, int *a, int *b);

struct Rva005688D2Base
{
    char m_pad[0x10];
    float m_scale;
};

class Rva005C83C0DivAvgField
{
public:
    int get() const;
};

class Rva005688D2
{
public:
    void rva005688D2(float *out, int mode);
    int rva00568991();
private:
    char m_pad[0x2C];
    Rva005C83C0DivAvgField *m_slots[4];
    Rva005688D2Base *m_base;
};

void Rva005688D2::rva005688D2(float *out, int mode)
{
    float first;
    float second;
    if (mode == 0 || mode == 2)
        first = 0.0f;
    else
        first = m_base->m_scale * g_00BC6C50;
    if (mode == 0 || mode == 1)
        second = 0.0f;
    else
        second = m_base->m_scale * g_00BC6C50;
    out[0] = first;
    out[1] = second;
}

int Rva005688D2::rva00568991()
{
    int sum = 0;
    int i = 0;
    for (Rva005C83C0DivAvgField **slot = m_slots; i < 4; ++i, ++slot) {
        Rva005C83C0DivAvgField *s = *slot;
        if (s != 0) {
            sum += s->get();
        }
        else {
            float scale = m_base->m_scale;
            float tmp[2];
            rva005688D2(tmp, i);
            int a;
            int b;
            rva005C80D1((char *)m_base + 0xE8, tmp, scale, &a, &b);
            sum += a * b;
        }
    }
    return sum;
}
