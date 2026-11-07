// FILE: CommandSetUpgrade.h //////////////////////////////////////////////////////////////////////
// Desc:   BFME2 CommandSetUpgrade over the canonical UpgradeModule.h, written from retail's tables.
//         Every unit that emits the class's vftables (its constructor's and its destructor's)
//         includes this one declaration, so their COMDAT copies are identical.
//
// Target facts (code addresses are RVAs, vftables VAs):
//  - ??0CommandSetUpgrade 0x004B3AB2 calls ??0UpgradeModule 0x00460AEC, then installs 0x00C57290
//    at +0, UpgradeModule's 0x00C57328 at +0x0C, 0x00C57248 at +0x10 and UpgradeModule's
//    0x00C58790 at +0x18; its destructor 0x004B39FC restores the same four tables and jumps to
//    ??1UpgradeModule 0x0046089D.
//  - 0x00C57290 (12 slots): deleting destructor 0x004B3AE3, loadPostProcess 0x00497805
//    (`jmp 0x0058B03E`, UpgradeModule's own body), GetSnapshotName 0x004B3A1C
//    ("CommandSetUpgrade"), xfer 0x004B8710 (Version1, then UpgradeModule::xfer; a body retail
//    folds with ArmorUpgrade::xfer), getModuleNameKey 0x004B3A4B, then UpgradeModule's slots.
//  - 0x00C57248 (UpgradeMux, 18 slots) is UpgradeModule's except slot 6, postUpgradeCheck
//    0x004B3B42 (one body with TooltipUpgrade's), slot 8, upgradeRemovalImplementation
//    0x004B3B88, and slot 10, upgradeImplementation 0x004B3AFF.
// Donor (Zero Hour CommandSetUpgrade.h) facts: the class name, its UpgradeModule base and the
// upgradeImplementation override; BFME2 adds the removal and post-upgrade check.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __BFME2_COMMANDSETUPGRADE_H_
#define __BFME2_COMMANDSETUPGRADE_H_

#include "UpgradeModule.h"

class CommandSetUpgrade : public UpgradeModule
{
public:
	CommandSetUpgrade( Thing *thing, const ModuleData *moduleData );
	virtual ~CommandSetUpgrade();

	virtual NameKeyType getModuleNameKey() const;
	virtual void postUpgradeCheck();										// UpgradeMux slot 6

protected:
	virtual const char *GetSnapshotName() const;							// primary slot 2
	virtual void xfer( Xfer *xfer );										// primary slot 3
	virtual void upgradeRemovalImplementation();							// UpgradeMux slot 8
	virtual void upgradeImplementation();									// UpgradeMux slot 10
};

#endif // __BFME2_COMMANDSETUPGRADE_H_
