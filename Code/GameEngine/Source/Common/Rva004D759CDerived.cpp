// cl: /MD
//
// Opaque single-inheritance destructors tail-calling
// StateMachine::~StateMachine at 0x004D759C (rowed in StateMachineDtor.cpp).
// Each class below stores its own vtable and tail-calls the base destructor;
// the base itself is only declared here, because a same-TU definition would
// capture the call locally instead of at the ledger address. Owner
// identities are unproven (opaque Rva names). One ledger row per destructor.

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

class Rva004A6C59 : public StateMachine
{
public:
	virtual ~Rva004A6C59();
};

Rva004A6C59::~Rva004A6C59()
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

class Rva004D7E61 : public StateMachine
{
public:
	virtual ~Rva004D7E61();
};

Rva004D7E61::~Rva004D7E61()
{
}

class Rva00542C19 : public StateMachine
{
public:
	virtual ~Rva00542C19();
};

Rva00542C19::~Rva00542C19()
{
}

class Rva005440BC : public StateMachine
{
public:
	virtual ~Rva005440BC();
};

Rva005440BC::~Rva005440BC()
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

class Rva00545211 : public StateMachine
{
public:
	virtual ~Rva00545211();
};

Rva00545211::~Rva00545211()
{
}

class Rva00545B84 : public StateMachine
{
public:
	virtual ~Rva00545B84();
};

Rva00545B84::~Rva00545B84()
{
}
