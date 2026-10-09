// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BB49BDestroy@@YGXPAVParameter@@@Z @0x003BB49B 34B leaf caller 0x003CB8F1 callees getUnitNamed destroyObject
// Evidence: ScriptEngine getUnitNamed then GameLogic destroyObject.
// ?Rva003BB4BDApply@@YGXPAVParameter@@MMMH@Z @0x003BB4BD 58B, the next
// action case of the same dispatcher (caller 0x003CBA3A): getUnitNamed, then
// the unnamed Object method at 0x00291A8C with three floats and an int.
class Object
{
public:
	void rva00291A8C(float a, float b, float c, int d);
};
class Parameter;
class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *p);
};
extern class ScriptEngine *TheScriptEngine;
class GameLogic
{
public:
	void destroyObject(Object *o);
};
extern GameLogic *TheGameLogic;
void __stdcall Rva003BB49BDestroy(Parameter *p)
{
	Object *o = TheScriptEngine->getUnitNamed(p);
	if (!o)
		return;
	TheGameLogic->destroyObject(o);
}
void __stdcall Rva003BB4BDApply(Parameter *p, float a, float b, float c, int d)
{
	Object *o = TheScriptEngine->getUnitNamed(p);
	if (!o)
		return;
	o->rva00291A8C(a, b, c, d);
}
