// ?rva005E4116@Rva005E4116@@QAEHXZ
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
// Rva005E4300Cmp::operator() is rowed in StrategicInGameUIHeroComparator.cpp;
// this copy was a duplicate definition.
class Rva005E549E {public:virtual void rva005E549E();};
class Rva005F6022ByteChaseField {public:unsigned char get()const;};
namespace StrategicInGameUI {UnicodeString GetTooltipText(int);}
struct RGBColor;class Mouse {public:void rva001EEA6D(UnicodeString,int,const RGBColor*,float);};extern Mouse*TheMouse;
class Rva005E6B3E {public:void updateTooltip();char unknown0[4];void*clip;char unknown8[0x10];Rva005E4300Entry*entry;};
// Rva005E6B3E::rva005E6B3E is rowed in its home unit; this copy was a duplicate definition.

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
// Rva005E6AD8::rva005E6AD8 is rowed in its home unit; this copy was a duplicate definition.

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
// StrategicInGameUI::Rva005E6CA1 is rowed in StrategicInGameUIHeroComparator.cpp;
// this copy was a duplicate definition.


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
// Rva005E4087::rva005E4087 is rowed in its home unit; this copy was a duplicate definition.

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
// Rva005D57EB::rva005D57EB is rowed in its home unit; this copy was a duplicate definition.





// Native5E4116..5E4157: sum of template cost (+0x618) over the integer
// keys of the set held at +0x14's +0x10, each resolved through the context
// index and the private 0x005E3967 (so the body lives in this unit). The set
// walk is STLport's: header->left first, the rowed _Rb_global<bool>
// increment between nodes.
namespace _STL {
struct _Rb_tree_node_base {char color; _Rb_tree_node_base *parent,*left,*right;};
template <class _Dummy> struct _Rb_global {static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *);};
}
struct Rva005E4116KeyNode : _STL::_Rb_tree_node_base {int key;};
struct Rva005E4116Iterator {
 Rva005E4116Iterator(_STL::_Rb_tree_node_base *n):node(n){}
 int operator*() const {return ((Rva005E4116KeyNode*)node)->key;}
 void operator++() {node=_STL::_Rb_global<bool>::_M_increment(node);}
 bool operator!=(const Rva005E4116Iterator &o) const {return node!=o.node;}
 _STL::_Rb_tree_node_base *node;
};
struct Rva005E4116KeySet {char pad[0x10]; _STL::_Rb_tree_node_base *header;
 Rva005E4116Iterator begin() const {return Rva005E4116Iterator(header->left);}
 Rva005E4116Iterator end() const {return Rva005E4116Iterator(header);}
};
class Rva005E4116 {public:int rva005E4116();
 char pad0[0x10];Rva005E4300Context *context;Rva005E4116KeySet *keys;
};
int Rva005E4116::rva005E4116() {
 int total=0;
 Rva005E4116Iterator end=keys->end();
 Rva005E4116Iterator it=keys->begin();
 for(;it!=end;++it) {
  int key=*it;
  Rva0040CB3AIndexedField *index=context->index;
  const Rva005E4300Entry *entry=(const Rva005E4300Entry*)index->get(key);
  Rva005E3967Template *t=StrategicInGameUI::Rva005E3967(entry);
  total+=t->cost;
 }
 return total;
}
// Native5E415F (table slot, 8B) forwards to that sum for its +0x10 object;
// native5E69D0 (table slot, 48B) calls it directly and adds the selected
// +0x14 entry's template cost when that clip's flag byte is set.
class Rva005F6037ByteChaseField {public:unsigned char get()const;};
struct Rva005E69D0Selection {char pad0[4];Rva005F6037ByteChaseField *clip;char pad8[0x18-8];Rva005E4300Entry *entry;};
class Rva005E69D0 {public:__declspec(noinline) int rva005E415F();int getTotalCost();
 char pad0[0x10];Rva005E4116 *sum;Rva005E69D0Selection *selection;
};
// Rva005E69D0::rva005E415F is rowed in its home unit; this copy was a duplicate definition.
// Rva005E69D0::rva005E69D0 is rowed in its home unit; this copy was a duplicate definition.
