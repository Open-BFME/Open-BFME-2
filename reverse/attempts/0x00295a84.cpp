// ?rva00295A84@Object@@QAEXPAV1@@Z
// partial score=0.9933078158 date=2026-10-10
// cl: /I. /O1 /G7 /MD /EHsc
// Native295A84..295CA6 RET4 and WB CC1CB0, caller295CA6 melee-victim
// picker, and target recursion establish Object's adjacent melee command.
// Original method name unresolved: retain the existing Object ABI spelling.
#include "Code/Libraries/Include/Lib/Coord3D.h"
class Object;class Player;class Thing;
enum ObjectStatusTypes{STATUS_26=0x26,STATUS_45=0x45,STATUS_1C=0x1c,STATUS_0F=0x0f,STATUS_11=0x11};
enum WeaponSlotType{WEAPONSLOT_PRIMARY=0};
enum Relationship{ENEMIES=0};
bool rva00344EB2Gate(Object*,Thing*);
template<int N>class Slots:public Slots<N-1>{public:virtual void gap(char(*)[N]);};template<>class Slots<0>{};
class AIUpdateInterface:public Slots<110>{public:
 virtual bool slot110();virtual bool slot111();virtual void slot112();virtual bool slot113();
virtual void slot114();virtual void slot115();virtual void slot116();virtual void slot117();virtual void slot118();virtual void slot119();virtual void slot120();virtual void slot121();virtual void slot122();virtual void slot123();virtual void slot124();virtual void slot125();virtual void slot126();virtual void slot127();virtual void slot128();virtual void slot129();virtual void slot130();virtual void slot131();virtual void slot132();virtual void slot133();virtual void slot134();virtual void slot135();virtual void slot136();
 unsigned getMoodMatrixValue()const;void rva0026D3FB(Object*);
 char pad04[0x3c7-4];bool m_flag3c7;
};
class Rva002C9400ByteField{public:unsigned char get()const;};
class Weapon{public:char pad00[4];Rva002C9400ByteField *m_field;};
struct ThingTemplateView{char pad00[0x108];unsigned char kinds[28];bool isStructure()const{return(kinds[0]&0x80)!=0;}bool isKind55()const{return(kinds[6]&0x80)!=0;}};
class Rva0028CECFOwner{public:bool rva0028CECF();};
class Object{public:
 void rva00295A84(Object*);
 Object*rva0028ACA0()const;bool testStatus(ObjectStatusTypes)const;Object*rva002931F5(bool);
 const Weapon*getCurrentWeapon(WeaponSlotType*)const;bool rva0029493F(Object*,int);
 bool rva0028CC7C(int);Player*getControllingPlayer()const;bool rva002943B2(const Player*);bool rva0028F518();void rva0028CDB6();Relationship getRelationship(const Object*)const;
 char pad00[4];ThingTemplateView*m_template;char pad08[0x258-8];AIUpdateInterface*m_ai;char pad25c[0x456-0x25c];bool m_recursing;
};
void Object::rva00295A84(Object*victim){
 AIUpdateInterface *ai=m_ai;
 if(victim){
  if(ai && !m_recursing && !rva00344EB2Gate(this,(Thing*)victim)){
   Object *related=rva0028ACA0();
   if(!ai->m_flag3c7 && related){
    bool same=(victim==related);
    if(victim->testStatus(STATUS_26)){
     related=related->rva002931F5(false);
     if(victim->rva002931F5(false)==related)same=true;
    }
    if(!testStatus(STATUS_26) || victim->m_template->isStructure()){
     if(!same)return;
    }
   }
   if(ai->slot113())return;
   const Weapon *weapon=getCurrentWeapon(0);if(!weapon)return;
   if(!weapon->m_field->get())return;
   if(rva0029493F(victim,2) && ((Rva0028CECFOwner*)this)->rva0028CECF())return;
   related=rva002931F5(false);
   if(testStatus(STATUS_26) && related && related->rva0029493F(victim,2) && ((Rva0028CECFOwner*)related)->rva0028CECF())return;
   if(ai->getMoodMatrixValue()&0x2000)return;
   if(!rva0028CC7C((int)victim))return;
   if(!ai->slot110() && !ai->slot111())return;
   if(testStatus(STATUS_45) || testStatus(STATUS_1C))return;
   if(victim->rva002943B2(getControllingPlayer()))return;
   if(rva0028F518())return;
   if(testStatus(STATUS_0F) && !testStatus(STATUS_11))return;
   ai->rva0026D3FB(victim);rva0028CDB6();ai->slot136();
   m_recursing=true;
   if(victim->getRelationship(this)==ENEMIES && !victim->m_template->isKind55())victim->rva00295A84(this);
   m_recursing=false;
  }
 }
}
