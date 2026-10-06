// cl: /MD /EHsc
// ??0Rva004D9539@@QAE@HHH@Z @0x004D9539 77B. EH ctor with two rowed Upgrades at +0/+8 then three ints at +0x10/+0x14/+0x18 plus zeroed +0x1C/+0x20.
// Evidence: retail __EH_prolog call Upgrades state0 call Upgrades mov args ret 0xC; callee 0x004CEE6E Upgrades@CashHackSpecialPowerModuleData; caller 0x004DADA9.
class CashHackSpecialPowerModuleData
{
public:
    struct Upgrades
    {
        int m_science;
        int m_amountToSteal;
        Upgrades();
        ~Upgrades();
    };
};
class Rva004D9539
{
public:
    Rva004D9539(int a, int b, int c);
private:
    CashHackSpecialPowerModuleData::Upgrades m_a; // +0
    CashHackSpecialPowerModuleData::Upgrades m_b; // +8
    int m_10; // +0x10
    int m_14; // +0x14
    int m_18; // +0x18
    int m_1C; // +0x1C
    unsigned char m_20; // +0x20
};
Rva004D9539::Rva004D9539(int a, int b, int c) : m_a(), m_b()
{
    m_10 = a;
    m_14 = b;
    m_18 = c;
    m_1C = 0;
    m_20 = 0;
}
