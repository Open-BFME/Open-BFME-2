// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ZH donor: GeneralsMD ScriptConditions.cpp evaluateSciencePurchasePoints and
// evaluateSkirmishStartPosition. Target evidence: the evaluateCondition jump
// table (0x007EC5C0) sends case 101 to 0x003E44D1 and case 107 to 0x003E4B2A,
// which initConditionTemplates names PLAYER_HAS_SCIENCEPURCHASEPOINTS and
// START_POSITION_IS. BFME2 difference: the player parameter is a mask from
// the pinned ScriptEngine helper 0x00357B82 walked with the rowed
// PlayerList::getEachPlayerFromMask 0x002A7BC9, true when any player matches.
// Player +0x24 is the science purchase points and +0x2E0 the multiplayer
// start index (retail offsets).
#include "ascii_string.h"
class Parameter
{
public:
    unsigned char m_beforeInt[8]; int m_int; float m_real; AsciiString m_string;
    unsigned char m_afterString[8];
};
typedef int PlayerMaskType;
class Player
{
public:
    int getSciencePurchasePoints() const { return m_sciencePurchasePoints; }
    int getMpStartIndex() const { return m_mpStartIndex; }
    unsigned char m_pad000[0x24];
    int m_sciencePurchasePoints; // +0x24
    unsigned char m_pad028[0x2E0 - 0x28];
    int m_mpStartIndex; // +0x2E0
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
    bool evaluateSciencePurchasePoints(Parameter *, Parameter *);
    bool evaluateSkirmishStartPosition(Parameter *, Parameter *);
};
bool ScriptConditions::evaluateSciencePurchasePoints(Parameter *pPlayerParm, Parameter *pSciencePointParm)
{
    int pointsNeeded = pSciencePointParm->m_int;
    PlayerMaskType mask = TheScriptEngine->rva00357B82(pPlayerParm);
    while (mask) {
        Player *pPlayer = ThePlayerList->getEachPlayerFromMask(mask);
        if (pPlayer && pPlayer->getSciencePurchasePoints() >= pointsNeeded) {
            return true;
        }
    }
    return false;
}
bool ScriptConditions::evaluateSkirmishStartPosition(Parameter *pSkirmishPlayerParm, Parameter *pStartNdx)
{
    PlayerMaskType mask = TheScriptEngine->rva00357B82(pSkirmishPlayerParm);
    while (mask) {
        Player *player = ThePlayerList->getEachPlayerFromMask(mask);
        if (player && pStartNdx->m_int - 1 == player->getMpStartIndex()) {
            return true;
        }
    }
    return false;
}
