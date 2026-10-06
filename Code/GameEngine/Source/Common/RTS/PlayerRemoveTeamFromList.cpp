// cl: /GX /MD
// stlport
// ?removeTeamFromList@Player@@QAEXPAVTeamPrototype@@@Z, RVA 0x002ABD48, size 75.
// Evidence (target): REL32 call at 0x003A0CDC from TeamPrototype::rva003A0CD1
// on m_owningPlayer with the prototype as argument; the body walks the
// STLport list at Player +0x32C (node next/prev/value), compares the value to
// the argument and erases the first hit through the out-of-line
// list::erase(iterator) at 0x002ABAC0 (hidden iterator return, iterator copied
// by value). Name and purpose carried from Zero Hour's
// Player::removeTeamFromList. Structural inference: the two empty walks
// before and after the search are debug-only list counts whose consumers the
// release build stripped; written here as the empty walks retail keeps.
#include <list>

class TeamPrototype;
typedef _STL::list<TeamPrototype *> PlayerTeamList;

class Player
{
public:
	void removeTeamFromList(TeamPrototype *team);

private:
	unsigned char m_pad[0x32C];
	PlayerTeamList m_playerTeamPrototypes;	// +0x32C
};

void Player::removeTeamFromList(TeamPrototype *team)
{
	PlayerTeamList::iterator it;
	for (it = m_playerTeamPrototypes.begin(); it != m_playerTeamPrototypes.end(); ++it)
		;
	for (it = m_playerTeamPrototypes.begin(); it != m_playerTeamPrototypes.end(); ++it)
		if (team == *it) { m_playerTeamPrototypes.erase(it); break; }
	for (it = m_playerTeamPrototypes.begin(); it != m_playerTeamPrototypes.end(); ++it)
		;
}
