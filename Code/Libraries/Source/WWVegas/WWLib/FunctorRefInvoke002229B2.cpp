// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
//
// ?invoke@Rva002229B2Ref@@QAEPAXPAX@Z, retail 0x002229B2, 49 bytes. Null-guard
// functor dispatch in the FunctorNotSet family (sibling of 0x001531F2 49B two-int
// and 0x0057CC15 46B void versions): frame holds 0x0C-byte exception slot
// default-constructed via rowed ??0FunctorNotSet@@QAE@XZ with shared 0xD0B644
// throw info; live path forwards one pointer arg to virtual slot 1 then returns
// the same pointer (mov eax [ebp+8] ret 4). Caller 0x00223C77 passes result
// pointer through holder at find result +8. Class and method names
// address-derived; FunctorNotSet is the proven throw type; op layout ptr at +0
// proven by mov ecx [ecx].
class FunctorNotSet
{
public:
    FunctorNotSet();
    virtual ~FunctorNotSet();
private:
    char m_pad[0x0C - 4];
};
class Rva002229B2Op
{
public:
    virtual ~Rva002229B2Op();
    virtual void invoke(void *a);
};
class Rva002229B2Ref
{
public:
    void *invoke(void *a);
private:
    Rva002229B2Op *m_op;
};
void *Rva002229B2Ref::invoke(void *a)
{
    Rva002229B2Op *op = m_op;
    if (op == 0) {
        throw FunctorNotSet();
    }
    op->invoke(a);
    return a;
}
