// FILE: SpecialPowerUpdateInterface.h ////////////////////////////////////////////////////////////
// Desc:   Canonical BFME2 SpecialPowerUpdateInterface.
//
// Target facts (code addresses are RVAs, table addresses VAs):
//  - The construction table 0x00C6F248 holds nine __purecall (0x0003B810) slots;
//    the next stored table 0x00C6F26C (store 0x0057BD12) starts after them.
//    SpecialAbilityUpdate (0x0044EF5E, store 0x0044EF7E), BattlePlanUpdate
//    (0x00497ED0, 0x00497EFA) and WeaponModeSpecialPowerUpdateBase (0x0058959A,
//    0x005895BB) store it at +0x20, then their own tables 0x00C552A4 (0x0044EF9D),
//    0x00C4FB7C (0x00497F20) and 0x00C7016C (0x005895E4). Destructor 0x00451F45
//    restores 0x00C552A4 (0x00451F6A). Other nine-slot interfaces share the folded
//    table (SlavedUpdate's constructor stores it at 0x004A18D8).
//  - Slot 0 of every implementation table is the intent method (0x004500A3,
//    0x004C6133): no virtual destructor. The interface has no base and no data:
//    implementers put its vptr at +0x20 after UpdateModule's 0x20 bytes and their
//    own fields at +0x24 (0x0044EFA4, 0x00497F48), so sizeof is 4.
//  - Slot 0: SpecialAbilityUpdate::initiateIntentToDoSpecialPower 0x004500A3,
//    five arguments, ret 20, no result.
//  - Slot 1: Object::findSpecialAbilityUpdate (0x0028BD92) calls it at 0x0028BDAE
//    and accepts the module on true; SpecialAbilityUpdate answers true (0x0050B5C6).
//  - Slot 2: SquishCollide::onCollide calls it at 0x004BBC8E on the result of
//    findSpecialAbilityUpdate(0x19) and returns on true (also 0x003E8CC4,
//    0x00495884). SpecialAbilityUpdate answers byte +0x74 (0x005C4AE5),
//    BattlePlanUpdate +0x30 != 0 (0x00497960). WeaponModeSpecialPowerUpdateBase's
//    slot 6 (0x00494ABE) returns this slot's answer.
//  - Slot 3: BattlePlanUpdate::getCommandOption (0x0049771E) fills it in
//    0x00C4FB7C; SpecialAbilityUpdate answers 0 (0x000D43D0).
//  - Slot 4: Object 0x0028BD5D returns the first module interface whose slot 4
//    answers true (0x0028BD79); groupOverrideSpecialPowerDestination (0x0036E20F)
//    and canOverrideSpecialPowerDestination (0x0041BB51) call that finder.
//  - Slot 5: groupOverrideSpecialPowerDestination (0x0036E1F7) passes its
//    destination to it at 0x0036E220. SpecialAbilityUpdate's body is ret 4.
//  - Slot 6: 0x0044EECA reads the button argument's +0x44 and +0x1D (ret 4).
//    0x0045028A/0x00450297 and 0x00293134/0x00293145 call slot 6 with null after
//    slot 1 answers true.
//  - Slot 7: SpecialPowerModule passes its module data's +8 word at 0x004946D0 and
//    0x004947BB and takes the first interface that answers true;
//    SpecialAbilityUpdate compares it with its module data's +0x38 (0x0044F09F).
//  - Slot 8: SpecialAbilityUpdate 0x0044EDA6 (one dword argument, ret 4);
//    ToggleDeploySpecialAbilityUpdate calls it with 0 at 0x004AE6F1.
// Donor (Zero Hour SpecialPowerUpdateModule.h) facts: the names of slots 0-6. Zero
// Hour's Object::findSpecialAbilityUpdate tests isSpecialAbility, SquishCollide
// tests isActive on that result, and groupOverrideSpecialPowerDestination and
// canOverrideSpecialPowerDestination find the interface whose
// doesSpecialPowerHaveOverridableDestinationActive answers true. Retail sets the
// intent method's void result and argument order and the slot order; slots 7 and 8
// have no donor name.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __BFME2_SPECIALPOWERUPDATEINTERFACE_H_
#define __BFME2_SPECIALPOWERUPDATEINTERFACE_H_

class SpecialPowerTemplate;
class Object;
struct Coord3D;
class Waypoint;
class CommandButton;
enum CommandOption;

class SpecialPowerUpdateInterface
{
public:
	virtual void initiateIntentToDoSpecialPower(const SpecialPowerTemplate *specialPowerTemplate,
		const Object *targetObj, const Coord3D *targetPos, unsigned int commandOptions,
		const Waypoint *way) = 0;
	virtual bool isSpecialAbility() const = 0;
	virtual bool isActive() const = 0;
	virtual CommandOption getCommandOption() const = 0;
	virtual bool doesSpecialPowerHaveOverridableDestinationActive() const = 0;
	virtual void setSpecialPowerOverridableDestination(const Coord3D *loc) = 0;
	virtual bool isPowerCurrentlyInUse(const CommandButton *command = 0) const = 0;
	virtual bool vslot07(int) = 0;
	virtual bool vslot08(int) = 0;
};

#endif
