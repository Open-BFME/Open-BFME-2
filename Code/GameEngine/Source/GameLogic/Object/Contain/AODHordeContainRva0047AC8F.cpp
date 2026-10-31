// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include
// ?rva0047AC8F@AODHordeContain@@UAEPAUCoord3D@@PAU2@PAVObject@@H@Z @0x0047AC8F 1563B.
// Native 47AC8F..47B2AA: AOD interface at +11C, output-pointer/RET12 ABI; slot 7 of
// the +0x11C interface vftable 0x00846930. WB1161040 names getUnitsIntendedPosition.
// Physical fields are target accesses; spread scales both axes after the index term.
// The Coord2D length/normalize/toAngle bodies are visible select-any copies of the
// coord2d.cpp homes (also inline) so cl treats the sway local as unaliased.
#include "Lib/Coord3D.h"
#include "Lib/Coord2D.h"
#include <math.h>
// Keep the CRT float wrapper visible under a local name so this unit does
// not emit competing sin(float)/cos(float) definitions.
inline float __cdecl aodSin(float radians) { return sinf(radians); }
inline float __cdecl aodCos(float radians) { return cosf(radians); }
#include "../../../Common/GameLogicObjectLookupView.h"
float Cos(float);
float Sin(float);
struct AODSway : Coord2D
{
 AODSway()
 {
 }
 AODSway(const Coord2D &source)
 {
  x=source.x;
  y=source.y;
 }
 AODSway(const AODSway &aODSway)
 {
  x=aODSway.x;
  y=aODSway.y;
 }
 ~AODSway()
 {
 }
};

class Rva00468E98Point
{
 public: float x,y;
 Rva00468E98Point(const Rva00468E98Point &,float);
 Rva00468E98Point(const Rva00468E98Point &p)
 {
  x=p.x;
  y=p.y;
 }
};

class Rva00468E98
{
 public: Rva00468E98Point rotate(Rva00468E98Point);
};

enum KindOfType
{
 KINDOF_INVALID = -1
};

enum PathfindLayerEnum
{
 LAYER_INVALID = 0
};

class Rva0008BB38FloatField
{
 public:
 float get() const;
};

class Locomotor {public:float getMaxSpeed(Object *) const;};
class AIUpdateInterface
{
 public:
 char m_pad00[0x1F0];
 Locomotor *m_curLocomotor; // +0x1F0
};

#include "../../../Common/Thing/thing.h"

class GeometryInfo
{
 public: float getMaxHeightAbovePosition() const;
};

class Object : public Thing
{
 public:
 bool isKindOf(KindOfType t) const;
 int rva0028B511() const;
 char m_pad060[0x74 - 0x60];
 int m_id; // +0x74
 char m_pad78[0xA8-0x78];
 GeometryInfo m_geometry;
 char m_padA9[0x258-0xA9];
 AIUpdateInterface *m_ai; // +0x258
};

template <int N> class AODTerrainSlots : public AODTerrainSlots<N - 1>
{
 public:
 virtual void gap(char (*)[N]);
};

template <> class AODTerrainSlots<0>
{
};

class TerrainLogic : public AODTerrainSlots<7>
{
 public:
 virtual float getLayerHeight(float x, float y, PathfindLayerEnum layer, Coord3D *normal, bool clip); // slot 7
 virtual void s08();
 virtual void s09();
 virtual void s10();
 virtual void s11();
 virtual void s12();
 virtual void s13();
 virtual void s14();
 virtual void s15();
 virtual void s16();
 virtual void s17();
 virtual void s18();
 virtual bool isUnderwater(float x, float y, float *waterZ, float *terrainZ, int unused); // slot 19
};

extern TerrainLogic *TheTerrainLogic;
extern GameLogic *TheGameLogic;
struct AODHordeContainModuleData
{
 char m_pad00[0x274];
 float m_frequencyScale;
 float m_frequencyRandomness;
 float m_amplitudeScale;
 float m_amplitudeRandomness;
 float m_stillAmplitude;
 float m_frequencyScaleZ;
 float m_frequencyRandomnessZ;
 float m_amplitudeScaleZ;
 float m_amplitudeRandomnessZ;
 float m_stillAmplitudeZ;
 float m_oathFulfilledZFactor;
 float m_2A0;
 float m_largeUnitMinHeight;
 float m_largeUnitMaxHeight;
 unsigned int m_largeUnitTimeout;
 float m_largeUnitTailOff;
 float m_scatterSpeedFactor;
 float m_scatterRandomness;
};

class Rva0046ACF6
{
 public:
 int rva0046ACF6(int id);
};

struct AODOffsetRecord
{
 int m_00;
 Coord2D m_offset; // +0x04
 char m_pad0C[0x1C - 0x0C];
};

struct AODWave
{
 float m_00, m_04, m_08, m_0C, m_10, m_14;
};

struct AODFormationSlot
{
 float m_key; // +0x00
 float m_angle; // +0x04
 Coord3D m_pos; // +0x08
 int m_14;
};

class HordeContainPrimary
{
 public:
 virtual void p00();
 const AODHordeContainModuleData *m_moduleData; // +0x04
 Object *m_object; // +0x08
 char m_pad0C[0x11C - 0x0C];
};

class HordeContainIface
{
 public:
 virtual void i00();
 virtual void i01();
 virtual void i02();
 virtual void i03();
 virtual void i04();
 virtual void i05();
 virtual void i06();
 virtual Coord3D *rva0047AC8F(Coord3D *out,Object *obj, int word) = 0;
 bool m_04; // +0x04
 char m_pad05[0x6C - 0x05];
 AODOffsetRecord *m_records; // +0x6C
 char m_pad70[0x7C - 0x70];
 bool m_7C; // +0x7C
 char m_pad7D[0x184 - 0x7D];
 int m_184; // +0x184
 char m_pad188[0x1F0 - 0x188];
 AODWave *m_wavesBegin; // +0x1F0
 AODWave *m_wavesEnd; // +0x1F4
 char m_pad1F8[0x1FC - 0x1F8];
 ObjectID m_trackedLargeUnit; // +0x1FC
 unsigned int m_largeUnitStartFrame; // +0x200
 Coord3D m_trackedPosition; // +0x204
 float m_largeUnitHeightFactor; // +0x210
 float m_largeUnitHeight; // +0x214
 float m_218; // +0x218
 char m_pad21C[0x5E0 - 0x21C];
 AODFormationSlot m_slots[20]; // +0x5E0
 int m_slotCount; // +0x7C0
};

// HordeContain's own slot 7, called non-virtually with the interface this.
class Rva00474B51
{
 public:
 Coord3D *rva00474B51(Coord3D *out,Object *obj, int word);
};

class HordeContain : public HordeContainPrimary, public HordeContainIface
{
 public:
 virtual Coord3D *rva0047AC8F(Coord3D *out,Object *obj, int word);
 Coord2D *rva0046A5B1(Coord2D *out, int index);
};

class AODHordeContain : public HordeContain
{
 public:
 virtual Coord3D *rva0047AC8F(Coord3D *out,Object *obj, int word);
};

// Byte-faithful select-any copies of the coord2d.cpp bodies, visible so sway stays unaliased.
__declspec(noinline) inline float Coord2D::length() const
{
 return (float)sqrt(x * x + y * y);
}
__declspec(noinline) inline void Coord2D::normalize()
{
 float len = length();
 if (len != 0.0f)
 {
  x /= len;
  y /= len;
 }
}

float ACos(float value);
__declspec(noinline) inline float Coord2D::toAngle() const
{
 float len = length();
 if (len == 0.0f)
  return 0.0f;
 const float raw = x / len;
 float cosine;
 if (raw < -1.0f)
  cosine = -1.0f;
 else if (raw > 1.0f)
  cosine = 1.0f;
 else
  cosine = raw;
 if (y < 0.0f)
  return -ACos(cosine);
 return ACos(cosine);
}

static __forceinline float AODHeightFalloff(float normalizedDistance)
{
 float a = (float)sqrt(normalizedDistance) * normalizedDistance;
 float b = normalizedDistance * normalizedDistance;
 b *= 1.0f - normalizedDistance;
 return a + b;
}

Coord3D *AODHordeContain::rva0047AC8F(Coord3D *out,Object *obj,int word)
{
 if (m_184)
 {
  ((Rva00474B51 *)((char *)this+0x11C))->rva00474B51(out,obj,word);
  return out;
 }
 int index = reinterpret_cast<Rva0046ACF6 *>(this)->rva0046ACF6(obj->m_id);
 AODSway offset(m_records[index].m_offset);
 int i;
 for (i = m_slotCount - 1; i > 0; --i)
 {
  if (m_slots[i].m_key == offset.x)
  break;
 }
 if (i < 0)
 i = 0;
 Coord3D pos;
 pos = m_slots[i].m_pos;
 float angle = m_slots[i].m_angle;
 float bob = 0.95f;
 Coord3D forward;
 Coord3D side;
 forward.y = (float)aodSin(angle);
 side.x = forward.y;
 pos.x -= offset.y * side.x;
 forward.x = (float)aodCos(angle);
 pos.y += offset.y * forward.x;
 const AODHordeContainModuleData *md = m_moduleData;
 if (!m_7C || (unsigned int)index >= (unsigned int)(m_wavesEnd - m_wavesBegin))
 {
  out->x=pos.x;
  out->y=pos.y;
  out->z=pos.z;
  return out;
 }
 Object *me = m_object;
 float speedRatio = 0.0f;
 if (me->m_ai)
 {
  Locomotor *loco = me->m_ai->m_curLocomotor;
  speedRatio = reinterpret_cast<Rva0008BB38FloatField *>(loco)->get() / loco->getMaxSpeed(me);
 }
 float stillBlend = md->m_stillAmplitude;
 if (stillBlend < 0.0f)
 stillBlend = 0.0f;
 if (stillBlend > 1.0f)
 stillBlend = 1.0f;
 if (stillBlend > 0.01f)
 m_04 = true;
 float speedFactor = (1.0f - stillBlend) * speedRatio + stillBlend;
 AODWave *wave = &m_wavesBegin[index];
 AODSway sway;
 sway.y = (float)aodSin(wave->m_00 + wave->m_08 * ((float)TheGameLogic->getFrame() * md->m_frequencyScale)) * wave->m_04;
 sway.y = speedFactor * md->m_amplitudeScale * sway.y;
 sway.x = 0.0f;
 Rva00468E98Point dir=((Rva00468E98 *)this)->rotate(reinterpret_cast<const Rva00468E98Point &>(sway));
 float len = sway.length();
 angle = sway.toAngle() + angle;
 dir.x = Cos(angle);
 dir.y = Sin(angle);
 dir.x *= len;
 dir.y *= len;
 stillBlend = md->m_stillAmplitudeZ;
 if (stillBlend < 0.0f)
 stillBlend = 0.0f;
 if (stillBlend > 1.0f)
 stillBlend = 1.0f;
 if (stillBlend > 0.01f)
 m_04 = true;
 bob += (float)aodSin(wave->m_0C + wave->m_14 * ((float)TheGameLogic->getFrame() * md->m_frequencyScaleZ)) * wave->m_10;
 speedFactor = (1.0f - stillBlend) * speedRatio + stillBlend;
 bob = speedFactor * md->m_amplitudeScaleZ * bob;
 if (obj->isKindOf((KindOfType)0xD7))
 {
  Coord2D spreadOutput;
  Coord2D spread = *rva0046A5B1(&spreadOutput, index);
  spread.normalize();
  float s = md->m_scatterSpeedFactor * m_218;
  s = (float)(index % 5) * md->m_scatterRandomness * m_218 * 0.25f + s;
  spread.x *= s;
  spread.y *= s;
  dir.x += spread.x;
  dir.y += spread.y;
 }
 pos.x += dir.x;
 pos.y += dir.y;
 float waterZ;
 if (TheTerrainLogic->isUnderwater(pos.x, pos.y, &waterZ, 0, 0))
 pos.z = waterZ;
 else
 pos.z = TheTerrainLogic->getLayerHeight(pos.x, pos.y, (PathfindLayerEnum)me->rva0028B511(), 0, true);
 pos.z += bob;
 if (m_trackedLargeUnit)
 {
  float maxHeight = md->m_2A0 * m_largeUnitHeight;
  if (maxHeight > md->m_largeUnitMaxHeight)
  maxHeight = md->m_largeUnitMaxHeight;
  if (maxHeight < md->m_largeUnitMinHeight)
  maxHeight = md->m_largeUnitMinHeight;
  unsigned int elapsed = TheGameLogic->getFrame() - m_largeUnitStartFrame;
  if (elapsed >= md->m_largeUnitTimeout)
  {
   m_trackedLargeUnit = INVALID_OBJECT_ID;
   {
    out->x=pos.x;
    out->y=pos.y;
    out->z=pos.z;
    return out;
   }
  }
  float falloff = 1.0f;
  int half = md->m_largeUnitTimeout / 2;
  if (elapsed > (unsigned int)half)
  falloff = 1.0f - (float)(elapsed - half) / half;
  Coord3D delta;
  const Coord3D *origin = &m_trackedPosition;
  delta.x = pos.x - origin->x;
  delta.y = pos.y - origin->y;
  const Coord3D *facing = me->getUnitDirectionVector2D();
  forward.x=facing->x;
  forward.y=facing->y;
  side.x = -forward.y;
  side.y = forward.x;
  float along = (float)fabs(delta.x * forward.x + delta.y * forward.y);
  float across = (float)fabs(delta.x * side.x + delta.y * side.y);
  across -= m_largeUnitHeightFactor;
  if (across < 0.0f)
  across = 0.0f;
  float dist = along + across;
  float radius = md->m_largeUnitTailOff * maxHeight;
  if (dist < radius)
  {
   float lift = (1.0f - AODHeightFalloff(dist / radius)) * maxHeight;
   lift *= falloff;
   pos.z += lift;
  }
 }
 if (obj->isKindOf((KindOfType)0xD7))
 {
  float rank = md->m_scatterSpeedFactor * md->m_oathFulfilledZFactor * m_218;
  rank = (float)((index + 2) % 5) * md->m_scatterRandomness * md->m_oathFulfilledZFactor * m_218 * 0.25f + rank;
  pos.z += rank;
 }
 {
  out->x=pos.x;
  out->y=pos.y;
  out->z=pos.z;
  return out;
 }
}
