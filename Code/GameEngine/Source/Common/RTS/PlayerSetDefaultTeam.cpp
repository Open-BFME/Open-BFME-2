// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// Player::setDefaultTeam, retail 0x002ABC7E (114 bytes).
// Identity (target): WorldBuilder's debug Player.cpp names it (wb-lead
// 3/callgraph): build "team" + the player name, look the team up through the
// team factory and make it the default team, activating it.
// Retail callees in order: StringBase<char>::set (0x000055F5),
// AsciiString::concat (0x00006987), the rowed two-name
// TeamFactory::findTeam (0x003A3E37, owner name then team name) on
// the global at VA 0x00E028BC, then the AsciiString release (0x00036410).
// Layout (target-measured): player name +0x4C, default team +0x2EC; the team's
// active flag +0x5D and created flag +0x5E are both set when it was inactive
// (Zero Hour Team::setActive shape, donor naming).
#include "ascii_string.h"

#include "../../../Include/Common/TeamBFME2.h"

class TeamFactory
{
public:
	Team *findTeam(const AsciiString &owner, const AsciiString &name);
};

extern TeamFactory *TheTeamFactory;

class Player
{
public:
	void setDefaultTeam();

private:
	char m_pad000[0x4C];
	AsciiString m_playerName; // +0x4C
	char m_pad050[0x2EC - 0x50];
	Team *m_defaultTeam; // +0x2EC
};

void Player::setDefaultTeam()
{
	AsciiString teamName;
	teamName = "team";
	teamName.concat(m_playerName);
	Team *team = TheTeamFactory->findTeam(m_playerName, teamName);
	if (team)
	{
		m_defaultTeam = team;
		team->setActive();
	}
}
