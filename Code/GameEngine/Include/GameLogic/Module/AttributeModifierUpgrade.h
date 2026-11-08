// FILE: AttributeModifierUpgrade.h ///////////////////////////////////////////////////////////////
// Desc:   BFME2 AttributeModifierUpgrade over the canonical UpgradeModule.h, written from retail's
//         tables. Every unit that emits the class's vftables (its constructor's and its
//         destructor's) includes this one declaration, so their COMDAT copies are identical.
//
// Target facts (code addresses are RVAs, vftables VAs):
//  - ??0AttributeModifierUpgrade 0x004B6740 calls ??0UpgradeModule 0x00460AEC, then installs
//    0x00C587E8 at +0, UpgradeModule's 0x00C57328 at +0x0C, 0x00C587A0 at +0x10 and
//    UpgradeModule's 0x00C58790 at +0x18; its destructor 0x004B66B3 restores the same four tables
//    and jumps to ??1UpgradeModule 0x0046089D.
//  - 0x00C587E8 (12 slots): deleting destructor 0x004B6771, loadPostProcess 0x00497805
//    (`jmp 0x0058B03E`, UpgradeModule's own body), the name getter 0x004B66D3, xfer 0x004B8710
//    (Version1, then UpgradeModule::xfer; a body retail folds with ArmorUpgrade::xfer),
//    getModuleNameKey 0x004B66D9, then UpgradeModule's slots.
//  - 0x00C587A0 (UpgradeMux, 18 slots) is UpgradeModule's except slot 8,
//    upgradeRemovalImplementation 0x004B67AD, and slot 10, upgradeImplementation 0x004B678D.
// Donor (BFME1 AttributeModifierUpgrade) facts: the class name, its UpgradeModule base, the two
// upgrade overrides and the module-data accessor.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __BFME2_ATTRIBUTEMODIFIERUPGRADE_H_
#define __BFME2_ATTRIBUTEMODIFIERUPGRADE_H_

#include "UpgradeModule.h"

class AttributeModifierUpgradeModuleData;

class AttributeModifierUpgrade : public UpgradeModule
{
public:
	AttributeModifierUpgrade( Thing *thing, const ModuleData *moduleData );
	virtual ~AttributeModifierUpgrade();

	virtual NameKeyType getModuleNameKey() const;							// primary slot 4

protected:
	virtual void xfer( Xfer *xfer );										// primary slot 3
	virtual void upgradeRemovalImplementation();							// UpgradeMux slot 8
	virtual void upgradeImplementation();									// UpgradeMux slot 10

	const AttributeModifierUpgradeModuleData *getData() const
	{
		return (const AttributeModifierUpgradeModuleData *)m_moduleData;
	}
};

#endif // __BFME2_ATTRIBUTEMODIFIERUPGRADE_H_
