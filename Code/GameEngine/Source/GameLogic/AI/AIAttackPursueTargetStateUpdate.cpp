// cl: /O1 /G7 /DNDEBUG /MD
//
// AIAttackPursueTargetState::update, retail 0x003495A1 (92 bytes): slot 6 of
// vtable 0x00C12730, whose slot-2 name getter returns
// AIAttackPursueTargetState (slot 5 is the rowed onExit). Ported from Zero
// Hour's GameEngine/Source/GameLogic/AI/AIStates.cpp (GeneralsMD tree
// vendored under reference/open-bfme-1/inputs/reference): run updateInternal
// (pinned 0x0034939E), and on the initial approach aim a turret at the next
// mood target (rowed getWhichTurretForCurWeapon, getNextMoodTarget,
// setTurretTargetObject).
// BFME 2 difference (target evidence): after setting the turret target it
// also sets the AI flag byte +0x3C7.
// Layout: m_isInitialApproach +0x5F, m_isForceAttacking +0x60.
typedef bool Bool;
enum StateReturnType
{
	STATE_CONTINUE = 0
};
enum WhichTurretType
{
	TURRET_INVALID = -1,
	TURRET_MAIN = 0
};
class Object;
class AIUpdateInterface
{
public:
	WhichTurretType getWhichTurretForCurWeapon() const;
	Object *getNextMoodTarget(Bool calledByAI, Bool calledDuringIdle);
	void setTurretTargetObject(WhichTurretType tur, Object *o, Bool isForceAttacking = false);
	void setBfme3C7() { m_bfme3C7 = true; }
private:
	unsigned char m_pad000[0x3C7];
	Bool m_bfme3C7; // +0x3C7
};
class Object
{
public:
	AIUpdateInterface *getAI() { return m_ai; }
private:
	unsigned char m_pad00[0x258];
	AIUpdateInterface *m_ai; // +0x258
};
class StateMachine
{
public:
	Object *getOwner() const { return m_owner; }
private:
	unsigned char m_pad00[0x14];
	Object *m_owner; // +0x14
};
class State
{
public:
	virtual ~State();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual StateReturnType onEnter();
	virtual void onExit(int status);
	virtual StateReturnType update();
protected:
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};
class AIAttackPursueTargetState : public State
{
public:
	virtual StateReturnType update();
private:
	StateReturnType updateInternal( void );
	unsigned char m_pad1C[0x5F - 0x1C];
	Bool m_isInitialApproach; // +0x5F
	Bool m_isForceAttacking; // +0x60
};

//----------------------------------------------------------------------------------------------------------
StateReturnType AIAttackPursueTargetState::update()
{
	// contained by AIAttackState, so no separate timer

	StateReturnType code = updateInternal();
	Object* source = getMachineOwner();
	AIUpdateInterface *ai = source->getAI();

	if (m_isInitialApproach) 
	{
		WhichTurretType tur = ai->getWhichTurretForCurWeapon();
		if (tur != TURRET_INVALID) 
		{
			Object *temporaryTarget = ai->getNextMoodTarget( true, false );
			if (temporaryTarget) 
			{
				ai->setTurretTargetObject(tur, temporaryTarget, m_isForceAttacking);
				ai->setBfme3C7();
			}
		}
	}

	return code;
}
