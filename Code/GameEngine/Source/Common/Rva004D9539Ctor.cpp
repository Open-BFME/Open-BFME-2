// cl: /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// ??0Rva004D9539@@QAE@HHH@Z @0x004D9539 77B. EH ctor with two Rva002390CB records at +0/+8 then three ints at +0x10/+0x14/+0x18 plus zeroed +0x1C/+0x20.
// Evidence: retail __EH_prolog call ctor state0 call ctor mov args ret 0xC; callee 0x004CEE6E; caller 0x004DADA9.
// The members' ctor 0x004CEE6E is pinned as ??0Rva002390CB (a fold shared
// with CashHackSpecialPowerModuleData::Upgrades' ctor), and retail's unwind
// funclet 0x00791265 runs 0x004C9F38, rowed as ??1Rva002390CB: ZH's Upgrades
// has no destructor, so the members are Rva002390CB records.
#include "../../Include/Common/Rva002390CB.h"
class Rva004D9539
{
public:
    Rva004D9539(int a, int b, int c);
private:
    Rva002390CB m_a; // +0
    Rva002390CB m_b; // +8
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
