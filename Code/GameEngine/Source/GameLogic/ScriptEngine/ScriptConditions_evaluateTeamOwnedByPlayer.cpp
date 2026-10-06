// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?evaluateTeamOwnedByPlayer@ScriptConditions@@IAE_NPAVParameter@@0@Z
// @0x003E6B57 110B. ZH donor: GeneralsMD ScriptConditions.cpp
// evaluateTeamOwnedByPlayer. Target evidence: the evaluateCondition jump table
// (0x007EC5C0) sends case 31 here, which initConditionTemplates names
// TEAM_OWNED_BY_PLAYER. BFME2 difference: the player parameter is a mask from
// the pinned ScriptEngine helper 0x00357B82 walked with the rowed
// PlayerList::getEachPlayerFromMask 0x002A7BC9, comparing each player with
// the rowed Team::getControllingPlayer 0x0039D7CF; the team comes first
// through the pinned getTeamNamed 0x003584E9.
#include "ascii_string.h"
class Parameter
{
public:
    const AsciiString &getString() const { return m_string; }
    unsigned char m_beforeInt[8]; int m_int; float m_real; AsciiString m_string;
    unsigned char m_afterString[8];
};
typedef int PlayerMaskType;
class Player;
class Team
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
    Team *getTeamNamed(AsciiString, bool);
    int rva00357B82(Parameter *playerParm);
};
extern ScriptEngine *TheScriptEngine;
class ScriptConditions
{
protected:
    bool evaluateTeamOwnedByPlayer(Parameter *, Parameter *);
};
bool ScriptConditions::evaluateTeamOwnedByPlayer(Parameter *pTeamParm, Parameter *pPlayerParm)
{
    Team *theTeam = TheScriptEngine->getTeamNamed(pTeamParm->getString(), false);
    if (!theTeam) {
        return false;
    }

    PlayerMaskType mask = TheScriptEngine->rva00357B82(pPlayerParm);
    while (mask) {
        Player *pPlayer = ThePlayerList->getEachPlayerFromMask(mask);
        if (theTeam->getControllingPlayer() == pPlayer) {
            return true;
        }
    }
    return false;
}
