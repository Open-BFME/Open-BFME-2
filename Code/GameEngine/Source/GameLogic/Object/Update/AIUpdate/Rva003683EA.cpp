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

class AIUpdateInterface
{
public:
	void rva00265667(const Coord3D *pos, int flag);
};

class Waypoint;

#include "../../../../../Include/GameLogic/AIStateMachineClass.h"

class Rva003683EA : public AIUpdateInterface
{
public:
	void rva003683EA(const Coord3D *pos, int flag);
private:
	char m_pad10[0x30 - sizeof(AIUpdateInterface)];
	StateMachine *m_machine; // +0x30
	char m_pad34[0x3BD - 0x34];
	unsigned char m_guard; // +0x3BD
	char m_pad3BE[0x528 - 0x3BE];
	int m_done; // +0x528
};

void Rva003683EA::rva003683EA(const Coord3D *pos, int flag)
{
	if (m_guard != 0)
		return;
	m_machine->clear();
	rva00265667(pos, flag);
	((AIStateMachine *)this)->setGoalWaypoint((const Waypoint *)flag);
	m_machine->setState(0x3FB);
	m_done = 1;
}
