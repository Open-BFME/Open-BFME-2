// FILE: BehaviorModule.h ////////////////////////////////////////////////////////////////////////
// Desc:   Canonical BFME2 BehaviorModuleInterface and BehaviorModule.
//
// Target facts:
//  - ??0BehaviorModule (0x00253330) calls ??0ObjectModule, then stores the
//    interface's own table 0x00BEE900 and its BehaviorModule table 0x00BEE9C0 at
//    +0x0C and the primary table 0x00BEEA7C at +0: sizeof 0x10.
//  - 0x00BEE900 holds exactly 47 __purecall slots (0x00BEEA7C follows 0x00BEE9C0
//    after 47 entries; the interface has no virtual destructor). In 0x00BEE9C0
//    slots 0-42 are 0x000D43D0 `xor eax,eax; ret` (getters returning NULL),
//    43, 45 and 46 are 0x0047A69C `ret 4` and 44 is 0x000B3FD0 `ret`.
//  - Each module family overrides one getter (the classes' constructors store their
//    own +0x0C tables): body modules slot 0, collides 1, contains 2, creates 3,
//    damages 4, dies 7 (DieModule's 0x002533D3 returns its +0x10
//    DieModuleInterface), special powers 8, updates 9, upgrades 10, AI updates 19.
//  - The primary table 0x00BEEA7C is ObjectModule's ten slots plus two of
//    BehaviorModule's own, both 0x000D43D0 (returning 0).
//  - ~DieModule (0x0045CE54) restores 0x00BEEA7C and 0x00BEE9C0 inline: the
//    BehaviorModule destructor is inline and empty.
// Donor (Zero Hour BehaviorModule.h) facts: the getter names. Zero Hour's order
// has getDestroy at 5 and getDie at 6; BFME2's dies override slot 7, so one slot
// was added before getDie. Only the slots a family's override pins carry a name;
// the rest are placeholders (slotNN, vslot10/11) until evidence names them.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __BFME2_BEHAVIORMODULE_H_
#define __BFME2_BEHAVIORMODULE_H_

#include "../../Common/ObjectModule.h"

class AIUpdateInterface;
class BodyModuleInterface;
class CollideModuleInterface;
class ContainModuleInterface;
class CreateModuleInterface;
class DamageModuleInterface;
class DieModuleInterface;
class SpecialPowerModuleInterface;
class UpdateModuleInterface;
class UpgradeModuleInterface;

//-------------------------------------------------------------------------------------------------
class BehaviorModuleInterface
{
public:
	virtual BodyModuleInterface *getBody() = 0;			// 0
	virtual CollideModuleInterface *getCollide() = 0;			// 1
	virtual ContainModuleInterface *getContain() = 0;			// 2
	virtual CreateModuleInterface *getCreate() = 0;			// 3
	virtual DamageModuleInterface *getDamage() = 0;			// 4
	virtual void *slot05() = 0;			// 5
	virtual void *slot06() = 0;			// 6
	virtual DieModuleInterface *getDie() = 0;			// 7
	virtual SpecialPowerModuleInterface *getSpecialPower() = 0;			// 8
	virtual UpdateModuleInterface *getUpdate() = 0;			// 9
	virtual UpgradeModuleInterface *getUpgrade() = 0;			// 10
	virtual void *slot11() = 0;			// 11
	virtual void *slot12() = 0;			// 12
	virtual void *slot13() = 0;			// 13
	virtual void *slot14() = 0;			// 14
	virtual void *slot15() = 0;			// 15
	virtual void *slot16() = 0;			// 16
	virtual void *slot17() = 0;			// 17
	virtual void *slot18() = 0;			// 18
	virtual AIUpdateInterface *getAIUpdateInterface() = 0;			// 19
	virtual void *slot20() = 0;			// 20
	virtual void *slot21() = 0;			// 21
	virtual void *slot22() = 0;			// 22
	virtual void *slot23() = 0;			// 23
	virtual void *slot24() = 0;			// 24
	virtual void *slot25() = 0;			// 25
	virtual void *slot26() = 0;			// 26
	virtual void *slot27() = 0;			// 27
	virtual void *slot28() = 0;			// 28
	virtual void *slot29() = 0;			// 29
	virtual void *slot30() = 0;			// 30
	virtual void *slot31() = 0;			// 31
	virtual void *slot32() = 0;			// 32
	virtual void *slot33() = 0;			// 33
	virtual void *slot34() = 0;			// 34
	virtual void *slot35() = 0;			// 35
	virtual void *slot36() = 0;			// 36
	virtual void *slot37() = 0;			// 37
	virtual void *slot38() = 0;			// 38
	virtual void *slot39() = 0;			// 39
	virtual void *slot40() = 0;			// 40
	virtual void *slot41() = 0;			// 41
	virtual void *slot42() = 0;			// 42
	virtual void slot43(int) = 0;			// 43
	virtual void slot44() = 0;			// 44
	virtual void slot45(int) = 0;			// 45
	virtual void slot46(int) = 0;			// 46
};

//-------------------------------------------------------------------------------------------------
class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	BehaviorModule( Thing *thing, const ModuleData *moduleData );
	virtual ~BehaviorModule() { }

	virtual void *vslot10() { return 0; }			// primary slot 10
	virtual void *vslot11() { return 0; }			// primary slot 11

	virtual BodyModuleInterface *getBody() { return 0; }
	virtual CollideModuleInterface *getCollide() { return 0; }
	virtual ContainModuleInterface *getContain() { return 0; }
	virtual CreateModuleInterface *getCreate() { return 0; }
	virtual DamageModuleInterface *getDamage() { return 0; }
	virtual void *slot05() { return 0; }
	virtual void *slot06() { return 0; }
	virtual DieModuleInterface *getDie() { return 0; }
	virtual SpecialPowerModuleInterface *getSpecialPower() { return 0; }
	virtual UpdateModuleInterface *getUpdate() { return 0; }
	virtual UpgradeModuleInterface *getUpgrade() { return 0; }
	virtual void *slot11() { return 0; }
	virtual void *slot12() { return 0; }
	virtual void *slot13() { return 0; }
	virtual void *slot14() { return 0; }
	virtual void *slot15() { return 0; }
	virtual void *slot16() { return 0; }
	virtual void *slot17() { return 0; }
	virtual void *slot18() { return 0; }
	virtual AIUpdateInterface *getAIUpdateInterface() { return 0; }
	virtual void *slot20() { return 0; }
	virtual void *slot21() { return 0; }
	virtual void *slot22() { return 0; }
	virtual void *slot23() { return 0; }
	virtual void *slot24() { return 0; }
	virtual void *slot25() { return 0; }
	virtual void *slot26() { return 0; }
	virtual void *slot27() { return 0; }
	virtual void *slot28() { return 0; }
	virtual void *slot29() { return 0; }
	virtual void *slot30() { return 0; }
	virtual void *slot31() { return 0; }
	virtual void *slot32() { return 0; }
	virtual void *slot33() { return 0; }
	virtual void *slot34() { return 0; }
	virtual void *slot35() { return 0; }
	virtual void *slot36() { return 0; }
	virtual void *slot37() { return 0; }
	virtual void *slot38() { return 0; }
	virtual void *slot39() { return 0; }
	virtual void *slot40() { return 0; }
	virtual void *slot41() { return 0; }
	virtual void *slot42() { return 0; }
	virtual void slot43(int) { }
	virtual void slot44() { }
	virtual void slot45(int) { }
	virtual void slot46(int) { }
};

#endif // __BFME2_BEHAVIORMODULE_H_
