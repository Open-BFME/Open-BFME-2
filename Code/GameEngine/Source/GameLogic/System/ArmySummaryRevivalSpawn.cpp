// ?SpawnOneDelayedCarryoverUnitIntoUnitRevivalTracker@ArmySummary@@QAE_NPAVObjectTypes@@@Z
// Native40D701..40D82F RET4; WB named caller3CA14C identifies the revival operation.
// Visible existing GetEntry/holder copy agrees with native hidden-handle escape.
// Failed record-copy scope exit destroys the record before queue advancement.
// The result becomes live after record teardown, preserving native branch layout.
// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/moduledata /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// WB named ScriptActions caller3CA14C and native ArmySummary operation evidence; BF1/ZH have
// no reusable ArmySummary source. Existing BFME2 summary/ref/vector providers
// establish the layouts and calls used below. All target deltas are native.
#include "ascii_string.h"
#include <vector>
#define BFME_SNAPSHOT_NAME_SLOT 1
#include "Common/Snapshot.h"
class Player;
class Object;
#include "../../Common/GameLogicObjectLookupView.h"
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
class Rva0040D8D6List {public:~Rva0040D8D6List();void*begin,*end,*limit;unsigned index;};
struct ArmySummaryEntryRef{Rva004F6093Holder holder;ArmySummaryEntryRef(){}ArmySummaryEntryRef(const Rva004F6093Holder&h):holder(h){}};
class Rva0040CB3AIndexedField{public:int find(int)const;};
class ObjectTypes{public:char pad[8];_STL::vector<AsciiString>types;};
class Rva00376A62{public:bool rva00376A62(const StringBase<char>&);};
namespace _STL{template<>vector<ObjectID>::iterator vector<ObjectID>::erase(iterator);}
struct UnitRevivalEntry { UnitRevivalEntry(); ~UnitRevivalEntry(); unsigned char opaque[0xD8]; };
struct Rva002E2D10Record { unsigned char opaque[0xD8]; };
class UnitRevivalTracker {public:void addRevivableUnit(const Rva002E2D10Record&,Player*);};
class Player {public:UnitRevivalTracker*getUnitRevivalTracker(){return &tracker;}private:unsigned char opaque[0x738];UnitRevivalTracker tracker;};
class Rva0040C4CB {public:unsigned char rva0040C4CB(void*,int);};
class ArmySummary : public Snapshot, public Rva0040D8D6List {
public:ArmySummaryEntryRef GetEntry(int);
 bool SpawnOneDelayedCarryoverUnitIntoUnitRevivalTracker(ObjectTypes*);
private:
 bool flag14;char gap15[3];AsciiString name18;int armyID;AsciiString name20;
 char bytes24[0x40-0x24];
 _STL::vector<Rva0040CB11Entry>entries;_STL::vector<ObjectID>pending;
 char bytes58[8];int at60;
};
Player*Rva0040C94ALookup(int);
__declspec(noinline) inline ArmySummaryEntryRef ArmySummary::GetEntry(int key){
 int index=((const Rva0040CB3AIndexedField*)this)->find(key);
 if(index<0)return ArmySummaryEntryRef();
 return ArmySummaryEntryRef(entries.begin()[index].value);
}

bool ArmySummary::SpawnOneDelayedCarryoverUnitIntoUnitRevivalTracker(ObjectTypes*types)
{
 if(types->types.size()==0)return false;
 const _STL::vector<ObjectID>::iterator last=pending.end();
 for(_STL::vector<ObjectID>::iterator i=pending.begin();i!=last;){
  ArmySummaryEntryRef ref=GetEntry((int)*i);
  ArmySummaryEntry*target=ref.holder.value;
  if(target && reinterpret_cast<Rva00376A62*>(types)->rva00376A62(*(StringBase<char>*)&target->templateName)){
   pending.erase(i);
   Player*player=Rva0040C94ALookup(armyID);
   bool result;
   if(!player)result=false;
   else {
    UnitRevivalTracker*tracker=player->getUnitRevivalTracker();
    if(!tracker)result=false;
    else {
     {
      UnitRevivalEntry entry;
      if(!((Rva0040C4CB*)ref.holder.value)->rva0040C4CB(&entry,armyID))goto advance;
      tracker->addRevivableUnit(*(const Rva002E2D10Record*)&entry,player);
     }
     result=true;
    }
   }
   return result;
  }
 advance:
  ++i;
 }
 return false;
}
