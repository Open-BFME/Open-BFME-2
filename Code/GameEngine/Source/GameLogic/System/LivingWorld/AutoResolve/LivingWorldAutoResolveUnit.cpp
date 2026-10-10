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
// Unit destructor/vtable currently live under neutral Rva0059B072 owners;
// their reconciliation remains separate linking work, not a link assertion.
#include "ascii_string.h"
struct TargetRef00217D4C {virtual void *destroy(unsigned); int references;};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
class ThingTemplate;class ArmySummary;
class ArmySummaryEntry {public: ArmySummaryEntry(const ArmySummaryEntry &); char opaque[0xAC]; TargetRef00217D4C reference; char rest[0xC8-0xB4];};
struct Rva0040DC56Element {ArmySummaryEntry *entry;};
class Rva004F6093Holder {
public:
 __declspec(noinline) Rva004F6093Holder(ArmySummaryEntry *);
 ~Rva004F6093Holder(){if(entry)ReleaseTreeHintRef00217D4C(&entry->reference);}
 ArmySummaryEntry *entry;
};
class LivingWorldAutoResolveUnit;
class ExperienceTrackerAutoResolve {public:ExperienceTrackerAutoResolve(LivingWorldAutoResolveUnit *,const Rva004F6093Holder &); char opaque[0x3C];};
class Rva005DB023 {public:void rva005DB023();};
class Rva0059AEBC {public:float rva0059AEBC();};
class ThingFactory {public:const ThingTemplate *findTemplate(const AsciiString &);};
extern ThingFactory *TheThingFactory;
class Rva0007DF07 {
public:
 __forceinline Rva0007DF07():references(0){}
 virtual ~Rva0007DF07(){}
 int references;
};
struct AutoResolveTargetHolder {
 TargetRef00217D4C *value;
 AutoResolveTargetHolder():value(0){}
 ~AutoResolveTargetHolder(){if(value)ReleaseTreeHintRef00217D4C(value);}
};
class LivingWorldAutoResolveUnit:public Rva0007DF07 {
public:
 LivingWorldAutoResolveUnit(const Rva0040DC56Element &,unsigned,ArmySummary *);
 virtual ~LivingWorldAutoResolveUnit();
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
LivingWorldAutoResolveUnit::LivingWorldAutoResolveUnit(const Rva0040DC56Element &source,unsigned p,ArmySummary *a)
 :entry(new ArmySummaryEntry(*source.entry)),hitpoints(0.0f),current(0.0f),maximum(0.0f),flag18(false),unknown1C(0),army(a),player(p) {
 thing=TheThingFactory->findTemplate(*(const AsciiString *)((const char *)source.entry+4));
 tracker=new ExperienceTrackerAutoResolve(this,entry);
 ((Rva005DB023 *)tracker)->rva005DB023();
 if(!thing) {hitpoints=0.0f;current=0.0f;maximum=0.0f;}
 else current=hitpoints=maximum=((Rva0059AEBC *)this)->rva0059AEBC();
}

// Keep the owned21B constructor visible (outlined) so the compiler sees
// its entry/count writes. It is rehomed from Rva002B2F0CSet.cpp with the
// same whole body; this is the same real name, not an alias.
Rva004F6093Holder::Rva004F6093Holder(ArmySummaryEntry *p):entry(p) {
 if(p) ++p->reference.references;
}
