// cl: /O1 /DNDEBUG /MD /I. /ICode/Libraries/Include /ICode/Libraries/Include/Lib /ICode/GameEngine/Include /ICode/GameEngine/Source/Common /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfmelist
// stlport
//
// Retail 0x00508120 (988B): DamageNugget damage-info fill helper, called by
// 0x005084FC (matched in Made002CC5E1Rva005084FC.cpp). Scoped view: emits the
// helper body only, does not model the vtable. The distance goes through
// math.h's inline sqrtf and the clamped distance is a named local; together
// they give retail's info/damage load placement around the visible
// PreRTS clamp<float> call (row 0x0000575A).
#include <math.h>
#include <list>
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#include <vector>
#include "GameLogic/ContainmentListView.h"
#include "Coord3D.h"
struct DamageOffset : Coord3D {
 void set(const Coord3D *other){ x=other->x; y=other->y; z=other->z; }
 void sub(const Coord3D *other){ x-=other->x; y-=other->y; z-=other->z; }
};
#include "RTS/XYDistanceCallView.h"
class DamageInfo
{
public:
 DamageInfo();
 unsigned char pad00[8];
 int sourceID08;
 int playerMask0C;
 int damageType10;
 int deathType14;
 int value18;
 int value1C;
 float amount20;
 bool flag24;
 bool flag25;
 unsigned char pad26[2];
 float delay28;
 int value2C;
 unsigned char pad30[0x40];
 float value70;
 float value74;
 unsigned char pad78[4];
};
class Rva005084FCModuleView
{
public:
 unsigned char pad00[0x10B];
 unsigned char flags10B;
};
class Player
{
public:
 unsigned char pad00[0x54];
 int index54;
};
#define RVA00508120_SLOT(n) virtual void slot##n();
#define RVA00508120_SLOT10(n) RVA00508120_SLOT(n##0) RVA00508120_SLOT(n##1) RVA00508120_SLOT(n##2) RVA00508120_SLOT(n##3) RVA00508120_SLOT(n##4) RVA00508120_SLOT(n##5) RVA00508120_SLOT(n##6) RVA00508120_SLOT(n##7) RVA00508120_SLOT(n##8) RVA00508120_SLOT(n##9)
// Object +0x250 contain interface: slot 71 (+0x11C) returns the eight-byte
// member descriptor that the pinned 0x0036AE51 copies into a local list.
class Rva00508120ContainView
{
public:
 RVA00508120_SLOT10(0) RVA00508120_SLOT10(1) RVA00508120_SLOT10(2) RVA00508120_SLOT10(3)
 RVA00508120_SLOT10(4) RVA00508120_SLOT10(5) RVA00508120_SLOT10(6) RVA00508120_SLOT(70)
 virtual Rva0036AE51ListView getMemberView();
};
class Object
{
public:
 void attemptDamage(DamageInfo *info);
 void attemptHealing(float amount, const Object *source);
 Player *getControllingPlayer() const;
 bool rva0028C149(int attribute, float *value, int arg);
 bool rva0028C15E(int attribute, float *value, int arg, int arg2);
 typedef bool (Object::*BoolLastScale)(int, float *, int, bool);
 __forceinline bool scaleBy(int attribute, float *value, int nameFilter, bool useInnateAttributes)
 { return (this->*reinterpret_cast<BoolLastScale>(&Object::rva0028C15E))(attribute, value, nameFilter, useInnateAttributes); }
 float rva002615E3(const Coord3D *position) const;
 bool rva0028F44C(const Object *other) const;
 unsigned char pad00[4];
 Rva005084FCModuleView *module04;
 unsigned char pad08[0x30];
 Coord3D position38;
 unsigned char pad44[0x250 - 0x44];
 Rva00508120ContainView *contain250;
};
#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
struct Rva005084FCWeaponView
{
 unsigned char pad00[8];
 int sourceID08;
};
struct Rva00508120WeaponTemplateView
{
 unsigned char pad00[0x10];
 int value10;
 unsigned char pad14[0x140 - 0x14];
 bool m_passengerProportionalAttack;
 unsigned char m_maxAttackPassengers;
 unsigned char pad142[0x16D - 0x142];
 bool m_shouldPlayUnderAttackEvaEvent;
 unsigned char pad16E[3];
 bool flag171;
};
struct Rva00508120WeaponView
{
 unsigned char pad00[4];
 Rva00508120WeaponTemplateView *template04;
 int sourceID08;
};
class ObjectFilter
{
public:
 bool isValid() const;
};
class Rva2225E0Filter : public ObjectFilter
{
public:
 bool accepts(Object *object, Player *player);
private:
 unsigned char pad00[4];
};
struct Rva00508120Scalar
{
 Rva2225E0Filter filter;
 float factor;
};
template <class T> T clamp(T lo, T value, T hi)
{
 if (value < lo)
  return lo;
 else if (value > hi)
  return hi;
 else
  return value;
}
class Rva00507823
{
public:
 virtual ~Rva00507823();
};
class DamageNugget : public Rva00507823
{
public:
private:
 bool generateDamageInfo(void *weapon, Object *target, DamageInfo *info, bool flag, const Coord3D *position);
private:
 unsigned char pad04[0x128 - 4];
 float damage128;
 float minDamage12C;
 float maxRadius130;
 float minRadius134;
 unsigned char pad138[0x148 - 0x138];
 bool bonusEnabled148;
 unsigned char pad149[3];
 float bonusScale14C;
 float scale150;
 unsigned int delay154;
 int damageType158;
 int value15C;
 int deathType160;
 int value164;
 _STL::vector<Rva00508120Scalar> scalars168;
 float speed174;
 unsigned char pad178[0x194 - 0x178];
 bool flag194;
 unsigned char pad195[3];
 float value198;
 Rva2225E0Filter filter19C;
};

// Retail 0x00508120 (988B, ret 0x14): the damage-info fill helper called only
// by 0x005084FC. WorldBuilder's debug build names it
// DamageNugget::generateDamageInfo (DamageNugget.cpp); BFME 1's matched
// DamageNugget::generateDamageInfo (0x002DB880) is the donor for the flow
// (contained-count scaling, filter scalars, attribute bonus/multiplier,
// distance delay). Target-only, from the native body: radius falloff of the
// damage between +0x12C (min damage, -1 disables) and +0x128 over the clamped
// distance +0x134..+0x130, the 0x0028F44C mutual bonus/scale block skipped by
// the flag argument, the +0x19C filter that sets DamageInfo +0x24 and the
// 32-bit player mask.
bool DamageNugget::generateDamageInfo(void *weapon, Object *target, DamageInfo *info, bool flag, const Coord3D *position)
{
 Rva00508120WeaponView *view = static_cast<Rva00508120WeaponView *>(weapon);
 Object *source = TheGameLogic->findObjectByID((ObjectID)view->sourceID08);
 if (!source)
  return false;
 if (minDamage12C != -1.0f && position)
 {
  float distance = sqrtf(((Rva000CBA20 *)target)->distSq((const Rva000CBA20Point *)position));
  float clamped = clamp(minRadius134, distance, maxRadius130);
  float ratio = (clamped - minRadius134) / (maxRadius130 - minRadius134);
  float damage = damage128;
  info->amount20 = damage - (damage - minDamage12C) * ratio;
 }
 else
  info->amount20 = damage128;
 Rva00508120ContainView *contain;
 if (view->template04->m_passengerProportionalAttack && (contain = source->contain250) != 0)
 {
  unsigned int count = contain->getMemberView().rva0036AE51().size();
  int maximum = view->template04->m_maxAttackPassengers;
  if (maximum > 0)
  {
   float ratio = (float)count / maximum;
   info->amount20 *= _STL::min(ratio, 1.0f);
  }
 }
 int scalars = scalars168.size();
 for (int i = 0; i < scalars; ++i)
 {
  if (scalars168[i].filter.accepts(target, source->getControllingPlayer()))
  {
   info->amount20 *= scalars168[i].factor;
   break;
  }
 }
 if (bonusEnabled148 && info->amount20 != 0.0f)
 {
  float bonus = 0.0f;
  if (source->rva0028C149(2, &bonus, 0))
   info->amount20 += bonus;
 }
 float multiplier = 1.0f;
 bool scaled;
 if (damageType158 == 15)
  scaled = source->scaleBy(11, &multiplier, 0, true);
 else
 {
  bool flag171 = false;
  if (view->template04)
   flag171 = view->template04->flag171;
  scaled = source->scaleBy(3, &multiplier, 0, flag171);
 }
 if (scaled)
  info->amount20 *= multiplier;
 float delay = (float)delay154;
 if (target)
 {
  if (speed174 > 0.0f)
  {
   DamageOffset offset;
   offset.set(&target->position38);
   offset.sub(&source->position38);
   delay += offset.length() / speed174;
  }
  if (!flag)
  {
   if (target->rva0028F44C(source))
    info->amount20 *= bonusScale14C + 1.0f;
   if (source->rva0028F44C(target))
   {
    info->amount20 = scale150 * info->amount20;
    if (info->amount20 < 1.0f)
     return false;
   }
  }
 }
 if (filter19C.isValid() && filter19C.accepts(target, source->getControllingPlayer()))
  info->flag24 = true;
 info->damageType10 = damageType158;
 info->deathType14 = deathType160;
 info->value18 = value164;
 info->value1C = value15C;
 info->delay28 = delay;
 info->sourceID08 = view->sourceID08;
 Player *player = source->getControllingPlayer();
 info->playerMask0C = 1 << player->index54;
 info->value2C = view->template04->value10;
 info->flag25 = view->template04->m_shouldPlayUnderAttackEvaEvent;
 return true;
}
