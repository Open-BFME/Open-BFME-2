// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?createEmptyTeam@TeamFactory@@QAEPAVTeam@@PAVPlayer@@@Z, retail 0x003A3CD9
// (229 bytes).
// Identity (target): WorldBuilder's debug Team.cpp:566..570
// TeamFactory::createEmptyTeam formats the "__TempTeam%d" name (retail
// literal 0x00C1AF28) and calls, in retail's order, Dict::Dict,
// AsciiString::format, operator new, the TeamPrototype constructor
// (0x003A3299), operator new and Team::Team (WB-named, 0x003A39A7), then the
// string and Dict teardown.
// Layout (target): the factory's prototype id counter at +0xBC (the name
// uses id+1, the constructor ++id) and team id counter at +0xC0; the
// player's name at +0x4C passed as the prototype's owner name; a 0x338-byte
// prototype marked singleton with the empty Dict; a 0x13C-byte Team.
#include "ascii_string.h"

class Dict
{
public:
	Dict(int numPairsToPreAllocate = 0);
	~Dict() { releaseData(); }

private:
	void releaseData();
	void *m_data;
};

class TeamFactory;

class Player
{
public:
	const AsciiString &getPlayerNameStr() const { return m_playerName; }

private:
	unsigned char m_pad00[0x4C];
	AsciiString m_playerName; // +0x4C
};

class TeamPrototype
{
public:
	TeamPrototype(TeamFactory *tf, const AsciiString &owner, const AsciiString &name,
		Player *ownerPlayer, bool isSingleton, Dict *d, int id);

private:
	unsigned char m_pad00[0x338];
};

class Team
{
public:
	Team(TeamPrototype *proto, int id);

private:
	unsigned char m_pad00[0x13C];
};

class TeamFactory
{
public:
	Team *createEmptyTeam(Player *player);

private:
	unsigned char m_pad00[0xBC];
	int m_uniqueTeamPrototypeID; // +0xBC
	int m_uniqueTeamID; // +0xC0
};

Team *TeamFactory::createEmptyTeam(Player *player)
{
	Dict d;
	AsciiString teamName;
	teamName.format("__TempTeam%d", m_uniqueTeamPrototypeID + 1);
	TeamPrototype *tp = new TeamPrototype(this, player->getPlayerNameStr(), teamName, player, true, &d, ++m_uniqueTeamPrototypeID);
	if (!tp)
		return 0;
	return new Team(tp, ++m_uniqueTeamID);
}
