// cl: /DNDEBUG /MD /EHs-c-
// ?getClipReloadTime@Weapon@@QBEHPBVObject@@@Z @0x002C9AC5 57B
// Weapon clip reload with computed bonus: 6x1.0f bonus then computeBonus plus template time.
// Evidence: same Weapon TU neighbours; [ecx+4] template like siblings; callees rowed computeBonus plus getClipReloadTime.
class Object;
typedef float Real;
class WeaponBonus
{
public:
	enum Field { DAMAGE = 0, RADIUS, RANGE, RATE_OF_FIRE, PRE_ATTACK };
	WeaponBonus()
	{
		for (int i = 0; i < 6; ++i)
			m_field[i] = 1.0f;
	}
	Real getField(Field field) const { return m_field[field]; }
	void appendBonuses(WeaponBonus &bonus) const;
	Real m_field[6];
};
#include "../../../Include/GameLogic/WeaponTemplate.h"
#include "../../../Include/GameLogic/Weapon.h"
int Weapon::getClipReloadTime(const Object *source) const
{
	WeaponBonus bonus;
	computeBonus(source, 0, bonus);
	return m_template->getClipReloadTime(bonus);
}
