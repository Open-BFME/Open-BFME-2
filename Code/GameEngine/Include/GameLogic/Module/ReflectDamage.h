// Target facts (code addresses are RVAs; table addresses are VAs):
// Factory 0x00250D8A's constructor 0x004BABB4 calls BehaviorModule's, inlines
// DamageModule's and installs 0x00C59CBC/+0, 0x00C597F8/+0x0C and
// 0x00C59CB0/+0x10; destructor 0x004BAB36 restores them. The object is 0x14
// bytes (no member past DamageModule). The primary table's slot 1 is
// loadPostProcess 0x00497805 (jumps to 0x0058B03E), slot 2 the snapshot name
// 0x004BAB4F (returns "ReflectDamage"), slot 3 xfer 0x0045CE8C (Version1, then
// the base xfer) and slot 4 getModuleNameKey 0x004BAB55. The +0x10 table holds
// onDamage 0x004BABFA, onHealing 0x0047A69C and onBodyDamageStateChange
// 0x000D1407.

#pragma once

#ifndef __BFME2_REFLECTDAMAGE_H_
#define __BFME2_REFLECTDAMAGE_H_

#include "DamageModuleClass.h"

class DamageInfo;
class Module;
class ModuleData;
class ReflectDamageModuleData;
class Thing;
class Xfer;

class ReflectDamage : public DamageModule
{
public:
	ReflectDamage(Thing *thing, const ModuleData *moduleData);
	virtual ~ReflectDamage();

	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);
	virtual NameKeyType getModuleNameKey() const;
	virtual void onDamage(DamageInfo *damageInfo);
	virtual void onHealing(DamageInfo *damageInfo);
	virtual void onBodyDamageStateChange(const DamageInfo *damageInfo, BodyDamageType oldState, BodyDamageType newState);

	const ReflectDamageModuleData *getReflectDamageModuleData() const
	{
		return (const ReflectDamageModuleData *)m_moduleData;
	}

protected:
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);
};

#endif // __BFME2_REFLECTDAMAGE_H_
