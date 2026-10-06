// cl: /MD /EHsc
// ?rva001F5D0E@Rva001F5D0E@@QAEXHH@Z @0x001F5D0E 42B
// Null-checked virtual slot 0xc at +0 with (int,int) then rowed Rva001F4276::call on this+4.
// Callees rowed: ?call@Rva001F4276@@QAEXHH@Z. Callers: jmp from 0x001F64B3. Honest Rva names.
struct Rva001F4276 {
    void call(int a, int b);
};
class Helper001F5D0E {
public:
    virtual ~Helper001F5D0E();
    virtual void m1();
    virtual void m2();
    virtual void m3(int a, int b);
};
class Rva001F5D0E {
public:
    void rva001F5D0E(int a, int b);
private:
    Helper001F5D0E *m_ptr;
    Rva001F4276 m_next;
};
void Rva001F5D0E::rva001F5D0E(int a, int b)
{
    Helper001F5D0E *p = m_ptr;
    if (p)
        p->m3(a, b);
    m_next.call(a, b);
}
