// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
//
// TurretStateMachine::TurretStateMachine, retail 0x004D7CE6 (373 bytes), and
// the five turret state constructors it calls, retail 0x004D7B98..0x004D7C4E.
// Zero Hour's TurretAI.cpp machine: the six turret states with their success
// and failure transitions; the fire state is the rowed attack-fire state
// 0x0033F483 given the turret's attack interface (TurretAI +0x04) and the
// out-of-range condition table. BFME 2 builds the machine from the rowed
// StateMachine constructor 0x004D79E1 with a name key (its unsigned spelling
// is pinned there) and creates every state with plain operator new; each
// state constructor passes its own name key to the rowed TurretState base
// 0x004D7B70.
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef UnsignedInt StateID;
#define NULL 0
class Object;
struct StateConditionInfo
{
	void *m_test;
	StateID m_toStateID;
	void *m_userData;
};
enum TurretStateType
{
	TURRETAI_IDLE = 0,
	TURRETAI_IDLESCAN = 1,
	TURRETAI_AIM = 2,
	TURRETAI_FIRE = 3,
	TURRETAI_RECENTER = 4,
	TURRETAI_HOLD = 5
};
struct State;
class StateMachine
{
public:
	StateMachine(Object *owner, UnsignedInt nameKey, Bool flag);
	virtual ~StateMachine();
	void defineState(StateID id, State *state, StateID successID, StateID failureID, const StateConditionInfo *conditions = NULL);
protected:
	unsigned char m_pad04[0x3C - 0x04];
};
// BFME 2's StateMachine constructor (owner, name key, flag), rowed by address.
class TurretAIAttackInterface
{
public:
	virtual void v00();
};
class TurretAIBase
{
public:
	virtual void v00();
};
class TurretAI : public TurretAIBase, public TurretAIAttackInterface
{
};
class TurretStateMachine : public StateMachine
{
public:
	TurretStateMachine(TurretAI *tai, Object *obj, UnsignedInt nameKey);
	virtual ~TurretStateMachine();
private:
	TurretAI *m_turretAI; // +0x3C
};
struct State
{
public:
	State(StateMachine *machine, UnsignedInt nameKey);
	virtual ~State();
protected:
	unsigned char m_pad04[0x20 - 0x04];
};
// The rowed turret-state base constructor 0x004D7B70.
class Rva004D7B70 : public State
{
public:
	Rva004D7B70(StateMachine *machine, UnsignedInt nameKey);
	virtual ~Rva004D7B70();
};
class TurretAIIdleState : public Rva004D7B70
{
public:
	TurretAIIdleState(TurretStateMachine *machine);
	virtual ~TurretAIIdleState();
private:
	UnsignedInt m_nextIdleScan; // +0x20
};
class TurretAIIdleScanState : public Rva004D7B70
{
public:
	TurretAIIdleScanState(TurretStateMachine *machine);
	virtual ~TurretAIIdleScanState();
private:
	float m_desiredAngle; // +0x20
};
class TurretAIAimTurretState : public Rva004D7B70
{
public:
	TurretAIAimTurretState(TurretStateMachine *machine);
	virtual ~TurretAIAimTurretState();
};
class TurretAIRecenterTurretState : public Rva004D7B70
{
public:
	TurretAIRecenterTurretState(TurretStateMachine *machine);
	virtual ~TurretAIRecenterTurretState();
};
class TurretAIHoldTurretState : public Rva004D7B70
{
public:
	TurretAIHoldTurretState(TurretStateMachine *machine);
	virtual ~TurretAIHoldTurretState();
private:
	UnsignedInt m_timestamp; // +0x20
};
// The rowed attack-fire state (0x0033F483): machine and attack interface.
class Rva0033F483 : public State
{
public:
	Rva0033F483(StateMachine *machine, int attackInterface);
private:
	unsigned char m_pad20[0x28 - 0x20];
};

TurretAIIdleState::TurretAIIdleState(TurretStateMachine *machine) : Rva004D7B70(machine, 0x2722c825u)
{
	m_nextIdleScan = 0;
}

TurretAIIdleScanState::TurretAIIdleScanState(TurretStateMachine *machine) : Rva004D7B70(machine, 0x0a3d5fb3u)
{
	m_desiredAngle = 0.0f;
}

TurretAIAimTurretState::TurretAIAimTurretState(TurretStateMachine *machine) : Rva004D7B70(machine, 0xf5fc67e3u)
{
}

TurretAIRecenterTurretState::TurretAIRecenterTurretState(TurretStateMachine *machine) : Rva004D7B70(machine, 0x5309dbfbu)
{
}

TurretAIHoldTurretState::TurretAIHoldTurretState(TurretStateMachine *machine) : Rva004D7B70(machine, 0x8546a46au)
{
	m_timestamp = 0;
}

// Zero Hour's outOfWeaponRangeObject condition (rowed 0x00343F8A).
class Rva00343F8A;
void rva00343F8A(Rva00343F8A *machine, void *userData);

TurretStateMachine::TurretStateMachine(TurretAI *tai, Object *obj, UnsignedInt nameKey) : StateMachine(obj, nameKey, false), m_turretAI(tai)
{
	static const StateConditionInfo fireConditions[] =
	{
		{ (void *)rva00343F8A, TURRETAI_AIM, NULL },
		{ NULL, 0, NULL }	// keep last
	};

	// order matters: first state is the default state.
	defineState( TURRETAI_IDLE, new TurretAIIdleState( this ), TURRETAI_IDLE, TURRETAI_IDLESCAN );
	defineState( TURRETAI_IDLESCAN, new TurretAIIdleScanState( this ), TURRETAI_HOLD, TURRETAI_HOLD );
	defineState( TURRETAI_AIM, new TurretAIAimTurretState( this ), TURRETAI_FIRE, TURRETAI_HOLD );
	defineState( TURRETAI_FIRE, new Rva0033F483( this, (int)static_cast<TurretAIAttackInterface *>(tai) ), TURRETAI_AIM, TURRETAI_AIM, fireConditions );
	defineState( TURRETAI_RECENTER, new TurretAIRecenterTurretState( this ), TURRETAI_IDLE, TURRETAI_IDLE );
	defineState( TURRETAI_HOLD, new TurretAIHoldTurretState( this ), TURRETAI_RECENTER, TURRETAI_RECENTER );
}
