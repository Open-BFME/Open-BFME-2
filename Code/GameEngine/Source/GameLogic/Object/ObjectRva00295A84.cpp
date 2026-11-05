// cl: /O1
//
// ?rva00295A84@Object@@QAEXPAV1@@Z retail 0x00295A84..0x00295CA6 (546B).
// Object melee-command gate: Native295A84..295CA6 RET4 and WB CC1CB0, caller
// 0x295CA6 (melee victim picker) and the target recursion establish Object's
// adjacent melee command. Original method name unresolved: retain the
// existing Object ABI spelling.
//
// Equal-arm conditional on the template receiver (ai->m_flag3c7 ? t : t)
// keeps retail's ai=EDI / related=EBX allocation (W7-S2 r4 sweep).
#include "../../../../Libraries/Include/Lib/Coord3D.h"
class Object;class Player;class Thing;
enum ObjectStatusTypes{STATUS_26=0x26,STATUS_45=0x45,STATUS_1C=0x1c,STATUS_0F=0x0f,STATUS_11=0x11};
enum WeaponSlotType{WEAPONSLOT_PRIMARY=0};
enum Relationship{ENEMIES=0};
bool rva00344EB2Gate(Object*,Thing*);
template<int N>class Slots:public Slots<N-1>{public:virtual void gap(char(*)[N]);};template<>class Slots<0>{};
#include "../../../Include/GameLogic/Module/AIUpdate.h"
class Rva002C9400ByteField
{
public:
	unsigned char get() const;
};
#include "../../../Include/GameLogic/Weapon.h"
struct ThingTemplateView{char pad00[0x108];unsigned char kinds[28];bool isStructure()const{return(kinds[0]&0x80)!=0;}bool isKind55()const{return(kinds[6]&0x80)!=0;}};
class Object{public:
 void rva00295A84(Object*);
 Object*rva0028ACA0()const;bool testStatus(ObjectStatusTypes)const;Object*rva002931F5(bool);
 const Weapon*getCurrentWeapon(WeaponSlotType*)const;bool rva0029493F(Object*,int);
 bool rva0028CC7C(int);Player*getControllingPlayer()const;bool rva002943B2(const Player*);bool rva0028F518();void rva0028CDB6();bool rva0028CECF();Relationship getRelationship(const Object*)const;
 char pad00[4];ThingTemplateView*m_template;char pad08[0x258-8];AIUpdateInterface*m_ai;char pad25c[0x456-0x25c];bool m_recursing;
};
void Object::rva00295A84(Object*victim){
 if(victim){
  AIUpdateInterface *ai=m_ai;
  if(ai && !m_recursing && !rva00344EB2Gate(this,(Thing*)victim)){
   Object *related=rva0028ACA0();
   if(!ai->m_field3C7 && related){
    bool same=(victim==related);
    if(victim->testStatus(STATUS_26)){
     related=related->rva002931F5(false);
     if(victim->rva002931F5(false)==related)same=true;
    }
    if(!testStatus(STATUS_26) || (ai->m_field3C7 ? victim->m_template : victim->m_template)->isStructure()){
     if(!same)return;
    }
   }
   if(ai->rva00262DA3())return;
   const Weapon *weapon=getCurrentWeapon(0);if(!weapon)return;
   if(!((const Rva002C9400ByteField *)weapon->m_template)->get())return;
   if(rva0029493F(victim,2) && rva0028CECF())return;
   related=rva002931F5(false);
   if(testStatus(STATUS_26) && related && related->rva0029493F(victim,2) && related->rva0028CECF())return;
   if(ai->getMoodMatrixValue()&0x2000)return;
   if(!rva0028CC7C((int)victim))return;
   if(!ai->isIdle() && !ai->rva00262D8F())return;
   if(testStatus(STATUS_45) || testStatus(STATUS_1C))return;
   if(victim->rva002943B2(getControllingPlayer()))return;
   if(rva0028F518())return;
   if(testStatus(STATUS_0F) && !testStatus(STATUS_11))return;
   ai->rva0026D3FB(victim);rva0028CDB6();ai->setLocomotorGoalNone();
   m_recursing=true;
   if(victim->getRelationship(this)==ENEMIES && !victim->m_template->isKind55())victim->rva00295A84(this);
   m_recursing=false;
  }
 }
}
