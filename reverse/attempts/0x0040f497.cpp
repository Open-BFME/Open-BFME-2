// ?Load@ArmySummary@@QAEX_N0H@Z
// partial score=0.43 date=2026-10-09
// cl: /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /EHsc
// stlport
// ?AddArmyEntry@ArmySummary@@QAEHABVRva004F6093Holder@@@Z @0x0040ECCF 128B
// Adds holder to sorted entry vector and broadcasts to listener list.
// Evidence: callees rowed (forEach 0x0040D8D6, Entry ctor 0x0040CB11,
// push_back 0x0040E8D1, Release 0x0007DEEF, forwarders 0x001FF3A9 slot0 and
// 0x005CC208 slot2); callers at 0x0040EE4E 0x0040F0CB 0x0040F178 0x0040F291
// 0x0040F428 0x004F7D07; vector at +0x40 and index at +0x3c shared with
// 0x0040ED4F; Entry (int plus Holder) and Holder layouts from
// stlport_sort_rva0040cb11entry.cpp.
// ?MergeUnitsFromArmy@ArmySummary@@QAEXAAV1@@Z @0x0040ED4F 314B: drains another
// instance's entries (back to front, notifying its listeners through vslots
// 4 and 3) into a holder vector, resets its flag at +0x14 and index to 1,
// then re-adds each holder here through AddArmyEntry. Target evidence: retail
// REL32s at 0x0040ED7A..0x0040EE75 and the shared +0x40/+0x3C layout. The
// /Ireference/shims/bfmealloc include matches the vector reserve/push_back
// copies; the visible entry ctor (noinline, holder copy kept out of line as
// at 0x0040CB11) lets MSVC keep the loop-2 holder in ESI across the call.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/arch:SSE /G7) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
#include <list>
#include "ascii_string.h"

enum ScienceType {};
class Object;

struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};

void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct Rva0040F454Target
{
	char m_pad00[4];
	AsciiString m_templateName;
	float m_value;
	char m_pad0C[0x90 - 0xC];
	int m_90;
	int m_94;
	char m_pad98[0xAC - 0x98];
	TargetRef00217D4C m_ac;
};

class Rva004F6093Holder
{
public:
	explicit Rva004F6093Holder(Rva0040F454Target *ptr) : m_ptr(ptr)
	{
		if (m_ptr)
			++m_ptr->m_ac.references;
	}
	Rva004F6093Holder(const Rva004F6093Holder &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr)
			++m_ptr->m_ac.references;
	}
	~Rva004F6093Holder()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(&m_ptr->m_ac);
	}
	Rva004F6093Holder &operator=(const Rva004F6093Holder &other)
	{
		if (this != &other)
		{
			if (other.m_ptr)
				++other.m_ptr->m_ac.references;
			if (m_ptr)
				ReleaseTreeHintRef00217D4C(&m_ptr->m_ac);
			m_ptr = other.m_ptr;
		}
		return *this;
	}

public:
	Rva0040F454Target *m_ptr;
};

// Retail's dtor (0x002B703F) was built under different EH flags; call it.
extern template _STL::vector<Rva004F6093Holder>::~vector();

class Rva0040CB11Entry
{
public:
	Rva0040CB11Entry(int key, const Rva004F6093Holder &val);

public:
	int m_first;
	Rva004F6093Holder m_second;
};

#pragma inline_depth(0)
inline __declspec(noinline) Rva0040CB11Entry::Rva0040CB11Entry(int key, const Rva004F6093Holder &val) : m_first(key), m_second(val)
{
}
#pragma inline_depth()

class Rva0040D8D6Listener
{
public:
	virtual void notify0(void *arg, int value);
	virtual void dummy();
	virtual void notify2(void *arg, int value);
	virtual void notify3(void *arg, int value);
	virtual void notify4(void *arg, int value);
};

class Rva0040D8D6List
{
public:
	void forEach(void (Rva0040D8D6Listener::*notify)(void *, int), void *arg, int value);

private:
	Rva0040D8D6Listener **m_begin;
	Rva0040D8D6Listener **m_end;
	Rva0040D8D6Listener **m_capacity;
	unsigned int m_index;
};

class INI;
struct Rva0040E534Input;

class ArmySummaryEntry : public Rva0040F454Target
{
public:
	ArmySummaryEntry();
	void Parse(INI *ini);

	char m_padB4[0xC5 - 0xB4];
	bool m_C5;
	char m_padC6[0xC8 - 0xC6];
};

class ArmySummary
{
public:
	int AddArmyEntry(const Rva004F6093Holder &holder);
	void MergeUnitsFromArmy(ArmySummary &other);
	static void parseArmyEntry(INI *ini, void *instance, void *store, const void *userData);
	void Load(bool tactical, bool first, int armyID);
	void LoadArmyEntry(Rva0040E534Input *entry, int count, _STL::list<Object *> *objects, int armyID);

private:
	char m_pad00[4];
	Rva0040D8D6List m_list;
	bool m_14;
	char m_pad15[0x1C - 0x15];
	int m_1C;
	char m_pad20[0x3C - 0x20];
	int m_next;
	_STL::vector<Rva0040CB11Entry, _STL::allocator<Rva0040CB11Entry> > m_vec;
	_STL::vector<ScienceType> m_4C;
	char m_pad58[0x60 - 0x58];
	int m_60;
};

int ArmySummary::AddArmyEntry(const Rva004F6093Holder &holder)
{
	int argVal = (int)holder.m_ptr;
	m_list.forEach(&Rva0040D8D6Listener::notify0, this, argVal);
	int old = m_next;
	m_next = old + 1;
	{
		m_vec.push_back(Rva0040CB11Entry(old, holder));
	}
	m_list.forEach(&Rva0040D8D6Listener::notify2, this, old);
	return old;
}

void ArmySummary::MergeUnitsFromArmy(ArmySummary &other)
{
	m_vec.reserve(m_vec.size() + other.m_vec.size());
	_STL::vector<Rva004F6093Holder> holders;
	holders.reserve(other.m_vec.size());
	while (!other.m_vec.empty())
	{
		Rva0040CB11Entry &back = other.m_vec.back();
		other.m_list.forEach(&Rva0040D8D6Listener::notify4, &other, back.m_first);
		Rva004F6093Holder holder(back.m_second);
		holders.push_back(holder);
		other.m_vec.pop_back();
		other.m_list.forEach(&Rva0040D8D6Listener::notify3, &other, (int)holder.m_ptr);
	}
	other.m_14 = false;
	other.m_next = 1;
	while (!holders.empty())
	{
		const Rva004F6093Holder holder(holders.back());
		holders.pop_back();
		AddArmyEntry(holder);
	}
}

// ?parseArmyEntry@ArmySummary@@SAXPAVINI@@PAX1PBX@Z @0x0040F077 121B: the
// "ArmyEntry" field parser (FieldParse row at 0x0083957C beside DisplayNameTag,
// Color, NightColor and SurvivalThreshhold; offset 0, so it reads the instance):
// news a 0xC8-byte ArmySummaryEntry (ctor 0x0040C351), parses it with 0x0040C5FA and
// adds the holder here. The method name follows the INI field name.
void ArmySummary::parseArmyEntry(INI *ini, void *instance, void *store, const void *userData)
{
	ArmySummaryEntry *army = new ArmySummaryEntry;
	Rva004F6093Holder holder(army);
	army->Parse(ini);
	((ArmySummary *)instance)->AddArmyEntry(holder);
}

class Rva0037EB1D
{
public:
	void rva0037EB1D(void *dest);

private:
	char m_pad00[0xA8];

public:
	int m_a8;
};

class BfmeY1038;
BfmeY1038 * __stdcall bfmeFind1038(int a);

// ?rva0040F10F@Rva002E2903Player@@QAEXPAVRva0037EB1D@@@Z @0x0040F10F 142B:
// called with ECX = the player found by 0x002B51F8 (caller 0x0037EBBA) but never
// reads it. Looks up the list by the source's +0xA8 id via bfmeFind1038, copies
// the source into a new ArmySummaryEntry (0x0037EB1D), bumps its +0x94 and adds it.
class Rva002E2903Player
{
public:
	void rva0040F10F(Rva0037EB1D *source);
};

void Rva002E2903Player::rva0040F10F(Rva0037EB1D *source)
{
	ArmySummary *list = (ArmySummary *)bfmeFind1038(source->m_a8);
	if (list != 0)
	{
		ArmySummaryEntry *army = new ArmySummaryEntry;
		Rva004F6093Holder holder(army);
		source->rva0037EB1D(army);
		++army->m_94;
		list->AddArmyEntry(holder);
	}
}

// ?Save@ArmySummarySystem@@QAEXPAVObject@@@Z @0x0040F19D 433B: WorldBuilder twin
// 0x0108C750 is ArmySummarySystem::Save (ArmySummary.cpp:1533..1601), caller
// GameLogic::LivingWorldTacticalBattleComplete (REL32 at 0x0023D92F) passes its
// object list. Gated by the TheGameLogic query 0x002034E9 it hands the region
// manager's current battle (0x0020E6B7) to 0x0040D43F, then for each listed object
// (next at +0x8C) owned by a living-world player (+0x3AC != -1) whose template
// carries KindOf bit 0x80 (byte +0x118 bit 0, the twin's BitFlags test inlined),
// not flagged at +0x438 bit 0 and with an army id at +0x45C, it news an
// ArmySummaryEntry, fills it through 0x00291198, marks +0x90 and bumps +0x94 and
// adds it to that army's summary. Then for each player with a living-world id it
// retrieves the heroes (UnitRevivalTracker at +0x738) and copies spell points,
// the +0x13C upgrade mask, the +0x2F0 science list and +0x14 to the
// LivingWorldPlayer. Offsets are target evidence; method names are the twin's.
class Player;
class GameLogic;
class PlayerList;
class LivingWorldLogic;
extern GameLogic *TheGameLogic;
extern PlayerList *ThePlayerList;
extern LivingWorldLogic *TheLivingWorldLogic;

class Rva002034E9Host { public: bool rva002034E9(); };
class Rva003F468D;
class Rva0020E6B7RegionManager { public: Rva003F468D *rva0020E6B7(); };
struct Rva0040F19DLivingWorldLogic { char pad00[0xb0]; Rva0020E6B7RegionManager *m_regions; };

struct Rva0040F19DTemplate { char pad00[0x118]; unsigned char m_kindOf118; };
struct Rva00291198Dest;
class Rva00291198Host { public: void rva00291198(Rva00291198Dest *dest); };

class Object
{
public:
	Player *getControllingPlayer() const;
	char pad00[4];
	Rva0040F19DTemplate *m_template;
	char pad08[0x8c - 0x8];
	Object *m_next;
	char pad90[0x438 - 0x90];
	unsigned char m_flags438;
	char pad439[0x45c - 0x439];
	int m_armyID;
};

struct BfmeFixedStorage128 { unsigned int m_bits[32]; };
class ArmySummarySystem;
class UnitRevivalTracker { public: void retrieveHeroesForArmySummary(ArmySummarySystem *system); };

class Player
{
public:
	char pad00[0x14];
	float m_14;
	char pad18[0x34 - 0x18];
	struct Rva0040F497Heroes *m_34;
	char pad38[0x13c - 0x38];
	BfmeFixedStorage128 m_upgrades;
	char pad1BC[0x2f0 - 0x1bc];
	_STL::vector<ScienceType> m_sciences;
	char pad2FC[0x3ac - 0x2fc];
	int m_livingWorldPlayerID;
	char pad3B0[0x738 - 0x3b0];
	UnitRevivalTracker m_revivalTracker;
};

class PlayerList
{
public:
	Player *getNthPlayer(int index);
	Player *Rva002A7A6F(int index);
	char pad00[0x14];
	int m_playerCount;
};

class Rva002E062EDwordSlot { public: void set(int value); };
class Rva002E15BC { public: void rva002E14E9(const BfmeFixedStorage128 &bits); };
class Rva002E2578 { public: void rva002E2578(const _STL::vector<ScienceType> &sciences); };
struct Rva0040F19DLivingWorldPlayer { char pad00[0x1c8]; float m_1C8; };
struct Rva002B488EResult;
class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *find(int id, unsigned int *index);
	Rva002B488EResult *rva002B488E(int id);
};

struct _Rva0040CA61Arg;

class ArmySummarySystem
{
public:
	void Save(Object *objects);
	void rva0040D43F(Rva003F468D *battle);
	void *rva0040D008(int key);
	int ComputePlayerEarnedSpellPoints(_Rva0040CA61Arg *player);
};

void ArmySummarySystem::Save(Object *objects)
{
	if (!reinterpret_cast<Rva002034E9Host *>(TheGameLogic)->rva002034E9())
		return;
	if (!objects)
		return;

	Rva003F468D *battle = reinterpret_cast<Rva0040F19DLivingWorldLogic *>(TheLivingWorldLogic)->m_regions->rva0020E6B7();
	if (battle)
		rva0040D43F(battle);

	for (Object *obj = objects; obj; obj = obj->m_next) {
		if (!obj)
			continue;
		Player *player = obj->getControllingPlayer();
		if (!player || player->m_livingWorldPlayerID == -1)
			continue;
		if (!(obj->m_template->m_kindOf118 & 1))
			continue;
		if (obj->m_flags438 & 1)
			continue;
		int armyID = obj->m_armyID;
		if (!armyID)
			continue;

		ArmySummaryEntry *army = new ArmySummaryEntry;
		Rva004F6093Holder holder(army);
		reinterpret_cast<Rva00291198Host *>(obj)->rva00291198(reinterpret_cast<Rva00291198Dest *>(army));
		holder.m_ptr->m_90 = 1;
		++holder.m_ptr->m_94;
		ArmySummary *summary = static_cast<ArmySummary *>(rva0040D008(armyID));
		if (summary)
			summary->AddArmyEntry(holder);
	}

	for (int i = 0; i < ThePlayerList->m_playerCount; ++i) {
		Player *player = ThePlayerList->getNthPlayer(i);
		if (!player || player->m_livingWorldPlayerID == -1)
			continue;
		player->m_revivalTracker.retrieveHeroesForArmySummary(this);
		int lwID = player->m_livingWorldPlayerID;
		Rva002E2903Player *lwPlayer = reinterpret_cast<Rva002BA8F1Logic *>(TheLivingWorldLogic)->find(lwID, 0);
		if (!lwPlayer)
			continue;
		reinterpret_cast<Rva002E062EDwordSlot *>(lwPlayer)->set(
			ComputePlayerEarnedSpellPoints(reinterpret_cast<_Rva0040CA61Arg *>(player)));
		reinterpret_cast<Rva002E15BC *>(lwPlayer)->rva002E14E9(player->m_upgrades);
		reinterpret_cast<Rva002E2578 *>(lwPlayer)->rva002E2578(player->m_sciences);
		reinterpret_cast<Rva0040F19DLivingWorldPlayer *>(lwPlayer)->m_1C8 = player->m_14;
	}
}

// ?Load@ArmySummary@@QAEX_N0H@Z @0x0040F497 846B: WorldBuilder twin 0x0108A7E0 is
// ArmySummary::Load (ArmySummary.cpp:905..945), already pinned; called by
// ArmySummarySystem::Load 0x0040F87E. Finds the living-world army by +0x1C
// (0x002B488E), its LivingWorldPlayer (army +0x54) and Player (+0x14 through
// 0x002A7A6F), and walks a sorted copy of the +0x40 entries twice: pass 0 takes
// templates with KindOf bit 90 (+0x110 bit 26), pass 1 the rest, skipping +0xC5
// entries unless the +0x60 limit exceeds sumUnflagged. A template named in the
// army's +0x28 list (or a static empty one) records the key in +0x4C; otherwise
// up to the entry's +0x90 count, capped on pass 1 by the 1000000 budget over
// the template's +0x618 cost, is loaded into a local object list. On a tactical
// first load outside game mode 3 the player's +0x34 hero names (+0xE8) are
// loaded too, and a non-empty list goes to the 0x0037FD2B placer (WB
// ArmyPlacer::PlaceLivingWorldArmy). Offsets are target evidence; names are the twin's.
class ThingFactory;
extern ThingFactory *TheThingFactory;
class Rva002D06CA { public: void *rva002D06CA(const AsciiString *name); };
struct Rva0040F497Template
{
	char pad00[0x64];
	AsciiString m_name;
	char pad68[0x110 - 0x68];
	unsigned int m_110;
	char pad114[0x618 - 0x114];
	int m_618;
};
struct Rva0040F497GameLogic { char pad00[0x114]; int m_mode; };
struct Rva0040F497Heroes { char pad00[0xe8]; _STL::vector<AsciiString> m_names; };
struct Rva002B488EResult { char pad00[0x54]; int m_playerID; };
struct Rva0040F497LivingWorldPlayer { char pad00[0x14]; int m_playerIndex; };
class Rva00318C32Ret { public: char pad00[0x28]; _STL::vector<AsciiString> m_names; };
class Rva00318C79Owner { public: Rva00318C32Ret *rva00318C32(); };
class Rva0040CF55Owner { public: int sumUnflagged() const; };

class Rva0037F57E
{
public:
	Rva0037F57E();
	virtual ~Rva0037F57E();
	void PlaceLivingWorldArmy(_STL::list<Object *> *objects, Rva002E2903Player *lwPlayer, Rva002B488EResult *army, bool strategic);
};

class Rva0040E0EB : public _STL::vector<Rva0040CB11Entry>
{
public:
	Rva0040E0EB(const _STL::vector<Rva0040CB11Entry> &other) : _STL::vector<Rva0040CB11Entry>(other) {}
	~Rva0040E0EB();
};

struct Rva0040F454Cmp { bool operator()(const Rva0040CB11Entry &a, const Rva0040CB11Entry &b) const; };
namespace _STL {
template <class _RandomAccessIter, class _Compare> void sort(_RandomAccessIter first, _RandomAccessIter last, _Compare comp);
}

void ArmySummary::Load(bool tactical, bool first, int armyID)
{
	Rva0037F57E placer;
	_STL::list<Object *> objects;

	int limit = m_60;
	bool overLimit = false;
	if (limit > 0 && limit > reinterpret_cast<const Rva0040CF55Owner *>(this)->sumUnflagged())
		overLimit = true;

	Rva0040E0EB sorted(m_vec);
	_STL::sort(sorted.begin(), sorted.end(), Rva0040F454Cmp());

	Rva002B488EResult *army = reinterpret_cast<Rva002BA8F1Logic *>(TheLivingWorldLogic)->rva002B488E(m_1C);
	if (!army)
		return;
	Rva002E2903Player *lwPlayer = reinterpret_cast<Rva002BA8F1Logic *>(TheLivingWorldLogic)->find(army->m_playerID, 0);
	if (!lwPlayer)
		return;
	Player *player = ThePlayerList->Rva002A7A6F(reinterpret_cast<Rva0040F497LivingWorldPlayer *>(lwPlayer)->m_playerIndex);
	if (!player)
		return;

	Rva00318C32Ret *info = reinterpret_cast<Rva00318C79Owner *>(army)->rva00318C32();
	static _STL::vector<AsciiString> s_noNames;
	const _STL::vector<AsciiString> *names = info ? &info->m_names : &s_noNames;

	int budget = 1000000;
	for (int pass = 0; pass < 2; ++pass) {
		for (unsigned int i = 0; i < sorted.size(); ++i) {
			ArmySummaryEntry *entry = static_cast<ArmySummaryEntry *>(sorted[i].m_second.m_ptr);
			if (entry->m_C5 && !overLimit)
				continue;
			Rva0040F497Template *tmpl = static_cast<Rva0040F497Template *>(
				reinterpret_cast<Rva002D06CA *>(TheThingFactory)->rva002D06CA(&entry->m_templateName));
			if (!tmpl)
				continue;
			if (((tmpl->m_110 >> 26) & 1) != (unsigned int)(pass == 0))
				continue;

			const AsciiString *it = names->begin();
			const AsciiString *end = names->end();
			bool found = false;
			while (!found && it != end) {
				if (it->compare(tmpl->m_name) == 0)
					found = true;
				++it;
			}

			if (found) {
				m_4C.push_back(*reinterpret_cast<const ScienceType *>(&sorted[i].m_first));
				continue;
			}

			Rva004F6093Holder *holder = &sorted[i].m_second;
			int cost = tmpl->m_618;
			int count = holder->m_ptr->m_90;
			if (cost > 0 && pass > 0)
				count = budget / cost;
			if (count > holder->m_ptr->m_90)
				count = holder->m_ptr->m_90;
			if (count > 0) {
				budget -= cost * count;
				LoadArmyEntry(reinterpret_cast<Rva0040E534Input *>(holder), count, &objects, 0);
			}
		}
	}

	if (reinterpret_cast<Rva0040F497GameLogic *>(TheGameLogic)->m_mode != 3 && tactical && first) {
		Rva0040F497Heroes *heroes = player->m_34;
		for (unsigned int j = 0; j < heroes->m_names.size(); ++j) {
			ArmySummaryEntry *hero = new ArmySummaryEntry;
			Rva004F6093Holder holder(hero);
			hero->m_templateName.set(heroes->m_names[j]);
			hero->m_90 = 1;
			LoadArmyEntry(reinterpret_cast<Rva0040E534Input *>(&holder), 1, &objects, armyID);
		}
	}

	if (!objects.empty())
		placer.PlaceLivingWorldArmy(&objects, lwPlayer, army, !tactical);
}
