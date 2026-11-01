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
class TerrainRoadType
{
public:
	float getRoadWidth();
};

class WeaponTemplate;
class Object;
class WeaponStore
{
public:
	void rva002CE964(const WeaponTemplate *tmpl, const Object *source, const Object *target);
};
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
class Object
{
public:
	char rva00294815();
	const Coord3D *getPosition() const { return &m_position; }
	Object *getContainedBy() const { return m_containedBy; }
	Rva004C2095Contain *getContain() const { return m_contain; }
private:
	unsigned char m_pad000[0x38];
	Coord3D m_position;		// +0x38
	unsigned char m_pad044[0x250 - 0x44];
	Rva004C2095Contain *m_contain;	// +0x250
	unsigned char m_pad254[0x274 - 0x254];
	Object *m_containedBy;		// +0x274
};
class DamageInfo;
struct PorcupineFormationBodyModuleData
{
	unsigned char m_pad00[0x68];
	const WeaponTemplate *m_weapon;	// +0x68
	char m_level;			// +0x6C
};
class ModuleData;
class ModuleBase
{
public:
	virtual ~ModuleBase();
protected:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"
class BodyModuleInterface : public Rva004C2095Slots<0>
{
public:
	virtual void attemptDamage(DamageInfo *damageInfo) = 0;
	virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
	virtual void s05(); virtual void s06(); virtual void s07(); virtual void s08();
	virtual void s09(); virtual void s10(); virtual void s11(); virtual void s12();
	virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16();
	virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20();
	virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
	virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28();
	virtual void s29(); virtual void s30(); virtual void s31(); virtual void s32();
	virtual void s33(); virtual void s34(); virtual void s35(); virtual void s36();
	virtual void s37();
	virtual bool rva004C2127(Object *other) = 0;
};
class ActiveBody : public ModuleBase, public BehaviorModuleInterface, public BodyModuleInterface
{
public:
	virtual void attemptDamage(DamageInfo *damageInfo);
};
class PorcupineFormationBodyModule : public ActiveBody
{
public:
	virtual void attemptDamage(DamageInfo *damageInfo);
	virtual bool rva004C2127(Object *other);
	bool rva004C2095();
	void rva004C21A9(DamageInfo *damageInfo);
	bool Rva004C20D5IsWithin(float range, const Coord3D *a, const Coord3D *b);
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

