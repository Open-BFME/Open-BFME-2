// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// ?doTeamHunt@ScriptActions@@QAEXABVAsciiString@@@Z @0x003BF8B4 79B
// Script team hunt via getTeamNamed pin 0x003584E9 with false, createGroup
// pin 0x002FEC4B, getTeamAsAIGroup pin 0x003A0F62, then rowed groupHunt
// 0x0037008E with source 1.
// Evidence: TheScriptEngine 0x009FE16C, TheAI 0x009FF0F8; caller 0x003CB735;
// precedents Rva003BF7ACDo 103B plus doTeamExitAll team/group sequence.
#include "ascii_string.h"
typedef bool Bool;
enum CommandSourceType { CMD_FROM_PLAYER = 0, CMD_FROM_SCRIPT = 1 };
class Team;
class AIGroup;
#include "../../../Include/GameLogic/ScriptEngine.h"
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
	void groupHunt(CommandSourceType src);
};
extern ScriptEngine *TheScriptEngine;
extern AI *TheAI;

void ScriptActions::doTeamHunt(const AsciiString &teamName)
{
	Team *team = TheScriptEngine->getTeamNamed((AsciiString &)teamName, false);
	if (team == 0)
		return;
	AIGroup *group = TheAI->createGroup();
	if (group == 0)
		return;
	team->getTeamAsAIGroup(group);
	group->groupHunt(CMD_FROM_SCRIPT);
}
