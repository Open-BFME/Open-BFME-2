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

#include "../../../Common/GameLogicObjectLookupView.h"

#include "../object.h"

extern GameLogic *TheGameLogic;

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

enum TurretTargetType
{
	TARGET_NONE,
	TARGET_OBJECT,
	TARGET_POSITION
};

struct TurretStateMachine
{
	char m_pad[0x20 - 4];
	ObjectID m_goalObjectID;
	Coord3D m_goalPosition;
	char m_pad30[0x34 - 0x30];
	ObjectID m_34;

	Object *getGoalObject();
	Object *rva004D7735();
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

// ?getGoalObject@TurretStateMachine@@QAEPAVObject@@XZ
// retail 0x004D7726, 15 bytes. TheGameLogic ID lookup of the goal ID at +0x20.
Object *TurretStateMachine::getGoalObject()
{
	return TheGameLogic->findObjectByID(m_goalObjectID);
}

// ?rva004D7735@TurretStateMachine@@QAEPAVObject@@XZ
// retail 0x004D7735, 15 bytes. TheGameLogic ID lookup of the ID at +0x34.
Object *TurretStateMachine::rva004D7735()
{
	return TheGameLogic->findObjectByID(m_34);
}

// Other units call this body (pinned at its address) under the spelling(s)
// below, with the same calling convention and stack arguments; bind them.
#pragma comment(linker, "/alternatename:?getGoalObject@StateMachine@@QAEPAVObject@@XZ=?getGoalObject@TurretStateMachine@@QAEPAVObject@@XZ")

// ?rva0026232D@Rva0026232DOwner@@QAEPAVObject@@XZ @0x0026232D 8B: forwards to TurretStateMachine::getGoalObject through the pointer held at +0x30
// (load ecx; tail jump). Owner and name are address-derived; no referencing
// site was found in this pass.
class Rva0026232DOwner
{
public:
	Object *rva0026232D();
private:
	char m_pad00[0x30];
	TurretStateMachine *m_machine30;
};

Object *Rva0026232DOwner::rva0026232D()
{
	return m_machine30->getGoalObject();
}
