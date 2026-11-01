// cl: /DNDEBUG /MD
//
// ??0StancesBehavior@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0045EF80, 54 bytes.
// Behavior-side ctor completing the StancesBehavior file-unit (poolkey rowed at
// 0x45EFBC; proc rowed at 0x45ED8C; ModuleData factory rowed at 0x24B3B4;
// instance factory rowed at 0x24B37C news 0x34 with this pinned 2-arg ctor).
//
// Retail shape: UpdateModule base (rowed 0x253390) + member at +0x20 via the
// pinned 0x330757 ctor + trailing zero at +0x30 + primary vtable 0xC424DC +
// secondaries 0xBEFF90/+0x0C and 0xC424D0/+0x10. The +0x20 member spans 0x10
// bytes (next explicit store is +0x30); its 23B body (Vector_base 0x211E58 +
// or -1 at +0x0C) fits a vector plus flag word.

// The retail table at RVA 0x008424DC: 13 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GStancesBehavior@@UAEPAXI@Z")();
void __identifier("?loadPostProcess@Rva00497805@@MAEXXZ")();
void __identifier("?Rva0045EFB6Get@@YAHXZ")();
void __identifier("?xfer@StancesBehavior@@MAEXPAVXfer@@@Z")();
void __identifier("?getModuleNameKey@StancesBehavior@@UBE?AW4NameKeyType@@XZ")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
void __identifier("?Add_Dependencies_To_List@RenderObjClass@@MAEXAAV?$DynamicVectorClass@VStringClass@@@@_N@Z")();
void __identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?getUpdatePhase@UpdateModule@@MBE?AW4SleepyUpdatePhase@@XZ")();
}
extern "C" const void *const vtbl_00C424DC[13] = {
	(const void *)&__identifier("??_GStancesBehavior@@UAEPAXI@Z"), // slot 0 0x0045F068
	(const void *)&__identifier("?loadPostProcess@Rva00497805@@MAEXXZ"), // slot 1 0x00497805
	(const void *)&__identifier("?Rva0045EFB6Get@@YAHXZ"), // slot 2 0x0045EFB6
	(const void *)&__identifier("?xfer@StancesBehavior@@MAEXPAVXfer@@@Z"), // slot 3 0x0045ED9D
	(const void *)&__identifier("?getModuleNameKey@StancesBehavior@@UBE?AW4NameKeyType@@XZ"), // slot 4 0x0045EFBC
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 5 0x000B3FD0
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 6 0x000B3FD0
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 7 0x000B3FD0
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 8 0x000B3FD0
	(const void *)&__identifier("?Add_Dependencies_To_List@RenderObjClass@@MAEXAAV?$DynamicVectorClass@VStringClass@@@@_N@Z"), // slot 9 0x0050B238
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 10 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 11 0x000D43D0
	(const void *)&__identifier("?getUpdatePhase@UpdateModule@@MBE?AW4SleepyUpdatePhase@@XZ"), // slot 12 0x0022C4CB
};

extern "C" const void *const __identifier("??_7StancesBehavior@@6BStancesBehaviorInterfaceB@@@")[];  // vftable 0x00C424D0

extern "C" const void *const __identifier("??_7AttributeModifierPoolUpdate@@6BBehaviorModuleInterface@@@")[];  // folded vftable 0x00BEFF90 (80 classes), by the name its definer AttributeModifierPoolUpdate.cpp emits on the canonical BehaviorModule chain (data ledger: ...@@6BBehaviorModuleOther@@@)

class Thing;
class ModuleData;

class Rva00330757Member
{
public:
	Rva00330757Member();
private:
	char m_data[0x10];
};

class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
protected:
	const void *m_vtable;
	char m_pad04[8];
	const void *m_p0C;
	const void *m_p10;
	char m_pad14[0x0C];
};

class StancesBehavior : public UpdateModule
{
public:
	StancesBehavior(Thing *thing, const ModuleData *moduleData);
private:
	Rva00330757Member m_member20;
	int m_30;
};

// ??0StancesBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x0045EF80
StancesBehavior::StancesBehavior(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	m_30 = 0;
	m_vtable = reinterpret_cast<const void *>(((unsigned int)vtbl_00C424DC));
	m_p0C = reinterpret_cast<const void *>(((unsigned int)__identifier("??_7AttributeModifierPoolUpdate@@6BBehaviorModuleInterface@@@")));
	m_p10 = reinterpret_cast<const void *>(((unsigned int)__identifier("??_7StancesBehavior@@6BStancesBehaviorInterfaceB@@@")));
}
