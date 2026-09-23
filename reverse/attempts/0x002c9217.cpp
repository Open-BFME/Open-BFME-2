// ?calculateRva002C9217@WeaponTemplateRangeRva002C9217@@QBEMPBUBonusRva002C9217@@M@Z
// partial score=0.22981366459627328 date=2026-09-23
// Scratch-only target-driven C++ trial for the BFME source-aware range family.
// Public identity remains provisional; target extent 0x002C9217, 161 bytes.
// cl: /O1 /arch:SSE /DNDEBUG /MD /EHs-c-
typedef float Real;
struct BonusRva002C9217 { Real fields[6]; };
class WeaponTemplateRangeRva002C9217
{
public:
    Real calculateRva002C9217(const BonusRva002C9217 *bonus, Real sourceDistance) const;
private:
    char pad00[0x14];
    Real m_attackRange;
    char pad18[4];
    Real m_rangeThreshold;
    Real m_rangeBase;
    Real m_rangeScale;
    char pad28[0x164 - 0x28];
    Real m_absoluteDistanceLimit;
};
extern "C" double fabs(double value);
Real WeaponTemplateRangeRva002C9217::calculateRva002C9217(
    const BonusRva002C9217 *bonus, Real sourceDistance) const
{
    Real range = bonus->fields[2] * m_attackRange - 2.5f;
    if ((0.0f - sourceDistance) >= m_rangeThreshold)
        range += m_rangeBase - (m_rangeThreshold + sourceDistance) * m_rangeScale;
    if (m_absoluteDistanceLimit > 0.0f && fabs((double)sourceDistance) > m_absoluteDistanceLimit)
        range = 0.0f;
    if (range < 0.0f)
        range = 0.0f;
    return range;
}
