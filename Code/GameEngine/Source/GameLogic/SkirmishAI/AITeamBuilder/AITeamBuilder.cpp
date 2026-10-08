// cl: /O1 /MD /EHs /arch:SSE /G7 /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /ICode/GameEngine/Source/Common /ICode/Libraries/Include
// stlport
#include <vector>
#include <set>
#include "../../../Common/GameLogicObjectLookupView.h"
#pragma pointers_to_members(full_generality, multiple_inheritance)
class Player;
struct AITeamRequirementView;
struct AITargetView;
struct Rva002A8AB1Record;
class Rva002A8F24 { public: Rva002A8AB1Record *rva002A8AB1(void *); };
extern Rva002A8F24 *g_00DFEEF8;
extern GameLogic *TheGameLogic;
class Team {
public:
 char pad[0x5d]; bool active; bool dirty;
 char pad5f[0x110-0x5f]; bool flag110; bool flag111;
 Team *dlink_next_TeamInstanceList() const;
};
template<class T> class DLINK_ITERATOR {
 typedef T *(T::*Next)() const;
 T *current;
 Next next;
public:
 DLINK_ITERATOR(T *p, Next f):current(p),next(f){}
 void advance() { if (current) current=((*current).*next)(); }
 bool done() const { return current==0; }
 T *cur() const { return current; }
};
class SkirmishAI { public: void Register(Team *); };
class Rva0039D5A9 { public: int rva0039D5A9(); };
struct Requirements {
 char pad[0x1a0]; int mode; unsigned maximum; unsigned minimum;
};
class TeamPrototype {
public:
 char prefix[0x12c]; Requirements requirements;
 char pad2d8[0x31c-0x2d8]; bool building; bool ready;
 char pad31e[0x334-0x31e]; Team *head;
 DLINK_ITERATOR<Team> iterate_TeamInstanceList() const { return DLINK_ITERATOR<Team>(head,&Team::dlink_next_TeamInstanceList); }
};
class AITeamBuilder {
public:
 int getCurNumUnits(Team *);
 int doesTeamMeetThreat(Team *);
 bool rva0059A01C(Object*,const AITeamRequirementView*,const AITargetView*);
 char prefix00[0x14]; Player* owner14;
};
class Rva0059AC4D {
 char prefix[8]; _STL::vector<TeamPrototype *> prototypes;
 Player *owner; _STL::set<int> busy;
public:
 void update();
 void rva0059ABC9(void *);
 void rva0059AC4D(void *);
 Team *rva00599F74(TeamPrototype *);
 void checkIdleTeams();
};
// Native59AC6E..59ADB9,331B; WB1528FA0 AITeamBuilder::update (assert125).
// The two prototype passes, owner14, active/ready31C/31D, Team flags5D/5E
// and110/111, set18 and every call are corroborated by retail. Keep the
// existing address-derived receiver and recruited-helper ABIs. Threat
// provider is presently typed int; this call site consumes its low byte.
void Rva0059AC4D::update()
{
 for (_STL::vector<TeamPrototype *>::iterator it=prototypes.begin(); it!=prototypes.end(); ++it) {
  TeamPrototype *prototype=*it;
  if (prototype->building) {
   int mode=*(int *)((char *)prototype+0x2cc);
   switch(mode) {
    case 2: rva0059AC4D(prototype); break;
    default: rva0059ABC9(prototype); break;
   }
  }
 }
 for (_STL::vector<TeamPrototype *>::iterator it=prototypes.begin(); it!=prototypes.end(); ++it) {
  TeamPrototype *prototype=*it;
  if (prototype->building) {
   Requirements *requirements=&prototype->requirements;
   Team *team=rva00599F74(prototype);
   if (team) {
    int count=((AITeamBuilder *)this)->getCurNumUnits(team);
    if ((unsigned)count >= requirements->minimum &&
        ((Rva0039D5A9 *)requirements)->rva0039D5A9()==0 &&
        (requirements->mode==1 || (unsigned)count>=requirements->maximum ||
         (unsigned char)((AITeamBuilder *)this)->doesTeamMeetThreat(team))) {
     team->flag110=true;
     team->flag111=false;
     if (!team->active) { team->dirty=true; team->active=true; }
     SkirmishAI *ai=(SkirmishAI *)g_00DFEEF8->rva002A8AB1(owner);
     ai->Register(team);
     prototype->building=false;
     prototype->ready=true;
    }
   }
  }
 }
 for (_STL::set<int>::iterator it=busy.begin(); it!=busy.end();) {
  if (!TheGameLogic->findObjectByID((ObjectID)*it)) busy.erase(it++);
  else ++it;
 }
 checkIdleTeams();
}

// Native599F74..599FAA54B; WB1529260 getTeamForAIPrototype asserts157..166.
// Head334 and callback5C4AF5 use the proven zero-adjusted8B member pointer.
Team *Rva0059AC4D::rva00599F74(TeamPrototype *prototype)
{
 Team *first=0;
 for(DLINK_ITERATOR<Team> it=prototype->iterate_TeamInstanceList(); !it.done(); it.advance()) {
  if (!first) first=it.cur();
 }
 return first;
}

#include "GameLogicObjectLookupView.h"
#include "Lib/Coord3D.h"
// Both rowed native query providers walk seven words. The existing
// Thing::isAnyKindOf provider retains BitFlags<69> in its ABI spelling;
// the actual requirement storage and any() instantiation are BitFlags<218>.
template<int N> class BitFlags { public: bool any() const; unsigned int words[7]; };
class Thing { public: bool isAnyKindOf(const BitFlags<69>&) const; };
struct RecruitThingTemplate { char prefix[0x113]; unsigned char kind113; };
class AIUpdateInterface { public: Object* getCurrentVictim() const; };
class Object {
public:
 char pad00[4]; RecruitThingTemplate* objectTemplate;
 char pad08[0x38-8]; Coord3D position;
 char pad44[0x258-0x44]; AIUpdateInterface* ai;
 char pad25c[0x304-0x25c]; Team* team;
 char pad308[0x438-0x308]; unsigned char flag438;
 char pad439[0x4c0-0x439]; unsigned int frame4c0;
};
class Player { public: char prefix[0x2ec]; Team* defaultTeam; };
struct AITeamRequirementView {
 char prefix[0xf0]; int priority;
 char padf4[0x1b4-0xf4]; BitFlags<218> required;
 BitFlags<218> forbidden;
};
struct AITargetView { int word0; int kind; int word8; Coord3D position; };
// This is an observed secondary-interface call, not a Snapshot override:
// native 59A06A adjusts Team by four and invokes slot eight for a float.
// Keep its unresolved interface identity separate from the Team list ABI.
class TeamPriorityCallView { public: virtual void slot0(); virtual void slot4(); virtual float priority(); };
struct TeamPriorityDataView { char prefix[0x111]; bool active; };
extern GameLogic* TheGameLogic;
extern int g_00E063E0;
// Native 0059A01C..0059A153 and WB0152A380 establish this three-argument
// recruitment predicate. WB only exposes inlined Vector3 names, so retain
// an address name for the outer method. Retail rejects unordered distance
// comparisons, then applies required/forbidden kinds, age, and victim gates.
bool AITeamBuilder::rva0059A01C(Object* obj,const AITeamRequirementView* req,const AITargetView* target) {
 Team* currentTeam;
 if(!obj || (obj->flag438&1) || (obj->objectTemplate->kind113&8))goto reject;
 currentTeam=obj->team;
 if(currentTeam!=owner14->defaultTeam) {
  if(!(((TeamPriorityDataView*)currentTeam)->active && ((TeamPriorityCallView*)((char*)currentTeam+4))->priority()<req->priority)) {
   if(!target||target->kind!=1)goto reject;
   Coord3D a={target->position.x,target->position.y,target->position.z};
   Coord3D b={obj->position.x,obj->position.y,obj->position.z};
   Coord3D delta={b.x-a.x,b.y-a.y,b.z-a.z};
   if(!(delta.z*delta.z+delta.y*delta.y+delta.x*delta.x<=1000000.0f))goto reject;
  }
 }
 if(req->required.any()&&!((Thing*)obj)->isAnyKindOf((const BitFlags<69>&)req->required))goto reject;
 if(req->forbidden.any()&&((Thing*)obj)->isAnyKindOf((const BitFlags<69>&)req->forbidden))goto reject;
 if(TheGameLogic->getFrame()-obj->frame4c0<(unsigned)g_00E063E0)goto reject;
 if(obj->ai->getCurrentVictim())goto reject;
 return true;
reject:
 return false;
}
