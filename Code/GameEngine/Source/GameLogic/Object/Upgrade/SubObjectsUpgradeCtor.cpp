// cl: /DNDEBUG /MD
//
// ??0SubObjectsUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004B4D63,
// 64 bytes. Behavior-side ctor completing the SubObjectsUpgrade file-unit
// (ModuleData proc/factory/ctor rowed at 0x4B52EB/0x25780C/0x257768;
// behavior factory rowed at 0x2500E6 news 0x38 with this pinned 2-arg ctor;
// poolkey rowed at 0x4B4D1E).
//
// Shape: frameless single-base ctor over the pinned UpgradeModule base
// 0x460AEC (RadarUpgrade donor spelling, human-readable pin) with four
// explicit vtable stores at +0/+0xC/+0x10/+0x18 via byte-wise pointer casts
// (Defector precedent: explicit stores, no virtuals declared anywhere so no
// vtable is emitted here; all four immediates are DIR32-masked in
// comparison), then TheGameLogic +0x40 pointer at +0x1C via extern global
// (A1 moffs, clamp-table precedent, no pin) and zero byte at +0x20. Flat
// classes throughout keep the body frameless. Factory news 0x38 fits the
// +0x20 tail. Zero new pins (base resolves via the existing UpgradeModule
// pin; global is DIR32-masked).

extern "C" const void *const vtbl_00C57328[];  // folded, 41 classes; via ??_7AllowBannerSpawnUpgrade@@6BBehaviorModuleInterface@@@
#pragma comment(linker, "/alternatename:_vtbl_00C57328=??_7AllowBannerSpawnUpgrade@@6BBehaviorModuleInterface@@@")
extern "C" const void *const vtbl_00C58790[];  // folded, 55 classes; via ??_7AODHordeContain@@6BIface2C@@@
#pragma comment(linker, "/alternatename:_vtbl_00C58790=??_7AODHordeContain@@6BIface2C@@@")

extern "C" const void *const vtbl_00C57BF8[];  // ??_7Rva004B4CDF@@6BUpgradeMux@@@
#pragma comment(linker, "/alternatename:_vtbl_00C57BF8=??_7Rva004B4CDF@@6BUpgradeMux@@@")
extern "C" const void *const vtbl_00C57C40[];  // ??_7Rva004B4CDF@@6BObjectModule@@@
#pragma comment(linker, "/alternatename:_vtbl_00C57C40=??_7Rva004B4CDF@@6BObjectModule@@@")

class Thing;
class ModuleData;

struct GameLogic
{
	void *m_pad[16];
	void *m_40;
};

extern GameLogic *TheGameLogic;

class UpgradeModule
{
public:
	UpgradeModule(Thing *thing, const ModuleData *moduleData);
private:
	unsigned char m_pad[0x1C];
};

class SubObjectsUpgrade : public UpgradeModule
{
public:
	SubObjectsUpgrade(Thing *thing, const ModuleData *moduleData);
private:
	void *m_1C;
	unsigned char m_20;
};

// ??0SubObjectsUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z @0x004B4D63
SubObjectsUpgrade::SubObjectsUpgrade(Thing *thing, const ModuleData *moduleData) :
	UpgradeModule(thing, moduleData)
{
	*(unsigned int *)this = ((unsigned int)vtbl_00C57C40);
	*(unsigned int *)((char *)this + 0xC) = ((unsigned int)vtbl_00C57328);
	*(unsigned int *)((char *)this + 0x10) = ((unsigned int)vtbl_00C57BF8);
	*(unsigned int *)((char *)this + 0x18) = ((unsigned int)vtbl_00C58790);
	m_1C = TheGameLogic->m_40;
	m_20 = 0;
}
// ?TheGameLogic@@3PAUGameLogic@@A: the global at VA 0xdfe78c is ?TheGameLogic@@3PAVGameLogic@@A.
#pragma comment(linker, "/alternatename:?TheGameLogic@@3PAUGameLogic@@A=?TheGameLogic@@3PAVGameLogic@@A")
