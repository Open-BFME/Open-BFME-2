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
// +0x0C/+0x10 secondary slots (explicit members, all immediates
// DIR32-masked) plus an and-zero int at +0x20 plus an or-minus-one int at
// +0x24, and parks the module awake-through-none via setWakeFrame.
// Member names follow the Bloodthirsty donor (m_object at +0x08,
// UPDATE_SLEEP_NONE). /GX for the EH prologue plus the single mid-body
// state store; the declared-only base dtor arms it with no emitted code.
// Zero new pins (base ctor resolves via its row; setWakeFrame resolves via
// the existing IAEX Object-uint pin at 0x44DF71).

extern "C" const void *const __identifier("??_7AttributeModifierPoolUpdate@@6BBehaviorModuleOther@@@")[];  // folded vftable 0x00BEFF90 (80 classes), by its data-ledger name

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

class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	~UpdateModule();

protected:
	void setWakeFrame(Object *object, UpdateSleepTime frame);

	const void *m_vtable;
	const ModuleData *m_moduleData;
	Object *m_object;
	const void *m_secondary0C;
	const void *m_secondary10;
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_reserved1C;
};

class AttachUpdate : public UpdateModule
{
public:
	AttachUpdate(Thing *thing, const ModuleData *moduleData);

private:
	int m_20;
	int m_24;
};

// ??0AttachUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x00491A0F
AttachUpdate::AttachUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData),
	m_20(0),
	m_24(-1)
{
	m_vtable = (const void *)((unsigned int)vtbl_00C4DB20);
	m_secondary0C = (const void *)((unsigned int)__identifier("??_7AttributeModifierPoolUpdate@@6BBehaviorModuleOther@@@"));
	m_secondary10 = (const void *)((unsigned int)__identifier("??_7Rva0049188D@@6BRva0049188D_B2@@@"));
	setWakeFrame(m_object, (UpdateSleepTime)UPDATE_SLEEP_NONE);
}
