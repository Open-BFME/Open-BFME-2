// ?adjustedRange@Rva002C9217@@QBEMABVWeaponBonus@@M@Z
// partial score=0.93 date=2026-10-10
// cl: /O1 /arch:SSE /MD /DNDEBUG /D_CRTIMP=
typedef float Real;
extern "C" double fabs(double value);

class WeaponBonus
{
public:
	Real m_fields[6];
};
class Rva002C9217
{
public:
	float adjustedRange(const WeaponBonus &bonus, float dz) const;
private:
	char m_pad00[0x14];
	float m_unmodifiedAttackRange;
	float m_minimumAttackRange;
	float m_dzThreshold;
	float m_dzBase;
	float m_dzScale;
	char m_pad28[0x164 - 0x28];
	float m_absDzLimit;
};
float Rva002C9217::adjustedRange(const WeaponBonus &bonus, float dz) const
{
	float range = bonus.m_fields[2] * m_unmodifiedAttackRange - 2.5f;
	float negDz = 0.0f - dz;
	if (negDz >= m_dzThreshold) {
		float adjust = m_dzThreshold + dz;
		adjust *= m_dzScale;
		range = m_dzBase - adjust + range;
	}
	if (m_absDzLimit > 0.0f) {
		if ((float)fabs((double)dz) > m_absDzLimit)
			range = 0.0f;
	}
	if (0.0f > range)
		range = 0.0f;
	return range;
}
