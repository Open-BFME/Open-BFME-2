// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
//
// BFME 2's giant-bird guard machine. BFME 1's GiantBirdGuardMachineCtor.cpp
// (Open-BFME-1) is the donor for the machine constructor's state table; the
// BFME 2 classes and sizes below are read from retail:
//
//  - GiantBirdGuardReturnState::GiantBirdGuardReturnState, retail 0x00367EE1
//    (50 bytes): the GiantBirdNormalFlightState constructor 0x00367539 (vtable
//    0x00C17300, whose slots 4-6 are the rowed NormalFlight bodies)
//    with both flags set, vtable 0x00C17708 (slot 3 is the rowed
//    GiantBirdGuardReturnState::xfer 0x00368015), an int at +0x24 and three
//    floats at +0x28 cleared;
//  - GiantBirdGuardMachine::GiantBirdGuardMachine, retail 0x00368A13
//    (290 bytes): the AIGuardMachine constructor 0x00543163 with the name
//    hash 0x3EDCCF0B, vtable 0x00C17768 (slot 2 returns
//    "GiantBirdGuardMachine", slot 3 is its rowed xfer 0x00367FDD), then the
//    donor's four defineState calls and setDefaultState(0xB79B). BFME 2
//    allocates the states with operator new: 0x34 bytes for the return state,
//    0x30 for the idle state (rowed constructor 0x00367E59), 0x44 for the
//    rowed inner (0x003689C4) and outer (0x00367E92) states;
//  - slot 10 of vtable 0x00C17600 (the machine class whose destructor is
//    rowed at 0x00367E26), retail 0x003697BB (57 bytes): allocates 0x74
//    bytes and constructs a GiantBirdGuardMachine for the machine's owner
//    (+0x14). Its name is not recovered;
//  - GiantBirdGuardReturnState::onEnter, retail 0x0036A7DB (175 bytes): slot 4
//    of vtable 0x00C17708. It follows the BFME 1 donor's AIGuardReturnState
//    goal choice (target, team, area) with BFME 2's precomputed area centre
//    (+0x54, valid flag +0x60) and the GiantBirdAIUpdate.cpp file/line random
//    call, then chains to GiantBirdNormalFlightState::onEnter (0x00369064).

typedef bool Bool;
typedef float Real;
typedef unsigned int UnsignedInt;
typedef unsigned int StateID;
typedef UnsignedInt TeamID;

#include "../../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../Common/GameLogicObjectLookupView.h"

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

class StateMachine;

struct State;
struct StateConditionInfo;

class Object
{
public:
	const Coord3D *getPosition() const { return &m_position; }
private:
	unsigned char m_pad00[0x38];
	Coord3D m_position; // +0x38
};

class Team
{
public:
	void rva0039E5B9(Coord3D *pos);
};

class TeamFactory
{
public:
	Team *findTeamByID(TeamID id);
};

class PolygonTrigger
{
public:
	void getCenterPoint(Coord3D *pOutCenter) const;
};

struct TAiData
{
	unsigned char m_pad00[0x44];
	UnsignedInt m_guardEnemyReturnScanRate; // +0x44
};

class AI
{
public:
	const TAiData *getAiData() const { return m_aiData; }
private:
	unsigned char m_pad00[0x18];
	TAiData *m_aiData; // +0x18
};

extern AI *TheAI;
extern GameLogic *TheGameLogic;
extern TeamFactory *TheTeamFactory;

int GetGameLogicRandomValue(int low, int high, char *file, int line);
#define GIANTBIRDAIUPDATE_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\AIUpdate\\GiantBirdAIUpdate.cpp"

class StateMachine
{
public:
	virtual ~StateMachine();
	void defineState(StateID id, State *state, StateID successID, StateID failureID, const StateConditionInfo *conditions);
	void rva004D7627(int id);
	void setGoalPosition(const Coord3D *pos);
	Object *getOwner() const { return m_owner; }
private:
	unsigned char m_pad04[0x14 - 0x04];
	Object *m_owner; // +0x14
};

class AIGuardMachine : public StateMachine
{
public:
	AIGuardMachine(Object *owner, unsigned int nameHash);
	virtual ~AIGuardMachine();
	Object *findTargetToGuardByID() { return TheGameLogic->findObjectByID(m_targetToGuard); }
	Team *findTeamToGuardByID() { return TheTeamFactory->findTeamByID(m_teamToGuard); }
	const PolygonTrigger *getAreaToGuard(void) const { return m_areaToGuard; }
	const Coord3D *getPositionToGuard(void) const { return &m_positionToGuard; }
	Bool hasBfmeAreaCenter() const { return m_bfmeAreaCenterValid; }
	const Coord3D *getBfmeAreaCenter() const { return &m_bfmeAreaCenter; }
private:
	unsigned char m_pad18[0x3C - 0x18];
	ObjectID m_targetToGuard; // +0x3C
	TeamID m_teamToGuard; // +0x40
	const PolygonTrigger *m_areaToGuard; // +0x44
	Coord3D m_positionToGuard; // +0x48
	Coord3D m_bfmeAreaCenter; // +0x54
	Bool m_bfmeAreaCenterValid; // +0x60
	unsigned char m_pad61[0x74 - 0x61];
};

class GiantBirdGuardMachine : public AIGuardMachine
{
public:
	GiantBirdGuardMachine(Object *owner);
	virtual ~GiantBirdGuardMachine();
};

struct State
{
	State(StateMachine *machine, unsigned int nameHash);
	virtual ~State();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual StateReturnType onEnter();
	StateMachine *getMachine() const { return m_machine; }
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
	unsigned char m_pad1C[0x20 - 0x1C];
};

class GiantBirdNormalFlightState : public State
{
public:
	GiantBirdNormalFlightState(StateMachine *machine, Bool flag20, Bool flag21);
	virtual StateReturnType onEnter();
	Bool m_bfme20; // +0x20
	Bool m_bfme21; // +0x21
};

// Retail clears the goal after the +0x24 store, the order an inline call
// gives (Zero Hour's Coord3D::zero shape), not member stores.
inline void zeroCoord3D(Coord3D *pos)
{
	pos->x = 0.0f;
	pos->y = 0.0f;
	pos->z = 0.0f;
}

class GiantBirdGuardReturnState : public GiantBirdNormalFlightState
{
public:
	GiantBirdGuardReturnState(StateMachine *machine);
	virtual StateReturnType onEnter();
private:
	AIGuardMachine *getGuardMachine() { return (AIGuardMachine *)getMachine(); }
	UnsignedInt m_nextReturnScanTime; // +0x24
	Coord3D m_goalPosition; // +0x28
};

class Rva00367E59 : public State
{
public:
	Rva00367E59(StateMachine *machine);
	unsigned char m_pad20[0x30 - 0x20];
};

class GiantBirdGuardInnerState : public State
{
public:
	GiantBirdGuardInnerState(StateMachine *machine);
	unsigned char m_pad20[0x44 - 0x20];
};

class GiantBirdGuardOuterState : public State
{
public:
	GiantBirdGuardOuterState(StateMachine *machine);
	unsigned char m_pad20[0x44 - 0x20];
};

class Rva00367E26 : public StateMachine
{
public:
	AIGuardMachine *rva003697BB();
};

GiantBirdGuardReturnState::GiantBirdGuardReturnState(StateMachine *machine)
	: GiantBirdNormalFlightState(machine, true, true), m_nextReturnScanTime(0)
{
	zeroCoord3D(&m_goalPosition);
}

GiantBirdGuardMachine::GiantBirdGuardMachine(Object *owner)
	: AIGuardMachine(owner, 0x3edccf0bu)
{
	defineState(0xB79B, new GiantBirdGuardReturnState(this), 0xB799, 0xB798, 0);
	defineState(0xB799, new Rva00367E59(this), 0xB798, 0xB79B, 0);
	defineState(0xB798, new GiantBirdGuardInnerState(this), 0xB79A, 0xB79A, 0);
	defineState(0xB79A, new GiantBirdGuardOuterState(this), 0xB79B, 0xB79B, 0);
	rva004D7627(0xB79B);
}

AIGuardMachine *Rva00367E26::rva003697BB()
{
	return new GiantBirdGuardMachine(getOwner());
}

StateReturnType GiantBirdGuardReturnState::onEnter()
{
	UnsignedInt now = TheGameLogic->getFrame();
	m_nextReturnScanTime = now + GetGameLogicRandomValue(0, TheAI->getAiData()->m_guardEnemyReturnScanRate, GIANTBIRDAIUPDATE_FILE, 2824);

	AIGuardMachine *machine = getGuardMachine();
	m_goalPosition = *machine->getPositionToGuard();
	Object *targetToGuard = machine->findTargetToGuardByID();
	if (targetToGuard)
	{
		m_goalPosition = *targetToGuard->getPosition();
	}
	else
	{
		Team *teamToGuard = machine->findTeamToGuardByID();
		if (teamToGuard)
		{
			teamToGuard->rva0039E5B9(&m_goalPosition);
		}
		else if (getGuardMachine()->getAreaToGuard())
		{
			if (getGuardMachine()->hasBfmeAreaCenter())
				m_goalPosition = *getGuardMachine()->getBfmeAreaCenter();
			else
				getGuardMachine()->getAreaToGuard()->getCenterPoint(&m_goalPosition);
		}
	}
	getMachine()->setGoalPosition(&m_goalPosition);
	return GiantBirdNormalFlightState::onEnter();
}
