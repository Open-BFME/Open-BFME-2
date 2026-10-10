// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /D_STLP_USE_STATIC_LIB
// stlport
// WB12F0570 names applyResults, native4F7B6B..4F7D7F proves whole532B.
// Existing target providers retain their established names and ABI views.
#include <vector>
#include <map>
#include <stl/_tree.h>
void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void*);
struct TargetRef00217D4C {void *vtable; int references;};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
class ArmySummaryEntry {public:
 ArmySummaryEntry(const ArmySummaryEntry&);
 char unknown00[0x94]; int count94; char unknown98[0xAC-0x98];
 TargetRef00217D4C ref; int buildingB4; char unknownB8[0xC8-0xB8];
};
class Rva004F6093Holder {public:
 ArmySummaryEntry *value;
 Rva004F6093Holder(ArmySummaryEntry *v):value(v){if(value)++value->ref.references;}
 ~Rva004F6093Holder(){if(value)ReleaseTreeHintRef00217D4C(&value->ref);}
};
struct Rva004E0790Inner;
class ArmySummary {public: int AddArmyEntry(const Rva004F6093Holder&); void rva0040DED9(); char unknown00[0x2C]; int flag2C;};
struct Rva0040DD3ARef {void *value;};
class Rva002E34A9 {public:void rva002E34A9(const Rva0040DD3ARef&,int);};
class Rva002E2903Player;
struct Rva002B488EResult {char unknown00[0x54];int player54; __forceinline int GetPlayer() const{return player54;}};
struct Rva002B2579Result;
class Rva002BA8F1Logic {public:
 Rva002B488EResult *rva002B488E(int);
 Rva002E2903Player *find(int,unsigned int*);
 Rva002B2579Result *rva002B2579(int);
};
class Rva002B25BFOwner {public:bool rva002B25BF(int);};
class LivingWorldBuilding {public:void updateArmySummaryEntryRepresentation(const Rva004E0790Inner&);};
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva00380200 {public:bool rva003805BB(float,bool);};
class Rva004F5FD8 {public:
 Rva004F5FD8(const Rva004F5FD8&);
 virtual ~Rva004F5FD8(){}
 int word04,word08; float experience0C; int words10[7];
};
struct SummaryTreeNode:_STL::_Rb_tree_node_base {int key;ArmySummary *summary; __forceinline ArmySummary*Get()const{return summary;}};
struct ApplyPlayerRecord { std::map<int,ArmySummary*> summaries;char unknown0C[0x28-12];Rva004F5FD8 *experience28;int side2C;int unknown30; __forceinline Rva004F5FD8* GetExperience()const{return experience28;}};
struct SummaryPointerView {ArmySummary*value; __forceinline ArmySummary*Get()const{return value;}};
struct ApplyUnit {char unknown00[8];ArmySummaryEntry *entry;char unknown0C[0x28-0xC];SummaryPointerView summary; __forceinline const SummaryPointerView&GetSummary()const{return summary;}};
struct ApplyUnitRef {ApplyUnit *value; __forceinline ApplyUnit*operator->()const{return value;}};
struct ApplyDeadEntry {int army;Rva0040DD3ARef entry;};
class LivingWorldAutoResolveBattle {public:
 void applyResults();
 __forceinline ApplyPlayerRecord&GetPlayer(unsigned int i){return players[i];}
 __forceinline Rva004F5FD8 *GetExperience(unsigned int i)const{return experience48[i];}
 std::vector<ApplyPlayerRecord> players;
 std::vector<ApplyUnitRef> units[2];
 char unknown24[0x48-0x24]; std::vector<Rva004F5FD8*> experience48;
 char unknown54[0x60-0x54];std::vector<int> destroyed60;
 std::vector<ApplyDeadEntry> revival6C;char unknown78[4];int threshold7C;
};
// ?applyResults@LivingWorldAutoResolveBattle@@QAEXXZ
void LivingWorldAutoResolveBattle::applyResults() {
 for(int *it=destroyed60.begin(),*end=destroyed60.end();it!=end;++it)
  reinterpret_cast<Rva002B25BFOwner*>(TheLivingWorldLogic)->rva002B25BF(*it);
 for(ApplyDeadEntry *it=revival6C.begin(),*end=revival6C.end();it!=end;++it) {
  Rva002B488EResult *army=reinterpret_cast<Rva002BA8F1Logic*>(TheLivingWorldLogic)->rva002B488E(it->army);
  if(army) {
   Rva002E2903Player *player=reinterpret_cast<Rva002BA8F1Logic*>(TheLivingWorldLogic)->find(army->GetPlayer(),0);
   if(player) reinterpret_cast<Rva002E34A9*>(player)->rva002E34A9(it->entry,1);
  }
 }
 for(unsigned int i=0;i<players.size();++i) {
  if(GetPlayer(i).GetExperience() && GetExperience(i)) {
   Rva004F5FD8 *after=GetExperience(i);
   Rva004F5FD8 points(*GetPlayer(i).GetExperience());
   reinterpret_cast<Rva00380200*>(&points)->rva003805BB((float)(int)(after->experience0C-points.experience0C),false);
  }
  std::map<int,ArmySummary*>::iterator it=GetPlayer(i).summaries.begin();
  std::map<int,ArmySummary*>::iterator end=GetPlayer(i).summaries.end();
  for(;it!=end && it->first<=threshold7C;++it) {
   ArmySummary *summary=it->second;
   summary->flag2C=4;
   summary->rva0040DED9();
  }
 }
 for(int side=0;side<2;++side) {
  ApplyUnitRef *it=units[side].begin();
  ApplyUnitRef *end=units[side].end();
  for(;it!=end;++it) {
   if((*it)->summary.Get()) {
    ArmySummaryEntry *entry=(*it)->entry;
    Rva004F6093Holder holder(new ArmySummaryEntry(*entry));
    (*it)->GetSummary().Get()->AddArmyEntry(holder);
    ++entry->count94;
    ++holder.value->count94;
   }
   int id=(*it)->entry->buildingB4;
   if(id) {
    Rva002B2579Result *building=reinterpret_cast<Rva002BA8F1Logic*>(TheLivingWorldLogic)->rva002B2579(id);
    if(building) reinterpret_cast<LivingWorldBuilding*>(building)->updateArmySummaryEntryRepresentation(*reinterpret_cast<Rva004E0790Inner*>((*it)->entry));
   }
  }
 }
}
