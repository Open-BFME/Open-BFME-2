// ?isDieApplicable@DieMuxData@@QBE_NPBVObject@@PBVDamageInfo@@@Z
// partial score=0.9901870692484411 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /DWIN32 /D_WINDOWS
// stlport
#include <bitset>

namespace _STL {
template<> bitset<128> &bitset<128>::reset();
}

enum ObjectID { INVALID_ID = 0 };
struct Coord3D { float x, y, z; };
class Rva0026157E { public: bool testMasks(const void *required, const void *exempt) const; };
class Object {
public:
 Coord3D *getPlanarDirectionTo(Coord3D *out, const Object *killer) const;
 float getOrientation() const { return orientation; }
 const Rva0026157E *getStatus() const { return (const Rva0026157E *)&status; }
private:
 char pad0[0x44]; float orientation; char pad48[0x94-0x48]; _STL::bitset<128> status;
};
class GameLogic { public: Object *findObjectByID(ObjectID); };
extern GameLogic *TheGameLogic;
struct DamageInput { char pad0[8]; ObjectID source; char pad0C[0x1C-0x0C]; int deathType; float amount; };
class DamageInfo { public: DamageInput in; };
extern "C" float __cdecl atan2f(float y, float x);
extern "C" double __cdecl fabs(double x);
float normalizeAngle(float a);

class DieMuxData
{
public:
 bool isDieApplicable(const Object *obj, const DamageInfo *damageInfo) const;

private:
	int m_flags; // +0
	_STL::bitset<128> m_exemptStatus; // +0x04
	_STL::bitset<128> m_requiredStatus; // +0x14
	float m_damageThreshold; // +0x24
	float m_angleMin; // +0x28
	float m_angleMax; // +0x2C
};

// Target004CE588..004CE69D(277B): donor DieModule.cpp confirms death-mask
// and object-status gate purpose. Native omits the donor veterancy word,
// adds damage threshold+24 and circular direction-angle limits+28/+2C.
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
  if (fabs(normalizeAngle(angle - midpoint)) > halfRange) return false;
 }
 return true;
}
