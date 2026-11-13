// cl: /DNDEBUG /MD
// Split from PorcupineFormationBodyModuleSlots.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
//
// PorcupineFormationBodyModule's +0x10 body-interface overrides (table
// 0x00C5C318) and the formation test they share, all names but
// attemptDamage by address.
// rva004C2095, retail 0x004C2095 (37 bytes), on the primary this: asks the
// container module (+0x250) of the Object our Object is contained by (+0x274)
// its slot 31 when all three exist, and answers false either way.
// attemptDamage, retail 0x004C2230 (45 bytes), slot 0: with the formation
// test holding, the class's 0x004C21A9 (pinned by address) sees the damage
// first; ActiveBody::attemptDamage 0x004BFE07 always follows.
// rva004C2127, retail 0x004C2127 (130 bytes), slot 38: true while the
// formation test fails, without our Object or module data, without the data's
// +0x6C level, or when that level is below the other Object's (Object
// 0x00294815, pinned by address); otherwise false, after the data's +0x68
// weapon (when set) is fired from our Object at the other through
// TheWeaponStore (the rowed rva002CE964) if the two positions are within the
// weapon's range (its +0x14 float; the getter folds with the rowed
// TerrainRoadType::getRoadWidth, used here only as a call view) by the rowed
// 0x004C20D5 distance test (reached as a member; pinned for this class).
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
// Call view for the existing folded fld [ecx+0x14]; ret provider at 0x0049CB57.
#include "../../../../Include/GameClient/TerrainRoadType.h"

class WeaponTemplate;
class Object;
#include "../../../../Include/GameLogic/WeaponStore.h"
extern WeaponStore *TheWeaponStore;
template <int N> class Rva004C2095Slots : public Rva004C2095Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva004C2095Slots<0>
{
};
class Rva004C2095Contain : public Rva004C2095Slots<31>
{
public:
	virtual void *rvaSlot31() = 0;
};
#include "../object.h"
class DamageInfo;
struct PorcupineFormationBodyModuleData
{
	unsigned char m_pad00[0x68];
	const WeaponTemplate *m_weapon;	// +0x68
	char m_level;			// +0x6C
};
class ModuleData;
#include "../../../../Include/GameLogic/Module/ModuleBase.h"
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"
#include "../../../../Include/GameLogic/Module/BodyModule.h"
#include "../../../../Include/GameLogic/Module/ActiveBody.h"
class PorcupineFormationBodyModule : public ActiveBody
{
public:
	PorcupineFormationBodyModule( Thing *thing, const ModuleData *moduleData );
	virtual ~PorcupineFormationBodyModule();
	virtual void attemptDamage(DamageInfo *damageInfo);
	virtual bool rva004C2127(Object *other);
	bool rva004C2095();
	void rva004C21A9(DamageInfo *damageInfo);
	bool Rva004C20D5IsWithin(float range, const Coord3D *a, const Coord3D *b);

protected:
	virtual void xfer( Xfer *xfer );
};


void PorcupineFormationBodyModule::attemptDamage(DamageInfo *damageInfo)
{
	if (rva004C2095())
	{
		rva004C21A9(damageInfo);
		ActiveBody::attemptDamage(damageInfo);
	}
	else
		ActiveBody::attemptDamage(damageInfo);
}

