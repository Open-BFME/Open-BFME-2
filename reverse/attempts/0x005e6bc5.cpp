// ?ComputeRankProgress@StrategicInGameUI@@YAMPBURva005E4300Entry@@@Z
// partial score=1.0 date=2026-10-10
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc
// Native005E4300..005E4389 low-byte comparator of selected hero keys;
// groupB8 signed order with zero priority then the native118B fallback.
// Its three private bodies are reconstructed from target; original template
// and record class names remain unknown. Public char describes the observed
// AL zero/one ABI without claiming the original C++ return spelling.
#include "ascii_string.h"
#include "unicode_string.h"
class ThingFactory;
extern ThingFactory *TheThingFactory;
class Rva002D06CA { public: void *rva002D06CA(const AsciiString *); };
struct Rva005E4300Entry {
 int key;
 AsciiString name;
 float metric;
 int rank;
 char pad[0xb8-0x10];
 int group;
};
struct Rva005E3967Template {
 char beforeText[0x40]; UnicodeString description;
 char beforeTitle[0x58-0x44]; UnicodeString title;
 char beforeMask[0x110-0x5C]; unsigned int mask;
 __forceinline const UnicodeString &titleText()const{return title;}
 __forceinline const UnicodeString &descriptionText()const{return description;}
};
class Rva0040CB3AIndexedField { public: int get(int) const; };
struct Rva005E4300Context {
 char pad0[0x18]; AsciiString selectedName;
 char pad1[0x78-0x1c]; Rva0040CB3AIndexedField *index;
};
namespace StrategicInGameUI {
static __declspec(noinline) Rva005E3967Template *Rva005E3967(const Rva005E4300Entry *entry)
{
 return (Rva005E3967Template *)((Rva002D06CA *)TheThingFactory)->rva002D06CA(&entry->name);
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
 if(ga!=gb) {if(ga==0)return true; if(gb==0)goto no; return ga<gb;}
 return StrategicInGameUI::Rva005E3FE6(a,b,keyA,keyB);}
 no:return false;
}

struct TargetRef00217D4C { void *vtable; int count; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct TreeHintRef00217D4C {
 TreeHintRef00217D4C(TargetRef00217D4C *p=0):m_ptr(p){if(p)++p->count;}
 TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &);
 ~TreeHintRef00217D4C(){if(m_ptr)ReleaseTreeHintRef00217D4C(m_ptr);}
 TargetRef00217D4C *m_ptr;
};
struct ExperienceLevelHandle {
 ExperienceLevelHandle() {}
 ExperienceLevelHandle(const ExperienceLevelHandle &r):list(r.list),node(r.node){}
 void *list,*node;
};
class ExperienceLevelStore {public:
 ExperienceLevelHandle rva00288D88(int,int);
 bool IsValid(ExperienceLevelHandle) const;
 ExperienceLevelHandle GetNextLevel(ExperienceLevelHandle) const;
 int GetRequiredExperience(ExperienceLevelHandle) const;
};
extern ExperienceLevelStore *TheExperienceLevelStore;
namespace StrategicInGameUI {
static __forceinline float GetExperience(const Rva005E4300Entry *entry){return entry->metric;}
static float ComputeRankProgress(const Rva005E4300Entry *entry) {
 ExperienceLevelHandle current=TheExperienceLevelStore->rva00288D88((int)Rva005E3967(entry),(int)GetExperience(entry));
 if(!TheExperienceLevelStore->IsValid(current))return -1.0f;
 ExperienceLevelHandle next=TheExperienceLevelStore->GetNextLevel(current);
 if(!TheExperienceLevelStore->IsValid(next))return -1.0f;
 int low=TheExperienceLevelStore->GetRequiredExperience(current);
 int high=TheExperienceLevelStore->GetRequiredExperience(next);
 return (entry->metric-low)/(high-low);
}
}
class Rva0037DCA5 {public:void *rva0037DC52();};
class Rva005398CD {public:Rva005398CD(const UnicodeString &,const UnicodeString &);private:char storage[12];};
namespace StrategicInGameUI {
TreeHintRef00217D4C Rva005E6A23(const Rva005E4300Entry *entry) {
 const UnicodeString &title=Rva005E3967(entry)->titleText();
 if(!title.isEmpty()) {
  Rva005E3967Template *t=(Rva005E3967Template *)((Rva0037DCA5 *)entry)->rva0037DC52();
  if(t) {
   const UnicodeString &description=t->descriptionText();
   return TreeHintRef00217D4C((TargetRef00217D4C *)new Rva005398CD(title,description));
  }
 }
 return TreeHintRef00217D4C();
}
}
class Rva0040CB2CIndexedField {public:int get(int) const;};
class Rva0040CC0EIndexedField {public:int get(int) const;};
struct HeroDetailsArmyEntry {int count;Rva005E4300Entry *entry;};
struct HeroDetailsArmySummary {char pad[0x40];HeroDetailsArmyEntry *begin,*end;};
struct HeroDetailsContext {char pad0[0x18];AsciiString selectedName;char pad1[0x54-0x1C];int playerID;char pad2[0x78-0x58];HeroDetailsArmySummary *summary;};
struct HeroDetailsPair {HeroDetailsPair(){} HeroDetailsPair(const HeroDetailsPair &p):count(p.count),entry(p.entry){} HeroDetailsPair(const int &c,Rva005E4300Entry *const &e):count(c),entry(e){} int count;Rva005E4300Entry *entry;};
namespace StrategicInGameUI {
HeroDetailsPair Rva005E6CA1(HeroDetailsContext *context) {
 HeroDetailsArmySummary *summary=context->summary;
 int count=summary->end-summary->begin;
 int i=0;
 Rva005E4300Entry *entry;
 for(;i<count;++i) {
  entry=(Rva005E4300Entry *)((Rva0040CB2CIndexedField *)summary)->get(i);
  if(entry->name==context->selectedName)goto found;
 }
 return HeroDetailsPair(0,0);
 found:return HeroDetailsPair(((Rva0040CC0EIndexedField *)summary)->get(i),entry);

}
}
class Image;
struct StrategicButtonImageView {int unknown;AsciiString templateName;};
namespace StrategicInGameUI {const Image *GetButtonImage(const StrategicButtonImageView *,int);}
struct Rva005F01D6In;
const Image *Rva005F01D6Get(Rva005F01D6In *);
class Rva005F62EE {public:void rva005F62EE(const Image *);void rva005F62F6(const Image *);};
class Rva005F64C0 {public:void rva005F64C0(int);void rva005F64C8(float);};
class Rva005F6306 {public:void rva005F6306();};
class Rva005F601BByteChaseField {public:unsigned char get() const;};
class Rva001FF3A9 {public:void rva001FF3A9(const TreeHintRef00217D4C &);};
struct Rva002BA8F1Listener;
class Rva005A0B4CList {public:void append(Rva002BA8F1Listener *);};
struct HeroDetailsInput;
class CreateAHeroData;

class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *data);
};

class Rva005CB265
{
public:
	virtual int rva005CB265();
};

class Rva005CB260
{
public:
	void rva005CB260();
};

class Rva005E6D0DBase
{
public:
    Rva005E6D0DBase(void *slot):m_slot(slot){}
	~Rva005E6D0DBase() {}
	virtual void Rva005E6D0DSlot0();

protected:
    void *m_slot;
};

class Rva005E6D0D : public Rva005E6D0DBase
{
public:
    Rva005E6D0D(void *,HeroDetailsInput *);
	~Rva005E6D0D();

private:
	Rva005CB265 *m_owner; // +0x08
	HeroDetailsContext *m_details;
	Rva002B7250 *m_container; // +0x10
	HeroDetailsPair m_pair;
    TreeHintRef00217D4C m_held; // +0x1C
};

Rva005E6D0D::~Rva005E6D0D()
{
	m_container->rva002B7250(reinterpret_cast<CreateAHeroData *>(this));
	int held = (int)m_held.m_ptr;
	if (held != 0 && m_owner->Rva005CB265::rva005CB265() == held)
		((Rva005CB260 *)m_owner)->rva005CB260();
}

struct HeroDetailsInput {Rva005CB265 *owner;HeroDetailsContext *details;Rva002B7250 *container;};
Rva005E6D0D::Rva005E6D0D(void *slot,HeroDetailsInput *input):Rva005E6D0DBase(slot),m_owner(input->owner),m_details(input->details),m_container(input->container),m_pair(0,0) {
 m_pair=StrategicInGameUI::Rva005E6CA1(m_details);
 void *button=m_slot;
 ((Rva005F62EE *)button)->rva005F62EE(StrategicInGameUI::GetButtonImage((const StrategicButtonImageView *)m_pair.entry,m_details->playerID));
 ((Rva005F62EE *)button)->rva005F62F6(Rva005F01D6Get((Rva005F01D6In *)m_pair.entry));
 ((Rva005F64C0 *)button)->rva005F64C0(m_pair.entry->rank);
 float progress=StrategicInGameUI::ComputeRankProgress(m_pair.entry);
 if(progress>=0.0f)((Rva005F64C0 *)button)->rva005F64C8(progress);
 else ((Rva005F6306 *)button)->rva005F6306();
 if(((Rva005F601BByteChaseField *)button)->get()) {
  m_held=StrategicInGameUI::Rva005E6A23(m_pair.entry);
  if(m_held.m_ptr)((Rva001FF3A9 *)m_owner)->rva001FF3A9(m_held);
 }
 ((Rva005A0B4CList *)m_container)->append((Rva002BA8F1Listener *)this);
}
