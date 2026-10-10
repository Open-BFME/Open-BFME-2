// cl: /Ireference/shims/bfme2_ascii /Oy- /DNDEBUG /MD /EHsc
// UpgradeCenter::canAffordUpgrade from the Upgrade.cpp reference, isolated
// so its BFME 2 money and UI layouts can be checked against retail.

class Player {
public:
    char m_pad[0x94];
    unsigned m_money;
};

class UpgradeTemplate {
public:
    unsigned calcCostToBuild(Player *, unsigned) const;
};

#include "ascii_string.h"


class InGameUI {
public:
    virtual void __stdcall slot0();
    virtual void __stdcall slot1();
    virtual void __stdcall slot2();
    virtual void __stdcall slot3();
    virtual void __stdcall slot4();
    virtual void __stdcall slot5();
    virtual void __stdcall slot6();
    virtual void __stdcall slot7();
    virtual void __stdcall slot8();
    virtual void __stdcall slot9();
    virtual void __stdcall slot10();
    virtual void __stdcall slot11();
    virtual void __stdcall slot12();
    virtual void __stdcall slot13();
    virtual void __stdcall slot14();
    virtual void __cdecl message(AsciiString);
};

extern InGameUI *TheInGameUI;

bool __stdcall bfmeCanAffordUpgrade(Player *player,
                                   const UpgradeTemplate *upgrade,
                                   unsigned context,
                                   bool displayReason)
{
    if (!player || !upgrade)
        return false;
    unsigned money = player->m_money;
    if (money < upgrade->calcCostToBuild(player, context)) {
        if (displayReason)
            TheInGameUI->message(AsciiString("GUI:NotEnoughMoneyToUpgrade"));
        return false;
    }
    return true;
}
// ?rva0026F11A@UpgradeCenter@@QAE_NPAVPlayer@@PBVUpgradeTemplate@@PAVObject@@_N@Z
// @0x0026F11A (83B): same body. Retail AIGroup::rva0036DE89 0x0036DEB8
// calls 0x0026F11A where its source calls
// TheUpgradeCenter->rva0026F11A(player, upgrade, obj, false), so the
// UpgradeCenter thiscall name belongs at this address too. The body never
// reads ECX (all four arguments come from the stack), hence identical bytes
// under either convention; the third argument is an Object* at call sites.
class Object;
class UpgradeCenter
{
public:
    bool rva0026F11A(Player *player, const UpgradeTemplate *upgrade,
                     Object *obj, bool displayReason);
};
bool UpgradeCenter::rva0026F11A(Player *player,
                                const UpgradeTemplate *upgrade,
                                Object *obj,
                                bool displayReason)
{
    if (!player || !upgrade)
        return false;
    unsigned money = player->m_money;
    if (money < upgrade->calcCostToBuild(player, (unsigned)obj)) {
        if (displayReason)
            TheInGameUI->message(AsciiString("GUI:NotEnoughMoneyToUpgrade"));
        return false;
    }
    return true;
}
