// cl: /O1 /MD
// 8B add ecx N / jmp forwarders into a member call at +N. Jump targets that are
// unrowed arrive as address-derived pins with the arity their ret proves:
// 0x0050174A -> 0x005016C3 (ret 0); 0x002A9ECA -> +8 0x00380459 (ret 4);
// 0x003EE7C2 -> +8 0x004E37CF (ret 8).
// ?rva002A0D11@Rva002A0D11@@QAEXXZ @0x002A0D11 -> rowed
// ?rva00239AF4@Rva00239AF4@@QAEXXZ at 0x00239AF4 (row spelling followed).
// Original names unknown so address-derived Rva names are used.

class Rva00239AF4
{
public:
    void rva00239AF4();
};
class Rva002A0D11
{
public:
    void rva002A0D11();
private:
    int m_00;
    Rva00239AF4 m_04;
};
void Rva002A0D11::rva002A0D11()
{
    m_04.rva00239AF4();
}

class Rva005016C3
{
public:
    void rva005016C3();
};
class Rva0050174A
{
public:
    void rva0050174A();
private:
    int m_00;
    Rva005016C3 m_04;
};
void Rva0050174A::rva0050174A()
{
    m_04.rva005016C3();
}
class Rva00380459
{
public:
    void rva00380459(int a);
};
class Rva002A9ECA
{
public:
    void rva002A9ECA(int a);
private:
    int m_00;
    int m_04;
    Rva00380459 m_08;
};
void Rva002A9ECA::rva002A9ECA(int a)
{
    m_08.rva00380459(a);
}
class Rva004E37CF
{
public:
    void rva004E37CF(int a, int b);
};
class Rva003EE7C2
{
public:
    void rva003EE7C2(int a, int b);
private:
    int m_00;
    int m_04;
    Rva004E37CF m_08;
};
void Rva003EE7C2::rva003EE7C2(int a, int b)
{
    m_08.rva004E37CF(a, b);
}
