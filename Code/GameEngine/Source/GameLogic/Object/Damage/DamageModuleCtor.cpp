// cl: /O1 /DNDEBUG /MD
//
// ??0DamageModule@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004B9704,
// 47 bytes. Base ctor for damage behaviors over the rowed BehaviorModule
// base 0x253330 with three explicit stores at +0x10/+0/+0x0C via byte-wise
// pointer casts (Defector precedent: explicit stores, no virtuals declared
// anywhere so no vtable is emitted here; all three immediates are
// DIR32-masked in comparison). The first +0x10 store is volatile (RunOffMap
// volatile-first-store precedent: a redundant same-slot pair survives iff
// the first is volatile; the second +0x10 re-stores the same value).
// Flat classes throughout keep the body frameless. Six raw callers all
// lea-ecx plus vtable plus call (first-member pattern); the BFME1
// EvacuateDamage donor calls this base. Row supersedes the ctor pin.

class Thing;
class ModuleData;

static int s_vtable;
static int s_secondary0C;
static int s_first10;
static int s_second10;

class BehaviorModule
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);

private:
	unsigned char m_pad[0x14];
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
	*(volatile unsigned int *)((char *)this + 0x10) = (unsigned int)&s_first10;
	*(unsigned int *)this = (unsigned int)&s_vtable;
	*(unsigned int *)((char *)this + 0xC) = (unsigned int)&s_secondary0C;
	*(unsigned int *)((char *)this + 0x10) = (unsigned int)&s_second10;
}
