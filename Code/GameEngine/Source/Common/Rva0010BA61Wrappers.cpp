// cl: /DNDEBUG /MD
//
// Helper-then-tail wrappers: each saves this, runs a no-argument member
// helper, restores this, and tail-jumps to another no-argument member.
// The first three restore this itself (mov ecx,esi); the rest load a
// member pointer (mov ecx,[esi+off]). Single-inheritance qualified base
// calls for same-object tails (VslotSmallBodiesAJ idiom); unrowed
// targets are pinned from each body's own REL32, rowed ones reuse their
// ledger names.
// 0x0010BA61: helper 0x00109D64, tail rowed-pin 0x00108895.
// 0x004E54B8: helper 0x004E5372, tail 0x004E52DC.
// 0x005962E7: helper rowed 0x0025C010, tail 0x00596269.
// 0x005D1516: helper rowed trivial 0x000B3FD0, tail 0x005D13C2 (+8).
// 0x005E1906: helper rowed 0x00248D08, tail 0x005E18D0 (+0xC).
// 0x005E1917: helper rowed 0x00420B2A, tail 0x005E18DC (+0xC).
// 0x005E1BC4: helper rowed trivial 0x000B3FD0, tail 0x005E1B9A (+0xC).
// 0x005E25DE: helper rowed trivial 0x000B3FD0, tail 0x005E254C (+0xC).
// 0x005E590F: helper rowed trivial 0x000B3FD0, tail 0x005E589E (+8).
// 0x005E6BA3: helper rowed trivial 0x000B3FD0, tail 0x005E6A9D (+0x20).
// 0x005E6BB4: helper rowed trivial 0x000B3FD0, tail 0x005E6AD8 (+0x20).

class Rva0010BA2COwner
{
public:
	void rva00108895();
};

class Rva0010BA61 : public Rva0010BA2COwner
{
public:
	void rva0010BA61();
private:
	void helper00109D64();
};
// Rva0010BA61::rva0010BA61 is defined with its retail-matched body in Code/GameEngine/Source/Common/Rva0010BA61.cpp (0x0010BA61).

class Rva004E52DCForwarder
{
public:
	void tail004E52DC();
};

class Rva004E54B8 : public Rva004E52DCForwarder
{
public:
	void rva004E54B8();
private:
	void helper004E5372();
};
void Rva004E54B8::rva004E54B8()
{
	helper004E5372();
	Rva004E52DCForwarder::tail004E52DC();
}

class Rva0025C010
{
public:
	void rva0025C010();
};

class Rva00596269Forwarder
{
public:
	void tail00596269();
};

class Rva005962E7 : public Rva00596269Forwarder
{
public:
	void rva005962E7();
};
void Rva005962E7::rva005962E7()
{
	((Rva0025C010 *)this)->rva0025C010();
	Rva00596269Forwarder::tail00596269();
}

class Coord3D
{
public:
	~Coord3D();
};

class Rva005D13C2Forwarder
{
public:
	void tail005D13C2();
};

class Rva005D1516
{
public:
	void rva005D1516();
private:
	char m_pad00[8];
	Rva005D13C2Forwarder *m_08;
};
void Rva005D1516::rva005D1516()
{
	((Coord3D *)this)->~Coord3D();
	m_08->tail005D13C2();
}

class Overridable
{
public:
	void markAsOverride();
};

class Rva005E18D0Forwarder
{
public:
	void tail005E18D0();
};

class Rva005E1906 : public Rva005E18D0Forwarder
{
public:
	void rva005E1906();
private:
	char m_pad00[0x0C];
	Rva005E18D0Forwarder *m_0C;
};
void Rva005E1906::rva005E1906()
{
	((Overridable *)this)->markAsOverride();
	m_0C->tail005E18D0();
}

class Rva00420B2AZeroSetter
{
public:
	void disable();
};

class Rva005E18DCForwarder
{
public:
	void tail005E18DC();
};

class Rva005E1917 : public Rva005E18DCForwarder
{
public:
	void rva005E1917();
private:
	char m_pad00[0x0C];
	Rva005E18DCForwarder *m_0C;
};
void Rva005E1917::rva005E1917()
{
	((Rva00420B2AZeroSetter *)this)->disable();
	m_0C->tail005E18DC();
}

class Rva005E1B9AForwarder
{
public:
	void tail005E1B9A();
};

class Rva005E1BC4
{
public:
	void rva005E1BC4();
private:
	char m_pad00[0x0C];
	Rva005E1B9AForwarder *m_0C;
};
void Rva005E1BC4::rva005E1BC4()
{
	((Coord3D *)this)->~Coord3D();
	m_0C->tail005E1B9A();
}

class Rva005E254CForwarder
{
public:
	void tail005E254C();
};

class Rva005E25DE
{
public:
	void rva005E25DE();
private:
	char m_pad00[0x0C];
	Rva005E254CForwarder *m_0C;
};
void Rva005E25DE::rva005E25DE()
{
	((Coord3D *)this)->~Coord3D();
	m_0C->tail005E254C();
}

class Rva005E589EForwarder
{
public:
	void tail005E589E();
};

class Rva005E590F
{
public:
	void rva005E590F();
private:
	char m_pad00[8];
	Rva005E589EForwarder *m_08;
};
void Rva005E590F::rva005E590F()
{
	((Coord3D *)this)->~Coord3D();
	m_08->tail005E589E();
}

class Rva005E6A9DForwarder
{
public:
	void tail005E6A9D();
};

class Rva005E6BA3
{
public:
	void rva005E6BA3();
private:
	char m_pad00[0x20];
	Rva005E6A9DForwarder *m_20;
};
void Rva005E6BA3::rva005E6BA3()
{
	((Coord3D *)this)->~Coord3D();
	m_20->tail005E6A9D();
}

class Rva005E6AD8Forwarder
{
public:
	void tail005E6AD8();
};

class Rva005E6BB4
{
public:
	void rva005E6BB4();
private:
	char m_pad00[0x20];
	Rva005E6AD8Forwarder *m_20;
};
void Rva005E6BB4::rva005E6BB4()
{
	((Coord3D *)this)->~Coord3D();
	m_20->tail005E6AD8();
}
