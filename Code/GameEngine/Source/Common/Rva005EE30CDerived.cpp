// cl: /O1 /MD
//
// Opaque destructors deriving from Rva005EE30C (whose row at 0x005EE30C
// resolves the tail calls). Each class below stores its own vtable and
// tail-calls the base destructor; the base itself is only declared here and
// defined once in Rva005EE30CChain.cpp, because a same-TU definition would
// capture the call locally instead of at the ledger address. Owner
// identities are unproven (opaque Rva names). One ledger row per destructor,
// landed one commit at a time.

class Rva005EE30C
{
public:
	Rva005EE30C();
	virtual ~Rva005EE30C();
};

class Rva005D736E : public Rva005EE30C
{
public:
	Rva005D736E();
	virtual ~Rva005D736E();
};

// ??0Rva005D736E@@QAE@XZ, retail 0x005D735C (18B): calls the rowed base
// constructor 0x005EE2E6 and stores vtable 0x00C75CEC, the one the
// destructor below restores, so it is this class's constructor.
Rva005D736E::Rva005D736E()
{
}

Rva005D736E::~Rva005D736E()
{
}

class Rva005D7706 : public Rva005EE30C
{
public:
	virtual ~Rva005D7706();
};

Rva005D7706::~Rva005D7706()
{
}

class Rva005D7855 : public Rva005EE30C
{
public:
	virtual ~Rva005D7855();
};

Rva005D7855::~Rva005D7855()
{
}

class Rva005D7A1B : public Rva005EE30C
{
public:
	virtual ~Rva005D7A1B();
};

Rva005D7A1B::~Rva005D7A1B()
{
}

class Rva005D7AC5 : public Rva005EE30C
{
public:
	Rva005D7AC5();
	virtual ~Rva005D7AC5();
};

// ??0Rva005D7AC5@@QAE@XZ, retail 0x005D7AB3 (18B): base constructor
// 0x005EE2E6 then vtable 0x00C75E44, the one this class's destructor
// restores.
Rva005D7AC5::Rva005D7AC5()
{
}

Rva005D7AC5::~Rva005D7AC5()
{
}

class Rva005D7B3E : public Rva005EE30C
{
public:
	virtual ~Rva005D7B3E();
};

Rva005D7B3E::~Rva005D7B3E()
{
}

class Rva005D7D88 : public Rva005EE30C
{
public:
	virtual ~Rva005D7D88();
};

Rva005D7D88::~Rva005D7D88()
{
}

class Rva005D7E1E : public Rva005EE30C
{
public:
	virtual ~Rva005D7E1E();
};

Rva005D7E1E::~Rva005D7E1E()
{
}

class Rva005D817D : public Rva005EE30C
{
public:
	virtual ~Rva005D817D();
};

Rva005D817D::~Rva005D817D()
{
}

class Rva005D8223 : public Rva005EE30C
{
public:
	virtual ~Rva005D8223();
};

Rva005D8223::~Rva005D8223()
{
}

class Rva005D8317 : public Rva005EE30C
{
public:
	virtual ~Rva005D8317();
};

inline Rva005D8317::~Rva005D8317()
{
}

class Rva005D84F6 : public Rva005EE30C
{
public:
	virtual ~Rva005D84F6();
};

Rva005D84F6::~Rva005D84F6()
{
}

class Rva005D86E6 : public Rva005EE30C
{
public:
	virtual ~Rva005D86E6();
};

Rva005D86E6::~Rva005D86E6()
{
}

class Rva005D8AE4 : public Rva005EE30C
{
public:
	virtual ~Rva005D8AE4();
};

Rva005D8AE4::~Rva005D8AE4()
{
}

class Rva005D8C25 : public Rva005EE30C
{
public:
	virtual ~Rva005D8C25();
};

Rva005D8C25::~Rva005D8C25()
{
}

class Rva005D8EE8 : public Rva005EE30C
{
public:
	virtual ~Rva005D8EE8();
};

Rva005D8EE8::~Rva005D8EE8()
{
}

class Rva005D91AB : public Rva005EE30C
{
public:
	virtual ~Rva005D91AB();
};

Rva005D91AB::~Rva005D91AB()
{
}

class Rva005D944A : public Rva005EE30C
{
public:
	virtual ~Rva005D944A();
};

Rva005D944A::~Rva005D944A()
{
}

class Rva005D95A8 : public Rva005EE30C
{
public:
	virtual ~Rva005D95A8();
};

Rva005D95A8::~Rva005D95A8()
{
}

class Rva005D96FA : public Rva005EE30C
{
public:
	virtual ~Rva005D96FA();
};

Rva005D96FA::~Rva005D96FA()
{
}

class Rva005D9C6C : public Rva005EE30C
{
public:
	virtual ~Rva005D9C6C();
};

Rva005D9C6C::~Rva005D9C6C()
{
}

class Rva005D9CD5 : public Rva005EE30C
{
public:
	virtual ~Rva005D9CD5();
};

Rva005D9CD5::~Rva005D9CD5()
{
}

#pragma inline_depth(0)
// ?bfmeEmitRva005EE30CDerived@@YAXPAVRva005D8317@@@Z present-unmatched
void bfmeEmitRva005EE30CDerived(Rva005D8317 *p)
{
	p->Rva005D8317::~Rva005D8317();
}
#pragma inline_depth()
