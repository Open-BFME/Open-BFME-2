// cl: /O2 /DNDEBUG /MD
//
// Small vtable-slot bodies with no ledger owner and no Ghidra entry in the
// /O2 library range, batch AK: constants and field reads. Classes and
// methods are address-derived and model only what each body touches.

typedef int Int;

// 0x00661480 (four tables) and 0x006680D0 (two tables): answer 0 for one
// resp. three arguments.
class Rva00661480
{
public:
	Int rva00661480(Int a);
	Int rva006680D0(Int a, Int b, Int c);
};
Int Rva00661480::rva00661480(Int)
{
	return 0;
}
Int Rva00661480::rva006680D0(Int, Int, Int)
{
	return 0;
}

// 0x0066E4C0 and 0x0066E560: the 64-bit values at +0x10 resp. +0x18.
class Rva0066E4C0
{
public:
	__int64 rva0066E4C0() const;
	__int64 rva0066E560() const;
private:
	char m_pad00[0x10];
	__int64 m_10;
	__int64 m_18;
};
__int64 Rva0066E4C0::rva0066E4C0() const
{
	return m_10;
}
__int64 Rva0066E4C0::rva0066E560() const
{
	return m_18;
}

// 0x00709BC0 (two tables): the leading word of the +0x30 object.
class Rva00709BC0
{
public:
	Int rva00709BC0() const;
private:
	char m_pad00[0x30];
	Int *m_30;
};
Int Rva00709BC0::rva00709BC0() const
{
	return *m_30;
}

// Tail-jump slots over unrowed callees, pinned in reverse/symbols.csv under
// address-derived names (argument counts from each callee's ret).

class Rva00624130
{
public:
	void rva00624130();
};
class Rva0061EF80
{
public:
	void rva0061EF80();
private:
	char m_pad00[0x0C];
	Rva00624130 *m_0C;
};
void Rva0061EF80::rva0061EF80()
{
	m_0C->rva00624130();
}
