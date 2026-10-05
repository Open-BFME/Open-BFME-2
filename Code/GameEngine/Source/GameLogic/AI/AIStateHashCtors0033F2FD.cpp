// cl: /O1 /DNDEBUG /MD
//
// State-derived constructors packed at 0x0033F2FD..0x0033F834, each
// followed by its rowed 6-byte constant getter. Every body calls the State
// constructor 0x004D73FC (the unsigned-hash twin pinned in symbols.csv, as
// in StateDerivedCtors_muse-a7a4.cpp) with a 32-bit name hash, then stores
// its own vtable and initialises its members (declared and initialised in
// offset order; the compiler schedules parameter-fed members and zeroed
// dwords before the vtable store and zeroed bytes after it). Member widths,
// offsets and argument counts come from the retail stores and ret sizes;
// 0x0033F4DF pops a second argument it never reads. The callers are the
// AI state-machine constructors at 0x00343xxx and 0x00352xxx; the state
// identities are not recovered, so every name is address-derived. Vtable
// values in the per-class notes are virtual addresses.
class StateMachine;

class State
{
public:
	State(StateMachine *machine, unsigned int hash);
	virtual ~State();

private:
	unsigned char m_pad04[0x20 - 4];
};

// Rva0033F2FD: retail 0x0033F2FD (29B), hash 0xed821984, vtable 0xc10e48 callers 0x003521A5 0x0035220B
class Rva0033F2FD : public State
{
public:
	Rva0033F2FD(StateMachine *machine);
};

Rva0033F2FD::Rva0033F2FD(StateMachine *machine)
	: State(machine, 0xED821984u)
{
}

// Rva0033F320: retail 0x0033F320 (29B), hash 0x5fe77381, vtable 0xc10e98 callers 0x003528B7
class Rva0033F320 : public State
{
public:
	Rva0033F320(StateMachine *machine);
};

Rva0033F320::Rva0033F320(StateMachine *machine)
	: State(machine, 0x5FE77381u)
{
}

// Rva0033F364: retail 0x0033F364 (33B), hash 0xefc3d47f, vtable 0xc10f40 callers 0x0034344D
class Rva0033F364 : public State
{
public:
	Rva0033F364(StateMachine *machine);

private:
	int m_20; // +0x20
};

Rva0033F364::Rva0033F364(StateMachine *machine)
	: State(machine, 0xEFC3D47Fu)
	, m_20(0)
{
}

// Rva0033F38B: retail 0x0033F38B (37B), hash 0xf17c0982, vtable 0xc10fa0 callers 0x00343486
class Rva0033F38B : public State
{
public:
	Rva0033F38B(StateMachine *machine);

private:
	int m_20; // +0x20
	int m_24; // +0x24
};

Rva0033F38B::Rva0033F38B(StateMachine *machine)
	: State(machine, 0xF17C0982u)
	, m_20(0)
	, m_24(0)
{
}

// Rva0033F3B6: retail 0x0033F3B6 (51B), hash 0x5c57bd74, vtable 0xc11008 callers 0x003432A1 0x00343679 0x00346DAE
class Rva0033F3B6 : public State
{
public:
	Rva0033F3B6(StateMachine *machine, bool arg0, bool arg1);

private:
	bool m_20; // +0x20
	bool m_21; // +0x21
	bool m_22; // +0x22
	bool m_23; // +0x23
};

Rva0033F3B6::Rva0033F3B6(StateMachine *machine, bool arg0, bool arg1)
	: State(machine, 0x5C57BD74u)
	, m_20(arg0)
	, m_21(false)
	, m_22(false)
	, m_23(arg1)
{
}

// Rva0033F3EF: retail 0x0033F3EF (37B), hash 0x5c57bd74, vtable 0xc11068 callers 0x00343907
class Rva0033F3EF : public State
{
public:
	Rva0033F3EF(StateMachine *machine);

private:
	bool m_20; // +0x20
	bool m_21; // +0x21
};

Rva0033F3EF::Rva0033F3EF(StateMachine *machine)
	: State(machine, 0x5C57BD74u)
	, m_20(false)
	, m_21(false)
{
}

// Rva0033F41A: retail 0x0033F41A (29B), hash 0x3e719b30, vtable 0xc110d0 callers 0x00352142
class Rva0033F41A : public State
{
public:
	Rva0033F41A(StateMachine *machine);
};

Rva0033F41A::Rva0033F41A(StateMachine *machine)
	: State(machine, 0x3E719B30u)
{
}

// Rva0033F43D: retail 0x0033F43D (29B), hash 0xe4f2d93d, vtable 0xc11120 callers 0x0034331C 0x003436F4 0x003437EA 0x0034399A and 1 more
class Rva0033F43D : public State
{
public:
	Rva0033F43D(StateMachine *machine);
};

Rva0033F43D::Rva0033F43D(StateMachine *machine)
	: State(machine, 0xE4F2D93Du)
{
}

// Rva0033F460: retail 0x0033F460 (29B), hash 0xfd797d2a, vtable 0xc11188 callers 0x00343534 0x003435B2 0x00343B03 0x00343B80
class Rva0033F460 : public State
{
public:
	Rva0033F460(StateMachine *machine);
};

Rva0033F460::Rva0033F460(StateMachine *machine)
	: State(machine, 0xFD797D2Au)
{
}

// Rva0033F483: retail 0x0033F483 (40B), hash 0x7252e66d, vtable 0xc111f8 callers 0x00340B7C 0x003432E6 0x00343578 0x003436BE and 4 more
class Rva0033F483 : public State
{
public:
	Rva0033F483(StateMachine *machine, int arg0);

private:
	int m_20; // +0x20
	bool m_24; // +0x24
};

Rva0033F483::Rva0033F483(StateMachine *machine, int arg0)
	: State(machine, 0x7252E66Du)
	, m_20(arg0)
	, m_24(false)
{
}

// Rva0033F4B1: retail 0x0033F4B1 (40B), hash 0x7252e66d, vtable 0xc11258 callers 0x0034395B 0x00343B47
class Rva0033F4B1 : public State
{
public:
	Rva0033F4B1(StateMachine *machine, int arg0);

private:
	int m_20; // +0x20
	bool m_24; // +0x24
};

Rva0033F4B1::Rva0033F4B1(StateMachine *machine, int arg0)
	: State(machine, 0x7252E66Du)
	, m_20(arg0)
	, m_24(false)
{
}

// Rva0033F4DF: retail 0x0033F4DF (37B), hash 0x4502d596, vtable 0xc112c0 callers 0x003522D8
class Rva0033F4DF : public State
{
public:
	Rva0033F4DF(StateMachine *machine, int unused); // ret 8, second argument unread

private:
	int m_20; // +0x20
	bool m_24; // +0x24
};

Rva0033F4DF::Rva0033F4DF(StateMachine *machine, int)
	: State(machine, 0x4502D596u)
	, m_20(0)
	, m_24(false)
{
}

// Rva0033F51D: retail 0x0033F51D (29B), hash 0x1f4fa782, vtable 0xc11318 callers 0x0035248D
class Rva0033F51D : public State
{
public:
	Rva0033F51D(StateMachine *machine);
};

Rva0033F51D::Rva0033F51D(StateMachine *machine)
	: State(machine, 0x1F4FA782u)
{
}

// Rva0033F540: retail 0x0033F540 (37B), hash 0xe84618b6, vtable 0xc11368 callers 0x003524BD
class Rva0033F540 : public State
{
public:
	Rva0033F540(StateMachine *machine);

private:
	int m_20; // +0x20
	bool m_24; // +0x24
};

Rva0033F540::Rva0033F540(StateMachine *machine)
	: State(machine, 0xE84618B6u)
	, m_20(0)
	, m_24(false)
{
}

// Rva0033F56B: retail 0x0033F56B (37B), hash 0x906db253, vtable 0xc113b8 callers 0x003524ED
class Rva0033F56B : public State
{
public:
	Rva0033F56B(StateMachine *machine);

private:
	int m_20; // +0x20
	bool m_24; // +0x24
};

Rva0033F56B::Rva0033F56B(StateMachine *machine)
	: State(machine, 0x906DB253u)
	, m_20(0)
	, m_24(false)
{
}

// Rva0033F596: retail 0x0033F596 (29B), hash 0x1072431b, vtable 0xc11410 callers 0x0035260F
class Rva0033F596 : public State
{
public:
	Rva0033F596(StateMachine *machine);
};

Rva0033F596::Rva0033F596(StateMachine *machine)
	: State(machine, 0x1072431Bu)
{
}

// Rva0033F5B9: retail 0x0033F5B9 (36B), hash 0x55a8130b, vtable 0xc11468 callers 0x0033F5EE 0x0033F610 0x00352642 0x003526A3
class Rva0033F5B9 : public State
{
public:
	Rva0033F5B9(StateMachine *machine, bool arg0);

private:
	bool m_20; // +0x20
};

Rva0033F5B9::Rva0033F5B9(StateMachine *machine, bool arg0)
	: State(machine, 0x55A8130Bu)
	, m_20(arg0)
{
}

// Rva0033F627: retail 0x0033F627 (33B), hash 0x16d9ec7e, vtable 0xc11588 callers 0x00343268
class Rva0033F627 : public State
{
public:
	Rva0033F627(StateMachine *machine);

private:
	int m_20; // +0x20
};

Rva0033F627::Rva0033F627(StateMachine *machine)
	: State(machine, 0x16D9EC7Eu)
	, m_20(0)
{
}

// Rva0033F64E: retail 0x0033F64E (40B), hash 0xdfb3dbc7, vtable 0xc115e8 callers 0x0033F687 0x0033F6A9 0x0033F6C9 0x003525AE
class Rva0033F64E : public State
{
public:
	Rva0033F64E(StateMachine *machine, bool arg0);

private:
	int m_20; // +0x20
	bool m_24; // +0x24
};

Rva0033F64E::Rva0033F64E(StateMachine *machine, bool arg0)
	: State(machine, 0xDFB3DBC7u)
	, m_20(0)
	, m_24(arg0)
{
}

// Rva0033F701: retail 0x0033F701 (29B), hash 0xcf7e4f5f, vtable 0xc11798 callers 0x003526D3
class Rva0033F701 : public State
{
public:
	Rva0033F701(StateMachine *machine);
};

Rva0033F701::Rva0033F701(StateMachine *machine)
	: State(machine, 0xCF7E4F5Fu)
{
}

// Rva0033F724: retail 0x0033F724 (33B), hash 0x9837864, vtable 0xc117f0 callers 0x00352732
class Rva0033F724 : public State
{
public:
	Rva0033F724(StateMachine *machine);

private:
	int m_20; // +0x20
};

Rva0033F724::Rva0033F724(StateMachine *machine)
	: State(machine, 0x9837864u)
	, m_20(0)
{
}

// Rva0033F74B: retail 0x0033F74B (33B), hash 0x56f63b0e, vtable 0xc11850 callers 0x00352761
class Rva0033F74B : public State
{
public:
	Rva0033F74B(StateMachine *machine);

private:
	int m_20; // +0x20
};

Rva0033F74B::Rva0033F74B(StateMachine *machine)
	: State(machine, 0x56F63B0Eu)
	, m_20(0)
{
}

// Rva0033F772: retail 0x0033F772 (37B), hash 0x705e17cf, vtable 0xc118b0 callers 0x00352791
class Rva0033F772 : public State
{
public:
	Rva0033F772(StateMachine *machine);

private:
	int m_20; // +0x20
	int m_24; // +0x24
};

Rva0033F772::Rva0033F772(StateMachine *machine)
	: State(machine, 0x705E17CFu)
	, m_20(0)
	, m_24(0)
{
}

// Rva0033F79D: retail 0x0033F79D (37B), hash 0xd08836d8, vtable 0xc11900 callers 0x003527C1
class Rva0033F79D : public State
{
public:
	Rva0033F79D(StateMachine *machine);

private:
	int m_20; // +0x20
	int m_24; // +0x24
};

Rva0033F79D::Rva0033F79D(StateMachine *machine)
	: State(machine, 0xD08836D8u)
	, m_20(0)
	, m_24(0)
{
}

// Rva0033F7C8: retail 0x0033F7C8 (29B), hash 0x16c0b5af, vtable 0xc11958 callers 0x00340398 0x0034454C 0x003523CD
class Rva0033F7C8 : public State
{
public:
	Rva0033F7C8(StateMachine *machine);
};

Rva0033F7C8::Rva0033F7C8(StateMachine *machine)
	: State(machine, 0x16C0B5AFu)
{
}

// Rva0033F7EB: retail 0x0033F7EB (29B), hash 0x1373a8a0, vtable 0xc119b0 callers 0x00352AF8
class Rva0033F7EB : public State
{
public:
	Rva0033F7EB(StateMachine *machine);
};

Rva0033F7EB::Rva0033F7EB(StateMachine *machine)
	: State(machine, 0x1373A8A0u)
{
}

// Rva0033F80E: retail 0x0033F80E (41B), hash 0xcac7338, vtable 0xc11a08 callers 0x003528E7
class Rva0033F80E : public State
{
public:
	Rva0033F80E(StateMachine *machine);

private:
	bool m_20; // +0x20
	unsigned char m_pad21[0x24 - 0x21];
	int m_24; // +0x24
	int m_28; // +0x28
};

Rva0033F80E::Rva0033F80E(StateMachine *machine)
	: State(machine, 0xCAC7338u)
	, m_20(false)
	, m_24(0)
	, m_28(-1)
{
}


// Derived states whose constructors call the ones above.
// Rva0033F5E3 and Rva0033F605: retail 0x0033F5E3 / 0x0033F605 (28B each),
// forwarding (machine, flag) to Rva0033F5B9, vtables 0xc114c0 / 0xc11520.
class Rva0033F5E3 : public Rva0033F5B9
{
public:
	Rva0033F5E3(StateMachine *machine, bool arg0);
};

Rva0033F5E3::Rva0033F5E3(StateMachine *machine, bool arg0)
	: Rva0033F5B9(machine, arg0)
{
}

class Rva0033F605 : public Rva0033F5B9
{
public:
	Rva0033F605(StateMachine *machine, bool arg0);
};

Rva0033F605::Rva0033F605(StateMachine *machine, bool arg0)
	: Rva0033F5B9(machine, arg0)
{
}

// Rva0033F67C and Rva0033F69E: retail 0x0033F67C / 0x0033F69E (28B each),
// forwarding (machine, flag) to Rva0033F64E, vtables 0xc11638 / 0xc11698;
// Rva0033F6C0: retail 0x0033F6C0 (26B), Rva0033F64E with false, vtable
// 0xc116f8 (caller 0x00343C3D).
class Rva0033F67C : public Rva0033F64E
{
public:
	Rva0033F67C(StateMachine *machine, bool arg0);
};

Rva0033F67C::Rva0033F67C(StateMachine *machine, bool arg0)
	: Rva0033F64E(machine, arg0)
{
}

class Rva0033F69E : public Rva0033F64E
{
public:
	Rva0033F69E(StateMachine *machine, bool arg0);
};

Rva0033F69E::Rva0033F69E(StateMachine *machine, bool arg0)
	: Rva0033F64E(machine, arg0)
{
}

class Rva0033F6C0 : public Rva0033F64E
{
public:
	Rva0033F6C0(StateMachine *machine);
};

Rva0033F6C0::Rva0033F6C0(StateMachine *machine)
	: Rva0033F64E(machine, false)
{
}

// Rva00340391: retail 0x00340391 (28B), derived from Rva0033F7C8, vtable
// 0xc12048; sets its own +0x20 byte to true.
class Rva00340391 : public Rva0033F7C8
{
public:
	Rva00340391(StateMachine *machine);

private:
	bool m_20; // +0x20
};

Rva00340391::Rva00340391(StateMachine *machine)
	: Rva0033F7C8(machine)
	, m_20(true)
{
}
