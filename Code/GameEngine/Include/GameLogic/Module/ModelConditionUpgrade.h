// FILE: ModelConditionUpgrade.h //////////////////////////////////////////////////////////////////
// Desc:   BFME2 ModelConditionUpgrade over the canonical UpgradeModule.h, written from retail's
//         tables. Every unit that emits the class's vftables (its constructor's and its
//         destructor's) includes this one declaration, so their COMDAT copies are identical.
//
// Target facts (code addresses are RVAs, vftables VAs):
//  - ??0ModelConditionUpgrade 0x004B64E5 calls ??0UpgradeModule 0x00460AEC, then installs
//    0x00C58658 at +0, UpgradeModule's 0x00C57328 at +0x0C, 0x00C58610 at +0x10 and
//    UpgradeModule's 0x00C58790 at +0x18; its destructor 0x004B63BD restores the same four tables
//    and jumps to ??1UpgradeModule 0x0046089D.
//  - 0x00C58658 (12 slots): deleting destructor 0x004B6516, loadPostProcess 0x00497805
//    (`jmp 0x0058B03E`, UpgradeModule's own body), the name getter 0x004B63DD
//    ("ModelConditionUpgrade"), xfer 0x004B8710 (Version1, then UpgradeModule::xfer; a body
//    retail folds with ArmorUpgrade::xfer), getModuleNameKey 0x004B63E3, then UpgradeModule's
//    slots.
//  - 0x00C58610 (UpgradeMux, 18 slots) is UpgradeModule's except slot 8,
//    upgradeRemovalImplementation 0x004B65A5, and slot 10, upgradeImplementation 0x004B6532.
// Donor (Zero Hour) facts: the UpgradeModule base and the upgrade override names; Zero Hour has
// no ModelConditionUpgrade.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __BFME2_MODELCONDITIONUPGRADE_H_
#define __BFME2_MODELCONDITIONUPGRADE_H_

#include "UpgradeModule.h"

class ModelConditionUpgrade : public UpgradeModule
{
public:
	ModelConditionUpgrade( Thing *thing, const ModuleData *moduleData );
	virtual ~ModelConditionUpgrade();

	virtual NameKeyType getModuleNameKey() const;
	virtual void upgradeRemovalImplementation();							// UpgradeMux slot 8

protected:
	virtual void xfer( Xfer *xfer );										// primary slot 3
	virtual void upgradeImplementation();									// UpgradeMux slot 10
};

#endif // __BFME2_MODELCONDITIONUPGRADE_H_
