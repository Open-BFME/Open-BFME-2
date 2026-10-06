// cl: /DNDEBUG /MD /EHsc
//
// ?rva004783F4@Rva004783F4@@QAEPAVTeam@@XZ, retail 0x004783F4, 24 bytes.
// Honest-address method: if the +0xFC instance pointer is null return null,
// else return TheTeamFactory->findInstance(it) through the pinned
// ?findInstance@Rva0039F761Owner row. Offset +0xFC is the first member after
// the 0xFC OpenContain base (GarrisonContainDtor precedent); owner is not
// proven by a vtable here so the address name is used. Evidence: caller
// 0x00480BFD, TheTeamFactory global 0x00A028BC, pinned findInstance
// 0x0039F761.

class Team;
class TeamFactory;

class Rva0039F761Owner
{
public:
	Team *findInstance(void *instance);
};

extern TeamFactory *TheTeamFactory;

class Rva004783F4
{
public:
	Team *rva004783F4();

private:
	unsigned char m_pad[0xFC];
	void *m_instance; // +0xFC
};

// ?rva004783F4@Rva004783F4@@QAEPAVTeam@@XZ @0x004783F4
Team *Rva004783F4::rva004783F4()
{
	if (m_instance == 0)
		return 0;
	return ((Rva0039F761Owner *)TheTeamFactory)->findInstance(m_instance);
}
