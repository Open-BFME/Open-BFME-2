// ?recruitPreDefined@AITeamBuilder@@QAEXPAVTeam@@PAHPAVTeamPrototype@@@Z
// partial score=0.91 date=2026-10-08
// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/moduledata /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_STLP_USE_STATIC_LIB /ICode/GameEngine/Source/Common /ICode/Libraries/Include
// stlport
// Native Team's two-base member-pointer ABI is shared with the verified
// TeamPrototypeTeamIterators.cpp; ZH supplies the same DLINK iterator.
#include <stdlib.h>
namespace _STL { void __cdecl free(void*); }
#define free _STL::free
#include <vector>
#include <map>
#include <hash_map>
#undef free
#include "ascii_string.h"
class MemoryPoolObject { public: virtual ~MemoryPoolObject(); };
#include "Common/Snapshot.h"
class Object;
class Player;
struct AITeamRequirementView;
struct AITargetView;
class Rva0039D769;
enum ObjectStatusTypes { STATUS_90=90 };
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
 void addUnitInfo(const Rva0039D769&);
 void rva003A0E08(const Rva0039D769&);
 char prefix00[0x1d8]; int unitCount;
 char pad1dc[0x2d0-0x1dc]; unsigned max2d0;
 char pad2d4[0x334-0x2d4];
 Team* teamHead334;
 DLINK_ITERATOR<Team> iterate_TeamInstanceList() const {
  return DLINK_ITERATOR<Team>(teamHead334,&Team::dlink_next_TeamInstanceList);
 }
};
class AITeamBuilder {
public:
 Team* getTeamForAIPrototype(TeamPrototype*);
 void recruitPreDefined(Team*,int*,TeamPrototype*);
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

#include "GameLogicObjectLookupView.h"
#include "Lib/Coord3D.h"
// Both rowed native query providers walk seven words. The existing
// Thing::isAnyKindOf provider retains BitFlags<69> in its ABI spelling;
// the actual requirement storage and any() instantiation are BitFlags<218>.
template<int N> class BitFlags { public: bool any() const; unsigned int words[7]; };
class Thing { public: bool isAnyKindOf(const BitFlags<69>&) const; };
struct RecruitThingTemplate { char prefix[0x64]; AsciiString name; char pad68[0x108-0x68]; unsigned char kind108; char pad109[10]; unsigned char kind113; };
class AIUpdateInterface { public: Object* getCurrentVictim() const; };
class Object {
public:
 bool testStatus(ObjectStatusTypes) const;
 void setTeam(Team*);
 char pad00[4]; RecruitThingTemplate* objectTemplate;
 char pad08[0x38-8]; Coord3D position;
 char pad44[0x258-0x44]; AIUpdateInterface* ai;
 char pad25c[0x304-0x25c]; Team* team;
 char pad308[0x438-0x308]; unsigned char flag438;
 char pad439[0x4c0-0x439]; unsigned int frame4c0;
};
class Player { public: char prefix[0x2ec]; Team* defaultTeam; };
struct AITeamRequirementView {
 int first; char records04[0xa8]; unsigned recordCount; char padb0[0xf0-0xb0]; int priority;
 char padf4[0x198-0xf4]; int targetKind; char pad19c[0x1b4-0x19c]; BitFlags<218> required;
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

class Rva0039D761DwordClearer { public: void clear(); };
class Rva002A8F24 { public: void* rva002A8F24(Player*); void* rva002A8B73(void*,int); };
class Rva005C4AD1LeaField { public: void* get() const; };
class Rva0039D5A9 { public: int rva0039D5A9(); };
class Rva0039EA9C {
public:
 Rva0039EA9C(); ~Rva0039EA9C();
 int first; int second; int third;
 AsciiString name0c; AsciiString name10; int final14;
};
extern Rva002A8F24* g_00DFEEF8;
namespace _STL {
 template<> vector<ObjectID>::vector(const vector<ObjectID>&);
 template<> unsigned int hash_map<int,int>::bucket_count() const;
}

class Rva0039D7C1ByteField { public: unsigned char get() const; };
class Rva0039D7C8LeaGetter { public: void* get() const; };
struct TreeOpaqueMapped00372FF4 { unsigned int m_bits; };
typedef _STL::pair<const float, TreeOpaqueMapped00372FF4> DistanceValue;
typedef _STL::_Rb_tree<float, DistanceValue, _STL::_Select1st<DistanceValue>,
    _STL::less<float>, _STL::allocator<DistanceValue> > DistanceTree;
typedef _STL::map<int, void *> HeaderConstructor;

enum ScienceType { SCIENCE_0 = 0 };
typedef _STL::vector<ScienceType> IDVectorView;
namespace _STL {
template <> HeaderConstructor::map();
template <> DistanceTree::iterator DistanceTree::insert_equal(const DistanceValue &);
template <> void IDVectorView::reserve(unsigned int);
template <> void IDVectorView::push_back(const ScienceType &);
}

// The rowed destructor owns an eight-byte tree header/count pair. Native
// construction uses the existing map constructor with this same storage.
class Rva00599FAA : public HeaderConstructor
{
public:
    __forceinline Rva00599FAA() {}
    ~Rva00599FAA();

};


void AITeamBuilder::recruitPreDefined(Team* team,int* count,TeamPrototype* remaining) {
 AITeamRequirementView* requirements=(AITeamRequirementView*)((char*)remaining+0x12c);
 if(requirements->priority<20)requirements->priority=20;
 void* stats=g_00DFEEF8->rva002A8F24(owner14);
 const IDVectorView* units=(const IDVectorView*)((Rva005C4AD1LeaField*)*(void**)stats)->get();
 IDVectorView sorted;
 TeamPrototype* prototype=team->prototype30;
 if(((Rva0039D7C1ByteField*)prototype)->get()) {
  Rva00599FAA distances;
  const ScienceType* end=units->end();
  for(const ScienceType* it=units->begin();it!=end;++it) {
   Object* object=TheGameLogic->findObjectByID((ObjectID)*it);
   const Coord3D* center=(const Coord3D*)((Rva0039D7C8LeaGetter*)prototype)->get();
   Coord3D delta={center->x,center->y,center->z};
   delta.x-=object->position.x;delta.y-=object->position.y;delta.z-=object->position.z;
   TreeOpaqueMapped00372FF4 value; value.m_bits=*it;
   ((DistanceTree*)&distances)->insert_equal(DistanceValue(delta.x*delta.x+delta.y*delta.y+delta.z*delta.z,value));
  }
  sorted.reserve(distances.size());
  DistanceTree* tree=(DistanceTree*)&distances;
  DistanceTree::iterator finish=tree->end();
  for(DistanceTree::iterator it=tree->begin();it._M_node!=finish._M_node;++it)sorted.push_back(*(const ScienceType*)&it->second.m_bits);
  units=&sorted;
 }
 AITargetView* target=(AITargetView*)g_00DFEEF8->rva002A8B73(owner14,requirements->targetKind);
 const ScienceType* end=units->end();
 for(const ScienceType* it=units->begin();it!=end;++it) {
  if(((Rva0039D5A9*)requirements)->rva0039D5A9()<=0)break;
  Object* obj=TheGameLogic->findObjectByID((ObjectID)*it);
  if(rva0059A01C(obj,requirements,target)) {
   bool recruited=false;
   for(unsigned i=0;i<requirements->recordCount&&!recruited;++i) {
    Rva0039EA9C* req=(Rva0039EA9C*)requirements->records04+i;
    if(((const StringBase<char>&)req->name10).compare((const StringBase<char>&)obj->objectTemplate->name)==0 && req->first>0) {
     obj->setTeam(team); ++*count;
     Rva0039EA9C used;
     used.first=1; used.second=1;
     used.name10=obj->objectTemplate->name;
     used.final14=req->final14;
     remaining->rva003A0E08((const Rva0039D769&)used);
     recruited=true;
    }
   }
  }
 }
}
