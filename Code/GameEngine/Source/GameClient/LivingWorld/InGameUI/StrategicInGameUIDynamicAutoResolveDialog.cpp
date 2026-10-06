// cl: /O1 /MD /arch:SSE
// StrategicInGameUIDynamicAutoResolveDialog.cpp --
// StrategicInGameUI::DynamicAutoResolveDialog members at their WorldBuilder
// home (reverse/wb_name_leads.csv: WB's debug build names the file and the
// class and asserts battlePlayerID >= 0); retail supplies the bytes.
//
// Layout (target evidence): a player's data keeps the player at +0x00, its
// index among the battle's 0x34-byte player entries (key at +0x30, matched
// against the player's key at +0x14) at +0x04, three zeroed reals at
// +0x08..+0x10 and four zeroed words at +0x14..+0x20.

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
