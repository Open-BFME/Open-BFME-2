// ?Rva005E6CA1@StrategicInGameUI@@YA?AUHeroDetailsPair@@PAUHeroDetailsContext@@@Z
// partial score=0.94 date=2026-10-10
// cl: /O1 /G6 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
struct HeroDetailsEntry {int id;AsciiString name;float experience;int rank;};
class Rva0040CB2CIndexedField {public:int get(int) const;};
class Rva0040CC0EIndexedField {public:int get(int) const;};
struct HeroDetailsArmyEntry {int count;HeroDetailsEntry *entry;};
struct HeroDetailsArmySummary {char pad[0x40];HeroDetailsArmyEntry *begin,*end;};
struct HeroDetailsContext {char pad0[0x18];AsciiString selectedName;char pad1[0x54-0x1C];int playerID;char pad2[0x78-0x58];HeroDetailsArmySummary *summary;};
struct HeroDetailsPair {HeroDetailsPair(){} HeroDetailsPair(const HeroDetailsPair &p):count(p.count),entry(p.entry){} HeroDetailsPair(const int &c,HeroDetailsEntry *const &e):count(c),entry(e){} int count;HeroDetailsEntry *entry;};
namespace StrategicInGameUI {
HeroDetailsPair Rva005E6CA1(HeroDetailsContext *context) {
 HeroDetailsArmySummary *summary=context->summary;
 int count=summary->end-summary->begin;
 int i=0;
 HeroDetailsEntry *entry;
 for(;i<count;++i) {
  entry=(HeroDetailsEntry *)((Rva0040CB2CIndexedField *)summary)->get(i);
  if(entry->name==context->selectedName)goto found;
 }
 return HeroDetailsPair(0,0);
 found:return HeroDetailsPair(((Rva0040CC0EIndexedField *)summary)->get(i),entry);
}
}
