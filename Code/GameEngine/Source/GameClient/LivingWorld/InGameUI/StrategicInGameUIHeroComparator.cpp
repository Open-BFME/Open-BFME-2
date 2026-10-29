// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc
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
 int rank;
 char pad[0xb8-0x10];
 int group;
};
struct Rva005E3967Template {
 char pad[0x110]; unsigned int mask; char toArchetype[0x5C4-0x114];int archetype;char beforeCost[0x618-0x5C8];int cost;
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
static __declspec(noinline) bool Rva005E3FE6(const Rva005E4300Entry *a,const Rva005E4300Entry *b,int keyA,int keyB)
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
// Retail 0x005E3977: the group order (group 0 first, then ascending) as a
// TU static; the comparator inlines it and cl keeps this register-convention
// copy (second group in EAX, first on the stack).
static bool compareGroups(int ga,int gb)
{
 if(ga==0)return true;
 if(gb==0)return false;
 return ga<gb;
}
class Rva005E4300Cmp {
public:
 char operator()(int,int) const;
private: Rva005E4300Context *m_context;
};
char Rva005E4300Cmp::operator()(int keyA,int keyB) const
{
 const Rva005E4300Entry *a=(const Rva005E4300Entry *)m_context->index->get(keyA);
 if(a->name.compare(m_context->selectedName)==0)return true;
 int rawB=m_context->index->get(keyB);
 const AsciiString *selected=&m_context->selectedName;
 const Rva005E4300Entry *b=(const Rva005E4300Entry *)rawB;
 if(b->name.compare(*selected)==0)goto no;
 {int ga=a->group,gb=b->group;
 if(ga!=gb) return compareGroups(ga,gb);
 return StrategicInGameUI::Rva005E3FE6(a,b,keyA,keyB);}
 no:return false;
}

class Rva005E549E {public:virtual void rva005E549E();};
class Rva005F6022ByteChaseField {public:unsigned char get()const;};
namespace StrategicInGameUI {UnicodeString GetTooltipText(int);}
struct RGBColor;class Mouse {public:void rva001EEA6D(UnicodeString,int,const RGBColor*,float);};extern Mouse*TheMouse;
class Rva005E6B3E {public:void rva005E6B3E();char unknown0[4];void*clip;char unknown8[0x10];Rva005E4300Entry*entry;};
void Rva005E6B3E::rva005E6B3E(){
 ((Rva005E549E*)((char*)clip+0xC))->Rva005E549E::rva005E549E();
 if(((Rva005F6022ByteChaseField*)clip)->get()){
  Rva005E3967Template*thingTemplate=StrategicInGameUI::Rva005E3967(entry);
  int kind=thingTemplate->archetype;
  TheMouse->rva001EEA6D(StrategicInGameUI::GetTooltipText(kind),-1,0,1.0f);
 }
}

struct TargetRef00217D4C {void*vtable;int count;};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
struct TreeHintRef00217D4C {
 ~TreeHintRef00217D4C(){if(m_ptr)ReleaseTreeHintRef00217D4C(m_ptr);}
 TreeHintRef00217D4C&operator=(const TreeHintRef00217D4C&);
 TargetRef00217D4C*m_ptr;
};
namespace StrategicInGameUI {TreeHintRef00217D4C Rva005E6A23(const Rva005E4300Entry*);}
class Rva003FE20FBase {public:virtual void slot1(void*);};
class Rva005E4157 {public:void rva005E4157(int);};
class Rva005E6AD8 {public:void rva005E6AD8();char pad0[4];void*clip;Rva003FE20FBase*owner;char padC[8];int value;Rva005E4300Entry*entry;TreeHintRef00217D4C held;};
void Rva005E6AD8::rva005E6AD8(){
 held=StrategicInGameUI::Rva005E6A23(entry);
 if(held.m_ptr)owner->Rva003FE20FBase::slot1(&held);
 ((Rva005E4157*)((char*)clip+0xC))->rva005E4157(value);
}

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
namespace StrategicInGameUI {
HeroDetailsPair Rva005E6CA1(Rva005E4300Context *context) {
 HeroDetailsArmySummary *summary=(HeroDetailsArmySummary*)context->index;
 int count=summary->end-summary->begin;
 int i=0;
 Rva005E4300Entry *entry;
 for(;i<count;++i) {
  entry=(Rva005E4300Entry *)((Rva0040CB2CIndexedField *)summary)->get(i);
  if(entry->name==context->selectedName)goto found;
 }
 if(i>=count)return HeroDetailsPair(0,0);
 found:return HeroDetailsPair(((Rva0040CC0EIndexedField *)summary)->get(i),entry);
}
}


// Native5E3F0A..5E3FE6: ESI entry / XMM0 result, kept by the real update below.
// All experience-store calls resolve to existing providers. Original helper
// and update class names remain unknown; the layouts describe target accesses.
struct ExperienceLevelHandle {
 ExperienceLevelHandle() {}
 ExperienceLevelHandle(const ExperienceLevelHandle &experienceLevelHandle):list(experienceLevelHandle.list),node(experienceLevelHandle.node){}
 void *list,*node;
};
class ExperienceLevelStore {public:
 ExperienceLevelHandle rva00288D88(int,int);
 bool IsValid(ExperienceLevelHandle) const;
 ExperienceLevelHandle GetNextLevel(ExperienceLevelHandle) const;
 int GetRequiredExperience(ExperienceLevelHandle) const;
};
class ExperienceLevelSystem;
extern ExperienceLevelSystem *TheExperienceLevelSystem;
namespace StrategicInGameUI {
static __forceinline float RankExperience(const Rva005E4300Entry *entry){return entry->metric;}
static float Rva005E3F0A(const Rva005E4300Entry *entry) {
 ExperienceLevelHandle current=((ExperienceLevelStore*)TheExperienceLevelSystem)->rva00288D88((int)Rva005E3967(entry),(int)RankExperience(entry));
 if(!((ExperienceLevelStore*)TheExperienceLevelSystem)->IsValid(current))return -1.0f;
 ExperienceLevelHandle next=((ExperienceLevelStore*)TheExperienceLevelSystem)->GetNextLevel(current);
 if(!((ExperienceLevelStore*)TheExperienceLevelSystem)->IsValid(next))return -1.0f;
 int low=((ExperienceLevelStore*)TheExperienceLevelSystem)->GetRequiredExperience(current);
 int high=((ExperienceLevelStore*)TheExperienceLevelSystem)->GetRequiredExperience(next);
 return (entry->metric-low)/(high-low);
}
}
class Rva0037DCA5 {public:void *GetDisplayNameStrategicGame(int);};
class Rva005F2A32 {public:
 void rva005F3272(const UnicodeString &);
 void rva005F2F41(int);
 void rva005F2F49(float);
 void rva005F2A42();
 void rva005F2F5C(int);
};
struct Rva005E4087Context {
 char pad0[0x54];int playerID;char pad1[0x78-0x58];Rva0040CB3AIndexedField *index;
};
class Rva005E4087 {public:void rva005E4087(int);
 char pad0[0x10];Rva005E4087Context *context;int unknown14;Rva005F2A32 *clip;
 char pad1[0x28-0x1C];int selected;
};
void Rva005E4087::rva005E4087(int key) {
 if(key!=selected) {
  const Rva005E4300Entry *entry=(const Rva005E4300Entry*)context->index->get(key);
  Rva005E3967Template *type=StrategicInGameUI::Rva005E3967(entry);
  clip->rva005F3272(*(const UnicodeString*)((Rva0037DCA5*)entry)->GetDisplayNameStrategicGame(context->playerID));
  clip->rva005F2F41(entry->rank);
  float progress=StrategicInGameUI::Rva005E3F0A(entry);
  if(progress>=0.0f)clip->rva005F2F49(progress);
  else clip->rva005F2A42();
  clip->rva005F2F5C(type->cost);
  selected=key;
 }
}

class GameWindow;
bool __cdecl Rva00381458(int channel, const UnicodeString &msg, GameWindow *window);
struct Rva005D57EBInner {
 __forceinline bool send(const UnicodeString &msg, GameWindow *window) {
  return Rva00381458((int)this, msg, window);
 }
};
class Rva005D57EB {
public:
 bool rva005D57EB(const UnicodeString &msg, GameWindow *window);
private:
 int m_00;
 Rva005D57EBInner *m_04;
};
bool Rva005D57EB::rva005D57EB(const UnicodeString &msg, GameWindow *window) {
 return m_04->send(msg, window);
}





// ?rva005D50AD@Rva005D50AD@@QAE_NABVUnicodeString@@PAVGameWindow@@@Z @0x005D50AD 23B.
// Same skeleton as 0x005D57EB above: forwards (m_04, msg, window) to the rowed
// cdecl LAN chat submit 0x0038169D and returns its bool. Retail pushes three
// arguments although the callee reads only two, so the call goes through the
// three-argument type the call site shows. Slot owner names stay address-derived.
bool __cdecl Rva0038169D(int channel, const UnicodeString &input);
typedef bool (__cdecl *Rva005D50ADSend)(int, const UnicodeString &, GameWindow *);
struct Rva005D50ADInner {
 __forceinline bool send(const UnicodeString &msg, GameWindow *window) {
  return ((Rva005D50ADSend)&Rva0038169D)((int)this, msg, window);
 }
};
class Rva005D50AD {
public:
 bool rva005D50AD(const UnicodeString &msg, GameWindow *window);
private:
 int m_00;
 Rva005D50ADInner *m_04;
};
bool Rva005D50AD::rva005D50AD(const UnicodeString &msg, GameWindow *window) {
 return m_04->send(msg, window);
}

// Native5E4116..5E4157 (banked, not here: this/header register swap) sums the
// template cost (+0x618) over the integer keys of the set held at +0x14's +0x10;
// only its receiver view is needed by 5E415F/5E69D0 below.
class Rva005E4116 {public:int rva005E4116();
 char pad0[0x10];Rva005E4300Context *context;void *keys;
};
// Native5E415F (table slot, 8B, rowed in stlport_map_int_sbserver.cpp) forwards
// to that sum for its +0x10 object;
// native5E69D0 (table slot, 48B) calls it directly and adds the selected
// +0x14 entry's template cost when that clip's flag byte is set.
class Rva005F6037ByteChaseField {public:unsigned char get()const;};
struct Rva005E69D0Selection {char pad0[4];Rva005F6037ByteChaseField *clip;char pad8[0x18-8];Rva005E4300Entry *entry;};
class Rva005E69D0 {public:int rva005E415F();int getTotalCost();
 char pad0[0x10];Rva005E4116 *sum;Rva005E69D0Selection *selection;
};
int Rva005E69D0::getTotalCost() {
 int total=rva005E415F();
 if(selection->clip->get()) {
  // Re-reading the selection into its own local lets it take over this's
  // register (retail mov edi,[edi+0x14]) and keeps total in esi.
  Rva005E69D0Selection *s=selection;
  total+=StrategicInGameUI::Rva005E3967(s->entry)->cost;
 }
 return total;
}

// Native005E42EE..005E4300 (18B, RET0): whether an entry is the context's
// selected one (entry+4 name against context+18), the test the comparator
// above spells inline. Retail passes the context in EAX and the entry in ECX,
// the private convention cl 7.1 picks for a file-static noinline helper; no
// retail call reaches this copy, so a source-only caller emits it.
namespace StrategicInGameUI {
static __declspec(noinline) bool Rva005E42EE(const Rva005E4300Context *context,const Rva005E4300Entry *entry)
{
 return entry->name.compare(context->selectedName)==0;
}
}
// ?Rva005E42EECaller absent-from-retail
bool Rva005E42EECaller(const Rva005E4300Context *context,const Rva005E4300Entry *entry)
{
 return StrategicInGameUI::Rva005E42EE(context,entry);
}
