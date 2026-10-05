// cl: /O1 /DNDEBUG /MD /EHsc
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
enum StateReturnType
{
	STATE_CONTINUE = 0
};
enum ObjectStatusTypes
{
	OBJECT_STATUS_BFME_26 = 0x26
};
struct Coord3D
{
	Real x, y, z;
};
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
class StateMachine
{
public:
	virtual ~StateMachine();
	virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06();
	virtual StateReturnType initDefaultState();
	Object *getOwner() const { return m_owner; }
	Object *getGoalObject();
	const Coord3D *getGoalPosition() const { return &m_goalPosition; }
protected:
	unsigned char m_pad04[0x14 - 0x04];
	Object *m_owner; // +0x14
	unsigned char m_pad18[0x24 - 0x18];
	Coord3D m_goalPosition; // +0x24
};
class AIUpdateInterface
{
public:
	const Coord3D *getGoalPosition() const { return m_stateMachine->getGoalPosition(); }
	Object *getGoalObject() { return m_stateMachine->getGoalObject(); }
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
	unsigned char m_pad30[0x3C - 0x30];
	Coord3D m_positionToGuard; // +0x3C
	ObjectID m_nemesisToAttack; // +0x48
};
class State
{
public:
	virtual ~State();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual StateReturnType onEnter();
protected:
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};
class AIGuardRetaliateState : public State
{
public:
	virtual StateReturnType onEnter();
private:
	unsigned char m_pad1C[0x20 - 0x1C];
	AIGuardRetaliateMachine *m_guardRetaliateMachine; // +0x20
};

//----------------------------------------------------------------------------------------------------------
StateReturnType AIGuardRetaliateState::onEnter()
{

	Object *obj = getMachineOwner();
	AIUpdateInterface *ai = obj->getAI();

	m_guardRetaliateMachine = new AIGuardRetaliateMachine( getMachineOwner());
	// tell the guarding machine what it is guarding with
	m_guardRetaliateMachine->setTargetPositionToGuard( ai->getGoalPosition() );

	Object *goalObject = ai->getGoalObject();
	if( goalObject )
	{
		if (goalObject->testStatus(OBJECT_STATUS_BFME_26) && goalObject->rva002931F5(false))
			goalObject = goalObject->rva002931F5(false);
		m_guardRetaliateMachine->setNemesisID( goalObject->getID() );
	}

	// now that essential parameters are set, set the machine's initial state
	return m_guardRetaliateMachine->initDefaultState();
}
