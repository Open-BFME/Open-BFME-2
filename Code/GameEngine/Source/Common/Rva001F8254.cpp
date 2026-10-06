// cl: /MD /EHsc
// ?rva001F8254@Rva001F8254@@QAEXH@Z 0x001F8254 34B
// Evidence: chain via rowed 0x001F64E9; null-checked virtual slot 3 at +0 with int arg then rowed Rva001F64E9 on this+4. Caller at 0x001F89BA. Honest Rva names.
struct Rva001F64E9 {
    void rva001F64E9(int);
};
class Helper001F8254 {
public:
    virtual ~Helper001F8254();
    virtual void pad1();
    virtual void pad2();
    virtual void slot3(int);
};
class Rva001F8254 {
public:
    void rva001F8254(int x);
private:
    Helper001F8254* m_ptr;
    Rva001F64E9 m_next;
};
void Rva001F8254::rva001F8254(int x)
{
    Helper001F8254* p = m_ptr;
    if (p)
        p->slot3(x);
    m_next.rva001F64E9(x);
}
