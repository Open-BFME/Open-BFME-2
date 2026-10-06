// cl: /MD
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

// 0x003EE7C2 follows its existing pin spelling (the SplineEffectParseINIBlock
// caller at 0x004E3F48 reaches it as Rva003BB730Owner::addEffect).
class AsciiString;
class Rva003BB730Record;
class Rva004E37CF
{
public:
    void rva004E37CF(AsciiString &name, Rva003BB730Record *record);
};
class Rva003BB730Owner
{
public:
    void addEffect(AsciiString &name, Rva003BB730Record *record);
private:
    int m_00;
    int m_04;
    Rva004E37CF m_08;
};
void Rva003BB730Owner::addEffect(AsciiString &name, Rva003BB730Record *record)
{
    m_08.rva004E37CF(name, record);
}
