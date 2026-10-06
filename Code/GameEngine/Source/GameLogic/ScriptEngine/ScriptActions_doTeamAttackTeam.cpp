// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ScriptActions::doTeamAttackTeam, retail 0x003BED59, 120 bytes.
// Target identity: initActionTemplates TEAM_ATTACK_TEAM with two team names;
// executeAction calls VA 0x007BED59. Target resolves both teams via
// getTeamNamed at 0x3584E9, creates an AIGroup through 0x2FEC4B, fills it via
// Team::getTeamAsAIGroup at 0x3A0F62, then calls groupAttackTeam at 0x36FF33
// with victim plus 0x7fffffff plus source 1. ZH donor ScriptActions.cpp
// doAttack TEAM_ATTACK_TEAM does the same validated team team group sequence.

// The donor AsciiString stores one StringBase<char> pointer. The inline copy
// constructor is carried locally so this handler uses the matched retail
// StringBase copy routine without depending on broader headers.
#include "ascii_string.h"


class Team;
enum CommandSourceType { CMD_FROM_SCRIPT = 1 };

class AIGroup
{
public:
    void groupAttackTeam(const Team *, int, CommandSourceType);
};

class ScriptEngine
{
public:
    Team *getTeamNamed(AsciiString, bool = false);
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
    void doTeamAttackTeam(const AsciiString &, const AsciiString &);
};

void ScriptActions::doTeamAttackTeam(const AsciiString &teamName, const AsciiString &victimTeamName)
{
    Team *theTeam = TheScriptEngine->getTeamNamed(teamName);
    Team *victimTeam = TheScriptEngine->getTeamNamed(victimTeamName);
    if (!theTeam) {
        return;
    }
    if (!victimTeam) {
        return;
    }
    AIGroup *theGroup = TheAI->createGroup();
    if (!theGroup) {
        return;
    }
    theTeam->getTeamAsAIGroup(theGroup);
    theGroup->groupAttackTeam(victimTeam, 0x7fffffff, CMD_FROM_SCRIPT);
}
