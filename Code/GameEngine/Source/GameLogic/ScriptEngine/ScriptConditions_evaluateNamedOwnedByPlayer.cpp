// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?evaluateNamedOwnedByPlayer@ScriptConditions@@IAE_NPAVParameter@@0@Z
// @0x003E40D2 96B. ZH donor: GeneralsMD ScriptConditions.cpp
// evaluateNamedOwnedByPlayer. Target evidence: the evaluateCondition jump
// table (0x007EC5C0) sends case 30 here, which initConditionTemplates names
// NAMED_OWNED_BY_PLAYER. BFME2 differences: the unit is looked up first
// (rowed getUnitNamed 0x003588E7 taking the Parameter), and the player
// parameter is a mask from the pinned ScriptEngine helper 0x00357B82 walked
// with the rowed PlayerList::getEachPlayerFromMask 0x002A7BC9, comparing each
// player with the rowed Object::getControllingPlayer 0x0028AFA9.
#include "ascii_string.h"
class Parameter;
typedef int PlayerMaskType;
class Player;
class Object
{
public:
    Player *getControllingPlayer() const;
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
    Object *getUnitNamed(Parameter *);
    int rva00357B82(Parameter *playerParm);
};
extern ScriptEngine *TheScriptEngine;
class ScriptConditions
{
protected:
    bool evaluateNamedOwnedByPlayer(Parameter *, Parameter *);
};
bool ScriptConditions::evaluateNamedOwnedByPlayer(Parameter *pUnitParm, Parameter *pPlayerParm)
{
    Object *pObj = TheScriptEngine->getUnitNamed(pUnitParm);
    if (!pObj) {
        return false;
    }

    PlayerMaskType mask = TheScriptEngine->rva00357B82(pPlayerParm);
    while (mask) {
        Player *pPlayer = ThePlayerList->getEachPlayerFromMask(mask);
        if (pObj->getControllingPlayer() == pPlayer) {
            return true;
        }
    }
    return false;
}
