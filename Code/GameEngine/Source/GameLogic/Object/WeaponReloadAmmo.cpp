// cl: /DNDEBUG /MD /EHs-c-
// BFME1 Weapon::reloadAmmo with BFME2's six-field bonus record.
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
#include "../../../Include/GameLogic/Weapon.h"
void Weapon::reloadAmmo(const Object *source)
{
    WeaponBonus bonus;
    computeBonus(source, 0, bonus);
    reloadWithBonus(source, bonus, false);
}
