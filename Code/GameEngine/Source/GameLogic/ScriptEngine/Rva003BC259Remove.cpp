// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BC259Remove@@YGXPAVParameter@@@Z @0x003BC259 34B: script action removing sequential scripts for a named unit.
// Evidence: calls rowed getUnitNamed 0x003588E7 with Parameter* then rowed ScriptEngine::rva0020517D 0x0020517D on the Object*; same TheScriptEngine global and stdcall shape as Rva003BE26DGrantUpgrade; caller 0x003CCE3E in dispatch.
class Parameter;
class Object;

class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *param);
	void rva0020517D(Object *obj);
};

extern ScriptEngine *TheScriptEngine;

void __stdcall Rva003BC259Remove(Parameter *param)
{
	Object *obj = TheScriptEngine->getUnitNamed(param);
	if (obj == 0)
		return;
	TheScriptEngine->rva0020517D(obj);
}
