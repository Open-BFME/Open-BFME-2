// FILE: TooltipUpgrade.h /////////////////////////////////////////////////////////////////////////
// Desc:   BFME2 TooltipUpgrade over the canonical UpgradeModule.h, written from retail's tables.
//         Every unit that emits the class's vftables (its constructor's and its destructor's)
//         includes this one declaration, so their COMDAT copies are identical.
//
// Target facts (code addresses are RVAs, vftables VAs):
//  - ??0TooltipUpgrade 0x004B7A50 calls ??0UpgradeModule 0x00460AEC, then installs 0x00C58C08 at
//    +0, UpgradeModule's 0x00C57328 at +0x0C, 0x00C58BC0 at +0x10 and UpgradeModule's 0x00C58790
//    at +0x18; its destructor 0x004B79AD restores the same four tables and jumps to
//    ??1UpgradeModule 0x0046089D.
//  - 0x00C58C08 (12 slots): deleting destructor 0x004B7A81, loadPostProcess 0x00497805
//    (`jmp 0x0058B03E`: the class's UpgradeModule base call, ICF-folded; UpgradeModule's own
//    loadPostProcess is 0x0058B03E), GetSnapshotName 0x004B79CD ("TooltipUpgrade"),
//    xfer 0x004B8710 (Version1, then UpgradeModule::xfer; a body retail folds with
//    ArmorUpgrade::xfer), getModuleNameKey 0x004B79E9, then UpgradeModule's slots.
//  - 0x00C58BC0 (UpgradeMux, 18 slots) is UpgradeModule's except slot 6, postUpgradeCheck
//    0x004B3B42 (one body with CommandSetUpgrade's), slot 8, upgradeRemovalImplementation
//    0x004B7ADB, and slot 10, upgradeImplementation 0x004B7A9D.
// Donor (Zero Hour) facts: the UpgradeModule base and the upgrade override names; Zero Hour has
// no TooltipUpgrade.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __BFME2_TOOLTIPUPGRADE_H_
#define __BFME2_TOOLTIPUPGRADE_H_

#include "UpgradeModule.h"

class TooltipUpgrade : public UpgradeModule
{
public:
	TooltipUpgrade( Thing *thing, const ModuleData *moduleData );
	virtual ~TooltipUpgrade();

	virtual NameKeyType getModuleNameKey() const;
	virtual void postUpgradeCheck();										// UpgradeMux slot 6

protected:
	virtual void loadPostProcess();								// primary slot 1
	virtual const char *GetSnapshotName() const;							// primary slot 2
	virtual void xfer( Xfer *xfer );										// primary slot 3
	virtual void upgradeRemovalImplementation();							// UpgradeMux slot 8
	virtual void upgradeImplementation();									// UpgradeMux slot 10
};

#endif // __BFME2_TOOLTIPUPGRADE_H_
