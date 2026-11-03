// Target facts (code addresses are RVAs; vftables and strings are VAs): constructor 0x0049B560 calls UpdateModule (0x00253390) at +0 and UpgradeMux (0x004CE2A3) at +0x20 before installing tables 0x00C50D2C/+0, 0x00C49F78/+0x0C, 0x00C50D20/+0x10 and 0x00C50CD8/+0x20. Factory 0x0024E624 pushes sizeof 0x28 at 0x0024E62F and calls this constructor at 0x0024E64B. UpgradeMux's constructor clears one byte at +4 (0x004CE2AB), so +0x24 is a bool followed by three padding bytes; there are no additional derived fields.
// The destructor 0x0049B6DD installs the same four tables at 0x0049B6EE..0x0049B702, then calls UpdateModule destruction (0x0024A797) at 0x0049B73E. Its later base tables belong to base teardown. Primary table 0x00C50D2C has 13 slots: deleting destructor 0x0049B884, loadPostProcess 0x00497805, Snapshot name getter 0x0049B5D6, xfer 0x0049B66B, module key 0x0049B5DC, four empty slots, onCapture, two null getters and inherited getUpdatePhase 0x0022C4CB. Both name bodies reference "AttributeModifierAuraUpdate" at 0x00BF5100. The +0x0C table has 47 slots, with getUpdate/9 = 0x002533D3 and getUpgrade/10 = 0x004543A9 (returns the +0x20 subobject); the +0x10 table has update/0 = 0x0049BCA3 and two inherited slots.
// UpgradeMux table 0x00C50CD8 has 18 slots in its registered parent's order: overrides 8=0x004B471F, 10=0x004A33E0, 11=0x0049B621, 12/15=0x0049B648, 13=0x0049B657 and 14=0x0049B661. Mask copying reads module data at [this-0x1C]+0x28/+0xA8; FX reads Object at [this-0x18]; the two predicates read data bytes +0x134/+0x135. xfer calls UpdateModule::xfer (0x0044DF9F) and UpgradeMux::upgradeMuxXfer (0x004CE397) with this+0x20. Override names follow the registered parents' evidenced slots; the rowed constructor, destructor, factory, key, update, xfer, mask and FX bodies remain out of line.

#pragma once

#ifndef BFME2_ATTRIBUTEMODIFIERAURAUPDATE_H
#define BFME2_ATTRIBUTEMODIFIERAURAUPDATE_H

#include "UpdateModule.h"
#include "UpgradeMux.h"

class AttributeModifierAuraUpdate : public UpdateModule, public UpgradeMux
{
public:
    AttributeModifierAuraUpdate(Thing *thing, const ModuleData *moduleData);
    virtual ~AttributeModifierAuraUpdate();

    static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);
    virtual NameKeyType getModuleNameKey() const;
    virtual UpdateSleepTime update();
    virtual UpgradeModuleInterface *getUpgrade();

protected:
    virtual void loadPostProcess();
#ifdef BFME_SNAPSHOT_NAME_SLOT
    virtual const char *GetSnapshotName() const;
#else
    virtual void crc(Xfer *xfer);
#endif
    virtual void xfer(Xfer *xfer);

    virtual void upgradeRemovalImplementation();
    virtual void upgradeImplementation();
    virtual void getUpgradeActivationMasks(UpgradeMaskType &activation, UpgradeMaskType &conflicting) const;
    virtual void performUpgradeFX();
    virtual bool requiresAllActivationUpgrades() const;
    virtual bool requiresAllConflictingUpgrades() const;
    virtual void processUpgradeRemoval();
};

#endif
