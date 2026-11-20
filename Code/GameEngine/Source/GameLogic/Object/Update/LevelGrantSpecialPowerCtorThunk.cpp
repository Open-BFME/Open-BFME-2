// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: LevelGrantSpecialPower module ctor.
// Base MI: vptrs at +0/+0xC/+0x10/+0x20.
// Target facts: the constructor 0x004C2B0E calls the SpecialAbilityUpdate base
// constructor 0x0044EF5E (rowed under the address spelling Rva0044EF5E) and
// stores 0x00C5C920 at +0x00, the 47-slot BehaviorModuleInterface table
// 0x00C4D640 at +0x0C, 0x00C4DEE8 at +0x10 and 0x00C552A4 at +0x20: the four
// vptrs of the canonical SpecialAbilityUpdate (UpdateModule's three plus
// SpecialPowerUpdateInterface). No override of LevelGrantSpecialPower's own is
// declared here.

class Thing;
class ModuleData;

#include "../../../../Include/GameLogic/Module/SpecialAbilityUpdate.h"

class Rva0044EF5E : public SpecialAbilityUpdate
{
public:
	Rva0044EF5E( Thing *thing, const ModuleData *moduleData );
	virtual ~Rva0044EF5E();
};

class LevelGrantSpecialPower : public Rva0044EF5E
{
public:
	LevelGrantSpecialPower( Thing *thing, const ModuleData *moduleData );
	virtual ~LevelGrantSpecialPower();
};

LevelGrantSpecialPower::LevelGrantSpecialPower( Thing *thing, const ModuleData *moduleData )
	: Rva0044EF5E( thing, moduleData )
{
}
