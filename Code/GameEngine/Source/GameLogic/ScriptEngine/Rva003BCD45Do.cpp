// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?Rva003BCD45Do@@YGXPAVParameter@@@Z @0x003BCD45 146B: gate behavior triple-check.
// Evidence: getUnitNamed 0x003588E7 then static gateKey via TheNameKeyGenerator nameToKey GateOpenAndCloseBehavior then findModule 0x0028B6D6 then gate-4 view with slots 0x18 0x28 0x20 bool checks; globals g_Va009FE16C TheNameKeyGenerator; ret 4; caller 0x003CDDAC.

#include "ascii_string.h"

class Parameter;
class Module
{
public:
	virtual void m0();
};
enum NameKeyType {};
class Object
{
protected:
	Module *findModule(NameKeyType key) const;
	friend void __stdcall Rva003BCD45Do(Parameter *param);
};
class GateView
{
public:
	virtual void g0(); virtual void g1(); virtual void g2(); virtual void g3(); virtual void g4(); virtual void g5();
	virtual bool s18();
	virtual void g7();
	virtual bool s20();
	virtual void g9();
	virtual bool s28();
};
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;
class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *param);
};
extern class ScriptEngine *TheScriptEngine;

void __stdcall Rva003BCD45Do(Parameter *param)
{
	Object *obj = TheScriptEngine->getUnitNamed(param);
	if (!obj)
		return;
	static NameKeyType gateKey = TheNameKeyGenerator->nameToKey("GateOpenAndCloseBehavior");
	Module *module = obj->findModule(gateKey);
	GateView *gate = module ? reinterpret_cast<GateView *>(reinterpret_cast<unsigned char *>(module) - 4) : 0;
	if (!gate)
		return;
	if (!gate->s18())
		return;
	if (!gate->s28())
		return;
	gate->s20();
}
