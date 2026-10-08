// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?createInstance@Rva003A3CBBOwner@@QAEPAVTeam@@ABVAsciiString@@0@Z @0x003A3CBB 30B
// TeamFactory::createInstance: forwards both names to pin-only 0x003A3B7E then activates the Team.
// Evidence: pin ECX is TeamFactory, caller 0x0035871D getTeamNamed passes (normalized,name), callee same args returns Team, status bytes +0x5D/+0x5E match Team::status setActive in ScriptEngineGetTeamNamed.
#include "ascii_string.h"

class Team
{
public:
	unsigned char m_pad00[0x5D];
	unsigned char m_active5D;
	unsigned char m_created5E;
};

class TeamPrototype;

// The pinned callee is the rowed TeamFactory::createInactiveTeam.
class TeamFactory
{
public:
	Team *createInactiveTeam(const AsciiString &name, const AsciiString &other);
};

class Rva003A3CBBOwner
{
public:
	Team *createInstance(const AsciiString &a, const AsciiString &b);
};

Team *Rva003A3CBBOwner::createInstance(const AsciiString &a, const AsciiString &b)
{
	Team *team = ((TeamFactory *)this)->createInactiveTeam(a, b);
	if (!team->m_active5D) {
		team->m_created5E = 1;
		team->m_active5D = 1;
	}
	return team;
}
