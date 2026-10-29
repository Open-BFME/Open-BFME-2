// cl: -O1 -arch:SSE -G7 -DNDEBUG -MD -EHsc -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// ?Rva003C89D1Guard@ScriptActions@@QAEXPAVParameter@@0@Z retail 0x003C89D1 68B
// Evidence: abuts 0x003C8964 doUnitGuardPosition; caller 0x003CB695; rowed getUnitNamed 0x003588E7 plus aiGuardObject guard plus AI +0x258 +0x20
class Parameter;
class Object;
enum CommandSourceType { CMD_FROM_SCRIPT = 1 };

class AICommandInterface
{
public:
	void aiGuardObject(Object *obj, int mode, CommandSourceType src);
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

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;


void ScriptActions::Rva003C89D1Guard(Parameter *parameter, Parameter *p2)
{
	Object *object = TheScriptEngine->getUnitNamed(p2);
	Object *o1 = TheScriptEngine->getUnitNamed(parameter);
	if (!o1)
		return;
	AIUpdateInterface *ai = o1->getAI();
	if (!ai)
		return;
	if (!object)
		return;
	ai->m_command.aiGuardObject(object, 0, CMD_FROM_SCRIPT);
}
