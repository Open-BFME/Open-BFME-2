// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?evaluateSkirmishPlayerHasBeenAttackedByPlayer@ScriptConditions@@IAE_NPAVParameter@@0@Z
// @0x003E4BFA 125B. ZH donor: GeneralsMD ScriptConditions.cpp
// evaluateSkirmishPlayerHasBeenAttackedByPlayer. Target evidence: the
// evaluateCondition jump table (0x007EC5C0) sends case 97 here, which
// initConditionTemplates names SKIRMISH_PLAYER_HAS_BEEN_ATTACKED_BY_PLAYER.
// BFME2 difference: both player parameters are masks from the pinned
// ScriptEngine helper 0x00357B82, walked with the rowed
// PlayerList::getEachPlayerFromMask 0x002A7BC9 (the attacker mask restarts for
// each player). The attacked-by test is the rowed indexed byte getter
// 0x002AA201 called on the Player with the attacker's index (Player +0x54);
// that row keeps its placeholder class, hence the cast.
#include "ascii_string.h"
class Parameter;
typedef int PlayerMaskType;
class Rva002AA201IndexedByteField
{
public:
    unsigned char get(int index) const;
};
class Player
{
public:
    int getPlayerIndex() const { return m_playerIndex; }
    unsigned char m_pad00[0x54];
    int m_playerIndex; // +0x54
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
    bool evaluateSkirmishPlayerHasBeenAttackedByPlayer(Parameter *, Parameter *);
};
bool ScriptConditions::evaluateSkirmishPlayerHasBeenAttackedByPlayer(Parameter *pSkirmishPlayerParm, Parameter *pAttackedByParm)
{
    PlayerMaskType playerMask = TheScriptEngine->rva00357B82(pSkirmishPlayerParm);
    PlayerMaskType attackerMask = TheScriptEngine->rva00357B82(pAttackedByParm);
    while (playerMask) {
        Player *player = ThePlayerList->getEachPlayerFromMask(playerMask);
        if (!player) {
            continue;
        }
        PlayerMaskType mask = attackerMask;
        while (mask) {
            Player *srcPlayer = ThePlayerList->getEachPlayerFromMask(mask);
            if (srcPlayer && ((const Rva002AA201IndexedByteField *)player)->get(srcPlayer->getPlayerIndex())) {
                return true;
            }
        }
    }
    return false;
}
