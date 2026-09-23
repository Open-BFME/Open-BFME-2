// cl: /O1 /DNDEBUG /MD /Oi
//
// ??0DynamicPortalBehaviour@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00460B6C,
// 95 bytes. Behavior-side ctor completing the DynamicPortalBehaviour
// file-unit (behavior factory rowed at 0x24B47B news 0x40 with this pinned
// 2-arg ctor; poolkey rowed at 0x460BD3).
//
// Shape: frameless single-base ctor over the pinned UpgradeModule base
// 0x460AEC with explicit vtable stores at +0/+0x0C/+0x10/+0x18 via byte-wise
// pointer casts (Defector precedent: explicit stores, no virtuals declared
// anywhere so no vtable is emitted here; all immediates are DIR32-masked in
// comparison) plus a volatile-first double-store pair at +0x1C/+0x20
// (RunOffMap precedent: a redundant same-slot pair survives iff the first is
// volatile) plus two byte zeros at +0x3C/+0x3D plus a zero loop at +0x24
// (for-loop over 6 ints optimizes to plain rep stosd x6 with lea-before-xor
// setup matching retail; memset with /Oi gives xor-before-lea and misses by
// 2 bytes). Flat classes throughout keep the body frameless.
// Factory news 0x40 fits the +0x3C tail. Zero new pins (base resolves via the
// existing UpgradeModule pin).

class Thing;
class ModuleData;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

static int s_vtable;
static int s_secondary0C;
static int s_secondary10;
static int s_secondary18;
static int s_first1C;
static int s_first20;
static int s_second1C;
static int s_second20;

class UpgradeModule
{
public:
	UpgradeModule(Thing *thing, const ModuleData *moduleData);

private:
	unsigned char m_pad[0x1C];
};

class DynamicPortalBehaviour : public UpgradeModule
{
public:
	DynamicPortalBehaviour(Thing *thing, const ModuleData *moduleData);

private:
	int m_1C;
	int m_20;
	int m_24[6];
	unsigned char m_3C;
	unsigned char m_3D;
	unsigned char m_pad3E[2];
};

// ??0DynamicPortalBehaviour@@QAE@PAVThing@@PBVModuleData@@@Z @0x00460B6C
DynamicPortalBehaviour::DynamicPortalBehaviour(Thing *thing, const ModuleData *moduleData) :
	UpgradeModule(thing, moduleData)
{
	*(volatile unsigned int *)((char *)this + 0x1C) = (unsigned int)&s_first1C;
	*(volatile unsigned int *)((char *)this + 0x20) = (unsigned int)&s_first20;
	_ReadWriteBarrier();
	*(unsigned int *)this = (unsigned int)&s_vtable;
	*(unsigned int *)((char *)this + 0xC) = (unsigned int)&s_secondary0C;
	*(unsigned int *)((char *)this + 0x10) = (unsigned int)&s_secondary10;
	*(unsigned int *)((char *)this + 0x18) = (unsigned int)&s_secondary18;
	*(unsigned int *)((char *)this + 0x1C) = (unsigned int)&s_second1C;
	*(unsigned int *)((char *)this + 0x20) = (unsigned int)&s_second20;
	m_3C = 0;
	m_3D = 0;
	for (int i = 0; i < 6; ++i)
		m_24[i] = 0;
}
