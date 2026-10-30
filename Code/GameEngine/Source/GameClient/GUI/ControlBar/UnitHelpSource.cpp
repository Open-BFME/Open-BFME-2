// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/GameEngine/Source/Common /D_STLP_USE_STATIC_LIB
// stlport
//
// ComputeObjectRank, retail 0x005C3180 (85B), from the WorldBuilder lead
// (UnitHelpSource.cpp): ask the object's experience tracker (Object +0x264,
// 0x0039AC0C) for its experience-level handle, and return the store's rank for
// it (ExperienceLevelStore::GetLevelRank) when the store reports the handle
// valid (ExperienceLevelStore::IsValid), else 0.
//
// Target facts: the store is the global at 0x00DFECC4 (pinned as
// TheExperienceLevelSystem); the handle is two dwords passed by value, copied with the
// member-wise copy constructor as in ExperienceLevelSystem.cpp.

#include "ascii_string.h"
#include "unicode_string.h"
// Retail keeps the title buffer in EDI across the owner-name isEmpty call
// (0x00035740) in rva004E7506: cl saw that body. The same body as the row in
// string_base_inline.cpp, visible here so the call is known not to touch title.
// The native wide helper is speed-optimized (string_base_inline.cpp).
// Keep that body visible for the caller while matching its external copy.
#pragma optimize("t", on)
template <> inline __declspec(noinline) bool StringBase<unsigned short>::isEmpty() const throw()
{
    return m_data == 0 || m_data->length == 0;
}
#pragma optimize("", on)
#include "GameLogicObjectLookupView.h"
#include <bitset>
typedef int Int;
class ThingTemplate;
class HelpHealth { public:
 virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3();
 virtual void slot4(); virtual void slot5(); virtual float maxHealth();
};
#include "../../../../Include/GameClient/DrawableBFME2.h"


struct ExperienceLevelNode;
class ExperienceLevelList;

struct ExperienceLevelIterator
{
	ExperienceLevelNode *m_node;
};

struct ExperienceLevelHandle
{
	ExperienceLevelHandle() {}
	ExperienceLevelHandle(const ExperienceLevelHandle &that) : m_list(that.m_list), m_iter(that.m_iter) {}

	ExperienceLevelList *m_list;
	ExperienceLevelIterator m_iter;
};

class ExperienceLevelStore
{
public:
	bool IsValid(ExperienceLevelHandle handle) const;
	ExperienceLevelHandle GetNextLevel(ExperienceLevelHandle handle) const;
	Int GetLevelRank(ExperienceLevelHandle handle) const;
};
class ExperienceLevelSystem;
extern ExperienceLevelSystem *TheExperienceLevelSystem;

class Rva005CB9FF
{
public:
	bool rva005CB9FF(int a);
};

class ExperienceTracker
{
public:
	ExperienceLevelHandle rva0039AC0C() const;
};

class Object
{
public:
 ThingTemplate *rva002911B7();
 void *getDisplayName();
 bool rva0029137E(AsciiString &);
 const ThingTemplate *getTemplate() const { return m_template; }
 const UnicodeString &name() const { return m_name; }
 HelpHealth *health() const { return m_health; }
 Object *owner() const { return m_owner; }
 const std::bitset<1024> &upgrades() const { return m_upgrades; }
 int battles() const { return m_battles; }
	bool rva0028C149(int, float *, int);
	bool rva0028C15E(int, float *, int, int);
	ExperienceTracker *getExperienceTracker() const { return m_experienceTracker; }

private:
 char pad0[4]; const ThingTemplate *m_template;
 char pad8[0x254-8]; HelpHealth *m_health;
 char pad258[0x264-0x258]; ExperienceTracker *m_experienceTracker;
 char pad268[0x274-0x268]; Object *m_owner;
 char pad278[0x284-0x278]; std::bitset<1024> m_upgrades;
 char pad304[0x468-0x304]; int m_battles;
 char pad46C[8]; UnicodeString m_name;
};
// Retail 0x004E729B: an object's maximum health as an int (0 without a body)
// as a TU static; the tooltip builder inlines it and cl keeps this
// register-convention copy (object in EAX, __ftol2 tail jump).
static int maxHealthOf(const Object *obj)
{
 return obj->health() ? (int)obj->health()->maxHealth() : 0;
}

#include <math.h>
class ThingTemplate
{
public:
 char prefix[0x30]; UnicodeString title; char pad34[4]; UnicodeString description;
 char pad3C[0x108-0x3c]; unsigned int kind[7];
 char pad124[0x5bc-0x124];
 __forceinline unsigned int hasKind(int n) const { return kind[n>>5] & (1U<<(n&31)); }
	int meleeDamage;
	int rangedDamage;
};

static __declspec(noinline) void rva004E72CB(const ThingTemplate *, int &, int &, Object *);

Int ComputeObjectRank(const Object *obj)
{
	ExperienceLevelHandle handle = obj->getExperienceTracker()->rva0039AC0C();
	if (!reinterpret_cast<ExperienceLevelStore *>(TheExperienceLevelSystem)->IsValid(handle))
		return 0;
	return reinterpret_cast<ExperienceLevelStore *>(TheExperienceLevelSystem)->GetLevelRank(handle);
}

static __declspec(noinline) Int ComputeObjectMaxRank(const Object *obj)
{
	ExperienceLevelHandle handle = obj->getExperienceTracker()->rva0039AC0C();
	if (!reinterpret_cast<ExperienceLevelStore *>(TheExperienceLevelSystem)->IsValid(handle))
		return 0;

	ExperienceLevelHandle next = reinterpret_cast<ExperienceLevelStore *>(TheExperienceLevelSystem)->GetNextLevel(handle);
	while (reinterpret_cast<ExperienceLevelStore *>(TheExperienceLevelSystem)->IsValid(next))
	{
		handle = next;
		next = reinterpret_cast<ExperienceLevelStore *>(TheExperienceLevelSystem)->GetNextLevel(handle);
	}
	Int maxRank = reinterpret_cast<ExperienceLevelStore *>(TheExperienceLevelSystem)->GetLevelRank(handle);

	Int rankCap;
	if (reinterpret_cast<Rva005CB9FF *>(obj->getExperienceTracker())->rva005CB9FF(reinterpret_cast<int>(&rankCap)))
	{
		if (rankCap < maxRank)
			maxRank = rankCap;
	}
	return maxRank;
}
// Native4E72CB..4E7392 (199B) takes template in EDI, melee-out in ESI,
// ranged-out in EBX and Object on stack; the4E7506 tooltip caller establishes
// these roles. Fields5BC/5C0 are target damage integers with negative sentinel.
// The byte-owned Object modifier wrappers supply additive2 and multiplicative3
// values; native rounds with floor(value+0.5f), then CRT ftol2. Original helper
// spelling is unproved. File-static visibility preserves the private convention.

static __declspec(noinline) void rva004E72CB(const ThingTemplate *tpl,
	int &melee, int &ranged, Object *obj)
{
	float bonus;
	if (!obj->rva0028C149(2, &bonus, 0))
		bonus = 0.0f;
	int add = (int)floor(bonus + 0.5f);
	melee = tpl->meleeDamage;
	if (melee >= 0)
		melee += add;
	ranged = tpl->rangedDamage;
	if (ranged >= 0)
		ranged += add;
	float multiplier;
	if (obj->rva0028C15E(3, &multiplier, 0, 1))
	{
		if (melee > 0)
			melee = (int)floor(melee * multiplier + 0.5f);
		if (ranged > 0)
			ranged = (int)floor(ranged * multiplier + 0.5f);
	}
}

extern GameLogic *TheGameLogic;
class GameTextInterface {
public:
#define V(n) virtual void slot##n();
 V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11) V(12) V(13)
 virtual UnicodeString fetch(const AsciiString &, bool *);
 V(15) V(16)
 virtual const UnicodeString *formatText(const char *, bool *);
#undef V
};
extern GameTextInterface *TheGameText;
class UpgradeTemplate { public: char pad[0x2c]; AsciiString label; };
class UpgradeCenter { public: const UpgradeTemplate *rva0026EEA0(int) const; };
extern UpgradeCenter *TheUpgradeCenter;
void Rva004E74E0Append(UnicodeString *, const UnicodeString *);
struct TargetRef00217D4C { void *vtable; int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct TreeHintRef00217D4C {
 TreeHintRef00217D4C(TargetRef00217D4C *p):m_ptr(p){ if(m_ptr)++m_ptr->references; }
 TreeHintRef00217D4C(const TreeHintRef00217D4C &v):m_ptr(v.m_ptr){if(m_ptr)++m_ptr->references;}
 ~TreeHintRef00217D4C(){if(m_ptr)ReleaseTreeHintRef00217D4C(m_ptr);}
 TargetRef00217D4C *m_ptr;
};
class InGameSimpleHelp { public: InGameSimpleHelp(const UnicodeString &,const UnicodeString &); char bytes[12]; };
class Rva004E7506 { public: TreeHintRef00217D4C rva004E7506(); char beforeId[4]; ObjectID id; };
struct HelpWideHeader445 { int refs; unsigned short length,capacity; unsigned short data[1]; };
static __forceinline const HelpWideHeader445 *helpHeader445(const UnicodeString &unicodeString) { return *(const HelpWideHeader445 *const *)&unicodeString; }
TreeHintRef00217D4C Rva004E7506::rva004E7506()
{
 UnicodeString title;
 UnicodeString details;
 bool disguise=false;
 Object *obj=id?TheGameLogic->findObjectByID(id):0;
 if(obj) {
  const ThingTemplate *tpl=obj->rva002911B7();
  if(tpl)disguise=true;else tpl=obj->getTemplate();
  if(tpl) {
   AsciiString titleKey;
   Drawable *draw=((Thing *)obj)->getDrawable();
   if(draw && draw->rva00274C62(&titleKey)) {
    title.set(TheGameText->fetch(titleKey,0));
   } else {
    if(obj->getTemplate()->hasKind(190))
     title = *(const UnicodeString *)obj->getDisplayName();
    else
     title = obj->name();
    const HelpWideHeader445 *titleHeader=helpHeader445(title);
    if(!titleHeader || !titleHeader->length) {
     title.set(tpl->title);
    }
    const UnicodeString &titleView=title;
    Object *owner=obj->owner();
    if(owner && owner->getTemplate()->hasKind(109)) {
     const UnicodeString &ownerName=owner->name();
     if(!ownerName.isEmpty()) {
      UnicodeString combined;
      combined.format(TheGameText->formatText("TOOLTIP:VerteranHordeMemberName",0),titleView.str(),ownerName.str());
      title.swap(combined);
     }
    }
    AsciiString additional;
    if(obj->rva0029137E(additional))title.set(TheGameText->fetch(additional,0));
   }
   int rank=disguise?1:ComputeObjectRank(obj);
   if(rank>0) {
    int maximum=ComputeObjectMaxRank(obj);
    if(maximum>1) {
     UnicodeString text;text.format(TheGameText->formatText("TOOLTIP:Rank",0),rank,maximum);
     Rva004E74E0Append(&details,&text);
    }
   }
   if(!obj->getTemplate()->hasKind(109) && !obj->getTemplate()->hasKind(61) &&
      !obj->getTemplate()->hasKind(54) && !obj->getTemplate()->hasKind(136) &&
      !obj->getTemplate()->hasKind(104) && !disguise) {
    UnicodeString text;
    int maximum=maxHealthOf(obj);
    if(maximum>0) {
     text.format(TheGameText->formatText("TOOLTIP:MaxHealth",0),maximum);Rva004E74E0Append(&details,&text);
    }
    int melee,ranged;rva004E72CB(tpl,melee,ranged,obj);
    if(melee>=0){text.format(TheGameText->formatText("TOOLTIP:MeleeDamage",0),melee);Rva004E74E0Append(&details,&text);}
    if(ranged>=0){text.format(TheGameText->formatText("TOOLTIP:RangedDamage",0),ranged);Rva004E74E0Append(&details,&text);}
   }
   const unsigned long *upgradeWords=reinterpret_cast<const unsigned long *>(&obj->upgrades());
   if(obj->upgrades().any())for(int upgradeIndex=0;upgradeIndex<1024;++upgradeIndex)if((upgradeWords[((unsigned int)upgradeIndex)>>5] & (1UL<<(upgradeIndex&31)))) {
    const UpgradeTemplate *up=TheUpgradeCenter->rva0026EEA0(upgradeIndex);
    if(up && !up->label.isEmpty()) {Rva004E74E0Append(&details,&TheGameText->fetch(up->label,0));}
   }
   if(obj->battles()>0){UnicodeString text;text.format(TheGameText->formatText("TOOLTIP:BattlesFought",0),obj->battles());Rva004E74E0Append(&details,&text);}
   AsciiString descriptionKey;
   UnicodeString description(tpl->description);
   draw=((Thing *)obj)->getDrawable();
   if(draw && draw->rva00274CB2(&descriptionKey)) { description.set(TheGameText->fetch(descriptionKey,0)); }
   const HelpWideHeader445 *descriptionHeader=helpHeader445(description);
   if(descriptionHeader && descriptionHeader->length)Rva004E74E0Append(&details,&description);
  }
 }
 TreeHintRef00217D4C help((TargetRef00217D4C *)new InGameSimpleHelp(title,details));
 return static_cast<const TreeHintRef00217D4C &>(help);
}
