// cl: /DNDEBUG /MD
//
// Null-checked vtable-slot forwarders with no ledger owner: each loads a
// member pointer, and when it is set tail-jumps to one method of it with the
// caller's stack arguments (the callee's ret N gives their count); when it is
// null it returns nothing, 0, false, -1 or 0x31 as the bytes show. Every
// class, method and callee is address-named: the bytes prove only the hop,
// the argument count and the fallback value.

typedef int Int;
typedef bool Bool;

class Rva00330995NullTarget
{
public:
	void rva00330995(Int a0);
};

class Rva000B31B9NullForwarder
{
public:
	void rva000B31B9(Int a0);
private:
	char m_lead[0x1D4];
	Rva00330995NullTarget *m_member;
};

// vtable 0x00BCBC40#26
void Rva000B31B9NullForwarder::rva000B31B9(Int a0)
{
	if (m_member)
		m_member->rva00330995(a0);
}

class Rva000EA644NullTarget
{
public:
	Bool rva000EA644(Int a0);
};

class Rva0006820FNullForwarder
{
public:
	Bool rva0006820F(Int a0);
private:
	char m_lead[0x3850];
	Rva000EA644NullTarget *m_member;
};

// vtable 0x00BC5DB0#142
Bool Rva0006820FNullForwarder::rva0006820F(Int a0)
{
	if (m_member)
		return m_member->rva000EA644(a0);
	return false;
}

class Rva000680B3NullTarget
{
public:
	void rva000680B3();
};

class Rva00091E38NullForwarder
{
public:
	void rva00091E38();
private:
	char m_lead[0x14];
	Rva000680B3NullTarget *m_member;
};

// vtable 0x00BC80A0#17
void Rva00091E38NullForwarder::rva00091E38()
{
	if (m_member)
		m_member->rva000680B3();
}

class Rva00068283NullTarget
{
public:
	void rva00068283(Int a0);
};

class Rva00091EDDNullForwarder
{
public:
	void rva00091EDD(Int a0);
private:
	char m_lead[0x14];
	Rva00068283NullTarget *m_member;
};

// vtable 0x00BC80A0#22
void Rva00091EDDNullForwarder::rva00091EDD(Int a0)
{
	if (m_member)
		m_member->rva00068283(a0);
}

class Rva0006819BNullTarget
{
public:
	Int rva0006819B(Int a0, Int a1);
};

class Rva00091F2ANullForwarder
{
public:
	Int rva00091F2A(Int a0, Int a1);
private:
	char m_lead[0x14];
	Rva0006819BNullTarget *m_member;
};

// vtable 0x00BC80A0#24
Int Rva00091F2ANullForwarder::rva00091F2A(Int a0, Int a1)
{
	if (m_member)
		return m_member->rva0006819B(a0, a1);
	return 0;
}

class Rva000681AFNullTarget
{
public:
	Bool rva000681AF(Int a0, Int a1);
};

class Rva00091F51NullForwarder
{
public:
	Bool rva00091F51(Int a0, Int a1);
private:
	char m_lead[0x14];
	Rva000681AFNullTarget *m_member;
};

// vtable 0x00BC80A0#28
Bool Rva00091F51NullForwarder::rva00091F51(Int a0, Int a1)
{
	if (m_member)
		return m_member->rva000681AF(a0, a1);
	return false;
}

class Rva000681D3NullTarget
{
public:
	Bool rva000681D3(Int a0, Int a1);
};

class Rva00091F62NullForwarder
{
public:
	Bool rva00091F62(Int a0, Int a1);
private:
	char m_lead[0x14];
	Rva000681D3NullTarget *m_member;
};

// vtable 0x00BC80A0#29
Bool Rva00091F62NullForwarder::rva00091F62(Int a0, Int a1)
{
	if (m_member)
		return m_member->rva000681D3(a0, a1);
	return false;
}

class Rva000681E7NullTarget
{
public:
	Bool rva000681E7(Int a0, Int a1);
};

class Rva00091F73NullForwarder
{
public:
	Bool rva00091F73(Int a0, Int a1);
private:
	char m_lead[0x14];
	Rva000681E7NullTarget *m_member;
};

// vtable 0x00BC80A0#30
Bool Rva00091F73NullForwarder::rva00091F73(Int a0, Int a1)
{
	if (m_member)
		return m_member->rva000681E7(a0, a1);
	return false;
}

class Rva000681FBNullTarget
{
public:
	Bool rva000681FB(Int a0);
};

class Rva00091F84NullForwarder
{
public:
	Bool rva00091F84(Int a0);
private:
	char m_lead[0x14];
	Rva000681FBNullTarget *m_member;
};

// vtable 0x00BC80A0#31
Bool Rva00091F84NullForwarder::rva00091F84(Int a0)
{
	if (m_member)
		return m_member->rva000681FB(a0);
	return false;
}

class Rva00068061NullTarget
{
public:
	void rva00068061(Int a0);
};

class Rva00091FABNullForwarder
{
public:
	void rva00091FAB(Int a0);
private:
	char m_lead[0x14];
	Rva00068061NullTarget *m_member;
};

// vtable 0x00BC80A0#27
void Rva00091FABNullForwarder::rva00091FAB(Int a0)
{
	if (m_member)
		m_member->rva00068061(a0);
}

class Rva0019C0A0NullTarget
{
public:
	Int rva0019C0A0();
};

class Rva0017FEC1NullForwarder
{
public:
	Int rva0017FEC1();
private:
	char m_lead[0x14];
	Rva0019C0A0NullTarget *m_member;
};

// vtable 0x00BD4F50#14
Int Rva0017FEC1NullForwarder::rva0017FEC1()
{
	if (m_member)
		return m_member->rva0019C0A0();
	return 0;
}

class Rva00149F20NullTarget
{
public:
	Int rva00149F20();
};

class Rva0018036CNullForwarder
{
public:
	Int rva0018036C();
private:
	char m_lead[0x14];
	Rva00149F20NullTarget *m_member;
};

// vtable 0x00BD4F90#14
Int Rva0018036CNullForwarder::rva0018036C()
{
	if (m_member)
		return m_member->rva00149F20();
	return 0;
}

class Rva001A3930NullTarget
{
public:
	Int rva001A3930();
};

class Rva00180AA6NullForwarder
{
public:
	Int rva00180AA6();
private:
	char m_lead[0x14];
	Rva001A3930NullTarget *m_member;
};

// vtable 0x00BD5050#14
Int Rva00180AA6NullForwarder::rva00180AA6()
{
	if (m_member)
		return m_member->rva001A3930();
	return 0;
}

class Rva001E11F8NullTarget
{
public:
	void rva001E11F8(Int a0, Int a1);
};

class Rva001E129BNullForwarder
{
public:
	void rva001E129B(Int a0, Int a1);
private:
	char m_lead[0x148];
	Rva001E11F8NullTarget *m_member;
};

// vtable 0x00BDD8F4#3
void Rva001E129BNullForwarder::rva001E129B(Int a0, Int a1)
{
	if (m_member)
		m_member->rva001E11F8(a0, a1);
}

class Rva001EB3D1NullTarget
{
public:
	void rva001EB3D1();
};

class Rva001EB722NullForwarder
{
public:
	void rva001EB722();
private:
	char m_lead[0xC];
	Rva001EB3D1NullTarget *m_member;
};

// vtable 0x00BDF228#9
void Rva001EB722NullForwarder::rva001EB722()
{
	if (m_member)
		m_member->rva001EB3D1();
}

class Rva002CAC6ENullTarget
{
public:
	void rva002CAC6E(Int a0, Int a1);
};

class Rva001F01B9NullForwarder
{
public:
	void rva001F01B9(Int a0, Int a1);
private:
	char m_lead[0x4];
	Rva002CAC6ENullTarget *m_member;
};

// vtable 0x00BE09E8#4
void Rva001F01B9NullForwarder::rva001F01B9(Int a0, Int a1)
{
	if (m_member)
		m_member->rva002CAC6E(a0, a1);
}

class Rva004D1616NullTarget
{
public:
	void rva004D1616(Int a0);
};
class ConnectionManager
{
public:
	void initTransport();
};
class Rva004CF113NullTarget
{
public:
	void rva004CF113(Int a0);
};

// Network (vtable 0x00BF6040): WorldBuilder's Network.cpp:68-71 names these
// three null-checked forwards to the connection manager (m_pConMgr, +0xC)
// ParseUserList and the two InitTransport overloads.
class Network
{
public:
	void ParseUserList(Int a0);
	void InitTransport();
	void InitTransport(Int a0);
private:
	char m_lead[0xC];
	void *m_pConMgr;
};

// vtable 0x00BF6040#17
void Network::ParseUserList(Int a0)
{
	if (m_pConMgr)
		((Rva004D1616NullTarget *)m_pConMgr)->rva004D1616(a0);
}

// vtable 0x00BF6040#20
void Network::InitTransport()
{
	if (m_pConMgr)
		((ConnectionManager *)m_pConMgr)->initTransport();
}

// vtable 0x00BF6040#19
void Network::InitTransport(Int a0)
{
	if (m_pConMgr)
		((Rva004CF113NullTarget *)m_pConMgr)->rva004CF113(a0);
}

class Rva004CFC81NullTarget
{
public:
	Int rva004CFC81();
};

class Rva0025DC17NullForwarder
{
public:
	Int rva0025DC17();
private:
	char m_lead[0xC];
	Rva004CFC81NullTarget *m_member;
};

// vtable 0x00BF6040#23
Int Rva0025DC17NullForwarder::rva0025DC17()
{
	if (m_member)
		return m_member->rva004CFC81();
	return 0;
}

class Rva004CF940NullTarget
{
public:
	void rva004CF940(Int a0);
};

class Rva0025DC5ENullForwarder
{
public:
	void rva0025DC5E(Int a0);
private:
	char m_lead[0xC];
	Rva004CF940NullTarget *m_member;
};

// vtable 0x00BF6040#35
void Rva0025DC5ENullForwarder::rva0025DC5E(Int a0)
{
	if (m_member)
		m_member->rva004CF940(a0);
}

class Rva004D02F6NullTarget
{
public:
	void rva004D02F6();
};

class Rva0025DC6DNullForwarder
{
public:
	void rva0025DC6D();
private:
	char m_lead[0xC];
	Rva004D02F6NullTarget *m_member;
};

// vtable 0x00BF6040#36
void Rva0025DC6DNullForwarder::rva0025DC6D()
{
	if (m_member)
		m_member->rva004D02F6();
}

class Rva004CF3B2NullTarget
{
public:
	Int rva004CF3B2();
};

class Rva0025DCE2NullForwarder
{
public:
	Int rva0025DCE2();
private:
	char m_lead[0xC];
	Rva004CF3B2NullTarget *m_member;
};

// vtable 0x00BF6040#44
Int Rva0025DCE2NullForwarder::rva0025DCE2()
{
	if (m_member)
		return m_member->rva004CF3B2();
	return 0;
}

class Rva004CF926NullTarget
{
public:
	Int rva004CF926();
};

class Rva0025DCF1NullForwarder
{
public:
	Int rva0025DCF1();
private:
	char m_lead[0xC];
	Rva004CF926NullTarget *m_member;
};

// vtable 0x00BF6040#45
Int Rva0025DCF1NullForwarder::rva0025DCF1()
{
	if (m_member)
		return m_member->rva004CF926();
	return -1;
}

class Rva004CF906NullTarget
{
public:
	Int rva004CF906();
};

class Rva0025DD01NullForwarder
{
public:
	Int rva0025DD01();
private:
	char m_lead[0xC];
	Rva004CF906NullTarget *m_member;
};

// vtable 0x00BF6040#46
Int Rva0025DD01NullForwarder::rva0025DD01()
{
	if (m_member)
		return m_member->rva004CF906();
	return 0x31;
}

class Rva004CF0CDNullTarget
{
public:
	Bool rva004CF0CD(Int a0);
};

class Rva0025DEBBNullForwarder
{
public:
	Bool rva0025DEBB(Int a0);
private:
	char m_lead[0xC];
	Rva004CF0CDNullTarget *m_member;
};

// vtable 0x00BF6040#64
Bool Rva0025DEBBNullForwarder::rva0025DEBB(Int a0)
{
	if (m_member)
		return m_member->rva004CF0CD(a0);
	return false;
}

class Rva004CEF58NullTarget
{
public:
	Bool rva004CEF58(Int a0);
};

class Rva0025DECCNullForwarder
{
public:
	Bool rva0025DECC(Int a0);
private:
	char m_lead[0xC];
	Rva004CEF58NullTarget *m_member;
};

// vtable 0x00BF6040#65
Bool Rva0025DECCNullForwarder::rva0025DECC(Int a0)
{
	if (m_member)
		return m_member->rva004CEF58(a0);
	return false;
}

class Rva004D00BBNullTarget
{
public:
	void rva004D00BB(Int a0);
};

class Rva0025E27FNullForwarder
{
public:
	void rva0025E27F(Int a0);
private:
	char m_lead[0xC];
	Rva004D00BBNullTarget *m_member;
};

// vtable 0x00BF6040#39
void Rva0025E27FNullForwarder::rva0025E27F(Int a0)
{
	if (m_member)
		m_member->rva004D00BB(a0);
}

class Rva000B3FD0NullTarget
{
public:
	void rva000B3FD0();
};

class Rva0035BD00NullForwarder
{
public:
	void rva0035BD00();
private:
	char m_lead[0x64];
	Rva000B3FD0NullTarget *m_member;
};

// vtable 0x00C16208#1
void Rva0035BD00NullForwarder::rva0035BD00()
{
	if (m_member)
		m_member->rva000B3FD0();
}
