// stlport
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD
#include "GameLogic/ScriptActionsBFME2.h"
// ?doNamedStopSpecialPowerCountdown@ScriptActions@@QAEXPAVParameter@@ABVAsciiString@@PAX@Z @0x003C3E75 80B: resolve unit via ScriptEngine then SpecialPowerTemplate by name query Object special-power module then slot 0x24 virtual. Evidence: sibling doNamedFireSpecialPowerAtWaypoint same getUnitNamed 0x3588E7 via g_Va009FE16C findSpecialPowerTemplate 0x29B6EB via TheSpecialPowerStore Object::getSpecialPowerModule 0x28BB9E StringBase copy 0x365F0; caller 0x003CC661; ret 0xC stdcall.
#include "ascii_string.h"

class SpecialPowerTemplate;
class SpecialPowerModuleInterface;

class Object
{
public:
	SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate *power) const;
};

class Parameter;
class Object;
#include "../../Include/GameLogic/ScriptEngine.h"

extern class ScriptEngine *TheScriptEngine;

class SpecialPowerTemplate;
class SpecialPowerStore
{
public:
	const SpecialPowerTemplate *findSpecialPowerTemplate(AsciiString name);
};

extern SpecialPowerStore *TheSpecialPowerStore;

class Rva003C3E75Target
{
public:
	virtual void w00();
	virtual void w01();
	virtual void w02();
	virtual void w03();
	virtual void w04();
	virtual void w05();
	virtual void w06();
	virtual void w07();
	virtual void w08();
	virtual void w09(void *arg);
};

void ScriptActions::doNamedStopSpecialPowerCountdown(Parameter *parameter, const AsciiString &name, void *arg3)
{
	Object *obj = TheScriptEngine->getUnitNamed(parameter);
	const SpecialPowerTemplate *found = TheSpecialPowerStore->findSpecialPowerTemplate(name);
	if (obj != 0 && found != 0)
	{
		void *sub = obj->getSpecialPowerModule(found);
		if (sub != 0)
			((Rva003C3E75Target *)sub)->w09(arg3);
	}
}

// Member ABI proved at each native executeAction3CA4BE call site: ECX=this.
// Canonical ScriptActions owner; address-derived verbs remain uncertain.
