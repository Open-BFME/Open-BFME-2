// cl: /O1 /DNDEBUG /MD
//
// Copy constructors of tiny aggregate holders: each copies one word-array
// member from its single argument with rep movsd (push N / pop ecx
// size-opt count). The mov eax,ecx park plus ret 4 is the constructor's
// return-this, not a method body.
// 0x005E35B5: 8 dwords (32B). 0x005EEEFF: 5 dwords (20B).
// 0x005F8F00: 9 dwords (36B).

struct EightInts
{
	int v[8];
};
struct FiveInts
{
	int v[5];
};
struct NineInts
{
	int v[9];
};

class Rva005E35B5
{
public:
	Rva005E35B5(const Rva005E35B5 &o);
private:
	EightInts m_data;
};
Rva005E35B5::Rva005E35B5(const Rva005E35B5 &o)
{
	m_data = o.m_data;
}

class Rva005EEEFF
{
public:
	Rva005EEEFF(const Rva005EEEFF &o);
private:
	FiveInts m_data;
};
Rva005EEEFF::Rva005EEEFF(const Rva005EEEFF &o)
{
	m_data = o.m_data;
}

class Rva005F8F00
{
public:
	Rva005F8F00(const Rva005F8F00 &o);
private:
	NineInts m_data;
};
Rva005F8F00::Rva005F8F00(const Rva005F8F00 &o)
{
	m_data = o.m_data;
}
