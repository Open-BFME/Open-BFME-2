// cl: /DNDEBUG /MD /Oi
//
// ??0DynamicPortalBehaviour@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00460B6C,
// 95 bytes. Behavior-side ctor completing the DynamicPortalBehaviour
// file-unit (behavior factory rowed at 0x24B47B news 0x40 with this pinned
// 2-arg ctor; poolkey rowed at 0x460BD3).
//
// Shape: frameless single-base ctor over the pinned UpgradeModule base
// 0x460AEC with explicit vtable stores at +0/+0x0C/+0x10/+0x18 via byte-wise
// pointer casts (Defector precedent: explicit stores, no virtuals declared
// anywhere so no vtable is emitted here; the final stores name the class's
// own tables by their retail immediates, the two transient first values stay
// TU-local dummies; all immediates are DIR32-masked in comparison)
// plus a volatile-first double-store pair at +0x1C/+0x20
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

extern "C" const void *const __identifier("??_7DynamicPortalBehaviour@@6BObjectModule@@@")[];  // vftable 0x00C428C4
extern "C" const void *const __identifier("??_7DynamicPortalBehaviour@@6BBehaviorModuleInterface@@@")[];  // vftable 0x00C42808
extern "C" const void *const __identifier("??_7DynamicPortalBehaviour@@6BUpgradeMux@@@")[];  // vftable 0x00C427C0
extern "C" const void *const __identifier("??_7DynamicPortalBehaviour@@6BModuleInterface@@@")[];  // vftable 0x00C58790
static int s_first1C;
static int s_first20;
extern "C" const void *const __identifier("??_7DynamicPortalBehaviour@@6BDynamicPortalExtraA@@@")[];  // vftable 0x00C427B8
extern "C" const void *const __identifier("??_7DynamicPortalBehaviour@@6BDynamicPortalExtraB@@@")[];  // vftable 0x00C427A8

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
	*(unsigned int *)this = (unsigned int)__identifier("??_7DynamicPortalBehaviour@@6BObjectModule@@@");
	*(unsigned int *)((char *)this + 0xC) = (unsigned int)__identifier("??_7DynamicPortalBehaviour@@6BBehaviorModuleInterface@@@");
	*(unsigned int *)((char *)this + 0x10) = (unsigned int)__identifier("??_7DynamicPortalBehaviour@@6BUpgradeMux@@@");
	*(unsigned int *)((char *)this + 0x18) = (unsigned int)__identifier("??_7DynamicPortalBehaviour@@6BModuleInterface@@@");
	*(unsigned int *)((char *)this + 0x1C) = (unsigned int)__identifier("??_7DynamicPortalBehaviour@@6BDynamicPortalExtraA@@@");
	*(unsigned int *)((char *)this + 0x20) = (unsigned int)__identifier("??_7DynamicPortalBehaviour@@6BDynamicPortalExtraB@@@");
	m_3C = 0;
	m_3D = 0;
	for (int i = 0; i < 6; ++i)
		m_24[i] = 0;
}
