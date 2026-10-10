// ?updateMeleeAttack@HordeMeleeAmoeba@@UAEXPAVObject@@@Z
// partial score=0.87 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /GX- /ICode/Libraries/Include/Lib /ICode/GameEngine/Source/Common
// stlport
// Retail587FA4..5880B8:276B RET4; WB146D7D0 names startMeleeAttack.
// Existing587D9C constructor establishes held4 / vector8 / force14 / data18.
// Native and WB prove60B entry offsets and circular-list / AI slots individually.
// The swarm recovery supplied the matching STLport indexing pattern.
#include "Coord3D.h"
#include "Coord2D.h"
#include <math.h>
#include <vector>
class Object;
enum ObjectStatusTypes { AMOEBA_STATUS_1C=0x1c, AMOEBA_STATUS_45=0x45 };
enum WeaponSlotType { PRIMARY_WEAPON=0 };
enum CommandSourceType { AMOEBA_COMMAND=2 };
class Weapon { public: bool isWithinAttackRange(const Object *,const Object *,float,int) const; };
template<int N> class AmoebaSlots : public AmoebaSlots<N-1> { public: virtual void gap(char (*)[N])=0; };
template<> class AmoebaSlots<0> {};
class AmoebaRangeQuery : public AmoebaSlots<18> { public: virtual Object *query(int,const Coord3D *,float,int,int)=0; };
class AmoebaContainer : public AmoebaSlots<31> { public: virtual AmoebaRangeQuery *rangeQuery()=0; };
class AmoebaAI : public AmoebaSlots<110> { public: virtual bool idleBlocked()=0; virtual bool specialState()=0;
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
 void rva0028ACEE(const Coord3D *,int);
 void rva00295F05(bool); void rva0028CDB6();
 unsigned char pad0[4]; void *m_template;
 unsigned char pad8[0x38-8]; Coord3D m_position;
 unsigned char pad44[0x74-0x44]; int m_id;
 unsigned char pad78[0xB8-0x78]; float radius;
 unsigned char padBC[0x250-0xBC]; AmoebaContainer *m_container;
 unsigned char pad254[4]; AmoebaAI *m_ai;
 void *aux; unsigned char pad260[0x438-0x260]; unsigned char flags;
};
struct AmoebaNode { AmoebaNode *next,*prev; Object *object; };
struct AmoebaList { AmoebaNode *head; };
struct AmoebaRange {
 void *owner; AmoebaList *list;
 unsigned int size() const { unsigned int n=0; for(AmoebaNode *p=list->head->next;p!=list->head;p=p->next) ++n; return n; }
};
class AmoebaListProvider : public AmoebaSlots<70> { public: virtual void fill(AmoebaRange *)=0; };
struct AmoebaHeld { unsigned char pad[0x120]; bool active; };
class Rva0046ACF6 { public: int rva0046ACF6(int); };

struct ICoord2DBase { int x,y; };
struct ICoord2D : public ICoord2DBase {};
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

// Native5872CF..587305 complete54B RET4. Amoeba update5889D7 and
// WB14718F0 prove this entry view and the four-cell FIFO at14 / count10.
// Original helper and entry type names remain unknown.
void AmoebaAttackEntry::rva005872CF(const ICoord2DBase &cell)
{
 if(timer==4) {
  for(int i=1;i<4;++i) cells[i-1]=cells[i];
 } else ++timer;
 static_cast<ICoord2DBase &>(cells[timer-1])=cell;
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
static __forceinline void amoebaNormalize(Coord2D &v)
{
 float length=(float)sqrt(v.x*v.x+v.y*v.y);
 float inverse=1.0f/length;
 v.x*=inverse; v.y*=inverse;
}
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
 int count=0;
 for(AmoebaNode *node=range.list->head->next;node!=range.list->head;node=node->next) {
  Object *unit=node->object;
  if(!unit || (unit->flags&1)) continue;
  if(unit->aux && *(unsigned char *)((char *)unit->aux+0x5c)) continue;
  AmoebaAI *ai=unit->m_ai;
  if(!ai) continue;
  int index=((Rva0046ACF6 *)held)->rva0046ACF6(unit->m_id);
  if(index<0 || index>=attacks.size()) continue;
  AmoebaAttackEntry &entry=attacks[index];
  if(*(int *)((char *)ai+0x1fc)==4 && *(int *)((char *)ai+0x140)) { entry.timer=0; entry.needsPosition=true; continue; }
  if(unit->testStatus(AMOEBA_STATUS_1C) || unit->testStatus(AMOEBA_STATUS_45)) continue;
  if(!ai->idleBlocked()) {
   ((AICommandInterface *)((char *)ai+0x20))->aiIdle(AMOEBA_COMMAND);
   entry.position=unit->m_position; entry.timer=0; entry.active=true; entry.needsPosition=true;
  }
  ordered[count].m_04=index;
  ordered[count].m_key=unit->rva002C97E8(&unit->m_position,&victim->m_position);
  ordered[count].m_08=(unsigned int)unit;
  ++count;
 }
 _STL::sort(ordered,ordered+count);
 bool forcePosition=force;
 force=false;
 for(int n=0;n<count;++n) {
  AmoebaAttackEntry &entry=attacks[ordered[n].m_04];
  Object *unit=(Object *)ordered[n].m_08;
  Object *attack=Rva0058723D(unit,victim);
  if(attack) {
   if(entry.arrived) { entry.arrived=false; entry.groupValue=data->groupValue; ((Rva001E42F2 *)unit)->rva001E42F2(data->mask); }
   unit->rva0028CDB6(); entry.timer=0; entry.needsPosition=true; AttackUnit(unit,attack); continue;
  }
  if(forcePosition) {
   unit->rva0028CDB6(); entry.needsPosition=true;
   if(entry.arrived) { entry.arrived=false; entry.groupValue=data->groupValue; ((Rva001E42F2 *)unit)->rva001E42F2(data->mask); }
  }
  ICoord2D current;
  Rva002EBC14Cell(&current,unit,&unit->m_position);
  float bestScore=0.0f;
  bool outside=false;
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
   bool valid[3][3];
   Coord3D best;
   ICoord2D bestCell;
   for(int i=-1;i<=1;++i) {
    for(int j=-1;j<=1;++j) {
     if(i==0 && j==0) continue;
     Coord3D candidate=unit->m_position;
     candidate.x+=(float)(i*10); candidate.y+=(float)(j*10);
     Pathfinder *pathfinder=((AmoebaAIManager *)TheAI)->pathfinder;
     if(!pathfinder->rva002F07F5(unit,&candidate)) { valid[i+1][j+1]=false; continue; }
     ICoord2D cell; cell.x=current.x+i; cell.y=current.y+j;
     if(((Rva0058729D *)&entry)->rva0058729D(cell)) { valid[i+1][j+1]=false; continue; }
     valid[i+1][j+1]=true;
     float score=10000.0f-fabs(unit->GetRelativeAngle(&candidate))*data->angleWeight*0.31836995f;
     Object *other=victim;
     if((*(unsigned char *)((char *)victim->m_template+0x115))&0x20) {
      AmoebaRangeQuery *query=(AmoebaRangeQuery *)victim->rva0028C197();
      if(query) other=query->query(0,&candidate,0.0f,0,0); else other=0;
     }
     if(other) {
      Coord2D toward;
      toward.x=unit->m_position.x-other->m_position.x; toward.y=unit->m_position.y-other->m_position.y;
      amoebaNormalize(toward);
      Coord2D displacement;
      displacement.x=unit->m_position.x-candidate.x; displacement.y=unit->m_position.y-candidate.y;
      Coord2D perpendicular;
      perpendicular.x=displacement.y; perpendicular.y=-displacement.x;
      amoebaNormalize(perpendicular);
      perpendicular.x*=other->radius; perpendicular.y*=other->radius;
      Coord2D left;
      left.x=displacement.x+perpendicular.x; left.y=displacement.y+perpendicular.y;
      amoebaNormalize(left);
      displacement.x-=perpendicular.x; displacement.y-=perpendicular.y;
      amoebaNormalize(displacement);
      if(left.x*toward.x+left.y*toward.y<data->alignment && displacement.x*toward.x+displacement.y*toward.y<data->alignment) continue;
     }
     Object *destination=other?other:victim;
     score-=sqrt(unit->rva002636F6(&candidate,destination,&destination->m_position));
     Coord2D group;
     group.x=amoebaLeader(held)->m_position.x-candidate.x;
     group.y=amoebaLeader(held)->m_position.y-candidate.y;
     float distance=group.x*group.x+group.y*group.y;
     float maximum=other && (*(unsigned char *)((char *)other->m_template+0x108)&0x80)?data->maxBuildingDistance:data->maxDistance;
     if(distance>maximum*maximum) { outside=true; continue; }
     if(distance>data->preferredDistance*data->preferredDistance) score-=sqrt(distance);
     if(score>bestScore) { best=candidate; bestCell=cell; bestScore=score; }
    }
   }
   if(bestScore<1.0f && outside) {
    for(int i=-1;i<=1;++i) {
     for(int j=-1;j<=1;++j) {
      if(i==0 && j==0) continue;
      if(!valid[i+1][j+1]) continue;
      Coord3D candidate=unit->m_position;
      candidate.x+=(float)(i*10); candidate.y+=(float)(j*10);
      Coord2D group;
      group.x=amoebaLeader(held)->m_position.x-candidate.x;
      group.y=amoebaLeader(held)->m_position.y-candidate.y;
      float score=1000000.0f-(group.x*group.x+group.y*group.y);
      if(score>bestScore) { best=candidate; bestCell.x=current.x+i; bestCell.y=current.y+j; bestScore=score; }
     }
    }
   }
   if(bestScore>0.0f) {
    entry.needsPosition=false; entry.position=best; entry.active=true;
    entry.rva005872CF(bestCell);
    unit->rva0028ACEE(&best,amoebaLeader(held)->rva0028B511());
    continue;
   }
  }
  attack=Rva0058723D(unit,0);
  if(attack) {
   if(entry.arrived) { entry.arrived=false; entry.groupValue=data->groupValue; ((Rva001E42F2 *)unit)->rva001E42F2(data->mask); }
   unit->rva0028CDB6(); entry.timer=0; entry.needsPosition=true; AttackUnit(unit,attack);
  } else entry.rva005872CF(current);
 }
}
