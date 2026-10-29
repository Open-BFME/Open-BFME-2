// stlport
// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD
#include "GameLogic/ScriptActionsBFME2.h"
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BD032Set@ScriptActions@@QAEXPAVParameter@@PAX@Z, retail 0x003BD032 48B leaf via rowed 0x003588E7 0x00290963 0x00290A10.
// Unit-named weapon-set switch: obj = g_Va009FE16C->getUnitNamed(p1); if obj then set/clear 0x17 by *(int*)(p2+8).
// Evidence: callees rowed; caller 0x003CE407; prev 0x003BCFC9 next 0x003BD153 same /O1.
class Parameter;
class Object;
enum WeaponSetType
{
	WEAPONSET_23 = 0x17
};
class Object
{
public:
	void setWeaponSetFlag(WeaponSetType wst);
	void clearWeaponSetFlag(WeaponSetType wst);
};
#include "../../../Include/GameLogic/ScriptEngine.h"
extern class ScriptEngine *TheScriptEngine;

void ScriptActions::Rva003BD032Set(Parameter *parameter, void *p2)
{
	Object *obj = TheScriptEngine->getUnitNamed(parameter);
	if (obj == 0)
		return;
	if (*(int *)((char *)p2 + 8) > 0)
		obj->setWeaponSetFlag((WeaponSetType)0x17);
	else
		obj->clearWeaponSetFlag((WeaponSetType)0x17);
}

// Member ABI proved at each native executeAction3CA4BE call site: ECX=this.
// Canonical ScriptActions owner; address-derived verbs remain uncertain.
