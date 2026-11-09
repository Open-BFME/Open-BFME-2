// FILE: WeaponSetUpgrade.h ///////////////////////////////////////////////////////////////////////
// Desc:   BFME2 WeaponSetUpgrade over the canonical UpgradeModule.h, written from retail's tables.
//         Every unit that emits the class's vftables (its constructor's and its destructor's)
//         includes this one declaration, so their COMDAT copies are identical.
//
// Target facts (code addresses are RVAs, vftables VAs):
//  - ??0WeaponSetUpgrade 0x004B5718 calls ??0UpgradeModule 0x00460AEC, then installs 0x00C57FE0
//    at +0, UpgradeModule's 0x00C57328 at +0x0C, 0x00C57F98 at +0x10 and UpgradeModule's
//    0x00C58790 at +0x18; its destructor 0x004B568B restores the same four tables and jumps to
//    ??1UpgradeModule 0x0046089D.
//  - 0x00C57FE0 (12 slots): deleting destructor 0x004B5749, loadPostProcess 0x00497805
//    (`jmp 0x0058B03E`, the base call retail folds across the module family), GetSnapshotName
//    0x004B56AB ("WeaponSetUpgrade"), xfer 0x004B8710 (Version1, then UpgradeModule::xfer; the body retail folds with
//    ArmorUpgrade::xfer), getModuleNameKey 0x004B56B1, then UpgradeModule's slots.
//  - 0x00C57F98 (UpgradeMux, 18 slots) is UpgradeModule's except slot 8, 0x004B5783, and slot 10,
//    0x004B5765 (the upgrade removal and upgrade bodies, rowed in WeaponSetUpgradeSecondary.cpp
//    under another class; not declared here until those rows carry this class's names).
// Donor (Zero Hour WeaponSetUpgrade.h) facts: the class name and its UpgradeModule base.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __BFME2_WEAPONSETUPGRADE_H_
#define __BFME2_WEAPONSETUPGRADE_H_

#include "UpgradeModule.h"

class WeaponSetUpgrade : public UpgradeModule
{
public:
	WeaponSetUpgrade( Thing *thing, const ModuleData *moduleData );
	virtual ~WeaponSetUpgrade();

	virtual NameKeyType getModuleNameKey() const;							// primary slot 4

protected:
	virtual void loadPostProcess();											// primary slot 1
	virtual const char *GetSnapshotName() const;							// primary slot 2
	virtual void xfer( Xfer *xfer );										// primary slot 3
};

#endif // __BFME2_WEAPONSETUPGRADE_H_
