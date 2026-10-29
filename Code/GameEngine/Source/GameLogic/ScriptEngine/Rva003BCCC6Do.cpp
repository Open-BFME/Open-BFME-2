// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BCCC6Do@ScriptActions@@QAEXPAVParameter@@0@Z @0x003BCCC6 85B: script action firing special power 0x2d from first named unit at second.
// Evidence: two rowed getUnitNamed 0x003588E7 via TheScriptEngine then rowed findSpecialPowerModuleInterface 0x00290E22 with 0x2d then slot 1 gate then slot 11 with (target 2); stdcall ret 8 same as doDestroyAllContained sibling; caller 0x003CDCBB in dispatch.
class Parameter;
class Object;

class SpecialPowerModuleInterface
{
public:
	virtual void s00();
	virtual bool isReady();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void doSpecialPowerAtObject(Object *target, int value);
};

enum SpecialPowerType
{
	SPECIAL_INVALID = 0
};

class Object
{
public:
	SpecialPowerModuleInterface *findSpecialPowerModuleInterface(SpecialPowerType type) const;
};

#include "../../../Include/GameLogic/ScriptEngine.h"

extern ScriptEngine *TheScriptEngine;

void ScriptActions::Rva003BCCC6Do(Parameter *parameter, Parameter *b)
{
	Object *object = TheScriptEngine->getUnitNamed(parameter);
	Object *u2 = TheScriptEngine->getUnitNamed(b);
	if (object == 0 || u2 == 0)
		return;
	SpecialPowerModuleInterface *sp = object->findSpecialPowerModuleInterface((SpecialPowerType)0x2d);
	if (sp == 0)
		return;
	if (!sp->isReady())
		return;
	sp->doSpecialPowerAtObject(u2, 2);
}
