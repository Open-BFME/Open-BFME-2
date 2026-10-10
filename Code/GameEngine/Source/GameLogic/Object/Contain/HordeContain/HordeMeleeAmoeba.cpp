// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /GX- /ICode/Libraries/Include/Lib /ICode/GameEngine/Source/Common
// stlport
// Retail587FA4..5880B8:276B RET4; WB146D7D0 names startMeleeAttack.
// Existing587D9C constructor establishes held4 / vector8 / force14 / data18.
// Native and WB prove60B entry offsets and circular-list / AI slots individually.
// The swarm recovery supplied the matching STLport indexing pattern.
#include "Coord3D.h"
#include <vector>
class Object;
enum ObjectStatusTypes { AMOEBA_STATUS_1C=0x1c };
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
 void rva0028ACEE(const Coord3D *,int);
 void rva00295F05(bool); void rva0028CDB6();
 unsigned char pad0[4]; void *m_template;
 unsigned char pad8[0x38-8]; Coord3D m_position;
 unsigned char pad44[0x74-0x44]; int m_id;
 unsigned char pad78[0x250-0x78]; AmoebaContainer *m_container;
 unsigned char pad254[4]; AmoebaAI *m_ai;
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

struct AmoebaAttackEntry {
 Coord3D position;
 bool needsPosition; unsigned char pad0D[3];
 int timer; unsigned char pad14[0x34-0x14];
 int groupValue; bool arrived,active; unsigned char pad3A[2];
};
struct AmoebaData { unsigned char pad[0x64]; int groupValue; };
class HordeMeleeAmoeba {
public:
 virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void startMeleeAttack(Object *);
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
