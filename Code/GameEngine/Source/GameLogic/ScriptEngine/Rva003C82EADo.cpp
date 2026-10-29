// cl: -O1 -arch:SSE -G7 -DNDEBUG -MD -EHsc -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
//
// ?Rva003C82EADo@ScriptActions@@QAEXPAVParameter@@0@Z @0x003C82EA (103B).
// Two-unit guard/attack via getUnitNamed plus leaveGroup plus rva0028B38D
// test plus rva0036EFF5 else rva0026C2D9. Evidence: callees rowed getUnitNamed
// 0x003588E7 leaveGroup 0x0028C01F rva0028B38D 0x0028B38D, caller 0x003CB27E.
// Precedent Rva003C89D1Guard.
class Parameter;
class Object;
enum CommandSourceType { CMD_FROM_SCRIPT = 1 };

class AICommandInterface
{
public:
	void rva0036EFF5(Object *obj, CommandSourceType src);
	void rva0026C2D9(Object *obj, int x, CommandSourceType src);
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
	void leaveGroup();
	int rva0028B38D() const;
	AIUpdateInterface *getAI() const { return *(AIUpdateInterface **)((const char *)this + 0x258); }
};

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

void ScriptActions::Rva003C82EADo(Parameter *parameter, Parameter *p2)
{
	Object *object = TheScriptEngine->getUnitNamed(parameter);
	Object *o2 = TheScriptEngine->getUnitNamed(p2);
	if (!object)
		return;
	if (!o2)
		return;
	AIUpdateInterface *ai = object->getAI();
	if (!ai)
		return;
	object->leaveGroup();
	if ((unsigned char)object->rva0028B38D())
		ai->m_command.rva0036EFF5(o2, CMD_FROM_SCRIPT);
	else
		ai->m_command.rva0026C2D9(o2, 0x7FFFFFFF, CMD_FROM_SCRIPT);
}
