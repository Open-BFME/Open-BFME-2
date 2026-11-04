// cl: /DNDEBUG /MD /GX
//
// ??0TerrainResourceBehavior@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x0048209B, 125 bytes. Behavior-side ctor (rowed instance factory
// 0x24C26C with this pinned 2-arg ctor as its sole raw caller at
// 0x24C293).
//
// Shape follows the SlaveWatcherBehavior precedent over the same rowed
// UpdateModule base 0x253390: EH prologue via /GX plus the declared-only
// base dtor, a two-phase +0x20/+0x24 slot pair via sourced-before
// address-take, the setWakeFrame arg pushes hoisted above the stores (no
// intervening call), the three derived vtable installs, immediate false
// and true bytes at +0x28/+0x29, one float zero at +0x2C via an xmm0-homed
// fzero local (/arch:SSE emits retail xorps+movss), and the setWakeFrame
// tail (protected IAEX Object-uint spelling resolves via the existing pin
// at 0x44DF71). Row supersedes the ctor pin.

extern "C" const void *const __identifier("??_7FakePathfindPortalBehaviour@@6BBehaviorModuleInterface@@@")[];  // folded vftable 0x00C42B60 (3 classes), the name FakePathfindPortalBehaviourDtor.cpp emits
extern "C" const void *const __identifier("??_7GhostObject@@6BRva001B3E60SecondBaseCore@@@")[];  // folded vftable 0x00C4EF80 (7 classes), by its data-ledger name

extern "C" const void *const __identifier("??_7Rva00481F82@@6BRva00481F82_S4@@@")[];  // vftable 0x00C493E8
extern "C" const void *const __identifier("??_7Rva00481F82@@6BRva00481F82_S3@@@")[];  // vftable 0x00C493F8
extern "C" const void *const __identifier("??_7Rva00481F82@@6BRva00481F82_S2@@@")[];  // vftable 0x00C493FC
// The retail table at RVA 0x00849408: 13 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva00481F82@@UAEPAXI@Z")();
void __identifier("?loadPostProcess@TerrainResourceBehavior@@MAEXXZ")();
void __identifier("?name@Rva00481FA9Named@@QBEPBDXZ")();
void __identifier("?xfer@TerrainResourceBehavior@@MAEXPAVXfer@@@Z")();
void __identifier("?getModuleNameKey@TerrainResourceBehavior@@UBE?AW4NameKeyType@@XZ")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
void __identifier("?rva00482134@Rva00482134@@QAEXXZ")();
void __identifier("?Add_Dependencies_To_List@RenderObjClass@@MAEXAAV?$DynamicVectorClass@VStringClass@@@@_N@Z")();
void __identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?getUpdatePhase@UpdateModule@@MBE?AW4SleepyUpdatePhase@@XZ")();
}
extern "C" const void *const vtbl_00C49408[13] = {
	(const void *)&__identifier("??_GRva00481F82@@UAEPAXI@Z"), // slot 0 0x00482118
	(const void *)&__identifier("?loadPostProcess@TerrainResourceBehavior@@MAEXXZ"), // slot 1 0x0048223D
	(const void *)&__identifier("?name@Rva00481FA9Named@@QBEPBDXZ"), // slot 2 0x00481FA9
	(const void *)&__identifier("?xfer@TerrainResourceBehavior@@MAEXPAVXfer@@@Z"), // slot 3 0x004821CB
	(const void *)&__identifier("?getModuleNameKey@TerrainResourceBehavior@@UBE?AW4NameKeyType@@XZ"), // slot 4 0x00481FBD
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 5 0x000B3FD0
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 6 0x000B3FD0
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 7 0x000B3FD0
	(const void *)&__identifier("?rva00482134@Rva00482134@@QAEXXZ"), // slot 8 0x00482134
	(const void *)&__identifier("?Add_Dependencies_To_List@RenderObjClass@@MAEXAAV?$DynamicVectorClass@VStringClass@@@@_N@Z"), // slot 9 0x0050B238
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 10 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 11 0x000D43D0
	(const void *)&__identifier("?getUpdatePhase@UpdateModule@@MBE?AW4SleepyUpdatePhase@@XZ"), // slot 12 0x0022C4CB
};
extern "C" const void *const __identifier("??_7SecondaryModuleBase@FXParticleSystem@@6B@")[];  // folded vftable 0x00C1C780 (49 classes), by its data-ledger name

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../../../../Include/GameLogic/Module/UpdateModule.h"

class __declspec(novtable) TRB_Iface3 { public: virtual void slot3(); };
class __declspec(novtable) TRB_Iface4 { public: virtual void slot4(); };

// Retail's named table providers are retained below; novtable leaves their
// installation explicit while describing the native interface subobjects.
class __declspec(novtable) TerrainResourceBehavior : public UpdateModule, public TRB_Iface3, public TRB_Iface4
{
public:
	TerrainResourceBehavior(Thing *thing, const ModuleData *moduleData);
	virtual ~TerrainResourceBehavior();
	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();
protected:
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();
private:
	bool m_registered;
	bool m_sleepAfterRegister;
	float m_incomeScale;
};

// ??0TerrainResourceBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x0048209B
TerrainResourceBehavior::TerrainResourceBehavior(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	float fzero = 0.0f;
	int *slot20 = reinterpret_cast<int *>(reinterpret_cast<char *>(this) + 0x20);
	int *slot24 = reinterpret_cast<int *>(reinterpret_cast<char *>(this) + 0x24);
	*slot20 = (int)((unsigned int)__identifier("??_7SecondaryModuleBase@FXParticleSystem@@6B@"));
	*slot24 = (int)((unsigned int)__identifier("??_7GhostObject@@6BRva001B3E60SecondBaseCore@@@"));
	*reinterpret_cast<const void **>(this) = (const void *)((unsigned int)vtbl_00C49408);
	*reinterpret_cast<const void **>(reinterpret_cast<char *>(this) + 0x0C) = (const void *)((unsigned int)__identifier("??_7FakePathfindPortalBehaviour@@6BBehaviorModuleInterface@@@"));
	*reinterpret_cast<const void **>(reinterpret_cast<char *>(this) + 0x10) = (const void *)((unsigned int)__identifier("??_7Rva00481F82@@6BRva00481F82_S2@@@"));
	*reinterpret_cast<const void **>(reinterpret_cast<char *>(this) + 0x20) = (const void *)((unsigned int)__identifier("??_7Rva00481F82@@6BRva00481F82_S3@@@"));
	*reinterpret_cast<const void **>(reinterpret_cast<char *>(this) + 0x24) = (const void *)((unsigned int)__identifier("??_7Rva00481F82@@6BRva00481F82_S4@@@"));
	m_registered = false;
	m_sleepAfterRegister = true;
	m_incomeScale = fzero;
	setWakeFrame(m_object, UPDATE_SLEEP_NONE);
}
