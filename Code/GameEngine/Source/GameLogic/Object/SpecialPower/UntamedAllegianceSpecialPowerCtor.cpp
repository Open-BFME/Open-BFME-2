// cl: /DNDEBUG /MD
//
// ??0UntamedAllegianceSpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004C7B06, 42 bytes.
// UntamedAllegianceSpecialPower behavior ctor: calls ??0SpecialPowerModule
// 0x00493C5A (thing plus data), then stores the class's three vptrs:
// 0x00C5E0E4 at +0, SpecialPowerModule's shared BehaviorModuleInterface
// table 0x00BEFCF8 at +0x0C and 0x00C5E080 at +0x10, the three the class's
// destructor 0x004C7B36 stores before it tail-calls ??1SpecialPowerModule.
// The rowed name getter at 0x4C7B4F proves the class; the rowed instance
// factory 0x25247A is the sole raw caller. The view is the class's
// UntamedAllegianceSpecialPower.cpp view, so the stores name its tables.

class Thing;
class ModuleData;
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"
#include "../../../../Include/GameLogic/Module/SpecialPowerModule.h"
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h
class SpecialPowerModule : public BehaviorModule, public SpecialPowerModuleInterface
{
public:
	SpecialPowerModule( Thing *thing, const ModuleData *moduleData );
	// Public: the rowed dtor at 0x00493DEF is ??1SpecialPowerModule@@UAE@XZ.
	virtual ~SpecialPowerModule();
};
enum NameKeyType
{
	NK_UNKNOWN = 0
};
class UntamedAllegianceSpecialPower : public SpecialPowerModule
{
public:
	UntamedAllegianceSpecialPower( Thing *thing, const ModuleData *moduleData );
protected:
	virtual ~UntamedAllegianceSpecialPower();
public:
	virtual NameKeyType getModuleNameKey() const;
};

UntamedAllegianceSpecialPower::UntamedAllegianceSpecialPower( Thing *thing, const ModuleData *moduleData )
	: SpecialPowerModule( thing, moduleData )
{
}
