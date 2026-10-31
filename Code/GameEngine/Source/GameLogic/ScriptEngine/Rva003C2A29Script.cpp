// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// ?Rva003C2A29Do@ScriptActions@@QAEXABVAsciiString@@0@Z @0x003C2A29 118B
// Script team group order via two getTeamNamed pins 0x003584E9 with false,
// createGroup pin 0x002FEC4B, getTeamAsAIGroup pin 0x003A0F62,
// then rowed rva00370451 with second team plus 0 and 1.
// Evidence: StringBase copy pin 0x000365F0 temporaries; TheScriptEngine 0x009FE16C
// TheAI 0x009FF0F8; caller 0x003CE10D; precedent doTeamSpinForFramecount by-value.
#include "ascii_string.h"
typedef bool Bool;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1
};

class Team;
class AIGroup;

#include "../../../Include/GameLogic/ScriptEngine.h"

class AI
{
public:
	AIGroup *createGroup();
};

#include "../../../Include/Common/TeamBFME2.h"

class AIGroup
{
public:
	void rva00370451(const Team *team, int x, CommandSourceType src);
};

extern ScriptEngine *TheScriptEngine;
extern AI *TheAI;

void ScriptActions::Rva003C2A29Do(const AsciiString &team1, const AsciiString &team2)
{
	Team *team = TheScriptEngine->getTeamNamed((AsciiString &)team1, false);
	Team *t2 = TheScriptEngine->getTeamNamed((AsciiString &)team2, false);
	if (team == 0 || t2 == 0)
		return;
	AIGroup *aIGroup = TheAI->createGroup();
	if (aIGroup == 0)
		return;
	team->getTeamAsAIGroup(aIGroup);
	aIGroup->rva00370451(t2, 0, CMD_FROM_SCRIPT);
}
