// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ScriptActions::doTeamAttackArea, retail 0x003BEF20, 109 bytes.
// Target identity: initActionTemplates index 0x32 (50) is TEAM_ATTACK_AREA;
// executeAction case 0x32 calls VA 0x007BEF20. Target resolves the team via
// getTeamNamed at 0x3584E9, creates an AIGroup through 0x2FEC4B, fills it via
// Team::getTeamAsAIGroup at 0x3A0F62, resolves a qualified trigger via 0x35768D,
// and calls groupAttackArea at 0x370517 with command source 1. Target body
// supports the pins and exact helper ordering described here.
// Donor facts: BFME1 ScriptActions.cpp maps this action to doTeamAttackArea and
// performs the same validated team/group/trigger sequence.

// The donor AsciiString stores one StringBase<char> pointer. The inline copy
// constructor is carried locally so this handler uses the matched retail
// StringBase copy routine without depending on broader headers.
#include "ascii_string.h"


class Team;
class PolygonTrigger;
enum CommandSourceType { CMD_FROM_SCRIPT = 1 };

class AIGroup
{
public:
    void groupAttackArea(PolygonTrigger *, CommandSourceType);
};

class ScriptEngine
{
public:
    Team *getTeamNamed(AsciiString, bool = false);
    PolygonTrigger *getQualifiedTriggerAreaByName(AsciiString);
};
extern ScriptEngine *TheScriptEngine;

class AI
{
public:
    AIGroup *createGroup();
};
extern AI *TheAI;

class Team
{
public:
    void getTeamAsAIGroup(AIGroup *);
};

class ScriptActions
{
protected:
    void doTeamAttackArea(const AsciiString &, const AsciiString &);
};

void ScriptActions::doTeamAttackArea(const AsciiString &teamName, const AsciiString &areaName)
{
    Team *theTeam = TheScriptEngine->getTeamNamed(teamName);
    if (!theTeam) {
        return;
    }
    AIGroup *theGroup = TheAI->createGroup();
    if (!theGroup) {
        return;
    }
    theTeam->getTeamAsAIGroup(theGroup);
    PolygonTrigger *trigger = TheScriptEngine->getQualifiedTriggerAreaByName(areaName);
    if (!trigger) {
        return;
    }
    theGroup->groupAttackArea(trigger, CMD_FROM_SCRIPT);
}
