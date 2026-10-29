// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD -GX -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
//
// ?Rva003C8A95Do@ScriptActions@@QAEXPAVParameter@@@Z @0x003C8A95 (42B).
// Unit hunt via getUnitNamed plus AI +0x258 plus aiHunt.
// Evidence: callees rowed 0x003588E7 0x002AE657, caller 0x003CB71D.
// Precedent Rva003C8A15Do Rva003C89D1Guard.
class Parameter;
class Object;
enum CommandSourceType { CMD_FROM_SCRIPT = 1 };

#include "../../../Include/GameLogic/ScriptEngine.h"
extern class ScriptEngine *TheScriptEngine;

class AICommandInterface
{
public:
	void aiHunt(CommandSourceType src);
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

void ScriptActions::Rva003C8A95Do(Parameter *param)
{
	Object *obj = TheScriptEngine->getUnitNamed(param);
	if (!obj)
		return;
	AIUpdateInterface *ai = obj->getAI();
	if (!ai)
		return;
	ai->m_command.aiHunt(CMD_FROM_SCRIPT);
}
