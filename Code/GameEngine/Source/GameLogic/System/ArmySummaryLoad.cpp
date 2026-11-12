// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /DBFME_ASCII_DTOR_DECL /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/moduledata /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
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
// Native DB8FEC freelist policy is distinct from the generic 41B allocator.
template<class T>class Rva001EB984PoolAllocator {};
#include "../../../../Libraries/Source/Apt/AptRefTarget.h"
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
#include "../../../Include/Common/ArmySummaryEntry.h"
class Rva004F6093Holder {
public:
 ArmySummaryEntry*value;
 __forceinline ArmySummaryEntry*operator->()const{return value;}
 __forceinline Rva004F6093Holder(ArmySummaryEntry*armySummaryEntry):value(armySummaryEntry){if(value)++value->Rva0007DF07::m_04;}
 __forceinline ~Rva004F6093Holder(){if(value)ReleaseTreeHintRef00217D4C(reinterpret_cast<TargetRef00217D4C *>(static_cast<Rva0007DF07 *>(value)));}
};
class Rva0040CB11Entry {public:int key;Rva004F6093Holder value;};
namespace _STL {
// Keep the existing entry-destruction providers; this /Oy- caller needs no
// new out-of-line copies of their /O1 template machinery.
template<> void _Destroy<Rva0040CB11Entry>(Rva0040CB11Entry*);
template<> void __destroy_aux<Rva0040CB11Entry*>(Rva0040CB11Entry*,Rva0040CB11Entry*,const __false_type&);
template<> void __destroy<Rva0040CB11Entry*,Rva0040CB11Entry>(Rva0040CB11Entry*,Rva0040CB11Entry*,Rva0040CB11Entry*);
template<> void _Destroy<Rva0040CB11Entry*>(Rva0040CB11Entry*,Rva0040CB11Entry*);
template<> vector<Rva0040CB11Entry>::vector(const vector<Rva0040CB11Entry>&);
template<class I,class C>void sort(I,I,C);
template<class T,class A>class list;
}
class FreelistProxyHead {public:void setup(const void*,void*);};
#include "../../../Include/Common/FreelistPool.h"
extern FreelistPool g_freelistPool00DB8FEC;
// The visible constructor preserves the native unused-allocator argument
// placement. Its /Oy- COMDAT copy loses to the exact strong /O1 provider
// in StlportObjectFreelistListBaseCtor.cpp; no alternate body is called.
namespace _STL {
template<class T,class A>class _List_base;
template<>class _List_base<Object*,Rva001EB984PoolAllocator<Object*> > {
public:
 _List_base(const Rva001EB984PoolAllocator<Object*>&);
 ~_List_base() throw(); // pinned 0x001EB769 body, emitted by HordeContainRva00475F61.cpp
 void*head;
};
__declspec(noinline) inline _List_base<Object*,Rva001EB984PoolAllocator<Object*> >::_List_base(const Rva001EB984PoolAllocator<Object*>&a)
{
 char dummy;((FreelistProxyHead*)this)->setup(&dummy,0);
 void*n=g_freelistPool00DB8FEC.pop();((void**)n)[0]=n;((void**)n)[1]=n;head=n;
}
template<>class list<Object*,allocator<Object*> > {public:void push_back(Object*const&);};
// Same verified circular-header wire ABI; the existing26B append worker
// owns native Object node allocation. No generic constructor is used here.
template<>class list<Object*,Rva001EB984PoolAllocator<Object*> > : public _List_base<Object*,Rva001EB984PoolAllocator<Object*> > {
public:
 list(const Rva001EB984PoolAllocator<Object*>&a=Rva001EB984PoolAllocator<Object*>()):_List_base<Object*,Rva001EB984PoolAllocator<Object*> >(a){}
 void push_back(Object *const &v); // pinned 0x001EC03C body, emitted by HordeContainRva00475F61.cpp
 bool empty()const{return *(void**)head==head;}
};
}
typedef _STL::list<Object*,Rva001EB984PoolAllocator<Object*> > LoadedObjectList;
class Rva0037F57E {
public:Rva0037F57E();virtual ~Rva0037F57E();
 void rva0037FD2B(LoadedObjectList*,class Rva002E2903Player*,struct Rva002B488EResult*,bool);
};
class Rva0040E0EB : public _STL::vector<Rva0040CB11Entry> {
public:Rva0040E0EB(const _STL::vector<Rva0040CB11Entry>&v):_STL::vector<Rva0040CB11Entry>(v){} ~Rva0040E0EB();
};
struct Rva0040F454Cmp {};
class Rva0040CF55Owner {public:int sumUnflagged()const;};
// The entry lookup is the rowed ArmySummaryEntry::rva0040C495 0x0040C495.
struct Rva0040E534Input {ArmySummaryEntry*value;};
// The delayed-key append is the rowed four-byte vector push_back 0x002E01C6
// (ICF-shared; bound through the vector<NameKeyType> row).
enum NameKeyType { NAMEKEY_INVALID = 0 };
namespace _STL { template <> void vector<NameKeyType, allocator<NameKeyType> >::push_back(const NameKeyType &); }
typedef _STL::vector<NameKeyType> Rva0040E6D6Sub;
class Rva00318C32Ret {public:char bytes00[0x28];_STL::vector<AsciiString>delayed;};
#include "../../../Include/GameLogic/Rva00318C79Owner.h"
struct Rva002B488EResult {char bytes00[0x54];int ownerID;__forceinline int getOwnerID()const{return ownerID;}};
class Rva002E2903Player {public:char bytes00[0x14];int playerID;};
#include "../../../Include/GameLogic/Rva002BA8F1Logic.h"
class LivingWorldLogic;
extern LivingWorldLogic*TheLivingWorldLogic;
#include "../../../Include/Common/PlayerList.h"
extern PlayerList*ThePlayerList;
class PlayerTemplate {public:char bytes00[0xE8];_STL::vector<AsciiString>startingUnits;};
class Player {public:char bytes00[0x34];PlayerTemplate*tmplate;};
#include "../../../Include/Common/ThingTemplate.h"
#include "../../../Include/Common/ThingFactory.h"
extern ThingFactory*TheThingFactory;
#include "../../Common/GameLogicObjectLookupView.h"
// bfme link decl-only begin
namespace _STL { template <> vector<Rva0040CB11Entry, allocator<Rva0040CB11Entry> >::vector(vector<Rva0040CB11Entry, allocator<Rva0040CB11Entry> > const &); }
// bfme link decl-only end

// A declaration-only specialization stops this TU emitting its own
// vector<AsciiString> dtor COMDAT, so the call binds the kept copy.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
template <> void allocator<AsciiString>::deallocate(AsciiString*, size_t) const;
}
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
   if(saved[index].value->m_c5 && !includeFlagged)continue;
   const ThingTemplate*definition=TheThingFactory->findTemplate(saved[index].value->m_name);
   if(!definition)continue;
   unsigned firstKind=(definition->m_kindof[2]>>26)&1;
   if(firstKind!=(pass==0))continue;
   _STL::vector<AsciiString>::const_iterator current=delayedNames.begin(),end=delayedNames.end();
   postpone=false;
   while(!postpone && current!=end){if(current->compare(definition->m_nameString)==0)postpone=true;++current;}
   if(postpone){self->delayed.push_back(*(const NameKeyType*)&saved[index].key);continue;}
   int count=saved[index].value->m_90;
   if(definition->m_commandPoints>0 && pass>0)count=budget/definition->m_commandPoints;
   if(count>saved[index].value->m_90)count=saved[index].value->m_90;
   if(count>0){budget-=count*definition->m_commandPoints;
    self->LoadArmyEntry((Rva0040E534Input*)&saved[index].value,count,&loaded,0);
   }
  }
 }
 if(TheGameLogic->m_114!=3 && battle && first){
  PlayerTemplate*playerTemplate=player->tmplate;
  for(unsigned index=0;index<playerTemplate->startingUnits.size();++index){
   Rva004F6093Holder entry(new ArmySummaryEntry);
   entry->m_name=playerTemplate->startingUnits[index];
   entry->m_90=1;
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
