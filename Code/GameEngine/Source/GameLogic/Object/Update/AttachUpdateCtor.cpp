// cl: /DNDEBUG /MD /GX
//
// ??0AttachUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00491A0F,
// 89 bytes. Behavior-side ctor completing the AttachUpdate file-unit
// (ModuleData proc/factory rowed at 0x491957/0x24D8D2; poolkey rowed at
// 0x491912; behavior instance factory rowed at 0x24D89A news 0x14 with this
// pinned 2-arg ctor as its caller).
//
// Shape follows WallUpgradeUpdate precedent verbatim over the same rowed
// UpdateModule base 0x253390: re-stores the primary vtable slot and the
// +0x0C/+0x10 secondary slots (native subobjects, all immediates
// DIR32-masked) plus an and-zero int at +0x20 plus an or-minus-one int at
// +0x24, and parks the module awake-through-none via setWakeFrame.
// Member names follow the Bloodthirsty donor (m_object at +0x08,
// UPDATE_SLEEP_NONE). /GX for the EH prologue plus the single mid-body
// state store; the declared-only base dtor arms it with no emitted code.
// Zero new pins (base ctor resolves via its row; setWakeFrame resolves via
// the existing IAEX Object-uint pin at 0x44DF71).

extern "C" const void *const __identifier("??_7AttributeModifierPoolUpdate@@6BBehaviorModuleInterface@@@")[];  // folded vftable 0x00BEFF90 (80 classes), by the name AttributeModifierPoolUpdate.cpp emits (the data-ledger spelling ...@@6BBehaviorModuleOther@@@ has no definer)

extern "C" const void *const __identifier("??_7Rva0049188D@@6BRva0049188D_B2@@@")[];  // vftable 0x00C4DB14
// The retail table at RVA 0x0084DB20: 13 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva0049188D@@UAEPAXI@Z")();
void __identifier("?loadPostProcess@Rva00497805@@MAEXXZ")();
void __identifier("?name@Rva004918A6Named@@QBEPBDXZ")();
void __identifier("?xfer@AttachUpdate@@MAEXPAVXfer@@@Z")();
void __identifier("?getModuleNameKey@AttachUpdate@@UBE?AW4NameKeyType@@XZ")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
void __identifier("?Add_Dependencies_To_List@RenderObjClass@@MAEXAAV?$DynamicVectorClass@VStringClass@@@@_N@Z")();
void __identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?getUpdatePhase@UpdateModule@@MBE?AW4SleepyUpdatePhase@@XZ")();
}
extern "C" const void *const vtbl_00C4DB20[13] = {
	(const void *)&__identifier("??_GRva0049188D@@UAEPAXI@Z"), // slot 0 0x00491A68
	(const void *)&__identifier("?loadPostProcess@Rva00497805@@MAEXXZ"), // slot 1 0x00497805
	(const void *)&__identifier("?name@Rva004918A6Named@@QBEPBDXZ"), // slot 2 0x004918A6
	(const void *)&__identifier("?xfer@AttachUpdate@@MAEXPAVXfer@@@Z"), // slot 3 0x004918AC
	(const void *)&__identifier("?getModuleNameKey@AttachUpdate@@UBE?AW4NameKeyType@@XZ"), // slot 4 0x00491912
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 5 0x000B3FD0
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 6 0x000B3FD0
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 7 0x000B3FD0
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 8 0x000B3FD0
	(const void *)&__identifier("?Add_Dependencies_To_List@RenderObjClass@@MAEXAAV?$DynamicVectorClass@VStringClass@@@@_N@Z"), // slot 9 0x0050B238
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 10 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 11 0x000D43D0
	(const void *)&__identifier("?getUpdatePhase@UpdateModule@@MBE?AW4SleepyUpdatePhase@@XZ"), // slot 12 0x0022C4CB
};

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

#include "../../../../Include/GameLogic/Module/UpdateModule.h"

enum ObjectID;
struct Coord3D;
class AttachUpdateModuleData;

// Keep the existing three native table providers. The folded behavior table
// belongs to AttributeModifierPoolUpdate; emitting a new derived table here
// would give the link a second identity for that shared retail address.
class __declspec(novtable) AttachUpdate : public UpdateModule
{
public:
	AttachUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~AttachUpdate();
	virtual UpdateSleepTime update();
	void rva00491AD0();	// 0x00491AD0
	void rva00491C84(Coord3D *out, const Object *parent);	// 0x00491C84, the anchor point
protected:
	virtual void xfer(Xfer *xfer);
private:
	const AttachUpdateModuleData *getAttachUpdateModuleData() const
	{
		return (const AttachUpdateModuleData *)m_moduleData;
	}
	ObjectID m_parentID;	// +0x20
	int m_diedEvaEvent;	// +0x24
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ??0AttachUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x00491A0F
AttachUpdate::AttachUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	*reinterpret_cast<const void **>(this) = vtbl_00C4DB20;
	*reinterpret_cast<const void **>(reinterpret_cast<char *>(this) + 0x0C) = (const void *)((unsigned int)__identifier("??_7AttributeModifierPoolUpdate@@6BBehaviorModuleInterface@@@"));
	*reinterpret_cast<const void **>(reinterpret_cast<char *>(this) + 0x10) = (const void *)((unsigned int)__identifier("??_7Rva0049188D@@6BRva0049188D_B2@@@"));
	m_parentID = (ObjectID)0;
	m_diedEvaEvent = -1;
	setWakeFrame(m_object, (UpdateSleepTime)UPDATE_SLEEP_NONE);
}
