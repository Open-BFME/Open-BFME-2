// ?Rva005E6A23@StrategicInGameUI@@YA?AUTreeHintRef00217D4C@@PBURva005E4300Entry@@@Z
// ?Rva005E6A23@StrategicInGameUI@@YA?AUTreeHintRef00217D4C@@PBURva005E4300Entry@@@Z
// cl: /I. /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc
// Native005E6B3E..005E6B8F obtains archetype at template+5C4 for the
// selected entry+18 and sends its Unicode tooltip to the owned Mouse API.
// Native005E4300..005E4389 low-byte comparator of selected hero keys;
// groupB8 signed order with zero priority then the native118B fallback.
// Its three private bodies are reconstructed from target; original template
// and record class names remain unknown. Public char describes the observed
// AL zero/one ABI without claiming the original C++ return spelling.
#include "ascii_string.h"
#include "unicode_string.h"
class ThingTemplate;
class ThingFactory { public: const ThingTemplate *findTemplate(const AsciiString &); };
extern ThingFactory *TheThingFactory;
struct Rva005E4300Entry {
 int key;
 AsciiString name;
 float metric;
 char pad[0xb8-0xc];
 int group;
};
struct Rva005E3967Template {
 char beforeDescription[0x40]; UnicodeString description; char toTitle[0x58-0x44]; UnicodeString title; char toMask[0x110-0x5C];unsigned int mask; char toArchetype[0x5C4-0x114];int archetype;__forceinline const UnicodeString&titleText()const{return title;} __forceinline const UnicodeString&descriptionText()const{return description;}
};
class Rva0040CB3AIndexedField { public: int get(int) const; };
struct Rva005E4300Context {
 char pad0[0x18]; AsciiString selectedName;
 char pad1[0x78-0x1c]; Rva0040CB3AIndexedField *index;
};
namespace StrategicInGameUI {
static __declspec(noinline) Rva005E3967Template *Rva005E3967(const Rva005E4300Entry *entry)
{
 return (Rva005E3967Template *)TheThingFactory->findTemplate(entry->name);
}
static __declspec(noinline) bool compareHeroEntries(const Rva005E4300Entry *a,const Rva005E4300Entry *b,int keyA,int keyB)
{
 bool flagA=((Rva005E3967(a)->mask>>26)&1)!=0;
 bool flagB=((Rva005E3967(b)->mask>>26)&1)!=0;
 if(flagA!=flagB)return flagA;
 if(!flagA) {
  int cmp=a->name.compare(b->name);
  if(cmp)return cmp<0;
 }
 if(a->metric!=b->metric)return a->metric>b->metric;
 return keyA<keyB;
}
}
class Rva005E4300Cmp {
public:
 char operator()(int,int) const;
private: Rva005E4300Context *m_context;
};
// Rva005E4300Cmp::operator(), Rva005E6B3E::rva005E6B3E and Rva005E6AD8::rva005E6AD8
// are rowed in StrategicInGameUIHeroComparator.cpp; this unit only declares them.
class Rva005E549E {public:void rva005E549E();};
class Rva005F6022ByteChaseField {public:unsigned char get()const;};
namespace StrategicInGameUI {UnicodeString GetTooltipText(int);}
struct RGBColor;class Mouse {public:void rva001EEA6D(UnicodeString,int,const RGBColor*,float);};extern Mouse*TheMouse;
class Rva005E6B3E {public:void updateTooltip();char unknown0[4];void*clip;char unknown8[0x10];Rva005E4300Entry*entry;};
struct TargetRef00217D4C {void*vtable;int count;};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
struct TreeHintRef00217D4C {
 TreeHintRef00217D4C(TargetRef00217D4C*target=0):m_ptr(target){if(target)++target->count;}
 ~TreeHintRef00217D4C(){if(m_ptr)ReleaseTreeHintRef00217D4C(m_ptr);}
 TreeHintRef00217D4C&operator=(const TreeHintRef00217D4C&);
 TargetRef00217D4C*m_ptr;
};
namespace StrategicInGameUI {TreeHintRef00217D4C Rva005E6A23(const Rva005E4300Entry*);}
class Rva003FE20FBase {public:virtual void slot1(void*);};
class Rva005E4157 {public:void rva005E4157(int);};
class Rva005E6AD8 {public:void rva005E6AD8();char pad0[4];void*clip;Rva003FE20FBase*owner;char padC[8];int value;Rva005E4300Entry*entry;TreeHintRef00217D4C held;};
// Native5E6CA1..5E6D0D, called by the listener constructor at5E6DFA.
// The caller consumes count then entry from the hidden return object.
// Context+78 is a summary whose8B entries begin40/end44; the two existing
// indexed providers yield its entry pointer and count. Field names describe
// target accesses; the original pair/context/summary class names are unknown.
class Rva0040CB2CIndexedField {public:int get(int) const;};
class Rva0040CC0EIndexedField {public:int get(int) const;};
struct HeroDetailsArmyEntry {int count;Rva005E4300Entry *entry;};
struct HeroDetailsArmySummary {char pad[0x40];HeroDetailsArmyEntry *begin,*end;};
struct HeroDetailsPair {
 HeroDetailsPair(){}
 HeroDetailsPair(const HeroDetailsPair &heroDetailsPair):count(heroDetailsPair.count),entry(heroDetailsPair.entry){}
 HeroDetailsPair(const int &c,Rva005E4300Entry *const &e):count(c),entry(e){}
 int count;Rva005E4300Entry *entry;
};
// StrategicInGameUI::Rva005E6CA1 is rowed in StrategicInGameUIHeroComparator.cpp.

class Rva0037DCA5 {public:void *GetThingTemplate();};
class InGameSimpleHelp {public:InGameSimpleHelp(const UnicodeString&,const UnicodeString&);virtual ~InGameSimpleHelp();int count;void*impl;};
namespace StrategicInGameUI {
TreeHintRef00217D4C Rva005E6A23(const Rva005E4300Entry*entry) {
 Rva005E3967Template *t=(Rva005E3967Template *)Rva005E3967(entry);
 Rva005E3967Template *t2=t;
 const UnicodeString &title=t2->titleText();
 const UnicodeString *titleAddress=&title;
 bool bEmpty = titleAddress->isEmpty();
 if(bEmpty == false) {
  t=(Rva005E3967Template *)((Rva0037DCA5 *)entry)->GetThingTemplate();
  if(t) {
   const UnicodeString &description=t->descriptionText();
   return TreeHintRef00217D4C((TargetRef00217D4C *)new InGameSimpleHelp(title,description));
  } else {
   return TreeHintRef00217D4C();
  }
 }
 return TreeHintRef00217D4C();
}
}
