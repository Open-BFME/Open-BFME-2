// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?addTeamToList@Player@@QAEXPAVTeamPrototype@@@Z @0x002AE228 (42B): Zero
// Hour Player::addTeamToList verbatim: walk the team-prototype list at
// Player +0x32C (STLport list<TeamPrototype *>, node next +0, value +8; the
// list Player's other team walks such as 0x002AD9FD start from) and
// push_back the prototype when absent. Callers 0x0039D723 and 0x003A2BEC
// (TeamFactory / TeamPrototype side, as ZH's TeamPrototype ctor and
// setControllingPlayer call it).
//
// The out-of-line list<TeamPrototype *>::push_back it calls is 0x002ADCC7
// (26B; also called from 0x002B17CA and 0x004F35EC): insert(end(), x)
// through the pinned list insert 0x002ACF9C, the iterator passed by value.
#include <list>

class TeamPrototype;
typedef _STL::list<TeamPrototype *> PlayerTeamList;

class Player
{
public:
	void addTeamToList(TeamPrototype *team);

private:
	char m_pad[0x32C];
	PlayerTeamList m_playerTeamPrototypes;		// +0x32C
};

void Player::addTeamToList(TeamPrototype *team)
{
	for (PlayerTeamList::iterator it = m_playerTeamPrototypes.begin(); it != m_playerTeamPrototypes.end(); ++it)
	{
		if (team == *it)
			return;
	}
	m_playerTeamPrototypes.push_back(team);
}
