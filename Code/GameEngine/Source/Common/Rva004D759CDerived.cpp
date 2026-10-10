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
// (0x004D7E61 / 0x008609C8 / 0x004D7CE6) and SupplyTruckStateMachine
// (0x004A6C59 / 0x008532A8 / 0x004A7010). The other owners stay address
// named. Every class declares only its destructor, like the views in the
// constructor units, so the vtable and deleting destructor copies agree.

class StateMachine
{
public:
	virtual ~StateMachine();
};

class Rva0033FAE9 : public StateMachine
{
public:
	virtual ~Rva0033FAE9();
};

Rva0033FAE9::~Rva0033FAE9()
{
}

class Rva0033FAFA : public StateMachine
{
public:
	virtual ~Rva0033FAFA();
};

Rva0033FAFA::~Rva0033FAFA()
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

class Rva0033FB84 : public StateMachine
{
public:
	virtual ~Rva0033FB84();
};

Rva0033FB84::~Rva0033FB84()
{
}

class Rva0033FB95 : public StateMachine
{
public:
	virtual ~Rva0033FB95();
};

Rva0033FB95::~Rva0033FB95()
{
}

class Rva0033FBA6 : public StateMachine
{
public:
	virtual ~Rva0033FBA6();
};

Rva0033FBA6::~Rva0033FBA6()
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

class Rva0034004C : public StateMachine
{
public:
	virtual ~Rva0034004C();
};

Rva0034004C::~Rva0034004C()
{
}

class Rva003402D0 : public StateMachine
{
public:
	virtual ~Rva003402D0();
};

Rva003402D0::~Rva003402D0()
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

class Rva003677B3 : public StateMachine
{
public:
	virtual ~Rva003677B3();
};

Rva003677B3::~Rva003677B3()
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
