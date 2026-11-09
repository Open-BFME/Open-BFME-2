// FILE: LevelUpUpgrade.h /////////////////////////////////////////////////////////////////////////
// Desc:   BFME2 LevelUpUpgrade over the canonical UpgradeModule.h, written from retail's tables.
//         Every unit that emits the class's vftables (its constructor's and its destructor's)
//         includes this one declaration, so their COMDAT copies are identical.
//
// Target facts (code addresses are RVAs, vftables VAs):
//  - ??0LevelUpUpgrade 0x004B3DC8 calls ??0UpgradeModule 0x00460AEC, then installs 0x00C57460
//    at +0, UpgradeModule's 0x00C57328 at +0x0C, 0x00C57418 at +0x10 and UpgradeModule's
//    0x00C58790 at +0x18; its destructor 0x004B3D3B restores the same four tables and jumps to
//    ??1UpgradeModule 0x0046089D.
//  - 0x00C57460 (12 slots): deleting destructor 0x004B3DF9, loadPostProcess 0x00497805
//    (`jmp 0x0058B03E`, the base call retail folds across the module family), the name getter
//    0x004B3D5B, xfer 0x004B8710 (Version1, then UpgradeModule::xfer; the body retail folds with
//    ArmorUpgrade::xfer), getModuleNameKey 0x004B3D61, then UpgradeModule's slots.
//  - 0x00C57418 (UpgradeMux, 18 slots) is UpgradeModule's except slot 2, 0x004B3E7F (rowed in
//    LevelUpUpgradeMuxSlots.cpp under a positional spelling), slot 8, 0x000B3FD0, and slot 10,
//    upgradeImplementation 0x004B3E15.
// Donor (BFME1 LevelUpUpgrade) facts: the class name and its UpgradeModule base.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __BFME2_LEVELUPUPGRADE_H_
#define __BFME2_LEVELUPUPGRADE_H_

#include "UpgradeModule.h"

class LevelUpUpgrade : public UpgradeModule
{
public:
	LevelUpUpgrade( Thing *thing, const ModuleData *moduleData );
	virtual ~LevelUpUpgrade();

	virtual NameKeyType getModuleNameKey() const;							// primary slot 4

protected:
	virtual void loadPostProcess();											// primary slot 1
	virtual void xfer( Xfer *xfer );										// primary slot 3
	virtual void upgradeImplementation();									// UpgradeMux slot 10
};

#endif // __BFME2_LEVELUPUPGRADE_H_
