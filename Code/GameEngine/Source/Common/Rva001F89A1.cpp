// cl: /MD /EHsc
// ?rva001F89A1@Rva001F89A1@@QAEXH@Z 0x001F89A1 34B
// Evidence: chain via rowed 0x001F8254; null-checked virtual slot 3 at +0 with int arg then rowed Rva001F8254 on this+4. Caller at 0x001F8E3C. Honest Rva names.
struct Rva001F8254 {
    void rva001F8254(int);
};
class Helper001F89A1 {
public:
    virtual ~Helper001F89A1();
    virtual void pad1();
    virtual void pad2();
    virtual void slot3(int);
};
class Rva001F89A1 {
public:
    void rva001F89A1(int x);
private:
    Helper001F89A1* m_ptr;
    Rva001F8254 m_next;
};
void Rva001F89A1::rva001F89A1(int x)
{
    Helper001F89A1* p = m_ptr;
    if (p)
        p->slot3(x);
    m_next.rva001F8254(x);
}
