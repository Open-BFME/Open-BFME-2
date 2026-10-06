// cl: /DNDEBUG /MD
//
// AIMoveAndEvacuateState::update, retail 0x00353C27 (100 bytes): slot 6 of
// vtable 0x00C12C28, whose slot-2 name getter 0x00342DA5 returns
// AIMoveAndEvacuateState; the body is the Zero Hour AIStates.cpp update
// (effectively-dead checks around the pinned base AIInternalMoveToState::update
// 0x00347460, then aiEvacuate(FALSE, CMD_FROM_AI) through the AI +0x20 command
// interface, rowed 0x002AE6B3, and Team::setActive inline).
// BFME2 layout (target evidence): Object private status byte +0x438 bit 0,
// AI +0x258, team +0x304; Team m_active +0x5D and m_created +0x5E.
typedef bool Bool;
#define FALSE false
enum StateExitType
{
	EXIT_NORMAL = 0
};
enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_FAILURE = -2
};
enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};
class AICommandInterface
{
public:
	void aiEvacuate(Bool exposeStealthUnits, CommandSourceType cmdSource);
};
class AIUpdateInterface
{
public:
	unsigned char m_pad00[0x20];
	AICommandInterface m_commands; // +0x20
};
class Team
{
public:
	void setActive(void) { if (!m_active) { m_created = true; m_active = true; } }
private:
	unsigned char m_pad00[0x5D];
	Bool m_active; // +0x5D
	Bool m_created; // +0x5E
};
class Object
{
public:
	enum
	{
		EFFECTIVELY_DEAD = 1
	};
	AIUpdateInterface *getAI() { return m_ai; }
	Team *getTeam() { return m_team; }
	Bool isEffectivelyDead() const { return (m_privateStatus & EFFECTIVELY_DEAD) != 0; }
private:
	unsigned char m_pad000[0x258];
	AIUpdateInterface *m_ai; // +0x258
	unsigned char m_pad25C[0x304 - 0x25C];
	Team *m_team; // +0x304
	unsigned char m_pad308[0x438 - 0x308];
	unsigned char m_privateStatus; // +0x438
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
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
protected:
	StateMachine *getMachine() const { return m_machine; }
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};
class AIInternalMoveToState : public State
{
public:
	virtual StateReturnType update();
};
class AIMoveAndEvacuateState : public AIInternalMoveToState
{
public:
	virtual StateReturnType update();
};
StateReturnType AIMoveAndEvacuateState::update()
{
	Object *obj = getMachine()->getOwner();
	if (obj->isEffectivelyDead())
	{
		return STATE_FAILURE;
	}

	// do movement
	StateReturnType status = AIInternalMoveToState::update();
	if (status != STATE_CONTINUE)
	{
		Object *obj = getMachineOwner();
		if (obj->isEffectivelyDead())
		{
			return STATE_FAILURE;
		}

		AIUpdateInterface *ai = obj->getAI();
		ai->m_commands.aiEvacuate(FALSE, CMD_FROM_AI);
		obj->getTeam()->setActive();
	}

	return status;
}
