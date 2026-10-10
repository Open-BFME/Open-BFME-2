// ?updateMeleeAttack@HordeMeleeFormation@@UAEXPAVObject@@@Z
// partial score=0.9694 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /GX- /ICode/Libraries/Include/Lib /ICode/GameEngine/Source/Common
// stlport
#include "Coord3D.h"
#include "GameLogicObjectLookupView.h"
#include <vector>
#include <deque>
class Object;
enum ObjectStatusTypes { FORMATION_STATUS_1C=0x1c, FORMATION_STATUS_44=0x44 };
enum WeaponSlotType { PRIMARY_WEAPON=0 };
enum CommandSourceType { FORMATION_COMMAND=2 };
class Weapon { public: bool isWithinAttackRange(const Object *,const Object *,float,int) const; };
template<int N> class FormationSlots : public FormationSlots<N-1> { public: virtual void gap(char (*)[N])=0; };
template<> class FormationSlots<0> {};
class FormationRangeQuery : public FormationSlots<18> { public: virtual Object *query(int,const Coord3D *,float,int,int)=0; };
class FormationContainer : public FormationSlots<31> { public: virtual FormationRangeQuery *rangeQuery()=0; };
class FormationAI : public FormationSlots<110> { public: virtual bool idleBlocked()=0; virtual bool specialState()=0;
 virtual void slot112()=0;
 virtual void slot113()=0;
 virtual void slot114()=0;
 virtual void slot115()=0;
 virtual void slot116()=0;
 virtual void slot117()=0;
 virtual void slot118()=0;
 virtual void slot119()=0;
 virtual void slot120()=0;
 virtual void slot121()=0;
 virtual void slot122()=0;
 virtual void slot123()=0;
 virtual void slot124()=0;
 virtual void slot125()=0;
 virtual void slot126()=0;
 virtual void slot127()=0;
 virtual void slot128()=0;
 virtual void slot129()=0;
 virtual void slot130()=0;
 virtual void slot131()=0;
 virtual void slot132()=0;
 virtual void slot133()=0;
 virtual void slot134()=0;
 virtual void slot135()=0;
 virtual void resetAttack()=0; };
class AICommandInterface { public: void rva0026C2D9(Object *,int,CommandSourceType); void aiIdle(CommandSourceType); };
class Object {
public:
 Object *rva002931F5(bool);
 bool testStatus(ObjectStatusTypes) const;
 const Weapon *getCurrentWeapon(WeaponSlotType *) const;
 int rva0028B511() const;
 void rva0028ACEE(const Coord3D *,int);
 void rva00295F05(bool);
 float rva002615E3(const Coord3D *) const;
 unsigned char pad0[4]; void *m_template;
 unsigned char pad8[0x38-8]; Coord3D m_position;
 unsigned char pad44[0x74-0x44]; int m_id;
 unsigned char pad78[0x250-0x78]; FormationContainer *m_container;
 unsigned char pad254[4]; FormationAI *m_ai;
 unsigned char pad25C[0x438-0x25c]; unsigned char flags;
};
struct FormationNode { FormationNode *next,*prev; Object *object; };
struct FormationList { FormationNode *head; };
struct FormationRange {
 void *owner; FormationList *list;
 unsigned int size() const { unsigned int n=0; for(FormationNode *p=list->head->next;p!=list->head;p=p->next) ++n; return n; }
};
class FormationListProvider : public FormationSlots<70> { public: virtual void fill(FormationRange *)=0; };
class FormationLeaderProvider : public FormationSlots<38> { public: virtual void setLeader(Object *)=0; };
struct FormationMember { unsigned char pad[0x18]; int follows; };
struct FormationHeld { unsigned char pad0[8]; Object *leader; unsigned char padC[0x120-0xc]; bool active;
 unsigned char pad121[0x188-0x121]; FormationMember *members; };
struct FormationData { void *unknown; bool follow; char pad5[3]; float firstDistance,nextDistance; };
struct BfmeE8 { int a,b; };
struct BfmeE12 { float x,y,z; };
struct Gen_t_00595870_p12cd { int a,b,c; };
namespace _STL {
 template<> void deque<BfmeE8>::clear();
 template<> BfmeE12 &deque<BfmeE12>::back();
 template<> void deque<BfmeE12>::pop_front();
 template<> void deque<Gen_t_00595870_p12cd>::push_back(const Gen_t_00595870_p12cd &);
 template<> void _Deque_iterator_base<BfmeE12>::_M_decrement();
 template<> int _Deque_iterator_base<BfmeE12>::_M_subtract(const _Deque_iterator_base<BfmeE12> &) const;
}
class Rva00585257Iter : public _STL::_Deque_iterator_base<BfmeE12> { public: void *rva00585257(); };

class Rva0046ACF6 { public: int rva0046ACF6(int); };
class Rva005D6FE5 { public: unsigned char rva005D6FE5(); };
class Pathfinder { public: int GetOverlapGoalUnits(Object *,const Coord3D *,int *); };
struct FormationAIManager { unsigned char pad[0x10]; Pathfinder *pathfinder; };
class AI; extern AI *TheAI;
extern GameLogic *TheGameLogic;
extern int g_Va00DBA4E4;
struct FormationAttackEntry { int state; Coord3D position,previousPosition; bool needsPosition; unsigned char pad1D[3];
 unsigned int nextFrame,lastFrame; _STL::deque<BfmeE12> path; ObjectID lastTarget; };
class HordeMeleeFormation {
public:
 virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void startMeleeAttack(Object *);
 virtual void slot4(); virtual void updateMeleeAttack(Object *);
 virtual void slot6();
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual bool rva00585017(int,Coord3D *);
 bool findMeleeAttackPosition(Object *,Coord3D *,Object *,const Coord3D *,bool,int *,bool);
 FormationHeld *held;
 _STL::vector<FormationAttackEntry> attacks;
 bool force; FormationData *data;
};

void HordeMeleeFormation::updateMeleeAttack(Object *victim)
{
 if(!victim) return;
 if(((Rva005D6FE5 *)this)->rva005D6FE5()) startMeleeAttack(victim);
 FormationRange range;
 ((FormationListProvider *)((char *)held+0x20))->fill(&range);
 FormationHeld *owner=held;
 Object *leader=owner->leader;
 if(!leader->testStatus(FORMATION_STATUS_44))
  ((FormationLeaderProvider *)((char *)owner+0x11c))->setLeader(leader);
 Object *container=victim->rva002931F5(false);
 if(container) victim=container;
 unsigned int now=TheGameLogic->getFrame();
 int count=range.size()>>1;
 int two=2;
 const int &maximum=(count<two)?two:count;
 count=maximum;
 FormationNode *node;
 for(node=range.list->head->next;node!=range.list->head;node=node->next) {
  Object *unit=node->object;
  int index=((Rva0046ACF6 *)held)->rva0046ACF6(unit->m_id);
  if(index>=0 && index<attacks.size()) attacks[index].previousPosition=unit->m_position;
 }
 for(node=range.list->head->next;node!=range.list->head;node=node->next) {
  Object *unit=node->object;
  if(!unit) continue;
  FormationAI *ai=unit->m_ai;
  if(ai && *(int *)((char *)ai+0x1fc)==4 && *(int *)((char *)ai+0x140)) continue;
  int index=((Rva0046ACF6 *)held)->rva0046ACF6(unit->m_id);
  if(index<0 || index>=attacks.size()) continue;
  FormationAttackEntry &entry=attacks[index];
  bool savePosition=false;
  if(entry.path.empty()) savePosition=true;
  else {
   const BfmeE12 &last=entry.path.back();
   Coord3D delta;
   float x=last.x,y=last.y,z=last.z;
   x-=unit->m_position.x; y-=unit->m_position.y; z-=unit->m_position.z;
   delta.x=x; delta.y=y; delta.z=z;
   if(delta.GetLengthEstimate2D()>=10.0f) savePosition=true;
  }
  if(savePosition) {
   if(entry.path.size()>10) entry.path.pop_front();
   ((_STL::deque<Gen_t_00595870_p12cd> *)&entry.path)->push_back(*(const Gen_t_00595870_p12cd *)&unit->m_position);
  }
  if(unit->testStatus(FORMATION_STATUS_1C) || ai->specialState()) {
   entry.needsPosition=true; entry.lastFrame=now;
   unit->rva0028ACEE(&unit->m_position,unit->rva0028B511());
   continue;
  }
  bool inRange=false;
  if(entry.state==3) inRange=((*(unsigned int *)((char *)victim->m_template+0x110)) & (1u<<29))!=0;
  if(*(unsigned char *)((char *)victim->m_template+0x108)&0x80) {
   int ids[16];
   Pathfinder *pathfinder=((FormationAIManager *)TheAI)->pathfinder;
   int overlap=pathfinder->GetOverlapGoalUnits(unit,&unit->m_position,ids);
   if(overlap==0 || overlap==2) inRange=true;
  }
  if(inRange && unit->getCurrentWeapon(0) && unit->getCurrentWeapon(0)->isWithinAttackRange(unit,victim,0.0f,1) && unit->m_ai) {
   ((AICommandInterface *)((char *)unit->m_ai+0x20))->rva0026C2D9(victim,0x7fffffff,FORMATION_COMMAND);
   unit->rva0028ACEE(&unit->m_position,unit->rva0028B511());
   continue;
  }
  int follows=held->members[index].follows;
  if(follows>=0) {
   if(!data->follow || (entry.state!=3 && entry.state!=0)) continue;
   float distance=held->members[follows].follows>=0?data->nextDistance:data->firstDistance;
   _STL::deque<BfmeE12>::reverse_iterator it=attacks[follows].path.rbegin();
   for(;it!=attacks[follows].path.rend();++it) {
    BfmeE12 *point=(BfmeE12 *)((Rva00585257Iter *)&it)->rva00585257();
    Coord3D delta;
    float x=point->x,y=point->y,z=point->z;
    x-=attacks[follows].previousPosition.x; y-=attacks[follows].previousPosition.y; z-=attacks[follows].previousPosition.z;
    delta.x=x; delta.y=y; delta.z=z;
    if(delta.GetLengthEstimate2D()>=distance) break;
   }
   if(it!=attacks[follows].path.rend()) {
    entry.position=*(Coord3D *)((Rva00585257Iter *)&it)->rva00585257();
    held->active=true; entry.state=1; entry.nextFrame=0;
    unit->rva0028ACEE(&entry.position,unit->rva0028B511());
   } else {entry.state=0; entry.nextFrame=now+g_Va00DBA4E4;}
   entry.needsPosition=false;
   continue;
  }
  if(entry.nextFrame>now && !force) continue;
  if(entry.state==1 || entry.state==2) { held->active=true; continue; }
  if(entry.state==3) { unit->rva00295F05(false); if(unit->testStatus(FORMATION_STATUS_1C)) continue; }
  if(entry.state==0 && count>0) entry.needsPosition=true;
  if(!entry.needsPosition && entry.state!=3) continue;
  entry.position=unit->m_position;
  Coord3D position;
  position.x=victim->m_position.x; position.y=victim->m_position.y; position.z=victim->m_position.z;
  Object *other=victim->rva002931F5(false);
  FormationContainer *attached;
  if(other && (attached=other->m_container)!=0 && attached->rangeQuery()) {
   Object *nearest=other->m_container->rangeQuery()->query(0,&entry.position,0.0f,0,0);
   if(nearest) {
    Object *last=TheGameLogic->findObjectByID(entry.lastTarget);
    if(last && !(last->flags&1)) {
     float oldDistance=last->rva002615E3(&unit->m_position);
     if(nearest->rva002615E3(&unit->m_position)+400.0f>oldDistance) nearest=last;
    }
    position=nearest->m_position;
   }
  }
  bool recent=entry.lastFrame+g_Va00DBA4E4>now;
  int frames=0;
  bool found=findMeleeAttackPosition(unit,&entry.position,victim,&position,recent,&frames,true);
  if(frames) entry.nextFrame=now+frames; else entry.nextFrame=0;
  if(found) { held->active=true; entry.state=1; --count; }
  else { if(entry.nextFrame) unit->rva00295F05(false); entry.state=0; entry.needsPosition=false; }
  unit->rva0028ACEE(&entry.position,unit->rva0028B511());
  entry.needsPosition=false;
  if(count<1) break;
 }
 force=false;
}
