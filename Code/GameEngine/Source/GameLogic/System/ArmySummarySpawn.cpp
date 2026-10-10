// ?SpawnOneDelayedCarryoverUnit@ArmySummary@@QAE?AW4ObjectID@@PAVObjectTypes@@@Z
// Native40E589..40E672 RET4; WB10889B0 names ArmySummary SpawnOneDelayedCarryoverUnit.
// Verified holder-copy visibility prevents its hidden-output address escaping.
// The entry-count snapshot follows the native post-list-init load order.
// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/moduledata /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// WB10889B0 ArmySummary::SpawnOneDelayedCarryoverUnit evidence; BF1/ZH have
// no reusable ArmySummary source. Existing BFME2 summary/ref/vector providers
// establish the layouts and calls used below. All target deltas are native.
#include "ascii_string.h"
#include <vector>
#define BFME_SNAPSHOT_NAME_SLOT 1
#include "Common/Snapshot.h"
class Player;
class Object;
// Native DB8FEC object-list policy is distinct from generic allocator41B.
template<class T>class Rva001EB984PoolAllocator {};
#include "../../Common/GameLogicObjectLookupView.h"
class Object {public:char bytes00[0x74];ObjectID id;};
struct LoadedObjectNode{LoadedObjectNode*next,*prev;Object*value;};
struct TargetRef00217D4C {void*vt;int references;};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
class ArmySummaryEntry {
public:Object*rva0040C495(Player*,int);
 char bytes00[4];AsciiString templateName;
 char bytes08[0x90-8];int count;
 char bytes94[0xAC-0x94];TargetRef00217D4C ref;
 char bytesB4[0xC5-0xB4];bool flagged;char bytesC6[2];
};
class Rva004F6093Holder {
public:
 ArmySummaryEntry*value;
 __forceinline Rva004F6093Holder():value(0){}
 __declspec(noinline) inline Rva004F6093Holder(const Rva004F6093Holder&x):value(x.value){if(value)++value->ref.references;}
 __forceinline ArmySummaryEntry*operator->()const{return value;}
 __forceinline Rva004F6093Holder(ArmySummaryEntry*p):value(p){if(value)++value->ref.references;}
 __forceinline ~Rva004F6093Holder(){if(value)ReleaseTreeHintRef00217D4C(&value->ref);}
};
class Rva0040CB11Entry {public:int key;Rva004F6093Holder value;};
class Rva001EB769 {public:void rva001EB769() throw();};
class FreelistProxyHead {public:void setup(const void*,void*);};
class FreelistPool {public:void*pop();};
extern FreelistPool g_freelistPool00DB8FEC;
// The visible constructor preserves the native unused-policy argument
// placement. Its complete40B copy and every relocation match the exact strong
// pool provider in StlportObjectFreelistListBaseCtor.cpp.
namespace _STL {
template<class T,class A>class list;
template<>class list<Object*,allocator<Object*> > {public:void push_back(Object*const&);};
template<class T,class A>class _List_base;
template<>class _List_base<Object*,Rva001EB984PoolAllocator<Object*> > {
public:
 _List_base(const Rva001EB984PoolAllocator<Object*>&);
 __forceinline ~_List_base() throw(){((Rva001EB769*)this)->rva001EB769();}
 void*head;
};
__declspec(noinline) inline _List_base<Object*,Rva001EB984PoolAllocator<Object*> >::_List_base(const Rva001EB984PoolAllocator<Object*>&a)
{
 char dummy;((FreelistProxyHead*)this)->setup(&dummy,0);
 void*n=g_freelistPool00DB8FEC.pop();((void**)n)[0]=n;((void**)n)[1]=n;head=n;
}
template<>class list<Object*,Rva001EB984PoolAllocator<Object*> > : public _List_base<Object*,Rva001EB984PoolAllocator<Object*> > {
public:
 list(const Rva001EB984PoolAllocator<Object*>&a=Rva001EB984PoolAllocator<Object*>()):_List_base<Object*,Rva001EB984PoolAllocator<Object*> >(a){}
 __forceinline void push_back(Object*const&v){((list<Object*,allocator<Object*> >*)this)->push_back(v);}
 bool empty()const{return *(void**)head==head;}
 Object*front()const{return ((LoadedObjectNode*)head)->next->value;}
};
}
typedef _STL::list<Object*,Rva001EB984PoolAllocator<Object*> > LoadedObjectList;
struct Rva0040E534Input {ArmySummaryEntry*value;};
class Rva0040D8D6List {public:~Rva0040D8D6List();void*begin,*end,*limit;unsigned index;};
struct ArmySummaryEntryRef{Rva004F6093Holder holder;ArmySummaryEntryRef(){}ArmySummaryEntryRef(const Rva004F6093Holder&h):holder(h){}};
class Rva0040CB3AIndexedField{public:int find(int)const;};
class ObjectTypes{public:char pad[8];_STL::vector<AsciiString>types;};
class Rva00376A62{public:bool rva00376A62(const StringBase<char>&);};
namespace _STL{template<>vector<ObjectID>::iterator vector<ObjectID>::erase(iterator);}
class ArmySummary : public Snapshot, public Rva0040D8D6List {
public:ArmySummaryEntryRef GetEntry(int);
 ObjectID SpawnOneDelayedCarryoverUnit(ObjectTypes*);
 void LoadArmyEntry(Rva0040E534Input*,int,LoadedObjectList*,int);
private:
 bool flag14;char gap15[3];AsciiString name18;int armyID;AsciiString name20;
 char bytes24[0x40-0x24];
 _STL::vector<Rva0040CB11Entry>entries;_STL::vector<ObjectID>pending;
 char bytes58[8];int at60;
};
Player*Rva0040C94ALookup(int);
__declspec(noinline) inline void ArmySummary::LoadArmyEntry(Rva0040E534Input*input,int count,LoadedObjectList*out,int overrideID)
{
 Player*player=Rva0040C94ALookup(armyID);
 if(player){
  int selected=overrideID?overrideID:armyID;
  for(;count>0;--count){
   Object*object=input->value->rva0040C495(player,selected);
   if(object)out->push_back(object);
  }
 }
}

ObjectID ArmySummary::SpawnOneDelayedCarryoverUnit(ObjectTypes*filter)
{
 if(filter->types.size()==0)return INVALID_OBJECT_ID;
 const _STL::vector<ObjectID>::iterator last=pending.end();
 for(_STL::vector<ObjectID>::iterator i=pending.begin();i!=last;){
  ArmySummaryEntryRef value=GetEntry((int)*i);
  ArmySummaryEntry*held=value.holder.value;
  if(held && reinterpret_cast<Rva00376A62*>(filter)->rva00376A62(*(StringBase<char>*)&held->templateName)){
   pending.erase(i);
   LoadedObjectList spawned;
   const int count=held->count; ObjectID result=INVALID_OBJECT_ID;
   LoadArmyEntry((Rva0040E534Input*)&value,count,&spawned,0);
   if(!spawned.empty() && spawned.front())result=spawned.front()->id;
   return result;
  }
  ++i;
 }
 return INVALID_OBJECT_ID;
}

__declspec(noinline) inline ArmySummaryEntryRef ArmySummary::GetEntry(int key){
 int index=((const Rva0040CB3AIndexedField*)this)->find(key);
 if(index<0)return ArmySummaryEntryRef();
 return ArmySummaryEntryRef(entries.begin()[index].value);
}
