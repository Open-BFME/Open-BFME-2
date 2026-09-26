// cl: /O1 /DNDEBUG /MD /EHs-c-
// BFME1 Weapon::reloadAmmo with BFME2's six-field bonus record.
class Object;
class WeaponBonus
{
public:
    WeaponBonus()
    {
        for (int i = 0; i < 6; ++i)
            m_multiplier[i] = 1.0f;
    }
private:
    float m_multiplier[6];
};
class Weapon
{
public:
    void reloadAmmo(const Object *source);
protected:
    void computeBonus(const Object *source, unsigned flags, WeaponBonus &bonus) const;
    void reloadWithBonus(const Object *source, const WeaponBonus &bonus, bool immediate);
};
void Weapon::reloadAmmo(const Object *source)
{
    WeaponBonus bonus;
    computeBonus(source, 0, bonus);
    reloadWithBonus(source, bonus, false);
}
