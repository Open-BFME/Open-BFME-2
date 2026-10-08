// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// Player::setDefaultTeam, retail 0x002ABC7E (114 bytes).
// Identity (target): WorldBuilder's debug Player.cpp names it (wb-lead
// 3/callgraph): build "team" + the player name, look the team up through the
// team factory and make it the default team, activating it.
// Retail callees in order: StringBase<char>::set (0x000055F5),
// AsciiString::concat (0x00006987), the rowed TeamFactory findTeam shape
// Rva0039FE6COwner::rva003A3E37 (0x003A3E37, owner name then team name) on
// the global at VA 0x00E028BC, then the AsciiString release (0x00036410).
// Layout (target-measured): player name +0x4C, default team +0x2EC; the team's
// active flag +0x5D and created flag +0x5E are both set when it was inactive
// (Zero Hour Team::setActive shape, donor naming).
#include "ascii_string.h"

class Team
{
public:
	void setActive()
	{
		if (!m_active)
		{
			m_created = true;
			m_active = true;
		}
	}

private:
	char m_pad00[0x5D];
	bool m_active; // +0x5D
	bool m_created; // +0x5E
};

// Address-named team factory receiver of the rowed findTeam shape.
class Rva0039FE6COwner
{
public:
	Team *rva003A3E37(const AsciiString &owner, const AsciiString &name);
};

extern class TeamFactory *TheTeamFactory;	// Player.cpp's global, read through this view

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
	Team *team = ((Rva0039FE6COwner *)TheTeamFactory)->rva003A3E37(m_playerName, teamName);
	if (team)
	{
		m_defaultTeam = team;
		team->setActive();
	}
}
