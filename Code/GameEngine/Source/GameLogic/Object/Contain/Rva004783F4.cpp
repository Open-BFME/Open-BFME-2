// cl: /DNDEBUG /MD /EHsc
//
// ?rva004783F4@Rva004783F4@@QAEPAVTeam@@XZ, retail 0x004783F4, 24 bytes.
// Honest-address method: if the +0xFC team id is zero return null,
// else return TheTeamFactory->findTeamByID(id) through the rowed
// ?findTeamByID@TeamFactory row. Offset +0xFC is the first member after
// the 0xFC OpenContain base (GarrisonContainDtor precedent); owner is not
// proven by a vtable here so the address name is used. Evidence: caller
// 0x00480BFD, TheTeamFactory global 0x00A028BC, rowed findTeamByID
// 0x0039F761.

class Team;
class TeamFactory;

class TeamFactory
{
public:
	Team *findTeamByID(unsigned int id);
};

extern TeamFactory *TheTeamFactory;

class Rva004783F4
{
public:
	Team *rva004783F4();

private:
	unsigned char m_pad[0xFC];
	unsigned int m_instance; // +0xFC team id
};

// ?rva004783F4@Rva004783F4@@QAEPAVTeam@@XZ @0x004783F4
Team *Rva004783F4::rva004783F4()
{
	if (m_instance == 0)
		return 0;
	return TheTeamFactory->findTeamByID(m_instance);
}
