// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ?setTemporaryTeam@Object@@QAEXPAVTeam@@@Z  0x00298480, 14B
// ?setTeam@Object@@QAEXPAVTeam@@@Z           0x00298AE4, 295B
// ?setOrRestoreTeam@Object@@AAEXPAVTeam@@_N@Z 0x00297379, 563B
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
// 13. Field and slot names past ZH's are placeholders. setOrRestoreTeam is
// ZH's body plus BFME2's skirmish-AI registry UnRegister/Register
// (0x002A8F56/0x002A9365 on 0x00DFEEF8) around the switch when the controlling
// player changes. /EHsc: its temp AsciiStrings need the unwind table.
typedef bool Bool;

#include "ascii_string.h"

class Player;
class Object;

class Team;
struct TeamTemplateInfo
{
	char m_pad0[0xFC];
	int m_initialTeamAttitude;	// +0xFC (proto +0x228)
};

class TeamPrototype
{
public:
	char m_pad0[0x10];
	AsciiString m_name;		// +0x10
	AsciiString m_x14;		// +0x14
	char m_pad18[0x12C - 0x18];
	TeamTemplateInfo m_templateInfo;	// +0x12C
	const TeamTemplateInfo *getTemplateInfo() const { return &m_templateInfo; }
};

class Team
{
public:
	Player *getControllingPlayer() const;	// 0x0039D7CF
	void prependTo_TeamMemberList(Object *obj);	// 0x0028A75F
	void removeFrom_TeamMemberList(Object *obj);	// 0x0028A77F
	// Inline forwarder to Object::dlink_isInList_TeamMemberList (row 0x0028A74F
	// lives in TeamIsInTeamMemberList.cpp); dllimport keeps this TU from
	// emitting a duplicate copy.
	__declspec(dllimport) __forceinline bool isInList_TeamMemberList(Object *obj) const;
	char m_pad0[0x30];
	TeamPrototype *m_proto;		// +0x30
	char m_pad34[4];
	Object *m_members;		// +0x38 team member list head
};

class BfmeMemberRV
{
public:
	Bool bfmeAskRV();			// 0x002AA231, Player::isPlayerActive
};

class Player
{
public:
	void becomingTeamMember(Object *obj, bool yes);	// 0x002AD4EC
	char m_pad0[0x54];
	int m_playerIndex;		// +0x54
	char m_pad58[0x2EC - 0x58];
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
// g_rva00A01DBCLuaState is only an alias of the owned global TheLuaScriptEngine (ledger names column); this unit reads the owner through its own view type.
extern class LuaScriptEngine *TheLuaScriptEngine;
#define g_rva00A01DBCLuaState (*(LuaDrawableState * *)&TheLuaScriptEngine)

struct Rva002D76C6Owner;
class Radar
{
public:
	void removeObject(Rva002D76C6Owner *obj);	// 0x002D7714
	void addObject(Object *obj);	// 0x002D7FEC
};
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

class AttackPriorityInfo
{
public:
	char m_pad0[4];
	AsciiString m_name;		// +4
};

class AIUpdateInterface
{
public:
	void rva0026DE3B(int attitude);	// 0x0026DE3B (setAttitude)
	char m_pad0[0x70];
	const AttackPriorityInfo *m_attackInfo;	// +0x70
};

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

// The skirmish-AI object registry behind 0x00DFEEF8 (UnRegister 0x002A8F56, Register 0x002A9365).
class Rva002A8F24
{
public:
	void UnRegister(Object *obj);
	void rva002A9365(Object *obj);
};
extern Rva002A8F24 *TheSkirmishAIManager;

// RVO getter 0x00291775 over the prototype's attack-priority name (+0x318).
class Rva00291775AsciiField { public: AsciiString get() const; };
// The out-of-line nothrow StringBase<char>::isEmpty (0x00001E2F) retail calls.
static __forceinline bool isEmptyOutOfLine(const AsciiString &s) { return ((const StringBase<char> *)&s)->isEmpty(); }


class BfmeInGameUI : public BfmeVirtualSlots<36>
{
public:
	virtual void objectChangedTeam(Object *obj, int oldPlayerIndex, int newPlayerIndex);	// slot 36 (+0x90)
};
class InGameUI;
extern InGameUI *TheInGameUI;

class Drawable { public: void changedTeam(); };	// 0x002742AC

class Object
{
public:
	void setTeam(Team *team);
	void setTemporaryTeam(Team *team);
	void updateUpgradeModules();
	bool dlink_isInList_TeamMemberList(Object *const *pListHead) const;	// 0x0028A6C7
	void onCapture(Player *oldOwner, Player *newOwner);	// 0x002966A0
private:
	void setOrRestoreTeam(Team *team, Bool restoring);

	char m_pad0[0x84];
	BfmeObjectHook *m_x84;			// +0x84
	char m_pad88[0x250 - 0x88];
	BfmeDrawableView *m_x250;		// +0x250
	char m_pad254[4];
	AIUpdateInterface *m_ai;		// +0x258
	char m_pad25C[4];
	void *m_radarData;			// +0x260
	char m_pad264[0x304 - 0x264];
	Team *m_team;				// +0x304
	AsciiString m_originalTeamName;		// +0x308
	char m_pad30C[0x4C4 - 0x30C];
	PartitionData *m_partitionData;		// +0x4C4
	Rva00625840 *m_x4C8;			// +0x4C8
	Rva009A2350 *m_x4CC;			// +0x4CC
};

inline bool Team::isInList_TeamMemberList(Object *obj) const
{
	return obj->dlink_isInList_TeamMemberList(&m_members);
}

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

// Zero Hour Object::setOrRestoreTeam plus BFME2's skirmish-AI registry updates around the switch.
// Retail fetches the new team's player first and keeps it in ebx across the
// current team's call.
static inline Bool playersDiffer(Team *newTeam, Team *oldTeam) { Player *newPlayer = newTeam->getControllingPlayer(); return oldTeam->getControllingPlayer() != newPlayer; }
void Object::setOrRestoreTeam(Team *team, Bool restoring)
{
	if (m_team == team)
		return;

	Team *oldTeam = m_team;

	if (m_team)
	{
		Team *currentTeam = m_team;
		if (currentTeam->isInList_TeamMemberList(this))
		{
			currentTeam->removeFrom_TeamMemberList(this);
			m_team->getControllingPlayer()->becomingTeamMember(this, false);
		}
	}

	Bool playerChanged = m_team && team && playersDiffer(team, m_team);
	if (playerChanged)
		TheSkirmishAIManager->UnRegister(this);

	m_team = team;

	if (playerChanged)
		TheSkirmishAIManager->rva002A9365(this);

	if (m_team)
	{
		Team *currentTeam = m_team;
		if (!currentTeam->isInList_TeamMemberList(this))
		{
			currentTeam->prependTo_TeamMemberList(this);
			m_team->getControllingPlayer()->becomingTeamMember(this, true);
		}

		const TeamPrototype *proto = m_team->m_proto;
		if (proto && proto->getTemplateInfo())
		{
			AIUpdateInterface *ai = m_ai;
			if (ai)
			{
				ai->rva0026DE3B(proto->getTemplateInfo()->m_initialTeamAttitude);
				if (!isEmptyOutOfLine(((const Rva00291775AsciiField *)proto)->get()))
				{
					AsciiString name = ((const Rva00291775AsciiField *)proto)->get();
					const AttackPriorityInfo *info = TheScriptEngine->getAttackInfo(name);
					if (info && !isEmptyOutOfLine(info->m_name))
						ai->m_attackInfo = info;
				}
			}
		}
		Drawable *draw = (Drawable *)m_x84;
		if (draw)
			draw->changedTeam();
	}

	if (oldTeam && team && !restoring)
		onCapture(oldTeam->getControllingPlayer(), team->getControllingPlayer());

	if (m_radarData)
	{
		TheRadar->removeObject((Rva002D76C6Owner *)this);
		TheRadar->addObject(this);
	}

	int oldPlayerIndex = oldTeam ? oldTeam->getControllingPlayer()->m_playerIndex : -1;
	int newPlayerIndex = m_team ? m_team->getControllingPlayer()->m_playerIndex : -1;
	if (oldPlayerIndex != newPlayerIndex)
		((BfmeInGameUI *)TheInGameUI)->objectChangedTeam(this, oldPlayerIndex, newPlayerIndex);
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
