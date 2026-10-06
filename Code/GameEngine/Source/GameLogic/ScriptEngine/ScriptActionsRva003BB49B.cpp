// cl: /O1
// ?Rva003BB49BDestroy@@YGXPAVParameter@@@Z @0x003BB49B 34B leaf caller 0x003CB8F1 callees getUnitNamed destroyObject
// Evidence: ScriptEngine getUnitNamed then GameLogic destroyObject.
class Object;
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
