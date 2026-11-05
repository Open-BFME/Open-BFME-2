// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ?triggerAbilityEffect@ScaleWallSpecialAbilityUpdate@@UAEXXZ, retail 0x00494E26, 34 bytes.
// Slot 17 of the vftable 0x00C4EB40 whose slot-2 name getter returns
// "ScaleWallSpecialAbilityUpdate". Runs the base SpecialAbilityUpdate slot 17
// (pinned triggerAbilityEffect, whose address name it carries so cl 7.1 places it in
// slot 17), then hands 1.0f to slot 15 of the special-power module the rowed
// lookup 0x0044E633 finds for this ability (ZH's getMySPM shape: the owner's
// module for module data +0x38). Method identity not established.

#include "../../../../Include/GameLogic/Module/SpecialAbilityUpdate.h"
#include "../../../../Include/GameLogic/Module/SpecialPowerModule.h"

class Rva0044E633
{
public:
	void *rva0044E633();
};

class ScaleWallSpecialAbilityUpdate : public SpecialAbilityUpdate
{
public:
	virtual void triggerAbilityEffect();
};

// ?triggerAbilityEffect@ScaleWallSpecialAbilityUpdate@@UAEXXZ @0x00494E26
void ScaleWallSpecialAbilityUpdate::triggerAbilityEffect()
{
	SpecialAbilityUpdate::triggerAbilityEffect();
	SpecialPowerModuleInterface *spm = (SpecialPowerModuleInterface *)((Rva0044E633 *)this)->rva0044E633();
	if (spm)
		spm->startPowerRecharge(1.0f);
}
