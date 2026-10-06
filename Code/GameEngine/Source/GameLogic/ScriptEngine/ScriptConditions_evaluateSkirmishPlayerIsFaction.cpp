// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?evaluateSkirmishPlayerIsFaction@ScriptConditions@@IAE_NPAVParameter@@0@Z
// @0x003E9E62 78B. ZH donor: GeneralsMD ScriptConditions.cpp
// evaluateSkirmishPlayerIsFaction. Target evidence: the evaluateCondition jump
// table (0x007EC5C0) sends case 87 here, which initConditionTemplates names
// SKIRMISH_PLAYER_FACTION. BFME2 difference: the player parameter is a mask
// from the pinned ScriptEngine helper 0x00357B82 walked with the rowed
// PlayerList::getEachPlayerFromMask 0x002A7BC9, true when any player's side
// string (Player +0x58) equals the faction parameter (rowed
// StringBase<char>::compare 0x000069D6).
#include "ascii_string.h"
class Parameter
{
public:
    const AsciiString &getString() const { return m_string; }
    unsigned char m_beforeInt[8]; int m_int; float m_real; AsciiString m_string;
    unsigned char m_afterString[8];
};
typedef int PlayerMaskType;
class Player
{
public:
    const AsciiString &getSide() const { return m_side; }
    unsigned char m_pad00[0x58];
    AsciiString m_side; // +0x58
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
    bool evaluateSkirmishPlayerIsFaction(Parameter *, Parameter *);
};
bool ScriptConditions::evaluateSkirmishPlayerIsFaction(Parameter *pSkirmishPlayerParm, Parameter *pFactionParm)
{
    PlayerMaskType mask = TheScriptEngine->rva00357B82(pSkirmishPlayerParm);
    while (mask) {
        Player *player = ThePlayerList->getEachPlayerFromMask(mask);
        if (player && player->getSide() == pFactionParm->getString()) {
            return true;
        }
    }
    return false;
}
