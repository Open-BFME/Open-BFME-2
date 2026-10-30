// cl: /DNDEBUG /MD /EHsc
// stlport
//
// ??0ReplenishUnitsBehavior@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x00484227, 154 bytes. Behavior-side ctor (rowed instance factory
// 0x24C599 news 0x28 with this pinned 2-arg ctor as its sole raw caller
// at 0x24C5C0).
//
// Shape follows the RadiateFearUpdate precedent over the same rowed
// UpdateModule base 0x253390: EH prologue via /GX plus the declared-only
// base dtor, the UpgradeMux base at +0x20 built in the init-list (rowed
// 0-arg ctor 0x4CE2A3; base layout mirrors UpgradeModuleCtor.cpp), the
// object pointer homed early, the three derived vtable installs, a vtable
// overwrite of the base, and a conditional wake frame — the module data
// flag at +0x138 selects a GetGameLogicRandomValue call (rowed int twin
// 0x233FF4 over lo/hi/file/line with the TU __FILE__ literal and line
// 0x74) versus the never-wake literal, tail-merged into one setWakeFrame
// tail (protected IAEX Object-uint spelling resolves via the existing pin
// at 0x44DF71). Row supersedes the ctor pin.

// Folded vftables: 0x00C49F20 (2 classes, FireWeaponWhenDamagedBehavior), 0x00C49F78 (3 classes, AttributeModifierAuraUpdate).
// ReplenishUnitsBehavior vftables: UpdateModule 0x00C49F68, BehaviorModuleBase 0x00C4A034.

// base dtor, an UpgradeMux member at +0x20 built in the init-list (rowed
// 0-arg ctor 0x4CE2A3; member layout mirrors UpgradeModuleCtor.cpp), the
// overwrite of the member, and a conditional wake frame — the module data
enum NameKeyType
{
	NK_UNKNOWN = 0
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

class Thing;
class ModuleData;
class Object;
class Xfer;
class ReplenishUnitsBehaviorModuleData;

#include "../../../../Include/Common/ObjectModule.h"

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public ObjectModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);

protected:
	void setWakeFrame(Object *object, UpdateSleepTime frame);
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class UpgradeMux
{
public:
	UpgradeMux();
	virtual bool isUpgradeActive() const = 0;
	void giveSelfUpgrade();

protected:
	virtual void upgradeMuxXfer(Xfer *xfer);

private:
	bool m_upgradeExecuted;
};

class ReplenishUnitsBehavior : public UpdateModule, public UpgradeMux
{
public:
	ReplenishUnitsBehavior(Thing *thing, const ModuleData *moduleData);
	virtual ~ReplenishUnitsBehavior();
	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();
	void rva004842DD(Object *target);

protected:
	virtual void xfer(Xfer *xfer);

private:
	const ReplenishUnitsBehaviorModuleData *getReplenishUnitsBehaviorModuleData() const
	{
		return (const ReplenishUnitsBehaviorModuleData *)m_moduleData;
	}
};

class Rva0025342CMember
{
public:
	Rva0025342CMember *construct();

private:
	unsigned char m_body[0x110];
};

class FXList;

// A 128-bit ObjectStatusMaskType; 0x0023DA79 clears it and sets one bit.
struct ObjectStatusMask
{
	ObjectStatusMask() {}
	bool test(int bit) const { return (m_bits[bit >> 5] >> (bit & 31)) & 1; }
	unsigned m_bits[4];
};

class __declspec(novtable) ReplenishUnitsBehaviorModuleData
{
public:
	ReplenishUnitsBehaviorModuleData();

private:
	friend class ReplenishUnitsBehavior;
	void *m_vtable;			// +0x00
	unsigned int m_04;		// +0x04 (retail never stores)
	Rva0025342CMember m_08;		// +0x08
	float m_replenishRadius;			// +0x118 the replenish radius
	float m_enemyCheckRadius;			// +0x11C the enemy check radius
	const FXList *m_120;		// +0x120 the replenish FX
	ObjectStatusMask m_124;		// +0x124 bitset<128>, the status a target needs
	UpdateSleepTime m_134;		// +0x134 the sleep
	bool m_138;			// +0x138
	bool m_139;			// +0x139 replenish horde members only
};

typedef int Int;
Int GetGameLogicRandomValue(Int lo, Int hi, char *file, int line);

// ??0ReplenishUnitsBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x00484227
ReplenishUnitsBehavior::ReplenishUnitsBehavior(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData), UpgradeMux()
{
	Object *obj = m_object;
	if (((const ReplenishUnitsBehaviorModuleData *)m_moduleData)->m_138)
	{
		giveSelfUpgrade();
		int hi = ((const ReplenishUnitsBehaviorModuleData *)m_moduleData)->m_134;
		setWakeFrame(obj, (UpdateSleepTime)(GetGameLogicRandomValue(1, hi, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Behavior\\ReplenishUnitsBehavior.cpp", 0x74)));
	}
	else
	{
		setWakeFrame(obj, UPDATE_SLEEP_FOREVER);
	}
}
