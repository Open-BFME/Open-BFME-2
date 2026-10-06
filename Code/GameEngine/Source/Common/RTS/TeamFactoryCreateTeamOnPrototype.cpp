// cl: /O1 /DNDEBUG /MD /EHsc
// TeamFactory::createTeamOnPrototype, retail 0x003A3DBE (121 bytes):
// ?createTeamOnPrototype@TeamFactory@@QAEPAVTeam@@PAVTeamPrototype@@_N@Z
// Identity (target): WorldBuilder's debug Team.cpp:576
// TeamFactory::createTeamOnPrototype; retail follows Zero Hour's body: no
// prototype gives null, a singleton prototype's existing team is reused,
// otherwise a new Team (0x13C bytes, Team::Team 0x003A39A7) takes
// ++m_uniqueTeamID (+0xC0).
// BFME 2 delta (target): a second argument activates the new team the way
// Zero Hour's Team::setActive does (+0x5D active, +0x5E created) when it
// is not active yet; TeamPrototype::xfer passes true when it recreates a
// missing team on load.
class TeamPrototype;

class Team
{
public:
	Team(TeamPrototype *proto, int id);
	void setActive()
	{
		if (!m_active)
		{
			m_created = true;
			m_active = true;
		}
	}

private:
	unsigned char m_pad00[0x5D];
	bool m_active; // +0x5D
	bool m_created; // +0x5E
	unsigned char m_pad5F[0x13C - 0x5F];
};

class TeamPrototype
{
public:
	bool getIsSingleton() const { return (m_flags & 1) != 0; }
	Team *getFirstItemIn_TeamInstanceList() const { return m_dlinkhead_TeamInstanceList; }

private:
	unsigned char m_pad00[0x18];
	int m_flags; // +0x18
	unsigned char m_pad1C[0x334 - 0x1C];
	Team *m_dlinkhead_TeamInstanceList; // +0x334
};

class TeamFactory
{
public:
	Team *createTeamOnPrototype(TeamPrototype *prototype, bool activate);

private:
	unsigned char m_pad00[0xC0];
	int m_uniqueTeamID; // +0xC0
};

Team *TeamFactory::createTeamOnPrototype(TeamPrototype *prototype, bool activate)
{
	if (prototype == 0)
		return 0;
	Team *t = 0;
	if (prototype->getIsSingleton())
	{
		t = prototype->getFirstItemIn_TeamInstanceList();
		if (t)
			return t;
	}
	t = new Team(prototype, ++m_uniqueTeamID);
	if (activate)
		t->setActive();
	return t;
}
