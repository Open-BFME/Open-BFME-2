// cl: /MD /EHsc
// ?rva001F9402@Rva001F9402@@QAEXH@Z @0x001F9402 34B.
// Null-checked virtual slot 3 at +0 with int arg, then rowed Rva001F8DC0::rva001F8DC0 on this+4.
// Chain from 0x001F8DC0 (same shape, member at +12 there); caller at 0x001FA4BD.
// Honest Rva names.
class Rva001F8DC0 {
public:
    void rva001F8DC0(int);
};
class Helper001F9402 {
public:
    virtual ~Helper001F9402();
    virtual void pad1();
    virtual void pad2();
    virtual void slot3(int);
};
class Rva001F9402 {
public:
    void rva001F9402(int x);
private:
    Helper001F9402* m_ptr;
    Rva001F8DC0 m_next;
};
void Rva001F9402::rva001F9402(int x)
{
    Helper001F9402* p = m_ptr;
    if (p)
        p->slot3(x);
    m_next.rva001F8DC0(x);
}
