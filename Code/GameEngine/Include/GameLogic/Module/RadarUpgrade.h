// FILE: RadarUpgrade.h ///////////////////////////////////////////////////////////////////////////
// Desc:   BFME2 RadarUpgrade over the canonical UpgradeModule.h, written from retail's tables.
//         Every unit that emits the class's vftables (its constructor's and its destructor's)
//         includes this one declaration, so their COMDAT copies are identical.
//
// Target facts (code addresses are RVAs, vftables VAs):
//  - ??0RadarUpgrade 0x004B478E calls ??0UpgradeModule 0x00460AEC, then installs 0x00C57890 at
//    +0, UpgradeModule's 0x00C57328 at +0x0C, 0x00C57848 at +0x10 and UpgradeModule's
//    0x00C58790 at +0x18; its destructor 0x004B46F9 restores the same four tables and jumps to
//    ??1UpgradeModule 0x0046089D.
//  - 0x00C57890 (12 slots): deleting destructor 0x004B47BF, loadPostProcess 0x00497805
//    (`jmp 0x0058B03E`: the class's UpgradeModule base call, ICF-folded; UpgradeModule's own
//    loadPostProcess is 0x0058B03E), GetSnapshotName 0x004B4719
//    ("RadarUpgrade"), xfer 0x004B8710 (Version1, then UpgradeModule::xfer; a body retail folds
//    with ArmorUpgrade::xfer), getModuleNameKey 0x004B4727, Module's empty slots 5-7, onDelete
//    0x004B47DB, onCapture 0x004B4828, then BehaviorModule's two zero-returning slots.
//  - 0x00C57848 (UpgradeMux, 18 slots) is UpgradeModule's except slot 8,
//    upgradeRemovalImplementation 0x004B471F (setUpgradeExecuted(false); one body in five
//    upgrade tables), and slot 10, upgradeImplementation 0x004B488F.
// Donor (Zero Hour RadarUpgrade.h) facts: the class name, its UpgradeModule base and the
// onDelete, onCapture and upgradeImplementation overrides.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __BFME2_RADARUPGRADE_H_
#define __BFME2_RADARUPGRADE_H_

#include "UpgradeModule.h"

class Player;
class RadarUpgradeModuleData;

class RadarUpgrade : public UpgradeModule
{
public:
	RadarUpgrade( Thing *thing, const ModuleData *moduleData );
	virtual ~RadarUpgrade();

	virtual NameKeyType getModuleNameKey() const;
	virtual void onDelete();												// primary slot 8
	virtual void onCapture( Player *oldOwner, Player *newOwner );			// primary slot 9

protected:
	virtual void loadPostProcess();								// primary slot 1
	virtual const char *GetSnapshotName() const;							// primary slot 2
	virtual void xfer( Xfer *xfer );										// primary slot 3
	virtual void upgradeRemovalImplementation();							// UpgradeMux slot 8
	virtual void upgradeImplementation();									// UpgradeMux slot 10

private:
	const RadarUpgradeModuleData *getRadarUpgradeModuleData() const { return (const RadarUpgradeModuleData *)m_moduleData; }
};

#endif // __BFME2_RADARUPGRADE_H_
