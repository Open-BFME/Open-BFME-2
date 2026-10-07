// ?newGame@PlayerList@@UAEXXZ
// partial score=0.6 date=2026-10-07
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
//
// Three PlayerList virtuals that hand one Player call to each of the twenty
// player slots (the inline pointer array at +0x18; MAX_PLAYER_COUNT is 20 in
// BFME2, see PlayerList_getNthPlayer.cpp), in vtable 0x00BFD618:
//
//   slot 10  0x002A7AB6  PlayerList::update   -> Player::update 0x002AE770
//   slot 16  0x002A7ACE  rva002A7ACE          -> Player 0x002A99FA
//   slot 15  0x002A7AE6  rva002A7AE6          -> Player 0x002B0D00
//
// Slot 10 is SubsystemInterface::update's slot (GameEngine's update sits in
// slot 10 of its table too), and Zero Hour's PlayerList::update is this loop
// over Player::update; that pairing names the first body and its callee
// (inference). Zero Hour's other two such loops, newMap and updateTeamStates,
// are not virtual there, and the two Player callees do not show which is
// which, so slots 15 and 16 keep address names.
//
// Slot 1, 0x002A7EF1, is Zero Hour's PlayerList::init verbatim (one player
// counted, every player re-initialised with no template, the neutral player
// made local), over the same twenty slots; its two callees take Zero Hour's
// names, Player::init and PlayerList::setLocalPlayer (the latter swaps the
// local player at +0x10, ret 4).

#include "ascii_string.h"

typedef bool Bool;
typedef int Int;

#define MAX_PLAYER_COUNT 20

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

enum PlayerType
{
	PLAYER_HUMAN,
	PLAYER_COMPUTER
};

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL,
	ALLIES
};

// The NameKey caches the Dict keys are read through (rowed get 0x00148F5E).
class Rva00148F5ECache
{
public:
	NameKeyType get();

private:
	NameKeyType m_key;
	const char *m_name;
};

extern Rva00148F5ECache g_00DBDE24;	///< playerName
extern Rva00148F5ECache g_00DBDE2C;	///< playerIsHuman
extern Rva00148F5ECache g_00DBDE4C;	///< playerEnemies
extern Rva00148F5ECache g_00DBDE54;	///< playerAllies
extern Rva00148F5ECache g_00DBDE8C;	///< multiplayerIsLocal

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

#define NAMEKEY(s) TheNameKeyGenerator->nameToKey(s)

class Dict
{
public:
	Bool getBool(NameKeyType key, Bool *exists = 0) const;
	AsciiString getAsciiString(int key, Bool *exists = 0) const;

private:
	void *m_data;
};

class BuildListInfo;

struct SidesInfo
{
	BuildListInfo *getBuildList() { return m_pBuildList; }
	void releaseBuildList() { m_pBuildList = 0; }
	Dict *getDict() { return &m_dict; }

	BuildListInfo *m_pBuildList;
	Dict m_dict;
};

class SidesList
{
public:
	Int getNumSides() { return m_numSides; }
	SidesInfo *getSideInfo(Int side);

private:
	unsigned char m_pad[0x3C];
	Int m_numSides;
};

extern SidesList *TheSidesList;

class TeamFactory
{
public:
	void clear();
	void initFromSides(SidesList *sides);
};

extern TeamFactory *TheTeamFactory;

class Network;
extern Network *TheNetwork;

class PlayerTemplate;
class Object;

class Player
{
public:
	void init(const PlayerTemplate *pt);	///< pinned 0x002AF729 (ZH name)
	void update();							///< pinned 0x002AE770 (ZH name, inferred)
	void rva002A99FA();
	void rva002B0D00();
	void initFromDict(const Dict *d);
	void setPlayerType(PlayerType t, Bool skirmish);
	void setDefaultTeam();
};

// Player::setBuildList and Player::setPlayerRelationship are rowed under
// address names; these views call them by those names.
class Rva002A99D2
{
public:
	void rva002A99D2(void *pBuildList);
};

class Rva002ADF9C
{
public:
	void rva002ADF9C(const Player *that, Object *r);
};

#define SET_BUILD_LIST(p, b) reinterpret_cast<Rva002A99D2 *>(p)->rva002A99D2(b)
#define SET_RELATIONSHIP(p, that, r) reinterpret_cast<Rva002ADF9C *>(p)->rva002ADF9C(that, (Object *)(r))

class PlayerList
{
public:
	virtual ~PlayerList();
	virtual void init();
	virtual void update();
	virtual void rva002A7ACE();
	virtual void rva002A7AE6();
	virtual void newGame();

	Player *getNeutralPlayer() { return m_players[0]; }
	Player *getNthPlayer(Int i);
	Player *findPlayerWithNameKey(NameKeyType key);
	void setLocalPlayer(Player *player);	///< pinned 0x002A7B34 (ZH name)

private:
	char m_unmodelled_04[0x10 - 0x04];
	Player *m_local;						// +0x10

	Int m_playerCount;						// +0x14
	Player *m_players[MAX_PLAYER_COUNT];	// +0x18
};

void PlayerList::init()
{
	m_playerCount = 1;
	m_players[0]->init(0);

	for (Int i = 1; i < MAX_PLAYER_COUNT; i++)
		m_players[i]->init(0);

	// call setLocalPlayer so that becomingLocalPlayer() gets called appropriately
	setLocalPlayer(m_players[0]);
}

void PlayerList::update()
{
	for (Int i = 0; i < MAX_PLAYER_COUNT; i++)
		m_players[i]->update();
}

void PlayerList::rva002A7ACE()
{
	for (Int i = 0; i < MAX_PLAYER_COUNT; i++)
		m_players[i]->rva002A99FA();
}

void PlayerList::rva002A7AE6()
{
	for (Int i = 0; i < MAX_PLAYER_COUNT; i++)
		m_players[i]->rva002B0D00();
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
		Dict *d = TheSidesList->getSideInfo(i)->getDict();
		AsciiString pname = d->getAsciiString(g_00DBDE24.get());
		if (pname.isEmpty())
			continue;	// it's neutral, which we've already done, so skip it.

		Player* p = m_players[m_playerCount++];
		p->initFromDict(d);

		// Multiplayer override
		Bool exists;	// throwaway, since we don't care if it exists
		if (d->getBool(g_00DBDE8C.get(), &exists))
		{
			setLocalPlayer(p);
			setLocal = true;
		}

		if (!setLocal && !TheNetwork && d->getBool(g_00DBDE2C.get()))
		{
			setLocalPlayer(p);
			setLocal = true;
		}

		// Set the build list.
		SET_BUILD_LIST(p, TheSidesList->getSideInfo(i)->getBuildList());
		// Build list is attached to player now, so release it from the side info.
		TheSidesList->getSideInfo(i)->releaseBuildList();
	}

	if (!setLocal)
	{
		for( i = 0; i < TheSidesList->getNumSides(); i++)
		{
			Player* p = getNthPlayer(i);
			if (p != getNeutralPlayer())
			{
				p->setPlayerType(PLAYER_HUMAN, false);
				setLocalPlayer(p);
				setLocal = true;
				break;
			}
		}
	}

	// must reset teams *after* creating players.
	TheTeamFactory->initFromSides(TheSidesList);

	for( i = 0; i < TheSidesList->getNumSides(); i++)
	{
		Dict *d = TheSidesList->getSideInfo(i)->getDict();
		Player* p = findPlayerWithNameKey(NAMEKEY(d->getAsciiString(g_00DBDE24.get())));

		AsciiString tok;

		AsciiString enemies = d->getAsciiString(g_00DBDE4C.get());
		while (enemies.nextToken(&tok))
		{
			Player *p2 = findPlayerWithNameKey(NAMEKEY(tok));
			if (p2)
				SET_RELATIONSHIP(p, p2, ENEMIES);
		}

		AsciiString allies = d->getAsciiString(g_00DBDE54.get());
		while (allies.nextToken(&tok))
		{
			Player *p2 = findPlayerWithNameKey(NAMEKEY(tok));
			if (p2)
				SET_RELATIONSHIP(p, p2, ALLIES);
		}

		// finally, make sure self & neutral are correct.
		SET_RELATIONSHIP(p, p, ALLIES);
		if (p != getNeutralPlayer())
			SET_RELATIONSHIP(p, getNeutralPlayer(), NEUTRAL);

		p->setDefaultTeam();
	}
}
