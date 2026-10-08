// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
//
// ?setTemporaryTeam@Object@@QAEXPAVTeam@@@Z  0x00298480, 14B
// ?setTeam@Object@@QAEXPAVTeam@@@Z           0x00298AE4, 295B
// Zero Hour Object::setTeam / setTemporaryTeam (GameLogic/Object/Object.cpp).
// Target evidence: setTemporaryTeam forwards (team, false) to 0x00297379, the
// shape of ZH's setOrRestoreTeam(team, restoring); setTeam swaps a team whose
// controlling player fails the rowed 20B test 0x002AA231 (Player
// isPlayerActive per its pin) for ThePlayerList+0x18's +0x2EC team, then
// rebuilds the name at +0x308 from the team's +0x30 record (+0x10, '/',
// +0x14; TheEmptyString when null) or clears it, and BFME2 adds the
// notifications: +0x4C4 PartitionData::makeDirty, +0x4C8 0x00625840, +0x4CC
// 0x009A2350 init, the 0x00E01DBC Lua state (0x00333F37 then 0x00333E5B),
// and for a non-null team the +0x250 object's slot-31 result slot 92, the
// rowed TheRadar call 0x002D7FAE and updateUpgradeModules, finally +0x84 slot
// 13. Field and slot names past ZH's are placeholders.
typedef bool Bool;

#include "ascii_string.h"

class Player;
class Object;

class Team;
class TeamPrototype
{
public:
	char m_pad0[0x10];
	AsciiString m_name;		// +0x10
	AsciiString m_x14;		// +0x14
};

class Team
{
public:
	Player *getControllingPlayer() const;	// 0x0039D7CF
	char m_pad0[0x30];
	TeamPrototype *m_proto;		// +0x30
};

class BfmeMemberRV
{
public:
	Bool bfmeAskRV();			// 0x002AA231, Player::isPlayerActive
};

class Player
{
public:
	char m_pad0[0x2EC];
	Team *m_defaultTeam;		// +0x2EC
};

class PlayerList
{
public:
	char m_pad0[0x18];
	Player *m_neutral;		// +0x18
};
extern PlayerList *ThePlayerList;

class PartitionData { public: void makeDirty(); };
class Rva00625840 { public: void rva00625840(); };
class Rva009A2350 { public: void init(); };

struct LuaDrawableState
{
	void rva00333F37(Object *obj);	// 0x00333F37 (EH body over the Lua stack)
	void rva00333E5B(Object *obj);
};
extern LuaDrawableState *g_rva00A01DBCLuaState;

class Radar;
extern Radar *TheRadar;
class Rva002D7FAEOwner { public: void rva002D7FAE(Object *obj); };

template <int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};
template <> class BfmeVirtualSlots<0> {};

class BfmeTeamSink : public BfmeVirtualSlots<92>
{
public:
	virtual void onTeamChanged(Team *team);		// slot 92 (+0x170)
};

class BfmeDrawableView : public BfmeVirtualSlots<31>
{
public:
	virtual BfmeTeamSink *teamSink();		// slot 31 (+0x7C)
};

class BfmeObjectHook : public BfmeVirtualSlots<13>
{
public:
	virtual void onTeamSet();			// slot 13 (+0x34)
};

class Object
{
public:
	void setTeam(Team *team);
	void setTemporaryTeam(Team *team);
	void updateUpgradeModules();
private:
	void setOrRestoreTeam(Team *team, Bool restoring);

	char m_pad0[0x84];
	BfmeObjectHook *m_x84;			// +0x84
	char m_pad88[0x250 - 0x88];
	BfmeDrawableView *m_x250;		// +0x250
	char m_pad254[0x304 - 0x254];
	Team *m_team;				// +0x304
	AsciiString m_originalTeamName;		// +0x308
	char m_pad30C[0x4C4 - 0x30C];
	PartitionData *m_partitionData;		// +0x4C4
	Rva00625840 *m_x4C8;			// +0x4C8
	Rva009A2350 *m_x4CC;			// +0x4CC
};

// Team's prototype strings (+0x10, +0x14), or the empty string with no prototype.
// ?teamProtoName absent-from-retail
static inline const AsciiString &teamProtoName(const Team *team)
{
	return team->m_proto == 0 ? AsciiString::TheEmptyString : team->m_proto->m_name;
}

// ?teamProtoX14 absent-from-retail
static inline const AsciiString &teamProtoX14(const Team *team)
{
	return team->m_proto == 0 ? AsciiString::TheEmptyString : team->m_proto->m_x14;
}

void Object::setTemporaryTeam(Team *team)
{
	const Bool restoring = false;
	setOrRestoreTeam(team, restoring);
}

void Object::setTeam(Team *team)
{
	// In order to prevent spawning useful units for a player after he dies, we
	// just assign objects to the neutral player if we try to misbehave.
	if (team && !((BfmeMemberRV *)team->getControllingPlayer())->bfmeAskRV())
		team = ThePlayerList->m_neutral->m_defaultTeam;

	setTemporaryTeam(team);
	if (m_team)
	{
		m_originalTeamName = teamProtoName(m_team);
		m_originalTeamName += '/';
		m_originalTeamName += teamProtoX14(m_team);
	}
	else
	{
		m_originalTeamName.clear();
	}

	if (m_partitionData)
		m_partitionData->makeDirty();
	if (m_x4C8)
		m_x4C8->rva00625840();
	if (m_x4CC)
		m_x4CC->init();
	if (g_rva00A01DBCLuaState)
	{
		g_rva00A01DBCLuaState->rva00333F37(this);
		g_rva00A01DBCLuaState->rva00333E5B(this);
	}
	if (team)
	{
		BfmeDrawableView *draw = m_x250;
		if (draw)
		{
			BfmeTeamSink *sink = draw->teamSink();
			if (sink)
				sink->onTeamChanged(team);
		}
		((Rva002D7FAEOwner *)TheRadar)->rva002D7FAE(this);
		updateUpgradeModules();
	}
	BfmeObjectHook *hook = m_x84;
	if (hook)
		hook->onTeamSet();
}
