// cl: /MD
//
// Opaque multiple-inheritance destructors tail-calling Rva0026E836::~
// Rva0026E836 at 0x0026E836 (pinned opaque SEH base dtor: five vptrs at
// +0x00/+0x0C/+0x10/+0x20/+0x24 plus member cleanup; identity unproven). The
// middle is modelled here with its full five-vptr shape (root plus three
// secondaries, the +0x10 one carrying 12 bytes of opaque data so the layout
// reaches +0x20); each class below derives singly from it (inheriting the
// five-vptr layout) and overrides every vptr before tail-calling the base
// destructor. The middle itself is only declared here (defined nowhere --
// it resolves via the pin), because a same-TU definition would capture the
// call locally instead of at the ledger address. Vtable values are DIR32
// auto-patches. Owner identities are unproven (opaque Rva names). One ledger
// row per destructor, landed one commit at a time.

class Rva0026E836_Root
{
public:
	virtual ~Rva0026E836_Root();

private:
	char m_pad04[8];
};

class Rva0026E836_M1
{
public:
	virtual void f1();
};

class Rva0026E836_B2
{
public:
	virtual void f2();

private:
	char m_pad08[12];
};

class Rva0026E836_M3
{
public:
	virtual void f3();
};

class Rva0026E836_M4
{
public:
	virtual void f4();
};

class Rva0026E836 : public Rva0026E836_Root, public Rva0026E836_M1, public Rva0026E836_B2, public Rva0026E836_M3, public Rva0026E836_M4
{
public:
	virtual ~Rva0026E836();
};

class Rva00490544 : public Rva0026E836
{
public:
	virtual ~Rva00490544();
};

Rva00490544::~Rva00490544()
{
}

class Rva004A9080 : public Rva0026E836
{
public:
	virtual ~Rva004A9080();
};

Rva004A9080::~Rva004A9080()
{
}

class Rva004A935D : public Rva0026E836
{
public:
	virtual ~Rva004A935D();
};

Rva004A935D::~Rva004A935D()
{
}

class Rva0047EB78 : public Rva0026E836
{
public:
	virtual ~Rva0047EB78();

private:
	char m_pad0028[0x3E4 - 0x28];
	int m_extra03E4;
};

Rva0047EB78::~Rva0047EB78()
{
	m_extra03E4 = 0xC47B84;
}

class Rva0048F3E0 : public Rva0026E836
{
public:
	virtual ~Rva0048F3E0();

private:
	char m_pad0028[0x3E4 - 0x28];
	int m_extra03E4;
};

Rva0048F3E0::~Rva0048F3E0()
{
	m_extra03E4 = 0xC4CC88;
}

class Rva0049A64B : public Rva0026E836
{
public:
	virtual ~Rva0049A64B();

private:
	char m_pad0028[0x3E4 - 0x28];
	int m_extra03E4;
};

Rva0049A64B::~Rva0049A64B()
{
	m_extra03E4 = 0xC50868;
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?f1@Rva0026E836_M1@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
