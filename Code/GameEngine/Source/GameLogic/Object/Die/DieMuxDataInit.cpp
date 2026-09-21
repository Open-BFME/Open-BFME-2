// cl: /O1 /arch:SSE /MD /DNDEBUG /DWIN32 /D_WINDOWS
// stlport
//
// ?init@DieMuxData@@QAEPAV1@XZ, retail 0x004CE534, 57 bytes. Frameless
// member initializer: ors the flag word at +0 to -1, resets the two
// bitset<128> members at +0x04/+0x14 through the rowed 0x24CA24, and loads
// the three damage-range floats at +0x24/+0x28/+0x2C from the shared -1.0
// and 1.0 pool constants (literals, value-verified). Returns this for
// chaining (mov eax,esi tail, Rva0025342CMember-construct precedent).
// Identity: 11 member-position callers all lea-ecx-plus-call with the
// +8-first-member pattern (SlowDeath-first per the BFME1
// SlowDeathBehaviorModuleData donor, ZH OpenContain.h first-member); the
// frameless-0x30 bitset/float shape fits BFME2-extended DieMuxData (ZH
// DieMuxData has DeathTypeFlags plus VeterancyLevelFlags plus exempt plus
// required; BFME2 adds the flag word and damage floats). Needed by the
// AudioLoopUpgrade 0x4B7C00 and SlowDeath 0x45E386 ctors.

#include <bitset>

namespace _STL {
template<> bitset<128> &bitset<128>::reset();
}

class DieMuxData
{
public:
	DieMuxData *init();

private:
	int m_flags; // +0
	_STL::bitset<128> m_deathTypes; // +0x04
	_STL::bitset<128> m_veterancyLevels; // +0x14
	float m_damageThreshold; // +0x24
	float m_minDamage; // +0x28
	float m_maxDamage; // +0x2C
};

// ?init@DieMuxData@@QAEPAV1@XZ @0x4CE534
DieMuxData *DieMuxData::init()
{
	m_flags |= -1;
	m_deathTypes.reset();
	m_veterancyLevels.reset();
	m_damageThreshold = -1.0f;
	m_minDamage = 1.0f;
	m_maxDamage = -1.0f;
	return this;
}
