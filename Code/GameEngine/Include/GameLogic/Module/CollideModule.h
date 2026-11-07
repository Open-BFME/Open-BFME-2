// FILE: CollideModule.h //////////////////////////////////////////////////////////////////////////
// Desc:   Canonical BFME2 CollideModuleInterface and CollideModule, written from retail's tables.
//         Every unit that emits a collide module's vftables includes this one declaration, so
//         their COMDAT copies of the base slots are identical.
//
// Target facts (code addresses are RVAs, vftables VAs):
//  - ??0CollideModule 0x004BB702 calls ??0BehaviorModule 0x00253330, stores the interface's own
//    table 0x00C40818 (six __purecall slots, no destructor slot) at +0x10, then 0x00C5A130 at +0,
//    0x00C5A040 at +0x0C and 0x00C5A00C at +0x10. The class adds no data (sizeof 0x14):
//    SquishCollide's constructor 0x004BB9CF stores nothing past its three vptrs.
//  - 0x00C5A130 (12 slots): deleting destructor 0x004BB739, loadPostProcess 0x0058B03E (the
//    shared tail jump to BehaviorModule::loadPostProcess), the name getter 0x004BB733
//    ("CollideModule"), xfer 0x004CE56D (Version1, then BehaviorModule::xfer 0x004C9C7D; one body
//    with DamageModule::xfer), getModuleNameKey __purecall, then BehaviorModule's slots 5..11.
//  - 0x00C5A040 (47 slots) differs from BehaviorModule's 0x00BEE9C0 only in slot 1, getCollide:
//    0x002533D3, the null-checked +0x0C -> +0x10 conversion UpdateModule's getUpdate shares.
//  - 0x00C5A00C (6 slots): __purecall, then 0x005CB9FF (`xor al,al; ret 4`) and four 0x0047A699
//    (`xor al,al; ret`).
//  - SalvageCrateCollide's collide table 0x00C5A9A8 replaces slot 5 with 0x0050B5C6
//    (`mov al,1; ret`); CrateCollide's 0x00C5A600 replaces slot 1 with 0x004BC51B, which adjusts
//    this to the complete object and jumps through primary slot 13 with the same argument.
// Donor (Zero Hour CollideModule.h / CollideModule.cpp) facts: the class and member names,
// getCollide returning this, the false defaults, and the out-of-line xfer (version 1, then the
// base) and loadPostProcess (the base call). Zero Hour's interface has seven slots (onCollide,
// wouldLikeToCollideWith, isHijackedVehicleCrateCollide, isSabotageBuildingCrateCollide,
// isCarBombCrateCollide, isRailroad, isSalvageCrateCollide); BFME2's has six and its slot 5 is
// the salvage-crate predicate (the one SalvageCrateCollide overrides), so one of Zero Hour's
// slots 2..5 is gone. Slots 2..4 keep neutral names until evidence says which remain.
// The name getter 0x004BB733 is rowed as the free-function scaffold ?Rva004BB733Get@@YAHXZ, so
// GetSnapshotName is not declared here; no rowed body names it as a member yet.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __BFME2_COLLIDEMODULE_H_
#define __BFME2_COLLIDEMODULE_H_

#include "BehaviorModule.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"

class Object;

//-------------------------------------------------------------------------------------------------
class CollideModuleInterface
{
public:
	virtual void onCollide( Object *other, const Coord3D *loc, const Coord3D *normal ) = 0;	// 0
	virtual bool wouldLikeToCollideWith( const Object *other ) const = 0;				// 1
	virtual bool slot02() const = 0;												// 2
	virtual bool slot03() const = 0;												// 3
	virtual bool slot04() const = 0;												// 4
	virtual bool isSalvageCrateCollide() const = 0;									// 5
};

//-------------------------------------------------------------------------------------------------
class CollideModule : public BehaviorModule, public CollideModuleInterface
{
public:
	CollideModule( Thing *thing, const ModuleData *moduleData );
	virtual ~CollideModule();

	virtual CollideModuleInterface *getCollide() { return this; }

	virtual bool wouldLikeToCollideWith( const Object *other ) const { return false; }
	virtual bool slot02() const { return false; }
	virtual bool slot03() const { return false; }
	virtual bool slot04() const { return false; }
	virtual bool isSalvageCrateCollide() const { return false; }

protected:
	virtual void loadPostProcess();										// primary slot 1
	virtual void xfer( Xfer *xfer );									// primary slot 3
};

typedef char CollideModuleSizeIs0x14[sizeof(CollideModule) == 0x14 ? 1 : -1];

#endif // __BFME2_COLLIDEMODULE_H_
