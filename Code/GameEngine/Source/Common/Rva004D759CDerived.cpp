// cl: /MD
//
// Opaque single-inheritance destructors tail-calling
// StateMachine::~StateMachine at 0x004D759C (rowed in StateMachineDtor.cpp).
// Each class below stores its own vtable and tail-calls the base destructor;
// the base itself is only declared here, because a same-TU definition would
// capture the call locally instead of at the ledger address. One ledger row
// per destructor.
//
// Named owners (target facts): each destructor stores the vtable its rowed
// constructor installs, that vtable's slot 0 is the deleting destructor
// rowed here (which calls this destructor) and its slot 2 returns the class
// name string -- AIGuardMachine (dtor 0x00542C19 / vtable 0x00869680 / ctor
// 0x00543163), AIDockMachine (0x005440BC / 0x008699A0 / 0x005448A1),
// AIGuardRetaliateMachine (0x00545211 / 0x00869E78 / 0x0054551F),
// AITNGuardMachine (0x00545B84 / 0x0086A090 / 0x00546001), TurretStateMachine
// (0x004D7E61 / 0x008609C8 / 0x004D7CE6), SupplyTruckStateMachine
// (0x004A6C59 / 0x008532A8 / 0x004A7010), AttackStateMachine (0x0033FAE9 /
// 0x00811A68 / 0x00346D17), AttackMeleeStateMachine (0x0033FAFA /
// 0x00811AC0 / 0x0034316A), AttackFireWhileChargingMachine (0x0033FB95 /
// 0x00811C30 / 0x00343838), BackAwayAndCowerStateMachine (0x003402D0 /
// 0x00811FE8 / 0x003444CE), AttackContesterStateMachine (0x0033FB84 /
// 0x00811BD0 / 0x00343756) and AIAttackMoveStateMachine (0x0034004C /
// 0x00811E58 / 0x0034C6EF; the getter 0x00340057 spells it
// "AIAttackMOveStateMachine"). The other owners stay address
// named. Every class declares only its destructor, like the views in the
// constructor units, so the vtable and deleting destructor copies agree.
// AttackPositionStateMachine (0x0033FBA6), AIAttackSwoopThenIdleStateMachine
// (0x003677B3), DozerPrimaryStateMachine (0x0048898C) and WorkerStateMachine
// (0x004A9964) define theirs in their constructor units, and so does
// BackAwayAndCowerStateMachine (Rva003444CEStates.cpp), whose constructor
// calls the virtual StateMachine::setGoalObject and so carries a longer
// view of the vtable.

#include "../../Include/Common/StateMachineClass.h"

class AttackStateMachine : public StateMachine
{
public:
	virtual ~AttackStateMachine();
};

AttackStateMachine::~AttackStateMachine()
{
}

class AttackMeleeStateMachine : public StateMachine
{
public:
	virtual ~AttackMeleeStateMachine();
};

AttackMeleeStateMachine::~AttackMeleeStateMachine()
{
}

class Rva0033FB73 : public StateMachine
{
public:
	virtual ~Rva0033FB73();
};

Rva0033FB73::~Rva0033FB73()
{
}

class AttackContesterStateMachine : public StateMachine
{
public:
	virtual ~AttackContesterStateMachine();
};

AttackContesterStateMachine::~AttackContesterStateMachine()
{
}

class AttackFireWhileChargingMachine : public StateMachine
{
public:
	virtual ~AttackFireWhileChargingMachine();
};

AttackFireWhileChargingMachine::~AttackFireWhileChargingMachine()
{
}

class Rva0033FC0A : public StateMachine
{
public:
	virtual ~Rva0033FC0A();
};

Rva0033FC0A::~Rva0033FC0A()
{
}

class AIAttackMoveStateMachine : public StateMachine
{
public:
	virtual ~AIAttackMoveStateMachine();
};

AIAttackMoveStateMachine::~AIAttackMoveStateMachine()
{
}

class Rva0034144B : public StateMachine
{
public:
	virtual ~Rva0034144B();
};

Rva0034144B::~Rva0034144B()
{
}

class SupplyTruckStateMachine : public StateMachine
{
public:
	virtual ~SupplyTruckStateMachine();
};

SupplyTruckStateMachine::~SupplyTruckStateMachine()
{
}

class TurretStateMachine : public StateMachine
{
public:
	virtual ~TurretStateMachine();
public:
	// retail vftable slot: the rowed override
	virtual StateReturnType resetToDefaultState();
public:
	// retail vftable slot: the rowed override
	virtual StateReturnType setState(unsigned int);
public:
	// retail vftable slot: the rowed override
	virtual void clear();
};

TurretStateMachine::~TurretStateMachine()
{
}

class AIGuardMachine : public StateMachine
{
public:
	virtual ~AIGuardMachine();
protected:
	// retail vftable slot: the rowed override
	virtual void xfer(Xfer *);
protected:
	virtual const char *GetSnapshotName() const;	// primary slot 2: retail 0x00542C24
};

AIGuardMachine::~AIGuardMachine()
{
}

class AIDockMachine : public StateMachine
{
public:
	virtual ~AIDockMachine();
protected:
	// retail vftable slot: the rowed override
	virtual void xfer(Xfer *);
};

AIDockMachine::~AIDockMachine()
{
}

class Rva00544C51 : public StateMachine
{
public:
	virtual ~Rva00544C51();
};

Rva00544C51::~Rva00544C51()
{
}

class AIGuardRetaliateMachine : public StateMachine
{
public:
	virtual ~AIGuardRetaliateMachine();
protected:
	// retail vftable slot: the rowed override
	virtual void xfer(Xfer *);
};

AIGuardRetaliateMachine::~AIGuardRetaliateMachine()
{
}

class AITNGuardMachine : public StateMachine
{
public:
	virtual ~AITNGuardMachine();
protected:
	// retail vftable slot: the rowed override
	virtual void xfer(Xfer *);
};

AITNGuardMachine::~AITNGuardMachine()
{
}
