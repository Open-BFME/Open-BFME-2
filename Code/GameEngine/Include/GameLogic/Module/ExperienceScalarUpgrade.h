// FILE: ExperienceScalarUpgrade.h ////////////////////////////////////////////////////////////////
// Desc:   BFME2 ExperienceScalarUpgrade over the canonical UpgradeModule.h, written from retail's
//         tables. Every unit that emits the class's vftables (its constructor's and its
//         destructor's) includes this one declaration, so their COMDAT copies are identical.
//
// Target facts (code addresses are RVAs, vftables VAs):
//  - ??0ExperienceScalarUpgrade 0x004B61C6 calls ??0UpgradeModule 0x00460AEC, then installs
//    0x00C584E8 at +0, UpgradeModule's 0x00C57328 at +0x0C, 0x00C584A0 at +0x10 and
//    UpgradeModule's 0x00C58790 at +0x18; its destructor 0x004B611C restores the same four tables
//    and jumps to ??1UpgradeModule 0x0046089D.
//  - 0x00C584E8 (12 slots): deleting destructor 0x004B61F7, loadPostProcess 0x00497805
//    (`jmp 0x0058B03E`, the class's UpgradeModule base call, ICF-folded), the name getter 0x004B613C, xfer 0x004B8710
//    (Version1, then UpgradeModule::xfer; a body retail folds with ArmorUpgrade::xfer),
//    getModuleNameKey 0x004B6142, then UpgradeModule's slots.
//  - 0x00C584A0 (UpgradeMux, 18 slots) is UpgradeModule's except slot 8,
//    upgradeRemovalImplementation 0x004B6236, and slot 10, upgradeImplementation 0x004B6213.
// Donor (Zero Hour ExperienceScalarUpgrade.h) facts: the class name, its UpgradeModule base,
// the two upgrade overrides and the module-data accessor.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __BFME2_EXPERIENCESCALARUPGRADE_H_
#define __BFME2_EXPERIENCESCALARUPGRADE_H_

#include "UpgradeModule.h"

class ExperienceScalarUpgradeModuleData;

class ExperienceScalarUpgrade : public UpgradeModule
{
public:
	ExperienceScalarUpgrade( Thing *thing, const ModuleData *moduleData );
	virtual ~ExperienceScalarUpgrade();

	virtual NameKeyType getModuleNameKey() const;							// primary slot 4

protected:
	virtual void loadPostProcess();											// primary slot 1
	virtual void xfer( Xfer *xfer );										// primary slot 3
	virtual void upgradeRemovalImplementation();							// UpgradeMux slot 8
	virtual void upgradeImplementation();									// UpgradeMux slot 10

private:
	const ExperienceScalarUpgradeModuleData *getExperienceScalarUpgradeModuleData() const { return (const ExperienceScalarUpgradeModuleData *)m_moduleData; }
};

#endif // __BFME2_EXPERIENCESCALARUPGRADE_H_
