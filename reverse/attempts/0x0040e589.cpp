// ?SpawnOneDelayedCarryoverUnit@ArmySummary@@QAE?AW4ObjectID@@PAVRva00376A62@@@Z
// partial score=0.94 date=2026-10-09
// cl: /O1 /Oy- /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/moduledata /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
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
#include "../../Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
class Object {public:char bytes00[0x74];ObjectID id;};
struct LoadedObjectNode{LoadedObjectNode*next,*prev;Object*value;};
struct TargetRef00217D4C {void*vt;int references;};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
class ArmySummaryEntry {
public:ArmySummaryEntry();Object*rva0040C495(Player*,int);
 char bytes00[4];AsciiString templateName;
 char bytes08[0x90-8];int count;
 char bytes94[0xAC-0x94];TargetRef00217D4C ref;
 char bytesB4[0xC5-0xB4];bool flagged;char bytesC6[2];
};
class Rva004F6093Holder {
public:
 ArmySummaryEntry*value;
 __forceinline Rva004F6093Holder():value(0){}
 Rva004F6093Holder(const Rva004F6093Holder&);
 __forceinline ArmySummaryEntry*operator->()const{return value;}
 __forceinline Rva004F6093Holder(ArmySummaryEntry*p):value(p){if(value)++value->ref.references;}
 __forceinline ~Rva004F6093Holder(){if(value)ReleaseTreeHintRef00217D4C(&value->ref);}
};
class Rva0040CB11Entry {public:int key;Rva004F6093Holder value;};
namespace _STL {
template<> vector<Rva0040CB11Entry>::vector(const vector<Rva0040CB11Entry>&);
template<class I,class C>void sort(I,I,C);
template<class T,class A>class list;
}
class Rva001EB984Member {public:void*init(void*);};
class Rva001EB769 {public:void rva001EB769() throw();};
class FreelistProxyHead {public:void setup(const void*,void*);};
class FreelistPool {public:void*pop();};
extern FreelistPool g_freelistPool00DB8FEC;
// The visible constructor preserves the native unused-allocator argument
// placement. Its /Oy- COMDAT copy loses to the exact strong /O1 provider
// in StlportObjectFreelistListBaseCtor.cpp; no alternate body is called.
namespace _STL {
template<class T,class A>class _List_base;
template<>class _List_base<Object*,allocator<Object*> > {
public:
 _List_base(const allocator<Object*>&);
 __forceinline ~_List_base() throw(){((Rva001EB769*)this)->rva001EB769();}
 void*head;
};
__declspec(noinline) inline _List_base<Object*,allocator<Object*> >::_List_base(const allocator<Object*>&a)
{
 char dummy;((FreelistProxyHead*)this)->setup(&dummy,0);
 void*n=g_freelistPool00DB8FEC.pop();((void**)n)[0]=n;((void**)n)[1]=n;head=n;
}
template<>class list<Object*,allocator<Object*> > : public _List_base<Object*,allocator<Object*> > {
public:
 list(const allocator<Object*>&a=allocator<Object*>()):_List_base<Object*,allocator<Object*> >(a){}
 void push_back(Object*const&);
 bool empty()const{return *(void**)head==head;}
 Object*front()const{return ((LoadedObjectNode*)head)->next->value;}
};
}
typedef _STL::list<Object*,_STL::allocator<Object*> > LoadedObjectList;
class Rva0037F57E {
public:Rva0037F57E();virtual ~Rva0037F57E();
 void rva0037FD2B(LoadedObjectList*,class Rva002E2903Player*,struct Rva002B488EResult*,bool);
};
class Rva0040E0EB : public _STL::vector<Rva0040CB11Entry> {
public:Rva0040E0EB(const _STL::vector<Rva0040CB11Entry>&v):_STL::vector<Rva0040CB11Entry>(v){} ~Rva0040E0EB();
};
struct Rva0040F454Cmp {};
class Rva0040CF55Owner {public:int sumUnflagged()const;};
struct Rva0040E534Input {ArmySummaryEntry*value;};
class Rva0040E6D6Sub {public:void forward(int*);void*words[3];};
class Rva00318C32Ret {public:char bytes00[0x28];_STL::vector<AsciiString>delayed;};
class Rva00318C79Owner {public:Rva00318C32Ret*rva00318C32();};
struct Rva002B488EResult {char bytes00[0x54];int ownerID;__forceinline int getOwnerID()const{return ownerID;}};
class Rva002E2903Player {public:char bytes00[0x14];int playerID;};
class Rva002BA8F1Logic {
public:Rva002B488EResult*rva002B488E(int);Rva002E2903Player*find(int,unsigned*);
};
class LivingWorldLogic;
extern LivingWorldLogic*TheLivingWorldLogic;
class PlayerList {public:Player*Rva002A7A6F(int);};
extern PlayerList*ThePlayerList;
class PlayerTemplate {public:char bytes00[0xE8];_STL::vector<AsciiString>startingUnits;};
class Player {public:char bytes00[0x34];PlayerTemplate*tmplate;};
class ThingTemplate {
public:char bytes00[0x64];AsciiString name;
 char bytes68[0x110-0x68];unsigned flags110;
 char bytes114[0x618-0x114];int commandPoints;
};
class ThingFactory {public:const ThingTemplate*findTemplate(const AsciiString&);};
extern ThingFactory*TheThingFactory;
#include "../../Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
extern GameLogic*TheGameLogic;
class Rva0040D8D6List {public:~Rva0040D8D6List();void*begin,*end,*limit;unsigned index;};
struct ArmySummaryEntryRef{Rva004F6093Holder holder;ArmySummaryEntryRef(){}ArmySummaryEntryRef(const Rva004F6093Holder&h):holder(h){}};
class Rva0040CB3AIndexedField{public:int find(int)const;};
class Rva00376A62{public:char pad[8];_STL::vector<AsciiString>types;bool rva00376A62(const StringBase<char>&);};
namespace _STL{template<>vector<ObjectID>::iterator vector<ObjectID>::erase(iterator);}
class ArmySummary : public Snapshot, public Rva0040D8D6List {
public:ArmySummaryEntryRef GetEntry(int);
 ObjectID SpawnOneDelayedCarryoverUnit(Rva00376A62*);
 void Load(bool,bool,int);
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

ObjectID ArmySummary::SpawnOneDelayedCarryoverUnit(Rva00376A62*filter)
{
 if(filter->types.size()==0)return INVALID_OBJECT_ID;
 const _STL::vector<ObjectID>::iterator last=pending.end();
 for(_STL::vector<ObjectID>::iterator i=pending.begin();i!=last;){
  ArmySummaryEntryRef value=GetEntry((int)*i);
  ArmySummaryEntry*held=value.holder.value;
  if(held && filter->rva00376A62(*(StringBase<char>*)&held->templateName)){
   pending.erase(i);
   LoadedObjectList spawned;
   ObjectID result=INVALID_OBJECT_ID;
   LoadArmyEntry((Rva0040E534Input*)&value,held->count,&spawned,0);
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
