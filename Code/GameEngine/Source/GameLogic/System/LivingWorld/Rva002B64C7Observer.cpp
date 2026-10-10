// cl: /O1 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?method@Rva002B64C7Observer@@QAEXPAUBuildingView@@@Z @0x002B64C7, 240B (WB D7E9F0 names
// OnDestroyingBuilding). Receiver is the secondary +0x10 view of the logic (phase at +0xE4,
// find on this-0x10): when the phase is 0 and the building has a type and region, the owner
// player's army list is walked and every summary entry holding the building's key cancels
// its upgrades. The type is read into a named local so the zero test shares the zero
// register of the other tests. Address-derived class/helper names.
#include <vector>
class ModuleData;
class Rva004E0632 { public: int rva004E0632() const; };
struct RegionView { char pad[0x13c]; int player; int getPlayer() const { return player; } };
struct BuildingView { char pad00[0x18]; int key; char pad1c[8]; RegionView *region; int getType() const { return ((const Rva004E0632*)this)->rva004E0632(); } };
class Rva002E2903Player;
class AsciiString;
class Rva002BA8F1Logic { public: Rva002E2903Player *find(int,unsigned*); };
class Rva00318C32Ret;
class Rva002E2504 { public: bool rva002E2504(Rva00318C32Ret*,_STL::vector<const ModuleData*>*); };
class Rva0040CB2CIndexedField { public: int get(int) const; };
struct EntryView { char pad[0xbc]; int buildingKey; };
class ArmySummaryEntry { public: void CancelUpgrades(); };
struct SummaryView { char pad[0x40]; int begin,end; };
struct ArmyView { char pad[0x78]; SummaryView *summary; };
class Rva002B64C7Observer { public: void method(BuildingView *building); int getPhase() const { return phase; } private: char pad[0xe4]; int phase; };
void Rva002B64C7Observer::method(BuildingView *building)
{
 if (getPhase() != 0) return;
 int type = building->getType();
 if (type == 0) return;
 RegionView *region=building->region;
 if (!region) return;
 Rva002E2903Player *player=((Rva002BA8F1Logic *)((char *)this-0x10))->find(region->getPlayer(),0);
 if (!player) return;
 _STL::vector<const ModuleData*> armies;
 ((Rva002E2504*)player)->rva002E2504((Rva00318C32Ret*)region,&armies);
 int *span=(int*)&armies;
 for(unsigned i=0;i<(unsigned)((span[1]-span[0])>>2);++i) {
  ArmyView *army=(ArmyView*)armies[i];
  int count=(army->summary->end-army->summary->begin)>>3;
  for(int j=0;j<count;++j) {
   EntryView *entry=(EntryView*)((Rva0040CB2CIndexedField*)army->summary)->get(j);
   if(entry->buildingKey==building->key) ((ArmySummaryEntry*)entry)->CancelUpgrades();
  }
 }
}
