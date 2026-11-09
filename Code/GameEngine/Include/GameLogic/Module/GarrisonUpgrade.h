// FILE: GarrisonUpgrade.h ////////////////////////////////////////////////////////////////////////
// Desc:   BFME2 GarrisonUpgrade over the canonical UpgradeModule.h, written from retail's tables.
//         Every unit that emits the class's vftables (its constructor's and its destructor's)
//         includes this one declaration, so their COMDAT copies are identical.
//
// Target facts (code addresses are RVAs, vftables VAs):
//  - ??0GarrisonUpgrade 0x004B5839 calls ??0UpgradeModule 0x00460AEC, then installs 0x00C58088
//    at +0, UpgradeModule's 0x00C57328 at +0x0C, 0x00C58040 at +0x10 and UpgradeModule's
//    0x00C58790 at +0x18; its destructor 0x004B57CE restores the same four tables and jumps to
//    ??1UpgradeModule 0x0046089D.
//  - 0x00C58088 (12 slots): deleting destructor 0x004B586A, loadPostProcess 0x00497805
//    (`jmp 0x0058B03E`, the class's UpgradeModule base call, ICF-folded), GetSnapshotName 0x004B57EE ("GarrisonUpgrade"), xfer 0x004B8710
//    (Version1, then UpgradeModule::xfer; a body retail folds with ArmorUpgrade::xfer),
//    getModuleNameKey 0x004B57F4, then UpgradeModule's slots.
//  - 0x00C58040 (UpgradeMux, 18 slots) is UpgradeModule's except slot 8,
//    upgradeRemovalImplementation 0x004B58FF, and slot 10, upgradeImplementation 0x004B5886.
// Donor (BFME1 GarrisonUpgrade) facts: the class name, its UpgradeModule base and the two
// upgrade overrides.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __BFME2_GARRISONUPGRADE_H_
#define __BFME2_GARRISONUPGRADE_H_

#include "UpgradeModule.h"

class GarrisonUpgrade : public UpgradeModule
{
public:
	GarrisonUpgrade( Thing *thing, const ModuleData *moduleData );
	virtual ~GarrisonUpgrade();

	virtual NameKeyType getModuleNameKey() const;							// primary slot 4

protected:
	virtual void loadPostProcess();											// primary slot 1
	virtual const char *GetSnapshotName() const;							// primary slot 2
	virtual void xfer( Xfer *xfer );										// primary slot 3
	virtual void upgradeRemovalImplementation();							// UpgradeMux slot 8
	virtual void upgradeImplementation();									// UpgradeMux slot 10
};

#endif // __BFME2_GARRISONUPGRADE_H_
