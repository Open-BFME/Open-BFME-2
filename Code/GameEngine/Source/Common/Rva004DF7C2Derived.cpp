// cl: /O1 /MD
//
// Opaque multiple-inheritance destructors tail-calling Rva004DF7C2::~
// Rva004DF7C2 at 0x004DF7C2 (pinned opaque MI base; identity unproven). Each
// class below derives (in order) from the opaque base, a shared empty
// polymorphic base, and its own empty polymorphic base, giving vptrs at
// +0x00/+0x0C/+0x10; the empty bases have implicit trivial destructors, so
// the derived destructor stores all three vptrs and tail-calls the base
// destructor. The +0x0C secondary is shared across the family (0xBEFF90).
// Owner identities are unproven (opaque Rva names). One ledger row per
// destructor, landed one commit at a time.

class Rva004DF7C2
{
public:
	virtual ~Rva004DF7C2();

private:
	char m_pad04[8];
};

class MiBase1
{
public:
	virtual void f1();
};

// ?f1@MiBase1@@UAEXXZ present-unmatched
void MiBase1::f1() {}

class Rva004DF52E_B2
{
public:
	virtual void f2();
};

// ?f2@Rva004DF52E_B2@@UAEXXZ present-unmatched
void Rva004DF52E_B2::f2() {}

class Rva004DF52E : public Rva004DF7C2, public MiBase1, public Rva004DF52E_B2
{
public:
	virtual ~Rva004DF52E();
};

Rva004DF52E::~Rva004DF52E()
{
}

class Rva004DF836_B2
{
public:
	virtual void f2();
};

// ?f2@Rva004DF836_B2@@UAEXXZ present-unmatched
void Rva004DF836_B2::f2() {}

class Rva004DF836 : public Rva004DF7C2, public MiBase1, public Rva004DF836_B2
{
public:
	virtual ~Rva004DF836();
};

Rva004DF836::~Rva004DF836()
{
}

class Rva004DF863_B2
{
public:
	virtual void f2();
};

// ?f2@Rva004DF863_B2@@UAEXXZ present-unmatched
void Rva004DF863_B2::f2() {}

class Rva004DF863 : public Rva004DF7C2, public MiBase1, public Rva004DF863_B2
{
public:
	virtual ~Rva004DF863();
};

Rva004DF863::~Rva004DF863()
{
}

class Rva004DF8A9_B2
{
public:
	virtual void f2();
};

// ?f2@Rva004DF8A9_B2@@UAEXXZ present-unmatched
void Rva004DF8A9_B2::f2() {}

class Rva004DF8A9 : public Rva004DF7C2, public MiBase1, public Rva004DF8A9_B2
{
public:
	virtual ~Rva004DF8A9();
};

Rva004DF8A9::~Rva004DF8A9()
{
}
