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

typedef bool Bool;
typedef int Int;
#define TRUE true
#define FALSE false

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

class TeamFactory
{
public:
	void clear();
	void initFromSides(SidesList *sides);
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
extern Rva00148F5ECache TheKey_playerName;
extern Rva00148F5ECache TheKey_playerIsHuman;
extern Rva00148F5ECache TheKey_playerEnemies;
extern Rva00148F5ECache TheKey_playerAllies;
extern Rva00148F5ECache TheKey_multiplayerIsLocal;

class Player
{
public:
	void initFromDict(const Dict *d);
	void setPlayerType(PlayerType t, Bool skirmish);
	void setDefaultTeam();
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
static inline void setBuildList(Player *p, BuildListInfo *buildList)
{
	((Rva002A99D2 *)p)->rva002A99D2(buildList);
}
static inline void setPlayerRelationship(Player *p, const Player *that, Relationship r)
{
	((Rva002ADF9C *)p)->rva002ADF9C(that, (Object *)r);
}

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

private:
	char m_pad04[0x10 - 4];
	Player *m_local;	// +0x10
	Int m_playerCount;	// +0x14
	Player *m_players[20];	// +0x18
};

__declspec(noinline) SidesInfo *SidesList::getSideInfo(Int i){return(i>=0 && i<m_numSides)?&m_sides[i]:0;}
__declspec(noinline) Player *PlayerList::getNthPlayer(Int i){if(i<0 || i>=20)return 0;return m_players[i];}
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
		AsciiString pname = d->getAsciiString(TheKey_playerName.get());
		if (pname.isEmpty())
			continue;	// it's neutral, which we've already done, so skip it.

		Player* p = m_players[m_playerCount++];
		p->initFromDict(d);

		// Multiplayer override
		Bool exists;	// throwaway, since we don't care if it exists
		if (d->getBool(TheKey_multiplayerIsLocal.get(), &exists))
		{
			setLocalPlayer(p);
			setLocal = true;
		}

		if (!setLocal && !TheNetwork && d->getBool(TheKey_playerIsHuman.get()))
		{
			setLocalPlayer(p);
			setLocal = true;
		}

		// Set the build list.
		setBuildList(p, TheSidesList->getSideInfo(i)->getBuildList());
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
		Player* p = findPlayerWithNameKey(NAMEKEY(d->getAsciiString(TheKey_playerName.get())));

		AsciiString tok;

		AsciiString enemies = d->getAsciiString(TheKey_playerEnemies.get());
		while (enemies.nextToken(&tok))
		{
			Player *p2 = findPlayerWithNameKey(NAMEKEY(tok));
			if (p2)
			{
				setPlayerRelationship(p, p2, ENEMIES);
			}
		}

		AsciiString allies = d->getAsciiString(TheKey_playerAllies.get());
		while (allies.nextToken(&tok))
		{
			Player *p2 = findPlayerWithNameKey(NAMEKEY(tok));
			if (p2)
			{
				setPlayerRelationship(p, p2, ALLIES);
			}
		}

		// finally, make sure self & neutral are correct.
		setPlayerRelationship(p, p, ALLIES);
		if (p != getNeutralPlayer())
			setPlayerRelationship(p, getNeutralPlayer(), NEUTRAL);

		p->setDefaultTeam();
	}

}
