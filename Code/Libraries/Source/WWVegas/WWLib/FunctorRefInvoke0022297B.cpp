// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
//
// ?invoke@Rva0022297BRef@@QAEXHHHH@Z, retail 0x0022297B, 55 bytes. Null-guard
// functor dispatch in the FunctorNotSet family (siblings 0x00222947 52B three-int
// and 0x002229B2 49B passthrough): frame holds 0x0C-byte exception slot
// default-constructed via rowed ??0FunctorNotSet@@QAE@XZ with shared 0xD0B644
// throw info; live path forwards four int args to virtual slot 1
// (push 0x14 push 0x10 push 0x0C push 0x08 call dword [eax+4] ret 0x10). Caller
// 0x00223D8D forwards holder+8 with four dwords. Class and method names
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
class Rva0022297BOp
{
public:
    virtual ~Rva0022297BOp();
    virtual void invoke(int a, int b, int c, int d);
};
class Rva0022297BRef
{
public:
    void invoke(int a, int b, int c, int d);
private:
    Rva0022297BOp *m_op;
};
void Rva0022297BRef::invoke(int a, int b, int c, int d)
{
    Rva0022297BOp *op = m_op;
    if (op == 0) {
        throw FunctorNotSet();
    }
    op->invoke(a, b, c, d);
}
