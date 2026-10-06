// cl: /MD
// ?rva001F4D76@Rva001F4D76@@QAEMXZ @0x001F4D76 39B.
// Float getter reads holder at +0x9c via seventh virtual slot plus 0x18 with 1.0f else.
// Same holder offset as siblings Rva001F4DC4 and Rva001F4D4F; default 1.0f float literal.
// Caller at 0x00562E92 proves thiscall float void. Honest Rva name.
struct Rva001F4D76Helper {
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
    virtual void f4();
    virtual void f5();
    virtual float f6();
};
class Rva001F4D76 {
public:
    char m_pad[0x9c];
    Rva001F4D76Helper *m_ptr;
    float rva001F4D76();
};
float Rva001F4D76::rva001F4D76()
{
    Rva001F4D76Helper *p = m_ptr;
    float v;
    if (p != 0)
        v = p->f6();
    else
        v = 1.0f;
    return v;
}
