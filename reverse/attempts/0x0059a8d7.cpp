// ?recruitUnDefined@AITeamBuilder@@QAEXPAVTeam@@PAH@Z
// partial score=0.85 date=2026-10-08
// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/moduledata /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common /ICode/Libraries/Include
// stlport
#include <stdlib.h>
namespace _STL { void __cdecl free(void*); }
#define free _STL::free
#include <vector>
#undef free
#include "GameLogicObjectLookupView.h"
#include "Lib/Coord3D.h"
// Native Team's two-base member-pointer ABI is shared with the verified
// TeamPrototypeTeamIterators.cpp; ZH supplies the same DLINK iterator.
class MemoryPoolObject { public: virtual ~MemoryPoolObject(); };
#include "Common/Snapshot.h"
class Player;
struct AITeamRequirementView;
struct AITargetView;
class TeamPrototype;
class Team : public MemoryPoolObject, public Snapshot {
public:
 Team* dlink_next_TeamInstanceList() const;
 char prefix08[0x30-8];
 TeamPrototype* prototype30;
};
template<class T> class DLINK_ITERATOR {
 typedef T* (T::*GetNextFunc)() const;
 T* current;
 GetNextFunc next;
public:
 DLINK_ITERATOR(T* c,GetNextFunc n):current(c),next(n){}
 void advance(){if(current)current=(current->*next)();}
 bool done() const{return current==0;}
 T* cur() const{return current;}
};
class TeamPrototype {
public:
 char prefix00[0x334];
 Team* teamHead334;
 DLINK_ITERATOR<Team> iterate_TeamInstanceList() const {
  return DLINK_ITERATOR<Team>(teamHead334,&Team::dlink_next_TeamInstanceList);
 }
};
class AITeamBuilder {
public:
 Team* getTeamForAIPrototype(TeamPrototype*);
 void recruitUnDefined(Team*,int*);
 void distanceSortUnits(void*,const void*,const Coord3D*);
 bool rva0059A01C(Object*,const AITeamRequirementView*,const AITargetView*);
 char prefix00[0x14];
 Player* owner14;
};
// WB01529260 names the method and asserts at most one team. Native
// 00599F74..00599FAA traverses the entire list and retains its first member.
Team* AITeamBuilder::getTeamForAIPrototype(TeamPrototype* prototype) {
 Team* result=0;
 for(DLINK_ITERATOR<Team> it=prototype->iterate_TeamInstanceList();!it.done();it.advance()) {
  if(!result)result=it.cur();
 }
 return result;
}

struct AITeamRequirementView {
 char pad00[0x198];
 int targetKind;
 char pad19c[4];
 int kind1A0;
 unsigned int max1A4;
};
class Rva002A8F24 { public: void* rva002A8F24(Player*); void* rva002A8B73(void*,int); };
class Rva005C4AD1LeaField { public: void* get() const; };
class Rva0039D7C1ByteField { public: unsigned char get() const; };
class Rva0039D7C8LeaGetter { public: void* get() const; };
struct RecruitThingTemplate { char pad00[0x108]; unsigned char kind108; char pad109[10]; unsigned char kind113; };
class Object {
public:
 char pad00[4]; RecruitThingTemplate* objectTemplate;
 void setTeam(Team*);
};
extern Rva002A8F24* g_00DFEEF8;
extern GameLogic* TheGameLogic;
void AITeamBuilder::recruitUnDefined(Team* teamToBuild,int* curNumUnits) {
 void* stats=g_00DFEEF8->rva002A8F24(owner14);
 Rva005C4AD1LeaField* unitStats=*(Rva005C4AD1LeaField**)stats;
 TeamPrototype* prototype=teamToBuild->prototype30;
 const AITeamRequirementView* requirements=(const AITeamRequirementView*)((const char*)prototype+0x12C);
 AITargetView* target=(AITargetView*)g_00DFEEF8->rva002A8B73(owner14,requirements->targetKind);
 const _STL::vector<ObjectID>* units=(const _STL::vector<ObjectID>*)unitStats->get();
 const _STL::vector<ObjectID>* useUnits=units;
 _STL::vector<ObjectID> sorted;
 if(((Rva0039D7C1ByteField*)prototype)->get()) {
  distanceSortUnits(&sorted,units,(const Coord3D*)((Rva0039D7C8LeaGetter*)prototype)->get());
  useUnits=&sorted;
 }
 const ObjectID* end=useUnits->end();
 for(const ObjectID* it=useUnits->begin();it!=end;++it) {
  if((unsigned int)*curNumUnits>=requirements->max1A4)break;
  Object* obj=TheGameLogic->findObjectByID(*it);
  if((obj->objectTemplate->kind108&8)&&rva0059A01C(obj,requirements,target)) {
   obj->setTeam(teamToBuild);
   ++*curNumUnits;
  }
 }
 if(requirements->kind1A0==0||requirements->kind1A0==1) {
  for(const ObjectID* it=useUnits->begin();it!=end;++it) {
   Object* obj=TheGameLogic->findObjectByID(*it);
   if((obj->objectTemplate->kind113&4)&&rva0059A01C(obj,requirements,target)) {
    obj->setTeam(teamToBuild);
    ++*curNumUnits;
   }
  }
 }
}
