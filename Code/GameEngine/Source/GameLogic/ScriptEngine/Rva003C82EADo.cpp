// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
//
// ?Rva003C82EADo@@YGXPAVParameter@@0@Z @0x003C82EA (103B).
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

class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *param);
};
extern ScriptEngine *TheScriptEngine;

void __stdcall Rva003C82EADo(Parameter *p1, Parameter *p2)
{
	Object *o1 = TheScriptEngine->getUnitNamed(p1);
	Object *o2 = TheScriptEngine->getUnitNamed(p2);
	if (!o1)
		return;
	if (!o2)
		return;
	AIUpdateInterface *ai = o1->getAI();
	if (!ai)
		return;
	o1->leaveGroup();
	if ((unsigned char)o1->rva0028B38D())
		ai->m_command.rva0036EFF5(o2, CMD_FROM_SCRIPT);
	else
		ai->m_command.rva0026C2D9(o2, 0x7FFFFFFF, CMD_FROM_SCRIPT);
}
