// ?ConsumeGarrisonUnitsFromRTS@@YAXPAVRva002BC1DAUnit@@PAURva002BC1DAArmy@@PAVLivingWorldBattle@@@Z
// cl: /O1 /G7 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// WB D826E0 named ConsumeGarrisonUnitsFromRTS and native2BBD52..2BC1DA.
// No BFME1/ZH garrison settlement source exists at verified donor575ba2b04.
// Native8B summary records and4B owning holders use existing BFME2 providers.
// Unnamed helper receivers remain explicit address views; no new pins.
#include <vector>
#include <algorithm>
#include "ascii_string.h"
struct TargetRef00217D4C {void*vt;int references;};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
class ArmySummaryEntry {public: char bytes00[4];AsciiString name;char bytes08[0xAC-8];TargetRef00217D4C ref;};
class Rva004F6093Holder {public:
 ArmySummaryEntry*value;
 Rva004F6093Holder(const Rva004F6093Holder&);
 Rva004F6093Holder&operator=(const Rva004F6093Holder&);
 __forceinline ~Rva004F6093Holder(){if(value)ReleaseTreeHintRef00217D4C(&value->ref);}
};
struct ArmySummaryEntryRef {ArmySummaryEntry*value;__forceinline ~ArmySummaryEntryRef(){if(value)ReleaseTreeHintRef00217D4C(&value->ref);}};
struct HeroEntryKey {char opaque[4];};
class AttackOrdersMember;
class Rva00318FC6;
class Rva00319028;
class Rva00319924 {public:int count(const AsciiString&);};
class Rva0031979COwner {public:void rva0031979C(int);};
class Rva00318FBE {public:int rva00318FBE();};
class LivingWorldArmy {public:void rva00319EA3(LivingWorldArmy*,ArmySummaryEntry*);};
class Rva0037DCA5 {public:int rva0037DCA5();void*rva0037DC52();};
class Rva003190A5 {public:bool query()const;};
class Rva0040CB2CIndexedField {public:int get(int)const;};
class Rva0040DB0ERegistry {public:int rva0040DB0E(const AsciiString&);};
class BfmeY1038 {public:int bfmeVal1038();};
struct Rva0040DC56Element {ArmySummaryEntry*value;__forceinline ArmySummaryEntry*Get()const{return value;}};
struct Record {int key;ArmySummaryEntry*value;};
class ArmySummary {public:__forceinline int entryCount()const{return records.size();}void GetEntries(_STL::vector<Rva0040DC56Element>&);ArmySummaryEntryRef GetEntry(int);char pad[0x40];_STL::vector<Record> records;};
struct SummaryHolder {ArmySummary*value;__forceinline ArmySummary*Get()const{return value;}};
class Rva002BC1DAUnit {public:char pad00[0x18];AsciiString name;char pad1C[0x78-0x1C];SummaryHolder summary;};
struct Rva002BC1DAArmy {char bytes[0x38];};
class LivingWorldBattle {public:int rva003F4752(void*);int rva003F4FAA(int,void*);int rva003F48FE(int,int,int);int rva003F4921(int,int,int);};
class Rva003F4DCA {public:int rva003F4DCA(int,int);};
class ThingTemplate {public:char pad00[0x113];unsigned char heroFlags;char pad114[0x5C4-0x114];int kind;};
class ThingFactory {public:const ThingTemplate*findTemplate(const AsciiString&);};
extern ThingFactory*TheThingFactory;
class Rva002B6066 {public:Rva0040DC56Element*rva002B6066(Rva0040DC56Element*);};
struct Rva002BBC1CCmp {bool operator()(const Rva004F6093Holder&,const Rva004F6093Holder&)const;};
namespace _STL {
template<>void sort<Rva004F6093Holder*,Rva002BBC1CCmp>(Rva004F6093Holder*,Rva004F6093Holder*,Rva002BBC1CCmp);
template<>vector<Rva0040DC56Element>::~vector();
}
class Rva0040CC0EIndexedField {public:int get(int)const;};
class AttackOrdersMember {public:ArmySummaryEntryRef rva0031996D(const HeroEntryKey&);char prefix[0x78];SummaryHolder summary;};
class Rva00318FC6 {public:int rva00318FC6(int,int);char prefix[0x78];SummaryHolder summary;};
class Rva00319028 {public:ArmySummaryEntryRef rva00319028(int,int);char prefix[0x78];SummaryHolder summary;};
// Native318FC6..319028 RET8, WB102B970 unnamed counter; every tested entry
// comes through owned40CB2C and37DC52/37DCA5; no original identifiers inferred.
// ?rva00318FC6@Rva00318FC6@@QAEHHH@Z
int Rva00318FC6::rva00318FC6(int kind,int maxCP){
 int count=0;
 for(int i=0;i<(int)summary.Get()->records.size();++i){
  ThingTemplate*thing=(ThingTemplate*)((Rva0037DCA5*)((Rva0040CB2CIndexedField*)summary.Get())->get(i))->rva0037DC52();
  if(thing->kind==kind&&((Rva0037DCA5*)((Rva0040CB2CIndexedField*)summary.Get())->get(i))->rva0037DCA5()<=maxCP)++count;
 }
 return count;
}
// Native319028..3190A5 RET0C (hidden owning holder + two integers).
// WB102BA30 independently proves reverse search and first-entry fallback.
// ?rva00319028@Rva00319028@@QAE?AUArmySummaryEntryRef@@HH@Z
ArmySummaryEntryRef Rva00319028::rva00319028(int kind,int maxCP){
 for(int i=(int)summary.Get()->records.size()-1;i>=0;--i){
  ThingTemplate*thing=(ThingTemplate*)((Rva0037DCA5*)((Rva0040CB2CIndexedField*)summary.Get())->get(i))->rva0037DC52();
  if(thing->kind==kind&&((Rva0037DCA5*)((Rva0040CB2CIndexedField*)summary.Get())->get(i))->rva0037DCA5()<=maxCP){
   int id=((Rva0040CC0EIndexedField*)summary.Get())->get(i);
   return summary.Get()->GetEntry(id);
  }
 }
 return summary.Get()->GetEntry(((Rva0040CC0EIndexedField*)summary.Get())->get(0));
}

// Native31996D..3199D2 RET8, hidden owning result + existing opaque key.
// Name comparison over the one-word key is observed in retail and WB102B870.
// ?rva0031996D@AttackOrdersMember@@QAE?AUArmySummaryEntryRef@@ABUHeroEntryKey@@@Z
ArmySummaryEntryRef AttackOrdersMember::rva0031996D(const HeroEntryKey&key){
 for(int i=(int)summary.Get()->records.size()-1;i>=0;--i){
  ArmySummaryEntry*entry=(ArmySummaryEntry*)((Rva0040CB2CIndexedField*)summary.Get())->get(i);
  if(entry->name.compare(*(const AsciiString*)&key)==0){
   int id=((Rva0040CC0EIndexedField*)summary.Get())->get(i);
   return summary.Get()->GetEntry(id);
  }
 }
 return summary.Get()->GetEntry(((Rva0040CC0EIndexedField*)summary.Get())->get(0));
}
