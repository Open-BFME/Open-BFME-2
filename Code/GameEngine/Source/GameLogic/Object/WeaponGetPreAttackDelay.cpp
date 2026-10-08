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

class Object
{
public:
	int getNumConsecutiveShotsFiredAtTarget(const Object *victim, const Coord3D *pos) const;
	Coord3D rva0028BE93() const;
	const Coord3D *getPosition() const { return &m_position; }

private:
	unsigned char m_pad00[0x38];
	Coord3D m_position; // +0x38
};

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

class WeaponTemplate
{
public:
	int getClipSize() const { return m_clipSize; }
	WeaponPrefireType getPrefireType() const { return m_prefireType; }
	int getPreAttackDelay(const WeaponBonus &bonus) const
	{
		return (int)(m_preAttackDelay * bonus.getField(PRE_ATTACK));
	}

private:
	unsigned char m_pad000[0xE4];
	int m_clipSize; // +0xE4
	unsigned char m_padE8[0x12C - 0xE8];
	WeaponPrefireType m_prefireType; // +0x12C
	unsigned char m_pad130[0x138 - 0x130];
	int m_preAttackDelay; // +0x138
};

class Weapon
{
public:
	int getPreAttackDelay(const Object *source, const Object *victim, const Coord3D *pos) const;
	unsigned int getRemainingAmmo(bool b) const;

protected:
	void computeBonus(const Object *source, unsigned flags, WeaponBonus &bonus) const;

private:
	unsigned char m_pad00[0x04];
	const WeaponTemplate *m_template; // +0x04
	unsigned char m_pad08[0x58 - 0x08];
	int m_preAttackDelayExtra; // +0x58
};

int Weapon::getPreAttackDelay(const Object *source, const Object *victim, const Coord3D *pos) const
{
	WeaponPrefireType type = m_template->getPrefireType();
	if (type == PREFIRE_PER_CLIP)
	{
		if (m_template->getClipSize() > 0 && getRemainingAmmo(false) < (unsigned int)m_template->getClipSize())
			return 0;
	}
	else if (type == PREFIRE_PER_ATTACK)
	{
		if (source->getNumConsecutiveShotsFiredAtTarget(victim, pos) > 0)
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
		return m_template->getPreAttackDelay(bonus) + m_preAttackDelayExtra;
	}
}
