// FILE: AllowBannerSpawnUpgrade.h ////////////////////////////////////////////////////////////////
// Desc:   BFME2 AllowBannerSpawnUpgrade over the canonical UpgradeModule.h, written from retail's
//         tables. Every unit that emits the class's vftables (its constructor's and its
//         destructor's) includes this one declaration, so their COMDAT copies are identical.
//
// Target facts (code addresses are RVAs, vftables VAs):
//  - ??0AllowBannerSpawnUpgrade 0x004B8587 calls ??0UpgradeModule 0x00460AEC, then installs
//    0x00C59030 at +0, UpgradeModule's 0x00C57328 at +0x0C, 0x00C58FE8 at +0x10 and
//    UpgradeModule's 0x00C58790 at +0x18; its destructor 0x004B84EA restores the same four tables
//    and jumps to ??1UpgradeModule 0x0046089D.
//  - 0x00C59030 (12 slots): deleting destructor 0x004B85B8, loadPostProcess 0x00497805
//    (`jmp 0x0058B03E`: the class's UpgradeModule base call, ICF-folded; UpgradeModule's own
//    loadPostProcess is 0x0058B03E), GetSnapshotName 0x004B850A
//    ("AllowBannerSpawnUpgrade"), xfer 0x004B8710 (Version1, then UpgradeModule::xfer; a body
//    retail folds with ArmorUpgrade::xfer), getModuleNameKey 0x004B8520, then UpgradeModule's.
//  - 0x00C58FE8 (UpgradeMux, 18 slots) is UpgradeModule's except slot 8,
//    upgradeRemovalImplementation 0x004B8518, and slot 10, upgradeImplementation 0x004B8510.
// Zero Hour has no AllowBannerSpawnUpgrade; the override names are UpgradeMux's.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __BFME2_ALLOWBANNERSPAWNUPGRADE_H_
#define __BFME2_ALLOWBANNERSPAWNUPGRADE_H_

#include "UpgradeModule.h"

class AllowBannerSpawnUpgrade : public UpgradeModule
{
public:
	AllowBannerSpawnUpgrade( Thing *thing, const ModuleData *moduleData );

	virtual NameKeyType getModuleNameKey() const;

protected:
	virtual ~AllowBannerSpawnUpgrade();
	virtual void loadPostProcess();								// primary slot 1
	virtual const char *GetSnapshotName() const;							// primary slot 2
	virtual void xfer( Xfer *xfer );										// primary slot 3
	virtual void upgradeRemovalImplementation();							// UpgradeMux slot 8
	virtual void upgradeImplementation();									// UpgradeMux slot 10
};

#endif // __BFME2_ALLOWBANNERSPAWNUPGRADE_H_
