// stlport
// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD
#include "GameLogic/ScriptActionsBFME2.h"
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?doNamedDelete@ScriptActions@@QAEXPAVParameter@@@Z @0x003BB49B 34B leaf caller 0x003CB8F1 callees getUnitNamed destroyObject
// Evidence: ScriptEngine getUnitNamed then GameLogic destroyObject.
// ?Rva003BB4BDApply@ScriptActions@@QAEXPAVParameter@@MMMH@Z @0x003BB4BD 58B, the next
// action case of the same dispatcher (caller 0x003CBA3A): getUnitNamed, then
// the unnamed Object method at 0x00291A8C with three floats and an int.
// LINK: 0x00291A8C is rowed as Object::rva00291A8C(float, float, float, AsciiString const&) (the fourth word is that string's address).
class AsciiString;
class Object
{
public:
	void rva00291A8C(float a, float b, float c, const AsciiString &d);
};
class Parameter;
#include "../../../Include/GameLogic/ScriptEngine.h"
extern class ScriptEngine *TheScriptEngine;
#include "../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
void ScriptActions::doNamedDelete(Parameter *p)
{
	Object *o = TheScriptEngine->getUnitNamed(p);
	if (!o)
		return;
	TheGameLogic->destroyObject(o);
}
void ScriptActions::Rva003BB4BDApply(Parameter *p, float a, float b, float c, int d)
{
	Object *o = TheScriptEngine->getUnitNamed(p);
	if (!o)
		return;
	o->rva00291A8C(a, b, c, *(const AsciiString *)d);
}

// Member ABI proved at each native executeAction3CA4BE call site: ECX=this.
// Canonical ScriptActions owner; address-derived verbs remain uncertain.
