// cl: /DNDEBUG /MD /EHsc
//
// AIGuardRetaliateState::onEnter, retail 0x003463DA (173 bytes): slot 4 of
// vtable 0x00C117F0, whose slot-2 name getter returns AIGuardRetaliateState.
// Ported from Zero Hour's GameEngine/Source/GameLogic/AI/AIStates.cpp
// (GeneralsMD tree vendored under reference/open-bfme-1/inputs/reference): a
// new AIGuardRetaliateMachine (rowed ctor 0x0054551F) over the owner, given
// the AI's goal position, the goal object's id as nemesis, then
// initDefaultState (machine vslot 7).
// BFME 2 difference (target evidence): when the goal object has status 0x26
// and the rowed opaque Object::rva002931F5(false) yields an object, that
// object becomes the nemesis instead.
// Layout (target evidence): m_guardRetaliateMachine +0x20; the AI's state
// machine +0x30 keeps the goal position at +0x24; the retaliate machine keeps
// the position to guard at +0x3C and the nemesis id at +0x48; sizeof 0x4C.
typedef bool Bool;
typedef float Real;
typedef unsigned int UnsignedInt;
enum ObjectID
{
	INVALID_ID = 0
};
#include "../../../Include/Common/StateMachine.h"
#include "../../../Include/Common/StateMachineClass.h"
enum ObjectStatusTypes
{
	OBJECT_STATUS_BFME_26 = 0x26
};
#include "../../../../Libraries/Include/Lib/Coord3D.h"
class Object
{
public:
	ObjectID getID() const { return m_id; }
	class AIUpdateInterface *getAI() { return m_ai; }
	Bool testStatus(ObjectStatusTypes bit) const;
	Object *rva002931F5(Bool flag);
private:
	unsigned char m_pad00[0x74];
	ObjectID m_id; // +0x74
	unsigned char m_pad78[0x258 - 0x78];
	class AIUpdateInterface *m_ai; // +0x258
};
#include "../../../Include/Common/StateMachineClass.h"
class AIUpdateInterface
{
public:
	const Coord3D *getGoalPosition() const { return m_stateMachine->getGoalPosition(); }
	Object *getGoalObject() { return m_stateMachine->getGoalObject(); }
	// LINK: same-body helpers under TU-unique names (identical inlined
	// bytes, chained to StateMachine::getGoalPosition). This TU's
	// copies lose (first-copy); the two calls below inline them but still emit
	// loser COMDATs. Rebinding there emits only unique (trivially kept)
	// copies. No flags touched.
	const Coord3D *bfme_ai_goal_position() const { return m_stateMachine->getGoalPosition(); }
	Object *bfme_ai_goal_object() { return m_stateMachine->getGoalObject(); }
private:
	unsigned char m_pad00[0x30];
	StateMachine *m_stateMachine; // +0x30
};
class AIGuardRetaliateMachine : public StateMachine
{
public:
	AIGuardRetaliateMachine(Object *owner);
	void setTargetPositionToGuard(const Coord3D *pos) { m_positionToGuard = *pos; }
	void setNemesisID(ObjectID id) { m_nemesisToAttack = id; }
private:
	Coord3D m_positionToGuard; // +0x3C
	ObjectID m_nemesisToAttack; // +0x48
};
class AIGuardRetaliateState : public State
{
public:
	virtual StateReturnType onEnter();
private:
	AIGuardRetaliateMachine *m_guardRetaliateMachine; // +0x20
};

//----------------------------------------------------------------------------------------------------------
StateReturnType AIGuardRetaliateState::onEnter()
{

	Object *obj = getMachineOwner();
	AIUpdateInterface *ai = obj->getAI();

	m_guardRetaliateMachine = new AIGuardRetaliateMachine( getMachineOwner());
	// tell the guarding machine what it is guarding with
	m_guardRetaliateMachine->setTargetPositionToGuard( ai->bfme_ai_goal_position() );

	Object *goalObject = ai->bfme_ai_goal_object();
	if( goalObject )
	{
		if (goalObject->testStatus(OBJECT_STATUS_BFME_26) && goalObject->rva002931F5(false))
			goalObject = goalObject->rva002931F5(false);
		m_guardRetaliateMachine->setNemesisID( goalObject->getID() );
	}

	// now that essential parameters are set, set the machine's initial state
	return m_guardRetaliateMachine->initDefaultState();
}
