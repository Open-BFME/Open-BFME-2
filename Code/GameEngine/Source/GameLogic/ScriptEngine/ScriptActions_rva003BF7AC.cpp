// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// ?Rva003BF7ACDo@ScriptActions@@QAEXABVAsciiString@@PAVParameter@@@Z @0x003BF7AC 103B
// Script team group order via getUnitNamed row 0x003588E7 (Parameter overload)
// plus getTeamNamed pin 0x003584E9 with false, createGroup pin 0x002FEC4B,
// getTeamAsAIGroup pin 0x003A0F62, then rowed groupGuardObject with unit plus 0 and 1.
// Evidence: TheScriptEngine 0x009FE16C, TheAI 0x009FF0F8; caller 0x003CB5E4;
// precedent Rva003C2A29Script.cpp 118B same team/group sequence with two teams.
#include "ascii_string.h"
typedef bool Bool;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1
};

class Parameter;
class Object;
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
	void groupGuardObject(Object *obj, int x, CommandSourceType src);
};

extern ScriptEngine *TheScriptEngine;
extern AI *TheAI;

void ScriptActions::Rva003BF7ACDo(const AsciiString &teamName, Parameter *param)
{
	Object *unit = TheScriptEngine->getUnitNamed(param);
	Team *team = TheScriptEngine->getTeamNamed((AsciiString &)teamName, false);
	if (team == 0 || unit == 0)
		return;
	AIGroup *group = TheAI->createGroup();
	if (group == 0)
		return;
	team->getTeamAsAIGroup(group);
	group->groupGuardObject(unit, 0, CMD_FROM_SCRIPT);
}
