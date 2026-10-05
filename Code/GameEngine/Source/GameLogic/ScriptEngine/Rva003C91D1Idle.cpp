// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
//
// ?Rva003C91D1Idle@@YGXPAVParameter@@@Z, retail 0x003C91D1 53 bytes.
// Free stdcall helper resolving a unit via rowed getUnitNamed 0x003588E7
// then releasing weapon lock via rowed releaseWeaponLock 0x0028D8B6 with
// TEMPORARILY and issuing rowed aiIdle 0x001E8A38 with script source.
// Evidence: caller 0x003CC881 in unclaimed dispatch, Object+0x258
// AIUpdateInterface, command +0x20. Same shape as Rva003C90B1Exit.
class Parameter;
class Object;

enum CommandSourceType { CMD_FROM_SCRIPT = 1 };
enum WeaponLockType { NOT_LOCKED, LOCKED_TEMPORARILY, LOCKED_PERMANENTLY };

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType src);
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
	void releaseWeaponLock(WeaponLockType lockType);
};

class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *param);
};
extern ScriptEngine *g_Va009FE16C;

void __stdcall Rva003C91D1Idle(Parameter *param)
{
	Object *obj = g_Va009FE16C->getUnitNamed(param);
	if (!obj)
		return;
	AIUpdateInterface *ai = obj->getAI();
	if (!ai)
		return;
	obj->releaseWeaponLock(LOCKED_TEMPORARILY);
	ai->m_command.aiIdle(CMD_FROM_SCRIPT);
}
