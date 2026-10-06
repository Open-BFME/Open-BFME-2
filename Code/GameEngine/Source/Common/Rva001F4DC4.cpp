// cl: /MD
// ?rva001F4DC4@Rva001F4DC4@@QAEMXZ @0x001F4DC4 34B.
// Float getter reads holder at +0x9c via eighth virtual slot plus 0x20 with 0.0f else via xorps.
// Callers at 0x0004D20C and 0x0055C646 prove thiscall float void. Prev STLport put_num and next 0x001F4E1B.
// Honest Rva names. /arch:SSE for xorps movss fld zero plus EBP frame with if-else local shape.
struct Rva001F4DC4Helper {
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
    virtual void f4();
    virtual void f5();
    virtual void f6();
    virtual void f7();
    virtual float f8();
};
class Rva001F4DC4 {
public:
    char m_pad[0x9c];
    Rva001F4DC4Helper *m_ptr;
    float rva001F4DC4();
};
float Rva001F4DC4::rva001F4DC4()
{
    Rva001F4DC4Helper *p = m_ptr;
    float v;
    if (p)
        v = p->f8();
    else
        v = 0.0f;
    return v;
}
