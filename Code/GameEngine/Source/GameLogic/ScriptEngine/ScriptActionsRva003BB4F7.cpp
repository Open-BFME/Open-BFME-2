// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BB4F7Kill@@YGXPAVParameter@@@Z @0x003BB4F7 33B leaf caller 0x003CBA4F callees getUnitNamed kill
// Evidence: ScriptEngine getUnitNamed then Object kill 8 0.
enum DamageType { DAMAGE_8 = 8 };
enum DeathType { DEATH_0 = 0 };
class Object
{
public:
	void kill(DamageType a, DeathType b);
};
class Parameter;
class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *p);
};
extern class ScriptEngine *TheScriptEngine;
void __stdcall Rva003BB4F7Kill(Parameter *p)
{
	Object *o = TheScriptEngine->getUnitNamed(p);
	if (!o)
		return;
	o->kill((DamageType)8, (DeathType)0);
}
