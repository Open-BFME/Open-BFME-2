// cl: /O1 /MD
//
// Destructors of the four ObjectHelper modules, each tail-calling
// ObjectHelper::~ObjectHelper at 0x004DF7C2 after storing its three vftables
// at +0x00, +0x0C and +0x10.
//
// Target facts: each destructor stores the vftables its class's constructor
// stores (ObjectDefectionHelper 0x00BFBD40 / 0x00BEFF90 / 0x00BFBD34,
// ObjectRecoveryHelper 0x00BFBD98 / 0x00BEFF90 / 0x00BFBD8C,
// ObjectRepulsorHelper 0x00BFBDF0 / 0x00BEFF90 / 0x00BFBDE4,
// ObjectWeaponStatusHelper 0x00BFBE48 / 0x00BEFF90 / 0x00BFBE3C), and the
// +0x0C table is UpdateModule's BehaviorModuleInterface table. So each class
// derives from the canonical ObjectHelper (UpdateModule) chain, and each view
// declares the overrides its constructor unit's view declares
// (Code/GameEngine/Source/GameLogic/Object/Helper/*HelperCtor.cpp), so this
// unit's vftable copies are those units' copies.

#include "../../Include/GameLogic/Module/ObjectHelper.h"

// MiBase1 is no base here; this unit is still the one that defines its slot.
#include "../../Include/Common/MiBase1.h"

// ?f1@MiBase1@@UAEXXZ present-unmatched
void MiBase1::f1() {}

class ObjectDefectionHelper : public ObjectHelper
{
public:
	virtual ~ObjectDefectionHelper();

	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();
	virtual DisabledMaskType getDisabledTypesToProcess() const;

protected:
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);
};

ObjectDefectionHelper::~ObjectDefectionHelper()
{
}

class ObjectRecoveryHelper : public ObjectHelper
{
public:
	virtual ~ObjectRecoveryHelper();

	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();

protected:
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);
};

ObjectRecoveryHelper::~ObjectRecoveryHelper()
{
}

class ObjectRepulsorHelper : public ObjectHelper
{
public:
	virtual ~ObjectRepulsorHelper();

	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();

protected:
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);
};

ObjectRepulsorHelper::~ObjectRepulsorHelper()
{
}

class ObjectWeaponStatusHelper : public ObjectHelper
{
public:
	virtual ~ObjectWeaponStatusHelper();

	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();
	virtual DisabledMaskType getDisabledTypesToProcess() const;

protected:
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);
	virtual SleepyUpdatePhase getUpdatePhase() const;
};

ObjectWeaponStatusHelper::~ObjectWeaponStatusHelper()
{
}
