// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?initTeam@TeamFactory@@QAEXABVAsciiString@@0_NPAVDict@@@Z, retail 0x003A404D
// (168 bytes).
// Identity (target): WorldBuilder's debug Team.cpp TeamFactory::initTeam
// (callgraph lead, score 2) calls, in retail's order, the prototype lookup
// findTeamPrototype (0x0039FE6C), nameToKey, PlayerList::findPlayerWithNameKey,
// operator new, the prototype constructor and
// TeamFactory::createInactiveTeam (WB-named, 0x003A3B7E).
// Donor (Zero Hour TeamFactory::initTeam): an existing prototype is left
// alone; the owner defaults to the neutral player (ThePlayerList +0x18); a
// new TeamPrototype takes ++m_uniqueTeamPrototypeID (+0xBC); singletons get
// their inactive team at once. BFME 2 deltas (target): the lookup and
// createInactiveTeam are keyed by (owner name, team name), here the
// prototype's +0x10/+0x14 strings, and the constructor takes the owner name
// before the team name. The 0x338-byte allocation matches TeamPrototype's
// size (its instance-list head is at +0x334).
#include "ascii_string.h"

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &nameString);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Player;
class Dict;
class Team;
class TeamFactory;

class PlayerList
{
public:
	Player *findPlayerWithNameKey(NameKeyType key);
	Player *getNeutralPlayer() { return m_players[0]; }

private:
	unsigned char m_pad00[0x18];
	Player *m_players[1]; // +0x18
};

extern PlayerList *ThePlayerList;

class TeamPrototype
{
public:
	TeamPrototype(TeamFactory *tf, const AsciiString &owner, const AsciiString &name,
		Player *ownerPlayer, bool isSingleton, Dict *d, int id);

	const AsciiString &getOwnerName() const { return m_owner; }
	const AsciiString &getName() const { return m_name; }

private:
	unsigned char m_pad00[0x10];
	AsciiString m_owner; // +0x10
	AsciiString m_name; // +0x14
	unsigned char m_pad18[0x338 - 0x18];
};

class TeamFactory
{
public:
	void initTeam(const AsciiString &name, const AsciiString &owner, bool isSingleton, Dict *d);
	TeamPrototype *findTeamPrototype(const AsciiString &owner, const AsciiString &name);
	Team *createInactiveTeam(const AsciiString &owner, const AsciiString &name);

private:
	unsigned char m_pad00[0xBC];
	int m_uniqueTeamPrototypeID; // +0xBC
};

void TeamFactory::initTeam(const AsciiString &name, const AsciiString &owner, bool isSingleton, Dict *d)
{
	if (findTeamPrototype(owner, name) != 0)
		return;
	Player *pOwner = ThePlayerList->findPlayerWithNameKey(TheNameKeyGenerator->nameToKey(owner));
	if (!pOwner)
		pOwner = ThePlayerList->getNeutralPlayer();
	TeamPrototype *tp = new TeamPrototype(this, owner, name, pOwner, isSingleton, d, ++m_uniqueTeamPrototypeID);
	if (isSingleton)
		createInactiveTeam(tp->getOwnerName(), tp->getName());
}
