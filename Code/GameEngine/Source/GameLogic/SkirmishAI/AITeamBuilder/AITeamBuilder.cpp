// cl: /O1 /MD /EHs /arch:SSE /G7 /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>
#include <set>
#include "../../../Common/GameLogicObjectLookupView.h"
#pragma pointers_to_members(full_generality, multiple_inheritance)
class Player;
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
