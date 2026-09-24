// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ?internalSetGoalPosition@StateMachine@@QAEXPBVCoord3D@@M@Z,
// retail 0x004D73C4, 32 bytes, plus
// ?setGoalObject@StateMachine@@QAEXPAVObject@@@Z,
// retail 0x004D7435, 39 bytes, plus
// ?setGoalPosition@StateMachine@@QAEXPBVCoord3D@@M@Z,
// retail 0x004D745C, 26 bytes, plus
// ?setGoalPosition@TurretStateMachine@@QAEXPBUCoord3D@@@Z,
// retail 0x00262224, 22 bytes. Dedicated TU for the StateMachine goal
// file-unit: the lock-gated setter, the storing worker, the object setter,
// and the TurretAI wrapper that supplies the default range.
// BFME1 reference (reference/open-bfme-1/Code/GameEngine/Source/Common/
// StateMachine.cpp, StateMachine::setGoalPosition plus
// internalSetGoalPosition plus setGoalObject): the lock flag gates the
// setter, the worker copies the position when non-null, and the object
// setter records the id plus forwards the object's position. BFME2 deltas:
// the worker takes a second float argument kept in the new member at +0x30
// (callers pass FLT_MAX for the unlimited default, the object setter
// forwards the stored value), the lock lives at +0x38, and the id/position
// reads are direct (m_id at +0x74, m_position at +0x38) instead of virtual.

#include <cfloat>

typedef int Int;

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object
{
public:
	unsigned char m_pad00[0x38];
	Coord3D m_position; // +0x38
	unsigned char m_pad44[0x74 - 0x44];
	Int m_id; // +0x74
};

class StateMachine
{
public:
	unsigned char m_pad00[0x04];
	void *m_currentState; // +0x04
	unsigned char m_pad08[0x20 - 0x08];
	Int m_goalObjectID; // +0x20
	Coord3D m_goalPosition; // +0x24
	float m_goalRange; // +0x30, BFME2-new range carried with the goal
	unsigned char m_pad34[0x38 - 0x34];
	bool m_locked; // +0x38

	void setGoalPosition(const Coord3D *pos, float goalRange);
	void internalSetGoalPosition(const Coord3D *pos, float goalRange);
	void setGoalObject(Object *obj);
	void halt();
};

class TurretStateMachine : public StateMachine
{
public:
	void setGoalPosition(const Coord3D *pos);
};

// ?internalSetGoalPosition@StateMachine@@QAEXPBVCoord3D@@M@Z
void StateMachine::internalSetGoalPosition(const Coord3D *pos, float goalRange)
{
	if (pos) {
		m_goalPosition = *pos;
		// Don't clear the goal object, or everything breaks.  Like construction of buildings.
	}
	m_goalRange = goalRange;
}

// ?setGoalPosition@StateMachine@@QAEXPBVCoord3D@@M@Z
void StateMachine::setGoalPosition(const Coord3D *pos, float goalRange)
{
	if (m_locked)
		return;
	internalSetGoalPosition(pos, goalRange);
}

// ?setGoalObject@StateMachine@@QAEXPAVObject@@@Z
void StateMachine::setGoalObject(Object *obj)
{
	if (obj) {
		m_goalObjectID = obj->m_id;
		internalSetGoalPosition(&obj->m_position, m_goalRange);
	}
	else {
		m_goalObjectID = 0;
	}
}

// ?setGoalPosition@TurretStateMachine@@QAEXPBUCoord3D@@@Z
void TurretStateMachine::setGoalPosition(const Coord3D *pos)
{
	StateMachine::setGoalPosition(pos, FLT_MAX);
}

// ?halt@StateMachine@@QAEXXZ
void StateMachine::halt()
{
	m_locked = true;
	m_currentState = 0; // don't exit current state, just clear it.
}
