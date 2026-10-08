// ?checkIdleTeams@Rva0059AC4D@@QAEXXZ
// partial score=0.88 date=2026-10-08
// cl: /ICode/Libraries/Include/Lib /O1 /arch:SSE /G7 /MD /EHsc /D_STLP_NO_EXCEPTIONS /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
#include <stdlib.h>
namespace _STL { void __cdecl free(void *); }
#define free _STL::free
#include <vector>
#include <set>
#undef free
#include "../../../Common/GameLogicObjectLookupView.h"
#include "Coord3D.h"
class Rva00295A0FCommands { public: void Rva00295A0FCommand(void *, int, int); };
class AIUpdateView { public: char prefix[0x20]; Rva00295A0FCommands commands; };
class ThingTemplate { public: char pad[0x108]; unsigned kind0; unsigned gap; unsigned kindWord110;  };
enum ObjectStatusTypes {};
class Object {
public:
 char prefix[4]; ThingTemplate *m_template;
 char pad08[0x74-8]; int id;
 char pad78[0x258-0x78]; AIUpdateView *ai;
 char pad25c[0x304-0x25c]; int player;
 char pad308[0x4c0-0x308]; unsigned lastCommand;
 bool testStatus(ObjectStatusTypes) const;
};
namespace _STL { template<> void vector<Object *>::push_back(Object *const &); }
class Player { public: char prefix[0x2ec]; int index; };
struct Rva002A8AB1Record;
class Rva002A8F24 { public: void *rva002A8F24(Player *); Rva002A8AB1Record *rva002A8AB1(void *); };
class Rva0025BFF8 { public: Object *rva0025BFF8(int); };
namespace _STL {
template <class T> struct hash;
template <class K,class T,class H,class E,class A> class hash_map {
 public: unsigned int bucket_count() const;
};
}
typedef _STL::hash_map<int,int,_STL::hash<int>,_STL::equal_to<int>,_STL::allocator<_STL::pair<const int,int> > > CountView;
extern Rva002A8F24 *g_00DFEEF8;
extern GameLogic *TheGameLogic;
extern int g_00E063E0;
int __cdecl GetGameLogicRandomValue(int,int,char*,int);
struct PositionEntry { int unknown; Coord3D position; };
class Rva0059AC4D {
 char pad[0x14]; Player *owner; _STL::set<int> busy;
public: void checkIdleTeams();
};
struct TargetListView { char prefix[0x20]; _STL::vector<PositionEntry *> entries; };
struct SkirmishView { char prefix[0x164]; TargetListView *targets; };
// Kept declaration-only: the native helper is a cardinality ABI view.
void Rva0059AC4D::checkIdleTeams()
{
 void *stats = g_00DFEEF8->rva002A8F24(owner);
 void *units = *(void **)stats;
 int n = ((CountView *)units)->bucket_count();
 if (n > 0) {
  _STL::vector<Object *> idle;
  int ownerID = owner->index;
  for (int i=0; i<n; ++i) {
   Object *object = ((Rva0025BFF8 *)units)->rva0025BFF8(i);
   ThingTemplate *templ=object->m_template;
   if ((((templ->kind0 & 8) && !(templ->kind0 & 0x80)) || (templ->kindWord110 & 0x04000000)) &&
       object->player==ownerID && !object->testStatus((ObjectStatusTypes)0x5a)) {
    int id=object->id;
    if (busy.find(id)==busy.end() && TheGameLogic->getFrame()-object->lastCommand >= (unsigned)g_00E063E0) {
     Object *candidate=object;
     idle.push_back(candidate);
    }
   }
  }
  SkirmishView *ai = (SkirmishView *)g_00DFEEF8->rva002A8AB1(owner);
  TargetListView *targets = ai->targets;
  Object **idleBegin=idle.begin();
  Object **idleEnd=idle.end();
  if (idleBegin != idleEnd && !targets->entries.empty()) {
   Object *object=idleBegin[GetGameLogicRandomValue(0,idleEnd-idleBegin-1,
    "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AITeamBuilder\\AITeamBuilder.cpp",0x251)];
   unsigned last = targets->entries.size()-1;
   PositionEntry **entryStart=targets->entries.begin();
   PositionEntry *entry=entryStart[last];
   int id=object->id;
   busy.insert(id);
   object->ai->commands.Rva00295A0FCommand(&entry->position,0x7fffffff,0);
  }
 }
}
