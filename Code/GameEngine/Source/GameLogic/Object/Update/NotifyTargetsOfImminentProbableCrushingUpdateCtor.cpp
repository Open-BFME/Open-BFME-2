// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
//
// ??0NotifyTargetsOfImminentProbableCrushingUpdate@@QAE@PAVThing@@PBVModuleData@@@Z,
// retail 0x00253E64, 40 bytes. Behavior-side ctor completing the
// NotifyTargetsOfImminentProbableCrushingUpdate file-unit (poolkey rowed at
// 0x253E8E, name getter rowed at 0x253ED3, behavior instance factory rowed
// at 0x255207 news 0x34 with this ctor as sole raw caller; the Horde twin
// keeps its own poolkey 0x253DB2, factory 0x2551CF and pinned ctor 0x253D88).
//
// Shape: frameless single-base ctor over the rowed UpdateModule base
// 0x253390 with three explicit vtable stores at +0/+0xC/+0x10 via byte-wise
// pointer casts (StopSpecialPower precedent: explicit stores, no virtuals
// declared anywhere so no vtable is emitted here; all three immediates are
// DIR32-masked in comparison). Zero new pins (base resolves via the
// rowed UpdateModule spelling).

extern "C" const void *const __identifier("??_7AttributeModifierPoolUpdate@@6BBehaviorModuleInterface@@@")[];  // folded vftable 0x00BEFF90 (80 classes), by the name its definer AttributeModifierPoolUpdate.cpp emits on the canonical BehaviorModule chain (the data-ledger spelling ...@@6BBehaviorModuleOther@@@ has no definer)

extern "C" const void *const __identifier("??_7Rva00253EF5@@6BRva00253EF5_B2@@@")[];  // vftable 0x00BF1860
// The retail table at RVA 0x007F186C: 13 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva00253EF5@@UAEPAXI@Z")();
void __identifier("?loadPostProcess@Rva00497805@@MAEXXZ")();
void __identifier("?name@Rva00253ED3Named@@QBEPBDXZ")();
void __identifier("?xfer@NotifyTargetsOfImminentProbableCrushingUpdate@@MAEXPAVXfer@@@Z")();
void __identifier("?getModuleNameKey@NotifyTargetsOfImminentProbableCrushingUpdate@@UBE?AW4NameKeyType@@XZ")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
void __identifier("?Add_Dependencies_To_List@RenderObjClass@@MAEXAAV?$DynamicVectorClass@VStringClass@@@@_N@Z")();
void __identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?getUpdatePhase@UpdateModule@@MBE?AW4SleepyUpdatePhase@@XZ")();
}
extern "C" const void *const vtbl_00BF186C[13] = {
	(const void *)&__identifier("??_GRva00253EF5@@UAEPAXI@Z"), // slot 0 0x00253ED9
	(const void *)&__identifier("?loadPostProcess@Rva00497805@@MAEXXZ"), // slot 1 0x00497805
	(const void *)&__identifier("?name@Rva00253ED3Named@@QBEPBDXZ"), // slot 2 0x00253ED3
	(const void *)&__identifier("?xfer@NotifyTargetsOfImminentProbableCrushingUpdate@@MAEXPAVXfer@@@Z"), // slot 3 0x004CEE39
	(const void *)&__identifier("?getModuleNameKey@NotifyTargetsOfImminentProbableCrushingUpdate@@UBE?AW4NameKeyType@@XZ"), // slot 4 0x00253E8E
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

class NotifyTargetsOfImminentProbableCrushingUpdate : public UpdateModule
{
public:
	NotifyTargetsOfImminentProbableCrushingUpdate(Thing *thing, const ModuleData *moduleData);
};

// ??0NotifyTargetsOfImminentProbableCrushingUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x00253E64
NotifyTargetsOfImminentProbableCrushingUpdate::NotifyTargetsOfImminentProbableCrushingUpdate(Thing *thing, const ModuleData *moduleData) :
	UpdateModule(thing, moduleData)
{
	*(unsigned int *)this = ((unsigned int)vtbl_00BF186C);
	*(unsigned int *)((char *)this + 0xC) = ((unsigned int)__identifier("??_7AttributeModifierPoolUpdate@@6BBehaviorModuleInterface@@@"));
	*(unsigned int *)((char *)this + 0x10) = ((unsigned int)__identifier("??_7Rva00253EF5@@6BRva00253EF5_B2@@@"));
}

// Native list merge4CEB14 calls this comparator; sort4CEB76 calls that
// merge, and wrapper4CED15 calls the sort. The wrapper's caller4CEDB8 is
// adjacent to the module update4CEE1A, which suggests this subsystem home.
// Native origin0/4 and input positions38/3C prove squared-distance ordering;
// the original comparator class name and module association remain uncertain.
struct Rva004CEAB7Position { char pad[0x38]; float x,y; };
class Rva004CEAB7 {
public:
 bool rva004CEAB7(void *,void *);
 float x,y,z;
};
bool Rva004CEAB7::rva004CEAB7(void *a,void *b)
{
 const Rva004CEAB7Position *left=(const Rva004CEAB7Position *)a;
 const Rva004CEAB7Position *right=(const Rva004CEAB7Position *)b;
 float centerX=x;
 float centerY=y;
 float otherX=centerX;
 float otherY=centerY;
 centerY-=left->y;
 centerX-=left->x;
 otherX-=right->x;
 otherY-=right->y;
 float len1=centerY*centerY+centerX*centerX;
 float len2=otherY*otherY+otherX*otherX;
 if (len1<len2) return true;
 return false;
}
