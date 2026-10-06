// cl: /MD /DNDEBUG
//
// AIStateMachine goal setters, ported from Zero Hour's GameEngine/Source/
// GameLogic/AI/AIStates.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference):
//  - setGoalTeam, retail 0x0035042D (53 bytes), and setGoalAIGroup, retail
//    0x00350462 (53 bytes): create the goal squad on first use (+0x4C; a
//    plain 0x1C-byte operator new and the Squad constructor 0x00268CAC), then
//    Squad::squadFromTeam (rowed 0x004D6D95) / squadFromAIGroup (0x004D6C48)
//    with clearSquadFirst true. setGoalSquad, retail 0x00352B9D (51 bytes),
//    copies the given squad into it (Squad::operator=, the two-vector copy
//    0x00351761). The constructor installs vftable 0x00BF9D60,
//    whose slot 3 is the rowed Squad::xfer 0x004D6EC4; retail has no unwind
//    frame around it, hence throw().
typedef bool Bool;
#define NULL 0

class Team;
class AIGroup;

class Squad
{
public:
	Squad() throw();
	void squadFromTeam(const Team *fromTeam, Bool clearSquadFirst);
	void squadFromAIGroup(const AIGroup *fromAIGroup, Bool clearSquadFirst);
	Squad &operator=(const Squad &that);
private:
	unsigned char m_data[0x1C];
};

class AIStateMachine
{
public:
	void setGoalTeam( const Team *team );
	void setGoalAIGroup( const AIGroup *group );
	void setGoalSquad( const Squad *squad );
private:
	unsigned char m_pad00[0x4C];
	Squad *m_goalSquad; // +0x4C
};

//----------------------------------------------------------------------------------------------------------
void AIStateMachine::setGoalTeam( const Team *team )
{
	if (m_goalSquad == NULL) {
		m_goalSquad = new Squad;
	}

	m_goalSquad->squadFromTeam(team, true);
}

//----------------------------------------------------------------------------------------------------------
void AIStateMachine::setGoalAIGroup( const AIGroup *group )
{
	if (m_goalSquad == NULL) {
		m_goalSquad = new Squad;
	}

	m_goalSquad->squadFromAIGroup(group, true);
}

//----------------------------------------------------------------------------------------------------------
void AIStateMachine::setGoalSquad( const Squad *squad )
{
	if (m_goalSquad == NULL) {
		m_goalSquad = new Squad;
	}

	(*m_goalSquad) = (*squad);
}
