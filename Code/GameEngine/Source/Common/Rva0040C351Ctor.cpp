// cl: /O1 /DNDEBUG /MD /G7 /arch:SSE /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// ??0ArmySummaryEntry@@QAE@XZ @0x0040C351 (77B).
// Derived of rowed CarryoverUnit ctor 0x0037DF2C (same this, no offset) with own
// vtable 0x00C3944C at +0x0 overwriting base vtable, member at +0xAC with base
// vtable 0x00BC6F20 plus int 0 plus derived vtable 0x00C3945C via inline base
// plus int init plus body derived store (preserves dead base store as mixed
// init versus body paths), ints 0 at +0xB4 +0xB8 +0xBC +0xC0 plus bytes 0 at
// +0xC4 +0xC5. Chain of 0x0037DF2C which this session landed. Callers at
// 0x003F22B6 0x0040EFBB 0x0040F09B 0x0040F149 0x0040F24D 0x0040F721.

#include "GameLogicObjectLookupView.h"

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
extern "C" const void *const __identifier("??_7Rva0007DF07@@6B@")[];  // folded vftable 0x00BC6F20 (7 classes), by its data-ledger name

class Player;
class Object;
class CarryoverUnit
{
public:
	CarryoverUnit();
	CarryoverUnit(const CarryoverUnit &o);
	Object *createSingleObject(Player *player);
private:
	char m_pad[0xac];
};
struct MemberAC
{
	MemberAC() : m_vtable((void *)((unsigned int)__identifier("??_7Rva0007DF07@@6B@"))), m_thingTemplate(0) {}
	void *m_vtable;
	int m_thingTemplate;
};
class ArmySummaryEntry : public CarryoverUnit
{
public:
	ArmySummaryEntry();
	ArmySummaryEntry(const ArmySummaryEntry &o);
	void Parse(class INI *ini);
	void MarkForUpgrades(const class Rva004E0632 *armory);
	void CancelUpgrades();
	void ApplyWorldMapUpgrades();
	Object *rva0040C495(class Player *player, int handle);
private:
	MemberAC m_ac;
	int m_b4;
	int m_b8;
	int m_bc;
	int m_c0;
	unsigned char m_c4;
	unsigned char m_default;
};
typedef void (*FieldParseProc)(class INI *, void *, void *, const void *);
struct FieldParse { const char *token; FieldParseProc parse; const void *userData; int offset; };
extern "C" {
void __identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z")();
}
// The retail table at 0x00839474: 1 entries and the null terminator; every parser is a rowed code owner.
extern const FieldParse armySummaryEntryFieldParse[2] = {
	{ "Default", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xC5 },
	{ 0, 0, 0, 0 }
};
extern "C" {
void __identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z")();
}
// The retail table at 0x00818D18: 2 entries and the null terminator; every parser is a rowed code owner.
extern const FieldParse carryoverUnitFieldParse[3] = {
	{ "ThingTemplate", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x4 },
	{ "Quantity", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x90 },
	{ 0, 0, 0, 0 }
};
class MultiIniFieldParse
{
public:
	MultiIniFieldParse();
	void add(const FieldParse *table, unsigned int x);
private:
	char m_pad[0x84];
};
class INI
{
public:
	void initFromINIMulti(void *what, const MultiIniFieldParse &parse);
};
class Rva004E0632
{
public:
	int rva004E0632() const;
};
struct Rva0040C430Ret
{
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void slotC(void *p);
};


// ??0ArmySummaryEntry@@QAE@ABV0@@Z retail 0x0040D688 121B. Copy ctor of ArmySummaryEntry:
// base copy 0x001EB79E then same dual-vtable member pattern as default ctor
// (m_ac() gives base 0xBC6F20 plus 0 which body overwrites with 0xC3945C,
// this gets 0xC3944C), ints/bytes copied from source. Callers in unclaimed
// 0x0040E96D 0x0040EAED 0x0040F34E 0x004E0BDC 0x004F7B6B 0x0059B1EC.


void ArmySummaryEntry::Parse(INI *ini)
{
	MultiIniFieldParse parse;
	parse.add(armySummaryEntryFieldParse, 0);
	parse.add(carryoverUnitFieldParse, 0);
	ini->initFromINIMulti(this, parse);
}

void ArmySummaryEntry::MarkForUpgrades(const Rva004E0632 *armory)
{
	if (m_bc != 0)
		return;
	m_bc = *(const int *)((const char *)armory + 0x18);
	int raw = armory->rva004E0632();
	if (raw == 0)
		return;
	((Rva0040C430Ret *)raw)->slotC(this);
}

// ?CancelUpgrades@ArmySummaryEntry@@QAEXXZ @0x0040C45C 57B.
// Clear-on-null lookup-and-notify over m_bc: Logic id lookup rowed via pin
// 0x002B2579 with m_bc, null result clears; Rva004E0632 getter rowed
// 0x004E0632 zero clears; else virtual slot 4 takes this, then clear.
// Evidence: thiscall no-arg void ret; and-0 clear; caller at 0x002B3F2C;
// same m_bc and getter as sibling MarkForUpgrades above.
struct Rva002B2579Result;
class Rva002BA8F1Logic
{
public:
	Rva002B2579Result *rva002B2579(int id);
};

class Rva0040C45CSlot4
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4(ArmySummaryEntry *arg);
};
void ArmySummaryEntry::CancelUpgrades()
{
	int id = m_bc;
	if (id == 0)
		return;
	Rva002B2579Result *found = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->rva002B2579(id);
	if (found == 0)
	{
		m_bc &= 0;
		return;
	}
	int value = ((const Rva004E0632 *)found)->rva004E0632();
	if (value == 0)
	{
		m_bc &= 0;
		return;
	}
	((Rva0040C45CSlot4 *)(void *)value)->v4(this);
	m_bc &= 0;
}

// ApplyWorldMapUpgrades: WB1091690 names the complete native351B
// 40C6A5..40C804 routine. No clean BFME1 ArmySummaryEntry donor exists at
// reference34f59164f6. Target masks10/template404 and modules2E4 agree
// independently with the WB flow; upgrade module slots30/68 and data
// masks08/88 plus level limits118/11C are measured target accesses.
// Existing concrete providers establish the bitset32 OR and predicates,
// ModuleInfo accessor, template lookup and eight-byte experience handle ABI.
// A local pointer to the carrier level preserves the native field reads and
// in-memory update without imposing volatile semantics on the class.
// codegen otherwise instantiates the min<int> COMDAT (one byte shape
// per TU flags); a file-static overload takes those calls instead so this
// TU emits no external copy.
namespace _STL {
static inline const int &min(const int &a, const int &b)
{
    return b < a ? b : a;
}
}
#include <bitset>
#include <algorithm>
class Rva0040C598 { public: void rva0040C598(const int *); void rva0040C5B1(const int *); };
class Rva0037DCA5 { public: void *GetThingTemplate(); };
class Rva002AA292 { public: bool rva002AA292(const int *) const; };
class Rva00406F9C { public: bool rva00406F9C(const void *); };
struct WorldMapUpgradeDataView {
 char unknown[8];
 int required[32];
 int excluded[32];
 char unknown108[0x118-0x108];
 int levels;
 int maxLevel;
};
class WorldMapModuleDataView {
public:
#define V(n) virtual void slot##n();
 V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11)
 virtual bool isWorldMapUpgrade() const;
 V(13) V(14) V(15) V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23) V(24) V(25)
 virtual const WorldMapUpgradeDataView *worldMapUpgradeData() const;
#undef V
};
class ModuleData;
struct WorldMapModuleRecordView { char name[8]; const ModuleData *data; int flags, unknown; };
class ModuleInfo {
public:
 const ModuleData *getNthData(int) const;
 int count() const { return end-begin; }
 const WorldMapModuleRecordView *begin, *end, *capacity;
};
class ThingTemplate;
struct ArmyUpgradeTemplateView {
 char pad[0x2E4];
 ModuleInfo modules;
 char pad2F0[0x404-0x2F0];
 _STL::_Base_bitset<32> upgrades;
};
struct ArmyUpgradeCarryoverView {
 char pad[8];
 float experience;
 int level;
 _STL::_Base_bitset<32> upgrades;
};
struct ExperienceLevelHandle {
 ExperienceLevelHandle() {}
 ExperienceLevelHandle(const ExperienceLevelHandle &experienceLevelHandle): list(experienceLevelHandle.list), iterator(experienceLevelHandle.iterator) {}
 void *list;
 void *iterator;
};
class ExperienceLevelStore {
public:
 ExperienceLevelHandle rva00288E21(const ThingTemplate *, int) const;
 bool IsValid(ExperienceLevelHandle) const;
 int GetRequiredExperience(ExperienceLevelHandle) const;
};
// TheExperienceLevelStore is only an alias of the owned global TheExperienceLevelSystem (ledger names column); this unit reads the owner through its own view type.
extern class ExperienceLevelSystem *TheExperienceLevelSystem;
#define TheExperienceLevelStore (*(ExperienceLevelStore * *)&TheExperienceLevelSystem)
void ArmySummaryEntry::ApplyWorldMapUpgrades() {
 if (!m_bc) return;
 const ThingTemplate *thing = (const ThingTemplate *)((Rva0037DCA5 *)this)->GetThingTemplate();
 if (thing) {
  ArmyUpgradeCarryoverView *carry = (ArmyUpgradeCarryoverView *)this;
  const ArmyUpgradeTemplateView *view = (const ArmyUpgradeTemplateView *)thing;
  carry->upgrades._M_do_or(view->upgrades);
  const ModuleInfo *modules = &view->modules;
  for (int i=0; i<modules->count(); ++i) {
   const WorldMapModuleDataView *data = (const WorldMapModuleDataView *)modules->getNthData(i);
   if (!data || !data->isWorldMapUpgrade()) continue;
   const WorldMapUpgradeDataView *upgrade = data->worldMapUpgradeData();
   if (!upgrade) continue;
   if (!((const Rva002AA292 *)&carry->upgrades)->rva002AA292(upgrade->required)) continue;
   if (((Rva00406F9C *)&carry->upgrades)->rva00406F9C(upgrade->excluded)) continue;
   int *level = &carry->level;
   if (*level >= upgrade->maxLevel) continue;
   int amount = upgrade->levels;
   int available = upgrade->maxLevel-*level;
   amount = _STL::min(amount, available);
   if (amount < 1) continue;
   *level += amount;
   ExperienceLevelHandle handle = TheExperienceLevelStore->rva00288E21(thing, *level);
   if (TheExperienceLevelStore->IsValid(handle))
    carry->experience = (float)TheExperienceLevelStore->GetRequiredExperience(handle);
  }
 }
 m_bc=0;
}

// ?check@Rva0040C804Target@@QAE_NXZ @0x0040C804 279B (pin name kept: the sole caller 0x005C4A91
// reaches it through that pin). Whether the carried unit's upgrade set covers the template's
// upgrades: true when the template has none or the carried set already contains all of them,
// otherwise the template upgrades the unit lacks (~carried & template) minus every
// world-map upgrade module's required set that the template satisfies, whose excluded set the
// template misses and whose level limit the unit has reached; true when nothing is left.
// Evidence: target bytes and WB debug body 01091CC0 (unnamed) structure; same views as
// ApplyWorldMapUpgrades above (carried set +0x10, level +0xC, template set +0x404, modules +0x2E4,
// module slots 0x30/0x68, data required +0x08 excluded +0x88 max level +0x11C); the 128-byte
// copy is the rowed BfmeFixedStorage128 copy constructor 0x0004548B, the AND/AND-NOT loops
// are rowed Rva0040C598 0x0040C598/0x0040C5B1. The purpose and class name are inferred.
struct BfmeFixedStorage128
{
	BfmeFixedStorage128(const BfmeFixedStorage128 &other);
	int m_bits[32];
};
class Rva0040C804Target
{
public:
	bool check();
};
static inline bool anyBitSet(const BfmeFixedStorage128 &bits)
{
	for (unsigned i = 0; i < 32; ++i)
		if (bits.m_bits[i])
			return true;
	return false;
}
bool Rva0040C804Target::check()
{
	const ThingTemplate *thing = (const ThingTemplate *)((Rva0037DCA5 *)this)->GetThingTemplate();
	if (thing)
	{
		ArmyUpgradeCarryoverView *carry = (ArmyUpgradeCarryoverView *)this;
		const ArmyUpgradeTemplateView *view = (const ArmyUpgradeTemplateView *)thing;
		if (!((const Rva002AA292 *)&carry->upgrades)->rva002AA292((const int *)&view->upgrades))
		{
			BfmeFixedStorage128 missing(*(const BfmeFixedStorage128 *)&carry->upgrades);
			for (unsigned i = 0; i < 32; ++i)
				missing.m_bits[i] = ~missing.m_bits[i];
			((Rva0040C598 *)&missing)->rva0040C598((const int *)&view->upgrades);
			const ModuleInfo *modules = &view->modules;
			for (int i = 0; i < modules->count(); ++i)
			{
				const WorldMapModuleDataView *data = (const WorldMapModuleDataView *)modules->getNthData(i);
				if (!data || !data->isWorldMapUpgrade())
					continue;
				const WorldMapUpgradeDataView *upgrade = data->worldMapUpgradeData();
				if (!upgrade)
					continue;
				if (!((const Rva002AA292 *)&view->upgrades)->rva002AA292(upgrade->required))
					continue;
				if (((Rva00406F9C *)&view->upgrades)->rva00406F9C(upgrade->excluded))
					continue;
				if (carry->level < upgrade->maxLevel)
					continue;
				((Rva0040C598 *)&missing)->rva0040C5B1(upgrade->required);
			}
			return !anyBitSet(missing);
		}
	}
	return true;
}

// Retail 0x0040C495 (54 bytes; WB twin 0x010920D0, callgraph), called once per
// unit by ArmySummary::LoadArmyEntry (0x0040E534): the base CarryoverUnit
// creates the object for the player (pinned createSingleObject 0x0037DCE8, the
// base CarryoverUnit under its WorldBuilder name), GameLogic's rowed 0x0023D0C2
// takes it with the handle, and the entry's +0xC0 value goes to the object's
// +0x460 (WB +0x474).
extern GameLogic *TheGameLogic;

struct Rva0040C495Object
{
	char m_pad[0x460];
	int m_460;
};

Object *ArmySummaryEntry::rva0040C495(Player *player, int handle)
{
	Object *obj = ((CarryoverUnit *)this)->createSingleObject(player);
	if (obj) {
		TheGameLogic->rva0023D0C2(obj, handle);
		((Rva0040C495Object *)obj)->m_460 = m_c0;
	}
	return obj;
}
