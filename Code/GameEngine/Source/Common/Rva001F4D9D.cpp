// cl: /MD
// ?rva001F4D9D@Rva001F4D9D@@QAEMXZ @0x001F4D9D 39B.
// Float getter reads holder at +0x9c via eighth virtual slot plus 0x1c with 1.0f else.
// Same holder offset as siblings Rva001F4D76 and Rva001F4DC4; default 1.0f float literal.
// Caller at 0x00562E9C proves thiscall float void. Honest Rva name.
struct Rva001F4D9DHelper {
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
    virtual void f4();
    virtual void f5();
    virtual void f6();
    virtual float f7();
};
class Rva001F4D9D {
public:
    char m_pad[0x9c];
    Rva001F4D9DHelper *m_ptr;
    float rva001F4D9D();
};
float Rva001F4D9D::rva001F4D9D()
{
    Rva001F4D9DHelper *p = m_ptr;
    float v;
    if (p != 0)
        v = p->f7();
    else
        v = 1.0f;
    return v;
}
