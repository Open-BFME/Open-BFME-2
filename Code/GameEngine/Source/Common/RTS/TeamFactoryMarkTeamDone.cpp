// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?markTeamDoneForTacticalAI@TeamFactory@@QAEXPAVTeam@@@Z, retail 0x0039FD98
// (121 bytes).
// Identity (target): WorldBuilder's debug Team.cpp:387..397 body
// TeamFactory::markTeamDoneForTacticalAI asserts team->getControllingPlayer()
// and (*it).second, and calls getControllingPlayer, Team::getName,
// nameToKey twice and the +0xB0 prototype map lower_bound (rowed 0x0039EA4E)
// in retail's order, then clears byte +0x31E of the found prototype.
// Layout (target): Team::m_proto +0x30 with the prototype name at +0x14
// (Team::getName inlined, AsciiString::TheEmptyString 0x00DE0878 for no
// prototype); the controlling player's name at +0x4C; the map key is
// (player name key, team name key), the same key/node shape as
// TeamFactoryFindPrototype.cpp (findPrototype 0x0039FE6C).
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

struct Rva0039D8FBKey
{
	int m_first;
	int m_second;
};

struct TeamPrototypeDoneView
{
	unsigned char m_pad000[0x14];
	AsciiString m_name; // +0x14
	unsigned char m_pad018[0x31E - 0x18];
	bool m_tacticalAIFlag31E; // +0x31E, cleared here; donor name unknown
};

struct Rva0039EA4ENode
{
	int m_color00;
	Rva0039EA4ENode *m_parent04;
	Rva0039EA4ENode *m_left08;
	Rva0039EA4ENode *m_right0C;
	Rva0039D8FBKey m_key10;
	TeamPrototypeDoneView *m_value18;
};

class Rva0039EA4E
{
public:
	Rva0039EA4ENode *rva0039EA4E(const Rva0039D8FBKey &key);
	Rva0039EA4ENode *m_header00;
};

class Player
{
public:
	const AsciiString &getPlayerNameStr() const { return m_playerName; }
private:
	unsigned char m_pad00[0x4C];
	AsciiString m_playerName; // +0x4C
};

class Team
{
public:
	Player *getControllingPlayer() const;
	const AsciiString &getName() const
	{
		return m_proto == 0 ? AsciiString::TheEmptyString : m_proto->m_name;
	}
private:
	unsigned char m_pad00[0x30];
	TeamPrototypeDoneView *m_proto; // +0x30
};

class TeamFactory
{
public:
	void markTeamDoneForTacticalAI(Team *team);
private:
	unsigned char m_pad00[0xB0];
	Rva0039EA4E m_prototypes; // +0xB0
};

void TeamFactory::markTeamDoneForTacticalAI(Team *team)
{
	if (!team->getControllingPlayer())
		return;
	int teamKey = TheNameKeyGenerator->nameToKey(team->getName());
	int playerKey = TheNameKeyGenerator->nameToKey(team->getControllingPlayer()->getPlayerNameStr());
	Rva0039D8FBKey key;
	key.m_first = playerKey;
	key.m_second = teamKey;
	Rva0039EA4ENode *it = m_prototypes.rva0039EA4E(key);
	if (it != m_prototypes.m_header00)
		it->m_value18->m_tacticalAIFlag31E = false;
}
