// cl: /DNDEBUG /MD
//
// ??0BannerCarrierUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00496A98,
// 42 bytes. Behavior-side ctor completing the BannerCarrierUpdate file-unit
// (poolkey rowed at 0x496A1E, behavior instance factory rowed at 0x24E173
// news 0x34 with this ctor as sole raw caller).
//
// Shape: frameless single-base ctor over the rowed UpdateModule base
// 0x253390 with three explicit vtable stores at +0/+0xC/+0x10 via byte-wise
// pointer casts (StopSpecialPower precedent: explicit stores, no virtuals
// declared anywhere so no vtable is emitted here; all three immediates are
// DIR32-masked in comparison). Zero new pins (base resolves via the
// rowed UpdateModule spelling).

extern "C" const void *const __identifier("??_7AttributeModifierPoolUpdate@@6BBehaviorModuleOther@@@")[];  // folded vftable 0x00BEFF90 (80 classes), by its data-ledger name

extern "C" const void *const __identifier("??_7Rva004969FF@@6BRva004969FF_B2@@@")[];  // vftable 0x00C4F82C
// The retail table at RVA 0x0084F838: 13 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva004969FF@@UAEPAXI@Z")();
void __identifier("?loadPostProcess@Rva00497805@@MAEXXZ")();
void __identifier("?name@Rva00496A18Named@@QBEPBDXZ")();
void __identifier("?xfer@Rva0047F94C@@QAEXPAVXfer@@@Z")();
void __identifier("?getModuleNameKey@BannerCarrierUpdate@@UBE?AW4NameKeyType@@XZ")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
void __identifier("?Add_Dependencies_To_List@RenderObjClass@@MAEXAAV?$DynamicVectorClass@VStringClass@@@@_N@Z")();
void __identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?getUpdatePhase@UpdateModule@@MBE?AW4SleepyUpdatePhase@@XZ")();
}
extern "C" const void *const vtbl_00C4F838[13] = {
	(const void *)&__identifier("??_GRva004969FF@@UAEPAXI@Z"), // slot 0 0x00496AC2
	(const void *)&__identifier("?loadPostProcess@Rva00497805@@MAEXXZ"), // slot 1 0x00497805
	(const void *)&__identifier("?name@Rva00496A18Named@@QBEPBDXZ"), // slot 2 0x00496A18
	(const void *)&__identifier("?xfer@Rva0047F94C@@QAEXPAVXfer@@@Z"), // slot 3 0x0047F94C
	(const void *)&__identifier("?getModuleNameKey@BannerCarrierUpdate@@UBE?AW4NameKeyType@@XZ"), // slot 4 0x00496A1E
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

#include "../../../../Include/GameLogic/Module/UpdateModule.h"

class BannerCarrierUpdate : public UpdateModule
{
public:
	BannerCarrierUpdate(Thing *thing, const ModuleData *moduleData);
};

// ??0BannerCarrierUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x00496A98
BannerCarrierUpdate::BannerCarrierUpdate(Thing *thing, const ModuleData *moduleData) :
	UpdateModule(thing, moduleData)
{
	*(unsigned int *)this = ((unsigned int)vtbl_00C4F838);
	*(unsigned int *)((char *)this + 0xC) = ((unsigned int)__identifier("??_7AttributeModifierPoolUpdate@@6BBehaviorModuleOther@@@"));
	*(unsigned int *)((char *)this + 0x10) = ((unsigned int)__identifier("??_7Rva004969FF@@6BRva004969FF_B2@@@"));
}
