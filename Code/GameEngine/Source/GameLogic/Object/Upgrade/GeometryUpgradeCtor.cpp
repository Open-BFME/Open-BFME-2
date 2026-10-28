// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
//
// ??0GeometryUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004B6A5E,
// 91 bytes. Behavior-side module ctor: UpgradeModule base plus the four
// most-derived vtable slots and the upgrade-name string cleared in the body.
// Identity is the rowed GeometryUpgrade::friend_newModuleInstance at
// 0x0025060A (news 0x20, calls this ctor with Thing* and ModuleData*) plus
// the BFME1 GeometryUpgradeConstructor donor (same base call, same four
// vtable slots at +0/+0xC/+0x10/+0x18, same AsciiString at +0x1C cleared
// through the folded 0x36410).
//
// Shape follows the donor and the SubObjectsUpgrade file-unit (same four
// slots; +0xC/+0x18 reuse 0xC57328/0xC58790 family-wide): the slots live
// inside the 0x1C UpgradeModule footprint, so the most-derived ctor
// re-emits all four before the member init (sibling
// GeometryUpgradeModuleDataCtor precedent: compiler vtable store precedes
// member nulls). No explicit stores and no statics; all four immediates
// are DIR32-masked in comparison.

#include "GeometryUpgradeView.h"

// ??0GeometryUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z @0x004B6A5E
GeometryUpgrade::GeometryUpgrade(Thing *thing, const ModuleData *moduleData) :
	UpgradeModule(thing, moduleData)
{
	m_upgradeName.clear();
}
