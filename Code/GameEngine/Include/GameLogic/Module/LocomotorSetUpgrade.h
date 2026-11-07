// FILE: LocomotorSetUpgrade.h ////////////////////////////////////////////////////////////////////
// Desc:   BFME2 LocomotorSetUpgrade over the canonical UpgradeModule.h, written from retail's
//         tables. Every unit that emits the class's vftables (its constructor's and its
//         destructor's) includes this one declaration, so their COMDAT copies are identical.
//
// Target facts (code addresses are RVAs, vftables VAs):
//  - ??0LocomotorSetUpgrade 0x004B3F0B calls ??0UpgradeModule 0x00460AEC, then installs
//    0x00C57530 at +0, UpgradeModule's 0x00C57328 at +0x0C, 0x00C574E8 at +0x10 and
//    UpgradeModule's 0x00C58790 at +0x18; its destructor 0x004B3EA0 restores the same four tables
//    and jumps to ??1UpgradeModule 0x0046089D.
//  - 0x00C57530 (12 slots): deleting destructor 0x004B3F3C, loadPostProcess 0x00497805
//    (`jmp 0x0058B03E`, UpgradeModule's own body), the name getter 0x004B3EC0
//    ("LocomotorSetUpgrade"; rowed as the non-virtual ?name@LocomotorSetUpgrade, so slot 2 stays
//    UpgradeModule's here), xfer 0x004B8710 (Version1, then UpgradeModule::xfer; a body retail
//    folds with ArmorUpgrade::xfer), getModuleNameKey 0x004B3EC6, then UpgradeModule's slots.
//  - 0x00C574E8 (UpgradeMux, 18 slots) is UpgradeModule's except slot 8,
//    upgradeRemovalImplementation 0x004B3F7B, and slot 10, upgradeImplementation 0x004B3F58.
// Donor (Zero Hour LocomotorSetUpgrade.h) facts: the class name, its UpgradeModule base and the
// upgradeImplementation override.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __BFME2_LOCOMOTORSETUPGRADE_H_
#define __BFME2_LOCOMOTORSETUPGRADE_H_

#include "UpgradeModule.h"

class LocomotorSetUpgrade : public UpgradeModule
{
public:
	LocomotorSetUpgrade( Thing *thing, const ModuleData *moduleData );

	virtual NameKeyType getModuleNameKey() const;

protected:
	virtual ~LocomotorSetUpgrade();
	virtual void xfer( Xfer *xfer );										// primary slot 3
	virtual void upgradeRemovalImplementation();							// UpgradeMux slot 8
	virtual void upgradeImplementation();									// UpgradeMux slot 10
};

#endif // __BFME2_LOCOMOTORSETUPGRADE_H_
