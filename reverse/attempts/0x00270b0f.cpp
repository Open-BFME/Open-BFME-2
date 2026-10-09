// ?rva00270B0F@Rva00270B0F@@QAEXHPAURva00270B0FOut@@@Z
// partial score=0.9 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?rva00270B0F@Rva00270B0F@@QAEXHPAURva00270B0FOut@@@Z retail 0x00270B0F
// (153 bytes, RET 8). Exponential smoothing step of a signed [-0.8 .. 0.8]
// value stored at +0x140: when the owner at +0xFC has a controller at +0x258
// whose virtual slot 0x168/4 reports the feature active, the new value is
// 0.8 * old + 0.2 * (4.0 * input), the input being read at +0x53C from the
// object returned by slot 0x188/4; the result is clamped and written both to
// +0x140 and to the caller's output at +4. The first argument is unused.
// Class names are placeholders for the address.
class Rva00270B0FInput
{
public:
    char m_pad[0x53C];
    float m_value;
};

class Rva00270B0FController
{
public:
    virtual void s00();
    virtual void s01();
    virtual void s02();
    virtual void s03();
    virtual void s04();
    virtual void s05();
    virtual void s06();
    virtual void s07();
    virtual void s08();
    virtual void s09();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual void s27();
    virtual void s28();
    virtual void s29();
    virtual void s30();
    virtual void s31();
    virtual void s32();
    virtual void s33();
    virtual void s34();
    virtual void s35();
    virtual void s36();
    virtual void s37();
    virtual void s38();
    virtual void s39();
    virtual void s40();
    virtual void s41();
    virtual void s42();
    virtual void s43();
    virtual void s44();
    virtual void s45();
    virtual void s46();
    virtual void s47();
    virtual void s48();
    virtual void s49();
    virtual void s50();
    virtual void s51();
    virtual void s52();
    virtual void s53();
    virtual void s54();
    virtual void s55();
    virtual void s56();
    virtual void s57();
    virtual void s58();
    virtual void s59();
    virtual void s60();
    virtual void s61();
    virtual void s62();
    virtual void s63();
    virtual void s64();
    virtual void s65();
    virtual void s66();
    virtual void s67();
    virtual void s68();
    virtual void s69();
    virtual void s70();
    virtual void s71();
    virtual void s72();
    virtual void s73();
    virtual void s74();
    virtual void s75();
    virtual void s76();
    virtual void s77();
    virtual void s78();
    virtual void s79();
    virtual void s80();
    virtual void s81();
    virtual void s82();
    virtual void s83();
    virtual void s84();
    virtual void s85();
    virtual void s86();
    virtual void s87();
    virtual void s88();
    virtual void s89();
    virtual bool isActive();
    virtual void s91();
    virtual void s92();
    virtual void s93();
    virtual void s94();
    virtual void s95();
    virtual void s96();
    virtual void s97();
    virtual Rva00270B0FInput *getInput();
};

struct Rva00270B0FOwner
{
    char m_pad[0x258];
    Rva00270B0FController *m_controller;
};

struct Rva00270B0FOut
{
    int m_unused;
    float m_value;
};

class Rva00270B0F
{
public:
    void rva00270B0F(int unused, Rva00270B0FOut *out);
private:
    char m_pad[0xFC];
    Rva00270B0FOwner *m_owner;
    char m_pad100[0x40];
    float m_smoothed;
};

void Rva00270B0F::rva00270B0F(int unused, Rva00270B0FOut *out)
{
    if (m_owner)
    {
        Rva00270B0FController *controller = m_owner->m_controller;
        if (controller && controller->isActive())
        {
            float target = controller->getInput()->m_value * 4.0f;
            float value = m_smoothed * 0.8f + target * 0.2f;
            if (value < -0.8f)
                value = -0.8f;
            else if (value > 0.8f)
                value = 0.8f;
            m_smoothed = value;
            out->m_value = value;
        }
    }
}
