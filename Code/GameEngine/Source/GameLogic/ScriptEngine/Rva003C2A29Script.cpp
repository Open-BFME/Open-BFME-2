// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?Rva003C2A29Do@@YGXABVAsciiString@@0@Z @0x003C2A29 118B
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

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString, Bool);
};

class AI
{
public:
	AIGroup *createGroup();
};

class Team
{
public:
	void getTeamAsAIGroup(AIGroup *group);
};

class AIGroup
{
public:
	void rva00370451(const Team *team, int x, CommandSourceType src);
};

extern ScriptEngine *TheScriptEngine;
extern AI *TheAI;

void __stdcall Rva003C2A29Do(const AsciiString &team1, const AsciiString &team2)
{
	Team *t1 = TheScriptEngine->getTeamNamed((AsciiString &)team1, false);
	Team *t2 = TheScriptEngine->getTeamNamed((AsciiString &)team2, false);
	if (t1 == 0 || t2 == 0)
		return;
	AIGroup *g = TheAI->createGroup();
	if (g == 0)
		return;
	t1->getTeamAsAIGroup(g);
	g->rva00370451(t2, 0, CMD_FROM_SCRIPT);
}
