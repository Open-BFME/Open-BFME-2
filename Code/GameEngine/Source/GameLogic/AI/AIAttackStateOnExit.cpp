// cl: /DNDEBUG /MD
//
// AIAttackState::onExit, retail 0x0034B889 (201 bytes): slot 5 of vtable
// 0x00C13B78, whose slot-2 name getter returns AIAttackState.
// Donor: BFME1 game/GameEngine/Source/GameLogic/AI/AIAttackStateOnExitClean.cpp
// (open-bfme-1 068db38bb4) and the Zero Hour AIStates.cpp onExit: delete the
// attack machine, clear object statuses 13/25/22/27/28, clear the attacking
// model conditions, release the weapon lock, then reset the AI victim, turret
// target and goal.
// BFME2 deltas (target evidence): the attack machine is at +0x24 and is deleted
// with a global-scope delete (vslot 0 with flag 0, then ::operator delete);
// the statuses go through the rowed setStatus(ObjectStatusTypes, bool); the
// conditions are bits 1*32+5..7 of the Object+0x10C words; the weapon-lock
// release is the Object +0x330 forwarder 0x0028BC4D (pinned by address); only
// turret 0 is reset; the goal reset is the rowed AIUpdateInterface::rva00262B0F.
enum StateExitType
{
	EXIT_NORMAL = 0
};
enum StateReturnType
{
	STATE_CONTINUE = 0
};
enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE = 0
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
	void setCurrentVictim(const Object *nemesis);
	void setTurretTargetObject(WhichTurretType tur, Object *o, bool isForceAttacking);
	void rva00262B0F(int x);
};
class ModelConditionFlags
{
public:
	unsigned int test(unsigned int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void clear(unsigned int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[19];
};
class Object
{
public:
	void rva0028AE6D();
	void rva0028BC4D();
	void setStatus(ObjectStatusTypes status, bool set);
	static __forceinline AIUpdateInterface *getAI(const Object *object) { return object->m_ai; }
	__forceinline void clearModelConditionState(unsigned int mc)
	{
		if (m_modelConditionFlags.test(mc) != 0)
		{
			m_modelConditionFlags.clear(mc);
			rva0028AE6D();
		}
	}
private:
	unsigned char m_pad000[0x10C];
	ModelConditionFlags m_modelConditionFlags; // +0x10C
	unsigned char m_pad158[0x258 - 0x158];
	AIUpdateInterface *m_ai; // +0x258
};
class StateMachine
{
public:
	virtual ~StateMachine();
	Object *getOwner() const { return m_owner; }
private:
	unsigned char m_pad04[0x14 - 0x04];
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
protected:
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};
class AIAttackState : public State
{
public:
	virtual void onExit(StateExitType status);
private:
	unsigned char m_pad1C[0x24 - 0x1C];
	StateMachine *m_attackMachine; // +0x24
};
void AIAttackState::onExit(StateExitType status)
{
	// destroy the attack machine
	if (m_attackMachine)
	{
		::delete m_attackMachine;
		m_attackMachine = 0;
	}

	Object *obj = getMachineOwner();
	obj->setStatus((ObjectStatusTypes)0x0D, false);
	obj->setStatus((ObjectStatusTypes)0x19, false);
	obj->setStatus((ObjectStatusTypes)0x16, false);
	obj->setStatus((ObjectStatusTypes)0x1B, false);
	obj->setStatus((ObjectStatusTypes)0x1C, false);
	obj->clearModelConditionState(1 * 32 + 5);
	obj->clearModelConditionState(1 * 32 + 6);
	obj->clearModelConditionState(1 * 32 + 7);
	obj->rva0028BC4D();

	AIUpdateInterface *ai = Object::getAI(obj);
	if (ai)
	{
		ai->setCurrentVictim(0);
		ai->setTurretTargetObject(TURRET_MAIN, 0, false);
		ai->rva00262B0F(0);
	}
}
