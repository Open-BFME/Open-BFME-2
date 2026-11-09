// FILE: BaseUpgrade.h ////////////////////////////////////////////////////////////////////////////
// Desc:   BFME2 BaseUpgrade over the canonical UpgradeModule.h, written from retail's tables.
//         Every unit that emits the class's vftables (its constructor's and its destructor's)
//         includes this one declaration, so their COMDAT copies are identical.
//
// Target facts (code addresses are RVAs, vftables VAs):
//  - ??0BaseUpgrade 0x004B371C calls ??0UpgradeModule 0x00460AEC, then installs 0x00C57120 at +0,
//    UpgradeModule's 0x00C57328 at +0x0C, 0x00C570D8 at +0x10 and UpgradeModule's 0x00C58790 at
//    +0x18; its destructor 0x004B362D restores the same four tables and jumps to
//    ??1UpgradeModule 0x0046089D.
//  - 0x00C57120 (12 slots): deleting destructor 0x004B374D, loadPostProcess 0x00497805
//    (`jmp 0x0058B03E`: the class's UpgradeModule base call, ICF-folded; UpgradeModule's own
//    loadPostProcess is 0x0058B03E), GetSnapshotName 0x004B364D ("BaseUpgrade"),
//    xfer 0x004B8710 (Version1, then UpgradeModule::xfer; a body retail folds with
//    ArmorUpgrade::xfer), getModuleNameKey 0x004B3653, then UpgradeModule's slots.
//  - 0x00C570D8 (UpgradeMux, 18 slots) is UpgradeModule's except slot 8,
//    upgradeRemovalImplementation, the shared empty body 0x000B3FD0, and slot 10,
//    upgradeImplementation 0x004B37CA.
// Donor (Zero Hour) facts: the UpgradeModule base and the upgradeImplementation override name;
// Zero Hour has no BaseUpgrade.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __BFME2_BASEUPGRADE_H_
#define __BFME2_BASEUPGRADE_H_

#include "UpgradeModule.h"

class BaseUpgrade : public UpgradeModule
{
public:
	BaseUpgrade( Thing *thing, const ModuleData *moduleData );
	virtual ~BaseUpgrade();

	virtual NameKeyType getModuleNameKey() const;

protected:
	virtual void loadPostProcess();								// primary slot 1
	virtual const char *GetSnapshotName() const;							// primary slot 2
	virtual void xfer( Xfer *xfer );										// primary slot 3
	virtual void upgradeImplementation();									// UpgradeMux slot 10
	virtual void upgradeRemovalImplementation() { }						// UpgradeMux slot 8
};

#endif // __BFME2_BASEUPGRADE_H_
