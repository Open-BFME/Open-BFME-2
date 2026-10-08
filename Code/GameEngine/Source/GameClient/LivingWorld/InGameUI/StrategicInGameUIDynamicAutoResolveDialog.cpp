// cl: /O1 /G7 /MD /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// StrategicInGameUIDynamicAutoResolveDialog.cpp --
// StrategicInGameUI::DynamicAutoResolveDialog members at their WorldBuilder
// home (reverse/wb_name_leads.csv: WB's debug build names the file and the
// class and asserts battlePlayerID >= 0); retail supplies the bytes.
//
// Layout (target evidence): a player's data keeps the player at +0x00, its
// index among the battle's 0x34-byte player entries (key at +0x30, matched
// against the player's key at +0x14) at +0x04, three zeroed reals at
// +0x08..+0x10 and four zeroed words at +0x14..+0x20.

#include <map>

typedef int Int;
typedef float Real;

struct DynamicAutoResolvePlayer
{
	unsigned char m_pad00[0x14];
	Int m_key;						// +0x14
};

struct DynamicAutoResolveBattlePlayer
{
	unsigned char m_pad00[0x30];
	Int m_key;						// +0x30
};

struct DynamicAutoResolveBattlePlayers
{
	DynamicAutoResolveBattlePlayer *m_start;
	DynamicAutoResolveBattlePlayer *m_finish;

	Int size() const { return Int(m_finish - m_start); }
};

// The battle player index of a player, -1 when absent (inlined in retail).
static inline Int findBattlePlayerID(const DynamicAutoResolveBattlePlayers *players, const DynamicAutoResolvePlayer *player)
{
	Int count = players->size();
	for (Int i = 0; i < count; ++i)
	{
		if (players->m_start[i].m_key == player->m_key)
			return i;
	}
	return -1;
}

// The member at +0x20 is an object of its own whose constructor clears it
// (WB constructs it in place after the plain members).
struct DynamicAutoResolvePlayerHandle
{
	DynamicAutoResolvePlayerHandle() : m_ptr(0) {}
	void *m_ptr;
};

namespace StrategicInGameUI
{
	class DynamicAutoResolveDialog
	{
	public:
		class Impl
		{
		public:
			struct PlayerData
			{
				PlayerData(const DynamicAutoResolvePlayer *player, const DynamicAutoResolveBattlePlayers *players);

				const DynamicAutoResolvePlayer *m_player;	// +0x00
				Int m_battlePlayerID;				// +0x04
				Real m_08;					// +0x08
				Real m_0C;					// +0x0C
				Real m_10;					// +0x10
				Int m_14;					// +0x14
				Int m_18;					// +0x18
				Int m_1C;					// +0x1C
				DynamicAutoResolvePlayerHandle m_20;		// +0x20
			};

			class ShowBattleStepStateHandler;
			class ClosingStateHandler;
			class MovieClip;
			class PlayerPanelMovieClip;
		};
	};
}

// StrategicInGameUI::DynamicAutoResolveDialog::Impl::PlayerData::PlayerData,
// retail 0x005EA6A7 (100 bytes).
StrategicInGameUI::DynamicAutoResolveDialog::Impl::PlayerData::PlayerData(const DynamicAutoResolvePlayer *player, const DynamicAutoResolveBattlePlayers *players)
	: m_player(player),
	  m_battlePlayerID(findBattlePlayerID(players, player)),
	  m_08(0.0f),
	  m_0C(0.0f),
	  m_10(0.0f),
	  m_14(0),
	  m_18(0),
	  m_1C(0)
{
}

// ---- DynamicAutoResolveDialog::Impl::ShowBattleStepStateHandler
//
// Target facts: OnReinforceAnimDone 0x005EA7A7 (virtual, pointer at
// 0x008781AC; ret 8) counts down +0x0C and, at zero, starts the first hit
// animation (0x005EA33D, WorldBuilder StartFirstHitAnim; rowed
// address-named) while +0x08 is positive, else finishes (Done 0x005EA441).
// Done hands control back to the dialog's Impl (+0x04): 0x005EA0C0 when its
// +0x10 is set, else 0x005EA0F6 (both address-named; 0x005EA0F6 pinned).
struct Rva005EA4FCBattle
{
	char m_pad00[0x34];
	int m_id; // +0x34
};

// The dialog state viewed by slot: vslot 7 says whether a skip is allowed.
class Rva005EA4FCState
{
public:
	virtual void vslot0();
	virtual void vslot1();
	virtual void vslot2();
	virtual void vslot3();
	virtual void vslot4();
	virtual void vslot5();
	virtual void vslot6();
	virtual bool vslot7();
};

// A battle player's 0x34-byte entry starts with an int map (its
// _M_lower_bound is the rowed 0x00382A92).
struct Rva005EAEAFBattlePlayer
{
	std::map<int, int> m_map;	// +0x00
	unsigned char m_pad0c[0x34 - 0x0C];
};

struct Rva005EAEAFBattlePlayers
{
	Rva005EAEAFBattlePlayer *m_start;	// +0x00
};

// The +0x20 object of a unit entry: +0x08 is the unit's icon slot whose
// rowed 0x005FB846 is called once its hit animation finishes it.
class Rva005FB846
{
public:
	void rva005FB846();
};

struct Rva005EAEAFIcon
{
	unsigned char m_pad00[0x08];
	Rva005FB846 m_slot;			// +0x08
};

// A 0x24-byte unit entry of the dialog: its battle player index at +0x04
// and its remaining strength at +0x0C.
struct Rva005EAEAFUnit
{
	int m_00;
	int m_battlePlayer;			// +0x04
	Real m_reinforced;			// +0x08
	Real m_strength;			// +0x0C
	Real m_finalStrength;			// +0x10
	int m_14;				// +0x14, handed to the icon's 0x005FBB68
	unsigned char m_pad18[0x1C - 0x18];
	int m_numReinforcements;		// +0x1C
	Rva005EAEAFIcon *m_icon;		// +0x20, the unit's player panel
};

// The panel slot's rowed 0x005FBB83 (percent) and 0x005FBB68 setters.
class Rva005FBB68
{
public:
	void rva005FBB68(int value);
	void rva005FBB55(Real percent);
	void rva005FBB83(Real percent);
};

class Rva005FB84E
{
public:
	void rva005FB84E();
};

// The dialog's +0x34 object: its rowed 0x005FC19E flag setter and the
// unrowed forwarder 0x005FC1A6 (pinned).
class Rva005FC19E
{
public:
	void rva005FC19E(int value);
	void rva005FC1A6();
};

struct Rva005EAEAFUnits
{
	Rva005EAEAFUnit *m_start;
	Rva005EAEAFUnit *m_finish;
	Rva005EAEAFUnit *m_end;
};

class Rva005EA183
{
public:
	void rva005EA0C0();
	void rva005EA0F6();
	void rva005EA136(); // 0x005EA136 (pinned)

	int *m_counts; // +0x00, indexed by a casualty's +0x30 slot
	char m_pad04[0x0C - 0x04];
	Rva005EA4FCBattle *m_battle; // +0x0C
	Rva005EAEAFBattlePlayers *m_10; // +0x10
	Rva005EA4FCState *m_state; // +0x14
	Real m_totalStrength; // +0x18
	Rva005EAEAFUnits m_units[2]; // +0x1C
	Rva005FC19E *m_34; // +0x34
	char m_pad38[0x3C - 0x38];
	int m_key; // +0x3C
	char m_pad40[0x44 - 0x40];
	bool m_44; // +0x44
};

class GameMessage
{
public:
	void appendIntegerArgument(int arg);
};

class MessageStream
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual GameMessage *appendType(int type);
};
extern MessageStream *TheMessageStream;

class Rva005EA33D
{
public:
	void rva005EA33D();
};

// The entry the handler's 0x008781B4 slot visits: a real at +0x0C and the
// count slot at +0x30.
struct Rva005EA5E3Entry
{
	unsigned char m_pad00[0x0C];
	Real m_0C;				// +0x0C
	unsigned char m_pad10[0x30 - 0x10];
	int m_slot;				// +0x30
};

class StrategicInGameUI::DynamicAutoResolveDialog::Impl::ShowBattleStepStateHandler
{
public:
	virtual void OnHitAnimDone(int player, int unit); // pointer at 0x008781A8
	virtual void OnReinforceAnimDone(void *a, void *b);
	virtual bool v0050B5C6();                          // 0x008781B0, shared body
	virtual bool rva005EA5E3(const Rva005EA5E3Entry *entry); // 0x008781B4
	void Done();
	void StartReinforceAnims();

private:
	Rva005EA183 *m_owner; // +0x04
	int m_08; // +0x08
	int m_numReinforceAnimsToComplete; // +0x0C
};

void StrategicInGameUI::DynamicAutoResolveDialog::Impl::ShowBattleStepStateHandler::Done()
{
	if (m_owner->m_10)
		m_owner->rva005EA0C0();
	else
		m_owner->rva005EA0F6();
}

void StrategicInGameUI::DynamicAutoResolveDialog::Impl::ShowBattleStepStateHandler::OnReinforceAnimDone(void *a, void *b)
{
	if (--m_numReinforceAnimsToComplete > 0)
		return;
	if (m_08 > 0)
		((Rva005EA33D *)this)->rva005EA33D();
	else
		Done();
}

// Whether the battle player's map reaches the key (inlined in retail).
static inline bool HoldsKey(std::map<int, int> &map, int key)
{
	return map.lower_bound(key) != map.end();
}

// ShowBattleStepStateHandler::OnHitAnimDone, retail 0x005EAEAF (106 bytes,
// virtual, pointer at 0x008781A8; WorldBuilder name, wb-name-unverified):
// a unit whose strength is gone, and whose battle player no longer holds
// the dialog's key, has its icon finished; the last pending hit finishes
// the step.
// ?StrategicInGameUI::DynamicAutoResolveDialog::Impl::ShowBattleStepStateHandler::OnHitAnimDone present-unmatched
void StrategicInGameUI::DynamicAutoResolveDialog::Impl::ShowBattleStepStateHandler::OnHitAnimDone(int player, int unit)
{
	Rva005EA183 *owner = m_owner;
	Rva005EAEAFUnit *entry = &owner->m_units[player].m_start[unit];
	if (entry->m_strength <= 0.0f)
	{
		Rva005EAEAFBattlePlayers *players = owner->m_10;
		if (!players || !HoldsKey(players->m_start[entry->m_battlePlayer].m_map, owner->m_key))
			entry->m_icon->m_slot.rva005FB846();
	}
	if (--m_08 <= 0)
		Done();
}

// Retail 0x005EA5E3, 31 bytes, ShowBattleStepStateHandler's slot at
// 0x008781B4 (unnamed in WorldBuilder): counts an entry with a positive
// +0x0C into the dialog's per-slot counts; always continues.
bool StrategicInGameUI::DynamicAutoResolveDialog::Impl::ShowBattleStepStateHandler::rva005EA5E3(const Rva005EA5E3Entry *entry)
{
	if (!(entry->m_0C <= 0.0f))
		++m_owner->m_counts[entry->m_slot];
	return true;
}

// MovieClip::OnSkipButtonClicked 0x005EA4FC (virtual, pointer at 0x008781E8;
// WorldBuilder name): when the dialog state allows it (vslot 7), appends
// message 0x6BE with the battle's id (+0x0C -> +0x34) and tail-calls the
// dialog Impl's 0x005EA136.
class StrategicInGameUI::DynamicAutoResolveDialog::Impl::MovieClip
{
public:
	virtual void OnSkipButtonClicked();

private:
	int m_04;
	Rva005EA183 *m_impl; // +0x08
};

void StrategicInGameUI::DynamicAutoResolveDialog::Impl::MovieClip::OnSkipButtonClicked()
{
	if (!m_impl->m_state->vslot7())
		return;
	GameMessage *msg = TheMessageStream->appendType(0x6BE);
	msg->appendIntegerArgument(m_impl->m_battle->m_id);
	m_impl->rva005EA136();
}

// The banner clip slots (+0x08 of the player panel): set slot i's banner
// (0x005FBB96, pinned) and the visible count (0x005FBB9E, rowed); both
// address-named.
class Rva005FBB9E
{
public:
	void rva005FBB96(int slot, int banner);
	void rva005FBB9E(int count);
};

// PlayerPanelMovieClip::DequeueBanner 0x005EA05D (WorldBuilder name): drops
// the first queued banner (+0x20, count +0x1C), shifting the rest down into
// their slots, then updates the visible count.
class StrategicInGameUI::DynamicAutoResolveDialog::Impl::PlayerPanelMovieClip
{
public:
	void DequeueBanner();

private:
	int m_00;
	int m_04;
	Rva005FBB9E m_slots; // +0x08
	char m_pad09[0x1C - 0x09];
	int m_numBanners; // +0x1C
	int m_banners[1]; // +0x20
};

void StrategicInGameUI::DynamicAutoResolveDialog::Impl::PlayerPanelMovieClip::DequeueBanner()
{
	--m_numBanners;
	for (int i = 0; i < m_numBanners; ++i)
	{
		m_banners[i] = m_banners[i + 1];
		m_slots.rva005FBB96(i, m_banners[i]);
	}
	m_slots.rva005FBB9E(m_numBanners);
}

// ShowBattleStepStateHandler::StartReinforceAnims, retail 0x005EA396 (171
// bytes; WorldBuilder name, wb-name-unverified): for each reinforced unit of
// both sides, shows its gain as a percent of the dialog's total strength,
// sets its panel's 0x005FBB68 value and drops one queued banner per
// reinforcement.
void StrategicInGameUI::DynamicAutoResolveDialog::Impl::ShowBattleStepStateHandler::StartReinforceAnims()
{
	for (int side = 0; side < 2; ++side)
	{
		Rva005EAEAFUnit *end = m_owner->m_units[side].m_finish;
		for (Rva005EAEAFUnit *unit = m_owner->m_units[side].m_start; unit != end; ++unit)
		{
			if (unit->m_numReinforcements > 0)
			{
				Real gain = _STL::max(unit->m_strength - unit->m_reinforced, 0.0f);
				((Rva005FBB68 *)&unit->m_icon->m_slot)->rva005FBB83(gain / m_owner->m_totalStrength * 100.0f);
				((Rva005FBB68 *)&unit->m_icon->m_slot)->rva005FBB68(unit->m_14);
				for (int i = unit->m_numReinforcements; i > 0; --i)
					((PlayerPanelMovieClip *)unit->m_icon)->DequeueBanner();
			}
		}
	}
}

// ClosingStateHandler: the dialog state shown while the dialog closes;
// Startup is its virtual at 0x00878138 and +0x04 is the dialog Impl.
class StrategicInGameUI::DynamicAutoResolveDialog::Impl::ClosingStateHandler
{
public:
	virtual void v00();
	virtual void v01();
	virtual void Startup();

private:
	Rva005EA183 *m_owner; // +0x04
};

// ClosingStateHandler::Startup, retail 0x005EA46F (141 bytes; WorldBuilder
// name, wb-name-unverified): shows every unit's final strength as a percent
// of the dialog's total and marks it alive or finished, then hands the
// +0x44 test to the +0x34 object and runs its 0x005FC1A6.
void StrategicInGameUI::DynamicAutoResolveDialog::Impl::ClosingStateHandler::Startup()
{
	for (int side = 0; side < 2; ++side)
	{
		Rva005EAEAFUnit *end = m_owner->m_units[side].m_finish;
		for (Rva005EAEAFUnit *unit = m_owner->m_units[side].m_start; unit != end; ++unit)
		{
			((Rva005FBB68 *)&unit->m_icon->m_slot)->rva005FBB55(unit->m_finalStrength / m_owner->m_totalStrength * 100.0f);
			if (unit->m_finalStrength > 0.0f)
				((Rva005FB84E *)&unit->m_icon->m_slot)->rva005FB84E();
			else
				unit->m_icon->m_slot.rva005FB846();
		}
	}
	m_owner->m_34->rva005FC19E(m_owner->m_44 == 0);
	m_owner->m_34->rva005FC1A6();
}
