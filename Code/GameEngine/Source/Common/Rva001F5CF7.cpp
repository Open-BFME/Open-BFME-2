// cl: /MD /EHsc
// ?rva001F5CF7@Rva001F5CF7@@QAEXXZ @0x001F5CF7 23B.
// Null-checked virtual slot +4 at +0 then tail-jmp to rowed Rva001F425C::call on this+4.
// Callers jmp from 0x001F6488 0x001F8206 0x001F8953 0x001F8DBB. Honest Rva names.
struct Rva001F425C {
    void call();
};
class Helper001F5CF7 {
public:
    virtual ~Helper001F5CF7();
    virtual void tick();
};
class Rva001F5CF7 {
public:
    void rva001F5CF7();
private:
    Helper001F5CF7* m_ptr;
    Rva001F425C m_next;
};
void Rva001F5CF7::rva001F5CF7()
{
    Helper001F5CF7* p = m_ptr;
    if (p)
        p->tick();
    m_next.call();
}
