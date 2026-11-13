// FILE: DoCommandUpgrade.h ///////////////////////////////////////////////////////////////////////
// Desc:   BFME2 DoCommandUpgrade over the canonical UpgradeModule.h, written from retail's tables.
//         Every unit that emits the class's vftables (its constructor's and its destructor's)
//         includes this one declaration, so their COMDAT copies are identical.
//
// Target facts (code addresses are RVAs, vftables VAs):
//  - ??0DoCommandUpgrade 0x004B4C2E calls ??0UpgradeModule 0x00460AEC, then installs 0x00C57B58
//    at +0, UpgradeModule's 0x00C57328 at +0x0C, 0x00C57B10 at +0x10 and UpgradeModule's
//    0x00C58790 at +0x18; its destructor 0x004B4BA1 restores the same four tables and jumps to
//    ??1UpgradeModule 0x0046089D.
//  - 0x00C57B58 (12 slots): deleting destructor 0x004B4C5F, loadPostProcess 0x00497805
//    (`jmp 0x0058B03E`, the class's UpgradeModule base call, ICF-folded), the name getter 0x004B4BC1 ("DoCommandUpgrade";
//    rowed as the non-virtual ?name@DoCommandUpgrade, so slot 2 stays UpgradeModule's here), xfer
//    0x004B8710 (Version1, then UpgradeModule::xfer; a body retail folds with
//    ArmorUpgrade::xfer), getModuleNameKey 0x004B4BC7, then UpgradeModule's slots.
//  - 0x00C57B10 (UpgradeMux, 18 slots) is UpgradeModule's except slot 8,
//    upgradeRemovalImplementation 0x004B4C7B, and slot 10, upgradeImplementation 0x004B4CAD
//    (both rowed public, DoCommandUpgradeSlots.cpp).
// Donor (Zero Hour) facts: the UpgradeModule base and the upgradeImplementation override name;
// Zero Hour has no DoCommandUpgrade.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __BFME2_DOCOMMANDUPGRADE_H_
#define __BFME2_DOCOMMANDUPGRADE_H_

#include "UpgradeModule.h"

class DoCommandUpgrade : public UpgradeModule
{
public:
	DoCommandUpgrade( Thing *thing, const ModuleData *moduleData );

	virtual NameKeyType getModuleNameKey() const;
	virtual void upgradeRemovalImplementation();							// UpgradeMux slot 8
	virtual void upgradeImplementation();									// UpgradeMux slot 10

protected:
	virtual ~DoCommandUpgrade();
	virtual void loadPostProcess();											// primary slot 1
	virtual void xfer( Xfer *xfer );										// primary slot 3
protected:
	virtual const char *GetSnapshotName() const;	// primary slot 2: retail 0x004B4BC1
};

#endif // __BFME2_DOCOMMANDUPGRADE_H_
