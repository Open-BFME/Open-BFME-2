// cl: /O1 /MD
// AITactic::initializeTeamTemplate @ 0x004ECE61, 50 bytes: slot 3 of the AITactic
// vtable, which WorldBuilder names initializeTeamTemplate in every tactic that
// overrides it (the AIRingHero/AIRoamingDefense/AITacticDefensive overrides
// call this base); its literal is AITactic.cpp line 386.
// Reads [this+0x20]->+4, random 3..5 into [arg1+0x2d4], always returns true.
// Evidence: 4 callers forwarding (this, arg1, arg2) e.g. 0x005AC924; rowed callee
// ?GetGameLogicRandomValue@@YAHHHPADH@Z with file/line 0x182; vtable slot 3 refs.
int __cdecl GetGameLogicRandomValue(int lo, int hi, char *file, int line);

class Team;
class TeamPrototype;

class TeamFactory
{
public:
	Team *findTeamByID(unsigned int id);			// 0x0039F761
};

extern TeamFactory *TheTeamFactory;

// Team::disband per WorldBuilder (rowed at 0x0039E9E0).
class Team
{
public:
	void disband();					// 0x0039E9E0
};

struct Rva002A8AB1Record
{
	void rva004EC07D(TeamPrototype *proto);			// 0x004EC07D
};

class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *owner);		// 0x002A8AB1
};

extern Rva002A8F24 *g_00DFEEF8;

// The tactic's target (WorldBuilder AITarget); rowed under a placeholder owner.
class Rva002C589B
{
public:
	void rva002C5843(bool flag);				// 0x002C5843
	void markApproachHazard(void *area);			// 0x002C590F
	void removeTactic() { --m_numTactics; }

	unsigned char m_pad00[4];
	int m_04;						// +0x04
	unsigned char m_pad08[0x1c - 8];
	int m_numTactics;					// +0x1C
};

struct AITacticTeamRecord
{
	unsigned int m_teamID;					// +0x00
	unsigned char m_pad04[0x14 - 4];
};

class AITactic
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual bool initializeTeamTemplate(void *p, int dummy);
	virtual unsigned int getNumberOfTeamsNeeded();

	void end(bool a, bool b);
	void sendTeamToAssistAnotherHorde(Team *team);		// 0x004ED52E

private:
	TeamPrototype **m_protoBegin;				// +0x04
	TeamPrototype **m_protoEnd;				// +0x08
	TeamPrototype **m_protoCap;				// +0x0C
	bool m_10;						// +0x10
	AITacticTeamRecord *m_teamsBegin;			// +0x14
	AITacticTeamRecord *m_teamsEnd;				// +0x18
	AITacticTeamRecord *m_teamsCap;				// +0x1C
	Rva002C589B *m_20;					// +0x20
	void *m_24;						// +0x24
	bool m_ended;						// +0x28
	unsigned char m_pad29[0x38 - 0x29];
	unsigned char m_38[0x50 - 0x38];			// +0x38
	bool m_50;						// +0x50
};

bool AITactic::initializeTeamTemplate(void *p, int /*dummy*/)
{
	void *mid = m_20;
	if (mid == 0)
		return true;
	if (*(int *)((char *)mid + 4) != 0)
		return true;
	*(int *)((char *)p + 0x2D4) = GetGameLogicRandomValue(3, 5, (char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AITacticalAI\\AITacticsGenerator\\AITactic.cpp", 0x182);
	return true;
}

// ?end@AITactic@@QAEX_N0@Z retail 0x004ED748, 213 bytes. WorldBuilder names it
// AITactic::end (AITactic.cpp); retail drops its asserts and the "END: %s ON:
// %s" log. Once only (+0x28): unless told otherwise calls virtual slot 2,
// releases each team prototype from the owner record 0x002A8AB1 gives for
// +0x24, disbands every team (first offering it to another horde unless
// +0x50 is set), then detaches from the target, marking an approach hazard
// when the tactic still needs teams. Both arguments are tested as bytes.
void AITactic::end(bool a, bool b)
{
	if (m_ended)
		return;
	m_ended = true;
	if (!b)
		slot02();

	Rva002A8AB1Record *record = g_00DFEEF8->rva002A8AB1(m_24);
	if (record)
	{
		TeamPrototype **protoEnd = m_protoEnd;
		for (TeamPrototype **it = m_protoBegin; it != protoEnd; ++it)
			record->rva004EC07D(*it);
	}

	AITacticTeamRecord *teamsEnd = m_teamsEnd;
	for (AITacticTeamRecord *rec = m_teamsBegin; rec != teamsEnd; ++rec)
	{
		Team *team = TheTeamFactory->findTeamByID(rec->m_teamID);
		if (team)
		{
			if (!m_50)
				sendTeamToAssistAnotherHorde(team);
			team->disband();
		}
	}

	if (m_20)
	{
		if (a)
			m_20->rva002C5843(true);
		else if (!b && getNumberOfTeamsNeeded() > 0)
			m_20->markApproachHazard(m_38);
		m_20->removeTactic();
		m_20 = 0;
	}
	m_10 = false;
}
