// cl: /DNDEBUG /MD
//
// BFME 2 AI state enter/exit overrides with no Zero Hour counterpart. Each
// class is named by its vtable's slot-2 name getter (the state's own name
// literal):
//
//  - AIHordeExitState::onExit, retail 0x00341A61 (52 bytes): slot 5 of
//    0x00C11468, also filling the AIHordeExitAndMoveToState (0x00C114C0) and
//    AIHordeExitAndFollowPathState (0x00C11520) tables. Tells the goal
//    object's contain (Object+0x250, slot 17) that the owner wants neither
//    to enter nor exit, then clears the machine goal object (machine slot
//    14), as Zero Hour's AIExitState::onExit tells the contain.
//  - AIHordeEnterState::onExit, retail 0x003462AE (51 bytes): slot 5 of
//    0x00C11410. Unless the goal object's template has kind byte +0x108 bit 2
//    set, calls the rowed Object::rva00292ED0 with 8 on it; then the base
//    State::onExit (the shared empty body 0x0047A69C, pinned).
//  - AIUncontrollableCower::onEnter, retail 0x00347EA8 (82 bytes): slot 4 of
//    0x00C12048. Remembers the owner's isSelectable at +0x20, clears it, sets
//    object status 0x45, raises model-condition bit 314 (word +0x130 of the
//    bits at +0x10C, notifying through the rowed Object::rva0028AE6D), locks
//    the machine (+0x38) and tail-calls AICowerState::onEnter (slot 4 of the
//    AICowerState table 0x00C11958, pinned 0x00344598).
//  - AIMoveOntoWallState::onEnter, retail 0x00343D63 (117 bytes): slot 4 of
//    0x00C11DB0. Creates its MoveOntoWallStateMachine (+0x20, 0x3C bytes,
//    pinned constructor 0x00343BC9 with key 0xCD5F1CAA), hands it the
//    machine's goal object (slot 14) and goal position (+0x24, the pinned
//    StateMachine::setGoalPosition 0x00262224) and starts it (slot 7,
//    initDefaultState).
//  - AIHarvestState::onEnter, retail 0x00341891 (89 bytes): slot 4 of
//    0x00C113B8. The same for its AIHarvestMachine (pinned constructor
//    0x00544ED4) without a goal object, returning the sub-machine's
//    initDefaultState result.
//
//  - AIUncontrollableCower::onExit, retail 0x00347EFA (78 bytes): slot 5 of
//    0x00C12048. Restores the remembered selectable flag, clears status
//    0x45 and condition bit 314, unlocks the machine and runs
//    AICowerState::onExit (pinned 0x003402FC).
//  - AIQuarrelState::onExit / update, retail 0x00340342 (45 bytes) and
//    0x0034036F (34 bytes): slots 5 and 6 of 0x00C119B0. The base onExit
//    then slot 107 of the rowed Object::rva0029439D interface; update fails
//    without an owner and otherwise succeeds when the rowed
//    Object::rva0028C264 (with 4) holds.
//  - AIHordeExitState::onEnter, retail 0x00341A1B (70 bytes): slot 4 of
//    0x00C11468. Needs an owner, a goal object and the owner's contain
//    slot-31 horde interface; then tells the goal's contain the owner wants
//    to exit (slot 17, WANTS_TO_EXIT) and continues, else fails.
//  - AIHordeExitState::update, retail 0x003462E1 (249 bytes; Ghidra splits
//    a phantom function at 0x00346365): slot 6 of 0x00C11468. Waits while
//    the goal's AI slot 106 says 2, needs the owner's horde (contain slot
//    31) and the goal's exit interface (contain slot 29), waits while it is
//    busy, reserves a door and exits the owner with the +0x20 byte copied to
//    g_00E03624 around the call; when horde slot 62 holds, a still-contained
//    owner exits once more.
//  - AIHordeEnterState::update, retail 0x003419C7 (84 bytes): slot 6 of
//    0x00C11410. With an owner, a goal and the owner's horde interface:
//    succeeds when its slot 61 holds, else hands it the goal (slot 63) and
//    continues; fails otherwise. Its onEnter, retail 0x00346214 (154
//    bytes, slot 4): with a live goal (byte +0x438 bit 0 clear) whose own
//    contain has no horde interface and accepts the owner (contain slot 38
//    with true, false), hands the owner's horde the goal's position, 2 and
//    the goal (horde slot 31), disables the goal with the rowed
//    Object::rva00292EB3(8) unless its template kind byte +0x108 bit 2 is
//    set, and tells the goal's contain (slot 39); fails otherwise.
//  - AIAttackMeleeHordeWaitState::onExit, retail 0x00345207 (63 bytes): slot
//    5 of 0x00C10F40 and of the path variant 0x00C10FA0. Nothing for an
//    owner with byte +0x94 bit 0; otherwise horde slots 78 and 90 (with 0)
//    on the owner's contain horde interface.
//  - AIRampageState::onExit, retail 0x0034BDF8 (95 bytes): slot 5 of
//    0x00C11A08. With an owner and AI: status 0x39 cleared, the rowed
//    clearWeaponSetFlag(8), AI bytes +0x3C5/+0x3C6 cleared, condition bit
//    132 raised and the rowed Object::kill(8, 0).
// The unit builds /G7 (retail passes the selectable Bool without
// zero-extending it).
//
// Target evidence: the pinned StateMachine::getGoalObject 0x004D7726, the
// rowed Object::isSelectable 0x0028D7FD, setSelectable 0x0028B76D and
// setStatus 0x0023DB0E. The base classes are inferred from the calls; the
// meaning of the status, condition and kind bits is not recovered.

enum StateExitType
{
	EXIT_NORMAL = 0
};
enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};
enum ObjectEnterExitType
{
	WANTS_TO_ENTER = 0,
	WANTS_TO_EXIT = 1,
	WANTS_NEITHER = 2
};
enum ObjectStatusTypes
{
	OBJECT_STATUS_BFME_39 = 0x39,
	OBJECT_STATUS_BFME_45 = 0x45
};
enum DisabledType
{
	DISABLED_BFME_8 = 8
};
typedef bool Bool;

class Object;

class ThingTemplate;

// A contain module's exit interface (contain slot 29).
class ExitInterface
{
public:
	virtual Bool isExitBusy() = 0;
	virtual int reserveDoorForExit(const ThingTemplate *objType, Object *specificObject) = 0;
	virtual void exitObjectViaDoor(Object *newObj, int exitDoor) = 0;
};

class ContainModuleInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void onObjectWantsToEnterOrExit(Object *obj, ObjectEnterExitType wants) = 0;
	virtual void slot18() = 0; virtual void slot19() = 0; virtual void slot20() = 0;
	virtual void slot21() = 0; virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0; virtual void slot26() = 0;
	virtual void slot27() = 0; virtual void slot28() = 0;
	virtual ExitInterface *getContainExitInterface() = 0;
	virtual void slot30() = 0;
	virtual class Rva00341A3EHorde *rva00341A3ESlot31() = 0;
	virtual void slot32() = 0; virtual void slot33() = 0; virtual void slot34() = 0;
	virtual void slot35() = 0; virtual void slot36() = 0; virtual void slot37() = 0;
	virtual Bool rva00346269Slot38(Object *obj, Bool flagA, Bool flagB) = 0;
	virtual void rva0034629CSlot39(Object *obj) = 0;
};

template <int N> class HordeSlots : public HordeSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class HordeSlots<0>
{
};

// What contain slot 31 returns (opaque): slot 31 (position, kind, object),
// slot 61 (Bool) and slot 63 (Object *) are the AIHordeEnterState calls.
struct Coord3D
{
	float x, y, z;
};

class Rva00341A3EHordeHead : public HordeSlots<31>
{
public:
	virtual void rva0034627FSlot31(const Coord3D *pos, int kind, Object *obj) = 0;
};

class Rva00341A3EHorde : public Rva00341A3EHordeHead
{
public:
	virtual void s32() = 0; virtual void s33() = 0; virtual void s34() = 0;
	virtual void s35() = 0; virtual void s36() = 0; virtual void s37() = 0;
	virtual void s38() = 0; virtual void s39() = 0; virtual void s40() = 0;
	virtual void s41() = 0; virtual void s42() = 0; virtual void s43() = 0;
	virtual void s44() = 0; virtual void s45() = 0; virtual void s46() = 0;
	virtual void s47() = 0; virtual void s48() = 0; virtual void s49() = 0;
	virtual void s50() = 0; virtual void s51() = 0; virtual void s52() = 0;
	virtual void s53() = 0; virtual void s54() = 0; virtual void s55() = 0;
	virtual void s56() = 0; virtual void s57() = 0; virtual void s58() = 0;
	virtual void s59() = 0; virtual void s60() = 0;
	virtual Bool rva003419F7Slot61() = 0;
	virtual Bool rva003463A0Slot62() = 0;
	virtual void rva00341A0BSlot63(Object *obj) = 0;
	virtual void s64() = 0; virtual void s65() = 0; virtual void s66() = 0;
	virtual void s67() = 0; virtual void s68() = 0; virtual void s69() = 0;
	virtual void s70() = 0; virtual void s71() = 0; virtual void s72() = 0;
	virtual void s73() = 0; virtual void s74() = 0; virtual void s75() = 0;
	virtual void s76() = 0; virtual void s77() = 0;
	virtual void rva00345230Slot78() = 0;
	virtual void s79() = 0; virtual void s80() = 0; virtual void s81() = 0;
	virtual void s82() = 0; virtual void s83() = 0; virtual void s84() = 0;
	virtual void s85() = 0; virtual void s86() = 0; virtual void s87() = 0;
	virtual void s88() = 0; virtual void s89() = 0;
	virtual void rva0034523CSlot90(int value) = 0;
};

class ThingTemplate
{
public:
	Bool isKindOfBfme108Bit2() const { return (m_kindOf[0] & 4) != 0; }
private:
	unsigned char m_pad00[0x108];
	unsigned char m_kindOf[4]; // +0x108
};

enum WeaponSetType
{
	WEAPONSET_BFME_8 = 8
};
enum DamageType
{
	DAMAGE_BFME_8 = 8
};
enum DeathType
{
	DEATH_NORMAL = 0
};

template <int N> class CowerSlots : public CowerSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class CowerSlots<0>
{
};

// The interface the rowed Object::rva0029439D returns (opaque): slot 107 is
// the one AIQuarrelState::onExit calls.
class Rva0029439DTarget : public CowerSlots<107>
{
public:
	virtual void rva00340366Slot107() = 0;
};

// The goal AI's slot 106 (2: the goal is still taking the owner in).
class AIExitStateView : public CowerSlots<106>
{
public:
	virtual int rva003462E1Slot106(Object *obj) = 0;
};
class AIUpdateInterface
{
public:
	unsigned char m_pad000[0x3C5];
	Bool m_bfmeFlag3C5; // +0x3C5
	Bool m_bfmeFlag3C6; // +0x3C6
};

class Rva0010CBits
{
public:
	unsigned int test(int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(int bit)
	{
		m_words[bit >> 5] |= (1U << (bit & 0x1f));
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
	const ThingTemplate *getTemplate() const { return m_template; }
	ContainModuleInterface *getContain() const { return m_contain; }
	Bool isSelectable() const;
	void setSelectable(Bool selectable);
	void setStatus(ObjectStatusTypes status, Bool set);
	Bool rva00292ED0(DisabledType type);
	void rva0028AE6D();
	__forceinline void setModelConditionBit(int bit)
	{
		if (m_conditionBits.test(bit) == 0)
		{
			m_conditionBits.set(bit);
			rva0028AE6D();
		}
	}
	__forceinline void clearModelConditionBit(int bit)
	{
		if (m_conditionBits.test(bit) != 0)
		{
			m_conditionBits.clear(bit);
			rva0028AE6D();
		}
	}
	void *rva0029439D();
	Bool rva0028C264(int *value, int kind);
	void clearWeaponSetFlag(WeaponSetType wst);
	void kill(DamageType damageType, DeathType deathType);
	AIUpdateInterface *getAI() { return m_ai; }
	const Coord3D *getPosition() const { return &m_position; }
	Bool isDestroyedBfme() const { return (m_bfmeFlags438 & 1) != 0; }
	Bool testBfmeFlag94() const { return (m_bfmeFlags94 & 1) != 0; }
	void rva00292EB3(DisabledType type);
	Object *getContainedBy() const { return m_containedBy; }
private:
	unsigned char m_pad000[0x04];
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad008[0x38 - 0x08];
	Coord3D m_position; // +0x38
	unsigned char m_pad044[0x94 - 0x44];
	unsigned char m_bfmeFlags94; // +0x94
	unsigned char m_pad095[0x10C - 0x95];
	Rva0010CBits m_conditionBits; // +0x10C
	unsigned char m_pad158[0x250 - (0x10C + sizeof(Rva0010CBits))];
	ContainModuleInterface *m_contain; // +0x250
	unsigned char m_pad254[0x258 - 0x254];
	AIUpdateInterface *m_ai; // +0x258
	unsigned char m_pad25C[0x274 - 0x25C];
	Object *m_containedBy; // +0x274
	unsigned char m_pad278[0x438 - 0x278];
	unsigned char m_bfmeFlags438; // +0x438
};

class StateMachine
{
public:
	virtual ~StateMachine();
	virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06();
	virtual StateReturnType initDefaultState();
	virtual void slot08(); virtual void slot09();
	virtual void slot10(); virtual void slot11(); virtual void slot12();
	virtual void slot13();
	virtual void setGoalObject(const Object *obj);
	Object *getOwner() const { return m_owner; }
	Object *getGoalObject();
	const Coord3D *getGoalPosition() const { return &m_goalPosition; }
	void setGoalPosition(const Coord3D *pos);
	void lock() { m_locked = true; }
	void unlock() { m_locked = false; }
private:
	unsigned char m_pad04[0x14 - 0x04];
	Object *m_owner; // +0x14
	unsigned char m_pad18[0x24 - 0x18];
	Coord3D m_goalPosition; // +0x24
	unsigned char m_pad30[0x38 - 0x30];
	Bool m_locked; // +0x38
};

// MoveOntoWallStateMachine (vftable 0x00C11D50, by its slot-2 name literal;
// dtor rowed as Rva0033FC0A): 0x3C bytes, constructor pinned 0x00343BC9.
class Rva0033FC0A : public StateMachine
{
public:
	Rva0033FC0A(Object *owner, unsigned int nameKey);
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

extern Bool g_00E03624;

class AIHordeExitState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
private:
	unsigned char m_pad1C[0x20 - 0x1C];
	Bool m_20; // +0x20
};

void AIHordeExitState::onExit(StateExitType status)
{
	Object *goal = getMachine()->getGoalObject();
	if (goal && goal->getContain())
		goal->getContain()->onObjectWantsToEnterOrExit(getMachineOwner(), WANTS_NEITHER);
	getMachine()->setGoalObject(0);
}

class AIHordeEnterState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
};

void AIHordeEnterState::onExit(StateExitType status)
{
	Object *goal = getMachine()->getGoalObject();
	if (goal && !goal->getTemplate()->isKindOfBfme108Bit2())
		goal->rva00292ED0(DISABLED_BFME_8);
	State::onExit(status);
}

class AICowerState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
};

class AIUncontrollableCower : public AICowerState
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
private:
	unsigned char m_pad1C[0x20 - 0x1C];
	Bool m_wasSelectable; // +0x20
};

StateReturnType AIUncontrollableCower::onEnter()
{
	Object *owner = getMachineOwner();
	m_wasSelectable = owner->isSelectable();
	owner->setSelectable(false);
	owner->setStatus(OBJECT_STATUS_BFME_45, true);
	owner->setModelConditionBit(314);
	getMachine()->lock();
	return AICowerState::onEnter();
}

// AIHarvestMachine (vftable 0x00C69D58, by its slot-2 name literal; dtor
// rowed as Rva00544C51): 0x3C bytes, constructor pinned 0x00544ED4.
class Rva00544C51 : public StateMachine
{
public:
	Rva00544C51(Object *owner);
};

class AIHarvestState : public State
{
public:
	virtual StateReturnType onEnter();
private:
	unsigned char m_pad1C[0x20 - 0x1C];
	Rva00544C51 *m_harvestMachine; // +0x20
};

StateReturnType AIHarvestState::onEnter()
{
	m_harvestMachine = new Rva00544C51(getMachineOwner());
	m_harvestMachine->setGoalPosition(getMachine()->getGoalPosition());
	return m_harvestMachine->initDefaultState();
}

class AIMoveOntoWallState : public State
{
public:
	virtual StateReturnType onEnter();
private:
	unsigned char m_pad1C[0x20 - 0x1C];
	Rva0033FC0A *m_wallMachine; // +0x20
};

StateReturnType AIMoveOntoWallState::onEnter()
{
	m_wallMachine = new Rva0033FC0A(getMachineOwner(), 0xCD5F1CAA);
	m_wallMachine->setGoalObject(getMachine()->getGoalObject());
	m_wallMachine->setGoalPosition(getMachine()->getGoalPosition());
	m_wallMachine->initDefaultState();
	return STATE_CONTINUE;
}

void AIUncontrollableCower::onExit(StateExitType status)
{
	Object *owner = getMachineOwner();
	owner->setSelectable(m_wasSelectable);
	owner->setStatus(OBJECT_STATUS_BFME_45, false);
	owner->clearModelConditionBit(314);
	getMachine()->unlock();
	AICowerState::onExit(status);
}

class AIQuarrelState : public State
{
public:
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
};

void AIQuarrelState::onExit(StateExitType status)
{
	State::onExit(status);
	Object *owner = getMachineOwner();
	if (owner)
	{
		Rva0029439DTarget *target = (Rva0029439DTarget *)owner->rva0029439D();
		if (target)
			target->rva00340366Slot107();
	}
}

StateReturnType AIQuarrelState::update()
{
	Object *owner = getMachineOwner();
	if (!owner)
		return STATE_FAILURE;
	int value;
	return owner->rva0028C264(&value, 4) ? STATE_SUCCESS : STATE_CONTINUE;
}

class AIRampageState : public State
{
public:
	virtual void onExit(StateExitType status);
};

void AIRampageState::onExit(StateExitType status)
{
	Object *owner = getMachineOwner();
	if (!owner)
		return;
	AIUpdateInterface *ai = owner->getAI();
	if (!ai)
		return;
	owner->setStatus(OBJECT_STATUS_BFME_39, false);
	owner->clearWeaponSetFlag(WEAPONSET_BFME_8);
	ai->m_bfmeFlag3C5 = false;
	ai->m_bfmeFlag3C6 = false;
	owner->setModelConditionBit(132);
	owner->kill(DAMAGE_BFME_8, DEATH_NORMAL);
}

StateReturnType AIHordeExitState::onEnter()
{
	Object *owner = getMachineOwner();
	Object *goal = getMachine()->getGoalObject();
	if (owner && goal && owner->getContain() && owner->getContain()->rva00341A3ESlot31())
	{
		if (goal->getContain())
			goal->getContain()->onObjectWantsToEnterOrExit(owner, WANTS_TO_EXIT);
		return STATE_CONTINUE;
	}
	return STATE_FAILURE;
}

StateReturnType AIHordeExitState::update()
{
	Object *owner = getMachineOwner();
	Object *goal = getMachine()->getGoalObject();
	if (!owner || !goal)
		return STATE_FAILURE;
	if (goal->getAI() && ((AIExitStateView *)goal->getAI())->rva003462E1Slot106(owner) == 2)
		return STATE_CONTINUE;
	if (!owner->getContain())
		return STATE_FAILURE;
	Rva00341A3EHorde *horde = owner->getContain()->rva00341A3ESlot31();
	if (!horde)
		return STATE_FAILURE;
	ExitInterface *exitInterface = goal->getContain() ? goal->getContain()->getContainExitInterface() : 0;
	if (!exitInterface)
		return STATE_FAILURE;
	if (exitInterface->isExitBusy())
		return STATE_CONTINUE;
	int exitDoor = exitInterface->reserveDoorForExit(owner->getTemplate(), owner);
	if (exitDoor == -1)
		return STATE_FAILURE;
	g_00E03624 = m_20;
	exitInterface->exitObjectViaDoor(owner, exitDoor);
	g_00E03624 = false;
	if (!horde->rva003463A0Slot62())
	{
		if (owner->getContainedBy())
			return STATE_CONTINUE;
	}
	else if (owner->getContainedBy())
	{
		g_00E03624 = m_20;
		exitInterface->exitObjectViaDoor(owner, exitDoor);
		g_00E03624 = false;
	}
	return STATE_SUCCESS;
}

StateReturnType AIHordeEnterState::update()
{
	Object *owner = getMachineOwner();
	Object *goal = getMachine()->getGoalObject();
	if (owner && goal && owner->getContain())
	{
		Rva00341A3EHorde *horde = owner->getContain()->rva00341A3ESlot31();
		if (horde)
		{
			if (horde->rva003419F7Slot61())
				return STATE_SUCCESS;
			horde->rva00341A0BSlot63(goal);
			return STATE_CONTINUE;
		}
	}
	return STATE_FAILURE;
}

StateReturnType AIHordeEnterState::onEnter()
{
	Object *owner = getMachineOwner();
	Object *goal = getMachine()->getGoalObject();
	if (owner && goal && !goal->isDestroyedBfme() && owner->getContain())
	{
		Rva00341A3EHorde *horde = owner->getContain()->rva00341A3ESlot31();
		if (horde)
		{
			ContainModuleInterface *goalContain = goal->getContain();
			if (goalContain && !goalContain->rva00341A3ESlot31()
				&& goalContain->rva00346269Slot38(owner, true, false))
			{
				horde->rva0034627FSlot31(goal->getPosition(), 2, goal);
				if (!goal->getTemplate()->isKindOfBfme108Bit2())
					goal->rva00292EB3(DISABLED_BFME_8);
				goalContain->rva0034629CSlot39(owner);
				return STATE_CONTINUE;
			}
		}
	}
	return STATE_FAILURE;
}

class AIAttackMeleeHordeWaitState : public State
{
public:
	virtual void onExit(StateExitType status);
};

void AIAttackMeleeHordeWaitState::onExit(StateExitType status)
{
	Object *owner = getMachineOwner();
	if (owner->testBfmeFlag94())
		return;
	if (owner->getContain())
	{
		Rva00341A3EHorde *horde = owner->getContain()->rva00341A3ESlot31();
		if (horde)
		{
			horde->rva00345230Slot78();
			horde->rva0034523CSlot90(0);
		}
	}
}
