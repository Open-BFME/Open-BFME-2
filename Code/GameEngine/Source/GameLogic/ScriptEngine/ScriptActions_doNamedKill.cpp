// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?doNamedKill@ScriptActions@@QAEXPAVParameter@@@Z @0x003BB4F7 33B leaf caller 0x003CBA4F callees getUnitNamed kill
// Evidence: ScriptEngine getUnitNamed then Object kill 8 0.
enum DamageType { DAMAGE_8 = 8 };
enum DeathType { DEATH_0 = 0 };
class Object
{
public:
	void kill(DamageType a, DeathType b);
};
class Parameter;
#include "../../../Include/GameLogic/ScriptEngine.h"
extern class ScriptEngine *TheScriptEngine;
void ScriptActions::doNamedKill(Parameter *parameter)
{
	Object *object = TheScriptEngine->getUnitNamed(parameter);
	if (!object)
		return;
	object->kill((DamageType)8, (DeathType)0);
}
