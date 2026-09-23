// ??0DamageModule@@QAE@PAVThing@@PBVModuleData@@@Z
// partial score=0.85 date=2026-09-23
// cl: /O1 /DNDEBUG /MD
//
// ??0DamageModule@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004B9704,
// 49 bytes. DamageModule intermediate base ctor (frameless leaf: base call
// plus vtable plus member stores). Called this-only with (Thing,ModuleData)
// by 6 derived Damage-family behavior ctors (0x4B97A7/0x4BA3F7/0x4BABBF/
// 0x4BAE35/0x4BB13B/0x4BB447, all push/push/mov/push/call arity); the
// EvacuateDamage call site matches its BFME1 donor.
//
// Shape: frameless single-base ctor over the rowed BehaviorModule base
// 0x253330 with four explicit body stores in retail order (+0x10, +0,
// +0xC, +0x10) via byte-wise pointer casts (no virtuals declared anywhere
// so no vtable is emitted here; all four immediates are DIR32-masked in
// comparison). The redundant first +0x10 store survives only as volatile
// (volatile-first-store law). Zero new pins (base resolves via the rowed
// BehaviorModule spelling).

class Thing;
class ModuleData;

class BehaviorModule
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};

class DamageModule : public BehaviorModule
{
public:
	DamageModule(Thing *thing, const ModuleData *moduleData);
};

// ??0DamageModule@@QAE@PAVThing@@PBVModuleData@@@Z @0x004B9704
DamageModule::DamageModule(Thing *thing, const ModuleData *moduleData) :
	BehaviorModule(thing, moduleData)
{
	*(unsigned int volatile *)((char *)this + 0x10) = 0x00BE2B78;
	*(unsigned int *)this = 0x00C598E4;
	*(unsigned int *)((char *)this + 0xC) = 0x00C597F8;
	*(unsigned int volatile *)((char *)this + 0x10) = 0x00BE2B78;
}
