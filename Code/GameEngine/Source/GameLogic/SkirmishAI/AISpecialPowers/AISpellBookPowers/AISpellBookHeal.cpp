// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// AISpellBookHeal::shouldActivate, retail 0x005D81A4 (109B), from the
// WorldBuilder lead (AISpellBookHeal.cpp): find one of the player's units in
// combat (the spell book base at +0x28, 0x005EEA20 with true, true), gather
// the combat statistics within 350 of it (AISpellBookBase::
// getStatsInCombatRange, 0x005EEBF6, into a zeroed 16-byte record from
// 0x005EE9CE) and, when the record's +4 ratio is under 0.8, let the AoE target
// picker (0x005EE8DD) settle on the unit's position.
//
// Target facts: the statistics record, the base and the picker keep their
// ledger's address-derived names.

typedef bool Bool;

#include "../../../../../../Libraries/Include/Lib/Coord3D.h"

class Player;

class Object
{
public:
	Player *getControllingPlayer() const;
	const Coord3D *getPosition() const { return &m_position; }

private:
	unsigned char m_pad00[0x38];
	Coord3D m_position;
};

class Rva005EE9CE
{
public:
	Rva005EE9CE *rva005EE9CE();

	float m_0;
	float m_ratio;
	float m_8;
	float m_c;
};

class Rva005EEA20
{
public:
	Object *rva005EEA20(Player *player, Bool a, Bool b);
	void getStatsInCombatRange(Rva005EE9CE *stats, Object *unit, float range);
};

class Rva005EE816
{
public:
	Bool rva005EE8DD(const Coord3D *pos, Object *obj);
};

class AISpellBookHeal
{
public:
	Bool shouldActivate(Object *obj);

private:
	unsigned char m_pad00[0x28];
	Rva005EEA20 m_base;
};

Bool AISpellBookHeal::shouldActivate(Object *obj)
{
	Object *unit = m_base.rva005EEA20(obj->getControllingPlayer(), true, true);
	if (unit)
	{
		Rva005EE9CE stats;
		stats.rva005EE9CE();
		m_base.getStatsInCombatRange(&stats, unit, 350.0f);
		if (stats.m_ratio < 0.8f)
			return ((Rva005EE816 *)this)->rva005EE8DD(unit->getPosition(), obj);
	}
	return false;
}
