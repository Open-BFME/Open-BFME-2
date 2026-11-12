// cl: /DNDEBUG /MD
//
// ??0SpecialPowerTimerRefreshSpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z,
// retail 0x00251BDE, 40 bytes. Behavior-side ctor completing the
// SpecialPowerTimerRefreshSpecialPower file-unit (poolkey rowed at
// 0x251C31, name getter rowed at 0x251C76, behavior instance factory rowed
// at 0x254B1E news 0x18 with this ctor as sole raw caller).
//
// Shape: frameless single-base ctor over the rowed SpecialPowerModule base
// 0x493C5A with three explicit vtable stores at +0/+0xC/+0x10 via byte-wise
// pointer casts (StopSpecialPower precedent: explicit stores, no virtuals
// declared anywhere so no vtable is emitted here; all three immediates are
// DIR32-masked in comparison). Zero new pins (base resolves via the
// rowed SpecialPowerModule spelling).

// Retail table 0x00BEFDB4 (14 slots), stored by the constructor below. Own the
// complete initialized table instead of a one-byte stand-in (Rva004DF324Dtor.cpp
// s_10 precedent): each slot names a matched row at retail's slot target, taken
// by address and never called through these erased signatures.
extern "C" {
void __identifier("??_GRva004C70A8@@UAEPAXI@Z")();
void __identifier("?j_004c8a2f@@YAXXZ")();
void __identifier("?name@Rva00251C76Named@@QBEPBDXZ")();
void __identifier("?rva004C38D0@Rva004C38D0@@QAEXPAVXfer@@@Z")();
void __identifier("?getModuleNameKey@SpecialPowerTimerRefreshSpecialPower@@UBE?AW4NameKeyType@@XZ")();
void __identifier("??1Elem4@@QAE@XZ")();
void __identifier("?rva005F267E@Rva0086EE20@@UAEXHM@Z")();
void __identifier("?getSpecialPower@BehaviorModule@@UAEPAVSpecialPowerModuleInterface@@XZ")();
void __identifier("?rva00493805@SpecialPowerModule@@UAEXXZ")();
void __identifier("?ApplyPowerToObject@SpecialPowerTimerRefreshSpecialPower@@UAEXPAVObject@@HPBV?$BitFlags@$0L@@@@Z")();
}
extern const void *const g_00BEFDB4[14] = {
	(const void *)&__identifier("??_GRva004C70A8@@UAEPAXI@Z"), //  0 0x00254B56
	(const void *)&__identifier("?j_004c8a2f@@YAXXZ"), //  1 0x004C8A2F
	(const void *)&__identifier("?name@Rva00251C76Named@@QBEPBDXZ"), //  2 0x00251C76
	(const void *)&__identifier("?rva004C38D0@Rva004C38D0@@QAEXPAVXfer@@@Z"), //  3 0x004C38D0
	(const void *)&__identifier("?getModuleNameKey@SpecialPowerTimerRefreshSpecialPower@@UBE?AW4NameKeyType@@XZ"), //  4 0x00251C31
	(const void *)&__identifier("??1Elem4@@QAE@XZ"), //  5 0x000B3FD0
	(const void *)&__identifier("??1Elem4@@QAE@XZ"), //  6 0x000B3FD0
	(const void *)&__identifier("??1Elem4@@QAE@XZ"), //  7 0x000B3FD0
	(const void *)&__identifier("??1Elem4@@QAE@XZ"), //  8 0x000B3FD0
	(const void *)&__identifier("?rva005F267E@Rva0086EE20@@UAEXHM@Z"), //  9 0x0050B238
	(const void *)&__identifier("?getSpecialPower@BehaviorModule@@UAEPAVSpecialPowerModuleInterface@@XZ"), // 10 0x000D43D0
	(const void *)&__identifier("?getSpecialPower@BehaviorModule@@UAEPAVSpecialPowerModuleInterface@@XZ"), // 11 0x000D43D0
	(const void *)&__identifier("?rva00493805@SpecialPowerModule@@UAEXXZ"), // 12 0x00493805
	(const void *)&__identifier("?ApplyPowerToObject@SpecialPowerTimerRefreshSpecialPower@@UAEXPAVObject@@HPBV?$BitFlags@$0L@@@@Z")  // 13 0x004C38B3
};

extern "C" const void *const __identifier("??_7SpecialPowerModule@@6BBehaviorModuleInterface@@@")[];  // folded vftable 0x00BEFCF8 (38 classes), by its data-ledger name
extern "C" const void *const __identifier("??_7SpecialPowerModule@@6B@")[];  // folded vftable 0x00C5E080 (2 classes), by its data-ledger name

class Thing;
class ModuleData;

class SpecialPowerModule
{
public:
	SpecialPowerModule(Thing *thing, const ModuleData *moduleData);
};

class SpecialPowerTimerRefreshSpecialPower : public SpecialPowerModule
{
public:
	SpecialPowerTimerRefreshSpecialPower(Thing *thing, const ModuleData *moduleData);
};

// ??0SpecialPowerTimerRefreshSpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z @0x00251BDE
SpecialPowerTimerRefreshSpecialPower::SpecialPowerTimerRefreshSpecialPower(Thing *thing, const ModuleData *moduleData) :
	SpecialPowerModule(thing, moduleData)
{
	*(unsigned int *)this = (unsigned int)&g_00BEFDB4;
	*(unsigned int *)((char *)this + 0xC) = ((unsigned int)__identifier("??_7SpecialPowerModule@@6BBehaviorModuleInterface@@@"));
	*(unsigned int *)((char *)this + 0x10) = ((unsigned int)__identifier("??_7SpecialPowerModule@@6B@"));
}
