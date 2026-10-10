// cl: /DNDEBUG /MD
//
// Six constant-return bodies found by tools/vtable_gaps.py: each is an
// UNNAMED slot of a vtable-shaped run that also carries named slots, so the
// only evidence that reaches them is the vtable -- they have no direct caller
// to name them and no Zero Hour counterpart to port.
//
// Identity is therefore not recoverable. Each keeps an address-derived class
// name: AGENTS.md allows an opaque address-token name (it is self-labelling and
// counted by progress.py) and prohibits a plausible guessed class, which no
// gate can see. The class exists to give the body the retail __thiscall
// convention -- `ret N` cleans the arguments, which a free __cdecl spelling
// would not reproduce. None of these classes has a virtual member, so no vtable
// is emitted and the TU adds no symbol the ledger lacks.
//
// Retail bodies:
//   0x0050B5C6   3B   b0 01 c3              mov al,1 ; ret
//   0x0050B5F1   5B   32 c0 c2 08 00        xor al,al ; ret 8
//   0x005CB9FF   5B   32 c0 c2 04 00        xor al,al ; ret 4
//   0x006C8770   5B   32 c0 c2 0c 00        xor al,al ; ret 0xc
//   0x005748AD   5B   33 c0 c2 0c 00        xor eax,eax ; ret 0xc
//   0x005748B2   5B   33 c0 c2 08 00        xor eax,eax ; ret 8

class Rva0050B5C6
{
public:
	bool rva0050B5C6();
};

bool Rva0050B5C6::rva0050B5C6()
{
	return true;
}

class Rva0050B5F1
{
public:
	bool rva0050B5F1(int a, int b);
};

bool Rva0050B5F1::rva0050B5F1(int a, int b)
{
	return false;
}

class Rva005CB9FF
{
public:
	bool rva005CB9FF(int a);
};

bool Rva005CB9FF::rva005CB9FF(int a)
{
	return false;
}

// The two below return Int rather than Bool -- `xor eax,eax`, not `xor al,al`.

class Rva005748AD
{
public:
	int rva005748AD(int a, int b, int c);
};

int Rva005748AD::rva005748AD(int a, int b, int c)
{
	return 0;
}

class Rva005748B2
{
public:
	int rva005748B2(int a, int b);
};

int Rva005748B2::rva005748B2(int a, int b)
{
	return 0;
}

// Installed-vtable constant result; original owner and parameter semantics
// remain unknown. RET 12 establishes native stack cleanup only.
class Rva0041BA5C {public: bool rva0041BA5C(int a0, int a1, int a2);};
bool Rva0041BA5C::rva0041BA5C(int a0, int a1, int a2) {return false;}

// Installed-vtable constant result; original owner and parameter semantics
// remain unknown. RET 24 establishes native stack cleanup only.
class Rva00481279 {public: bool rva00481279(int a0, int a1, int a2, int a3, int a4, int a5);};
bool Rva00481279::rva00481279(int a0, int a1, int a2, int a3, int a4, int a5) {return false;}

// Installed-vtable constant result; original owner and parameter semantics
// remain unknown. RET 12 establishes native stack cleanup only.
class Rva0049A6D7 {public: bool rva0049A6D7(int a0, int a1, int a2);};
bool Rva0049A6D7::rva0049A6D7(int a0, int a1, int a2) {return true;}

// Installed-vtable constant result; original owner and parameter semantics
// remain unknown. RET 4 establishes native stack cleanup only.
class Rva0046480A {public: int rva0046480A(int a0);};
int Rva0046480A::rva0046480A(int a0) {return -1;}

// Installed-vtable constant result; original owner and parameter semantics
// remain unknown. RET 0 establishes native stack cleanup only.
class Rva0058C484 {public: int rva0058C484();};
int Rva0058C484::rva0058C484() {return 28;}
