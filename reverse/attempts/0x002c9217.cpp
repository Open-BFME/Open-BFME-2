// ?getDzAdjustedRange@WeaponTemplate@@QBEMABVWeaponBonus@@M@Z
// partial score=0.72 date=2026-09-24
// Partial score=0.72 date=2026-09-24
// Scratch-only target-driven C++ trial for game.dat 0x002C9217 (161B, ret 8).
// Supersedes the 0.23 bank (same path): layout hypothesis converged
// (bonus.RANGE x template range - 2.5, dz threshold/base/scale triple,
// abs-dz dead zone, non-negative clamp), all callees settled (_fabs only).
// Identity is provisional: a WeaponTemplate range query over (bonus, dz)
// sitting between free wrappers 0x2C92B8/0x2C92DC and rowed
// getMinimumAttackRange; public overload name unresolved, so this stash uses
// a descriptive stand-in. Do NOT row this name without wrapper/chain proof.
// Proven by probe matrix (10 variants, LCS 0.9184 instruction-aligned):
// - head homes this in esi exactly (push esi + mov esi,ecx placement)
// - fabs tail needs the (float) cast form for homing; nocast breaks it
// - zero-first clamp (0.0f > r) is exact; r-first mirrors operands
// Walls (no lever after 10 probes, do NOT retry blind):
// - jbe vs retail jb on the (0-dz < m_dzThreshold) compare: every '<'-family
//   spelling mirrors operands (loads threshold to a register); '>' keeps the
//   mem form but inverts meaning. Systemic MSVC7.1 canonicalization.
// - fabs x87 stack: mine dups st(0) where retail fxchs (2-4B length delta).
// cl: /O1 /arch:SSE /MD /DNDEBUG
typedef float Real;
extern "C" double fabs(double value);
extern const float g_unk0xBCFB10;
class WeaponBonus
{
public:
	Real m_fields[6];
};
class WeaponTemplate
{
public:
	float getDzAdjustedRange(const WeaponBonus &bonus, float dz) const;
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
float WeaponTemplate::getDzAdjustedRange(const WeaponBonus &bonus, float dz) const
{
	float range = bonus.m_fields[2] * m_unmodifiedAttackRange - g_unk0xBCFB10;
	float negDz = 0.0f - dz;
	if (negDz > m_dzThreshold) {
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
