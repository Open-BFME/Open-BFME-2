// ?Rva005E3967@StrategicInGameUI@@YAPAUHeroDetailsTemplate@@PBUHeroDetailsEntry@@@Z
// partial score=1.0 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// ??1Rva005E6D0D@@QAE@XZ retail 0x005E6D0D 103B
// Non-virtual dtor of a polymorphic class: own vptr C77E4C; under EH state 1
// the object passes itself to the rowed
// ?rva002B7250@Rva002B7250@@QAEXPAVCreateAHeroData@@@Z 0x002B7250 on its
// +0x10 container, then when the held ref at +0x1C is set and the owner at +8
// reports it through the no-arg virtual getter (pinned twin
// ?rva005CB265@Rva005CB265@@UAEHXZ 0x005CB265) the owner is cleared through
// the rowed forwarder 0x005CB260; the ref member's inline dtor releases it
// via the rowed fastcall ReleaseTreeHintRef00217D4C 0x0007DEEF and the base's
// inline dtor restores C79544. Same unlock check as Rva005E73B2Check.cpp.
// Names address-derived.

#include "ascii_string.h"
#include "unicode_string.h"
struct TargetRef00217D4C { void *vtable; int count; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct TreeHintRef00217D4C {
 TreeHintRef00217D4C(TargetRef00217D4C *p=0):m_ptr(p){if(p)++p->count;}
 TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &);
 ~TreeHintRef00217D4C(){if(m_ptr)ReleaseTreeHintRef00217D4C(m_ptr);}
 TargetRef00217D4C *m_ptr;
};
class ThingFactory;
extern ThingFactory *TheThingFactory;
class Rva002D06CA {public:void *rva002D06CA(const AsciiString *);};
struct HeroDetailsEntry {int id;AsciiString name;float experience;int rank;};
struct HeroDetailsTemplate {char beforeText[0x40];UnicodeString description;char beforeTitle[0x58-0x44];UnicodeString title;
 __forceinline const UnicodeString &titleText()const{return title;}
 __forceinline const UnicodeString &descriptionText()const{return description;}
};
namespace StrategicInGameUI {
static __declspec(noinline) HeroDetailsTemplate *Rva005E3967(const HeroDetailsEntry *entry) {
 return (HeroDetailsTemplate *)((Rva002D06CA *)TheThingFactory)->rva002D06CA(&entry->name);
}
}
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
static __forceinline float GetExperience(const HeroDetailsEntry *entry){return entry->experience;}
static float ComputeRankProgress(const HeroDetailsEntry *entry) {
 ExperienceLevelHandle current=TheExperienceLevelStore->rva00288D88((int)Rva005E3967(entry),(int)GetExperience(entry));
 if(!TheExperienceLevelStore->IsValid(current))return -1.0f;
 ExperienceLevelHandle next=TheExperienceLevelStore->GetNextLevel(current);
 if(!TheExperienceLevelStore->IsValid(next))return -1.0f;
 int low=TheExperienceLevelStore->GetRequiredExperience(current);
 int high=TheExperienceLevelStore->GetRequiredExperience(next);
 return (entry->experience-low)/(high-low);
}
}
class Rva0037DCA5 {public:void *rva0037DC52();};
class Rva005398CD {public:Rva005398CD(const UnicodeString &,const UnicodeString &);private:char storage[12];};
namespace StrategicInGameUI {
TreeHintRef00217D4C Rva005E6A23(const HeroDetailsEntry *entry) {
 const UnicodeString &title=Rva005E3967(entry)->titleText();
 if(!title.isEmpty()) {
  HeroDetailsTemplate *t=(HeroDetailsTemplate *)((Rva0037DCA5 *)entry)->rva0037DC52();
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
 ((Rva005F62EE *)m_slot)->rva005F62EE(StrategicInGameUI::GetButtonImage((const StrategicButtonImageView *)m_pair.entry,m_details->playerID));
 ((Rva005F62EE *)m_slot)->rva005F62F6(Rva005F01D6Get((Rva005F01D6In *)m_pair.entry));
 ((Rva005F64C0 *)m_slot)->rva005F64C0(m_pair.entry->rank);
 float progress=StrategicInGameUI::ComputeRankProgress(m_pair.entry);
 if(progress>=0.0f)((Rva005F64C0 *)m_slot)->rva005F64C8(progress);
 else ((Rva005F6306 *)m_slot)->rva005F6306();
 if(((Rva005F601BByteChaseField *)m_slot)->get()) {
  m_held=StrategicInGameUI::Rva005E6A23(m_pair.entry);
  if(m_held.m_ptr)((Rva001FF3A9 *)m_owner)->rva001FF3A9(m_held);
 }
 ((Rva005A0B4CList *)m_container)->append((Rva002BA8F1Listener *)this);
}
