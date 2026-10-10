// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /DWIN32 /D_WINDOWS
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

#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Common/GameLogicObjectLookupView.h"
class Rva0026157E { public: bool testMasks(const void *required, const void *exempt) const; };
class Object {
public:
 Coord3D *getPlanarDirectionTo(Coord3D *out, const Object *killer) const;
 float getOrientation() const { return orientation; }
 const Rva0026157E *getStatus() const { return (const Rva0026157E *)&status; }
private:
 char pad0[0x44]; float orientation; char pad48[0x94-0x48]; _STL::bitset<128> status;
};
extern GameLogic *TheGameLogic;
struct DamageInput { char pad0[8]; ObjectID source; char pad0C[0x1C-0x0C]; int deathType; float amount; };
class DamageInfo { public: DamageInput in; };
extern "C" float __cdecl atan2f(float y, float x);
extern "C" double __cdecl fabs(double x);
float normalizeAngle(float a);

class DieMuxData
{
public:
	DieMuxData *init();
	bool isDieApplicable(const Object *obj, const DamageInfo *damageInfo) const;

private:
	int m_flags; // +0
	_STL::bitset<128> m_exemptStatus; // +0x04
	_STL::bitset<128> m_requiredStatus; // +0x14
	float m_damageThreshold; // +0x24
	float m_angleMin; // +0x28
	float m_angleMax; // +0x2C
};

// ?init@DieMuxData@@QAEPAV1@XZ @0x4CE534
DieMuxData *DieMuxData::init()
{
	m_flags |= -1;
	m_exemptStatus.reset();
	m_requiredStatus.reset();
	m_damageThreshold = -1.0f;
	m_angleMin = 1.0f;
	m_angleMax = -1.0f;
	return this;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??0DieMuxData@@QAE@XZ=?init@DieMuxData@@QAEPAV1@XZ")

// ?isDieApplicable@DieMuxData@@QBE_NPBVObject@@PBVDamageInfo@@@Z
// Target004CE588..004CE69D(277B): donor DieModule.cpp confirms death-mask
// and object-status gate purpose. Native omits the donor veterancy word,
// adds damage threshold+24 and circular direction-angle limits+28/+2C.
// The initializer's former death/veterancy/min/max labels were structural
// guesses; this body establishes the required/exempt and angle use.
// Required/exempt mask meaning comes from rowed tester26157E, and the
// direction source/amount offsets8/20 and deathType1C from native access.
bool DieMuxData::isDieApplicable(const Object *obj, const DamageInfo *damageInfo) const
{
 if (!(m_flags & (1 << (damageInfo->in.deathType - 1)))) return false;
 if (!obj->getStatus()->testMasks(&m_requiredStatus, &m_exemptStatus)) return false;
 if (m_damageThreshold >= 0.0f && m_damageThreshold > damageInfo->in.amount) return false;
 if (m_angleMax > m_angleMin) {
  Object *source = TheGameLogic->findObjectByID(damageInfo->in.source);
  if (!source) return false;
  Coord3D direction;
  obj->getPlanarDirectionTo(&direction, source);
  float orientation = obj->getOrientation();
  float sourceAngle = atan2f(direction.y, direction.x);
  float angle = normalizeAngle(orientation - sourceAngle);
  float midpoint = (*(const volatile float*)&m_angleMax + m_angleMin) * 0.5f;
  float halfRange = m_angleMax - midpoint;
  if (fabs((this?(normalizeAngle(angle - midpoint)):(normalizeAngle(angle - midpoint)))) > halfRange) return false;
 }
 return true;
}
