// FILE: DelayedUpgrade.h /////////////////////////////////////////////////////////////////////////
// Desc:   BFME2 DelayedUpgrade over the canonical UpgradeModule.h, written from retail's tables.
//         Every unit that emits the class's vftables (its constructor's and its destructor's)
//         includes this one declaration, so their COMDAT copies are identical.
//
// Target facts (code addresses are RVAs, vftables VAs):
//  - ??0DelayedUpgrade 0x004B3C75 calls ??0UpgradeModule 0x00460AEC, then installs 0x00C573E4 at
//    +0, UpgradeModule's 0x00C57328 at +0x0C, 0x00C572E0 at +0x10 and UpgradeModule's 0x00C58790
//    at +0x18; its destructor 0x004B3C0A restores the same four tables.
//  - 0x00C573E4 (12 slots): deleting destructor 0x004B3CA6, loadPostProcess 0x00497805
//    (`jmp 0x0058B03E`, UpgradeModule's own body), GetSnapshotName 0x004B3C2A
//    ("DelayedUpgrade"), xfer 0x004B8710 (Version1, then UpgradeModule::xfer; a body retail
//    folds with ArmorUpgrade::xfer), getModuleNameKey 0x004B3C30, then UpgradeModule's slots.
//  - 0x00C572E0 (UpgradeMux, 18 slots) is UpgradeModule's except slot 8,
//    upgradeRemovalImplementation, the shared empty body 0x000B3FD0, and slot 10,
//    upgradeImplementation 0x004B3CC2.
// Donor (Zero Hour) facts: the UpgradeModule base and the upgradeImplementation override name;
// Zero Hour has no DelayedUpgrade.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __BFME2_DELAYEDUPGRADE_H_
#define __BFME2_DELAYEDUPGRADE_H_

#include "UpgradeModule.h"

class DelayedUpgrade : public UpgradeModule
{
public:
	DelayedUpgrade( Thing *thing, const ModuleData *moduleData );

	virtual NameKeyType getModuleNameKey() const;

protected:
	virtual const char *GetSnapshotName() const;							// primary slot 2
	virtual void xfer( Xfer *xfer );										// primary slot 3
	virtual void upgradeImplementation();									// UpgradeMux slot 10
	virtual void upgradeRemovalImplementation() { }						// UpgradeMux slot 8
};

#endif // __BFME2_DELAYEDUPGRADE_H_
