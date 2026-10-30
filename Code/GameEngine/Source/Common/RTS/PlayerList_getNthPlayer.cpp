// cl: /O1 /arch:SSE /G7 /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii
//
// ?newGame@PlayerList@@UAEXXZ, retail 0x002a8008, 766 bytes. Banked partial (score 1.0) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// PlayerList::newGame, retail 0x002A8008 (766 bytes).
//
// Zero Hour's PlayerList::newGame (GameEngine/Source/Common/RTS/
// PlayerList.cpp) carried to BFME 2 over the views the body needs. Target
// facts read from retail: PlayerList keeps the local player at +0x10, the
// player count at +0x14 and the player array at +0x18 (slot 0 is the
// neutral player); SidesList's side count is +0x3C; a SidesInfo is
// { build list, Dict }; init() is virtual slot 1. Callees use the ledger's
// names: the static name keys through Rva00148F5ECache::get, the build-list
// setter Rva002A99D2 and the relationship setter Rva002ADF9C (whose rowed
// view types the relationship argument as Object*). TeamFactory::clear,
// TeamFactory::initFromSides and Player::initFromDict are pinned at their
// unrowed bodies. PlayerList.cpp keeps the Zero Hour body, which does not
// compile to this layout.
#include "ascii_string.h"
#include "unicode_string.h"
#include "../GameLogicObjectLookupView.h"

typedef bool Bool;
typedef int Int;
#define MAX_PLAYER_COUNT 20
#define BitTest(x, i) (((x) & (i)) != 0)

enum NameKeyType { NAMEKEY_INVALID = 0 };
enum Relationship { ENEMIES = 0, NEUTRAL = 1, ALLIES = 2 };
enum PlayerType { PLAYER_HUMAN = 0, PLAYER_COMPUTER = 1 };

class Object;
class BuildListInfo;

class Dict
{
public:
	AsciiString getAsciiString(Int key, Bool *exists = 0) const;
	Bool getBool(Int key, Bool *exists = 0) const;
};

class SidesInfo
{
public:
	BuildListInfo *getBuildList() { return m_pBuildList; }
	void releaseBuildList() { m_pBuildList = 0; }
	Dict *getDict() { return &m_dict; }

private:
	BuildListInfo *m_pBuildList;	// +0x00
	Dict m_dict; char m_tail[0x60-4-sizeof(Dict)];	// +0x04
};

class SidesList
{
public:
	SidesInfo *getSideInfo(Int side);
	Int getNumSides() const { return m_numSides; }

private:
	char m_pad[0x3C];
	Int m_numSides; SidesInfo m_sides[1];	// +0x3C
};
extern SidesList *TheSidesList;

class Team;
class TeamFactory
{
public:
	void clear();
	void initFromSides(SidesList *sides);
	Team *findTeam(const AsciiString &name);
	Team *findTeam(const AsciiString &owner, const AsciiString &name);
};
extern TeamFactory *TheTeamFactory;

class NetworkInterface;
extern NetworkInterface *TheNetwork;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
};
extern NameKeyGenerator *TheNameKeyGenerator;
#define NAMEKEY(x) (TheNameKeyGenerator->nameToKey(x))

// The rowed static-name-key cache: key() of TheKey_* is its get().
class Rva00148F5ECache
{
public:
	NameKeyType get();
};
class StaticNameKey;
extern const StaticNameKey TheKey_playerName;
extern Rva00148F5ECache TheKey_playerIsHuman;
extern Rva00148F5ECache TheKey_playerEnemies;
extern Rva00148F5ECache TheKey_playerAllies;
extern const StaticNameKey TheKey_multiplayerIsLocal;

class PlayerSub60
{
public:
	Int m_pad18[6]; // 0x18 bytes
	Int m_18; // +0x18 (Player+0x78)
	Int m_1C; // +0x1C (Player+0x7C)
};
typedef int PlayerMaskType;
enum
{
	ALLOW_SAME_PLAYER = 0x01,
	ALLOW_ALLIES = 0x02,
	ALLOW_ENEMIES = 0x04,
	ALLOW_NEUTRAL = 0x08
};


class PlayerTemplate
{
public:
	UnicodeString getDisplayName() const;
};

class Player
{
public:
	void initFromDict(const Dict *d);
	void setPlayerType(PlayerType t, Bool skirmish);
	void setDefaultTeam();
	PlayerMaskType getPlayerMask() const { return 1 << m_playerIndex; }
	Relationship getRelationship(const Team *that) const;
	Team *getDefaultTeam() const { return m_defaultTeam; }
	bool rva002AA245() const; // 0x002AA245
	bool isPlayerActive() const;
	int field5C() const { return m_5C; }
	int getPlayerIndex() const { return m_playerIndex; }

	unsigned char m_pad[0x34];
	PlayerTemplate *m_playerTemplate; // +0x34
	UnicodeString m_playerDisplayName; // +0x38
	unsigned char m_pad3C[0x54 - 0x3C];
	Int m_playerIndex; // +0x54
	unsigned char m_pad58[0x5C - 0x58];
	int m_5C; // +0x5C
	PlayerSub60 m_60; // +0x60
	unsigned char m_pad80[0x2EC - 0x80];
	Team *m_defaultTeam; // +0x2EC
};

// Rowed receivers of the build-list and relationship setters.
class Rva002A99D2
{
public:
	void rva002A99D2(void *buildList);
};
class Rva002ADF9C
{
public:
	void rva002ADF9C(const Player *that, Object *relationship);
};
static inline void setBuildList(Player *player, BuildListInfo *buildList)
{
	((Rva002A99D2 *)player)->rva002A99D2(buildList);
}
static inline void setPlayerRelationship(Player *player, const Player *that, Relationship r)
{
	((Rva002ADF9C *)player)->rva002ADF9C(that, (Object *)r);
}

class Rva002AA22AByteField
{
public:
	unsigned char get() const;
};
class ParticleSystem
{
public:
	bool isSaveable() const;
};
class PlayerList
{
public:
	virtual ~PlayerList();
	virtual void init();
	virtual void reset();
	virtual void update();
	virtual void newGame();

	Player *getNthPlayer(Int i);
	Player *getNeutralPlayer() { return m_players[0]; }
	Player *findPlayerWithNameKey(NameKeyType key);
	void setLocalPlayer(Player *player);

	Player *getPlayerFromMask(PlayerMaskType mask);
	Player *getEachPlayerFromMask(PlayerMaskType &maskToAdjust);
	int rva002A7C0B(bool flag);
	int rva002A7D30();
	PlayerMaskType getPlayersWithRelationship(Int srcPlayerIndex, unsigned int allowedRelationships, bool reverse);
	void rva002A8306(bool forward);
	int getPlayerCount() const { return m_playerCount; }

private:
	char m_pad04[0x10 - 4];
	Player *m_local;	// +0x10
	Int m_playerCount;	// +0x14
	Player *m_players[20];	// +0x18
};
extern PlayerList *ThePlayerList;

// Select-any copy of the body rowed in SidesList_getSideInfo.cpp.
__declspec(noinline) inline SidesInfo *SidesList::getSideInfo(Int i){return(i>=0 && i<m_numSides)?&m_sides[i]:0;}
// ?getNthPlayer@PlayerList@@QAEPAVPlayer@@H@Z
Player *PlayerList::getNthPlayer(Int i)
{
	if (i < 0 || i >= 20)
	{
		return NULL;
	}
	return m_players[i];
}

// ?getPlayerFromMask@PlayerList@@QAEPAVPlayer@@H@Z
Player *PlayerList::getPlayerFromMask(PlayerMaskType mask)
{
	if (mask == 0)
		return NULL;

	Player *player = NULL;
	Int i;

	for (i = 0; i < MAX_PLAYER_COUNT; i++)
	{
		player = getNthPlayer(i);
		if (player && player->getPlayerMask() == mask)
			return player;
	}
	return NULL;
}

// ?getEachPlayerFromMask@PlayerList@@QAEPAVPlayer@@AAH@Z
Player *PlayerList::getEachPlayerFromMask(PlayerMaskType &maskToAdjust)
{
	Player *player = NULL;
	Int i;

	for (i = 0; i < MAX_PLAYER_COUNT; i++)
	{
		player = getNthPlayer(i);
		if (player && BitTest(player->getPlayerMask(), maskToAdjust))
		{
			maskToAdjust &= (~player->getPlayerMask());
			return player;
		}
	}

	maskToAdjust = 0;
	return NULL;
}

int PlayerList::rva002A7C0B(bool flag)
{
	int count = 0;
	for (int i = 0; i < MAX_PLAYER_COUNT; i++)
	{
		Player *player = getNthPlayer(i);
		if (!player)
			continue;
		if (!player->rva002AA245())
			continue;
		if (((Rva002AA22AByteField *)player)->get())
			continue;
		if (((ParticleSystem *)player)->isSaveable())
			continue;
		if (flag)
		{
			PlayerSub60 *s = &player->m_60;
			if (s)
				count += s->m_18 + s->m_1C;
		}
		count++;
	}
	return count;
}

int PlayerList::rva002A7D30()
{
	int mask = 0;
	for (int i = 0; i < m_playerCount; i++)
	{
		Player *player = getNthPlayer(i);
		if (!player)
			continue;
		mask |= player->getPlayerMask();
	}
	return mask;
}

// ?getPlayersWithRelationship@PlayerList@@QAEHHI_N@Z, retail 0x002A7C70
// (192B). Zero Hour's PlayerList::getPlayersWithRelationship with two BFME
// additions read from the target: a flag that asks each other player's view
// of the source instead of the source's view of them, and a relationship
// outside the three (default case) that counts only when every ALLOW_ bit
// (0xF) is requested.
PlayerMaskType PlayerList::getPlayersWithRelationship(Int srcPlayerIndex, unsigned int allowedRelationships, bool reverse)
{
	PlayerMaskType retVal = 0;

	if (allowedRelationships == 0)
		return retVal;

	Player *srcPlayer = getNthPlayer(srcPlayerIndex);
	if (!srcPlayer)
		return retVal;

	if (BitTest(allowedRelationships, ALLOW_SAME_PLAYER))
		retVal = srcPlayer->getPlayerMask();

	for (Int i = 0; i < m_playerCount; ++i)
	{
		Player *player = getNthPlayer(i);
		if (!player)
			continue;

		if (player == srcPlayer)
			continue;

		Relationship r = !reverse ? srcPlayer->getRelationship(player->getDefaultTeam())
			: player->getRelationship(srcPlayer->getDefaultTeam());
		switch (r)
		{
			case ENEMIES:
				if (BitTest(allowedRelationships, ALLOW_ENEMIES))
					retVal |= player->getPlayerMask();
				break;
			case NEUTRAL:
				if (BitTest(allowedRelationships, ALLOW_NEUTRAL))
					retVal |= player->getPlayerMask();
				break;
			case ALLIES:
				if (BitTest(allowedRelationships, ALLOW_ALLIES))
					retVal |= player->getPlayerMask();
				break;
			default:
				if (allowedRelationships == 0xF)
					retVal |= player->getPlayerMask();
				break;
		}
	}

	return retVal;
}

void PlayerList::newGame()
{
	Int i;

	TheTeamFactory->clear(); // cleans up energy, among other things

	// first, re-init ourselves.
	init();

	// ok, now create the rest of players we need.
	Bool setLocal = false;
	for( i = 0; i < TheSidesList->getNumSides(); i++)
	{
		Dict *dict = TheSidesList->getSideInfo(i)->getDict();
		AsciiString pname = dict->getAsciiString(((Rva00148F5ECache *)&TheKey_playerName)->get());
		if (pname.isEmpty())
			continue;	// it's neutral, which we've already done, so skip it.

		Player* player = m_players[m_playerCount++];
		player->initFromDict(dict);

		// Multiplayer override
		Bool exists;	// throwaway, since we don't care if it exists
		if (dict->getBool(((Rva00148F5ECache *)&TheKey_multiplayerIsLocal)->get(), &exists))
		{
			setLocalPlayer(player);
			setLocal = true;
		}

		if (!setLocal && !TheNetwork && dict->getBool(TheKey_playerIsHuman.get()))
		{
			setLocalPlayer(player);
			setLocal = true;
		}

		// Set the build list.
		setBuildList(player, TheSidesList->getSideInfo(i)->getBuildList());
		// Build list is attached to player now, so release it from the side info.
		TheSidesList->getSideInfo(i)->releaseBuildList();
	}

	if (!setLocal)
	{
		for( i = 0; i < TheSidesList->getNumSides(); i++)
		{
			Player* player = getNthPlayer(i);
			if (player != getNeutralPlayer())
			{
				player->setPlayerType(PLAYER_HUMAN, false);
				setLocalPlayer(player);
				setLocal = true;
				break;
			}
		}
	}

	// must reset teams *after* creating players.
	TheTeamFactory->initFromSides(TheSidesList);

	for( i = 0; i < TheSidesList->getNumSides(); i++)
	{
		Dict *dict = TheSidesList->getSideInfo(i)->getDict();
		Player* player = findPlayerWithNameKey(NAMEKEY(dict->getAsciiString(((Rva00148F5ECache *)&TheKey_playerName)->get())));

		AsciiString tok;

		AsciiString enemies = dict->getAsciiString(TheKey_playerEnemies.get());
		while (enemies.nextToken(&tok))
		{
			Player *p2 = findPlayerWithNameKey(NAMEKEY(tok));
			if (p2)
			{
				setPlayerRelationship(player, p2, ENEMIES);
			}
		}

		AsciiString allies = dict->getAsciiString(TheKey_playerAllies.get());
		while (allies.nextToken(&tok))
		{
			Player *p2 = findPlayerWithNameKey(NAMEKEY(tok));
			if (p2)
			{
				setPlayerRelationship(player, p2, ALLIES);
			}
		}

		// finally, make sure self & neutral are correct.
		setPlayerRelationship(player, player, ALLIES);
		if (player != getNeutralPlayer())
			setPlayerRelationship(player, getNeutralPlayer(), NEUTRAL);

		player->setDefaultTeam();
	}

}

class BfmeMemberRV;
class BfmeThingRV
{
public:
	BfmeMemberRV *bfmePickRV();
	unsigned char m_bfmeHead[0x10]; // +0x00 BFME1 0xc
	BfmeMemberRV *m_bfmeMine; // +0x10
};

class Rva002A7DD0
{
public:
	bool rva002A7DD0();
private:
	char m_lead[0x10]; // +0x00
	BfmeMemberRV *m_ptr10; // +0x10 +0x10
};

class Rva002A7E42
{
public:
	void rva002A7E42(Player *player);
};

extern GameLogic *TheGameLogic;

class ControlBar
{
public:
	void rva0031BAC3(Player *);
	void setControlBarSchemeByPlayer(Player *);
	void setObservedPlayer(Player *player) { m_observedPlayer = player; }
	char m_pad00[0x210];
	Player *m_observedPlayer; // +0x210
};
extern ControlBar *TheControlBar;

class GameTextInterface
{
public:
#define V(n) virtual void v##n();
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09) V(10) V(11) V(12) V(13) V(14) V(15) V(16)
#undef V
	virtual UnicodeString *fetchPtr(const char *label, bool *exists = 0);	// +0x44
};
extern GameTextInterface *TheGameText;

class InGameUI
{
public:
#define V(n) virtual void v##n();
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18)
#undef V
	virtual void message(UnicodeString message, ...);	// +0x4C
};
extern InGameUI *TheInGameUI;

class PartitionManager;
extern PartitionManager *TheShroudManager;
class BfmeTaintManager;
extern BfmeTaintManager *TheTaintManager;

class PointGroupClass
{
public:
	enum PointModeEnum
	{
		TRIS = 0
	};
};
class Rva00739730 { public: void rva00739730(int playerIndex, int callback); };
class Rva006C0800 { public: void rva006C0800(PointGroupClass::PointModeEnum callback); };
void rva002D7AE0(int a, int b, int c);
void rva002D7B18(int a, int b, int c);

// ?rva002A8306@PlayerList@@QAEX_N@Z
// PlayerList::rva002A8306, retail 0x002A8306..0x002A851D 535 B.
// Observer cycling: callers AptPalantir::OnBttnObserveNextPlayer 0x002D3100
// (true) and ObservePriorPlayer 0x002D3108 (false) on ThePlayerList.
// WorldBuilder twin 0x00D24BE0 (unnamed; strings GUI:PlayerObservingAll and
// GUI:PlayerObservingSpecificHuman). When the list owner's local player is an
// observer (0x002A7DD0) and the game mode passes GameLogic::rva0042219 it
// steps the player index by +1 or -1 with wraparound from the observed player
// (0x002A7E14) skipping players with +0x5C set and inactive players other than
// the first inactive observer slot; then it stores the chosen player in
// TheControlBar+0x210 and posts the observing message through TheInGameUI
// slot 0x4C before re-registering the shroud / taint callbacks and the
// 0x002A7E42 refresh. Offsets and callees are target evidence.
// Inline accessors follow the debug twin's field reads and shared loop local.
// Native GameTextManager slot 0x44 returns a UnicodeString pointer.
// Retail compiles this after getNthPlayer in one unit; cl 7.1 reads that visible
// body when it allocates registers here, so the two stay together.
void PlayerList::rva002A8306(bool forward)
{
	if (!reinterpret_cast<Rva002A7DD0 *>(this)->rva002A7DD0())
		return;
	Player *player = reinterpret_cast<Player *>(reinterpret_cast<BfmeThingRV *>(ThePlayerList)->bfmePickRV());
	if (!player)
		return;
	if (!TheGameLogic->rva0042219())
		return;

	int step = forward ? 1 : -1;
	int index = player->getPlayerIndex();
	int observer = !player->isPlayerActive() ? player->getPlayerIndex() : -1;
	Player *p;
	int i;
	for (i = 0; i < ThePlayerList->getPlayerCount(); ++i) {
		p = ThePlayerList->getNthPlayer(i);
		if (observer == -1 && p && !p->isPlayerActive() && p->field5C() == 0)
			observer = i;
	}

	int start = index;
	for (;;) {
		index += step;
		int count = ThePlayerList->getPlayerCount();
		if (index >= count)
			index = 0;
		else if (index < 0)
			index = count;
		if (index == start)
			break;
		p = ThePlayerList->getNthPlayer(index);
		if (p && p->field5C() == 0) {
			if (p->isPlayerActive() || index == observer)
				break;
		}
	}

	player = ThePlayerList->getNthPlayer(index);
	TheControlBar->setObservedPlayer(player);

	UnicodeString message;
	UnicodeString unused;
	if (!player->isPlayerActive()) {
		message.format(TheGameText->fetchPtr("GUI:PlayerObservingAll"));
	} else {
		message.format(TheGameText->fetchPtr("GUI:PlayerObservingSpecificHuman"),
			player->m_playerDisplayName.str(), player->m_playerTemplate->getDisplayName().str());
	}
	TheInGameUI->message(message);

	if (TheShroudManager)
		reinterpret_cast<Rva00739730 *>(TheShroudManager)->rva00739730(player->getPlayerIndex(), (int)&rva002D7AE0);
	if (TheTaintManager)
		reinterpret_cast<Rva006C0800 *>(TheTaintManager)->rva006C0800((PointGroupClass::PointModeEnum)(int)&rva002D7B18);
	reinterpret_cast<Rva002A7E42 *>(this)->rva002A7E42(player);
}

// ?bfmeAnchorGetSideInfoCopy@@YAXPAVSidesList@@@Z absent-from-retail
void bfmeAnchorGetSideInfoCopy(SidesList *sidesList) { sidesList->getSideInfo(0); }
