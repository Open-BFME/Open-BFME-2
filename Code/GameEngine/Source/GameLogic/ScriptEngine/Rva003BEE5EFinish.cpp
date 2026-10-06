// ?updateTeamSetAttitude@ScriptActions@@IAEXABVAsciiString@@H@Z
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ScriptActions::updateTeamSetAttitude, retail 0x003BEE5E, 80 bytes.
// Target identity: initActionTemplates index 0x2E (46) is TEAM_SET_ATTITUDE;
// executeAction case 0x2E calls VA 0x007BEE5E. The target body copies the team
// name onto the stack, resolves it through getTeamNamed at 0x3584E9, asks TheAI
// at 0xDFF0F8 for a group via 0x2FEC4B, then calls 0x3A0F62 with the team/group
// and 0x36DD16 with the attitude argument. Callee pins record these
// relationships; the 0x365F0 call is the AsciiString copy constructor and the
// 89 65 FC is the unwind store for that destructor-scoped temporary, which is
// why the name reaches getTeamNamed as a by-value AsciiString rather than
// straight from [ebp+0x8].
// Donor facts: BFME1 ScriptActions.cpp maps TEAM_SET_ATTITUDE to
// updateTeamSetAttitude and performs the same create-group, team-fill,
// set-attitude sequence. Data layouts and the helper names beyond those pin
// uses remain donor-derived; the target body independently establishes call
// order.

typedef int Int;
typedef bool Bool;

class Object;
class Team;
class AIGroup;

enum AttitudeType { ATTITUDE_UNSPECIFIED = 0 };

#include "ascii_string.h"

class ScriptEngine
{
public:
    Team *getTeamNamed(AsciiString, Bool = false);
};
extern ScriptEngine *TheScriptEngine;

class AIGroup
{
public:
    void setAttitude(AttitudeType);
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
    void updateTeamSetAttitude(const AsciiString &, Int);
};

void ScriptActions::updateTeamSetAttitude(const AsciiString &teamName,
                                         Int attitude)
{
    Team *theSrcTeam = TheScriptEngine->getTeamNamed(teamName);
    if (!theSrcTeam) {
        return;
    }
    AIGroup *pAIGroup = TheAI->createGroup();
    if (!pAIGroup) {
        return;
    }
    theSrcTeam->getTeamAsAIGroup(pAIGroup);
    pAIGroup->setAttitude((AttitudeType)attitude);
}