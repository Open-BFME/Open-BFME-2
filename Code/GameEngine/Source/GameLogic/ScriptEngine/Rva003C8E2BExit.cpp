// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD -EHsc -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// platformsdk
// stlport
#include <windows.h>
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// ?Rva003C8E2BExit@ScriptActions@@QAEXABVAsciiString@@@Z retail 0x003C8E2B 94B
// Team exit-all action (ZH doTeamExitAllBuildings shape).
// Evidence: between Rva003C89D1Guard and Rva003C90B1Exit; caller 0x003CC1A3;
// rowed getTeamNamed 0x003584E9 plus iterate 0x00263864 plus advance 0x00263526
// plus aiExit 0x0036F39B.
#include "ascii_string.h"

class Object;
template<class OBJ> class DLINK_ITERATOR
{
public:
	void advance();
	bool done() const { return m_cur == 0; }
	OBJ *cur() const { return m_cur; }
private:
	OBJ *m_cur;
	char m_pad[20];
};

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
};

enum CommandSourceType { CMD_FROM_SCRIPT = 1 };

#include "../../../Include/GameLogic/ScriptEngine.h"

class AICommandInterface
{
public:
	void aiExit(Object *obj, CommandSourceType src);
};

class AIUpdateInterface
{
public:
	char m_pad[0x20];
	AICommandInterface m_command;
};

class Object
{
public:
	AIUpdateInterface *getAI() const { return *(AIUpdateInterface **)((const char *)this + 0x258); }
};

// Zero Hour's ScriptActions::doTeamExitAllBuildings without its locomotor-set
// call. Its explicit `if (!obj) continue;` is what makes cl keep one zero in
// ESI for every push and compare, as retail does.

extern ScriptEngine *TheScriptEngine;

void ScriptActions::Rva003C8E2BExit(const AsciiString &teamName)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
	if (!theTeam) {
		return;
	}
	for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		Object *obj = iter.cur();
		if (!obj) {
			continue;
		}
		AIUpdateInterface *ai = obj->getAI();
		if (!ai) {
			continue;
		}
		ai->m_command.aiExit(NULL, CMD_FROM_SCRIPT);
	}
}
