// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ?Rva003C8A95Do@@YGXPAVParameter@@@Z @0x003C8A95 (42B).
// Unit hunt via getUnitNamed plus AI +0x258 plus aiHunt.
// Evidence: callees rowed 0x003588E7 0x002AE657, caller 0x003CB71D.
// Precedent Rva003C8A15Do Rva003C89D1Guard.
class Parameter;
class Object;
enum CommandSourceType { CMD_FROM_SCRIPT = 1 };

class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *param);
};
extern ScriptEngine *g_Va009FE16C;

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

void __stdcall Rva003C8A95Do(Parameter *param)
{
	Object *obj = g_Va009FE16C->getUnitNamed(param);
	if (!obj)
		return;
	AIUpdateInterface *ai = obj->getAI();
	if (!ai)
		return;
	ai->m_command.aiHunt(CMD_FROM_SCRIPT);
}
