// cl: /MD
//
// Opaque multiple-inheritance destructors tail-calling Rva00493DEF::~
// Rva00493DEF at 0x00493DEF (pinned opaque MI base: SEH, three vptrs
// including the shared 0xBEFCF8 secondary; identity unproven). Each class
// below derives (in order) from the opaque base, a shared empty polymorphic
// base, and its own empty polymorphic base, giving vptrs at +0x00/+0x0C/+0x10;
// the empty bases have implicit trivial destructors, so the derived
// destructor stores all three vptrs and tail-calls the base destructor. The
// +0x0C secondary is shared across the family (0xBEFCF8). Owner identities
// are unproven (opaque Rva names). One ledger row per destructor, landed one
// commit at a time.

class Rva00493DEF
{
public:
	virtual ~Rva00493DEF();

private:
	char m_pad04[8];
};

class MiBase1
{
public:
	virtual void f1();
};

class Rva004C2656_B2
{
public:
	virtual void f2();
};

class Rva004C2656 : public Rva00493DEF, public MiBase1, public Rva004C2656_B2
{
public:
	virtual ~Rva004C2656();
};

Rva004C2656::~Rva004C2656()
{
}

class Rva004C29BB_B2
{
public:
	virtual void f2();
};

class Rva004C29BB : public Rva00493DEF, public MiBase1, public Rva004C29BB_B2
{
public:
	virtual ~Rva004C29BB();
};

Rva004C29BB::~Rva004C29BB()
{
}

class Rva004C3108_B2
{
public:
	virtual void f2();
};

class Rva004C3108 : public Rva00493DEF, public MiBase1, public Rva004C3108_B2
{
public:
	virtual ~Rva004C3108();
};

Rva004C3108::~Rva004C3108()
{
}

class Rva004C3905_B2
{
public:
	virtual void f2();
};

class Rva004C3905 : public Rva00493DEF, public MiBase1, public Rva004C3905_B2
{
public:
	virtual ~Rva004C3905();
};

Rva004C3905::~Rva004C3905()
{
}

class Rva004C4044_B2
{
public:
	virtual void f2();
};

class Rva004C4044 : public Rva00493DEF, public MiBase1, public Rva004C4044_B2
{
public:
	virtual ~Rva004C4044();
};

Rva004C4044::~Rva004C4044()
{
}

class Rva004C43A3_B2
{
public:
	virtual void f2();
};

class Rva004C43A3 : public Rva00493DEF, public MiBase1, public Rva004C43A3_B2
{
public:
	virtual ~Rva004C43A3();
};

Rva004C43A3::~Rva004C43A3()
{
}

class Rva004C4508_B2
{
public:
	virtual void f2();
};

class Rva004C4508 : public Rva00493DEF, public MiBase1, public Rva004C4508_B2
{
public:
	virtual ~Rva004C4508();
};

Rva004C4508::~Rva004C4508()
{
}

class Rva004C48C6_B2
{
public:
	virtual void f2();
};

class Rva004C48C6 : public Rva00493DEF, public MiBase1, public Rva004C48C6_B2
{
public:
	virtual ~Rva004C48C6();
};

Rva004C48C6::~Rva004C48C6()
{
}

class Rva004C4BD1_B2
{
public:
	virtual void f2();
};

class Rva004C4BD1 : public Rva00493DEF, public MiBase1, public Rva004C4BD1_B2
{
public:
	virtual ~Rva004C4BD1();
};

Rva004C4BD1::~Rva004C4BD1()
{
}

class Rva004C4DE9_B2
{
public:
	virtual void f2();
};

class Rva004C4DE9 : public Rva00493DEF, public MiBase1, public Rva004C4DE9_B2
{
public:
	virtual ~Rva004C4DE9();
};

Rva004C4DE9::~Rva004C4DE9()
{
}

class Rva004C5019_B2
{
public:
	virtual void f2();
};

class Rva004C5019 : public Rva00493DEF, public MiBase1, public Rva004C5019_B2
{
public:
	virtual ~Rva004C5019();
};

Rva004C5019::~Rva004C5019()
{
}

class Rva004C67A0_B2
{
public:
	virtual void f2();
};

class Rva004C67A0 : public Rva00493DEF, public MiBase1, public Rva004C67A0_B2
{
public:
	virtual ~Rva004C67A0();
};

Rva004C67A0::~Rva004C67A0()
{
}

class Rva004C7B36_B2
{
public:
	virtual void f2();
};

class Rva004C7B36 : public Rva00493DEF, public MiBase1, public Rva004C7B36_B2
{
public:
	virtual ~Rva004C7B36();
};

Rva004C7B36::~Rva004C7B36()
{
}

class Rva004C7C33_B2
{
public:
	virtual void f2();
};

class Rva004C7C33 : public Rva00493DEF, public MiBase1, public Rva004C7C33_B2
{
public:
	virtual ~Rva004C7C33();
};

Rva004C7C33::~Rva004C7C33()
{
}

class Rva004C7EAE_B2
{
public:
	virtual void f2();
};

class Rva004C7EAE : public Rva00493DEF, public MiBase1, public Rva004C7EAE_B2
{
public:
	virtual ~Rva004C7EAE();
};

Rva004C7EAE::~Rva004C7EAE()
{
}

class Rva004C8213_B2
{
public:
	virtual void f2();
};

class Rva004C8213 : public Rva00493DEF, public MiBase1, public Rva004C8213_B2
{
public:
	virtual ~Rva004C8213();
};

Rva004C8213::~Rva004C8213()
{
}

class Rva004C85A4_B2
{
public:
	virtual void f2();
};

class Rva004C85A4 : public Rva00493DEF, public MiBase1, public Rva004C85A4_B2
{
public:
	virtual ~Rva004C85A4();
};

Rva004C85A4::~Rva004C85A4()
{
}

class Rva004C86E4_B2
{
public:
	virtual void f2();
};

class Rva004C86E4 : public Rva00493DEF, public MiBase1, public Rva004C86E4_B2
{
public:
	virtual ~Rva004C86E4();
};

Rva004C86E4::~Rva004C86E4()
{
}

class Rva004C87F4_B2
{
public:
	virtual void f2();
};

class Rva004C87F4 : public Rva00493DEF, public MiBase1, public Rva004C87F4_B2
{
public:
	virtual ~Rva004C87F4();
};

Rva004C87F4::~Rva004C87F4()
{
}

class Rva004C8A16_B2
{
public:
	virtual void f2();
};

class Rva004C8A16 : public Rva00493DEF, public MiBase1, public Rva004C8A16_B2
{
public:
	virtual ~Rva004C8A16();
};

Rva004C8A16::~Rva004C8A16()
{
}
