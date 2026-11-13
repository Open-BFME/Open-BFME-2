// cl: /MD /DNDEBUG
// platformsdk
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
#include <windows.h>
typedef bool Bool;

class Team;
class AIGroup;

class Squad
{
public:
	Squad() throw();
private:
	unsigned char m_data[0x1C];
};

// LINK: the three Squad operations are rowed under their retail names
// (0x004D6D95, 0x0018B8B0, 0x00351761); the views keep the call shapes.
class Rva004D6C9C
{
public:
	void rva004D6D95(Team *fromTeam, Bool clearSquadFirst);
};
class Rva0018B8B0Arg;
#include "../../../Include/GameLogic/Rva0018B8B0Holder.h"
struct BfmeThingCDF
{
	BfmeThingCDF *bfmeGoCDF(BfmeThingCDF *that);
};

#include "../../../Include/GameLogic/AIStateMachineClass.h"

//----------------------------------------------------------------------------------------------------------
void AIStateMachine::setGoalTeam( const Team *team )
{
	if (m_goalSquad == NULL) {
		m_goalSquad = new Squad;
	}

	((Rva004D6C9C *)m_goalSquad)->rva004D6D95((Team *)team, true);
}

//----------------------------------------------------------------------------------------------------------
void AIStateMachine::setGoalAIGroup( const AIGroup *group )
{
	if (m_goalSquad == NULL) {
		m_goalSquad = new Squad;
	}

	((Rva0018B8B0Holder *)m_goalSquad)->apply((Rva0018B8B0Arg *)group, true);
}

//----------------------------------------------------------------------------------------------------------
void AIStateMachine::setGoalSquad( const Squad *squad )
{
	if (m_goalSquad == NULL) {
		m_goalSquad = new Squad;
	}

	((BfmeThingCDF *)m_goalSquad)->bfmeGoCDF((BfmeThingCDF *)squad);
}
