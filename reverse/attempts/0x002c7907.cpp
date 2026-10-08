// ?getAbleToUseWeaponAgainstTarget@WeaponSet@@QBE?AW4CanAttackResult@@W4AbleToAttackType@@PBVObject@@1PBUCoord3D@@W4CommandSourceType@@@Z
// partial score=0.88 date=2026-10-08
// BANK ONLY: native WeaponSet::getAbleToUseWeaponAgainstTarget 0x002C7907, 1020B RET20.
// Donor semantic lead: reference BFME1 ba7ddda ZH WeaponSet.cpp, plus WB
// WeaponSet.cpp 1091..1183 independently showing the BFME additions.
// Native Object +4 template, +38 position, +94 status, +250 contain,
// +258 AI, +274 containedBy agree with already matched siblings. Six slots
// +8..1C and anti mask +2C agree with the ctor and update418.
// NativeContainedRange is an opaque two-word returned view: WB uses its +4
// list pointer and a debug virtual destructor; retail inlines its cleanup.
// The names of these container slots and the returned class remain unknown.
// The 116 BitFlags cast preserves the existing isAnyKindOf callee pin ABI;
// the native seven-word masks are BitFlags<218> at template +EC +slot*28.
// Best trial has retail's 1020-byte extent, but is NOT exact: local this and
// contain spill slots are swapped; early contain null assignment, mask-loop
// branch polarity, and late POSSIBLE constant/owner register allocation differ.
// getVictimAntiMask is an ordinary static function whose compiler chooses EDX;
// it is banked separately at 135B versus retail136 and has no admitted pin.
// No dummy ECX parameter, asm, guessed class identity or byte-lift is used.
// cl: /O1 /Oy- /G7 /arch:SSE /DNDEBUG /MD
#include "../Code/Libraries/Include/Lib/Coord3D.h"
extern "C" double __cdecl fabs(double);
enum CanAttackResult { NOT_POSSIBLE=0, INVALID_SHOT=1, AFTER_MOVING=2, POSSIBLE=3 };
enum AbleToAttackType { ATTACK_NEW_TARGET=0 };
enum CommandSourceType { CMD_FROM_PLAYER=0 };
enum ObjectStatusTypes { STATUS_25=0x25 };
template<int N> class BitFlags { public: bool any() const; unsigned words[7]; };
class Thing { public: bool isAnyKindOf(const BitFlags<116>&) const; };
class Object;
class SpawnBehaviorInterface { public:
virtual void slot0()=0;
virtual void slot1()=0;
virtual void slot2()=0;
virtual void slot3()=0;
virtual void slot4()=0;
virtual void slot5()=0;
virtual CanAttackResult slot6(AbleToAttackType,const Object *,const Coord3D *,CommandSourceType)=0;
};
struct NativeItem { NativeItem *next,*prev; Object *object; };
struct NativeItemList { NativeItem *head; };
struct NativeContainedRange { unsigned first; NativeItemList *list; };
class Bfme250Interface { public:
virtual void slot0()=0;
virtual void slot1()=0;
virtual void slot2()=0;
virtual void slot3()=0;
virtual bool slot4() const=0;
virtual void slot5()=0;
virtual void slot6()=0;
virtual void slot7()=0;
virtual void slot8()=0;
virtual void slot9()=0;
virtual void slot10()=0;
virtual void slot11()=0;
virtual void slot12()=0;
virtual void slot13()=0;
virtual void slot14()=0;
virtual void slot15()=0;
virtual void slot16()=0;
virtual void slot17()=0;
virtual void slot18()=0;
virtual void slot19()=0;
virtual void slot20()=0;
virtual void slot21()=0;
virtual void slot22()=0;
virtual void slot23()=0;
virtual void slot24()=0;
virtual void slot25()=0;
virtual void slot26()=0;
virtual void slot27()=0;
virtual void slot28()=0;
virtual void slot29()=0;
virtual void slot30()=0;
virtual void slot31()=0;
virtual void slot32()=0;
virtual void slot33()=0;
virtual void slot34()=0;
virtual void slot35()=0;
virtual void slot36()=0;
virtual void slot37()=0;
virtual void slot38()=0;
virtual void slot39()=0;
virtual void slot40()=0;
virtual void slot41()=0;
virtual void slot42()=0;
virtual void slot43()=0;
virtual void slot44()=0;
virtual bool slot45() const=0;
virtual void slot46()=0;
virtual void slot47()=0;
virtual void slot48()=0;
virtual void slot49()=0;
virtual void slot50()=0;
virtual void slot51()=0;
virtual void slot52()=0;
virtual void slot53()=0;
virtual void slot54()=0;
virtual bool slot55(const Object *,const Object **)=0;
virtual void slot56()=0;
virtual void slot57()=0;
virtual void slot58()=0;
virtual void slot59()=0;
virtual void slot60()=0;
virtual void slot61()=0;
virtual void slot62()=0;
virtual void slot63()=0;
virtual void slot64()=0;
virtual void slot65()=0;
virtual void slot66()=0;
virtual void slot67()=0;
virtual void slot68()=0;
virtual void slot69()=0;
virtual NativeContainedRange slot70() const=0;
virtual void slot71()=0;
virtual void slot72()=0;
virtual void slot73()=0;
virtual void slot74()=0;
virtual void slot75()=0;
virtual bool slot76(Coord3D *,Coord3D *) const=0;
};
class Rva001E46E1 { public: float rva001E4845(Object *); };
struct NativeAI { char pad[0x1f0]; Rva001E46E1 *module; };
struct NativeWeaponKinds { char pad[0x108]; unsigned k108,k10C,k110,k114; };
class Object { public:
 bool testStatus(ObjectStatusTypes) const;
 Object *rva002931F5(bool);
 float GetRelativeAngle(const Coord3D *) const;
 bool isAbleToAttack() const;
 CanAttackResult getAbleToUseWeaponAgainstTarget(AbleToAttackType,const Object *,const Coord3D *,CommandSourceType) const;
 SpawnBehaviorInterface *getSpawnBehaviorInterface() const;
 char pad0[4]; NativeWeaponKinds *m_template;
 char pad8[0x38-8]; Coord3D m_position;
 char pad44[0x94-0x44]; unsigned m_status;
 char pad98[0x250-0x98]; Bfme250Interface *m_contain;
 char pad254[4]; NativeAI *m_ai;
 char pad25C[0x274-0x25c]; Object *m_containedBy;
};
struct NativeWeaponTemplate { char pad0[0x2c]; float m_angle; char pad30[0x170-0x30]; bool m_noObject; };
class Rva002C9B80Owner { public: bool rva002CB2D1(Object *,const Coord3D *,const void *,const Coord3D *); };
class Weapon { public:
 bool isWithinAttackRange(const Object *,const Object *,float,int) const;
 char isWithinAttackRange(Object *,void *,float,int) const;
 bool rva002CCED3(const Object *,const Object *);
 void *m_0; NativeWeaponTemplate *m_template;
};
struct NativeWeaponSetTemplate { char pad[0xec]; BitFlags<218> masks[6]; };
class WeaponSet { public:
 CanAttackResult getAbleToUseWeaponAgainstTarget(AbleToAttackType,const Object *,const Object *,const Coord3D *,CommandSourceType) const;
 private: bool isAnyWithinTargetPitch(const Object *,const Object *) const;
 char pad0[4]; NativeWeaponSetTemplate *m_set; Weapon *m_weapons[6];
 int m_current,m_lock; unsigned m_filled,m_anti;
};
__forceinline bool nativeBit(const void *mask,unsigned bit) { return (static_cast<const unsigned *>(mask)[bit>>5]>>(bit&31))&1; }
__declspec(noinline) static int getVictimAntiMask(const Object *victim)
{
 NativeWeaponKinds *t=victim->m_template;
 unsigned a=t->k10C;
 if(a&0x800000) return 0x12;
 if(a&0x100000) return 8;
 unsigned b=t->k110;
 if(b&0x800) return 0x40;
 unsigned c=t->k108;
 if(c&0x2000000) return 4;
 if(nativeBit(&victim->m_status,6)) {
   if(c&0x200) return 1;
   if(c&0x100) return 0x20;
   if(c&0x400) return 0x200;
   return (b>>7)&0x80;
 }
 return ((c&0x80)|1)*2;
}

CanAttackResult WeaponSet::getAbleToUseWeaponAgainstTarget(AbleToAttackType attackType,const Object *source,const Object *victim,const Coord3D *pos,CommandSourceType commandSource) const
{
 int targetAntiMask;
 if(victim) { targetAntiMask=getVictimAntiMask(victim); pos=&victim->m_position; }
 else targetAntiMask=2;
 const Object *containedBy=source->m_containedBy;
 Bfme250Interface *contain;
 if(containedBy) contain=containedBy->m_contain;
 else contain=0;
 if(source->testStatus(STATUS_25) && !(attackType&8)) {
   if(!containedBy) return INVALID_SHOT;
   if(contain) {
     const Object *otherVictim=0;
     if(contain->slot55(source,&otherVictim)) {
       if(!otherVictim) return NOT_POSSIBLE;
       if(otherVictim!=victim && const_cast<Object *>(otherVictim)->rva002931F5(false)!=const_cast<Object *>(victim)->rva002931F5(false)) return NOT_POSSIBLE;
     }
   }
 }
 char withinAttackRange=false;
 bool hasAWeaponInRange=false;
 bool hasAWeapon=false;
 for(int slot=0;slot<6;++slot) {
   Weapon *weapon=m_weapons[slot];
   if(weapon) {
     hasAWeapon=true;
     if((m_anti&targetAntiMask)==0) continue;
     if(victim && weapon->m_template->m_noObject) continue;
     if(source->testStatus(STATUS_25)) withinAttackRange=true;
     else if(contain && contain->slot4()) {
       Coord3D targetPos; targetPos.x=pos->x; targetPos.y=pos->y; targetPos.z=pos->z;
       Coord3D goalPos;
       if(!(source->m_template->k114&0x2000) && contain->slot76(&goalPos,&targetPos))
         withinAttackRange=((Rva002C9B80Owner *)weapon)->rva002CB2D1(const_cast<Object *>(source),&goalPos,victim,&targetPos);
       else if(victim) withinAttackRange=weapon->isWithinAttackRange(source,victim,0.0f,1);
     }
     else if(victim) withinAttackRange=weapon->isWithinAttackRange(source,victim,0.0f,1);
     else withinAttackRange=weapon->isWithinAttackRange(const_cast<Object *>(source),const_cast<Coord3D *>(pos),0.0f,1);
     if(withinAttackRange) {
       if(source->m_template->k108&4) {
         if(!source->m_ai || !source->m_ai->module) {
           float angle=weapon->m_template->m_angle;
           if(angle>0.0f && pos && fabs(source->GetRelativeAngle(pos))>angle) withinAttackRange=false;
         }
       }
       if(withinAttackRange) { hasAWeaponInRange=true; break; }
     }
   }
 }
 if((source->m_template->k108&4) || (source->m_template->k110&0x100000) || (containedBy && !(containedBy->m_template->k114&0x2000))) {
   if(hasAWeapon && !hasAWeaponInRange && attackType!=4) return INVALID_SHOT;
 }
 else if(source->m_ai && source->m_ai->module && (source->m_ai->module->rva001E4845(const_cast<Object *>(source))<=0.0f)) {
   if(hasAWeapon && !hasAWeaponInRange && attackType!=4) return INVALID_SHOT;
 }
 CanAttackResult okResult=withinAttackRange ? POSSIBLE : AFTER_MOVING;
 if((m_anti&targetAntiMask)==0) return INVALID_SHOT;
 if(!victim) return okResult;
 if(!isAnyWithinTargetPitch(source,victim)) return INVALID_SHOT;
 int first,last;
 if(m_lock) first=last=m_current;
 else { first=5;last=0; }
 for(int i=first;i>=last;--i) {
   Weapon *weapon=m_weapons[i];
   if(weapon && weapon->rva002CCED3(source,victim)) {
     const BitFlags<218> &only=m_set->masks[i];
     if(!only.any() || ((const Thing *)victim)->isAnyKindOf((const BitFlags<116> &)only)) return okResult;
   }
 }
 contain=source->m_contain;
 if(contain && contain->slot45()) {
   NativeContainedRange items=contain->slot70();
   for(NativeItem *it=items.list->head->next;it!=items.list->head;it=it->next) {
     Object *member=it->object;
     if(member->isAbleToAttack()) {
       CanAttackResult result=member->getAbleToUseWeaponAgainstTarget(attackType,victim,pos,commandSource);
       if(result==POSSIBLE || result==AFTER_MOVING) return result;
     }
   }
 }
 SpawnBehaviorInterface *spawn=source->getSpawnBehaviorInterface();
 if(spawn && spawn->slot6(attackType,victim,pos,commandSource)==POSSIBLE) {
   if((source->m_template->k108&4) && (source->m_template->k110&0x100000) && okResult==AFTER_MOVING) okResult=POSSIBLE;
   return okResult;
 }
 return INVALID_SHOT;
}
