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
// 0x00811C30 / 0x00343838), AttackContesterStateMachine (0x0033FB84 /
// 0x00811BD0 / 0x00343756) and AIAttackMoveStateMachine (0x0034004C /
// 0x00811E58 / 0x0034C6EF; the getter 0x00340057 spells it
// "AIAttackMOveStateMachine"). The other owners stay address
// named. Every class declares only its destructor, like the views in the
// constructor units, so the vtable and deleting destructor copies agree.
// AttackPositionStateMachine (0x0033FBA6), AIAttackSwoopThenIdleStateMachine
// (0x003677B3) and BackAwayAndCowerStateMachine (0x003402D0) define theirs in
// their constructor units.

class StateMachine
{
public:
	virtual ~StateMachine();
};

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

class Rva0048898C : public StateMachine
{
public:
	virtual ~Rva0048898C();
};

Rva0048898C::~Rva0048898C()
{
}

// Rva0048898C is DozerPrimaryStateMachine: its vtable 0x0084B668 holds
// ?GetSnapshotName@DozerPrimaryStateMachine (0x00488997) in slot 2.
#pragma comment(linker, "/alternatename:??1DozerPrimaryStateMachine@@UAE@XZ=??1Rva0048898C@@UAE@XZ")

class SupplyTruckStateMachine : public StateMachine
{
public:
	virtual ~SupplyTruckStateMachine();
};

SupplyTruckStateMachine::~SupplyTruckStateMachine()
{
}

class Rva004A9964 : public StateMachine
{
public:
	virtual ~Rva004A9964();
};

Rva004A9964::~Rva004A9964()
{
}

// Rva004A9964 is WorkerStateMachine: its vtable 0x00854058 holds
// ?GetSnapshotName@WorkerStateMachine (0x004A996F) in slot 2.
#pragma comment(linker, "/alternatename:??1WorkerStateMachine@@UAE@XZ=??1Rva004A9964@@UAE@XZ")

class TurretStateMachine : public StateMachine
{
public:
	virtual ~TurretStateMachine();
};

TurretStateMachine::~TurretStateMachine()
{
}

class AIGuardMachine : public StateMachine
{
public:
	virtual ~AIGuardMachine();
};

AIGuardMachine::~AIGuardMachine()
{
}

class AIDockMachine : public StateMachine
{
public:
	virtual ~AIDockMachine();
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
};

AIGuardRetaliateMachine::~AIGuardRetaliateMachine()
{
}

class AITNGuardMachine : public StateMachine
{
public:
	virtual ~AITNGuardMachine();
};

AITNGuardMachine::~AITNGuardMachine()
{
}
