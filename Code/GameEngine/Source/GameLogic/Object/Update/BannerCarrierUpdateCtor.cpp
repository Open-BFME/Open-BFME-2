// cl: /O1 /DNDEBUG /MD
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

class Thing;
class ModuleData;

class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
};

class BannerCarrierUpdate : public UpdateModule
{
public:
	BannerCarrierUpdate(Thing *thing, const ModuleData *moduleData);
};

// ??0BannerCarrierUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x00496A98
BannerCarrierUpdate::BannerCarrierUpdate(Thing *thing, const ModuleData *moduleData) :
	UpdateModule(thing, moduleData)
{
	*(unsigned int *)this = 0x00C4F838;
	*(unsigned int *)((char *)this + 0xC) = 0x00BEFF90;
	*(unsigned int *)((char *)this + 0x10) = 0x00C4F82C;
}
