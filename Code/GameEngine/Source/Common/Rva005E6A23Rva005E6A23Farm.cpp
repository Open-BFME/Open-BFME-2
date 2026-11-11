// ?Rva005E6A23@StrategicInGameUI@@YA?AUTreeHintRef00217D4C@@PBURva005E4300Entry@@@Z
// ?Rva005E6A23@StrategicInGameUI@@YA?AUTreeHintRef00217D4C@@PBURva005E4300Entry@@@Z
// cl: /I. /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
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
#include "../../Include/Common/ThingFactory.h"
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
#include "../../Include/Common/Rva0040CB3AIndexedField.h"
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
#include "../../../Libraries/Source/WWVegas/WWLib/Rva005E4300Cmp.h"
// Rva005E4300Cmp::operator(), Rva005E6B3E::rva005E6B3E and Rva005E6AD8::rva005E6AD8
// are rowed in StrategicInGameUIHeroComparator.cpp; this unit only declares them.
namespace StrategicInGameUI {UnicodeString GetTooltipText(int);}
struct RGBColor;class Mouse {public:void rva001EEA6D(UnicodeString,int,const RGBColor*,float);};extern Mouse*TheMouse;
class Rva005E6B3E {public:void updateTooltip();char unknown0[4];void*clip;char unknown8[0x10];Rva005E4300Entry*entry;};
#include "../../../Libraries/Source/Apt/AptRefTarget.h"
inline TreeHintRef00217D4C::~TreeHintRef00217D4C() {if(m_ptr)ReleaseTreeHintRef00217D4C(m_ptr);}
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);

namespace StrategicInGameUI {TreeHintRef00217D4C Rva005E6A23(const Rva005E4300Entry*);}
class Rva003FE20FBase {public:virtual void slot1(void*);};
class Rva005E6AD8 {public:void rva005E6AD8();char pad0[4];void*clip;Rva003FE20FBase*owner;char padC[8];int value;Rva005E4300Entry*entry;TreeHintRef00217D4C held;};
// Native5E6CA1..5E6D0D, called by the listener constructor at5E6DFA.
// The caller consumes count then entry from the hidden return object.
// Context+78 is a summary whose8B entries begin40/end44; the two existing
// indexed providers yield its entry pointer and count. Field names describe
// target accesses; the original pair/context/summary class names are unknown.
// StrategicInGameUI::Rva005E6CA1 is rowed in StrategicInGameUIHeroComparator.cpp.

#include "../../Include/Common/Rva0037DCA5.h"
class InGameSimpleHelp {public:InGameSimpleHelp(const UnicodeString&,const UnicodeString&);virtual ~InGameSimpleHelp();int count;void*impl;};
namespace StrategicInGameUI {
TreeHintRef00217D4C Rva005E6A23(const Rva005E4300Entry*entry) {
 Rva005E3967Template *thingTemplate=(Rva005E3967Template *)Rva005E3967(entry);
 Rva005E3967Template *t2=thingTemplate;
 const UnicodeString &title=t2->titleText();
 const UnicodeString *titleAddress=&title;
 bool bEmpty = titleAddress->isEmpty();
 if(bEmpty == false) {
  thingTemplate=(Rva005E3967Template *)((Rva0037DCA5 *)entry)->GetThingTemplate();
  if(thingTemplate) {
   const UnicodeString &description=thingTemplate->descriptionText();
   return TreeHintRef00217D4C((TargetRef00217D4C *)new InGameSimpleHelp(title,description));
  } else {
   return TreeHintRef00217D4C();
  }
 }
 return TreeHintRef00217D4C();
}
}
