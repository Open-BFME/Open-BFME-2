// Canonical BFME2 UpgradeModule. Code addresses are RVAs; table addresses are VAs.
// Target facts:
// Constructor 0x00460AEC calls BehaviorModule at 0x00460B04 and UpgradeMux with this+0x10 at 0x00460B12. Its final tables are 0x00C42768 at +0, 0x00C57328 at +0x0C, 0x00C42720 at +0x10 and 0x00C58790 at +0x18. The earlier +0x18 store of 0x00BE2B78 is the three-pure-slot base construction table, not UpgradeModule's table.
// Destructor 0x0046089D restores the +0x10 and +0x18 tables, then BehaviorModule's 0x00BEEA7C and 0x00BEE9C0 at +0 and +0x0C, and jumps to Snapshot teardown 0x0049B47C. These last two stores destroy the base; the constructor's primary table belongs to UpgradeModule. Its slot 0 is deleting destructor 0x00460B50, which calls 0x0046089D and conditionally operator delete 0x0002FD60.
// The constructor writes through +0x1B. ArmorUpgrade's factory pushes 0x1C at 0x0024FDD2 and calls its constructor at 0x0024FDEE; that constructor (0x004B3468) only calls UpgradeModule and replaces the same four tables. Together these bound UpgradeModule's sizeof to 0x1C. BehaviorModule's constructor 0x00253330 establishes its 0x10-byte prefix; UpgradeMux's constructor 0x004CE2A3 clears byte +4, placing m_upgradeExecuted at complete-object +0x14.
// Primary table 0x00C42768 has twelve entries before the class-name literal: 0=0x00460B50, 1=0x0058B03E (tail jump to empty loadPostProcess), 2=0x00460B4A (returns the name literal at 0x00C42798), 3=0x004CE3F9 (xfer), 4=__purecall, 5-8=0x000B3FD0, 9=0x0050B238 (ret 8), 10-11=0x000D43D0 (return zero). Slots 4-11 retain the registered BehaviorModule declarations.
// The +0x0C table has BehaviorModuleInterface's 47 slots. Slot 4 is 0x0045875F, which returns complete-object +0x18; slot 10 is 0x002533D3, which returns complete-object +0x10. Both adjust the interface receiver by -0x0C for the null test. These prove the getDamage and getUpgrade overrides, while the +0x18 base's class name remains unproved.
// The +0x10 table 0x00C42720 has eighteen entries, ending at the primary table:
// 0=0x00098CBC (isAlreadyUpgraded, byte +4), 1=0x004CE27C (attemptUpgrade, one pointer argument), 2=0x004CE2B0 (wouldUpgrade), 3=0x004CE4B0 (the rowed UpgradeModule reset wrapper).
// 4=0x0047A699 (false), 5=0x004CE270 (forceRefreshUpgrade), 6=0x000B3FD0 (postUpgradeCheck), 7=0x00460AE2 (module-data byte +0x116, no argument).
// 8=__purecall (named upgradeRemovalImplementation by leaf rows), 9=0x00452354 (bool setter, ret 4), 10=__purecall (upgradeImplementation by leaf rows and forceRefreshUpgrade's dispatch at 0x004CE278).
// 11=0x00460AAC (getUpgradeActivationMasks), 12/15=0x00460AD3 (performUpgradeFX), 13=0x00460A98 (requiresAllActivationUpgrades), 14=0x00460AA2 (requiresAllConflictingUpgrades), 16=0x004CE397 (upgradeMuxXfer), 17=0x000B3FD0 (empty).
// UpgradeMux's root table 0x00C5FF10 has the same eighteen positions, with 3=0x004CE342, 7=false and 8/10-15=pure. giveSelfUpgrade 0x0045230C dispatches slots 12,15,10,9 in that order, supplying true to slot 9. The ledger names its nonvirtual setter spelling rva00452354 at 0x00452354; setUpgradeExecuted is the donor name for the virtual setter operation.
// The +0x18 table 0x00C58790 has three entries followed by zero: 0/1=0x0047A69C (ret 4), 2=0x000D1407 (ret 12). Its class and method names are unproved, so they remain neutral. Neither this interface nor UpgradeMux has a virtual destructor.
// xfer 0x004CE3F9 calls BehaviorModule xfer 0x004C9C7D, then upgradeMuxXfer 0x004CE397 with this+0x10. The rowed condition helpers are 0x004CE41E, 0x004CE4A0 and 0x004CE4A8; the reset wrapper 0x004CE4B0 subtracts 0x10 before calling the first. Module data +4 and object +8 are also read by 0x004CE41E; 0x00460AAC/0x00460AD3 read them at -0x0C/-8 from the mux receiver.
// Donor facts: Zero Hour UpgradeModule.h supplies BehaviorModule/UpgradeMux inheritance and the matching operation names. BFME2's mask argument is a reference (ledger attemptUpgrade), its rowed getUpgradeActivationMasks uses struct UpgradeMaskType, and its extra slots and +0x18 interface come from the target, not the donor. Slots 7 and 15 retain neutral names because the donor signatures disagree with retail. The BitFlags forward declaration follows the rowed UpgradeMuxAttemptUpgrade.cpp and the registered Thing header; an already included Zero Hour BitFlags definition supplies its own declaration. The decorated name records the template value, not the parameter's signedness.

#pragma once
#ifndef __BFME2_UPGRADEMODULE_H_
#define __BFME2_UPGRADEMODULE_H_

#include "BehaviorModule.h"

class Thing;
class ModuleData;
class Object;
class Xfer;
class UpgradeModuleInterface;
class DamageModuleInterface;
class Rva00406F9C;
struct UpgradeMaskType;
#ifndef __BitFlags_H_
template <int NUMBITS> class BitFlags;
#endif

class UpgradeMux
{
public:
	UpgradeMux();
	virtual bool isAlreadyUpgraded() const;
	virtual bool attemptUpgrade(const BitFlags<128> &keyMask);
	virtual bool wouldUpgrade(const BitFlags<128> &keyMask) const;
	virtual bool rva004CE4B0(Rva00406F9C *mask);
	virtual bool isSubObjectsUpgrade();
	virtual void forceRefreshUpgrade();
	virtual void postUpgradeCheck();
	virtual unsigned char slot07() const;

	void giveSelfUpgrade();
	void rva00452354(bool executed);

protected:
	virtual void upgradeRemovalImplementation() = 0;
	virtual void setUpgradeExecuted(bool executed);
	virtual void upgradeImplementation() = 0;
	virtual void getUpgradeActivationMasks(UpgradeMaskType &activation, UpgradeMaskType &conflicting) const = 0;
	virtual void performUpgradeFX() = 0;
	virtual bool requiresAllActivationUpgrades() const = 0;
	virtual bool requiresAllConflictingUpgrades() const = 0;
	virtual void muxSlot15() = 0;
	virtual void upgradeMuxXfer(Xfer *xfer);
	virtual void upgradeMuxLoadPostProcess();

	bool m_upgradeExecuted; // +0x04
};

class UpgradeModuleInterface18
{
public:
	virtual void vslot18_00(void *) = 0;
	virtual void vslot18_01(void *) = 0;
	virtual void vslot18_02(void *, void *, void *) = 0;
};

class UpgradeModule : public BehaviorModule, public UpgradeMux, public UpgradeModuleInterface18
{
public:
	UpgradeModule(Thing *thing, const ModuleData *moduleData);
	virtual DamageModuleInterface *getDamage()
	{
		return reinterpret_cast<DamageModuleInterface *>(static_cast<UpgradeModuleInterface18 *>(this));
	}
	virtual UpgradeModuleInterface *getUpgrade()
	{
		return reinterpret_cast<UpgradeModuleInterface *>(static_cast<UpgradeMux *>(this));
	}
	void rva004CE41E(bool apply);
	void rva004CE4A0();
	void rva004CE4A8();
	virtual bool rva004CE4B0(Rva00406F9C *mask);
	virtual unsigned char slot07() const;
	virtual void vslot18_00(void *) { }
	virtual void vslot18_01(void *) { }
	virtual void vslot18_02(void *, void *, void *) { }

protected:
	virtual ~UpgradeModule();
	virtual void loadPostProcess();
#ifdef BFME_SNAPSHOT_NAME_SLOT
	virtual const char *GetSnapshotName() const;
#else
	virtual void crc(Xfer *xfer);
#endif
	virtual void xfer(Xfer *xfer);
	virtual void getUpgradeActivationMasks(UpgradeMaskType &activation, UpgradeMaskType &conflicting) const;
	virtual void performUpgradeFX();
	virtual bool requiresAllActivationUpgrades() const;
	virtual bool requiresAllConflictingUpgrades() const;
	virtual void muxSlot15();
};

#endif
