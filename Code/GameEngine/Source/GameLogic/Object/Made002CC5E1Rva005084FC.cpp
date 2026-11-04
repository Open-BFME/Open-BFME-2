// cl: /O1 /DNDEBUG /MD /arch:SSE /ICode/GameEngine/Source/Common
// Retail0x005084FC186B; vtable00864048 slot14 owned by matched DamageNugget
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
#include "GameLogicObjectLookupView.h"
struct Coord3D;
#include "../../../Include/GameLogic/Module/AttributeModifierPoolUpdate.h"
struct Rva005086CEPair {void *context;void *list;};
class Rva00291793 {public:int rva00291793();};
class Rva005086CEContain {public:
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual void slot26();
 virtual void slot27();
 virtual void slot28();
 virtual void slot29();
 virtual void slot30();
 virtual void slot31();
 virtual void slot32();
 virtual void slot33();
 virtual void slot34();
 virtual void slot35();
 virtual void slot36();
 virtual void slot37();
 virtual void slot38();
 virtual void slot39();
 virtual void slot40();
 virtual void slot41();
 virtual void slot42();
 virtual void slot43();
 virtual void slot44();
 virtual void slot45();
 virtual void slot46();
 virtual void slot47();
 virtual void slot48();
 virtual void slot49();
 virtual void slot50();
 virtual void slot51();
 virtual void slot52();
 virtual void slot53();
 virtual void slot54();
 virtual void slot55();
 virtual void slot56();
 virtual void slot57();
 virtual void slot58();
 virtual void slot59();
 virtual void slot60();
 virtual void slot61();
 virtual void slot62();
 virtual void slot63();
 virtual void slot64();
 virtual void slot65();
 virtual void slot66();
 virtual void slot67();
 virtual void slot68();
 virtual void slot69();
 virtual void slot70();
 virtual Rva005086CEPair *members(Rva005086CEPair*);
};
template<int N> class BitFlags {public: __declspec(nothrow) BitFlags(const BitFlags&);unsigned words[7];};
extern BitFlags<116> KINDOFMASK_NONE;
int Rva00360C1FEqual(const void*,const void*);
#include "../../Common/Thing/thing.h"
template<class T> static __forceinline const T& minDamageRatio(const T&lhs,const T&rhs) {return rhs<lhs?rhs:lhs;}

// Construct the verified owner of the native 0x7C damage record. The
// older DamageInfo constructor pin also names divergent definitions.
// DamageInfo stays opaque at the already-owned method boundaries.
class DamageInfo;
class Rva00263895Member
{
public:
 Rva00263895Member() throw();
 unsigned char pad00[0x10];
 int damageType10;
 unsigned char pad14[0x0C];
 float amount20;
 bool flag24;
 unsigned char pad25[0x4B];
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
class Object
{
public:
 void attemptDamage(DamageInfo *info);
 float rva0028D2C5(void*) const;
 void attemptHealing(float amount, const Object *source);
 unsigned char pad00[4];
 Rva005084FCModuleView *module04;
 unsigned char pad08[0x250-8]; Rva005086CEContain *contain250;
private:
 friend class DamageNugget;
 AttributeModifierPoolUpdate *findAttributeModifierPoolUpdate() const;
};
extern GameLogic *TheGameLogic;
struct Rva005086CETemplate {char pad[0x140];bool scaleByCount;unsigned char divisor;};
struct Rva005084FCWeaponView
{
 unsigned char pad00[4];
 Rva005086CETemplate *parameters;
 int sourceID08;
};
#include "../../../Include/GameLogic/Module/Rva00507823.h"
class DamageNugget : public Rva00507823
{
public:
 bool rva005084FC(void *weapon, Object *target, const Coord3D *position);
 bool rva005086CE(void *weapon,Object *target);
private:
 unsigned char pad128[0x178 - 0x128];
 BitFlags<116> filter178;
 bool flag194;
 unsigned char pad195[3];
 float value198;
 bool generateDamageInfo(void *weapon, Object *target, DamageInfo *info, bool flag, const Coord3D *position);
};
bool DamageNugget::rva005084FC(void *weapon, Object *target, const Coord3D *position)
{
 Rva00263895Member info;
 if (generateDamageInfo(weapon, target, (DamageInfo*)&info, false, position) == true)
 {
  if (info.damageType10 == 7)
   target->attemptHealing(info.amount20, target);
  else
  {
   target->attemptDamage((DamageInfo*)&info);
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

// Native 005086CE..0050882B, RET8, owning vtable864048/864C38 slot1.
// WB0109F2E0 confirms the full target/filter/modifier flow. The explicit
// minimum reference followed by a value copy preserves its scalar lifetime.
// The final <= guard preserves retail behavior for unordered float values.
// Pinned BFME1 a7c38d3b DamageNugget.cpp supplies the source-count/divisor
// damage scale with a reference-returning min; native fixes the target ABI,
// condition filter and modifier-category gate. Original virtual name unknown.
bool DamageNugget::rva005086CE(void *weapon,Object *target)
{
 Rva005084FCWeaponView *descriptor=(Rva005084FCWeaponView*)weapon;
 if(!rva005075D6(weapon,target)) return false;
 Rva00263895Member info;
 generateDamageInfo(weapon,target,(DamageInfo*)&info,true,0);
 if(!target) return false;
 Object *source=TheGameLogic->findObjectByID((ObjectID)descriptor->sourceID08);
 if(!source) return false;
 // The existing equality provider returns canonical integer 0 or 1; this
 // caller consumes its low byte, as native TEST AL proves.
 if(!(unsigned char)Rva00360C1FEqual(&filter178,&KINDOFMASK_NONE)) {
  BitFlags<116> required(filter178);
  if(((Thing*)target)->isKindOfMulti(required,KINDOFMASK_NONE)) {
   AttributeModifierPoolUpdate *modifiers=source->findAttributeModifierPoolUpdate();
   if(modifiers && modifiers->isCategoryDisabled(1)) return false;
  }
 }
 float damage=target->rva0028D2C5((char*)&info+4);
 if(descriptor->parameters->scaleByCount) {
  Rva005086CEContain *contain=source->contain250;
  if(contain) {
   Rva005086CEPair pair;
   unsigned count=((Rva00291793*)contain->members(&pair))->rva00291793();
   int divisor=descriptor->parameters->divisor;
   if(divisor>0) {
    float ratio=(float)count/divisor;
    const float& selected=minDamageRatio(ratio,1.0f);
    float scale=selected;
    damage=damage*scale;
   }
  }
 }
 if(damage<=0.0f && !info.flag24) return false;
 return true;
}
