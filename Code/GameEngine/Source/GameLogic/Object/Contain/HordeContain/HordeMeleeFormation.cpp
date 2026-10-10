// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /GX- /ICode/Libraries/Include/Lib /ICode/GameEngine/Source/Common
// stlport
// Native00586083..0058619F is284B RET4. WB1472FE0 names
// HordeMeleeFormation::startMeleeAttack (source lines75/83); the native
// constructor00586D8E installs table0086FD90 with this body at slot3.
// The84B record layout and deque+28 follow the existing verified constructor,
// assignment and snapshot transfer00587075. BfmeE12 is an element-size stand-in.
// clear0058592D has the existing neutral BfmeE8 owner: this storage projection
// invokes its verified scalar cleanup, not an element-identity or alias claim.
// Only the external clear declaration is emitted; no second provider or pin.
#include "Coord3D.h"
#include <vector>
#include <deque>
class Object;
enum ObjectStatusTypes { FORMATION_STATUS_1C=0x1c };
enum CommandSourceType { FORMATION_COMMAND=2 };
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
class AICommandInterface { public: void aiIdle(CommandSourceType); };
class Object {
public:
 bool testStatus(ObjectStatusTypes) const;
 int rva0028B511() const;
 void rva0028ACEE(const Coord3D *,int);
 unsigned char pad0[4]; void *m_template;
 unsigned char pad8[0x38-8]; Coord3D m_position;
 unsigned char pad44[0x74-0x44]; int m_id;
 unsigned char pad78[0x250-0x78]; FormationContainer *m_container;
 unsigned char pad254[4]; FormationAI *m_ai;
};
struct FormationNode { FormationNode *next,*prev; Object *object; };
struct FormationList { FormationNode *head; };
struct FormationRange {
 void *owner; FormationList *list;
 unsigned int size() const { unsigned int n=0; for(FormationNode *p=list->head->next;p!=list->head;p=p->next) ++n; return n; }
};
class FormationListProvider : public FormationSlots<70> { public: virtual void fill(FormationRange *)=0; };
struct FormationHeld { unsigned char pad[0x120]; bool active; };
class Rva0046ACF6 { public: int rva0046ACF6(int); };

struct BfmeE8 { int a,b; };
struct BfmeE12 { float x,y,z; };
namespace _STL { template<> void deque<BfmeE8>::clear(); }
struct FormationAttackEntry {
 int state; Coord3D position; int unknown10[3]; bool needsPosition; char pad[3]; int a,b;
 _STL::deque<BfmeE12> path; int tail;
};
class HordeMeleeFormation {
public:
 virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void startMeleeAttack(Object *);
 virtual void slot4(); virtual void slot5(); virtual void slot6(); virtual void slot7();
 virtual void slot8(); virtual void slot9(); virtual void slot10(); virtual void slot11(); virtual void slot12();
 virtual bool rva00585017(int,Coord3D *);
 FormationHeld *held; _STL::vector<FormationAttackEntry> attacks;
 bool force; void *other;
};
void HordeMeleeFormation::startMeleeAttack(Object *victim)
{
 held->active=true;
 FormationRange range;
 ((FormationListProvider *)((char *)held+0x20))->fill(&range);
 for(FormationNode *node=range.list->head->next;node!=range.list->head;node=node->next) {
  Object *unit=node->object;
  if(!unit) continue;
  FormationAI *ai=unit->m_ai;
  if(ai && *(int *)((char *)ai+0x1fc)==4 && *(int *)((char *)ai+0x140)) continue;
  int index=((Rva0046ACF6 *)held)->rva0046ACF6(unit->m_id);
  if(index<0 || index>=attacks.size()) continue;
  if(!unit->testStatus(FORMATION_STATUS_1C)) {
   if(!ai) continue;
   if(!ai->idleBlocked()) ((AICommandInterface *)((char *)ai+0x20))->aiIdle(FORMATION_COMMAND);
  }
  FormationAttackEntry &entry=attacks[index];
  entry.position=unit->m_position;
  entry.needsPosition=true;
  ((_STL::deque<BfmeE8> *)&entry.path)->clear();
  unit->rva0028ACEE(&unit->m_position,unit->rva0028B511());
  unit->m_ai->resetAttack();
 }
}

// Native585017..585059 is66B RET8. WB1474BB0 and the constructor
// table slot13 establish index/output ABI; the original spelling is unknown.
// The following10B deque iterator body at585059 is outside this extent.
bool HordeMeleeFormation::rva00585017(int index,Coord3D *result)
{
 if(index>=0 && index<attacks.size() && !attacks[index].needsPosition) {
  *result=attacks[index].position;
  return true;
 }
 return false;
}
