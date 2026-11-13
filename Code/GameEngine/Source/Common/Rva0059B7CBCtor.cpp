// cl: /GX-
//
// Retail RVA 0x0059B7CB, Ghidra boundary 25 bytes. It installs vtable
// VA 0x00C70EBC and copies two four-byte arguments to +4 and +8, returning
// this with ret 8. The vtable's slot 0 reaches the shared deleting body
// at 0x004A10FD; that folded body does not identify this class's owner.
// The class, argument types and field meanings remain unknown. In
// particular this is not Gdiplus::Image, whose vtable is VA 0x00BBB524.

#include <new.h>

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
	// Slot 0 is the rowed 0x0035A97E (GapBodiesS3D.cpp).
	virtual void slot00(int cellX, int cellY);
private:
	unsigned int m_field04;
	unsigned int m_field08;
};

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline Rva00359853::Rva00359853(unsigned int field04, unsigned int field08)
{
	m_field04 = field04;
	m_field08 = field08;
}

// ?bfmeAnchorRva00359853 absent-from-retail
void *bfmeAnchorRva00359853(void *where, unsigned int a, unsigned int b)
{
	return new (where) Rva00359853(a, b);
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


// 0x004E7AF3 (VA 0xc625a8): one more of the shape above, found by its
// identical instruction skeleton (only the vtable immediate differs).
class Rva004E7AF3
{
public:
	Rva004E7AF3(unsigned int field04, unsigned int field08);
	virtual void slot00() {}
private:
	unsigned int m_field04;
	unsigned int m_field08;
};

Rva004E7AF3::Rva004E7AF3(unsigned int field04, unsigned int field08)
{
	m_field04 = field04;
	m_field08 = field08;
}

// Three more of this shape, out-of-line copies with their own vtables:
// 0x0029B32D (VA 0xbfd010), 0x002B25D6 (VA 0xbfdfec), 0x002B262D (VA 0xbfdff0).
// Same select-any recipe as Rva00359853 above; class names address-derived.

class Rva0029B32D
{
public:
	Rva0029B32D(unsigned int field04, unsigned int field08);
	virtual void slot00() {}
private:
	unsigned int m_field04;
	unsigned int m_field08;
};

__declspec(noinline) inline Rva0029B32D::Rva0029B32D(unsigned int field04, unsigned int field08)
{
	m_field04 = field04;
	m_field08 = field08;
}

// ?bfmeAnchorRva0029B32D absent-from-retail
void *bfmeAnchorRva0029B32D(void *where, unsigned int a, unsigned int b)
{
	return new (where) Rva0029B32D(a, b);
}

class Rva002B25D6
{
public:
	Rva002B25D6(unsigned int field04, unsigned int field08);
	virtual void slot00() {}
private:
	unsigned int m_field04;
	unsigned int m_field08;
};

__declspec(noinline) inline Rva002B25D6::Rva002B25D6(unsigned int field04, unsigned int field08)
{
	m_field04 = field04;
	m_field08 = field08;
}

// ?bfmeAnchorRva002B25D6 absent-from-retail
void *bfmeAnchorRva002B25D6(void *where, unsigned int a, unsigned int b)
{
	return new (where) Rva002B25D6(a, b);
}

class Rva002B262D
{
public:
	Rva002B262D(unsigned int field04, unsigned int field08);
	virtual void slot00() {}
private:
	unsigned int m_field04;
	unsigned int m_field08;
};

__declspec(noinline) inline Rva002B262D::Rva002B262D(unsigned int field04, unsigned int field08)
{
	m_field04 = field04;
	m_field08 = field08;
}

// ?bfmeAnchorRva002B262D absent-from-retail
void *bfmeAnchorRva002B262D(void *where, unsigned int a, unsigned int b)
{
	return new (where) Rva002B262D(a, b);
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?slot00@Rva0059B7CB@@UAEXXZ=??_GObjectModule@@UAEPAXI@Z")
