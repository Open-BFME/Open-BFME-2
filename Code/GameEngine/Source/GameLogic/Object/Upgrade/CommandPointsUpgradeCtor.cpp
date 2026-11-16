// cl: /DNDEBUG /MD
//
// ??0CommandPointsUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004B8661, 49 bytes.
// CommandPointsUpgrade behavior ctor over the canonical UpgradeModule base
// (0x460AEC, thing plus data); the compiler stores the class's four tables
// (0x00C590A8 at +0, 0x00C57328 at +0x0C, 0x00C59060 at +0x10 and 0x00C58790 at
// +0x18). The rowed name getter at 0x4B85FA and ModuleData triple
// (proc 0x4B863F plus ctor 0x254891 plus factory 0x2548D2) prove the class;
// the rowed instance factory 0x2508EE is the sole raw caller. The class
// declaration is the one its destructor's unit (FireWeaponWhenDeadBehaviorDerived.cpp)
// uses, so both units emit the same vftable copies.

#include "../../../../Include/GameLogic/Module/UpgradeModule.h"

enum NameKeyType;
class CommandPointsUpgrade : public UpgradeModule
{
public:
	CommandPointsUpgrade(Thing *thing, const ModuleData *moduleData);
	virtual ~CommandPointsUpgrade();
protected:
	virtual void upgradeRemovalImplementation();						// UpgradeMux slot 8 (0x004B86DA)
	virtual void upgradeImplementation();							// UpgradeMux slot 10 (0x004B86AE)
public:
	virtual enum NameKeyType getModuleNameKey() const;
};

// ??0CommandPointsUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z @0x4B8661
CommandPointsUpgrade::CommandPointsUpgrade(Thing *thing, const ModuleData *moduleData)
	: UpgradeModule(thing, moduleData)
{
}
