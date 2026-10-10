// cl: /DNDEBUG /MD
//
// State-derived constructors outside the packed 0x0033F2FD family (see
// AIStateHashCtors0033F2FD.cpp for the shared recipe): each calls the State
// constructor 0x004D73FC with a 32-bit name hash, stores its vtable (VA in
// the per-class note) and initialises its members in offset order. The
// zeroed float triples at +0x24 are written after the vtable store, which
// the Coord3D zero() call in the body reproduces; the SSE float stores need
// /arch:SSE. Member widths, offsets and argument counts come from the
// retail stores and ret sizes; names stay address-derived.
class StateMachine;

#include "../../../../Libraries/Include/Lib/Coord3D.h"

// Retail inlines these three zero stores; the canonical Coord3D::zero is the out-of-line owner.
static inline void zeroInline(Coord3D &c) { c.x = 0.0f; c.y = 0.0f; c.z = 0.0f; }

class State
{
public:
	State(StateMachine *machine, unsigned int hash);
	virtual ~State();

private:
	unsigned char m_pad04[0x20 - 4];
};

// Rva00342547: retail 0x00342547 (37B), hash 0x6649a02e, vtable 0xc12378
class Rva00342547 : public State
{
public:
	Rva00342547(StateMachine *machine);

private:
	float m_20; // +0x20
};

Rva00342547::Rva00342547(StateMachine *machine)
	: State(machine, 0x6649A02Eu)
	, m_20(0.0f)
{
}

// Rva0036756A: retail 0x0036756A (60B), hash 0x826eaa22, vtable 0xc17360 callers 0x003676E4 0x00367A14 0x00367A4F 0x00367AF0 and 2 more
class Rva0036756A : public State
{
public:
	Rva0036756A(StateMachine *machine, int arg0, bool arg1);

private:
	int m_20; // +0x20
	unsigned char m_pad24[0x30 - 0x24];
	bool m_30; // +0x30
	unsigned char m_pad31[0x34 - 0x31];
	int m_34; // +0x34
	float m_38; // +0x38
};

Rva0036756A::Rva0036756A(StateMachine *machine, int arg0, bool arg1)
	: State(machine, 0x826EAA22u)
	, m_20(arg0)
	, m_30(arg1)
	, m_34(0)
	, m_38(1.0f)
{
}

// Rva003675AC: retail 0x003675AC (36B), hash 0xff874822, vtable 0xc173c0 callers 0x00367719 0x00367A83 0x00367B28 0x00367C06
class Rva003675AC : public State
{
public:
	Rva003675AC(StateMachine *machine, int arg0);

private:
	int m_20; // +0x20
};

Rva003675AC::Rva003675AC(StateMachine *machine, int arg0)
	: State(machine, 0xFF874822u)
	, m_20(arg0)
{
}

// Rva003675D6: retail 0x003675D6 (40B), hash 0xde23e437, vtable 0xc17418 callers 0x00367752 0x00367ABB 0x00367B61 0x00367C3E
class Rva003675D6 : public State
{
public:
	Rva003675D6(StateMachine *machine, bool arg0);

private:
	bool m_20; // +0x20
	unsigned char m_pad21[0x24 - 0x21];
	int m_24; // +0x24
};

Rva003675D6::Rva003675D6(StateMachine *machine, bool arg0)
	: State(machine, 0xDE23E437u)
	, m_20(arg0)
	, m_24(0)
{
}

// Rva00367E59: retail 0x00367E59 (51B), hash 0x539b80b3, vtable 0xc17648 callers 0x00368A95
class Rva00367E59 : public State
{
public:
	Rva00367E59(StateMachine *machine);

private:
	int m_20; // +0x20
	Coord3D m_24; // +0x24, zeroed in the body after the vtable store
};

Rva00367E59::Rva00367E59(StateMachine *machine)
	: State(machine, 0x539B80B3u)
	, m_20(0)
{
	zeroInline(m_24);
}

// Rva004884ED: retail 0x004884ED (40B), hash 0xaa55fe2f, vtable 0xc4b3e0 callers 0x00488627
class Rva004884ED : public State
{
public:
	Rva004884ED(StateMachine *machine, int arg0);

private:
	int m_20; // +0x20
	int m_24; // +0x24
};

Rva004884ED::Rva004884ED(StateMachine *machine, int arg0)
	: State(machine, 0xAA55FE2Fu)
	, m_20(arg0)
	, m_24(0)
{
}

// Rva0048851B: retail 0x0048851B (36B), hash 0xf0395b0e, vtable 0xc4b448 callers 0x0048865E
class Rva0048851B : public State
{
public:
	Rva0048851B(StateMachine *machine, int arg0);

private:
	int m_20; // +0x20
};

Rva0048851B::Rva0048851B(StateMachine *machine, int arg0)
	: State(machine, 0xF0395B0Eu)
	, m_20(arg0)
{
}

// Rva00488545: retail 0x00488545 (40B), hash 0xbca9f972, vtable 0xc4b4b0 callers 0x00488691
class Rva00488545 : public State
{
public:
	Rva00488545(StateMachine *machine, int arg0);

private:
	int m_20; // +0x20
	int m_24; // +0x24
};

Rva00488545::Rva00488545(StateMachine *machine, int arg0)
	: State(machine, 0xBCA9F972u)
	, m_20(arg0)
	, m_24(0)
{
}

// Rva004886C7: retail 0x004886C7 (40B), hash 0xc618e42c, vtable 0xc4b568 callers 0x00488DEC
class Rva004886C7 : public State
{
public:
	Rva004886C7(StateMachine *machine);

private:
	int m_20; // +0x20
	int m_24; // +0x24
	bool m_28; // +0x28
};

Rva004886C7::Rva004886C7(StateMachine *machine)
	: State(machine, 0xC618E42Cu)
	, m_20(0)
	, m_24(0)
	, m_28(false)
{
}

// Rva004A992A: retail 0x004A992A (29B), hash 0xf02b7162, vtable 0xc54010 callers 0x004A9DBB
class Rva004A992A : public State
{
public:
	Rva004A992A(StateMachine *machine);
};

Rva004A992A::Rva004A992A(StateMachine *machine)
	: State(machine, 0xF02B7162u)
{
}

// Rva00542D25: retail 0x00542D25 (51B), hash 0x8f11452, vtable 0xc696d0 callers 0x0054321D
class Rva00542D25 : public State
{
public:
	Rva00542D25(StateMachine *machine);

private:
	int m_20; // +0x20
	Coord3D m_24; // +0x24, zeroed in the body after the vtable store
};

Rva00542D25::Rva00542D25(StateMachine *machine)
	: State(machine, 0x8F11452u)
	, m_20(0)
{
	zeroInline(m_24);
}

// Rva00544095: retail 0x00544095 (33B), hash 0xd2719020, vtable 0xc69940 callers 0x00544917
class Rva00544095 : public State
{
public:
	Rva00544095(StateMachine *machine);

private:
	int m_20; // +0x20
};

Rva00544095::Rva00544095(StateMachine *machine)
	: State(machine, 0xD2719020u)
	, m_20(0)
{
}

// Rva00544C2A: retail 0x00544C2A (33B), hash 0x466e7761, vtable 0xc69cf8 callers 0x00544F7A
class Rva00544C2A : public State
{
public:
	Rva00544C2A(StateMachine *machine);

private:
	int m_20; // +0x20
};

Rva00544C2A::Rva00544C2A(StateMachine *machine)
	: State(machine, 0x466E7761u)
	, m_20(0)
{
}

// Rva00545B4F: retail 0x00545B4F (29B), hash 0xed015b70, vtable 0xc6a038 callers 0x0054609C
class Rva00545B4F : public State
{
public:
	Rva00545B4F(StateMachine *machine);
};

Rva00545B4F::Rva00545B4F(StateMachine *machine)
	: State(machine, 0xED015B70u)
{
}

