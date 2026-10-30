// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc
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
 char beforeText[0x40]; UnicodeString description;
 char beforeTitle[0x58-0x44]; UnicodeString title;
 char beforeMask[0x110-0x5C]; unsigned int mask;
 __forceinline const UnicodeString &titleText()const{return title;}
 __forceinline const UnicodeString &descriptionText()const{return description;}
};
class Rva0040CB3AIndexedField { public: int get(int) const; };
struct Rva005E4300Context {
 char pad0[0x18]; AsciiString selectedName;
 char pad1[0x54-0x1c]; int playerID;
 char pad2[0x78-0x58]; Rva0040CB3AIndexedField *index;
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
 ExperienceLevelHandle(const ExperienceLevelHandle &experienceLevelHandle):list(experienceLevelHandle.list),node(experienceLevelHandle.node){}
 void *list,*node;
};
class ExperienceLevelStore {public:
 ExperienceLevelHandle rva00288D88(int,int);
 bool IsValid(ExperienceLevelHandle) const;
 ExperienceLevelHandle GetNextLevel(ExperienceLevelHandle) const;
 int GetRequiredExperience(ExperienceLevelHandle) const;
};
// TheExperienceLevelStore is only an alias of the owned global TheExperienceLevelSystem (ledger names column); this unit reads the owner through its own view type.
extern class ExperienceLevelSystem *TheExperienceLevelSystem;
#define TheExperienceLevelStore (*(ExperienceLevelStore * *)&TheExperienceLevelSystem)
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
class Rva0037DCA5 {public:void *GetThingTemplate();};
class InGameSimpleHelp {public:InGameSimpleHelp(const UnicodeString &,const UnicodeString &);private:char storage[12];};
// StrategicInGameUI::Rva005E6A23 is rowed in Common/Rva005E6A23Rva005E6A23Farm.cpp;
// a copy here was linked in place of the retail one.
namespace StrategicInGameUI {TreeHintRef00217D4C Rva005E6A23(const Rva005E4300Entry *entry);}
struct HeroDetailsPair {HeroDetailsPair(){} HeroDetailsPair(const HeroDetailsPair &p):count(p.count),entry(p.entry){} HeroDetailsPair(const int &c,Rva005E4300Entry *const &e):count(c),entry(e){} int count;Rva005E4300Entry *entry;};
// Assigns a returned (id, entry) pair through references to two members, the
// shape WB 0x01600AB0 shows (two member addresses taken before the call).
template <class A, class B> struct HeroDetailsTie {
 HeroDetailsTie(A &a, B &b):first(a),second(b){}
 template <class P> HeroDetailsTie &operator=(const P &p){first=p.count;second=p.entry;return *this;}
 A &first; B &second;
};
namespace StrategicInGameUI {
// Rowed in StrategicInGameUIHeroComparator.cpp (WB FindLeaderEntry).
HeroDetailsPair Rva005E6CA1(Rva005E4300Context *context);
}
class Image;
struct StrategicButtonImageView {int unknown;AsciiString templateName;};
namespace StrategicInGameUI {const Image *GetButtonImage(const StrategicButtonImageView *,int);}
struct Rva005F01D6In;
const Image *Rva005F01D6Get(Rva005F01D6In *);
class Rva005F62EE {public:void rva005F62EE(const Image *);void rva005F62F6(const Image *);};
class Rva005F64C0 {public:void setLeaderRank(int);void rva005F64C8(float);};
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

// Base vtable C79544: the listener callbacks rowed in StrategicUiArmyHandler.cpp.
class Rva005FPrimaryCallbacks {public:

 virtual void primary0(void*,void*){}

 virtual void primary1(void*){}

 virtual void primary2(void*,void*){}
 __forceinline ~Rva005FPrimaryCallbacks(){}
};

class Rva005E6D0D : public Rva005FPrimaryCallbacks
{
public:
    Rva005E6D0D(void *,HeroDetailsInput *);
	~Rva005E6D0D();

private:
    void *m_slot;
	Rva005CB265 *m_owner; // +0x08
	Rva005E4300Context *m_details;
	Rva002B7250 *m_container; // +0x10
	int m_leaderEntryID; // +0x14
	Rva005E4300Entry *m_leaderEntry; // +0x18
    TreeHintRef00217D4C m_held; // +0x1C
};


struct HeroDetailsInput {Rva005CB265 *owner;Rva005E4300Context *details;Rva002B7250 *container;};

// WB 0x01600AB0 StrategicInGameUI::HeroArmyDetailsPanel::Impl::Impl
// (StrategicInGameUIHeroArmyDetailsPanel.cpp 176-177): leader entry id +0x14
// and leader entry +0x18 are assigned together from FindLeaderEntry. The ctor
// is the only caller of the static ComputeRankProgress, whose register-argument
// convention needs this local caller.
Rva005E6D0D::Rva005E6D0D(void *slot,HeroDetailsInput *input):m_slot(slot),m_owner(input->owner),m_details(input->details),m_container(input->container),m_leaderEntryID(0),m_leaderEntry(0) {
 HeroDetailsTie<int,Rva005E4300Entry *>(m_leaderEntryID,m_leaderEntry)=StrategicInGameUI::Rva005E6CA1(m_details);
 void *button=m_slot;
 ((Rva005F62EE *)button)->rva005F62EE(StrategicInGameUI::GetButtonImage((const StrategicButtonImageView *)m_leaderEntry,m_details->playerID));
 ((Rva005F62EE *)button)->rva005F62F6(Rva005F01D6Get((Rva005F01D6In *)m_leaderEntry));
 ((Rva005F64C0 *)button)->setLeaderRank(m_leaderEntry->rank);
 float progress=StrategicInGameUI::ComputeRankProgress(m_leaderEntry);
 if(progress>=0.0f)((Rva005F64C0 *)button)->rva005F64C8(progress);
 else ((Rva005F6306 *)button)->rva005F6306();
 if(((Rva005F601BByteChaseField *)button)->get()) {
  m_held=StrategicInGameUI::Rva005E6A23(m_leaderEntry);
  if(m_held.m_ptr)((Rva001FF3A9 *)m_owner)->rva001FF3A9(m_held);
 }
 ((Rva005A0B4CList *)m_container)->append((Rva002BA8F1Listener *)this);
}
