// cl: /GX-
//
// Retail RVA 0x0059B7CB, Ghidra boundary 25 bytes. It installs vtable
// VA 0x00C70EBC and copies two four-byte arguments to +4 and +8, returning
// this with ret 8. The vtable's slot 0 reaches the shared deleting body
// at 0x004A10FD; that folded body does not identify this class's owner.
// The class, argument types and field meanings remain unknown. In
// particular this is not Gdiplus::Image, whose vtable is VA 0x00BBB524.

class Rva0059B7CB
{
public:
	Rva0059B7CB(unsigned int field04, unsigned int field08);
	virtual void slot00();

private:
	unsigned int m_field04;
	unsigned int m_field08;
};

Rva0059B7CB::Rva0059B7CB(unsigned int field04, unsigned int field08)
{
	m_field04 = field04;
	m_field08 = field08;
}

// Four more constructors of this shape, each installing its own vtable (the only
// differing operand): 0x00359853 (VA 0xc153d4), 0x00431A34 (VA 0xc3c9ac), 0x004E9FFD (VA 0xc62888), 0x00567847 (VA 0xc6ced8). The virtual is declared inline and
// empty so the vtable the compiler emits resolves in this unit. Owners keep
// their addresses.

class Rva00359853
{
public:
	Rva00359853(unsigned int field04, unsigned int field08);
	virtual void slot00() {}
private:
	unsigned int m_field04;
	unsigned int m_field08;
};

Rva00359853::Rva00359853(unsigned int field04, unsigned int field08)
{
	m_field04 = field04;
	m_field08 = field08;
}

class Rva00431A34
{
public:
	Rva00431A34(unsigned int field04, unsigned int field08);
	virtual void slot00() {}
private:
	unsigned int m_field04;
	unsigned int m_field08;
};

Rva00431A34::Rva00431A34(unsigned int field04, unsigned int field08)
{
	m_field04 = field04;
	m_field08 = field08;
}

class Rva004E9FFD
{
public:
	Rva004E9FFD(unsigned int field04, unsigned int field08);
	virtual void slot00() {}
private:
	unsigned int m_field04;
	unsigned int m_field08;
};

Rva004E9FFD::Rva004E9FFD(unsigned int field04, unsigned int field08)
{
	m_field04 = field04;
	m_field08 = field08;
}

class Rva00567847
{
public:
	Rva00567847(unsigned int field04, unsigned int field08);
	virtual void slot00() {}
private:
	unsigned int m_field04;
	unsigned int m_field08;
};

Rva00567847::Rva00567847(unsigned int field04, unsigned int field08)
{
	m_field04 = field04;
	m_field08 = field08;
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?slot00@Rva0059B7CB@@UAEXXZ=??_GObjectModule@@UAEPAXI@Z")
