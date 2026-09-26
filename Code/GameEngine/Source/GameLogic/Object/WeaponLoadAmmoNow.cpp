// cl: /O1 /DNDEBUG /MD /EHs-c-
// BFME1 Weapon::loadAmmoNow with BFME2's six-field bonus record.
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
    void loadAmmoNow(const Object *source);
protected:
    void computeBonus(const Object *source, unsigned flags, WeaponBonus &bonus) const;
    void reloadWithBonus(const Object *source, const WeaponBonus &bonus, bool immediate);
};
void Weapon::loadAmmoNow(const Object *source)
{
    WeaponBonus bonus;
    computeBonus(source, 0, bonus);
    reloadWithBonus(source, bonus, true);
}
