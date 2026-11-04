// cl: /O1 /DNDEBUG /MD /EHs-c- /arch:SSE
// ?getPreAttackDelay@Weapon@@QBEHPBVObject@@0PBUCoord3D@@@Z, retail 0x002CCFF0
// (168 bytes).
// Identity (target): WorldBuilder's debug Weapon.cpp:3612 body
// Weapon::getPreAttackDelay calls, in retail's order,
// Weapon::getRemainingAmmo, Object::getNumConsecutiveShotsFiredAtTarget,
// an Object position query, Coord3D equality and Weapon::computeBonus.
// Donor (Zero Hour Weapon::getPreAttackDelay): no delay when the prefire
// type is per clip (2) and the clip is part used, or per attack (1) and
// the source already fired at the victim; otherwise the template's
// pre-attack delay scaled by the bonus. BFME 2 deltas (target): a victim
// position argument, a per-position type (3) with no delay while the
// source's last shot position (Object 0x0028BE93) equals its own position
// (+0x38), the six-field WeaponBonus (pre-attack field 4), and the
// Weapon's own +0x58 delay added to the result.
// Layout (target): Weapon::m_template +0x04; template clip size +0xE4,
// prefire type +0x12C, pre-attack delay +0x138.
#include "../../../../Libraries/Include/Lib/Coord3D.h"

struct Arg1_004DEA70;
struct Coord3DBase;

#include "object.h"

enum WeaponPrefireType
{
	PREFIRE_PER_SHOT = 0,
	PREFIRE_PER_ATTACK = 1,
	PREFIRE_PER_CLIP = 2,
	PREFIRE_PER_POSITION = 3
};

enum WeaponBonusField
{
	PRE_ATTACK = 4,
	FIELD_COUNT = 6
};

class WeaponBonus
{
public:
	WeaponBonus()
	{
		for (int i = 0; i < FIELD_COUNT; ++i)
			m_field[i] = 1.0f;
	}
	float getField(WeaponBonusField f) const { return m_field[f]; }

private:
	float m_field[FIELD_COUNT];
};

#include "../../../Include/GameLogic/WeaponTemplate.h"

// The header has no prefire or pre-attack-delay accessors; these TU-local
// inlines read its +0x12C prefire type and +0x138 delay.
static __forceinline WeaponPrefireType weaponTemplatePrefireType(const WeaponTemplate *wt)
{
	return wt->m_prefireType;
}
static __forceinline int weaponTemplatePreAttackDelay(const WeaponTemplate *wt, const WeaponBonus &bonus)
{
	return (int)(wt->m_preAttackDelay * bonus.getField(PRE_ATTACK));
}

#include "../../../Include/GameLogic/Weapon.h"

int Weapon::getPreAttackDelay(const Object *source, const Object *victim, const Coord3D *pos) const
{
	WeaponPrefireType type = weaponTemplatePrefireType(m_template);
	if (type == PREFIRE_PER_CLIP)
	{
		if (m_template->getClipSize() > 0 && getRemainingAmmo(false) < (unsigned int)m_template->getClipSize())
			return 0;
	}
	else if (type == PREFIRE_PER_ATTACK)
	{
		if ((int)const_cast<Object *>(source)->rva0028BE7F(
                reinterpret_cast<Arg1_004DEA70 *>(const_cast<Object *>(victim)),
                reinterpret_cast<const Coord3DBase *>(pos)) > 0)
			return 0;
	}
	else if (type == PREFIRE_PER_POSITION)
	{
		Coord3D lastShotPos = source->rva0028BE93();
		if (lastShotPos == *source->getPosition())
			return 0;
	}

	// Shape (inference): retail lets the bonus share the position
	// temporary's frame slot, so it lives in its own block.
	{
		WeaponBonus bonus;
		computeBonus(source, 0, bonus);
		return weaponTemplatePreAttackDelay(m_template, bonus) + (int)m_tailState;
	}
}
