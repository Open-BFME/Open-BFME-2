// cl: /O1 /DNDEBUG /MD
//
// ??0RunOffMapBehavior@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0046217B,
// 49 bytes. Behavior-side ctor completing the RunOffMapBehavior file-unit
// (ModuleData proc/factory/ctor rowed at 0x46216A/0x254F24/0x254ECE;
// behavior factory rowed at 0x24B6B1 news 0x34 with this pinned 2-arg ctor;
// poolkey rowed at 0x4621B2).
//
// Shape: frameless single-base ctor over the rowed BehaviorModule base
// 0x253330 (CreateModule donor spelling, human-readable row) with four
// explicit vtable stores at +0x10/+0/+0xC/+0x10 via byte-wise pointer casts
// (Defector precedent: explicit stores, no virtuals declared anywhere so no
// vtable is emitted here; all four immediates are DIR32-masked in
// comparison). The first +0x10 store is volatile (Assault
// volatile-first-store precedent: a redundant same-slot pair survives iff
// the first is volatile; pointer-local DSEs away under pressure,
// source-order does not hold). Flat classes throughout keep the body
// frameless. Factory news fits. Zero new pins (base resolves via the
// existing BehaviorModule row).

class Thing;
class ModuleData;

class BehaviorModule
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
private:
	unsigned char m_pad[0x10];
};

class RunOffMapBehavior : public BehaviorModule
{
public:
	RunOffMapBehavior(Thing *thing, const ModuleData *moduleData);
};

// ??0RunOffMapBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x0046217B
RunOffMapBehavior::RunOffMapBehavior(Thing *thing, const ModuleData *moduleData) :
	BehaviorModule(thing, moduleData)
{
	*(volatile unsigned int *)((char *)this + 0x10) = 0x00C1C780;
	*(unsigned int *)this = 0x00C4307C;
	*(unsigned int *)((char *)this + 0xC) = 0x00C42FC0;
	*(unsigned int *)((char *)this + 0x10) = 0x00C42F1C;
}
