// stlport
// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD
#include "GameLogic/ScriptActionsBFME2.h"
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?doUnitStopSequentialScript@ScriptActions@@QAEXPAVParameter@@@Z @0x003BC259 34B: script action removing sequential scripts for a named unit.
// Evidence: calls rowed getUnitNamed 0x003588E7 with Parameter* then rowed ScriptEngine::rva0020517D 0x0020517D on the Object*; same TheScriptEngine global and stdcall shape as Rva003BE26DGrantUpgrade; caller 0x003CCE3E in dispatch.
class Parameter;
class Object;

#include "../../../Include/GameLogic/ScriptEngine.h"

extern ScriptEngine *TheScriptEngine;

void ScriptActions::doUnitStopSequentialScript(Parameter *param)
{
	Object *obj = TheScriptEngine->getUnitNamed(param);
	if (obj == 0)
		return;
	TheScriptEngine->rva0020517D(obj);
}

// Member ABI proved at each native executeAction3CA4BE call site: ECX=this.
// Canonical ScriptActions owner; address-derived verbs remain uncertain.
