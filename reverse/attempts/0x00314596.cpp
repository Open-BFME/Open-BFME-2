// ?rva00314596@Rva003145B1@@QAEXXZ
// partial score=0.5 date=2026-10-08
// cl: /O1 /Oy- /DNDEBUG /MD
// ?Rva003145B1Dispatch@Rva003145B1@@QAEHHHH@Z @ 0x003145B1 (63B).
// Honest address-derived dispatch: if plus 0x04 then slot 4 with three args else slot 2 with three args then if first arg is 2 call own slot 2.
// Evidence: neighbors 0x00314581 plus 0x003145F0 plus twin 0x00314596 sharing plus 0x04 plus 0x08 layout.
class TargetA
{
public:
    virtual void a0();
    virtual void a1();
    virtual void a2();
    virtual int a3();
    virtual int a4(int x, int y, int z);
};
class TargetB
{
public:
    virtual void b0();
    virtual int b1();
    virtual int b2(int x, int y, int z);
};
class Rva003145B1
{
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    int Rva003145B1Dispatch(int a0, int a1, int a2);
    int rva00314596();
private:
    TargetA *m_04;
    TargetB *m_08;
};
int Rva003145B1::Rva003145B1Dispatch(int a0, int a1, int a2)
{
    int result;
    if (m_04)
        result = m_04->a4(a0, a1, a2);
    else
        result = m_08->b2(a0, a1, a2);
    if (a0 == 2)
        v2();
    return result;
}

// ?rva00314596@Rva003145B1@@QAEHXZ retail 0x00314596 27 bytes. Twin of the dispatch above:
// the same +0x04/+0x08 pair, no arguments; a non-null +0x04 target takes slot 3, else +0x08 takes slot 1.
// Retail tail-jumps to both, so the body is a single return of each virtual call.
int Rva003145B1::rva00314596()
{
    if (m_04)
        return m_04->a3();
    return m_08->b1();
}
