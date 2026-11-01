// cl: /DNDEBUG /MD /GX
//
// ??0RespawnUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004AF096,
// 128 bytes. Behavior-side ctor (rowed instance factory 0x24F8F6 news
// 0x44 with this pinned 2-arg ctor as its sole raw caller at 0x24F91D).
//
// Shape follows the SlaveWatcherBehavior precedent over the same rowed
// UpdateModule base 0x253390: EH prologue via /GX plus the declared-only
// base dtor, a minus-one-homed local (or-ecx) plus a zero-homed local,
// the setWakeFrame arg pushes hoisted above the stores (no intervening
// call), minus-one at +0x28/+0x34/+0x38/+0x3C, the three derived vtable
// installs, zeros at +0x2C/+0x30/+0x24, byte zeros at +0x40/+0x41, minus-
// one float at +0x20 via the pooled -1.0f literal (/arch:SSE movss), and
// the setWakeFrame tail (protected IAEX Object-uint spelling resolves via
// the existing pin at 0x44DF71). Row supersedes the ctor pin.

extern "C" const void *const __identifier("??_7AttributeModifierPoolUpdate@@6BBehaviorModuleOther@@@")[];  // folded vftable 0x00BEFF90 (80 classes), by the name its definer AttributeModifierPoolUpdate.cpp emits on the canonical BehaviorModule chain (data ledger: ...@@6BBehaviorModuleOther@@@)

// The retail table at RVA 0x008556B0: 16 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva004AF17D@@QAEPAXI@Z")();
void __identifier("?loadPostProcess@Rva00497805@@MAEXXZ")();
void __identifier("?name@RespawnUpdate@@QBEPBDXZ")();
void __identifier("?xfer@RespawnUpdate@@MAEXPAVXfer@@@Z")();
void __identifier("?getModuleNameKey@RespawnUpdate@@UBE?AW4NameKeyType@@XZ")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
void __identifier("?Add_Dependencies_To_List@RenderObjClass@@MAEXAAV?$DynamicVectorClass@VStringClass@@@@_N@Z")();
void __identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?getUpdatePhase@UpdateModule@@MBE?AW4SleepyUpdatePhase@@XZ")();
void __identifier("?getPercentReady@RespawnUpdate@@UAEMPAH@Z")();
void __identifier("?getDeadImage@RespawnUpdate@@UAEPBVImage@@XZ")();
void __identifier("?get@Rva005C4FEBByteField@@QBEEXZ")();
}
extern const void *const g_00C556B0[16] = {
	(const void *)&__identifier("??_GRva004AF17D@@QAEPAXI@Z"), // slot 0 0x004AF161
	(const void *)&__identifier("?loadPostProcess@Rva00497805@@MAEXXZ"), // slot 1 0x00497805
	(const void *)&__identifier("?name@RespawnUpdate@@QBEPBDXZ"), // slot 2 0x004AF15B
	(const void *)&__identifier("?xfer@RespawnUpdate@@MAEXPAVXfer@@@Z"), // slot 3 0x004AF00B
	(const void *)&__identifier("?getModuleNameKey@RespawnUpdate@@UBE?AW4NameKeyType@@XZ"), // slot 4 0x004AF116
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 5 0x000B3FD0
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 6 0x000B3FD0
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 7 0x000B3FD0
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 8 0x000B3FD0
	(const void *)&__identifier("?Add_Dependencies_To_List@RenderObjClass@@MAEXAAV?$DynamicVectorClass@VStringClass@@@@_N@Z"), // slot 9 0x0050B238
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 10 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 11 0x000D43D0
	(const void *)&__identifier("?getUpdatePhase@UpdateModule@@MBE?AW4SleepyUpdatePhase@@XZ"), // slot 12 0x0022C4CB
	(const void *)&__identifier("?getPercentReady@RespawnUpdate@@UAEMPAH@Z"), // slot 13 0x004AEFAD
	(const void *)&__identifier("?getDeadImage@RespawnUpdate@@UAEPBVImage@@XZ"), // slot 14 0x004AF2DE
	(const void *)&__identifier("?get@Rva005C4FEBByteField@@QBEEXZ"), // slot 15 0x005C4FEB
};
// The retail table at RVA 0x008556A4: 3 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("?update@RespawnUpdate@@UAE?AW4UpdateSleepTime@@XZ")();
void __identifier("?getDisabledTypesToProcess@Rva004DF396@@UBE?AV?$BitFlags@$0L@@@XZ")();
void __identifier("?rva0044DF8D@UpdateModule@@UAEXW4UpdateSleepTime@@@Z")();
}
extern const void *const g_00C556A4[3] = {
	(const void *)&__identifier("?update@RespawnUpdate@@UAE?AW4UpdateSleepTime@@XZ"), // slot 0 0x004AF92F
	(const void *)&__identifier("?getDisabledTypesToProcess@Rva004DF396@@UBE?AV?$BitFlags@$0L@@@XZ"), // slot 1 0x004DF396
	(const void *)&__identifier("?rva0044DF8D@UpdateModule@@UAEXW4UpdateSleepTime@@@Z"), // slot 2 0x0044DF8D
};

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
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

class RespawnUpdate : public UpdateModule
{
public:
	RespawnUpdate(Thing *thing, const ModuleData *moduleData);

private:
	float m_20;
	unsigned int m_24;
	unsigned int m_28;
	unsigned int m_2C;
	unsigned int m_30;
	unsigned int m_34;
	unsigned int m_38;
	unsigned int m_3C;
	unsigned char m_40;
	unsigned char m_41;
};

// ??0RespawnUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x004AF096
RespawnUpdate::RespawnUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	float negOne = -1.0f;
	int minusOne = -1;
	int zero = 0;
	m_34 = minusOne;
	m_38 = minusOne;
	m_3C = minusOne;
	m_28 = minusOne;
	m_vtable = (const void *)g_00C556B0;
	m_secondary0C = (const void *)((unsigned int)__identifier("??_7AttributeModifierPoolUpdate@@6BBehaviorModuleOther@@@"));
	m_secondary10 = (const void *)g_00C556A4;
	m_2C = zero;
	m_30 = zero;
	m_40 = zero;
	m_20 = negOne;
	m_41 = zero;
	m_24 = zero;
	setWakeFrame(m_object, UPDATE_SLEEP_FOREVER);
}
