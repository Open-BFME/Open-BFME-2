// cl: /O1 /DNDEBUG /MD /EHsc
//
// Zero Hour's SupplyTruckStateMachine (GeneralsMD GameLogic/Object/Update/
// AIUpdate/SupplyTruckAIUpdate.cpp): the machine's constructor, the two
// forced-state conditions and the docking state's onEnter.
//
// Target evidence. The ctor 0x004A7010 is pinned from its one caller, the
// matched SupplyTruckAIUpdate ctor 0x004A71A1 (news 0x3C, calls it on
// getObject()); its name key 0xF95C8C34 goes to the scalar-key spelling of
// the rowed StateMachine base ctor 0x004D79E1, and it installs vtable
// 0x008532A8, whose slot 2 0x004A6C64 returns "SupplyTruckStateMachine".
// It news six 0x20-byte states through their rowed ctors and defines them
// with ids 1,0,2,3,4,5. The condition tables sit in .rdata at 0x00853300
// (states 4 and 5), 0x00853330 (states 1 and 3), 0x00853360 (state 2) and
// 0x00853390 (state 0); their entries name the rowed owner* conditions and
// the two forced-state tests rowed here (0x004A6CC2 in 0x00853300 and
// 0x00853390, 0x004A6C92 in 0x00853390). The DockingState onEnter
// 0x004A6C6A is vtable slot 4 of both 0x00852E38 (state 4) and 0x00852E90
// (state 5). AI interface slot 95 (+0x17C) is getSupplyTruckAIInterface;
// SupplyTruckAIUpdate's interface vtable 0x00852F38 holds a byte setter at
// +0x2C and byte getters at +0x30 and +0x38.
//
// Donor-carried: the names, the state ids (ST_IDLE 0 .. ST_DOCKING 4), the
// condition tables' roles and the ZH bodies of the conditions and onEnter.
// BFME 2 adds a sixth state (id 5, ctor 0x004A699C) and a sixth condition
// (rowed ownerRva004A6D15) leading to it; its name is not asserted.
//
// Structural inference. Retail passes the address 0x00853330 for both the
// busy and the regrouping state, yet keeps 0x20 rather than that address in
// a register across the first five news. Only two distinct tables give that
// allocation (one shared table makes cl hold the address in edi instead), so
// the regrouping table is written as its own array with the busy table's
// entries; the identical pair shares one address in retail. The
// machine's dtor is the rowed 0x004A6C59 (11 bytes, vtable store and jmp to
// the base dtor) and is only declared here. State is a struct in this view
// because the rowed defineState is spelled with one.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class Object;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

typedef UnsignedInt StateID;

enum
{
	ST_IDLE = 0,
	ST_BUSY,
	ST_WANTING,
	ST_REGROUPING,
	ST_DOCKING,
	ST_RVA004A699C
};

class SupplyTruckAIInterface
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10();
	virtual void setForceWantingState(Bool v); // +0x2C
	virtual Bool isForcedIntoWantingState() const; // +0x30
	virtual void setForceBusyState(Bool v); // +0x34
	virtual Bool isForcedIntoBusyState() const; // +0x38
};

class AIUpdateInterface
{
public:
	virtual void v000(); virtual void v001(); virtual void v002(); virtual void v003();
	virtual void v004(); virtual void v005(); virtual void v006(); virtual void v007();
	virtual void v008(); virtual void v009(); virtual void v010(); virtual void v011();
	virtual void v012(); virtual void v013(); virtual void v014(); virtual void v015();
	virtual void v016(); virtual void v017(); virtual void v018(); virtual void v019();
	virtual void v020(); virtual void v021(); virtual void v022(); virtual void v023();
	virtual void v024(); virtual void v025(); virtual void v026(); virtual void v027();
	virtual void v028(); virtual void v029(); virtual void v030(); virtual void v031();
	virtual void v032(); virtual void v033(); virtual void v034(); virtual void v035();
	virtual void v036(); virtual void v037(); virtual void v038(); virtual void v039();
	virtual void v040(); virtual void v041(); virtual void v042(); virtual void v043();
	virtual void v044(); virtual void v045(); virtual void v046(); virtual void v047();
	virtual void v048(); virtual void v049(); virtual void v050(); virtual void v051();
	virtual void v052(); virtual void v053(); virtual void v054(); virtual void v055();
	virtual void v056(); virtual void v057(); virtual void v058(); virtual void v059();
	virtual void v060(); virtual void v061(); virtual void v062(); virtual void v063();
	virtual void v064(); virtual void v065(); virtual void v066(); virtual void v067();
	virtual void v068(); virtual void v069(); virtual void v070(); virtual void v071();
	virtual void v072(); virtual void v073(); virtual void v074(); virtual void v075();
	virtual void v076(); virtual void v077(); virtual void v078(); virtual void v079();
	virtual void v080(); virtual void v081(); virtual void v082(); virtual void v083();
	virtual void v084(); virtual void v085(); virtual void v086(); virtual void v087();
	virtual void v088(); virtual void v089(); virtual void v090(); virtual void v091();
	virtual void v092(); virtual void v093(); virtual void v094();
	virtual SupplyTruckAIInterface *getSupplyTruckAIInterface(); // slot 95 (+0x17C)
};

class Object
{
public:
	AIUpdateInterface *getAIUpdateInterface() { return m_ai; }
private:
	unsigned char m_pad000[0x258];
	AIUpdateInterface *m_ai; // +0x258
};

struct State;

struct StateConditionInfo
{
	Bool (*test)(State *thisState, void *userData);
	StateID toStateID;
	void *userData;
};

class StateMachine
{
public:
	virtual ~StateMachine();
	void defineState(StateID id, State *state, StateID successID, StateID failureID, const StateConditionInfo *conditions = 0);
	Object *getOwner() const { return m_owner; }
protected:
	unsigned char m_pad04[0x14 - 0x04];
	Object *m_owner; // +0x14
	unsigned char m_pad18[0x3C - 0x18]; // operator new size 0x3C
};

struct State
{
public:
	virtual ~State();
	Object *getMachineOwner() const { return m_machine->getOwner(); }
protected:
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
	unsigned char m_pad1C[0x20 - 0x1C];
};

// BFME 2's StateMachine constructor (owner, name key, flag), rowed by
// address as ??0Rva004D759C@@QAE@PAVObject@@VAsciiString@@_N@Z; the key is
// taken as one dword, as in the dozer and worker machines' TUs.
class Rva004D759C : public StateMachine
{
public:
	Rva004D759C(Object *owner, UnsignedInt nameKey, Bool flag);
	virtual ~Rva004D759C();
};

// ZH's SupplyTruckBusyState (rowed ctor 0x004A6BCA).
class Rva004A6BCA : public State
{
public:
	Rva004A6BCA(StateMachine *machine);
};

// ZH's SupplyTruckIdleState (rowed ctor 0x004A6C13).
class Rva004A6C13 : public State
{
public:
	Rva004A6C13(StateMachine *machine);
};

// ZH's SupplyTruckWantsToPickUpOrDeliverBoxesState (rowed ctor 0x004A6933).
class Rva004A6933 : public State
{
public:
	Rva004A6933(StateMachine *machine);
};

// ZH's RegroupingState (rowed ctor 0x004A6956).
class Rva004A6956 : public State
{
public:
	Rva004A6956(StateMachine *machine);
};

// ZH's DockingState (rowed ctor 0x004A6979).
class Rva004A6979 : public State
{
public:
	Rva004A6979(StateMachine *machine);
	virtual void s01(); virtual void s02(); virtual void s03();
	virtual StateReturnType onEnter(); // slot 4
};

// BFME 2's sixth supply truck state (rowed ctor 0x004A699C); it shares the
// docking state's onEnter.
class Rva004A699C : public State
{
public:
	Rva004A699C(StateMachine *machine);
};

class SupplyTruckStateMachine : public Rva004D759C
{
public:
	SupplyTruckStateMachine(Object *owner);
	virtual ~SupplyTruckStateMachine();

	static Bool ownerIdle(State *thisState, void *userData);
	static Bool ownerDocking(State *thisState, void *userData);
	static Bool ownerRva004A6D15(State *thisState, void *userData);
	static Bool ownerAvailableForSupplying(State *thisState, void *userData);
	static Bool ownerNotDockingOrIdle(State *thisState, void *userData);
	static Bool isForcedIntoWantingState(State *thisState, void *userData);
	static Bool isForcedIntoBusyState(State *thisState, void *userData);
};

StateReturnType Rva004A6979::onEnter()
{
	Object *owner = getMachineOwner();
	SupplyTruckAIInterface *update = owner->getAIUpdateInterface()->getSupplyTruckAIInterface();
	if (!update)
	{
		return STATE_FAILURE;
	}

	// after we dock the first time, we clear this, and then follow our normal state machine path
	update->setForceWantingState(false);

	return STATE_CONTINUE;
}

SupplyTruckStateMachine::SupplyTruckStateMachine(Object *owner) : Rva004D759C(owner, 0xF95C8C34, false)
{
	static const StateConditionInfo busyConditions[] =
	{
		{ ownerIdle, ST_IDLE, 0 },
		{ ownerDocking, ST_DOCKING, 0 },
		{ ownerRva004A6D15, ST_RVA004A699C, 0 },
		{ 0, 0, 0 } // keep last
	};

	static const StateConditionInfo idleConditions[] =
	{
		{ isForcedIntoBusyState, ST_BUSY, 0 },
		{ isForcedIntoWantingState, ST_WANTING, 0 },
		{ ownerDocking, ST_DOCKING, 0 },
		{ ownerRva004A6D15, ST_RVA004A699C, 0 },
		{ ownerNotDockingOrIdle, ST_BUSY, 0 },
		{ 0, 0, 0 } // keep last
	};

	static const StateConditionInfo wantingConditions[] =
	{
		{ ownerDocking, ST_DOCKING, 0 },
		{ ownerRva004A6D15, ST_RVA004A699C, 0 },
		{ ownerNotDockingOrIdle, ST_BUSY, 0 },
		{ 0, 0, 0 } // keep last
	};

	static const StateConditionInfo regroupingConditions[] =
	{
		{ ownerIdle, ST_IDLE, 0 },
		{ ownerDocking, ST_DOCKING, 0 },
		{ ownerRva004A6D15, ST_RVA004A699C, 0 },
		{ 0, 0, 0 } // keep last
	};

	static const StateConditionInfo dockingConditions[] =
	{
		{ isForcedIntoBusyState, ST_BUSY, 0 },
		{ ownerAvailableForSupplying, ST_WANTING, 0 },
		{ ownerNotDockingOrIdle, ST_BUSY, 0 },
		{ 0, 0, 0 } // keep last
	};

	// order matters: first state is the default state.
	defineState(ST_BUSY, new Rva004A6BCA(this), ST_BUSY, ST_BUSY, busyConditions);
	defineState(ST_IDLE, new Rva004A6C13(this), ST_BUSY, ST_BUSY, idleConditions);
	defineState(ST_WANTING, new Rva004A6933(this), ST_BUSY, ST_REGROUPING, wantingConditions);
	defineState(ST_REGROUPING, new Rva004A6956(this), ST_WANTING, ST_BUSY, regroupingConditions);
	defineState(ST_DOCKING, new Rva004A6979(this), ST_BUSY, ST_BUSY, dockingConditions);
	defineState(ST_RVA004A699C, new Rva004A699C(this), ST_BUSY, ST_BUSY, dockingConditions);
}

Bool SupplyTruckStateMachine::isForcedIntoWantingState(State *thisState, void *userData)
{
	Object *owner = thisState->getMachineOwner();
	AIUpdateInterface *ai = owner->getAIUpdateInterface();
	if (!ai)
		return false;
	SupplyTruckAIInterface *update = ai->getSupplyTruckAIInterface();
	if (!update)
		return false;

	if (update->isForcedIntoWantingState())
	{
		return true;
	}

	return false;
}

Bool SupplyTruckStateMachine::isForcedIntoBusyState(State *thisState, void *userData)
{
	Object *owner = thisState->getMachineOwner();
	AIUpdateInterface *ai = owner->getAIUpdateInterface();
	if (!ai)
		return false;
	SupplyTruckAIInterface *update = ai->getSupplyTruckAIInterface();
	if (!update)
		return false;

	if (update->isForcedIntoBusyState())
	{
		return true;
	}

	return false;
}
