// cl: /DNDEBUG /MD /EHs-c-
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

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?Rva002CE1AC@Weapon@@QAEXPAVObject@@@Z=?loadAmmoNow@Weapon@@QAEXPBVObject@@@Z")
