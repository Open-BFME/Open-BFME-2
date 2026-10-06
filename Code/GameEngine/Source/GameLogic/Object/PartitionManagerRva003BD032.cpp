// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BD032Set@@YGXPAVParameter@@PAX@Z, retail 0x003BD032 48B leaf via rowed 0x003588E7 0x00290963 0x00290A10.
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
class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *p);
};
extern class ScriptEngine *TheScriptEngine;

void __stdcall Rva003BD032Set(Parameter *p1, void *p2)
{
	Object *obj = TheScriptEngine->getUnitNamed(p1);
	if (obj == 0)
		return;
	if (*(int *)((char *)p2 + 8) > 0)
		obj->setWeaponSetFlag((WeaponSetType)0x17);
	else
		obj->clearWeaponSetFlag((WeaponSetType)0x17);
}
