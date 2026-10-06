// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// Zero Hour's ScriptConditions::evaluateScienceAcquired (retail 0x003E4403,
// 108B) and evaluateCanPurchaseScience (0x003E446F, 98B), next after the
// FromUnit evaluators as in Zero Hour: the science looked up by internal
// name on TheScienceStore first, then per player of the BFME2 player mask
// the rowed ScriptEngine science query 0x00357B3D (its row types the
// science as ObjectID) or Player::isCapableOfPurchasingScience.
#include "ascii_string.h"
class Parameter
{
public:
    const AsciiString &getString() const { return m_string; }
    unsigned char m_beforeInt[8]; int m_int; float m_real; AsciiString m_string;
    unsigned char m_afterString[8];
};
typedef int PlayerMaskType;
enum ScienceType
{
    SCIENCE_INVALID = -1
};
enum ObjectID
{
    INVALID_ID = 0
};
class ScienceStore
{
public:
    ScienceType getScienceFromInternalName(const AsciiString &name) const;
};
extern ScienceStore *TheScienceStore;
class Player
{
public:
    int getPlayerIndex() const { return m_playerIndex; }
    bool isCapableOfPurchasingScience(ScienceType science) const;
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
    bool rva00357B3D(int playerIndex, ObjectID science, bool clearIt);
};
extern ScriptEngine *TheScriptEngine;
class ScriptConditions
{
protected:
    bool evaluateScienceAcquired(Parameter *pPlayerParm, Parameter *pScienceParm);
    bool evaluateCanPurchaseScience(Parameter *pPlayerParm, Parameter *pScienceParm);
};

bool ScriptConditions::evaluateScienceAcquired(Parameter *pPlayerParm, Parameter *pScienceParm)
{
    ScienceType science = TheScienceStore->getScienceFromInternalName(pScienceParm->getString());
    if (science == SCIENCE_INVALID)
        return false;
    PlayerMaskType mask = TheScriptEngine->rva00357B82(pPlayerParm);
    while (mask)
    {
        Player *player = ThePlayerList->getEachPlayerFromMask(mask);
        if (player && TheScriptEngine->rva00357B3D(player->getPlayerIndex(), (ObjectID)science, true))
            return true;
    }
    return false;
}

bool ScriptConditions::evaluateCanPurchaseScience(Parameter *pPlayerParm, Parameter *pScienceParm)
{
    ScienceType science = TheScienceStore->getScienceFromInternalName(pScienceParm->getString());
    if (science == SCIENCE_INVALID)
        return false;
    PlayerMaskType mask = TheScriptEngine->rva00357B82(pPlayerParm);
    while (mask)
    {
        Player *player = ThePlayerList->getEachPlayerFromMask(mask);
        if (player && player->isCapableOfPurchasingScience(science))
            return true;
    }
    return false;
}
