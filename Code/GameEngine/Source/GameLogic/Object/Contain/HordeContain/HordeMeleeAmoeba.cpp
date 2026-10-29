// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /GX- /ICode/Libraries/Include/Lib /ICode/GameEngine/Source/Common
// stlport
// Retail587FA4..5880B8:276B RET4; WB146D7D0 names startMeleeAttack.
// Existing587D9C constructor establishes held4 / vector8 / force14 / data18.
// Native and WB prove60B entry offsets and circular-list / AI slots individually.
// The swarm recovery supplied the matching STLport indexing pattern.
#include "Coord3DCtorView.h"
#include "Coord2D.h"
#include <math.h>
#include <vector>
class AmoebaCoord2D : public Coord2D {
public:
 __forceinline float GetLength() const {
  float x_value=x, y_value=y;
  return (float)sqrt(x_value*x_value+y_value*y_value);
 }
 __forceinline float Normalize() {
  float length=GetLength();
  float inverse=1.0f/length;
  x*=inverse; y*=inverse;
  return length;
 }
 AmoebaCoord2D &operator-=(const AmoebaCoord2D &v) { x-=v.x; y-=v.y; return *this; }
 AmoebaCoord2D &operator+=(const AmoebaCoord2D &v) { x+=v.x; y+=v.y; return *this; }
 AmoebaCoord2D &operator*=(float f) { x*=f; y*=f; return *this; }
};
class Object;
enum ObjectStatusTypes { AMOEBA_STATUS_1C=0x1c, AMOEBA_STATUS_45=0x45 };
enum WeaponSlotType { PRIMARY_WEAPON=0 };
enum CommandSourceType { AMOEBA_COMMAND=2 };
#include "../../../../../Include/GameLogic/Weapon.h"
template<int N> class AmoebaSlots : public AmoebaSlots<N-1> { public: virtual void gap(char (*)[N])=0; };
template<> class AmoebaSlots<0> {};
class AmoebaRangeQuery : public AmoebaSlots<18> { public: virtual Object *query(int,const Coord3D *,float,int,int)=0; };
class AmoebaContainer : public AmoebaSlots<31> { public: virtual AmoebaRangeQuery *rangeQuery()=0; };
class AmoebaAI : public AmoebaSlots<110> { public: virtual bool idleBlocked()=0; virtual void gap111()=0; bool specialState() const { return *(const unsigned char *)((const char *)this + 0x5c) != 0; }
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
 float rva002C97E8(const Coord3D *,const Coord3D *) const;
 float GetRelativeAngle(const Coord3D *) const;
 float rva002636F6(const Coord3D *,const void *,const Coord3D *) const;
 void *rva0028C197() const;
 void rva0028ACEE(int,int);
 void rva00295F05(bool); void rva0028CDB6(); void rva001E42F2(const int *);
 unsigned char pad0[4]; void *m_template;
 unsigned char pad8[0x38-8]; Coord3D m_position;
 unsigned char pad44[0x74-0x44]; int m_id;
 const Coord3D *getPosition() const { return &m_position; }
 unsigned char pad78[0xB8-0x78]; float radius;
 unsigned char padBC[0x250-0xBC]; AmoebaContainer *m_container;
 unsigned char pad254[4]; AmoebaAI *m_ai; AmoebaAI *m_specialAI;
 unsigned char pad260[0x438 - 0x260]; unsigned char m_status;
};
struct AmoebaNode { AmoebaNode *next,*prev; Object *object; };
struct AmoebaList { AmoebaNode *head; };
struct AmoebaRange {
 void *owner; AmoebaList *list;
 unsigned int size() const { unsigned int n=0; for(AmoebaNode *amoebaNode=list->head->next;amoebaNode!=list->head;amoebaNode=amoebaNode->next) ++n; return n; }
};
class AmoebaListProvider : public AmoebaSlots<70> { public: virtual void fill(AmoebaRange *)=0; };
struct AmoebaHeld { unsigned char pad[0x120]; bool active; };
class Rva0046ACF6 { public: int rva0046ACF6(int); };

#include "../../../../../../Libraries/Include/Lib/ICoord2D.h"
// Keep the shared view conversion inline without a competing external copy.
struct ICoord2DBase;
__declspec(dllimport) __forceinline ICoord2DBase &asBase(ICoord2D &);
#include "../../../../../../Libraries/Include/Lib/ICoord2DBase.h"
struct AmoebaAttackEntry {
 void rva005872CF(const ICoord2DBase &);
 Coord3D position;
 bool needsPosition; unsigned char pad0D[3];
 int timer; ICoord2D cells[4];
 int groupValue; bool arrived,active; unsigned char pad3A[2];
};
struct AmoebaData { int unused; float angleWeight,alignment,preferredDistance,maxDistance,maxBuildingDistance; int mask[19]; int groupValue,minRest,maxRest; };
class HordeMeleeAmoeba {
public:
 virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void startMeleeAttack(Object *);
 virtual void slot4(); virtual void updateMeleeAttack(Object *);
 void AttackUnit(Object *,Object *);
 virtual void notifyOfMemberDeath(Object *);
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual bool rva0058776E(int,Coord3D *);
 AmoebaHeld *held;
 _STL::vector<AmoebaAttackEntry> attacks;
 bool force; AmoebaData *data;
};
void HordeMeleeAmoeba::startMeleeAttack(Object *victim)
{
 held->active=true;
 force=true;
 AmoebaRange range;
 ((AmoebaListProvider *)((char *)held+0x20))->fill(&range);
 for(AmoebaNode *node=range.list->head->next;node!=range.list->head;node=node->next) {
  Object *unit=node->object;
  if(!unit) continue;
  AmoebaAI *ai=unit->m_ai;
  if(!ai) continue;
  int index=((Rva0046ACF6 *)held)->rva0046ACF6(unit->m_id);
  if(index<0 || index>=attacks.size()) continue;
  AmoebaAttackEntry &entry=attacks[index];
  entry.position=unit->m_position;
  entry.active=true;
  entry.needsPosition=true;
  entry.groupValue=data->groupValue;
  entry.arrived=false;
  entry.timer=0;
  if(*(int *)((char *)ai+0x1fc)==4 && *(int *)((char *)ai+0x140)) continue;
  if(!unit->testStatus(AMOEBA_STATUS_1C) && !ai->idleBlocked())
   ((AICommandInterface *)((char *)ai+0x20))->aiIdle(AMOEBA_COMMAND);
  unit->rva0028CDB6();
  ai->resetAttack();
 }
}
void HordeMeleeAmoeba::notifyOfMemberDeath(Object *deadUnit)
{
 AmoebaRange range;
 ((AmoebaListProvider *)((char *)held+0x20))->fill(&range);
 AmoebaNode *head = range.list->head;
 AmoebaNode *cur = head->next;
 if (cur == head)
  return;
 do
 {
  Object *obj = cur->object;
  if (obj && !(obj->m_status & 1))
  {
   if (!obj->m_specialAI || !obj->m_specialAI->specialState())
   {
    if (obj->m_ai)
    {
     int offsetIndex = ((Rva0046ACF6 *)held)->rva0046ACF6(obj->m_id);
     if (offsetIndex >= 0 && (unsigned int)offsetIndex < attacks.size())
     {
      AmoebaAttackEntry &entry = attacks[offsetIndex];
      if (entry.arrived)
      {
       entry.arrived = false;
       entry.groupValue = data->groupValue;
       obj->rva001E42F2(data->mask);
      }
     }
    }
   }
  }
  cur = cur->next;
 } while (cur != range.list->head);
}

// Native5872CF..587305 complete54B RET4. Amoeba update5889D7 and
// WB14718F0 prove this entry view and the four-cell FIFO at14 / count10.
// Original helper and entry type names remain unknown.
void AmoebaAttackEntry::rva005872CF(const ICoord2DBase &cell)
{
 if(timer==4) {
  for(int i=1;i<4;++i) cells[i-1]=cells[i];
 } else ++timer;
 *reinterpret_cast<ICoord2DBase *>(&cells[timer-1])=cell;
}

// Native58776E..5877AF:65B RET8. Existing constructor table86FF38
// slot13 and WB1470EA0 prove the index / Coord3D output ABI. Original
// method name remains unknown; active39 controls whether a position exists.
bool HordeMeleeAmoeba::rva0058776E(int index,Coord3D *result)
{
 if(index>=0 && index<attacks.size() && attacks[index].active) {
  *result=attacks[index].position;
  return true;
 }
 return false;
}

struct Rva00588195Elem { float m_key; unsigned int m_04,m_08; };
namespace _STL { template<class Iterator> void sort(Iterator,Iterator); }
class Pathfinder { public: bool rva002F07F5(Object *,const Coord3D *); };
struct AmoebaAIManager { unsigned char pad[0x10]; Pathfinder *pathfinder; };
class AI; extern AI *TheAI;
class Rva001E42F2 { public: void rva001E42F2(const int *); };
class Rva001E431E { public: void rva001E431E(const int *); };
class Rva0058729D { public: bool rva0058729D(const ICoord2DBase &); };
class AmoebaPositionProvider : public AmoebaSlots<38> { public: virtual void setLeader(Object *)=0; };
ICoord2D *Rva002EBC14Cell(ICoord2D *,void *,const Coord3D *);
Object *Rva0058723D(Object *,Object *);
int GetGameLogicRandomValue(int,int,char *,int);

static __forceinline Object *amoebaLeader(AmoebaHeld *held) { return *(Object **)((char *)held+8); }
void HordeMeleeAmoeba::updateMeleeAttack(Object *victim)
{
 if(!victim) return;
 Object *parent=victim->rva002931F5(false);
 if(parent) victim=parent;
 ((AmoebaPositionProvider *)((char *)held+0x11c))->setLeader(amoebaLeader(held));
 AmoebaRange range;
 ((AmoebaListProvider *)((char *)held+0x20))->fill(&range);
 Rva00588195Elem ordered[50];
 AmoebaNode *next;
 int count=0;
 for(AmoebaNode *node=range.list->head->next;node!=range.list->head;) {
  {
  Object *unit=node->object;
  if(!unit || (unit->m_status&1)) goto advanceNode;
  if(unit->m_specialAI && *(unsigned char *)((char *)unit->m_specialAI+0x5c)) goto advanceNode;
  AmoebaAI *ai=unit->m_ai;
  if(!ai) goto advanceNode;
  int index=((Rva0046ACF6 *)held)->rva0046ACF6(unit->m_id);
  if(index<0 || index>=attacks.size()) goto completeBody;
  AmoebaAttackEntry &entry=attacks[index];
  if(*(int *)((char *)ai+0x1fc)==4 && *(int *)((char *)ai+0x140)) { entry.needsPosition=true; entry.timer=0; goto completeBody; }
  if(unit->testStatus(AMOEBA_STATUS_1C) || unit->testStatus(AMOEBA_STATUS_45)) goto advanceNode;
  if(!ai->idleBlocked()) {
   ((AICommandInterface *)((char *)ai+0x20))->aiIdle(AMOEBA_COMMAND);
   entry.position=unit->m_position; entry.timer=0; entry.active=true; entry.needsPosition=true;
  }
  ordered[count].m_04=index;
  ordered[count].m_key=unit->rva002C97E8(&unit->m_position,&victim->m_position);
  ordered[count].m_08=(unsigned int)unit;
  ++count;
  }
// Keep the two completion edges: their shared cursor copy produces the
// retail spill and frame slots before MSVC merges the identical tails.
completeBody:
 if(force) {
advanceNode:
 next=node;
 } else { next=node; }
 node=next->next;
 }
 _STL::sort(ordered,ordered+count);
 bool forcePosition=force;
 force=false;
 for(int n=0;n<count;++n) {
  Object *unit=(Object *)ordered[n].m_08;
  AmoebaAttackEntry &entry=attacks[ordered[n].m_04];
  Object *attack=Rva0058723D(unit,victim);
  if(attack) {
   if(entry.arrived) { entry.arrived=false; entry.groupValue=data->groupValue; ((Rva001E42F2 *)unit)->rva001E42F2(data->mask); }
   unit->rva0028CDB6(); entry.needsPosition=true; entry.timer=0; AttackUnit(unit,attack); continue;
  }
  if(forcePosition) {
   unit->rva0028CDB6(); entry.needsPosition=true;
   if(entry.arrived) { entry.arrived=false; entry.groupValue=data->groupValue; ((Rva001E42F2 *)unit)->rva001E42F2(data->mask); }
  }
  ICoord2D bestCell;
  ICoord2D current;
  Rva002EBC14Cell(&current,unit,&unit->m_position);
  float bestScore=0.0f;
  Coord3D best;
  bool outside=false;
  bool valid[3][3];
  if(!entry.arrived) {
   if(!entry.groupValue) {
    entry.arrived=true;
    entry.groupValue=GetGameLogicRandomValue(data->minRest,data->maxRest,(char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\HordeMeleeAmoeba.cpp",0x123);
    ((Rva001E431E *)unit)->rva001E431E(data->mask);
   } else --entry.groupValue;
  }
  if(entry.arrived) {
   if(!entry.groupValue) {
    entry.arrived=false; entry.groupValue=data->groupValue;
    ((Rva001E42F2 *)unit)->rva001E42F2(data->mask);
   } else --entry.groupValue;
  }
  if(!entry.arrived) {
   for(int i=-1;i<=1;++i) {
    for(int j=-1;j<=1;++j) {
     if(i==0 && j==0) continue;
     Coord3D candidate=unit->m_position;
     candidate.x+=(float)(i*10); candidate.y+=(float)(j*10);
     Pathfinder *pathfinder=((AmoebaAIManager *)TheAI)->pathfinder;
     if(!pathfinder->rva002F07F5(unit,&candidate)) { valid[i+1][j+1]=false; continue; }
     ICoord2D cell=current; cell.x+=i; cell.y+=j;
     if(((Rva0058729D *)&entry)->rva0058729D(reinterpret_cast<const ICoord2DBase &>(cell))) { valid[i+1][j+1]=false; continue; }
     valid[i+1][j+1]=true;
     float score=10000.0f-fabs(unit->GetRelativeAngle(&candidate))*data->angleWeight*0.31836995f;
     Object *other;
     if((*(unsigned char *)((char *)victim->m_template+0x115))&0x20) {
      AmoebaRangeQuery *query=(AmoebaRangeQuery *)victim->rva0028C197();
      if(!query) other=0; else other=query->query(0,&candidate,0.0f,0,0);
     } else other=victim;
     if(other) {
      AmoebaCoord2D toward;
      toward.x=unit->m_position.x-other->m_position.x; toward.y=unit->m_position.y-other->m_position.y;
      toward.Normalize();
      AmoebaCoord2D perpendicular,left,right;
      left.x=right.x=unit->m_position.x-candidate.x;
      left.y=right.y=unit->m_position.y-candidate.y;
      perpendicular.x=left.y; perpendicular.y=-left.x;
      perpendicular.Normalize();
      float radius=other->radius; perpendicular.x*=radius; perpendicular.y*=radius;
      left+=perpendicular;
      left.Normalize();
      right-=perpendicular;
      right.Normalize();
      if(toward.x*left.x+toward.y*left.y<data->alignment && toward.x*right.x+toward.y*right.y<data->alignment) continue;
     }
     Object *destination=other?other:victim;
     score-=sqrt(unit->rva002636F6(&candidate,destination,&destination->m_position));
     AmoebaCoord2D group;
     const Coord3D *leaderPos=amoebaLeader(held)->getPosition();
     group.x=leaderPos->x-candidate.x;
     group.y=leaderPos->y-candidate.y;
     float distance=group.x*group.x+group.y*group.y;
     float maximum=other && (*(unsigned char *)((char *)other->m_template+0x108)&0x80)?data->maxBuildingDistance:data->maxDistance;
     if(distance>maximum*maximum) { outside=true; continue; }
     if(distance>data->preferredDistance*data->preferredDistance) score-=sqrt(distance);
     if(score>bestScore) { bestScore=score; best=candidate; bestCell=cell; }
    }
   }
  }
   if(bestScore<1.0f && outside) {
    for(int i=-1;i<=1;++i) {
     for(int j=-1;j<=1;++j) {
      if(i==0 && j==0) continue;
      if(!valid[i+1][j+1]) continue;
      Coord3D candidate=unit->m_position;
      candidate.x+=(float)(i*10); candidate.y+=(float)(j*10);
      AmoebaCoord2D group;
      const Coord3D *leaderPos=amoebaLeader(held)->getPosition();
      group.x=leaderPos->x-candidate.x;
      group.y=leaderPos->y-candidate.y;
      float score=1000000.0f-(group.x*group.x+group.y*group.y);
      if(score>bestScore) { bestScore=score; best=candidate; bestCell.x=current.x+i; bestCell.y=current.y+j; }
     }
    }
   }
   if(bestScore>0.0f) {
    entry.needsPosition=false; entry.position=best; entry.active=true;
    entry.rva005872CF(reinterpret_cast<const ICoord2DBase &>(bestCell));
    unit->rva0028ACEE((int)&best,amoebaLeader(held)->rva0028B511());
    continue;
   }
  Object *fallback=Rva0058723D(unit,0);
  if(fallback) {
   if(entry.arrived) { entry.arrived=false; entry.groupValue=data->groupValue; ((Rva001E42F2 *)unit)->rva001E42F2(data->mask); }
   unit->rva0028CDB6(); entry.needsPosition=true; entry.timer=0; AttackUnit(unit,fallback);
  } else entry.rva005872CF(reinterpret_cast<const ICoord2DBase &>(current));
 }
}
