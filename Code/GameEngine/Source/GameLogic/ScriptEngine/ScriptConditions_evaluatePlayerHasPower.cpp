// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ZH donor: GeneralsMD ScriptConditions.cpp evaluatePlayerHasPower and
// evaluatePlayerHasNOrFewerBuildings. Target evidence: the evaluateCondition
// jump table (0x007EC5C0) sends cases 33 and 47 (PLAYER_HAS_POWER, and
// PLAYER_HAS_NO_POWER through the dispatcher) to 0x003E417D and case 32 to
// 0x003E4132, which initConditionTemplates names PLAYER_HAS_N_OR_FEWER_BUILDINGS.
// BFME2 difference: the player parameter is a mask from the pinned ScriptEngine
// helper 0x00357B82, walked with the rowed PlayerList::getEachPlayerFromMask
// 0x002A7BC9 on ThePlayerList (0x00DFEEE8); power asks the rowed 0x004DF17F on
// the energy block embedded at Player +0x1BC (ZH hasSufficientPower), and the
// building count sums Player::countBuildings 0x002AB10F over the mask.
// Structural inference: the count result is an if/return pair, which keeps
// retail's setge into al without a zeroed eax.
#include "ascii_string.h"
class Parameter
{
public:
    unsigned char m_beforeInt[8]; int m_int; float m_real; AsciiString m_string;
    unsigned char m_afterString[8];
};
typedef int PlayerMaskType;
class Rva004DF17F
{
public:
    bool rva004DF17F() const;
};
class Player
{
public:
    Rva004DF17F *getEnergy() { return &m_energy; }
    int countBuildings();
    unsigned char m_pad000[0x1BC];
    Rva004DF17F m_energy;
};
class PlayerList
{
public:
    Player *getEachPlayerFromMask(PlayerMaskType &maskToAdjust);
};
extern PlayerList *ThePlayerList;
class ScriptEngine
{
public:
    int rva00357B82(Parameter *playerParm);
};
extern ScriptEngine *TheScriptEngine;
class ScriptConditions
{
protected:
    bool evaluatePlayerHasNOrFewerBuildings(Parameter *, Parameter *);
    bool evaluatePlayerHasPower(Parameter *);
};
bool ScriptConditions::evaluatePlayerHasNOrFewerBuildings(Parameter *pBuildingCountParm, Parameter *pPlayerParm)
{
    PlayerMaskType mask = TheScriptEngine->rva00357B82(pPlayerParm);
    int count = 0;
    while (mask) {
        Player *pPlayer = ThePlayerList->getEachPlayerFromMask(mask);
        if (pPlayer) {
            count += pPlayer->countBuildings();
        }
    }
    // Native code reads this view's +0x08 word directly. Other Parameter
    // views give getInt a different layout, so do not emit that shared name.
    if (pBuildingCountParm->m_int >= count) {
        return true;
    }
    return false;
}
bool ScriptConditions::evaluatePlayerHasPower(Parameter *pPlayerParm)
{
    PlayerMaskType mask = TheScriptEngine->rva00357B82(pPlayerParm);
    while (mask) {
        Player *pPlayer = ThePlayerList->getEachPlayerFromMask(mask);
        if (!pPlayer) {
            continue;
        }
        Rva004DF17F *pPlayersEnergy = pPlayer->getEnergy();
        if (!pPlayersEnergy) {
            continue;
        }
        if (pPlayersEnergy->rva004DF17F()) {
            return true;
        }
    }
    return false;
}
