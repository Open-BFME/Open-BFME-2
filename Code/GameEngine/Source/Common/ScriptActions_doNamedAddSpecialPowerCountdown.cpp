// stlport
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD
#include "GameLogic/ScriptActionsBFME2.h"
// ?doNamedAddSpecialPowerCountdown@ScriptActions@@QAEXPAVParameter@@ABVAsciiString@@H@Z @0x003C3F9E 101B: resolve unit via ScriptEngine then SpecialPowerTemplate by name query Object special-power module then slot 0x10 plus scaled frame via slot 0x20. Evidence: sibling doNamedSetSpecialPowerCountdown same getUnitNamed 0x3588E7 via g_Va009FE16C findSpecialPowerTemplate 0x29B6EB via TheSpecialPowerStore Object::getSpecialPowerModule 0x28BB9E StringBase copy 0x365F0; caller 0x003CC6BD; ret 0xC stdcall.
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

extern int BfmeLogicFramesPerSecond;

class Rva003C3F9ETarget
{
public:
	virtual void w00();
	virtual void w01();
	virtual void w02();
	virtual void w03();
	virtual int w04();
	virtual void w05();
	virtual void w06();
	virtual void w07();
	virtual void w08(int arg);
};

void ScriptActions::doNamedAddSpecialPowerCountdown(Parameter *parameter, const AsciiString &name, int seconds)
{
	Object *obj = TheScriptEngine->getUnitNamed(parameter);
	const SpecialPowerTemplate *found = TheSpecialPowerStore->findSpecialPowerTemplate(name);
	if (obj != 0 && found != 0)
	{
		Rva003C3F9ETarget *m_specialPowerModule = (Rva003C3F9ETarget *)obj->getSpecialPowerModule(found);
		if (m_specialPowerModule != 0)
		{
			int scaled = BfmeLogicFramesPerSecond * seconds;
			m_specialPowerModule->w08(m_specialPowerModule->w04() + scaled);
		}
	}
}

// Member ABI proved at each native executeAction3CA4BE call site: ECX=this.
// Canonical ScriptActions owner; address-derived verbs remain uncertain.
