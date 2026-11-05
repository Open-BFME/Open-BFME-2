// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// Native59B1EC..59B2EC256B RET12; WB14D5A60 names this constructor
// at its AutoResolve home line40. Retail reinforcement helper4F9658
// independently allocates52B and passes the entry holder, unsigned player
// and ArmySummary. Target accesses prove refcount4, owned entry8, float
// slotsC/10/14, flag18, word1C, reference20, tracker24, army28, template2C
// and player30. Names of the three float states and unaccessed bytes remain
// inferred storage roles. Existing121B ArmySummaryEntry copy provesC8 size;
// tracker ctor113 proves3C. All callees use current whole-body owners.
// The21B pointer constructor at2B2F0C must be called as a constructor:
// a setter-method shim changes the parent lifetime and register schedule.
// The inherited ref base is the existing Rva0007DF07 view. Its real virtual
// destructor emits the same seven-byte reset as the admitted base cleanup.
// Unit destructor and sole scalar slot are verified under the same real
// class in Rva0059B072Dtor.cpp. A whole-tree link remains separate evidence.
#include "ascii_string.h"
#include "../../../../../../Libraries/Source/Apt/AptRefTarget.h"
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
class ThingTemplate;class ArmySummary;
#include "../../../../../Include/Common/ArmySummaryEntry.h"
struct Rva0040DC56Element {ArmySummaryEntry *entry;};
class Rva004F6093Holder {
public:
 __declspec(noinline) Rva004F6093Holder(ArmySummaryEntry *);
 ~Rva004F6093Holder(){if(entry)ReleaseTreeHintRef00217D4C(reinterpret_cast<TargetRef00217D4C *>(static_cast<Rva0007DF07 *>(entry)));}
 ArmySummaryEntry *entry;
};
class LivingWorldAutoResolveUnit;
class ExperienceTrackerAutoResolve {public:ExperienceTrackerAutoResolve(LivingWorldAutoResolveUnit *,const Rva004F6093Holder &); char opaque[0x3C];};
class Rva005DB023 {public:void rva005DB023();};
#include "../../../../../Include/Common/ThingFactory.h"
extern ThingFactory *TheThingFactory;
#include "../../../../../Include/Common/Rva0007DF07.h"
struct AutoResolveTargetHolder {
 TargetRef00217D4C *value;
 AutoResolveTargetHolder():value(0){}
 ~AutoResolveTargetHolder(){if(value)ReleaseTreeHintRef00217D4C(value);}
};
class LivingWorldAutoResolveUnit:public Rva0007DF07 {
public:
 LivingWorldAutoResolveUnit(const Rva0040DC56Element &,unsigned,ArmySummary *);
 virtual ~LivingWorldAutoResolveUnit();
 float rva0059AEBC(); // max hitpoints for the entry level (0x0059AEBC)
 Rva004F6093Holder entry;
 float hitpoints,current,maximum;
 bool flag18;
 int unknown1C;
 AutoResolveTargetHolder holder20;
 ExperienceTrackerAutoResolve *tracker;
 ArmySummary *army;
 const ThingTemplate *thing;
 unsigned player;
};
LivingWorldAutoResolveUnit::LivingWorldAutoResolveUnit(const Rva0040DC56Element &source,unsigned p,ArmySummary *armySummary)
 :entry(new ArmySummaryEntry(*source.entry)),hitpoints(0.0f),current(0.0f),maximum(0.0f),flag18(false),unknown1C(0),army(armySummary),player(p) {
 thing=TheThingFactory->findTemplate(*(const AsciiString *)((const char *)source.entry+4));
 tracker=new ExperienceTrackerAutoResolve(this,entry);
 ((Rva005DB023 *)tracker)->rva005DB023();
 if(!thing) {hitpoints=0.0f;current=0.0f;maximum=0.0f;}
 else current=hitpoints=maximum=rva0059AEBC();
}

// Keep the owned21B constructor visible (outlined) so the compiler sees
// its entry/count writes. It is rehomed from Rva002B2F0CSet.cpp with the
// same whole body; this is the same real name, not an alias.
inline Rva004F6093Holder::Rva004F6093Holder(ArmySummaryEntry *armySummaryEntry):entry(armySummaryEntry) {
 if(armySummaryEntry) ++armySummaryEntry->Rva0007DF07::m_04;
}
