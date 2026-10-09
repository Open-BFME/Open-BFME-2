// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /I. /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Native4D6DF3..4D6E95 RET8; callers in privateAttackObject and
// privateForceAttackObject pass an Object and true to a 1C-byte Squad.
// ZH/BF1f989 Squad::squadFromTeam guides optional clear + member-ID append;
// target replaces team iteration with Object contain250 slot31 and the
// resulting horde interface slot67 filling a list<Object*>. Original method
// name remains address-derived. Squad ctor268CAC proves two vectors4/10.
// Native member ObjectID74 is copied into a local before push_back; binding
// ids through a local pointer keeps native LEA then finish load. Whole162B
// and EH exact. Emitted list-pointer ctor/dtor are byte-and-relocation twins
// of the owned list<int> bodies4EC36C/4EC395, zero unique-byte credit.
#include <vector>
#include <list>
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
class Object;
template<int N> class SquadMembersSlots : public SquadMembersSlots<N-1>{public:virtual void gap(char(*)[N])=0;};template<>class SquadMembersSlots<0>{};
class SquadMembersHorde : public SquadMembersSlots<67>{public:virtual void slot67(_STL::list<Object*>*)=0;};
class SquadMembersContain : public SquadMembersSlots<31>{public:virtual SquadMembersHorde*slot31()=0;};
class Object {public:char pad0[0x74];ObjectID id;char pad78[0x250-0x78];SquadMembersContain *contain;};
class Squad {public:virtual void *slot0(int);void rva004D6DF3(Object*,bool);_STL::vector<ObjectID> ids;_STL::vector<Object*> objects;};
void Squad::rva004D6DF3(Object *obj,bool clearFirst){
 if(!obj)return;
 if(clearFirst){_STL::vector<ObjectID> *v=&ids;v->erase(v->begin(),v->end());}
 SquadMembersContain *contain=obj->contain;if(!contain)return;
 SquadMembersHorde *group=contain->slot31();if(!group)return;
 _STL::list<Object*>members;group->slot67(&members);
 for(_STL::list<Object*>::iterator i=members.begin();i!=members.end();++i){Object *member=*i;if(member){ObjectID id=member->id;ids.push_back(id);}}
}
