// FILE: WeaponBonusUpgrade.h /////////////////////////////////////////////////////////////////////
// Desc:   BFME2 WeaponBonusUpgrade over the canonical UpgradeModule.h, written from retail's tables.
//         Every unit that emits the class's vftables (its constructor's and its destructor's)
//         includes this one declaration, so their COMDAT copies are identical.
//
// Target facts (code addresses are RVAs, vftables VAs):
//  - ??0WeaponBonusUpgrade 0x004B5633 calls ??0UpgradeModule 0x00460AEC, then installs 0x00C57F68
//    at +0, UpgradeModule's 0x00C57328 at +0x0C, 0x00C57F20 at +0x10 and UpgradeModule's
//    0x00C58790 at +0x18; its destructor 0x004B55C8 restores the same four tables.
//  - 0x00C57F68 (12 slots): deleting destructor 0x004B5664, loadPostProcess 0x00497805
//    (`jmp 0x0058B03E`: the class's UpgradeModule base call, ICF-folded; UpgradeModule's own
//    loadPostProcess is 0x0058B03E), the name getter 0x004B55E8 ("WeaponBonusUpgrade"),
//    xfer 0x004B8710 (Version1, then UpgradeModule::xfer; a body retail folds with
//    ArmorUpgrade::xfer), getModuleNameKey 0x004B55EE, then UpgradeModule's slots.
//  - 0x00C57F20 (UpgradeMux, 18 slots) is UpgradeModule's except slot 8,
//    upgradeRemovalImplementation, the shared empty body 0x000B3FD0, and slot 10,
//    upgradeImplementation 0x004B5680.
// Donor (Zero Hour WeaponBonusUpgrade.h) facts: the class name, its UpgradeModule base and the
// upgradeImplementation override.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __BFME2_WEAPONBONUSUPGRADE_H_
#define __BFME2_WEAPONBONUSUPGRADE_H_

#include "UpgradeModule.h"

class WeaponBonusUpgrade : public UpgradeModule
{
public:
	WeaponBonusUpgrade( Thing *thing, const ModuleData *moduleData );
	virtual ~WeaponBonusUpgrade();

	virtual NameKeyType getModuleNameKey() const;

protected:
	virtual void loadPostProcess();							// primary slot 1
	virtual const char *GetSnapshotName() const;						// primary slot 2
	virtual void xfer( Xfer *xfer );									// primary slot 3
	virtual void upgradeImplementation();								// UpgradeMux slot 10
	virtual void upgradeRemovalImplementation() { }						// UpgradeMux slot 8
};

#endif // __BFME2_WEAPONBONUSUPGRADE_H_
