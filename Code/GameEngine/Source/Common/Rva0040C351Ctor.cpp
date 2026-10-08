// cl: /O1 /DNDEBUG /MD /G7 /arch:SSE /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// ??0ArmySummaryEntry@@QAE@XZ @0x0040C351 (77B).
// Derived of rowed Rva0037DF2C ctor 0x0037DF2C (same this, no offset) with own
// vtable 0x00C3944C at +0x0 overwriting base vtable, member at +0xAC with base
// vtable 0x00BC6F20 plus int 0 plus derived vtable 0x00C3945C via inline base
// plus int init plus body derived store (preserves dead base store as mixed
// init versus body paths), ints 0 at +0xB4 +0xB8 +0xBC +0xC0 plus bytes 0 at
// +0xC4 +0xC5. Chain of 0x0037DF2C which this session landed. Callers at
// 0x003F22B6 0x0040EFBB 0x0040F09B 0x0040F149 0x0040F24D 0x0040F721.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
extern "C" const void *const vtbl_00BC6F20[];  // folded, 7 classes; via ??_7Rva0007DF07@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BC6F20=??_7Rva0007DF07@@6B@")

class Rva0037DF2C
{
public:
	Rva0037DF2C();
	Rva0037DF2C(const Rva0037DF2C &o);
private:
	char m_pad[0xac];
};
struct MemberAC
{
	MemberAC() : m_vtable((void *)((unsigned int)vtbl_00BC6F20)), m_04(0) {}
	void *m_vtable;
	int m_04;
};
class ArmySummaryEntry : public Rva0037DF2C
{
public:
	ArmySummaryEntry();
	ArmySummaryEntry(const ArmySummaryEntry &o);
	void Parse(class INI *ini);
	void MarkForUpgrades(const class Rva004E0632 *a);
	void CancelUpgrades();
	void ApplyWorldMapUpgrades();
private:
	MemberAC m_ac;
	int m_b4;
	int m_b8;
	int m_bc;
	int m_c0;
	unsigned char m_c4;
	unsigned char m_c5;
};
struct FieldParse;
extern const FieldParse g_00C39474;
extern const FieldParse g_00C18D18;
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
ArmySummaryEntry::ArmySummaryEntry() : Rva0037DF2C()
{
	MemberAC *p = &m_ac;
	p->m_vtable = (void *)0x00C3945C;
	*(unsigned int *)this = 0x00C3944C;
	m_b4 = 0;
	m_b8 = 0;
	m_bc = 0;
	m_c0 = 0;
	m_c4 = 0;
	m_c5 = 0;
}

// ??0ArmySummaryEntry@@QAE@ABV0@@Z retail 0x0040D688 121B. Copy ctor of ArmySummaryEntry:
// base copy 0x001EB79E then same dual-vtable member pattern as default ctor
// (m_ac() gives base 0xBC6F20 plus 0 which body overwrites with 0xC3945C,
// this gets 0xC3944C), ints/bytes copied from source. Callers in unclaimed
// 0x0040E96D 0x0040EAED 0x0040F34E 0x004E0BDC 0x004F7B6B 0x0059B1EC.
extern const void *const g_00C3944C[];
extern const void *const g_00C3945C[];
ArmySummaryEntry::ArmySummaryEntry(const ArmySummaryEntry &o) : Rva0037DF2C(o), m_ac()
{
	*(const void **)this = g_00C3944C;
	MemberAC *p = &m_ac;
	p->m_vtable = (void *)g_00C3945C;
	m_b4 = o.m_b4;
	m_b8 = o.m_b8;
	m_bc = o.m_bc;
	m_c0 = o.m_c0;
	m_c4 = o.m_c4;
	m_c5 = o.m_c5;
}

void ArmySummaryEntry::Parse(INI *ini)
{
	MultiIniFieldParse parse;
	parse.add(&g_00C39474, 0);
	parse.add(&g_00C18D18, 0);
	ini->initFromINIMulti(this, parse);
}

void ArmySummaryEntry::MarkForUpgrades(const Rva004E0632 *a)
{
	if (m_bc != 0)
		return;
	m_bc = *(const int *)((const char *)a + 0x18);
	int raw = a->rva004E0632();
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
#include <bitset>
#include <algorithm>
class Rva0037DCA5 { public: void *rva0037DC52(); };
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
 ExperienceLevelHandle(const ExperienceLevelHandle &o): list(o.list), iterator(o.iterator) {}
 void *list;
 void *iterator;
};
class ExperienceLevelStore {
public:
 ExperienceLevelHandle rva00288E21(const ThingTemplate *, int) const;
 bool IsValid(ExperienceLevelHandle) const;
 int GetRequiredExperience(ExperienceLevelHandle) const;
};
extern ExperienceLevelStore *TheExperienceLevelStore;
void ArmySummaryEntry::ApplyWorldMapUpgrades() {
 if (!m_bc) return;
 const ThingTemplate *thing = (const ThingTemplate *)((Rva0037DCA5 *)this)->rva0037DC52();
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
