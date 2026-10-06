// cl: /MD /EHsc
// ?rva001F5D38@Rva001F5D38@@QAEXXZ @0x001F5D38 23B.
// Null-checked virtual slot +4 at +0 then tail-jmp to rowed Rva001F429A::call on this+4.
// Caller jmp from 0x001F64E4. Honest Rva names.
struct Rva001F429A {
    void call();
};
class Helper001F5D38 {
public:
    virtual ~Helper001F5D38();
    virtual void tick();
};
class Rva001F5D38 {
public:
    void rva001F5D38();
private:
    Helper001F5D38* m_ptr;
    Rva001F429A m_next;
};
void Rva001F5D38::rva001F5D38()
{
    Helper001F5D38* p = m_ptr;
    if (p)
        p->tick();
    m_next.call();
}
