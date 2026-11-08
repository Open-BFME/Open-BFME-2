// FILE: MaxHealthUpgrade.h ///////////////////////////////////////////////////////////////////////
// Desc:   BFME2 MaxHealthUpgrade over the canonical UpgradeModule.h, written from retail's tables.
//         Every unit that emits the class's vftables (its constructor's and its destructor's)
//         includes this one declaration, so their COMDAT copies are identical.
//
// Target facts (code addresses are RVAs, vftables VAs):
//  - ??0MaxHealthUpgrade 0x004B630A calls ??0UpgradeModule 0x00460AEC, then installs 0x00C58590
//    at +0, UpgradeModule's 0x00C57328 at +0x0C, 0x00C58548 at +0x10 and UpgradeModule's
//    0x00C58790 at +0x18; its destructor 0x004B6259 restores the same four tables and jumps to
//    ??1UpgradeModule 0x0046089D.
//  - 0x00C58590 (12 slots): deleting destructor 0x004B633B, loadPostProcess 0x00497805
//    (`jmp 0x0058B03E`, UpgradeModule's own body), the name getter 0x004B6279, xfer 0x004B8710
//    (Version1, then UpgradeModule::xfer; a body retail folds with ArmorUpgrade::xfer),
//    getModuleNameKey 0x004B627F, then UpgradeModule's slots.
//  - 0x00C58548 (UpgradeMux, 18 slots) is UpgradeModule's except slot 8,
//    upgradeRemovalImplementation 0x004B638A, and slot 10, upgradeImplementation 0x004B6357.
// Donor (Zero Hour MaxHealthUpgrade.h) facts: the class name, its UpgradeModule base, the
// upgrade overrides and the module-data accessor.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __BFME2_MAXHEALTHUPGRADE_H_
#define __BFME2_MAXHEALTHUPGRADE_H_

#include "UpgradeModule.h"

class MaxHealthUpgradeModuleData;

class MaxHealthUpgrade : public UpgradeModule
{
public:
	MaxHealthUpgrade( Thing *thing, const ModuleData *moduleData );
	virtual ~MaxHealthUpgrade();

	virtual NameKeyType getModuleNameKey() const;							// primary slot 4

protected:
	virtual void xfer( Xfer *xfer );										// primary slot 3
	virtual void upgradeRemovalImplementation();							// UpgradeMux slot 8
	virtual void upgradeImplementation();									// UpgradeMux slot 10

private:
	const MaxHealthUpgradeModuleData *getMaxHealthUpgradeModuleData() const { return (const MaxHealthUpgradeModuleData *)m_moduleData; }
};

#endif // __BFME2_MAXHEALTHUPGRADE_H_
