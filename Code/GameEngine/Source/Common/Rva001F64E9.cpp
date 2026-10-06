// cl: /MD /EHsc
// ?rva001F64E9@Rva001F64E9@@QAEXH@Z 0x001F64E9 34B
// Evidence: leaf via rowed 0x001F5D4F; null-checked virtual slot 3 at +0 with int arg then rowed Rva001F5D4F on this+4. Caller at 0x001F826D. Honest Rva names.
struct Rva001F5D4F {
    void rva001F5D4F(int);
};
class Helper001F64E9 {
public:
    virtual ~Helper001F64E9();
    virtual void pad1();
    virtual void pad2();
    virtual void slot3(int);
};
class Rva001F64E9 {
public:
    void rva001F64E9(int x);
private:
    Helper001F64E9* m_ptr;
    Rva001F5D4F m_next;
};
void Rva001F64E9::rva001F64E9(int x)
{
    Helper001F64E9* p = m_ptr;
    if (p)
        p->slot3(x);
    m_next.rva001F5D4F(x);
}
