// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /Ireference/shims/bfmealloc
//
// ??0BuildableHeroListUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004B8332, 49 bytes.
// BuildableHeroListUpgrade behavior ctor over the canonical UpgradeModule base
// (0x460AEC, thing plus data): the compiler re-stores the four most-derived
// vtable slots at +0/+0x0C/+0x10/+0x18 (GeometryUpgrade ctor precedent; the
// immediates are DIR32-masked). The rowed name getter at 0x4B82CB proves the
// class; the rowed instance factory 0x25087E is the sole raw caller.

class Thing;
class ModuleData;

#include "../../../../Include/GameLogic/Module/UpgradeModule.h"

class BuildableHeroListUpgrade : public UpgradeModule
{
public:
	BuildableHeroListUpgrade(Thing *thing, const ModuleData *moduleData);
protected:
	virtual void upgradeRemovalImplementation();
	virtual void upgradeImplementation();
};

// ??0BuildableHeroListUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z @0x004B8332
BuildableHeroListUpgrade::BuildableHeroListUpgrade(Thing *thing, const ModuleData *moduleData)
	: UpgradeModule(thing, moduleData)
{
}
