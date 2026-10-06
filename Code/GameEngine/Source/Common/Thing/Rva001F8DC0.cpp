// cl: /MD /EHsc
// ?rva001F8DC0@Rva001F8DC0@@QAEXH@Z @0x001F8DC0 34B.
// Null-checked virtual slot 3 at +0 with int arg, then rowed Rva001F5D4F::rva001F5D4F on this+12.
// Chain from 0x001F5D4F (same shape, member at +4 there); caller at 0x001F941B.
// Honest Rva names.
class Rva001F5D4F {
public:
    void rva001F5D4F(int);
};
class Helper001F8DC0 {
public:
    virtual ~Helper001F8DC0();
    virtual void pad1();
    virtual void pad2();
    virtual void slot3(int);
};
class Rva001F8DC0 {
public:
    void rva001F8DC0(int x);
private:
    Helper001F8DC0* m_ptr;
    char m_pad[8];
    Rva001F5D4F m_next;
};
void Rva001F8DC0::rva001F8DC0(int x)
{
    Helper001F8DC0* p = m_ptr;
    if (p)
        p->slot3(x);
    m_next.rva001F5D4F(x);
}
