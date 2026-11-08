// ?rva003683EA@Rva003683EA@@QAEXPBUCoord3D@@H@Z
// partial score=0.99 date=2026-09-30
// ?rva003683EA@Rva003683EA@@QAEXPBUCoord3D@@H@Z
// partial score=0.99 date=2026-09-30
// cl: /DNDEBUG /MD
// ?rva003683EA@Rva003683EA@@QAEXPBUCoord3D@@H@Z retail 0x003683EA 73B.
// Chain lane: calls 0x00265667 which we landed; guard byte plus machine slots plus base plus scale.
// Evidence: caller at 0x0036BD51; callees rowed 0x00265667 plus gen-alias 0x003E3BFB.

#include "../../../../../../Libraries/Include/Lib/Coord3D.h"

#include "../../../../../Include/Common/StateMachineClass.h"



class Waypoint;

#include "../../../../../Include/GameLogic/AIStateMachineClass.h"
#include "../../../../../Include/GameLogic/Module/AIUpdate.h"

class Rva003683EA : public AIUpdateInterface
{
public:
	void rva003683EA(const Coord3D *pos, int flag);
private:
	char m_pad3E4[0x528 - sizeof(AIUpdateInterface)];
	int m_done; // +0x528
};

void Rva003683EA::rva003683EA(const Coord3D *pos, int flag)
{
	if (m_field3BD != 0)
		return;
	m_stateMachine->clear();
	rva00265667(pos, flag);
	((AIStateMachine *)this)->setGoalWaypoint((const Waypoint *)flag);
	m_stateMachine->setState(0x3FB);
	m_done = 1;
}
