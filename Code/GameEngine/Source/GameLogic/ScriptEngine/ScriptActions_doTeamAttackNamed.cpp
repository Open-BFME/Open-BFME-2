// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ScriptActions::doTeamAttackNamed, retail 0x003C3B7D, 141 bytes.
// Target identity: initActionTemplates index 0x33 (51) is TEAM_ATTACK_NAMED;
// executeAction case 0x33 calls VA 0x007C3B7D. The target resolves a team,
// resolves its victim, creates/fills an AIGroup, then calls StringBase compare
// at 0x69B1 against target string xref "Aragorn 2" and emits a special player
// attack before the normal script attack. Target direct calls and helper pins
// support the Team/AIGroup operations.
// Donor facts: BFME1 ScriptActions_doTeamAttackNamed_Thunk.cpp and Zero Hour
// source document the same one-off Aragorn 2 player-source command followed by
// the unconditional script-source groupAttackObject call.

typedef int Int;
typedef bool Bool;

class Object;
class Team;

class StringBaseChar
{
public:
    int compare(const char *) const;
};

#include "ascii_string.h"


enum CommandSourceType
{
    CMD_FROM_PLAYER = 0,
    CMD_FROM_SCRIPT = 1
};

class ScriptEngine
{
public:
    Team *getTeamNamed(AsciiString, bool);
    Object *getUnitNamed(const AsciiString &);
};
extern ScriptEngine *TheScriptEngine;

class AIGroup
{
private:
    void groupAttackObjectPrivate(bool, Object *, Int, CommandSourceType);
public:
    void groupAttackObject(Object *victim, Int maxShotsToFire,
                           CommandSourceType cmdSource)
    {
        groupAttackObjectPrivate(false, victim, maxShotsToFire, cmdSource);
    }
};

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
    void doTeamAttackNamed(const AsciiString &, const AsciiString &);
};

void ScriptActions::doTeamAttackNamed(const AsciiString &teamName,
                                      const AsciiString &unitName)
{
    Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
    if (!theTeam) {
        return;
    }
    Object *theVictim = TheScriptEngine->getUnitNamed(unitName);
    if (!theVictim) {
        return;
    }
    AIGroup *theGroup = TheAI->createGroup();
    if (!theGroup) {
        return;
    }
    theTeam->getTeamAsAIGroup(theGroup);
    if (teamName.compare("Aragorn 2") == 0) {
        theGroup->groupAttackObject(theVictim, 0x7fffffff, CMD_FROM_PLAYER);
    }
    theGroup->groupAttackObject(theVictim, 0x7fffffff, CMD_FROM_SCRIPT);
}
