// UpgradeMux: canonical BFME2 mix-in declaration. Code addresses are RVAs; table addresses are VAs.
// Target facts: constructor 0x004CE2A3 stores table 0x00C5FF10 at +0 (0x004CE2A5) and clears byte +4 (0x004CE2AB), with no base-constructor call. DetachableRiderBody constructor 0x004C1C82 constructs it at +0x100 (0x004C1CAB); factory 0x00251705 allocates 0x108 bytes. ObjectCreationUpgrade constructor 0x004B40A6 places its next base at +8. The mix-in occupies eight bytes, including three bytes of tail padding, and has no virtual destructor.
// Table 0x00C5FF10 has eighteen entries before non-code data at 0x00C5FF58: slots 0=0x00098CBC, 1=0x004CE27C, 2=0x004CE2B0, 3=0x004CE342, 4/7=0x0047A699, 5=0x004CE270, 6/17=0x000B3FD0, 8/10/11/12/13/14/15=__purecall (0x0003B810), 9=0x00452354 and 16=0x004CE397. Slots 4/7 return false; slots 6/17 are empty returns.
// UpgradeModule constructor 0x00460AEC calls the mix-in constructor at 0x00460B12, then replaces its +0x10 table with 0x00C42720 at 0x00460B21. This derived table retains the mix-in's slot order; its differing entries are overrides, not another UpgradeMux layout.
// Slot 0 (0x00098CBC) reads byte +4. Slot 1 (0x004CE27C) forwards one pointer to slot 2 and returns with ret 4; its ledger spells the argument const BitFlags<128>&. Slot 2 (0x004CE2B0) obtains two 0x80-byte masks through slot 11, tests byte +4, and selects all/any conflicting and activation tests through slots 14/13 at 0x004CE301/0x004CE326. Slot 3 (0x004CE342) tests the activation mask and clears byte +4 on success.
// UpgradeModule table 0x00C42720 slots 11/12/13/14 target ledger rows getUpgradeActivationMasks (0x00460AAC), performUpgradeFX (0x00460AD3), requiresAllActivationUpgrades (0x00460A98) and requiresAllConflictingUpgrades (0x00460AA2). The last two read module-data bytes +0x114/+0x115. Slot 8 is named by removal-implementation rows, including CommandSetUpgrade 0x004B3B88 and its constructor's table 0x00C57248.
// giveSelfUpgrade (0x0045230C) calls slots 12, 15, 10 and 9, passing true to slot 9. Its target 0x00452354 copies an argument byte to +4 and returns with ret 4; the existing nonvirtual ledger spelling rva00452354 remains declared separately. forceRefreshUpgrade (0x004CE270) calls slot 10 only when byte +4 is set. upgradeMuxXfer (0x004CE397) transfers byte +4 through Xfer slot +0x90. These rowed methods and the constructor remain out of line.
// FireWeaponWhenDeadBehavior::xfer (0x00482BDB) calls upgradeMuxXfer at 0x00482C12 with this+0x20 (0x00482C0F). Friendship gives this confirmed caller access to the protected helper without changing its ledger spelling or the subobject layout.
// Donor facts: Zero Hour GameLogic/Module/UpgradeModule.h supplies m_upgradeExecuted and the matching method names, including wouldUpgrade, resetUpgrade, isSubObjectsUpgrade, setUpgradeExecuted, processUpgradeRemoval and upgradeMuxLoadPostProcess. BFME2 adds postUpgradeCheck, removal implementation and the second all/any predicate; slot 7 remains neutral because its name is unproved. No separately registered parent header exists for this mix-in.

#pragma once

#ifndef BFME2_UPGRADEMUX_H
#define BFME2_UPGRADEMUX_H

template <int NUMBITS> class BitFlags;
struct UpgradeMaskType;
class Xfer;

class UpgradeMux
{
    friend class FireWeaponWhenDeadBehavior;

public:
    UpgradeMux();
    void giveSelfUpgrade();
    void rva00452354(bool executed);

    virtual bool isAlreadyUpgraded() const;
    virtual bool attemptUpgrade(const BitFlags<128> &keyMask);
    virtual bool wouldUpgrade(const BitFlags<128> &keyMask) const;
    virtual bool resetUpgrade(const BitFlags<128> &keyMask);
    virtual bool isSubObjectsUpgrade();
    virtual void forceRefreshUpgrade();
    virtual void postUpgradeCheck();
    virtual bool vslot07() const;
    virtual void upgradeRemovalImplementation() = 0;
    virtual void setUpgradeExecuted(bool executed);
    virtual void upgradeImplementation() = 0;
    virtual void getUpgradeActivationMasks(UpgradeMaskType &activation, UpgradeMaskType &conflicting) const = 0;
    virtual void performUpgradeFX() = 0;
    virtual bool requiresAllActivationUpgrades() const = 0;
    virtual bool requiresAllConflictingUpgrades() const = 0;
    virtual void processUpgradeRemoval() = 0;

protected:
    virtual void upgradeMuxXfer(Xfer *xfer);
    virtual void upgradeMuxLoadPostProcess();

public:
    bool m_upgradeExecuted;
};

#endif
