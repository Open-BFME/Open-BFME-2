// cl: /DNDEBUG /MD
//
// ??0PlayerHealSpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x004C7E7E, 42 bytes. PlayerHealSpecialPower behavior ctor: calls
// ??0SpecialPowerModule 0x00493C5A (thing plus data), then stores the class's
// three vptrs: 0x00C5E36C at +0 (the behavior vtable, distinct from the
// ModuleData vtable 0x00C5E7A8), SpecialPowerModule's shared
// BehaviorModuleInterface table 0x00BEFCF8 at +0x0C and 0x00C5E308 at +0x10,
// the three the class's destructor 0x004C7EAE stores before it tail-calls
// ??1SpecialPowerModule. The PlayerHeal file-unit (pool key at 0x004C7EFB,
// ModuleData proc 0x004C7E63 ending exactly where this ctor begins,
// ModuleData factory 0x002525C7) proves the class; the instance factory at
// 0x0025258F is the sole raw caller. The view declares the virtuals
// PlayerHealSpecialPower.cpp declares, so the stores name its tables.

class Thing;
class ModuleData;
class Object;
struct Coord3D;
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"
#include "../../../../Include/GameLogic/Module/SpecialPowerModule.h"
class SpecialPowerModule : public BehaviorModule, public SpecialPowerModuleInterface
{
public:
	SpecialPowerModule( Thing *thing, const ModuleData *moduleData );
	// Public: the rowed dtor at 0x00493DEF is ??1SpecialPowerModule@@UAE@XZ.
	virtual ~SpecialPowerModule();
	virtual void doSpecialPower(unsigned int options);					// 0x0049490F
	virtual void doSpecialPowerAtObject(Object *obj, unsigned int options);		// 0x0049495B
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options);	// 0x004949D8
};
enum NameKeyType
{
	NK_UNKNOWN = 0
};
class PlayerHealSpecialPower : public SpecialPowerModule
{
public:
	PlayerHealSpecialPower( Thing *thing, const ModuleData *moduleData );
protected:
	virtual ~PlayerHealSpecialPower();
public:
	virtual NameKeyType getModuleNameKey() const;
	virtual void doSpecialPower(unsigned int options);
	virtual void doSpecialPowerAtObject(Object *obj, unsigned int options);
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options);
};

PlayerHealSpecialPower::PlayerHealSpecialPower( Thing *thing, const ModuleData *moduleData )
	: SpecialPowerModule( thing, moduleData )
{
}
