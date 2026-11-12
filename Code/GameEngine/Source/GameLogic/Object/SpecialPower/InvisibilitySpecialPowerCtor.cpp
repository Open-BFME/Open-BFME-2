// cl: /DNDEBUG /MD
//
// ??0InvisibilitySpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x004C23A4, 42 bytes. Behavior-side ctor completing the
// InvisibilitySpecialPower file-unit (poolkey rowed at 0x4C23D4, ModuleData
// proc/factory/ctor rowed at 0x4C2389/0x2518CB/0x4C244D, behavior instance
// factory rowed at 0x251893 news 0x34 with this ctor as sole raw caller).
//
// Shape: frameless single-base ctor over the rowed SpecialPowerModule base
// 0x493C5A with three explicit vtable stores at +0/+0xC/+0x10 via byte-wise
// pointer casts (StopSpecialPower precedent: explicit stores, no virtuals
// declared anywhere so no vtable is emitted here; all three immediates are
// DIR32-masked in comparison). Zero new pins (base resolves via the
// rowed SpecialPowerModule spelling).

// Retail table 0x00C5C4B8 (25 slots), stored by the constructor below. Own the
// complete initialized table instead of a one-byte stand-in (Rva004DF324Dtor.cpp
// s_10 precedent): each slot names a matched row at retail's slot target, taken
// by address and never called through these erased signatures.
extern "C" {
void __identifier("?eq@Rva002687D0@@QBE_NH@Z")();
void __identifier("?isReady@SpecialPowerModule@@UBE_NXZ")();
void __identifier("?getPercentReady@SpecialPowerModule@@UBEMXZ")();
void __identifier("?rva00251C08@Rva00251C08@@QAE_NXZ")();
void __identifier("?rva00493AB7@Rva00493AB7@@QAEIXZ")();
void __identifier("?getPowerName@SpecialPowerModule@@UBE?AVAsciiString@@XZ")();
void __identifier("?get@Rva00493236PtrChaseField@@QBEHXZ")();
void __identifier("?onSpecialPowerCreation@SpecialPowerModule@@UAEXXZ")();
void __identifier("?rva0010670B@Rva002217EA@@QAEXPBVImage@@@Z")();
void __identifier("?pauseCountdown@SpecialPowerModule@@UAEX_N@Z")();
void __identifier("?doSpecialPower@SpecialPowerModule@@UAEXI@Z")();
void __identifier("?doSpecialPowerAtObject@InvisibilitySpecialPower@@UAEXPAVObject@@I@Z")();
void __identifier("?doSpecialPowerAtLocation@InvisibilitySpecialPower@@UAEXPBUCoord3D@@I@Z")();
void __identifier("?doSpecialPowerUsingWaypoints@SpecialPowerModule@@UAEXPBUCoord3D@@PBVWaypoint@@I@Z")();
void __identifier("?markSpecialPowerTriggered@SpecialPowerModule@@UAEXPBUCoord3D@@@Z")();
void __identifier("?startPowerRecharge@SpecialPowerModule@@UAEXM@Z")();
void __identifier("?rva00493218@InvisibilitySpecialPower@@UBE?AVRva002390CB@@XZ")();
void __identifier("?rva00251C2C@Rva00251C2C@@QAEXXZ")();
void __identifier("?rva0049466D@SpecialPowerModule@@UAE_NPBUCoord3D@@@Z")();
void __identifier("?get@Bfme939Helper@@QBEHXZ")();
void __identifier("?get@Rva004932D5ByteChaseField@@QBEEXZ")();
void __identifier("?rva0049329E@Rva0049329E@@QAEXXZ")();
void __identifier("?get@Rva004BF893LeaField@@QBEPAXXZ")();
}
extern const void *const g_00C5C4B8[25] = {
	(const void *)&__identifier("?eq@Rva002687D0@@QBE_NH@Z"), //  0 0x0049323D
	(const void *)&__identifier("?isReady@SpecialPowerModule@@UBE_NXZ"), //  1 0x004934DE
	(const void *)&__identifier("?getPercentReady@SpecialPowerModule@@UBEMXZ"), //  2 0x0049355E
	(const void *)&__identifier("?rva00251C08@Rva00251C08@@QAE_NXZ"), //  3 0x00251C08
	(const void *)&__identifier("?rva00493AB7@Rva00493AB7@@QAEIXZ"), //  4 0x00493AB7
	(const void *)&__identifier("?getPowerName@SpecialPowerModule@@UBE?AVAsciiString@@XZ"), //  5 0x004934B8
	(const void *)&__identifier("?get@Rva00493236PtrChaseField@@QBEHXZ"), //  6 0x00493236
	(const void *)&__identifier("?onSpecialPowerCreation@SpecialPowerModule@@UAEXXZ"), //  7 0x004933C2
	(const void *)&__identifier("?rva0010670B@Rva002217EA@@QAEXPBVImage@@@Z"), //  8 0x0010670B
	(const void *)&__identifier("?pauseCountdown@SpecialPowerModule@@UAEX_N@Z"), //  9 0x00492FC2
	(const void *)&__identifier("?doSpecialPower@SpecialPowerModule@@UAEXI@Z"), // 10 0x0049490F
	(const void *)&__identifier("?doSpecialPowerAtObject@InvisibilitySpecialPower@@UAEXPAVObject@@I@Z"), // 11 0x004C2419
	(const void *)&__identifier("?doSpecialPowerAtLocation@InvisibilitySpecialPower@@UAEXPBUCoord3D@@I@Z"), // 12 0x004C2517
	(const void *)&__identifier("?doSpecialPowerUsingWaypoints@SpecialPowerModule@@UAEXPBUCoord3D@@PBVWaypoint@@I@Z"), // 13 0x00494A2A
	(const void *)&__identifier("?markSpecialPowerTriggered@SpecialPowerModule@@UAEXPBUCoord3D@@@Z"), // 14 0x00494591
	(const void *)&__identifier("?startPowerRecharge@SpecialPowerModule@@UAEXM@Z"), // 15 0x0049369D
	(const void *)&__identifier("?rva00493218@InvisibilitySpecialPower@@UBE?AVRva002390CB@@XZ"), // 16 0x00493218
	(const void *)&__identifier("?rva00251C2C@Rva00251C2C@@QAEXXZ"), // 17 0x00251C2C
	(const void *)&__identifier("?rva0049466D@SpecialPowerModule@@UAE_NPBUCoord3D@@@Z"), // 18 0x0049466D
	(const void *)&__identifier("?rva00251C2C@Rva00251C2C@@QAEXXZ"), // 19 0x00251C2C
	(const void *)&__identifier("?get@Bfme939Helper@@QBEHXZ"), // 20 0x0030F2C7
	(const void *)&__identifier("?get@Rva004932D5ByteChaseField@@QBEEXZ"), // 21 0x004932D5
	(const void *)&__identifier("?rva0049329E@Rva0049329E@@QAEXXZ"), // 22 0x0049329E
	(const void *)&__identifier("?get@Rva004BF893LeaField@@QBEPAXXZ"), // 23 0x004BF893
	(const void *)&__identifier("?get@Rva004BF893LeaField@@QBEPAXXZ")  // 24 0x004BF893
};
// Retail table 0x00C5C51C (14 slots), stored by the constructor below. Own the
// complete initialized table instead of a one-byte stand-in (Rva004DF324Dtor.cpp
// s_10 precedent): each slot names a matched row at retail's slot target, taken
// by address and never called through these erased signatures.
extern "C" {
void __identifier("??_GRva004C70A8@@UAEPAXI@Z")();
void __identifier("?loadPostProcess@SpecialPowerModule@@MAEXXZ")();
void __identifier("?Rva004C23CEGet@@YAHXZ")();
void __identifier("?xfer@Rva004C8A95@@MAEXPAVXfer@@@Z")();
void __identifier("?getModuleNameKey@InvisibilitySpecialPower@@UBE?AW4NameKeyType@@XZ")();
void __identifier("??1Elem4@@QAE@XZ")();
void __identifier("?rva005F267E@Rva0086EE20@@UAEXHM@Z")();
void __identifier("?getSpecialPower@BehaviorModule@@UAEPAVSpecialPowerModuleInterface@@XZ")();
void __identifier("?rva00493805@SpecialPowerModule@@UAEXXZ")();
void __identifier("?ApplyPowerToObject@SpecialPowerModule@@UAEXPAVObject@@HPBV?$BitFlags@$0L@@@@Z")();
}
extern const void *const g_00C5C51C[14] = {
	(const void *)&__identifier("??_GRva004C70A8@@UAEPAXI@Z"), //  0 0x00254B56
	(const void *)&__identifier("?loadPostProcess@SpecialPowerModule@@MAEXXZ"), //  1 0x004C8A2F: jmp 0x00493B1E, named by its target
	(const void *)&__identifier("?Rva004C23CEGet@@YAHXZ"), //  2 0x004C23CE
	(const void *)&__identifier("?xfer@Rva004C8A95@@MAEXPAVXfer@@@Z"), //  3 0x004C8A95
	(const void *)&__identifier("?getModuleNameKey@InvisibilitySpecialPower@@UBE?AW4NameKeyType@@XZ"), //  4 0x004C23D4
	(const void *)&__identifier("??1Elem4@@QAE@XZ"), //  5 0x000B3FD0
	(const void *)&__identifier("??1Elem4@@QAE@XZ"), //  6 0x000B3FD0
	(const void *)&__identifier("??1Elem4@@QAE@XZ"), //  7 0x000B3FD0
	(const void *)&__identifier("??1Elem4@@QAE@XZ"), //  8 0x000B3FD0
	(const void *)&__identifier("?rva005F267E@Rva0086EE20@@UAEXHM@Z"), //  9 0x0050B238
	(const void *)&__identifier("?getSpecialPower@BehaviorModule@@UAEPAVSpecialPowerModuleInterface@@XZ"), // 10 0x000D43D0
	(const void *)&__identifier("?getSpecialPower@BehaviorModule@@UAEPAVSpecialPowerModuleInterface@@XZ"), // 11 0x000D43D0
	(const void *)&__identifier("?rva00493805@SpecialPowerModule@@UAEXXZ"), // 12 0x00493805
	(const void *)&__identifier("?ApplyPowerToObject@SpecialPowerModule@@UAEXPAVObject@@HPBV?$BitFlags@$0L@@@@Z")  // 13 0x00493EA7
};

extern "C" const void *const __identifier("??_7SpecialPowerModule@@6BBehaviorModuleInterface@@@")[];  // folded vftable 0x00BEFCF8 (38 classes), by its data-ledger name

class Thing;
class ModuleData;

class SpecialPowerModule
{
public:
	SpecialPowerModule(Thing *thing, const ModuleData *moduleData);
};

class InvisibilitySpecialPower : public SpecialPowerModule
{
public:
	InvisibilitySpecialPower(Thing *thing, const ModuleData *moduleData);
};

// ??0InvisibilitySpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z @0x004C23A4
InvisibilitySpecialPower::InvisibilitySpecialPower(Thing *thing, const ModuleData *moduleData) :
	SpecialPowerModule(thing, moduleData)
{
	*(unsigned int *)this = (unsigned int)&g_00C5C51C;
	*(unsigned int *)((char *)this + 0xC) = ((unsigned int)__identifier("??_7SpecialPowerModule@@6BBehaviorModuleInterface@@@"));
	*(unsigned int *)((char *)this + 0x10) = (unsigned int)&g_00C5C4B8;
}
