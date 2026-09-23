// ?getDelayBetweenShotsRva002C9322@WeaponTemplate@@QBEHPBUBfmeWeaponBonusArrayRva002C9322@@M@Z
// partial score=0.5555555555555556 date=2026-09-23
// Scratch-only reference adaptation for the WeaponTemplate timing sibling.
// Target caller at RVA 0x002CE3F2 supplies a six-float bonus array plus a Real factor.
// Public signature/name is provisional; no production identity or pin is asserted.
// cl: /O1 /DNDEBUG /MD /EHs-c-
#include <math.h>
typedef int Int;
typedef float Real;
struct BfmeWeaponBonusArrayRva002C9322 { Real fields[6]; };
class WeaponTemplate
{
public:
    Int getDelayBetweenShotsRva002C9322(const BfmeWeaponBonusArrayRva002C9322 *bonus, Real factor) const;
private:
    char m_pad00[0xF0];
    Int m_minDelayBetweenShots;
    Int m_maxDelayBetweenShots;
};
Int GetGameLogicRandomValue(Int lo, Int hi, char *file, Int line);
__forceinline long fast_float2long_round(float f)
{
    long i;
    __asm {
        fld [f]
        fistp [i]
    }
    return i;
}

Int WeaponTemplate::getDelayBetweenShotsRva002C9322(
    const BfmeWeaponBonusArrayRva002C9322 *bonus, Real factor) const
{
    Int delayToUse;
    if (m_minDelayBetweenShots == m_maxDelayBetweenShots)
        delayToUse = m_minDelayBetweenShots;
    else
        delayToUse = GetGameLogicRandomValue(m_minDelayBetweenShots, m_maxDelayBetweenShots,
            "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Weapon.cpp", 988);
    return fast_float2long_round((Real)floor((double)((Real)delayToUse / (bonus->fields[3] * factor))));
}
