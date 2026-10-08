// cl: /DNDEBUG /MD
//
// Vtable-slot forwarders with no ledger owner: each moves `this` to a member
// object (add ecx, N), a member pointer (mov ecx, [ecx+N]) or a global
// (mov ecx, [VA]) and tail-jumps to one method, passing the caller's stack
// arguments through (the callee's ret N gives their count). Every class,
// method and callee here is address-named: the bytes prove only the hop and
// the argument count. Callee names already in the ledger are reused through
// their own pins when present; otherwise each callee is pinned by address.

typedef int Int;

class Rva00330E2DTarget
{
public:
	void rva00330E2D(Int a0);
};

class Rva000B318DForwarder
{
public:
	void rva000B318D(Int a0);
private:
	char m_lead[0x1D0];
	Rva00330E2DTarget m_member;
};

// vtable 0x00BCBC40#24
void Rva000B318DForwarder::rva000B318D(Int a0)
{
	m_member.rva00330E2D(a0);
}

class Rva00330DBATarget
{
public:
	void rva00330DBA();
};

class Rva000B3266Forwarder
{
public:
	void rva000B3266();
private:
	char m_lead[0x1D0];
	Rva00330DBATarget m_member;
};

// vtable 0x00BCBC40#28
void Rva000B3266Forwarder::rva000B3266()
{
	m_member.rva00330DBA();
}

class Rva000055F5Target
{
public:
	void rva000055F5(Int a0);
};

class Rva000B5FB3Forwarder
{
public:
	void rva000B5FB3(Int a0);
private:
	char m_lead[0x260];
	Rva000055F5Target m_member;
};

// vtable 0x00BCBC40#53
void Rva000B5FB3Forwarder::rva000B5FB3(Int a0)
{
	m_member.rva000055F5(a0);
}

class Rva0013132DTarget
{
public:
	void rva0013132D();
};

class Rva00131CD3Forwarder
{
public:
	void rva00131CD3();
private:
	char m_lead[0x14];
	Rva0013132DTarget *m_member;
};

// vtable 0x00BD25D8#2
void Rva00131CD3Forwarder::rva00131CD3()
{
	m_member->rva0013132D();
}

class Rva0013EA30Target
{
public:
	void rva0013EA30(Int a0);
};

class Rva00131CEAForwarder
{
public:
	void rva00131CEA(Int a0);
private:
	char m_lead[0x1C];
	Rva0013EA30Target m_member;
};

// vtable 0x00BD25D8#16
void Rva00131CEAForwarder::rva00131CEA(Int a0)
{
	m_member.rva0013EA30(a0);
}

class Rva0055B863Target
{
public:
	void rva0055B863(Int a0);
};

class Rva003ABCE6Forwarder
{
public:
	void rva003ABCE6(Int a0);
private:
	char m_lead[0x1C];
	Rva0055B863Target m_member;
};

// vtable 0x00C1C53C#4
void Rva003ABCE6Forwarder::rva003ABCE6(Int a0)
{
	m_member.rva0055B863(a0);
}

class Rva0023DAA5Target
{
public:
	void rva0023DAA5();
};

class Rva002C5265Forwarder
{
public:
	void rva002C5265();
private:
	char m_lead[0x30];
	Rva0023DAA5Target m_member;
};

// vtable 0x00BC7C90#45
void Rva002C5265Forwarder::rva002C5265()
{
	m_member.rva0023DAA5();
}

class Rva002D2DF6Target
{
public:
	void rva002D2DF6();
};

class Rva002D35C7Forwarder
{
public:
	void rva002D35C7();
private:
	char m_lead[0x10];
	Rva002D2DF6Target *m_member;
};

// vtable 0x00C02AA8#9
void Rva002D35C7Forwarder::rva002D35C7()
{
	m_member->rva002D2DF6();
}

class Rva002D6460Target
{
public:
	void rva002D6460(Int a0);
};

class Rva002D65EEForwarder
{
public:
	void rva002D65EE(Int a0);
private:
	char m_lead[0x4];
	Rva002D6460Target *m_member;
};

// vtable 0x00C02A84#7
void Rva002D65EEForwarder::rva002D65EE(Int a0)
{
	m_member->rva002D6460(a0);
}

class Rva003295B4Target
{
public:
	void rva003295B4(Int a0, Int a1);
};

class Rva0032965BForwarder
{
public:
	void rva0032965B(Int a0, Int a1);
private:
	char m_lead[0x4];
	Rva003295B4Target *m_member;
};

// vtable 0x00C0D8C4#1
void Rva0032965BForwarder::rva0032965B(Int a0, Int a1)
{
	m_member->rva003295B4(a0, a1);
}

class Rva00119F00Target
{
public:
	void rva00119F00();
};

class Rva000448B9Forwarder
{
public:
	void rva000448B9();
private:
	char m_lead[0x168];
	Rva00119F00Target *m_member;
};

// vtable 0x00BC3C80#53
void Rva000448B9Forwarder::rva000448B9()
{
	m_member->rva00119F00();
}

class Rva00079167Target
{
public:
	void rva00079167();
};

class Rva000791DDForwarder
{
public:
	void rva000791DD();
private:
	char m_lead[0x4];
	Rva00079167Target *m_member;
};

// vtable 0x00BC68F0#66
void Rva000791DDForwarder::rva000791DD()
{
	m_member->rva00079167();
}

class Rva00079186Target
{
public:
	void rva00079186(Int a0);
};

class Rva000791E5Forwarder
{
public:
	void rva000791E5(Int a0);
private:
	char m_lead[0x4];
	Rva00079186Target *m_member;
};

// vtable 0x00BC68F0#67
void Rva000791E5Forwarder::rva000791E5(Int a0)
{
	m_member->rva00079186(a0);
}

class Rva00210E9DTarget
{
public:
	void rva00210E9D();
};

// The global at VA 0x00DFE1C8.
class LivingWorldManager; extern LivingWorldManager *TheLivingWorldManager;

class Rva0009AD42Forwarder
{
public:
	void rva0009AD42();
private:
};

// vtable 0x00BC89C8#12
void Rva0009AD42Forwarder::rva0009AD42()
{
	((Rva00210E9DTarget *)TheLivingWorldManager)->rva00210E9D();
}

class Rva000B0DA8Target
{
public:
	void rva000B0DA8(Int a0, Int a1);
};

class Rva000B1974Forwarder
{
public:
	void rva000B1974(Int a0, Int a1);
private:
	char m_lead[0xC];
	Rva000B0DA8Target *m_member;
};

// vtable 0x00BC95B8#1
void Rva000B1974Forwarder::rva000B1974(Int a0, Int a1)
{
	m_member->rva000B0DA8(a0, a1);
}

class Rva001B4C7ATarget
{
public:
	void rva001B4C7A();
};

class Rva001B4CD0Forwarder
{
public:
	void rva001B4CD0();
private:
	char m_lead[0xC];
	Rva001B4C7ATarget m_member;
};

// vtable 0x00BD7678#1
void Rva001B4CD0Forwarder::rva001B4CD0()
{
	m_member.rva001B4C7A();
}

class Rva00222D47Target
{
public:
	void rva00222D47(Int a0, Int a1, Int a2);
};

class Rva00222D3FForwarder
{
public:
	void rva00222D3F(Int a0, Int a1, Int a2);
private:
	char m_lead[0x4];
	Rva00222D47Target *m_member;
};

// vtable 0x00BE6D5C#1
void Rva00222D3FForwarder::rva00222D3F(Int a0, Int a1, Int a2)
{
	m_member->rva00222D47(a0, a1, a2);
}

class Rva0022C9D2Forwarder
{
public:
	void rva0022C9D2();
private:
	char m_lead[0x10];
	Rva0023DAA5Target m_member;
};

// vtable 0x00BE74F0#9
void Rva0022C9D2Forwarder::rva0022C9D2()
{
	m_member.rva0023DAA5();
}

class Rva004CF3B9Target
{
public:
	void rva004CF3B9();
};

class Rva0025DC30Forwarder
{
public:
	void rva0025DC30();
private:
	char m_lead[0xC];
	Rva004CF3B9Target *m_member;
};

// vtable 0x00BF6040#31
void Rva0025DC30Forwarder::rva0025DC30()
{
	m_member->rva004CF3B9();
}

class Rva004D01D5Target
{
public:
	void rva004D01D5(Int a0, Int a1, Int a2, Int a3);
};

class Rva0025DC56Forwarder
{
public:
	void rva0025DC56(Int a0, Int a1, Int a2, Int a3);
private:
	char m_lead[0xC];
	Rva004D01D5Target *m_member;
};

// vtable 0x00BF6040#34
void Rva0025DC56Forwarder::rva0025DC56(Int a0, Int a1, Int a2, Int a3)
{
	m_member->rva004D01D5(a0, a1, a2, a3);
}

class Rva004D0E93Target
{
public:
	void rva004D0E93(Int a0, Int a1, Int a2);
};

class Rva0025DEDDForwarder
{
public:
	void rva0025DEDD(Int a0, Int a1, Int a2);
private:
	char m_lead[0xC];
	Rva004D0E93Target *m_member;
};

// vtable 0x00BF6040#66
void Rva0025DEDDForwarder::rva0025DEDD(Int a0, Int a1, Int a2)
{
	m_member->rva004D0E93(a0, a1, a2);
}

class Rva002034E9Target
{
public:
	void rva002034E9();
};

// The global at VA 0x00DFE78C.
extern class GameLogic *TheGameLogic;

class Rva002A9F53Forwarder
{
public:
	void rva002A9F53();
private:
};

// vtable 0x00BFDF18#5
void Rva002A9F53Forwarder::rva002A9F53()
{
	(*(Rva002034E9Target **)&TheGameLogic)->rva002034E9();
}

class Rva00513B94Target
{
public:
	void rva00513B94();
};

class Rva002AADAEForwarder
{
public:
	void rva002AADAE();
private:
	char m_lead[0x4];
	Rva00513B94Target *m_member;
};

// vtable 0x00BFDC6C#0
void Rva002AADAEForwarder::rva002AADAE()
{
	m_member->rva00513B94();
}

class Rva00222D9ATarget
{
public:
	void rva00222D9A(Int a0);
};

class Rva002AC2BFForwarder
{
public:
	void rva002AC2BF(Int a0);
private:
	char m_lead[0x4];
	Rva00222D9ATarget *m_member;
};

// vtable 0x00BFDC6C#2
void Rva002AC2BFForwarder::rva002AC2BF(Int a0)
{
	m_member->rva00222D9A(a0);
}

class Rva002AC2CFTarget
{
public:
	void rva002AC2CF(Int a0, Int a1, Int a2);
};

class Rva002AC2C7Forwarder
{
public:
	void rva002AC2C7(Int a0, Int a1, Int a2);
private:
	char m_lead[0x4];
	Rva002AC2CFTarget *m_member;
};

// vtable 0x00BFDC6C#1
void Rva002AC2C7Forwarder::rva002AC2C7(Int a0, Int a1, Int a2)
{
	m_member->rva002AC2CF(a0, a1, a2);
}

class Rva003003C5Target
{
public:
	void rva003003C5(Int a0, Int a1);
};

class Rva00300481Forwarder
{
public:
	void rva00300481(Int a0, Int a1);
private:
	char m_lead[0xC];
	Rva003003C5Target *m_member;
};

// vtable 0x00C07484#1
void Rva00300481Forwarder::rva00300481(Int a0, Int a1)
{
	m_member->rva003003C5(a0, a1);
}

class Rva003294D6Target
{
public:
	void rva003294D6(Int a0, Int a1);
};

class Rva00329653Forwarder
{
public:
	void rva00329653(Int a0, Int a1);
private:
	char m_lead[0x4];
	Rva003294D6Target *m_member;
};

// vtable 0x00C0D8C4#0
void Rva00329653Forwarder::rva00329653(Int a0, Int a1)
{
	m_member->rva003294D6(a0, a1);
}

class Rva002198C8Target
{
public:
	void rva002198C8();
};

class Rva0032AF9CForwarder
{
public:
	void rva0032AF9C();
private:
	char m_lead[0x4];
	Rva002198C8Target *m_member;
};

// vtable 0x00C0D938#0
void Rva0032AF9CForwarder::rva0032AF9C()
{
	m_member->rva002198C8();
}

class Rva0032AFD4Target
{
public:
	void rva0032AFD4(Int a0, Int a1, Int a2);
};

class Rva0032AFCCForwarder
{
public:
	void rva0032AFCC(Int a0, Int a1, Int a2);
private:
	char m_lead[0x4];
	Rva0032AFD4Target *m_member;
};

// vtable 0x00C0D938#1
void Rva0032AFCCForwarder::rva0032AFCC(Int a0, Int a1, Int a2)
{
	m_member->rva0032AFD4(a0, a1, a2);
}

class Rva0033082FTarget
{
public:
	void rva0033082F(Int a0, Int a1);
};

class Rva003308EEForwarder
{
public:
	void rva003308EE(Int a0, Int a1);
private:
	char m_lead[0xC];
	Rva0033082FTarget *m_member;
};

// vtable 0x00C0DB58#1
void Rva003308EEForwarder::rva003308EE(Int a0, Int a1)
{
	m_member->rva0033082F(a0, a1);
}

class Rva00358F7CTarget
{
public:
	void rva00358F7C();
};

class Rva003592FAForwarder
{
public:
	void rva003592FA();
private:
	char m_lead[0xC];
	Rva00358F7CTarget m_member;
};

// vtable 0x00C15398#9
void Rva003592FAForwarder::rva003592FA()
{
	m_member.rva00358F7C();
}

class Rva00392092Target
{
public:
	void rva00392092();
};

class Rva003922B7Forwarder
{
public:
	void rva003922B7();
private:
	char m_lead[0x10];
	Rva00392092Target m_member;
};

// vtable 0x00C1A088#1
void Rva003922B7Forwarder::rva003922B7()
{
	m_member.rva00392092();
}

class Rva003A547ETarget
{
public:
	void rva003A547E(Int a0);
};

class Rva003A5896Forwarder
{
public:
	void rva003A5896(Int a0);
private:
	char m_lead[0x1C];
	Rva003A547ETarget m_member;
};

// vtable 0x00C1B5A8#3
void Rva003A5896Forwarder::rva003A5896(Int a0)
{
	m_member.rva003A547E(a0);
}

class Rva001DBCDCTarget
{
public:
	void rva001DBCDC();
};

class Rva003ED1B6Forwarder
{
public:
	void rva003ED1B6();
private:
	char m_lead[0xC];
	Rva001DBCDCTarget m_member;
};

// vtable 0x00C36100#9
void Rva003ED1B6Forwarder::rva003ED1B6()
{
	m_member.rva001DBCDC();
}

class Rva0020F0D3Target
{
public:
	void rva0020F0D3();
};

class Rva003FCE30Forwarder
{
public:
	void rva003FCE30();
private:
	char m_lead[0x4];
	Rva0020F0D3Target *m_member;
};

// vtable 0x00C37C20#0
void Rva003FCE30Forwarder::rva003FCE30()
{
	m_member->rva0020F0D3();
}

class Rva003FD05ETarget
{
public:
	void rva003FD05E(Int a0, Int a1, Int a2);
};

class Rva003FD056Forwarder
{
public:
	void rva003FD056(Int a0, Int a1, Int a2);
private:
	char m_lead[0x4];
	Rva003FD05ETarget *m_member;
};

// vtable 0x00C37C20#1
void Rva003FD056Forwarder::rva003FD056(Int a0, Int a1, Int a2)
{
	m_member->rva003FD05E(a0, a1, a2);
}
