// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
//
// ??0HordeNotifyTargetsOfImminentProbableCrushingUpdate@@QAE@PAVThing@@PBVModuleData@@@Z,
// retail 0x00253D88, 40 bytes. Behavior-side ctor completing the
// HordeNotifyTargetsOfImminentProbableCrushingUpdate file-unit (poolkey
// rowed at 0x253DB2, behavior instance factory rowed at 0x2551CF news 0x34
// with this ctor as sole raw caller; the non-Horde twin keeps its own
// poolkey 0x253E8E, factory 0x255207 and rowed ctor 0x253E64).
//
// Shape: frameless single-base ctor over the rowed UpdateModule base
// 0x253390 with three explicit vtable stores at +0/+0xC/+0x10 via byte-wise
// pointer casts (StopSpecialPower precedent: explicit stores, no virtuals
// declared anywhere so no vtable is emitted here; all three immediates are
// DIR32-masked in comparison). Zero new pins (base resolves via the
// rowed UpdateModule spelling).

extern "C" const void *const __identifier("??_7AttributeModifierPoolUpdate@@6BBehaviorModuleInterface@@@")[];  // folded vftable 0x00BEFF90 (80 classes), by the name its definer AttributeModifierPoolUpdate.cpp emits on the canonical BehaviorModule chain (the data-ledger spelling ...@@6BBehaviorModuleOther@@@ has no definer)

extern "C" const void *const __identifier("??_7Rva00253E19@@6BRva00253E19_B2@@@")[];  // vftable 0x00BF17EC
// The retail table at RVA 0x007F17F8: 13 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva00253E19@@UAEPAXI@Z")();
void __identifier("?loadPostProcess@Rva00497805@@MAEXXZ")();
void __identifier("?name@Rva00253DF7Named@@QBEPBDXZ")();
void __identifier("?xfer@NotifyTargetsOfImminentProbableCrushingUpdate@@MAEXPAVXfer@@@Z")();
void __identifier("?getModuleNameKey@HordeNotifyTargetsOfImminentProbableCrushingUpdate@@UBE?AW4NameKeyType@@XZ")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
void __identifier("?Add_Dependencies_To_List@RenderObjClass@@MAEXAAV?$DynamicVectorClass@VStringClass@@@@_N@Z")();
void __identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?getUpdatePhase@UpdateModule@@MBE?AW4SleepyUpdatePhase@@XZ")();
}
extern "C" const void *const vtbl_00BF17F8[13] = {
	(const void *)&__identifier("??_GRva00253E19@@UAEPAXI@Z"), // slot 0 0x00253DFD
	(const void *)&__identifier("?loadPostProcess@Rva00497805@@MAEXXZ"), // slot 1 0x00497805
	(const void *)&__identifier("?name@Rva00253DF7Named@@QBEPBDXZ"), // slot 2 0x00253DF7
	(const void *)&__identifier("?xfer@NotifyTargetsOfImminentProbableCrushingUpdate@@MAEXPAVXfer@@@Z"), // slot 3 0x004CEE39
	(const void *)&__identifier("?getModuleNameKey@HordeNotifyTargetsOfImminentProbableCrushingUpdate@@UBE?AW4NameKeyType@@XZ"), // slot 4 0x00253DB2
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

class HordeNotifyTargetsOfImminentProbableCrushingUpdate : public UpdateModule
{
public:
	HordeNotifyTargetsOfImminentProbableCrushingUpdate(Thing *thing, const ModuleData *moduleData);
};

// ??0HordeNotifyTargetsOfImminentProbableCrushingUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x00253D88
HordeNotifyTargetsOfImminentProbableCrushingUpdate::HordeNotifyTargetsOfImminentProbableCrushingUpdate(Thing *thing, const ModuleData *moduleData) :
	UpdateModule(thing, moduleData)
{
	*(unsigned int *)this = ((unsigned int)vtbl_00BF17F8);
	*(unsigned int *)((char *)this + 0xC) = ((unsigned int)__identifier("??_7AttributeModifierPoolUpdate@@6BBehaviorModuleInterface@@@"));
	*(unsigned int *)((char *)this + 0x10) = ((unsigned int)__identifier("??_7Rva00253E19@@6BRva00253E19_B2@@@"));
}

// Native4CEB14..4CEB76. STLport4.5.3 _S_merge algorithm, from BFME1
// ba7dd inputs/vendor/stlport/stl/_list.c, using the verified distance helper.
// Nodes carry pointer-sized payloads at8; original list/owner names unknown.
// This helper's comparator home is the neighboring non-Horde constructor TU.
// Keep its declaration out of line: seeing the body changes register allocation.
class Rva004CEAB7 {
public: bool rva004CEAB7(void *,void *);
float x,y,z;
};
namespace _STL {
struct _List_node_base { _List_node_base *next,*prev; };
template <class Dummy> struct _List_global {
 static void _Transfer(_List_node_base *,_List_node_base *,_List_node_base *);
};
}
struct Rva004CEB14Node : _STL::_List_node_base { void *value; };
struct Rva004CEB14List { Rva004CEB14Node *head; };
void Rva004CEB14(Rva004CEB14List &dst, Rva004CEB14List &src, Rva004CEAB7 comp)
{
 Rva004CEB14Node *first1=(Rva004CEB14Node *)dst.head->next;
 Rva004CEB14Node *last1=dst.head;
 Rva004CEB14Node *first2=(Rva004CEB14Node *)src.head->next;
 Rva004CEB14Node *last2=src.head;
 while (first1!=last1 && first2!=last2) {
  if (comp.rva004CEAB7(first2->value, first1->value)) {
   Rva004CEB14Node *next=(Rva004CEB14Node *)first2->next;
   _STL::_List_global<bool>::_Transfer(first1,first2,next);
   first2=next;
  } else first1=(Rva004CEB14Node *)first1->next;
 }
 if (first2!=last2)
  _STL::_List_global<bool>::_Transfer(last1,first2,last2);
}
