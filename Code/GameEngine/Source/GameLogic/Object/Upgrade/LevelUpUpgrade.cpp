// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"


// The registered UpgradeModule view (canonical_classes.csv); it brings BehaviorModule.h and
// UpgradeMux.h and supplies the getDamage/getUpgrade overrides of the BehaviorModuleInterface table.
#include "../../../../Include/GameLogic/Module/UpgradeModule.h"
// BfmeXfer.h leaves its value types for the unit to declare with its own class-keys.
class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../../Include/Common/BfmeXfer.h"

// The class is LevelUpUpgrade.h's, shared with its destructor's unit (FireWeaponWhenDeadBehaviorDerived.cpp).
#include "../../../../Include/GameLogic/Module/LevelUpUpgrade.h"

LevelUpUpgrade::LevelUpUpgrade( Thing *thing, const ModuleData *moduleData )
	: UpgradeModule( thing, moduleData )
{
}

// Primary slot 1 of 0x00C57460, retail 0x00497805 (`jmp 0x0058B03E`): the UpgradeModule base
// call that every module-family override without work of its own shares (ICF).
void LevelUpUpgrade::loadPostProcess()
{
	UpgradeModule::loadPostProcess();
}

// Primary slot 3 of 0x00C57460, retail 0x004B8710: Version1, then the UpgradeModule base call,
// the body retail folds with ArmorUpgrade::xfer and the other simple Upgrades.
void LevelUpUpgrade::xfer( Xfer *xfer )
{
	xfer->Version1();
	UpgradeModule::xfer(xfer);
}

// UpgradeMux slot 8 of 0x00C57418, retail 0x000B3FD0 (a bare `ret`): LevelUpUpgrade has nothing
// to undo when the upgrade is removed; UpgradeMux leaves the slot pure, and retail folds the empty
// body with every other empty void method (ICF).
void LevelUpUpgrade::upgradeRemovalImplementation()
{
}
