// cl: /DNDEBUG /MD
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
// Slot 38 reaches the rowed free-function distance test with its primary this
// in ecx, which the body ignores: bind this unit's member spelling to that
// body (cf. the symbols.csv pin documenting the thiscall evidence).
#pragma comment(linker, "/alternatename:?Rva004C20D5IsWithin@PorcupineFormationBodyModule@@QAE_NMPBUCoord3D@@0@Z=?Rva004C20D5IsWithin@@YG_NMPBUCoord3D@@0@Z")
// Call view for the existing folded fld [ecx+0x14]; ret provider at 0x0049CB57.
class TerrainRoadType
{
public:
	float getRoadWidth();
};

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
class ThingTemplate;
class Object
{
public:
	char rva00294815();
	const Coord3D *getPosition() const { return &m_position; }
	Object *getContainedBy() const { return m_containedBy; }
	Rva004C2095Contain *getContain() const { return m_contain; }
	const ThingTemplate *getTemplate() const { return m_template; }
	bool test438Bit0() const { return (m_438 & 1) != 0; }
	char m_pad00[0x4];
private:
	const ThingTemplate *m_template; // +0x04
	char m_pad08[0x30];
	Coord3D m_position; // +0x38
	char m_pad44[0x20C];
	Rva004C2095Contain *m_contain; // +0x250
	char m_pad254[0x20];
	Object *m_containedBy; // +0x274
	char m_pad278[0x1C0];
	unsigned char m_438; // +0x438
	char m_pad439[0x3];
};
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

bool PorcupineFormationBodyModule::rva004C2095()
{
	Object *obj = m_object;
	if (obj && obj->getContainedBy() && obj->getContainedBy()->getContain())
		obj->getContainedBy()->getContain()->rvaSlot31();
	return false;
}


bool PorcupineFormationBodyModule::rva004C2127(Object *other)
{
	if (!rva004C2095())
		return true;
	Object *self = m_object;
	if (self == 0)
		return true;
	const PorcupineFormationBodyModuleData *data = (const PorcupineFormationBodyModuleData *)m_moduleData;
	if (data == 0)
		return true;
	if (data->m_level == 0 || data->m_level < other->rva00294815())
		return true;
	const WeaponTemplate *weapon = data->m_weapon;
	if (weapon == 0)
		return false;
	if (Rva004C20D5IsWithin(((TerrainRoadType *)weapon)->getRoadWidth(), self->getPosition(), other->getPosition()))
		TheWeaponStore->rva002CE964(data->m_weapon, self, other);
	return false;
}
