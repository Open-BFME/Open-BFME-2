// ?addToGoalPath@AIStateMachine@@QAEXPBUCoord3D@@@Z
// partial score=0.9 date=2026-10-04
// cl: /O1 /G7 /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// AIStateMachine goal setters, ported from Zero Hour's GameEngine/Source/
// GameLogic/AI/AIStates.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference):
//  - setGoalTeam, retail 0x0035042D (53 bytes), and setGoalAIGroup, retail
//    0x00350462 (53 bytes): create the goal squad on first use (+0x4C; a
//    plain 0x1C-byte operator new and the Squad constructor 0x00268CAC), then
//    Squad::squadFromTeam (rowed 0x004D6D95) / squadFromAIGroup (0x004D6C48)
//    with clearSquadFirst true.
//  - addToGoalPath, retail 0x0035385E (64 bytes): the goal path is the
//    vector<Coord3D> at +0x3C; appends the point unless it equals the last
//    one (Coord3D::equals 0x00003702; out-of-line push_back 0x002CE7DC).
#include <vector>

typedef float Real;
typedef bool Bool;
#define NULL 0

struct Coord3DBase
{
	Real x, y, z;
};
struct Coord3D : public Coord3DBase
{
	Bool equals(const Coord3DBase &r) const;
};

class Team;
class AIGroup;

class Squad
{
public:
	Squad() throw();
	void squadFromTeam(const Team *fromTeam, Bool clearSquadFirst);
	void squadFromAIGroup(const AIGroup *fromAIGroup, Bool clearSquadFirst);
private:
	unsigned char m_data[0x1C];
};

class AIStateMachine
{
public:
	void setGoalTeam( const Team *team );
	void setGoalAIGroup( const AIGroup *group );
	void addToGoalPath( const Coord3D *pathPoint );
private:
	unsigned char m_pad00[0x3C];
	_STL::vector<Coord3D> m_goalPath; // +0x3C
	unsigned char m_pad48[0x4C - 0x48];
	Squad *m_goalSquad; // +0x4C
};

//----------------------------------------------------------------------------------------------------------
void AIStateMachine::addToGoalPath( const Coord3D *pathPoint)
{
	if (m_goalPath.size()==0) {
		m_goalPath.push_back(*pathPoint);
	}	else {
		Coord3D *finalPoint = &m_goalPath[ m_goalPath.size() - 1 ];
		if( !finalPoint->equals( *pathPoint ) )
		{
			m_goalPath.push_back(*pathPoint);
		}
	}
}

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
