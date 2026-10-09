// cl: /O1 /Oy- /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/moduledata /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// WB108A7E0 ArmySummary::Load semantic and identity evidence; BF1/ZH have
// no reusable ArmySummary source. Existing BFME2 summary/ref/vector providers
// establish the layouts and calls used below. All target deltas are native.
#include "ascii_string.h"
#include <vector>
#define BFME_SNAPSHOT_NAME_SLOT 1
#include "Common/Snapshot.h"
class Player;
class Object;
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
#include "../../Common/GameLogicObjectLookupView.h"
extern GameLogic*TheGameLogic;
class Rva0040D8D6List {public:~Rva0040D8D6List();void*begin,*end,*limit;unsigned index;};
class ArmySummary : public Snapshot, public Rva0040D8D6List {
public:void Load(bool,bool,int);
 void LoadArmyEntry(Rva0040E534Input*,int,LoadedObjectList*,int);
private:
 bool flag14;char gap15[3];AsciiString name18;int armyID;AsciiString name20;
 char bytes24[0x40-0x24];
 _STL::vector<Rva0040CB11Entry>entries;Rva0040E6D6Sub delayed;
 char bytes58[8];int at60;
};
void ArmySummary::Load(bool battle,bool first,int overrideID)
{
 ArmySummary*self=this;
 Rva0037F57E placer;
 LoadedObjectList loaded;
 int required=self->at60;
 bool includeFlagged=false;bool postpone;
 if(required>0 && required>((Rva0040CF55Owner*)self)->sumUnflagged())includeFlagged=true;
 Rva0040E0EB saved(self->entries);
 _STL::sort(saved.begin(),saved.end(),Rva0040F454Cmp());
 Rva002B488EResult*army=((Rva002BA8F1Logic*)TheLivingWorldLogic)->rva002B488E(self->armyID);
 if(!army)return;
 Rva002E2903Player*lwPlayer=((Rva002BA8F1Logic*)TheLivingWorldLogic)->find(army->getOwnerID(),0);
 if(!lwPlayer)return;
 Player*player=ThePlayerList->Rva002A7A6F(lwPlayer->playerID);
 if(!player)return;
 Rva00318C32Ret*region=((Rva00318C79Owner*)army)->rva00318C32();
 // Native lazy static vector at E02FB0 and guard E02FBC. The current
 // data ledger still calls its old dump declaration g_Va00E02FB0 unsigned;
 // retain the proven vector lifetime rather than that incomplete data type.
 static _STL::vector<AsciiString>empty;
 const _STL::vector<AsciiString>&delayedNames=region?region->delayed:empty;
 int budget=1000000;
 for(int pass=0;pass<2;++pass){
  for(unsigned index=0;index<saved.size();++index){
   if(saved[index].value->flagged && !includeFlagged)continue;
   const ThingTemplate*definition=TheThingFactory->findTemplate(saved[index].value->templateName);
   if(!definition)continue;
   unsigned firstKind=(definition->flags110>>26)&1;
   if(firstKind!=(pass==0))continue;
   _STL::vector<AsciiString>::const_iterator current=delayedNames.begin(),end=delayedNames.end();
   postpone=false;
   while(!postpone && current!=end){if(current->compare(definition->name)==0)postpone=true;++current;}
   if(postpone){self->delayed.forward(&saved[index].key);continue;}
   int count=saved[index].value->count;
   if(definition->commandPoints>0 && pass>0)count=budget/definition->commandPoints;
   if(count>saved[index].value->count)count=saved[index].value->count;
   if(count>0){budget-=count*definition->commandPoints;
    self->LoadArmyEntry((Rva0040E534Input*)&saved[index].value,count,&loaded,0);
   }
  }
 }
 if(TheGameLogic->m_114!=3 && battle && first){
  PlayerTemplate*tmplate=player->tmplate;
  for(unsigned index=0;index<tmplate->startingUnits.size();++index){
   Rva004F6093Holder entry(new ArmySummaryEntry);
   entry->templateName=tmplate->startingUnits[index];
   entry->count=1;
   self->LoadArmyEntry((Rva0040E534Input*)&entry,1,&loaded,overrideID);
  }
 }
 if(!loaded.empty())placer.rva0037FD2B(&loaded,lwPlayer,army,!battle);
}

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
