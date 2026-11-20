// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: WeaponModeSpecialPowerUpdate module ctor.
//
// UpdateModule supplies the +0, +0xC and +0x10 vfptrs and the fields through +0x1C.
// The remaining interfaces occupy +0x20 and +0x24. The next fields start at +0x28.
//
// The only body statement is the flag at +0x38, then the helper is put to sleep
// rather than woken: retail pushes 0x3FFFFFFF, not 1.

class Thing;
class ModuleData;
class Object;

#include "../../../../../../reference/open-bfme-1/game/GameEngine/Include/GameLogic/Module/UpdateSleepTime.h"





// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"
#include "../../../../Include/GameLogic/Module/UpdateModule.h"


class __declspec(novtable) WeaponModeSpecialPowerUpdateIface3
{
public:
	virtual void weaponModeIface3Anchor();
};

class __declspec(novtable) WeaponModeSpecialPowerUpdateIface4
{
public:
	virtual void weaponModeIface4Anchor();
};

class WeaponModeSpecialPowerUpdateBase : public UpdateModule
{
public:
	WeaponModeSpecialPowerUpdateBase(Thing *thing, const ModuleData *moduleData);
};

class WeaponModeSpecialPowerUpdate : public WeaponModeSpecialPowerUpdateBase, public WeaponModeSpecialPowerUpdateIface3, public WeaponModeSpecialPowerUpdateIface4
{
public:
	WeaponModeSpecialPowerUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~WeaponModeSpecialPowerUpdate();
	virtual UpdateSleepTime update();

protected:
	Object *getObject(void) const { return m_object; }

	unsigned char m_unreconstructed_28[0x10];
	bool m_38;									///< retail this+0x38
public:
	// retail slot 4: the rowed ?getModuleNameKey@WeaponModeSpecialPowerUpdate@@UBE?AW4NameKeyType@@XZ
	virtual NameKeyType getModuleNameKey() const;
};

// ??0WeaponModeSpecialPowerUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
WeaponModeSpecialPowerUpdate::WeaponModeSpecialPowerUpdate(Thing *thing, const ModuleData *moduleData)
	: WeaponModeSpecialPowerUpdateBase(thing, moduleData)
{
	m_38 = false;

	setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER);
}
