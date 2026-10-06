// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
//
// ?invoke@Rva00222947Ref@@QAEXHHH@Z, retail 0x00222947, 52 bytes. Null-guard
// functor dispatch in the FunctorNotSet family (sibling of 0x001531F2 49B two-int
// and 0x002229B2 49B passthrough): frame holds 0x0C-byte exception slot
// default-constructed via rowed ??0FunctorNotSet@@QAE@XZ with shared 0xD0B644
// throw info; live path forwards three int args to virtual slot 1
// (push 0x10 push 0x0C push 0x08 call dword [eax+4] ret 0x0C). Callers at
// 0x00223E40 0x00223F3F 0x00411FF6 pass dwords with holder at find result +8.
// Class and method names address-derived; FunctorNotSet is the proven throw type.
class FunctorNotSet
{
public:
    FunctorNotSet();
    virtual ~FunctorNotSet();
private:
    char m_pad[0x0C - 4];
};
class Rva00222947Op
{
public:
    virtual ~Rva00222947Op();
    virtual void invoke(int a, int b, int c);
};
class Rva00222947Ref
{
public:
    void invoke(int a, int b, int c);
private:
    Rva00222947Op *m_op;
};
void Rva00222947Ref::invoke(int a, int b, int c)
{
    Rva00222947Op *op = m_op;
    if (op == 0) {
        throw FunctorNotSet();
    }
    op->invoke(a, b, c);
}
