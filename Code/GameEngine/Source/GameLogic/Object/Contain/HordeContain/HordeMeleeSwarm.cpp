// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /GX- /ICode/Libraries/Include/Lib /ICode/GameEngine/Source/Common
// stlport
// Retail 0x00584644..0x005849EF, 939 bytes, thiscall RET 4.
// WorldBuilder 0x0147A360 names HordeMeleeSwarm::updateMeleeAttack; native
// constructor table 0x0086FC80 confirms virtual slot 5. Entry layout follows
// the existing 0x00584A9B transfer and 0x005843DA constructor evidence.
// The position-search sibling at 0x00583D54 has a proven call ABI but remains
// unrecovered. Interface storage views below describe observed retail slots.
#include "Coord3D.h"
#include "GameLogicObjectLookupView.h"
#include <vector>
class Object;
enum ObjectStatusTypes { SWARM_STATUS_1C=0x1c };
enum WeaponSlotType { PRIMARY_WEAPON=0 };
enum CommandSourceType { SWARM_COMMAND=2 };
class Weapon { public: bool isWithinAttackRange(const Object *,const Object *,float,int) const; };
template<int N> class SwarmSlots : public SwarmSlots<N-1> { public: virtual void gap(char (*)[N])=0; };
template<> class SwarmSlots<0> {};
class SwarmRangeQuery : public SwarmSlots<18> { public: virtual Object *query(int,const Coord3D *,float,int,int)=0; };
class SwarmContainer : public SwarmSlots<31> { public: virtual SwarmRangeQuery *rangeQuery()=0; };
class SwarmAI : public SwarmSlots<110> { public: virtual bool idleBlocked()=0; virtual bool specialState()=0;
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
 unsigned char pad0[4]; void *m_template;
 unsigned char pad8[0x38-8]; Coord3D m_position;
 unsigned char pad44[0x74-0x44]; int m_id;
 unsigned char pad78[0x250-0x78]; SwarmContainer *m_container;
 unsigned char pad254[4]; SwarmAI *m_ai;
};
struct SwarmNode { SwarmNode *next,*prev; Object *object; };
struct SwarmList { SwarmNode *head; };
struct SwarmRange {
 void *owner; SwarmList *list;
 unsigned int size() const { unsigned int n=0; for(SwarmNode *p=list->head->next;p!=list->head;p=p->next) ++n; return n; }
};
class SwarmListProvider : public SwarmSlots<70> { public: virtual void fill(SwarmRange *)=0; };
struct SwarmHeld { unsigned char pad[0x120]; bool active; };
class Rva0046ACF6 { public: int rva0046ACF6(int); };
class Rva005D6FE5 { public: unsigned char rva005D6FE5(); };
class Pathfinder { public: int GetOverlapGoalUnits(Object *,const Coord3D *,int *); };
struct SwarmAIManager { unsigned char pad[0x10]; Pathfinder *pathfinder; };
class AI; extern AI *TheAI;
extern GameLogic *TheGameLogic;
extern int g_Va00DBA4E4;
struct SwarmAttackEntry { int state; Coord3D position; bool needsPosition; unsigned char pad11[3]; unsigned int nextFrame,lastFrame; };
class HordeMeleeSwarm {
public:
 virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void startMeleeAttack(Object *);
 virtual void slot4(); virtual void updateMeleeAttack(Object *);
 bool findMeleeAttackPosition(Object *,Coord3D *,Object *,const Coord3D *,bool,int *,bool);
 SwarmHeld *held;
 _STL::vector<SwarmAttackEntry> attacks;
 bool force;
};
void HordeMeleeSwarm::updateMeleeAttack(Object *victim)
{
 if(!victim) return;
 if(((Rva005D6FE5 *)this)->rva005D6FE5()) startMeleeAttack(victim);
 SwarmRange range;
 ((SwarmListProvider *)((char *)held+0x20))->fill(&range);
 Object *container=victim->rva002931F5(false);
 if(container) victim=container;
 unsigned int now=TheGameLogic->getFrame();
 int count=range.size()>>1;
 int two=2;
 const int &maximum=(count<two)?two:count;
 count=maximum;
 for(SwarmNode *node=range.list->head->next;node!=range.list->head;node=node->next) {
  Object *unit=node->object;
  if(!unit) continue;
  SwarmAI *ai=unit->m_ai;
  if(ai && *(int *)((char *)ai+0x1fc)==4 && *(int *)((char *)ai+0x140)) continue;
  int index=((Rva0046ACF6 *)held)->rva0046ACF6(unit->m_id);
  if(index<0 || index>=attacks.size()) continue;
  SwarmAttackEntry &entry=attacks[index];
  if(unit->testStatus(SWARM_STATUS_1C) || ai->specialState()) {
   entry.needsPosition=true;
   entry.lastFrame=now;
   unit->rva0028ACEE(&unit->m_position,unit->rva0028B511());
   continue;
  }
  bool inRange=false;
  if(entry.state==3) inRange=((*(unsigned int *)((char *)victim->m_template+0x110)) & (1u<<29))!=0;
  if(*(unsigned char *)((char *)victim->m_template+0x108)&0x80) {
   int ids[16];
   Pathfinder *pathfinder=((SwarmAIManager *)TheAI)->pathfinder;
   int overlap=pathfinder->GetOverlapGoalUnits(unit,&unit->m_position,ids);
   if(overlap==0 || overlap==2) inRange=true;
  }
  if(inRange && unit->getCurrentWeapon(0) && unit->getCurrentWeapon(0)->isWithinAttackRange(unit,victim,0.0f,1) && unit->m_ai) {
   ((AICommandInterface *)((char *)unit->m_ai+0x20))->rva0026C2D9(victim,0x7fffffff,SWARM_COMMAND);
   unit->rva0028ACEE(&unit->m_position,unit->rva0028B511());
   continue;
  }
  if(entry.nextFrame>now && !force) continue;
  if(entry.state==1 || entry.state==2) { held->active=true; continue; }
  if(entry.state==3) { unit->rva00295F05(false); if(unit->testStatus(SWARM_STATUS_1C)) continue; }
  if(entry.state==0 && count>0) entry.needsPosition=true;
  if(!entry.needsPosition && entry.state!=3) continue;
  entry.position=unit->m_position;
  Coord3D position;
  position.x=victim->m_position.x; position.y=victim->m_position.y; position.z=victim->m_position.z;
  Object *other=victim->rva002931F5(false);
  SwarmContainer *attached;
  if(other && (attached=other->m_container)!=0 && attached->rangeQuery()) {
   Object *nearest=other->m_container->rangeQuery()->query(0,&entry.position,0.0f,0,0);
   if(nearest) position=nearest->m_position;
  }
  bool recent=entry.lastFrame+g_Va00DBA4E4>now;
  int frames=0;
  bool overlap=entry.nextFrame>0 && (*(unsigned char *)((char *)victim->m_template+0x108)&0x80)!=0;
  bool found=findMeleeAttackPosition(unit,&entry.position,victim,&position,recent,&frames,overlap);
  if(frames) entry.nextFrame=now+frames; else entry.nextFrame=0;
  if(found) { held->active=true; entry.state=1; --count; }
  else { if(entry.nextFrame) unit->rva00295F05(false); entry.state=0; entry.needsPosition=false; }
  unit->rva0028ACEE(&entry.position,unit->rva0028B511());
  entry.needsPosition=false;
  attacks[index]=entry;
  if(count<1) break;
 }
 force=false;
}

// Native58453D..584644 is263B RET4 and slot3 of the constructor table.
// The exact update calls this slot on its read-and-clear restart flag.
// WB1479FC0 independently confirms the full traversal and idle/reset calls.
void HordeMeleeSwarm::startMeleeAttack(Object *victim)
{
 held->active=true;
 SwarmRange range;
 ((SwarmListProvider *)((char *)held+0x20))->fill(&range);
 for(SwarmNode *node=range.list->head->next;node!=range.list->head;node=node->next) {
  Object *unit=node->object;
  if(!unit) continue;
  SwarmAI *ai=unit->m_ai;
  if(ai && *(int *)((char *)ai+0x1fc)==4 && *(int *)((char *)ai+0x140)) continue;
  if(!unit->testStatus(SWARM_STATUS_1C) && ai && !ai->idleBlocked())
   ((AICommandInterface *)((char *)ai+0x20))->aiIdle(SWARM_COMMAND);
  int index=((Rva0046ACF6 *)held)->rva0046ACF6(unit->m_id);
  if(index<0 || index>=attacks.size()) continue;
  SwarmAttackEntry &entry=attacks[index];
  entry.position=unit->m_position;
  entry.needsPosition=true;
  unit->rva0028ACEE(&unit->m_position,unit->rva0028B511());
  unit->m_ai->resetAttack();
 }
}
