// cl: /Ireference/shims/bfmealloc /D_CRTIMP= /Ireference/shims/bfme2_ascii /Ireference/shims/iniexception /O1 /G7 /EHs /MD /arch:SSE /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// LivingWorldPlayer.cpp -- LivingWorldPlayer members recovered from
// WorldBuilder leads (reverse/wb_name_leads.csv): WB's debug build names the
// function; retail supplies the bytes. The player's queued command points at
// +0x298 drop by the dequeued unit's cost (rowed 0x004E1755) and clamp at 0.
//
// RemoveArmy takes an iterator into m_armyVec (+0x1B8, WB member name), hands
// the army's id (+0x78) to the game logic (0x0023D007, unrowed: forwards to
// the member at GameLogic+0x184) and erases it. The army vector erases
// through the folded pointer-vector erase (rowed as vector<void *>), so the
// view below holds void pointers.

typedef int Int;

// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include "FixedStorage128.h"
#include "ascii_string.h"
#include "unicode_string.h"
#include "Common/INIException.h"
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline unsigned int vector<void *,allocator<void *> >::size()const  { return (unsigned int)(this->_M_finish - this->_M_start); } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * & vector<void *,allocator<void *> >::operator[](unsigned int n) { return *(this->_M_start + n); } }

class INI;

namespace _STL
{
	// Keep the already verified pointer-vector erase provider out of line.
	template <> void **vector<void *>::erase(void **position);
}

// Native2E12F3..2E134C and WBDE4FC0 prove the216-byte stride and
// the key atAC. Native2E1451..2E14DD and the verified UnitRevivalEntry
// copies establish the consumed experience/rank/upgrade fields. The remaining
// fields and the key-search method name remain unknown. Retail's mangled
// ?CalcRevivalCostsForEntry@@YAXAAVUnitRevivalEntry@@@Z and the matched
// UnitRevivalEntry ctor/copy/dtor rows name the record class.
class Xfer;
class UnitRevivalEntry
{
public:
	UnitRevivalEntry();
	UnitRevivalEntry(const UnitRevivalEntry &);
	~UnitRevivalEntry();
	void *getThingTemplate();
	void rva0037E473(Xfer*);
	char m_pad00[0x8];
	float experience; // +0x08
	int rank; // +0x0C
	int level; // +0x10
	BfmeFixedStorage128 upgrades; // +0x14
	unsigned int cost; // +0x94
	int startFrame; // +0x98
	unsigned int time; // +0x9C
	bool revival; // +0xA0
	bool flagA1; // +0xA1
	char m_padA2[0x2];
	int productionID; // +0xA4
	int armyID; // +0xA8
	int key; // +0xAC
	char record[0x18]; // +0xB0
	int valueC8; // +0xC8
	float factor; // +0xCC
	char textD0[8]; // +0xD0
};

struct LivingWorldArmy
{
public:
	unsigned char m_pad00[0x78];
	Int m_id;				// +0x78
};

#include "../../../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

class SpawnArmy
{
public:
	Int rva004E1755();			// 0x004E1755, command-point cost
};

// The existing61B provider consumes a24-byte subrecord. These are
// pointer views into that record; no objects of the declaration-only class
// are constructed here.
class Rva001EAFC1 { public: Rva001EAFC1 &operator=(const Rva001EAFC1 &); };
struct LivingWorldRevivalUnitDataView {
    char unknown00[8]; float experience; int rank; BfmeFixedStorage128 upgrades;
    char unknown90[4]; char record94[0x18];
};
class Rva002E0D93;
class Rva002E204D
{
public:
	Rva002E0D93 *rva002E204D(Rva002E0D93 *);
};
// The rowed predicate ?rva00318F42@Rva00318F42 at 0x00318F42. Native and WB
// identify the receiver as an element of m_armyVec; its original method is
// unknown.
class Rva00318F42 { public: bool rva00318F42(); };
// Three-word RGB copies are proven by the native color setter and the
// recovered MultiplayerColorDefinition constructor. Reference getNumColors
// supplies the lazy-count semantics; target settings fields are38 and40.
// The extra color triplets' original field names remain unknown.
struct LivingWorldPlayerRGBColorView { float r,g,b; };
class MultiplayerColorDefinition { public:
 char unknown00[4]; LivingWorldPlayerRGBColorView rgbAt04;
 char unknown10[0x24-0x10]; LivingWorldPlayerRGBColorView rgbAt24,rgbAt30;
};
class MultiplayerSettings { public:
 MultiplayerColorDefinition *getColor(int);
 int getNumColors() { if(numColors==0) numColors=listCount; return numColors; }
private: char unknown00[0x38]; int listCount; int unknown3C; int numColors;
};
extern MultiplayerSettings *TheMultiplayerSettings;

// WBDE4E00 names FindArmyWithHero and asserts KINDOF_HERO at line787.
// Native2E1257 tests that flag at template113 and searches summary pairs40,
// stride8, through the existing integer-returning indexed getter. Its result
// is a pointer in this caller; the hero entry key lives atC0. Original template
// qualifiers and entry type names remain unknown, so retain opaque views.
class Rva0040CB2CIndexedField { public: int get(int) const; };
struct PlayerHeroEntryView { char unknown00[0xC0]; int heroKey; };
struct PlayerHeroPairView { int first,second; };
struct PlayerHeroSummaryView { char unknown00[0x40]; _STL::vector<PlayerHeroPairView> entries; };
struct PlayerHeroArmyView { char unknown00[0x78]; PlayerHeroSummaryView *summary; };
struct PlayerHeroTemplateView { char unknown00[0x113]; unsigned char flags; };

// Native AddArmy accesses the army summary through +78 and its two packed
// colors at24/28. Existing army-id and RGB views are retained separately;
// their original shared type spellings are not established by these accesses.
struct PlayerArmyColorSummaryView { char unknown00[0x24]; unsigned day,night; };
class ModuleData;
struct Rva0040E6D6Arg;
class Rva0023CFFCLogic {public:void rva0023CFFC(Rva0040E6D6Arg*);};

struct Rva002E2690Element;
class LivingWorldPlayer
{
public:
	typedef _STL::vector<void *> ArmyVec;
	static void ParseLivingWorldPlayer(INI *ini, void *instance);
	void MarkUnitsForUpgrades(void *region);
	int GetNumRegionsOwned();
	int GetConflictResolveType();
	void AddUpgrade(void *upgrade, bool persistentOnly);
	void RemoveUpgrade(void *upgrade);
	void rva002E14E9(const BfmeFixedStorage128 &mask);
	bool rva002E1155(SpawnArmy *unit);
	void OnUnitDequeued(SpawnArmy *unit);
	void SetColorIndex(int color);
	void AddArmy(LivingWorldArmy *army);
	void *FindArmyWithHero(void *thing, int key);
	void **RemoveArmy(void **&iter);
	bool rva002E12F3(int key);
	bool rva002E0B30();
	void RemoveRevivalUnit(int key);
	void GetRevivalUnitData(int key, LivingWorldRevivalUnitDataView *out);
	int rva002E199E(const void *thing);
	bool HasArmyQueuedInAnyBuilding(void*,int*,int);
	void ExtractRevivalUnitDataForCurrentMap(std::vector<Rva002E2690Element>*);
	char m_pad00[0x44];
private:
	int m_playerType; // +0x44 +44, native and WB switch
	char m_pad48[0x138];
	int m_colorIndex; // +0x180
	LivingWorldPlayerRGBColorView m_color184; // +0x184
	LivingWorldPlayerRGBColorView m_color190; // +0x190
	LivingWorldPlayerRGBColorView m_color19C; // +0x19C
public:
	_STL::vector<UnitRevivalEntry> m_records; // +0x1A8
	char m_pad1B4[0x4];
private:
	ArmyVec m_armyVec; // +0x1B8 +0x1B8
	char m_pad1C4[0x14];
	unsigned int m_upgradeBits[32]; // +0x1D8 +1D8, native and WB BitFlags<1024>
	char m_pad258[0x40];
	int m_queuedCommandPoints; // +0x298 +0x298
	char m_pad29C[0x18];
	int m_conflictResolveType; // +0x2B4 +2B4, native and WB case0
};

// Existing out-of-line player providers; their original method names are unknown.
class Rva002E0C68 { public: Int rva002E0C68(); };
class Rva002E0CD4 { public: Int get() const; };

// Retail 2E1155..2E118E, RET4; WB DE4B30 has the same field and three calls.
// canQueueUnit proves the LivingWorldPlayer receiver. The dequeuing sibling
// identifies +298 as queued command points; count queued and active points
// together with the new unit before comparing against the player's limit.
bool LivingWorldPlayer::rva002E1155(SpawnArmy *unit)
{
    Int queuedCommandPoints = m_queuedCommandPoints;
    return ((Rva002E0C68 *)this)->rva002E0C68() + queuedCommandPoints
        + unit->rva004E1755() <= ((Rva002E0CD4 *)this)->get();
}

// LivingWorldPlayer::OnUnitDequeued, retail 0x002E0764.
void LivingWorldPlayer::OnUnitDequeued(SpawnArmy *unit)
{
	m_queuedCommandPoints -= unit->rva004E1755();
	if (m_queuedCommandPoints < 0)
		m_queuedCommandPoints = 0;
}

// LivingWorldPlayer::RemoveArmy, retail 0x002E10FE.
void **LivingWorldPlayer::RemoveArmy(void **&iter)
{
	TheGameLogic->rva0023D007(((LivingWorldArmy *)*iter)->m_id);
	return m_armyVec.erase(iter);
}

// Full89-byte RET4 body, with no relocations. The unsigned loop index and
// STLport size calculation retain retail's signed pointer-range division.
bool LivingWorldPlayer::rva002E12F3(int key)
{
	for (unsigned int i = 0; i < m_records.size(); ++i)
	{
		if (m_records[i].key == key)
			return true;
	}
	return false;
}

// WBDE5040 names RemoveRevivalUnit; native2E2225..2E2285 RET4.
// Reuse the full61B216-byte vector erase at2E204D under its owner spelling.
void LivingWorldPlayer::RemoveRevivalUnit(int key)
{
    if (key == 0) return;
    for (unsigned int i = 0; i < m_records.size(); ++i) {
        if (m_records[i].key == key) {
            reinterpret_cast<Rva002E204D *>(&m_records)->rva002E204D(
                reinterpret_cast<Rva002E0D93 *>(&m_records[i]));
            break;
        }
    }
}
// WBDE64F0 names GetRevivalUnitData; native2E1451..2E14DD RET8.
// Output field offsets are target facts; its original type name is unknown.
void LivingWorldPlayer::GetRevivalUnitData(int key, LivingWorldRevivalUnitDataView *out)
{
    if (key == 0) return;
    for (unsigned int i = 0; i < m_records.size(); ++i) {
        const UnitRevivalEntry &entry = m_records[i];
        if (entry.key == key) {
            out->rank = entry.rank;
            out->experience = entry.experience;
            out->upgrades = entry.upgrades;
            *reinterpret_cast<Rva001EAFC1 *>(out->record94) =
                *reinterpret_cast<const Rva001EAFC1 *>(entry.record);
            break;
        }
    }
}
// Native2E0B30..2E0B76, 70B; WBDE45B0 independently scans the army vector
// at1B8 and calls318F42 until true. Signed span arithmetic retains retail's
// recomputed vector count. Player/m_armyVec identity is established by the
// existing RemoveArmy body; the predicate and member names remain unknown.
bool LivingWorldPlayer::rva002E0B30()
{
 int *span=(int *)&m_armyVec;
 for(unsigned int i=0; i<(unsigned)((span[1]-span[0])>>2); ++i)
  if (((Rva00318F42 *)m_armyVec[i])->rva00318F42()) return true;
 return false;
}

// WBDE36A0 names SetColorIndex; native2E0F91..2E1001 RET4,112B.
// Keep the old index unless settings and an in-range new index are available.
// Once selected, copy definition triplets24/04/30 to player184/190/19C.
void LivingWorldPlayer::SetColorIndex(Int color)
{
 if(m_colorIndex==color || !TheMultiplayerSettings || color<0 ||
    color>=TheMultiplayerSettings->getNumColors()) return;
 m_colorIndex=color;
 MultiplayerColorDefinition *definition=TheMultiplayerSettings->getColor(color);
 if(definition) {
  m_color184=definition->rgbAt24;
  m_color190=definition->rgbAt04;
  m_color19C=definition->rgbAt30;
 }
}

// Native2E1257..2E12F3 RET8,156B; no borrowed callee types or new pins.
void *LivingWorldPlayer::FindArmyWithHero(void *thing, int key)
{
 if(!(((PlayerHeroTemplateView*)thing)->flags & 4))return 0;
 for(unsigned i=0;i<m_armyVec.size();++i) {
  PlayerHeroArmyView *army=(PlayerHeroArmyView*)m_armyVec[i];
  PlayerHeroSummaryView *summary=army->summary;
  if(!summary)continue;
  for(int j=0;j<(int)summary->entries.size();++j) {
   PlayerHeroEntryView *entry=(PlayerHeroEntryView*)((Rva0040CB2CIndexedField*)summary)->get(j);
   if(entry->heroKey==key)return army;
  }
 }
 return 0;
}

// WB DE3D70 names AddArmy; native2E246D..2E2504 RET4 establishes
// registration, the1B8 pointer-vector member and packed-color propagation.
// The established ModuleData pointer-vector provider is a storage view;
// it does not establish the original army-vector element spelling.
void LivingWorldPlayer::AddArmy(LivingWorldArmy *army)
{
 if (!army) return;
 ((_STL::vector<const ModuleData*>*)&m_armyVec)->push_back(*(const ModuleData**)&army);
 if(m_colorIndex>=0 && m_colorIndex<(army?TheMultiplayerSettings:TheMultiplayerSettings)->getNumColors()) {
  unsigned day=*(unsigned*)((char*)(army?TheMultiplayerSettings:TheMultiplayerSettings)->getColor(m_colorIndex)+0x10);
  unsigned night=*(unsigned*)((char*)(army?TheMultiplayerSettings:TheMultiplayerSettings)->getColor(m_colorIndex)+0x20);
  (*(PlayerArmyColorSummaryView**)((char*)army+0x78))->day=day;(*(PlayerArmyColorSummaryView**)((char*)army+0x78))->night=night;
 } else {(*(PlayerArmyColorSummaryView**)((char*)army+0x78))->day=0xff000000;(*(PlayerArmyColorSummaryView**)((char*)army+0x78))->night=0xff000000;}
 ((Rva0023CFFCLogic*)TheGameLogic)->rva0023CFFC((Rva0040E6D6Arg*)*(PlayerArmyColorSummaryView**)((char*)army+0x78));
}

// Native2E199E..2E1A1A, complete124B RET4; WBDE5150 independently
// searches the same216B revival records and compares record+D4 against
// the argument+64 through StringBase<char>::compare. Return keyAC on a
// match, zero otherwise. Original method and argument class names unknown.
int LivingWorldPlayer::rva002E199E(const void *thing)
{
    for (unsigned int i=0; i<m_records.size(); ++i) {
        const UnitRevivalEntry &record=m_records[i];
        const StringBase<char> &name=*(const StringBase<char> *)((const char *)&record+0xD4);
        const StringBase<char> &wanted=*(const StringBase<char> *)((const char *)thing+0x64);
        if (name.compare(wanted)==0) return record.key;
    }
    return 0;
}

// WB DE74D0 names LivingWorldPlayer::ParseLivingWorldPlayer at source lines
// 1489..1499. Both retail2E1D22 and WB share the two error literals, null-input
// checks, getNextToken/initFromINI and two conditional lookup calls before
// LivingWorldCampaign::AddPlayer. The two consumed stack arguments are INI*
// and an instance pointer; no stronger original instance type is asserted.
// Replace the split-out free-function placeholder and manual throw/zero
// ThrowInfo anchor with this named static callback and ordinary C++ throws.
// The record's original class/type names remain unknown; keep its rowed views.
// Retail body241B and EH handler778800 remain under their existing boundaries.
struct FieldParse
{
	const char *token;
	void (__cdecl *parse)(INI *ini, void *instance, void *store, const void *userData);
	const void *userData;
	int offset;
};

class INI
{
public:
	const char *getNextToken(const char *seps);
	void initFromINI(void *what, const FieldParse *parseTable);
	static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);
	static void parseInt(INI *ini, void *instance, void *store, const void *userData);
	static void parseBool(INI *ini, void *instance, void *store, const void *userData);
};

// The parsers retail's LivingWorldPlayer table reaches, each an already-rowed
// body: INI::parseAsciiString (0x0002F11E), INI::parseInt (0x0002EF56) and
// INI::parseBool (0x0002E850). Declared with the real INI* first argument so the
// records below bind to those rowed symbols.

// Retail VA 0x00C049D8 (.rdata, file offset 0x00800E18): the seven field records
// of the 0x28-byte LivingWorldPlayer and the zero terminator, 128 bytes - the
// ledger's own bound. Four names through INI::parseAsciiString at +0xC/+0x10/
// +0x14 (the three template/region strings of the rowed record's +0x8 AsciiString
// pair) and three ints/bools at +0x18..+0x24. Every parse target is a rowed,
// byte-matched body.
// The full eight-record array emits ?g_00C049D8@@3QBUFieldParse@@B;
// its sizeof128 and every retail pointer are verified by data_rows.csv.
extern const struct FieldParse g_00C049D8[] =
{
	{ "PlayerTemplate",    &INI::parseAsciiString, 0, 0x0C },
	{ "AITemplate",        &INI::parseAsciiString, 0, 0x10 },
	{ "BaseRegion",        &INI::parseAsciiString, 0, 0x14 },
	{ "MP_SlotColorIndex", &INI::parseInt,         0, 0x18 },
	{ "IsDumb",             &INI::parseBool,        0, 0x24 },
	{ "TeamNumber",         &INI::parseInt,         0, 0x1C },
	{ "LWHandicap",         &INI::parseInt,         0, 0x20 },
	{ 0, 0, 0, 0 }
};

class Rva002E18C3Lookup
{
public:
	AsciiString *find(const AsciiString &name);
};

extern class Rva002E18C3Lookup *TheLivingWorldPlayerTemplateStore;
extern class Rva002E18C3Lookup *TheLivingWorldAITemplateStore;

class Rva002E0F1E
{
public:
	virtual ~Rva002E0F1E();
	UnicodeString m_04;
	AsciiString m_08;
	AsciiString m_strPlayerTemplateName;
	AsciiString m_10;
	AsciiString m_baseRegion;
	int m_mP_SlotColorIndex;
	int m_teamNumber;
	int m_lWHandicap;
	bool m_isDumb;
};

class Rva002E0EF7 : public Rva002E0F1E
{
public:
	Rva002E0EF7();
public:
	virtual ~Rva002E0EF7();	// rowed elsewhere; declared so this unit binds to it
};

class Rva002E0A0A
{
	char opaque[40];
};

class LivingWorldCampaign
{
public:
	void AddPlayer(const Rva002E0A0A &arg);
};

void LivingWorldPlayer::ParseLivingWorldPlayer(INI *ini, void *instance)
{
	if (ini == 0 || instance == 0)
	{
		throw INIException(3, "ParseLivingWorldPlayer::Invalid data passed in.");
	}
	Rva002E0EF7 record;
	const char *tok = ini->getNextToken(0);
	record.m_08 = tok;
	if (record.m_08.getLength() == 0)
	{
		throw INIException(3, "ParseLivingWorldPlayer::No name specified.");
	}
	ini->initFromINI(&record, g_00C049D8);
	AsciiString *found = TheLivingWorldPlayerTemplateStore->find(record.m_strPlayerTemplateName);
	if (found == 0)
		goto done;
	if (record.m_isDumb)
		goto append;
	{
		AsciiString *asciiString = TheLivingWorldAITemplateStore->find(record.m_10);
		if (asciiString == 0)
			goto done;
	}
append:
	((LivingWorldCampaign *)instance)->AddPlayer(*(const Rva002E0A0A *)&record);
done:;
}


// Native2E2D8D..2E2F39 RET4; WBDE4730 names the operation and the same
// armory/army/summary-entry loops. ModuleData-pointer vectors retain the
// existing collector/push providers' spelling only as a storage view.
// The region argument's original type and the filter slot's name are unknown.
class Rva003F287F {public:void rva003F28DB(_STL::vector<const ModuleData*>&);};
class Rva00318C32Ret;
class Rva002E2504 {public:bool rva002E2504(Rva00318C32Ret*,_STL::vector<const ModuleData*>*);};
class Rva0040C804Target {public:bool check();};
class Rva004E0632 {public:int rva004E0632() const;};
class ArmySummaryEntry {public:void MarkForUpgrades(const Rva004E0632*);};
struct UpgradeSummaryBoundsView { char pad[0x40]; PlayerHeroPairView *begin,*end; };
struct LivingWorldUpgradeFilterView {virtual void slot0();virtual bool accepts(ArmySummaryEntry*);};
struct Rva002E0864Cmp {unsigned char unused;bool operator()(void*,void*) const;};
namespace _STL {template<> void sort<void**,Rva002E0864Cmp>(void**,void**,Rva002E0864Cmp);}

void LivingWorldPlayer::MarkUnitsForUpgrades(void *region)
{
    _STL::vector<const ModuleData*> armories;
    ((Rva003F287F*)region)->rva003F28DB(armories);
    if (!armories.empty()) {
        _STL::vector<const ModuleData*> armies;
        ((Rva002E2504*)this)->rva002E2504((Rva00318C32Ret*)region,&armies);
        const ModuleData **armyEnd=armies.end();
        if (armies.begin()!=armyEnd) {
            _STL::vector<const ModuleData*> units;
            // Retail updates the cached byte distance in its stack slot, then shifts
            // that slot by two. Volatile reproduces this observable local update;
            // the original source qualification is unknown.
            volatile int armyCount=(const char*)armyEnd-(const char*)armies.begin();
            armyCount >>= 2;
            for(unsigned i=0;i<(unsigned)armyCount;++i) {
                PlayerHeroArmyView *army=(PlayerHeroArmyView*)armies[i];
                UpgradeSummaryBoundsView *summary=(UpgradeSummaryBoundsView*)army->summary;
                int count=summary->end-summary->begin;
                for(int j=0;j<count;++j) {
                    ArmySummaryEntry *entry=(ArmySummaryEntry*)((Rva0040CB2CIndexedField*)army->summary)->get(j);
                    if(!((Rva0040C804Target*)entry)->check()) {
                        const ModuleData *stored=(const ModuleData*)entry;
                        units.push_back(stored);
                    }
                }
            }
            if(!units.empty()) {
                _STL::sort((void**)units.begin(),(void**)units.end(),Rva002E0864Cmp());
                for(unsigned i=0;i<armories.size();++i) {
                    const Rva004E0632 *armory=(const Rva004E0632*)armories[i];
                    LivingWorldUpgradeFilterView *filter=(LivingWorldUpgradeFilterView*)armory->rva004E0632();
                    for(unsigned j=0;j<units.size();++j) {
                        ArmySummaryEntry *entry=(ArmySummaryEntry*)units[j];
                        if(*(int*)((char*)entry+0xBC)==0 && filter->accepts(entry))
                        entry->MarkForUpgrades(armory);
                    }
                }
            }
        }
    }
}

// WBDE39D0 names GetNumRegionsOwned and asserts the region list at source272.
// Native2E1001..2E1046 counts regions whose owner13C equals player14, through
// the canonical singleton's B0 holder, its +08 campaign and +2C pointer range.
// This rehomes the already verified69B body; no unique C++ coverage is added.
// The original method's const qualification is not established by these bytes.
int LivingWorldPlayer::GetNumRegionsOwned()
{
	int c = 0;
	void **pp = (void **)TheLivingWorldLogic;
	pp = *(void ***)((char *)pp + 0xB0);
	pp = *(void ***)((char *)pp + 8);
	char *p;
	if (pp)
		p = (char *)pp + 0x2C;
	else
		p = 0;
	if (!p)
		goto done;
	{
		int *start = *(int **)p;
		int *end = *(int **)(p + 4);
		int n = (int)(end - start);
		if (n == 0)
			goto done;
		int id = *(int *)((char *)this + 0x14);
		int *cur = start;
		int left = n;
		while (left) {
			void *e = *(void **)cur;
			if (*(int *)((char *)e + 0x13C) == id)
				c++;
			cur = (int *)((char *)cur + 4);
			left--;
		}
	}
done:
	return c;
}

// WBDE7000/DE72C0 name AddUpgrade/RemoveUpgrade and independently access
// the same player mask1D8 and template04/38/78 fields as native2E1588/2E15BC.
// Their assertions establish player-upgrade type0 and the1024-bit storage.
// Retain the consumed void* and bool ABI; original argument type/qualifiers
// remain unknown. Rehome existing exact bodies, without adding coverage.
struct LivingWorldUpgradeTemplateView
{
	int m_00;
	int m_04;
	char m_pad[0x38 - 8];
	int m_38;
	char m_pad2[0x78 - 0x3C];
	unsigned char m_78;
};

void LivingWorldPlayer::RemoveUpgrade(void *argp)
{
	LivingWorldUpgradeTemplateView *livingWorldUpgradeTemplateView = (LivingWorldUpgradeTemplateView *)argp;
	if (livingWorldUpgradeTemplateView->m_04 != 0)
		return;
	unsigned int bit = (unsigned int)livingWorldUpgradeTemplateView->m_38;
	m_upgradeBits[bit >> 5] &= ~(1u << (bit & 31));
}

void LivingWorldPlayer::AddUpgrade(void *argp, bool flag)
{
	LivingWorldUpgradeTemplateView *livingWorldUpgradeTemplateView = (LivingWorldUpgradeTemplateView *)argp;
	if (livingWorldUpgradeTemplateView->m_04 != 0)
		return;
	if (flag != 0 && livingWorldUpgradeTemplateView->m_78 == 0)
		return;
	unsigned int bit = (unsigned int)livingWorldUpgradeTemplateView->m_38;
	m_upgradeBits[bit >> 5] |= (1u << (bit & 31));
}

class UpgradeCenter;
extern UpgradeCenter *TheUpgradeCenter;
struct Rva0026F0F0
{
	void *rva0026F0F0(const void *mask);
};
struct Rva00046827
{
	int rva00046827();
};

// Native 002E14E9..002E1588, 159B, RET4. The adjacent rowed set/clear
// methods prove the receiver's mask at +1D8 and the template's +04/+38/+78
// fields. Both native temporary masks are 128 bytes, copied by 0004548B.
// The player receiver is established by these adjacent named methods and
// ArmySummarySystem::Save; the original mask-filter method name is unresolved.
void LivingWorldPlayer::rva002E14E9(const BfmeFixedStorage128 &mask)
{
	BfmeFixedStorage128 unchecked(mask);
	BfmeFixedStorage128 accepted(mask);
	while (reinterpret_cast<Rva00046827 *>(&unchecked)->rva00046827() > 0) {
		LivingWorldUpgradeTemplateView *livingWorldUpgradeTemplateView = static_cast<LivingWorldUpgradeTemplateView *>(
			reinterpret_cast<Rva0026F0F0 *>(TheUpgradeCenter)->rva0026F0F0(&unchecked));
		if (!livingWorldUpgradeTemplateView)
			break;
		if (!livingWorldUpgradeTemplateView->m_78 || livingWorldUpgradeTemplateView->m_04 != 0) {
			unsigned int bit = static_cast<unsigned int>(livingWorldUpgradeTemplateView->m_38);
			reinterpret_cast<unsigned int *>(accepted.bytes)[bit >> 5] &= ~(1u << (bit & 31));
		}
		unsigned int bit = static_cast<unsigned int>(livingWorldUpgradeTemplateView->m_38);
		reinterpret_cast<unsigned int *>(unchecked.bytes)[bit >> 5] &= ~(1u << (bit & 31));
	}
	*reinterpret_cast<BfmeFixedStorage128 *>(m_upgradeBits) = accepted;
}

// WBDE3C90 names GetConflictResolveType at LivingWorldPlayer.cpp368;
// native2E0699..2E06B8 preserves the type44 switch and case0 field2B4.
// WB's case1 callee131AD00 is exactly return4. Retail folds that body at
// 4FB350 with the existing encoding-0 slot2 provider. The declaration below
// binds that physical body only: it does not identify the player's embedded
// +4C object as a motion channel. Its original type/method names are unknown.
// Rehome existing31B C++; no new coverage or original return-enum claim.
class BFME2Encoding0MotionChannel { public: virtual int UnknownSlot2(); };
int LivingWorldPlayer::GetConflictResolveType()
{
    switch (m_playerType) {
    case 0:
        return m_conflictResolveType;
    case 1:
        return reinterpret_cast<BFME2Encoding0MotionChannel *>(
            reinterpret_cast<char *>(this)+0x4C)->BFME2Encoding0MotionChannel::UnknownSlot2();
    case 2:
        return 3;
    default:
        return 3;
    }
}
