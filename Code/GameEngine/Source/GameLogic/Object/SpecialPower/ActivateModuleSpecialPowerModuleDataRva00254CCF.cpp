// cl: /DNDEBUG /MD
//
// ?Rva00254CCF@ActivateModuleSpecialPowerModuleData@@UAEXPAVRva00254CCFArg@@@Z retail 0x00254CCF 60 bytes.
// Vslot 34 offset 0x88 of vtable 0x7F3F60 owned by ActivateModuleSpecialPowerModuleData ctor 0x256DA1.
// Body takes arg object plus loops vector at +0x10/+0x14: 2-bool 1/1 local via virtual slot 10
// plus 0x28 on arg then per-element virtual slot 12 plus 0x30. No callers. No donor.
// Slot not mapped to real crc/xfer name per reverse-overload rule so honest Rva name.
// Flags copy neighbour ActivateModuleSpecialPowerModuleDataCtor first line.

class Rva00254CCFArg
{
public:
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10(void *p);
    virtual void v11();
    virtual void v12(int v);
};

struct TwoBools
{
    bool a;
    bool b;
};

class ActivateModuleSpecialPowerModuleData
{
public:
    virtual void Rva00254CCF(Rva00254CCFArg *arg);

private:
    char m_pad00[0x0C];
    int *m_begin10;
    int *m_end14;
};

void ActivateModuleSpecialPowerModuleData::Rva00254CCF(Rva00254CCFArg *arg)
{
    TwoBools t;
    t.a = true;
    t.b = true;
    arg->v10(&t);
    for (int *p = m_begin10; p != m_end14; ++p) {
        arg->v12(*p);
    }
}
