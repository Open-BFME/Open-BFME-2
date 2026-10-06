// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?isOutOfAmmo@WeaponSet@@QBE_NXZ @0x002C73CE, 41B.
// WeaponSet::isOutOfAmmo. Returns true when every present weapon reports
// OUT_OF_AMMO (1), skipping null slots. Retail scans the six slots at +0x8.
// Evidence: neighbour WeaponSetRvaSlotSearch.cpp proves six slots at +0x8;
// caller 0x0028ADD5 does add ecx 0x330 then jmp here (Object WeaponSet
// forwarder); callee ?getStatus@Weapon@@QBE?AW4WeaponStatus@@XZ is rowed.
// Donor: ZH WeaponSet::isOutOfAmmo verbatim except WEAPONSLOT_COUNT 6.
//
// ?isAnyWithinTargetPitch@WeaponSet@@ABE_NPBVObject@@0@Z @0x002C7362, 60B.
// WeaponSet::isAnyWithinTargetPitch (private). Returns true when no pitch
// limit or any of the six slots at +0x8 reports isWithinTargetPitch.
// Evidence: [ecx+0x34] early-out plus six-slot loop calling rowed
// ?isWithinTargetPitch@Weapon@@QBE_NPBVObject@@0@Z; caller 0x002C7BC3.
// Donor: ZH WeaponSet::isAnyWithinTargetPitch verbatim except 6 slots.

enum WeaponStatus
{
	READY_TO_FIRE,
	OUT_OF_AMMO,
	BETWEEN_FIRING_SHOTS,
	RELOADING_CLIP,
	PRE_ATTACK
};

class Object;

class Weapon
{
public:
	WeaponStatus getStatus() const;
	bool isWithinTargetPitch(const Object *obj, const Object *victim) const;
	void loadAmmoNow(const Object *obj);
	void reloadAmmo(const Object *obj);
};

class WeaponSet
{
public:
	bool isOutOfAmmo() const;
	void reloadAllAmmo(const Object *obj, bool now);

private:
	bool isAnyWithinTargetPitch(const Object *obj, const Object *victim) const;

private:
	char m_pad[8];
	Weapon *m_weapons[6];
	char m_pad20[0x34 - 0x20];
	bool m_hasPitchLimit;
};

bool WeaponSet::isOutOfAmmo() const
{
	for (int i = 0; i < 6; ++i) {
		const Weapon *weapon = m_weapons[i];
		if (weapon == 0)
			continue;
		if (weapon->getStatus() != OUT_OF_AMMO)
			return false;
	}
	return true;
}

bool WeaponSet::isAnyWithinTargetPitch(const Object *obj, const Object *victim) const
{
	if (!m_hasPitchLimit)
		return true;
	for (int i = 0; i < 6; ++i) {
		const Weapon *weapon = m_weapons[i];
		if (weapon && weapon->isWithinTargetPitch(obj, victim))
			return true;
	}
	return false;
}

void WeaponSet::reloadAllAmmo(const Object *obj, bool now)
{
	for (int i = 0; i < 6; ++i) {
		Weapon *weapon = m_weapons[i];
		if (weapon != 0) {
			if (now)
				weapon->loadAmmoNow(obj);
			else
				weapon->reloadAmmo(obj);
		}
	}
}
