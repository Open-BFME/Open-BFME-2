// FILE: UnpauseSpecialPowerUpgrade.h /////////////////////////////////////////////////////////////
// Desc:   BFME2 UnpauseSpecialPowerUpgrade over the canonical UpgradeModule.h, written from
//         retail's tables. Every unit that emits the class's vftables (its constructor's and its
//         destructor's) includes this one declaration, so their COMDAT copies are identical.
//
// Target facts (code addresses are RVAs, vftables VAs):
//  - ??0UnpauseSpecialPowerUpgrade 0x004B548C calls ??0UpgradeModule 0x00460AEC, then installs
//    0x00C57EA8 at +0, UpgradeModule's 0x00C57328 at +0x0C, 0x00C57E60 at +0x10 and
//    UpgradeModule's 0x00C58790 at +0x18; its destructor 0x004B53DF restores the same four tables
//    and jumps to ??1UpgradeModule 0x0046089D.
//  - 0x00C57EA8 (12 slots): deleting destructor 0x004B54BD, loadPostProcess 0x00497805
//    (`jmp 0x0058B03E`, UpgradeModule's own body), the name getter 0x004B53FF, xfer 0x004B8710
//    (Version1, then UpgradeModule::xfer; a body retail folds with ArmorUpgrade::xfer),
//    getModuleNameKey 0x004B5405, slot 5 0x004B54D9, then UpgradeModule's slots.
//  - 0x00C57E60 (UpgradeMux, 18 slots) is UpgradeModule's except slot 8,
//    upgradeRemovalImplementation 0x004B5574, and slot 10, upgradeImplementation 0x004B54E9.
// Open: 0x004B54D9 is rowed as onCreate, declared here as a new virtual, so this class's copy of
// 0x00C57EA8 still puts it after UpgradeModule's slots instead of in slot 5 (Module's
// onObjectCreated slot); naming it as that override needs a naming basis.
// Donor (BFME1 UnpauseSpecialPowerUpgrade) facts: the class name, its UpgradeModule base and the
// upgrade overrides.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __BFME2_UNPAUSESPECIALPOWERUPGRADE_H_
#define __BFME2_UNPAUSESPECIALPOWERUPGRADE_H_

#include "UpgradeModule.h"

class UnpauseSpecialPowerUpgradeModuleData;

class UnpauseSpecialPowerUpgrade : public UpgradeModule
{
public:
	UnpauseSpecialPowerUpgrade( Thing *thing, const ModuleData *moduleData );
	virtual ~UnpauseSpecialPowerUpgrade();

	virtual NameKeyType getModuleNameKey() const;							// primary slot 4

protected:
	virtual void xfer( Xfer *xfer );										// primary slot 3
	virtual void onCreate();
	virtual void upgradeRemovalImplementation();							// UpgradeMux slot 8
	virtual void upgradeImplementation();									// UpgradeMux slot 10

private:
	const UnpauseSpecialPowerUpgradeModuleData *getUnpauseSpecialPowerUpgradeModuleData() const { return (const UnpauseSpecialPowerUpgradeModuleData *)m_moduleData; }
};

#endif // __BFME2_UNPAUSESPECIALPOWERUPGRADE_H_
