// ??0Rva003FC58C@@QAE@ABV?$StringBase@D@@@Z
// partial score=0.6374 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
// ??0Rva003FC58C@@QAE@ABV?$StringBase@D@@@Z @0x003FC58C 311B
// ModuleData ctor with StringBase at +4 many ints floats and pushback.
// Evidence: vtable 0x00837C30 StringBase copy 0x000365F0 rva002129A1 0x002129A1 callers 0x003FD154 etc.
template <typename T>
class StringBase
{
    friend class Rva003FC58C;
private:
    StringBase(const StringBase &that);
    void *m_data;
};

class ModuleData
{
public:
    virtual ~ModuleData();
};

class Rva002129A1
{
public:
    void rva002129A1(const ModuleData *data);
};

extern Rva002129A1 *g_009FE1C8;
extern "C" float INV;
extern float g_00BC28F8;
extern float g_00C37C2C;
extern float g_00BCCB3C;

class Rva003FC58C : public ModuleData
{
public:
    Rva003FC58C(const StringBase<char> &name);
private:
    StringBase<char> m_04;
    int m_08;
    int m_0C;
    int m_10;
    int m_14;
    int m_18;
    int m_1C;
    int m_20;
    int m_24;
    int m_28;
    int m_2C;
    int m_30;
    int m_34;
    int m_38;
    int m_3C;
    int m_40;
    int m_44;
    int m_48;
    int m_4C;
    int m_50;
    float m_54;
    unsigned char m_58;
    char m_pad59[3];
    float m_5C;
    float m_60;
    float m_64;
    float m_68;
    float m_6C;
    float m_70;
    float m_74;
    unsigned char m_78;
    char m_pad79[3];
    float m_7C;
    float m_80;
    float m_84;
    unsigned char m_88;
    char m_pad89[3];
    float m_8C;
    float m_90;
    float m_94;
    float m_98;
    float m_9C;
    float m_A0;
    float m_A4;
    float m_A8;
};
// ??0Rva003FC58C@@QAE@ABV?$StringBase@D@@@Z present-unmatched
Rva003FC58C::Rva003FC58C(const StringBase<char> &name) : m_04(name)
{
    register int izero = 0;
    m_08 = izero;
    m_0C = izero;
    m_10 = izero;
    m_14 = izero;
    m_18 = izero;
    m_1C = izero;
    m_24 = izero;
    m_20 = izero;
    float zero;
    float inv;
    float f2;
    zero = 0.0f;
    inv = INV;
    f2 = g_00BC28F8;
    m_54 = zero;
    m_28 = izero;
    m_2C = izero;
    m_30 = izero;
    m_38 = izero;
    m_3C = izero;
    m_44 = izero;
    m_4C = izero;
    m_50 = izero;
    m_58 = (unsigned char)izero;
    m_34 = 1;
    m_40 = 1;
    m_48 = 1;
    m_5C = zero;
    m_60 = zero;
    m_64 = zero;
    m_68 = zero;
    m_6C = zero;
    m_70 = zero;
    m_8C = zero;
    float f3;
    f3 = g_00C37C2C;
    m_74 = inv;
    float one;
    one = 1.0f;
    m_90 = f3;
    float f4;
    f4 = g_00BCCB3C;
    m_78 = (unsigned char)izero;
    m_7C = one;
    m_80 = one;
    m_84 = f2;
    m_88 = (unsigned char)izero;
    m_94 = f4;
    m_98 = one;
    m_9C = one;
    m_A0 = one;
    m_A4 = one;
    m_A8 = one;
    g_009FE1C8->rva002129A1(this);
}
