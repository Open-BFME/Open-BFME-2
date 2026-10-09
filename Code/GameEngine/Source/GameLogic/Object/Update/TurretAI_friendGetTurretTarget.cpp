// cl: /DNDEBUG /MD
//
// TurretAI::friend_getTurretTarget (retail 0x004D81F1, 110 bytes) moved to
// Code/GameEngine/Source/GameLogic/AI/TurretAIIdleStates.cpp: its caller
// TurretAIAimTurretState::update 0x004D8EAC only reproduces with the callee
// defined earlier in the same unit. Its notes below are kept for history.
// Verbatim BFME2 logic (Zero Hour TurretAI::friend_getTurretTarget without the
// clearDeadTargets parameter: dead targets always clear). BFME2 layout: state
// machine at +0x14 with goal ID at +0x20 and goal position at +0x24; target
// type at +0x2c; idle-mood flag at +0x3F. The Object* home reuses no extra
// frame: obj writes through the reference parameter and pos fills the 12-byte
// reference. getGoalObject resolves through TheGameLogic by pin and
// setGoalObject(NULL) goes through vtable slot 0x38.

typedef bool Bool;

enum ObjectID
{
	INVALID_ID = 0
};

class Object
{
public:
	char m_pad[0x438];
	unsigned char m_deadFlags;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum TurretTargetType
{
	TARGET_NONE,
	TARGET_OBJECT,
	TARGET_POSITION
};

struct TurretData
{
	char m_pad[0x4C];
	unsigned m_slotMask;
};

struct TurretStateMachine
{
	char m_pad[0x20 - 4];
	ObjectID m_goalObjectID;
	Coord3D m_goalPosition;

	Object *getGoalObject();
	virtual void _rsvd00();
	virtual void _rsvd01();
	virtual void _rsvd02();
	virtual void _rsvd03();
	virtual void _rsvd04();
	virtual void _rsvd05();
	virtual void _rsvd06();
	virtual void _rsvd07();
	virtual void _rsvd08();
	virtual void _rsvd09();
	virtual void _rsvd10();
	virtual void _rsvd11();
	virtual void _rsvd12();
	virtual void _rsvd13();
	virtual void setGoalObject(Object *o);
};

class TurretAI
{
	char m_pad0[8];
	TurretData *m_data;
	char m_pad1[0x14 - 0x0C];
	TurretStateMachine *m_machine;
	char m_pad2[0x2C - 0x18];
	mutable TurretTargetType m_target;
	char m_pad3[0x3F - 0x30];
	mutable Bool m_targetWasSetByIdleMood;

public:
	TurretTargetType friend_getTurretTarget(Object *&obj, Coord3D &pos) const;
};

// ?getGoalObject@TurretStateMachine@@QAEPAVObject@@XZ
// retail 0x004D7726, 15 bytes. TheGameLogic ID lookup of the goal ID at +0x20.
Object *TurretStateMachine::getGoalObject()
{
	return TheGameLogic->findObjectByID(m_goalObjectID);
}

// Other units call this body (pinned at its address) under the spelling(s)
// below, with the same calling convention and stack arguments; bind them.
#pragma comment(linker, "/alternatename:?getGoalObject@StateMachine@@QAEPAVObject@@XZ=?getGoalObject@TurretStateMachine@@QAEPAVObject@@XZ")
