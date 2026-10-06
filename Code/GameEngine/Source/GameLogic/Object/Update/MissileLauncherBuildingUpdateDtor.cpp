// cl: /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??_GMissileLauncherBuildingUpdate@@UAEPAXI@Z at retail 0x004CDA19 (28B).
// Emitted scalar deleting destructor (flag plus pinned operator delete at
// 0x0002FD60), and ??1MissileLauncherBuildingUpdate@@UAE@XZ at 0x004CD9C0
// (89B): compiler vptr restores, implicit destruction of the trailing
// vector (null-checked 0x30830 free), then the base call. The vector is a
// real member so the implicit destruction and SEH states fall out.
#include <vector>

struct BfmeE16 { float x, y, z, w; };

class Thing;
class ModuleData;

class Object;
class DamageInfo;

// Four-vptr module hierarchy (+0 +0x0C +0x10 +0x20), as in the matched
// GiveOrRestoreUpgradeSpecialPowerDtor.cpp; the dtor's vptr restores are
// compiler-generated, which puts them ahead of the EH state store.
class BehaviorModuleBase
{
public:
	virtual void behaviorModuleBaseAnchor();
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};

class UpdateModuleInterface
{
public:
	virtual void update();
};

// Opaque UpdateModule-derived intermediate; dtor resolves to the pin at
// 0x00451F45.
class Rva0044EF5E : public BehaviorModule, public UpdateModuleInterface
{
public:
	Rva0044EF5E(Thing *thing, const ModuleData *moduleData);
	virtual ~Rva0044EF5E();

protected:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class DamageModuleInterface
{
public:
	virtual void onDamage(DamageInfo *damageInfo);
};

class MissileLauncherBuildingUpdate : public Rva0044EF5E, public DamageModuleInterface
{
public:
	virtual ~MissileLauncherBuildingUpdate();

private:
	unsigned char m_pad24[0x88 - 0x24];
	_STL::vector<BfmeE16> m_tail;		// +0x88
};

MissileLauncherBuildingUpdate::~MissileLauncherBuildingUpdate()
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?behaviorModuleOtherAnchor@BehaviorModuleOther@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
