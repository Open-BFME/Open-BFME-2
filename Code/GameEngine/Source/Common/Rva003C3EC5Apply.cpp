// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?Rva003C3EC5Apply@@YGXPAVParameter@@ABVAsciiString@@H@Z @0x003C3EC5 97B: resolve unit via ScriptEngine then SpecialPowerTemplate by name filter via BfmeSubBEC then slot 0x20 virtual with scaled GameLogic frame. Evidence: sibling Rva003C3E75Apply same getUnitNamed 0x3588E7 via g_Va009FE16C findSpecialPowerTemplate 0x29B6EB via TheSpecialPowerStore BfmeSubBEC 0x28BB9E StringBase copy 0x365F0; caller 0x003CC68F; ret 0xC stdcall.
#include "ascii_string.h"

class Parameter;
class Object;
class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *p);
};

extern class ScriptEngine *TheScriptEngine;

class SpecialPowerTemplate;
class SpecialPowerStore
{
public:
	const SpecialPowerTemplate *findSpecialPowerTemplate(AsciiString name);
};

extern SpecialPowerStore *TheSpecialPowerStore;

class BfmeSubBEC
{
public:
	void *rva0028BB9E(void *found);
};

extern int g_Va00DBA4E4;

class GameLogic
{
public:
	char m_pad00[0x40];
	int m_40;
};

extern GameLogic *TheGameLogic;

class Rva003C3EC5Target
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
	virtual void w08(int arg);
};

void __stdcall Rva003C3EC5Apply(Parameter *p, const AsciiString &name, int arg3)
{
	Object *obj = TheScriptEngine->getUnitNamed(p);
	const SpecialPowerTemplate *found = TheSpecialPowerStore->findSpecialPowerTemplate(name);
	if (obj != 0 && found != 0)
	{
		void *sub = ((BfmeSubBEC *)obj)->rva0028BB9E((void *)found);
		if (sub != 0)
			((Rva003C3EC5Target *)sub)->w08(g_Va00DBA4E4 * arg3 + TheGameLogic->m_40);
	}
}
