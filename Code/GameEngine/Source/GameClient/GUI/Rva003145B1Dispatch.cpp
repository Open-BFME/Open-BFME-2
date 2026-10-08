// cl: /Oy- /DNDEBUG /MD
// ?Rva003145B1Dispatch@Rva003145B1@@QAEHHHH@Z @ 0x003145B1 (63B).
// Honest address-derived dispatch: if plus 0x04 then slot 4 with three args else slot 2 with three args then if first arg is 2 call own slot 2.
// Evidence: neighbors 0x00314581 plus 0x003145F0 plus twin 0x00314596 sharing plus 0x04 plus 0x08 layout.
class TargetA
{
public:
    virtual void a0();
    virtual void a1();
    virtual void a2();
    virtual int a3(int x, int y, int z);
    virtual int a4(int x, int y, int z);
};
class TargetB
{
public:
    virtual void b0();
    virtual int b1(int x, int y, int z);
    virtual int b2(int x, int y, int z);
};
class Rva003145B1
{
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    int Rva003145B1Dispatch(int a0, int a1, int a2);
    int rva00314596(int a0, int a1, int a2);
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

// ?rva00314596@Rva003145B1@@QAEHHHH@Z @ 0x00314596 (27B): the twin of
// GameWindow::winSendInputMsg (0x00314511) on this layout -- the +0x04 handler's
// slot 3, else the +0x08 object's slot 1, both reached by tail jumps with the
// caller's three arguments still on the stack; /Oy- keeps retail's frame.
int Rva003145B1::rva00314596(int a0, int a1, int a2)
{
    if (m_04)
        return m_04->a3(a0, a1, a2);
    return m_08->b1(a0, a1, a2);
}
