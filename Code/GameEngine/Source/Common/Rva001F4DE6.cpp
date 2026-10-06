// cl: /MD
// ?rva001F4DE6@Rva001F4DE6@@QAEHXZ @0x001F4DE6 19B.
// Int getter reads holder at +0x9c via eleventh virtual slot plus 0x28 with 1 else.
// Same holder offset as float siblings Rva001F4D76 Rva001F4D9D; default 1 via inc.
// Callers at 0x00560548 and 0x00562F8B prove thiscall int void. Honest Rva name.
struct Rva001F4DE6Helper {
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
    virtual void f4();
    virtual void f5();
    virtual void f6();
    virtual void f7();
    virtual void f8();
    virtual void f9();
    virtual int f10();
};
class Rva001F4DE6 {
public:
    char m_pad[0x9c];
    Rva001F4DE6Helper *m_ptr;
    int rva001F4DE6();
};
int Rva001F4DE6::rva001F4DE6()
{
    Rva001F4DE6Helper *p = m_ptr;
    if (p != 0)
        return p->f10();
    return 1;
}
