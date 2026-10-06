// cl: /DNDEBUG /MD /EHsc
//
// ?Rva003C90B1Exit@@YGXPAVParameter@@@Z @0x003C90B1 44B: free stdcall helper
// resolving a unit via rowed getUnitNamed 0x003588E7 then issuing rowed aiExit
// 0x0036F39B with null object and script source. Evidence: caller 0x003CC1F4,
// Object+0x258 AIUpdateInterface, command +0x20.
class Parameter;
class Object;
enum CommandSourceType { CMD_FROM_SCRIPT = 1 };

class AICommandInterface
{
public:
	void aiExit(Object *obj, CommandSourceType src);
};

class AIUpdateInterface
{
public:
	char m_pad[0x20];
	AICommandInterface m_command; // +0x20
};

class Object
{
public:
	AIUpdateInterface *getAI() const { return *(AIUpdateInterface **)((const char *)this + 0x258); }
};

class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *param);
};
extern ScriptEngine *TheScriptEngine;


void __stdcall Rva003C90B1Exit(Parameter *param)
{
	Object *obj = TheScriptEngine->getUnitNamed(param);
	if (!obj)
		return;
	AIUpdateInterface *ai = obj->getAI();
	if (!ai)
		return;
	ai->m_command.aiExit(0, CMD_FROM_SCRIPT);
}
