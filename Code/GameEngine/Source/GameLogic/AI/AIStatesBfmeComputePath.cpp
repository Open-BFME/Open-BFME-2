// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// Small computePath (slot 17) and onExit (slot 5) overrides of AI states,
// each named by its vtable's own slot-2 name getter (the state's name
// literal). BFME 2 logs a numbered "CritterDesync" line from computePath
// when the desync log is on (g_00E03745, file g_00DFEFF0):
//
//  - AIMoveAndTightenState::computePath 0x00340158 (34 bytes; 0x00C124D8,
//    whose constructor 0x00342843 builds on AIInternalMoveToState directly):
//    "ComputePath4", then keeps the existing path (true).
//  - AIMoveAwayAndCowerState::computePath 0x003403DC (53 bytes; 0x00C12FF0)
//    and AIBackAwayState::computePath 0x0034042C (53 bytes; 0x00C13050):
//    "ComputePath8" / "ComputePath9", then spend one of the repath tries at
//    +0x4C (Zero Hour's m_okToRepathTimes) or fail.
//  - AIPickUpCrateState::computePath 0x00345B5F (42 bytes; 0x00C128D0) and
//    AIFollowPathState::computePath 0x00345B89 (42 bytes; 0x00C12BC8):
//    "ComputePath30" / "ComputePath31", then the base
//    AIInternalMoveToState::computePath (pinned 0x003441F7) as a tail call.
//  - AIWaitUntilFinishedFiringState::onExit 0x00341391 (16 bytes;
//    0x00C11120): releases the owner's weapon lock (pinned
//    Object::releaseWeaponLock, LOCKED_TEMPORARILY); no base call.
//  - AIAttackMeleeSquishState::onExit 0x003497C7 (31 bytes; 0x00C12868):
//    base onExit, then object status 0x1C cleared.
//  - AIMoveAwayAndCowerState::onExit 0x00347F48 (46 bytes): base onExit,
//    then AI slot 142 with 0.
//  - AIBackAwayState::onExit 0x00347FFE (80 bytes): base onExit, then
//    model-condition bit 65 cleared (notifying through the rowed
//    Object::rva0028AE6D), AI slot 142 with 0 and the AI byte +0x3C8 cleared.
//
// The meaning of the status, condition and AI bytes is not recovered.

typedef bool Bool;
typedef float Real;
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
	OBJECT_STATUS_BFME_1C = 0x1C
};
enum WeaponLockType
{
	NOT_LOCKED,
	LOCKED_TEMPORARILY
};

extern unsigned char g_00E03745;
extern void *g_00DFEFF0;
struct FprintfTarget
{
	char m_pad[4];
};
extern "C" void fprintf(FprintfTarget *target, const char *format, ...);
static __forceinline void critterDesyncLog(const char *text)
{
	if (g_00E03745)
	{
		FprintfTarget *log = (FprintfTarget *)g_00DFEFF0;
		if (log != 0)
			fprintf(log, text);
	}
}

template <int N> class AIComputePathAISlots : public AIComputePathAISlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class AIComputePathAISlots<0>
{
};

class AIUpdateInterface : public AIComputePathAISlots<142>
{
public:
	virtual void rva00347F6BSlot142(int value) = 0;
	unsigned char m_pad004[0x3C8 - 0x04];
	Bool m_bfmeFlag3C8; // +0x3C8
};

class Rva0010CBits
{
public:
	unsigned int test(int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void clear(int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[19];
};

class Object
{
public:
	AIUpdateInterface *getAI() { return m_ai; }
	void setStatus(ObjectStatusTypes status, Bool set);
	void releaseWeaponLock(WeaponLockType lockType);
	void rva0028AE6D();
	__forceinline void clearModelConditionBit(int bit)
	{
		if (m_conditionBits.test(bit) != 0)
		{
			m_conditionBits.clear(bit);
			rva0028AE6D();
		}
	}
private:
	unsigned char m_pad000[0x10C];
	Rva0010CBits m_conditionBits; // +0x10C
	unsigned char m_pad158[0x258 - (0x10C + sizeof(Rva0010CBits))];
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
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
	virtual void slot07(); virtual void slot08(); virtual void slot09();
	virtual void slot10(); virtual void slot11(); virtual void slot12();
	virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16();
protected:
	virtual Bool computePath();
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};

class AIInternalMoveToState : public State
{
public:
	virtual void onExit(StateExitType status);
protected:
	virtual Bool computePath();
	unsigned char m_pad1C[0x4C - 0x1C];
};

class AIMoveAndTightenState : public AIInternalMoveToState
{
protected:
	virtual Bool computePath();
};

Bool AIMoveAndTightenState::computePath()
{
	critterDesyncLog("CritterDesync: ComputePath4");
	return true;
}

class AIMoveAwayAndCowerState : public AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType status);
protected:
	virtual Bool computePath();
private:
	int m_okToRepathTimes; // +0x4C
};

Bool AIMoveAwayAndCowerState::computePath()
{
	critterDesyncLog("CritterDesync: ComputePath8");
	if (m_okToRepathTimes > 0)
	{
		m_okToRepathTimes--;
		return true;
	}
	return false;
}

void AIMoveAwayAndCowerState::onExit(StateExitType status)
{
	AIInternalMoveToState::onExit(status);
	Object *owner = getMachineOwner();
	if (owner && owner->getAI())
		owner->getAI()->rva00347F6BSlot142(0);
}

class AIBackAwayState : public AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType status);
protected:
	virtual Bool computePath();
private:
	int m_okToRepathTimes; // +0x4C
};

Bool AIBackAwayState::computePath()
{
	critterDesyncLog("CritterDesync: ComputePath9");
	if (m_okToRepathTimes > 0)
	{
		m_okToRepathTimes--;
		return true;
	}
	return false;
}

void AIBackAwayState::onExit(StateExitType status)
{
	AIInternalMoveToState::onExit(status);
	Object *owner = getMachineOwner();
	if (!owner)
		return;
	owner->clearModelConditionBit(65);
	if (owner->getAI())
	{
		owner->getAI()->rva00347F6BSlot142(0);
		owner->getAI()->m_bfmeFlag3C8 = false;
	}
}

class AIPickUpCrateState : public AIInternalMoveToState
{
protected:
	virtual Bool computePath();
};

Bool AIPickUpCrateState::computePath()
{
	critterDesyncLog("CritterDesync: ComputePath30");
	return AIInternalMoveToState::computePath();
}

class AIFollowPathState : public AIInternalMoveToState
{
protected:
	virtual Bool computePath();
};

Bool AIFollowPathState::computePath()
{
	critterDesyncLog("CritterDesync: ComputePath31");
	return AIInternalMoveToState::computePath();
}

class AIWaitUntilFinishedFiringState : public State
{
public:
	virtual void onExit(StateExitType status);
};

void AIWaitUntilFinishedFiringState::onExit(StateExitType status)
{
	getMachineOwner()->releaseWeaponLock(LOCKED_TEMPORARILY);
}

class AIAttackMeleeSquishState : public AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType status);
};

void AIAttackMeleeSquishState::onExit(StateExitType status)
{
	AIInternalMoveToState::onExit(status);
	getMachineOwner()->setStatus(OBJECT_STATUS_BFME_1C, false);
}
