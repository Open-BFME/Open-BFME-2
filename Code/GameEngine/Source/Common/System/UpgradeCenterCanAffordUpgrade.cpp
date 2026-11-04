// cl: /Ireference/shims/bfme2_ascii /Oy- /DNDEBUG /MD /EHsc
// UpgradeCenter::canAffordUpgrade from the Upgrade.cpp reference, isolated
// so its BFME 2 money and UI layouts can be checked against retail.

class Player {
public:
    char m_pad[0x94];
    unsigned m_money;
};

#include "../../../Include/Common/Upgrade.h"

#include "ascii_string.h"


#include "../../../Include/GameClient/InGameUI.h"

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
            TheInGameUI->rva0029E656(AsciiString("GUI:NotEnoughMoneyToUpgrade"));
        return false;
    }
    return true;
}
// ?rva0026F11A@UpgradeCenter@@QAE_NPAVPlayer@@PBVUpgradeTemplate@@PAVObject@@_N@Z
// @0x0026F11A (83B): same body. Retail AIGroup::queueUpgrade 0x0036DEB8
// calls 0x0026F11A where its source calls
// TheUpgradeCenter->rva0026F11A(player, upgrade, obj, false), so the
// UpgradeCenter thiscall name belongs at this address too. The body never
// reads ECX (all four arguments come from the stack), hence identical bytes
// under either convention; the third argument is an Object* at call sites.
class Object;
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
            TheInGameUI->rva0029E656(AsciiString("GUI:NotEnoughMoneyToUpgrade"));
        return false;
    }
    return true;
}
