// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// Zero Hour's ScriptConditions::evaluatePlayerSpecialPowerFromUnitTriggered,
// ...Midway, ...Complete and evaluateUpgradeFromUnitComplete (retail
// 0x003E422B, 0x003E42A1, 0x003E4317, 0x003E438D; 118B each, in Zero Hour's
// order, called from the condition dispatcher at 0x003EB490..0x003EB60D):
// an optional unit parameter supplies the source ObjectID (+0x74; a missing
// unit answers false), then the rowed ScriptEngine queries 0x003571B8,
// 0x0035721A, 0x0035727C and 0x003572DE (Zero Hour's isSpecialPowerTriggered,
// ...MidwayThrough, ...Complete and isUpgradeComplete order) run per player
// index (+0x54). BFME2 difference, as in
// ScriptConditions_evaluateSkirmishPlayerIsFaction.cpp: the player parameter
// is a mask walked with PlayerList::getEachPlayerFromMask.
#include "ascii_string.h"
class Parameter
{
public:
    const AsciiString &getString() const { return m_string; }
    unsigned char m_beforeInt[8]; int m_int; float m_real; AsciiString m_string;
    unsigned char m_afterString[8];
};
typedef int PlayerMaskType;
typedef unsigned int ObjectID;
class Object
{
public:
    ObjectID getID() const { return m_id; }
private:
    unsigned char m_pad00[0x74];
    ObjectID m_id; // +0x74
};
class Player
{
public:
    int getPlayerIndex() const { return m_playerIndex; }
private:
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
    Object *getUnitNamed(Parameter *unitParm);
    bool rva003571B8(int playerIndex, const AsciiString &name, bool flag, int sourceID);
    bool rva0035721A(int playerIndex, const AsciiString &name, bool flag, int sourceID);
    bool rva0035727C(int playerIndex, const AsciiString &name, bool flag, int sourceID);
    bool rva003572DE(int playerIndex, const AsciiString &name, bool flag, int sourceID);
};
extern ScriptEngine *TheScriptEngine;
class ScriptConditions
{
protected:
    bool evaluatePlayerSpecialPowerFromUnitTriggered(Parameter *pPlayerParm, Parameter *pSpecialPowerParm, Parameter *pUnitParm);
    bool evaluatePlayerSpecialPowerFromUnitMidway(Parameter *pPlayerParm, Parameter *pSpecialPowerParm, Parameter *pUnitParm);
    bool evaluatePlayerSpecialPowerFromUnitComplete(Parameter *pPlayerParm, Parameter *pSpecialPowerParm, Parameter *pUnitParm);
    bool evaluateUpgradeFromUnitComplete(Parameter *pPlayerParm, Parameter *pUpgradeParm, Parameter *pUnitParm);
};

bool ScriptConditions::evaluatePlayerSpecialPowerFromUnitTriggered(Parameter *pPlayerParm, Parameter *pSpecialPowerParm, Parameter *pUnitParm)
{
    ObjectID sourceID = 0;
    if (pUnitParm)
    {
        Object *pUnit = TheScriptEngine->getUnitNamed(pUnitParm);
        if (!pUnit)
            return false;
        sourceID = pUnit->getID();
    }
    PlayerMaskType mask = TheScriptEngine->rva00357B82(pPlayerParm);
    while (mask)
    {
        Player *player = ThePlayerList->getEachPlayerFromMask(mask);
        if (player && TheScriptEngine->rva003571B8(player->getPlayerIndex(), pSpecialPowerParm->getString(), true, sourceID))
            return true;
    }
    return false;
}

bool ScriptConditions::evaluatePlayerSpecialPowerFromUnitMidway(Parameter *pPlayerParm, Parameter *pSpecialPowerParm, Parameter *pUnitParm)
{
    ObjectID sourceID = 0;
    if (pUnitParm)
    {
        Object *pUnit = TheScriptEngine->getUnitNamed(pUnitParm);
        if (!pUnit)
            return false;
        sourceID = pUnit->getID();
    }
    PlayerMaskType mask = TheScriptEngine->rva00357B82(pPlayerParm);
    while (mask)
    {
        Player *player = ThePlayerList->getEachPlayerFromMask(mask);
        if (player && TheScriptEngine->rva0035721A(player->getPlayerIndex(), pSpecialPowerParm->getString(), true, sourceID))
            return true;
    }
    return false;
}

bool ScriptConditions::evaluatePlayerSpecialPowerFromUnitComplete(Parameter *pPlayerParm, Parameter *pSpecialPowerParm, Parameter *pUnitParm)
{
    ObjectID sourceID = 0;
    if (pUnitParm)
    {
        Object *pUnit = TheScriptEngine->getUnitNamed(pUnitParm);
        if (!pUnit)
            return false;
        sourceID = pUnit->getID();
    }
    PlayerMaskType mask = TheScriptEngine->rva00357B82(pPlayerParm);
    while (mask)
    {
        Player *player = ThePlayerList->getEachPlayerFromMask(mask);
        if (player && TheScriptEngine->rva0035727C(player->getPlayerIndex(), pSpecialPowerParm->getString(), true, sourceID))
            return true;
    }
    return false;
}

bool ScriptConditions::evaluateUpgradeFromUnitComplete(Parameter *pPlayerParm, Parameter *pUpgradeParm, Parameter *pUnitParm)
{
    ObjectID sourceID = 0;
    if (pUnitParm)
    {
        Object *pUnit = TheScriptEngine->getUnitNamed(pUnitParm);
        if (!pUnit)
            return false;
        sourceID = pUnit->getID();
    }
    PlayerMaskType mask = TheScriptEngine->rva00357B82(pPlayerParm);
    while (mask)
    {
        Player *player = ThePlayerList->getEachPlayerFromMask(mask);
        if (player && TheScriptEngine->rva003572DE(player->getPlayerIndex(), pUpgradeParm->getString(), true, sourceID))
            return true;
    }
    return false;
}
