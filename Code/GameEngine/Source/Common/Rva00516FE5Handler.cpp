// cl: /O1 /MD
// ?rva00516FE5@Rva00516FE5@@QAEHHII@Z at 0x00516FE5 size 66
// Evidence: vtable slot 2 neighbours GameWindow draw; calls pinned base _bfme_AptGameWindow 0x0051274F then child virtual +0x14 over +0x280 array.

class _bfme_AptGameWindow
{
public:
    int rva0051274F(int a, unsigned b, unsigned c);
};

class Rva00516FE5;

class Rva00516FE5Child
{
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual int handler(Rva00516FE5 *parent, int a, unsigned b, unsigned c);
};

class Rva00516FE5
{
public:
    int rva00516FE5(int a, unsigned b, unsigned c);
private:
    char m_pad[0x280];
    Rva00516FE5Child **m_begin;
    Rva00516FE5Child **m_end;
};

int Rva00516FE5::rva00516FE5(int a, unsigned b, unsigned c)
{
    ((_bfme_AptGameWindow *)this)->rva0051274F(a, b, c);
    for (Rva00516FE5Child **p = m_begin; p != m_end; ++p)
        (*p)->handler(this, a, b, c);
    return 1;
}
