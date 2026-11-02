/* Target facts (addresses are RVAs except table VAs): ctor 0x004B9704 calls BehaviorModule ctor 0x00253330, then stores VA 0x00BE2B78 at +0x10, VA 0x00C598E4 at +0, VA 0x00C597F8 at +0x0C and VA 0x00BE2B78 again at +0x10. BehaviorModule occupies +0..+0x0F; CallHelpOnDamage ctor 0x004BB43C writes its first member at +0x14, bounding DamageModule to 0x14 bytes with no own data.
   VA 0x00C598E4 has 12 primary slots (the DamageModule string starts at VA 0x00C59914): deleting destructor 0x004B973B, loadPostProcess 0x0058B03E, GetSnapshotName 0x004B9735, xfer 0x004CE56D, then BehaviorModule's slots 4..11. VA 0x00C597F8 has 47 slots; only slot 4 differs from BehaviorModule's VA 0x00BEE9C0, selecting 0x002533D3, which converts the +0x0C receiver to +0x10. VA 0x00BE2B78 has exactly three purecall slots and no destructor slot. Deleting destructor 0x004B973B calls 0x004B96CC, which restores VA 0x00BE2B78 at +0x10 and BehaviorModule's VA 0x00BEEA7C/+0 and VA 0x00BEE9C0/+0x0C before tail-calling Snapshot cleanup 0x0049B47C; these are base-teardown tables, not a second DamageModule layout.
   Donor names: Zero Hour DamageModule.h names getDamage and the three DamageModuleInterface callbacks. Retail CallHelpOnDamage's VA 0x00C59FD0 has onDamage 0x004BB547, empty ret4 0x0047A69C and empty ret12 0x000D1407 in that order; the ledger names onHealing 0x00483111 and onBodyDamageStateChange 0x000D1407 in PoisonedBehavior. Callbacks belong only to the secondary interface; declaring them again on DamageModule would add primary slots beyond retail's twelve. */

#pragma once

#ifndef __BFME2_DAMAGEMODULECLASS_H_
#define __BFME2_DAMAGEMODULECLASS_H_

#include "BehaviorModule.h"

class DamageInfo;
enum BodyDamageType;

class DamageModuleInterface
{
public:
	virtual void onDamage(DamageInfo *damageInfo) = 0;
	virtual void onHealing(DamageInfo *damageInfo) = 0;
	virtual void onBodyDamageStateChange(const DamageInfo *damageInfo, BodyDamageType oldState, BodyDamageType newState) = 0;
};

class DamageModule : public BehaviorModule, public DamageModuleInterface
{
public:
	DamageModule(Thing *thing, const ModuleData *moduleData);
	virtual ~DamageModule();

	virtual DamageModuleInterface *getDamage() { return this; }

protected:
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);
};

typedef char DamageModuleSizeIs0x14[sizeof(DamageModule) == 0x14 ? 1 : -1];

#endif
