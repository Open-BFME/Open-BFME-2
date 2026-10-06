// cl: /MD
// ?rva001F4D4F@Rva001F4D4F@@QAEMXZ @0x001F4D4F 39B.
// Float getter reads holder at +0x9c via sixth virtual slot plus 0x14 with 1.0f else.
// Same holder offset as sibling Rva001F4D76; default 1.0f float literal.
struct Rva001F4D4FHelper {
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
    virtual void f4();
    virtual float f5();
};
class Rva001F4D4F {
public:
    char m_pad[0x9c];
    Rva001F4D4FHelper *m_ptr;
    float rva001F4D4F();
};
float Rva001F4D4F::rva001F4D4F()
{
    Rva001F4D4FHelper *p = m_ptr;
    float v;
    if (p != 0)
        v = p->f5();
    else
        v = 1.0f;
    return v;
}
