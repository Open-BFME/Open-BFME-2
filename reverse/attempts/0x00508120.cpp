// ?rva00508120@Made002CC5E1@@AAE_NPAXPAVObject@@PAVDamageInfo@@_NPBUCoord3D@@@Z
// partial score=0.9889686996647947 date=2026-10-10
// ?rva00508120@Made002CC5E1@@AAE_NPAXPAVObject@@PAVDamageInfo@@_NPBUCoord3D@@@Z
// partial score=0.97 date=2026-10-09
// cl: /O1 /DNDEBUG /MD /I. /ICode/Libraries/Include /ICode/GameEngine/Include /ICode/GameEngine/Source/Common /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfmelist
// stlport
// Retail0x005084FC186B; vtable00864048 slot14 owned by matched Made002CC5E1
// deleting destructor/constructor. Original method name unknown. This scoped
// view emits the method body only and deliberately does not model the vtable.
// BFME1 b25 DamageNugget generateDamageInfo is the fill-helper semantic lead,
// not this apply wrapper. Nativehelper508120 RET20 receives weapon opaque
// pointer target Object DamageInfo flag and Coord3D position; nativecall2615E3
// establishes lastarg coordinate pointer (not float). DamageInfo ctor263895
// and offsets10/20/70/74 from native loads and matched Object/heal siblings.
// Target healing passes target itself; source bonus healing passes null.
// Bonus tests !=0 (unordered included) whereas final result tests >0.
// Parent correction of uncompiled router artifact; native wrapper5084FC186B.
// DamageInfo local uses already-pinned ctor263895 and actual named attemptDamage.
#include <math.h>
#include <list>
#include <vector>
// ContainmentListView.h (inlined for the bank)
#include <list>
struct Rva0036ADF9Element {
    int rawWords[1];
    bool operator<(const Rva0036ADF9Element &) const;
    bool operator==(const Rva0036ADF9Element &) const;
};
typedef _STL::list<Rva0036ADF9Element> ContainmentList;
// Consumers read the first dword as an object pointer or identifier. Preserve
// its bits without treating the opaque element as a different C++ object type.
inline const int &containmentFirstWord(const Rva0036ADF9Element &element)
{
    return element.rawWords[0];
}
class Rva0036AE51ListView {
public:
    void *a;
    ContainmentList *b;
    ContainmentList rva0036AE51();
};
struct Coord3D
{
 float x, y, z;
 void set(const Coord3D *other) { x = other->x; y = other->y; z = other->z; }
 void sub(const Coord3D *other) { x -= other->x; y -= other->y; z -= other->z; }
 float length() const;
};
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
 bool rva0028C15E(int attribute, float *value, int arg, bool arg2);
 float rva002615E3(const Coord3D *position) const;
 bool rva0028F44C(const Object *other) const;
 unsigned char pad00[4];
 Rva005084FCModuleView *module04;
 unsigned char pad08[0x30];
 Coord3D position38;
 unsigned char pad44[0x250 - 0x44];
 Rva00508120ContainView *contain250;
};
enum ObjectID { INVALID_ID = 0 };
class GameLogic
{
public:
 Object *findObjectByID(ObjectID id);
};
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
 bool scaleByContained140;
 unsigned char maxContained141;
 unsigned char pad142[0x16D - 0x142];
 bool flag16D;
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
template <class T> T clamp(T lo, T value, T hi);
class Rva00507823
{
public:
 virtual ~Rva00507823();
};
class Made002CC5E1 : public Rva00507823
{
public:
 bool rva005084FC(void *weapon, Object *target, const Coord3D *position);
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
 bool rva00508120(void *weapon, Object *target, DamageInfo *info, bool flag, const Coord3D *position);
};
bool Made002CC5E1::rva005084FC(void *weapon, Object *target, const Coord3D *position)
{
 DamageInfo info;
 if (rva00508120(weapon, target, &info, false, position) == true)
 {
  if (info.damageType10 == 7)
   target->attemptHealing(info.amount20, target);
  else
  {
   target->attemptDamage(&info);
   float factor = value198 * info.value70;
   if (flag194)
   {
    if (factor != 0.0f)
    {
     Object *source = TheGameLogic->findObjectByID((ObjectID)static_cast<Rva005084FCWeaponView *>(weapon)->sourceID08);
     if (source && !(source->module04->flags10B & 2))
      source->attemptHealing(factor, 0);
    }
   }
  }
 }
 if (info.value74 > 0.0f)
  return true;
 return false;
}

// Retail 0x00508120 (988B, ret 0x14): the damage-info fill helper called only
// by 0x005084FC above. WorldBuilder's debug build names it
// DamageNugget::generateDamageInfo (DamageNugget.cpp); BFME 1's matched
// DamageNugget::generateDamageInfo (0x002DB880) is the donor for the flow
// (contained-count scaling, filter scalars, attribute bonus/multiplier,
// distance delay). Target-only, from the native body: radius falloff of the
// damage between +0x12C (min damage, -1 disables) and +0x128 over the clamped
// distance +0x134..+0x130, the 0x0028F44C mutual bonus/scale block skipped by
// the flag argument, the +0x19C filter that sets DamageInfo +0x24 and the
// 32-bit player mask.
bool Made002CC5E1::rva00508120(void *weapon, Object *target, DamageInfo *info, bool flag, const Coord3D *position)
{
 Rva00508120WeaponView *view = static_cast<Rva00508120WeaponView *>(weapon);
 Object *source = TheGameLogic->findObjectByID((ObjectID)view->sourceID08);
 if (!source)
  return false;
 if (minDamage12C != -1.0f && position)
 {
  float distance = (float)sqrt(target->rva002615E3(position));
  float damage = damage128;
  info->amount20 = damage - (damage - minDamage12C) * ((clamp(minRadius134, distance, maxRadius130) - minRadius134) / (maxRadius130 - minRadius134));
 }
 else
  info->amount20 = damage128;
 Rva00508120ContainView *contain;
 if (view->template04->scaleByContained140 && (contain = source->contain250) != 0)
 {
  unsigned int count = contain->getMemberView().rva0036AE51().size();
  int maximum = view->template04->maxContained141;
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
  scaled = source->rva0028C15E(11, &multiplier, 0, true);
 else
 {
  bool flag171 = false;
  if (view->template04)
   flag171 = view->template04->flag171;
  scaled = source->rva0028C15E(3, &multiplier, 0, flag171);
 }
 if (scaled)
  info->amount20 *= multiplier;
 float delay = (float)delay154;
 if (target)
 {
  if (speed174 > 0.0f)
  {
   Coord3D offset;
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
 info->playerMask0C = 1 << (this?source->getControllingPlayer():source->getControllingPlayer())->index54;
 info->value2C = view->template04->value10;
 info->flag25 = view->template04->flag16D;
 return true;
}
