// cl: /MD
//
// Opaque multiple-inheritance destructors tail-calling DieModule::~DieModule
// at 0x0045CE54. Each class below derives (in order) from DieModule, a shared
// empty polymorphic base, and its own empty polymorphic base, giving vptrs at
// +0x00/+0x0C/+0x10; the empty bases have implicit trivial destructors (no
// code, no calls), so the derived destructor stores all three vptrs and
// tail-calls the DieModule destructor. The +0x0C secondary is shared across
// the family (none of them override the shared base), the other two are
// per-class. Owner identities are unproven (opaque Rva names). One ledger row
// per destructor, landed one commit at a time.

class DieModule
{
protected:
	virtual ~DieModule();

private:
	char m_pad04[8];
};

class MiBase1
{
public:
	virtual void f1();
};

class Rva0045CE6D_B2
{
public:
	virtual void f2();
};

class Rva0045CE6D : public DieModule, public MiBase1, public Rva0045CE6D_B2
{
public:
	virtual ~Rva0045CE6D();
};

Rva0045CE6D::~Rva0045CE6D()
{
}

class Rva004851FE_B2
{
public:
	virtual void f2();
};

class Rva004851FE : public DieModule, public MiBase1, public Rva004851FE_B2
{
public:
	virtual ~Rva004851FE();
};

Rva004851FE::~Rva004851FE()
{
}

class Rva00485425_B2
{
public:
	virtual void f2();
};

class Rva00485425 : public DieModule, public MiBase1, public Rva00485425_B2
{
public:
	virtual ~Rva00485425();
};

Rva00485425::~Rva00485425()
{
}

class Rva0048593D_B2
{
public:
	virtual void f2();
};

class Rva0048593D : public DieModule, public MiBase1, public Rva0048593D_B2
{
public:
	virtual ~Rva0048593D();
};

Rva0048593D::~Rva0048593D()
{
}

class Rva00486136_B2
{
public:
	virtual void f2();
};

class Rva00486136 : public DieModule, public MiBase1, public Rva00486136_B2
{
public:
	virtual ~Rva00486136();
};

Rva00486136::~Rva00486136()
{
}

class Rva004864AA_B2
{
public:
	virtual void f2();
};

class Rva004864AA : public DieModule, public MiBase1, public Rva004864AA_B2
{
public:
	virtual ~Rva004864AA();
};

Rva004864AA::~Rva004864AA()
{
}

class Rva00486579_B2
{
public:
	virtual void f2();
};

class Rva00486579 : public DieModule, public MiBase1, public Rva00486579_B2
{
public:
	virtual ~Rva00486579();
};

Rva00486579::~Rva00486579()
{
}

class Rva004869FC_B2
{
public:
	virtual void f2();
};

class Rva004869FC : public DieModule, public MiBase1, public Rva004869FC_B2
{
public:
	virtual ~Rva004869FC();
};

Rva004869FC::~Rva004869FC()
{
}

class Rva00486B56_B2
{
public:
	virtual void f2();
};

class Rva00486B56 : public DieModule, public MiBase1, public Rva00486B56_B2
{
public:
	virtual ~Rva00486B56();
};

Rva00486B56::~Rva00486B56()
{
}

class Rva00486C76_B2
{
public:
	virtual void f2();
};

class Rva00486C76 : public DieModule, public MiBase1, public Rva00486C76_B2
{
public:
	virtual ~Rva00486C76();
};

Rva00486C76::~Rva00486C76()
{
}

class Rva004C227A_B2
{
public:
	virtual void f2();
};

class Rva004C227A : public DieModule, public MiBase1, public Rva004C227A_B2
{
public:
	virtual ~Rva004C227A();
};

Rva004C227A::~Rva004C227A()
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?f2@Rva004869FC_B2@@UAEXXZ=?onDie@SpecialPowerCompletionDie@@UAEXPBVDamageInfo@@@Z")
