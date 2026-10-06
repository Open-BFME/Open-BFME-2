// cl: /MD
// ?rva001F4DF9@Rva001F4DF9@@QAEMXZ @0x001F4DF9 34B.
// Float getter reads holder at +0x98 via sixth virtual slot plus 0x14 with 0.0f else via xorps.
// Sibling of 0x001F4DC4 plus 0x9c via slot 0x20 same flags and same 7-caller family.
// Honest Rva names. /arch:SSE for xorps movss fld zero plus EBP frame with if-else local shape.
struct Rva001F4DF9Helper {
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
    virtual void f4();
    virtual float f5();
};
class Rva001F4DF9 {
public:
    char m_pad[0x98];
    Rva001F4DF9Helper *m_ptr;
    float rva001F4DF9();
};
float Rva001F4DF9::rva001F4DF9()
{
    Rva001F4DF9Helper *p = m_ptr;
    float v;
    if (p)
        v = p->f5();
    else
        v = 0.0f;
    return v;
}
