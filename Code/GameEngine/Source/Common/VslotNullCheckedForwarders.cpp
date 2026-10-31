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

// Real owners of the forwarders' targets, under their ledger names.
class Drawable;
class Transport;
struct Coord3D;
struct BuffInfoView;
class TBuff;
class W3DTreeBuffer { public: Bool rva000EA644(void *firstValue); };		// 0x000EA644
class Rva000680B3Host { public: void rva000680B3(); };			// 0x000680B3
class Rva000664F4
{
public:
	TBuff *rva0006819B(Drawable *firstValue, const BuffInfoView *secondValue);	// 0x0006819B
	Bool rva000681AF(void *firstValue, const Coord3D *secondValue);		// 0x000681AF
	Bool rva000681D3(unsigned int firstValue, Int secondValue);			// 0x000681D3
	Bool rva000681E7(Int firstValue, Bool secondValue);				// 0x000681E7
	Bool rva000681FB(void *firstValue);					// 0x000681FB
	void rva000682E1(Int firstValue);					// 0x000682E1
};
class Gen009794F0 { public: Int handle(); };				// 0x0019C0A0
class Rva00149F20Holder { public: Int get() const; };			// 0x00149F20
class Rva001E11F8 { public: void rva001E11F8(Int firstValue, Int secondValue); };	// 0x001E11F8
class Rva001EB3D1 { public: void rva001EB3D1(); };			// 0x001EB3D1
class Rva002CA9CA { public: void rva002CAC6E(Int firstValue, Int secondValue); };	// 0x002CAC6E
class Rva004CFC81 { public: unsigned int rva004CFC81() const; };	// 0x004CFC81
class BFMEConnectionManager
{
public:
	unsigned char rva004CEF58(Int firstValue);				// 0x004CEF58
	int isPlayerSlotActive(int slot);				// 0x004CF0CD
	void attachTransport(Transport *transport);			// 0x004CF113
};


// rowed as ?setColor@Shadow@@QAEXH@Z (Shadow_setOpacity.cpp)
class Shadow
{
public:
	void setColor(Int firstValue);
};

class Rva000B31B9NullForwarder
{
public:
	void rva000B31B9(Int firstValue);
private:
	char m_lead[0x1D4];
	Shadow *m_member;
};

// vtable 0x00BCBC40#26
void Rva000B31B9NullForwarder::rva000B31B9(Int firstValue)
{
	if (m_member)
		m_member->setColor(firstValue);
}

class Rva0006820FNullForwarder
{
public:
	Bool rva0006820F(Int firstValue);
private:
	char m_lead[0x3850];
	W3DTreeBuffer *m_member;
};

class Rva00091E38NullForwarder
{
public:
	void rva00091E38();
private:
	char m_lead[0x14];
	Rva000680B3Host *m_member;
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
	void rva00068283(Int firstValue);
};

class Rva00091EDDNullForwarder
{
public:
	void rva00091EDD(Int firstValue);
private:
	char m_lead[0x14];
	Rva00068283NullTarget *m_member;
};

// vtable 0x00BC80A0#22
void Rva00091EDDNullForwarder::rva00091EDD(Int firstValue)
{
	if (m_member)
		m_member->rva00068283(firstValue);
}

class Rva00091F2ANullForwarder
{
public:
	Int rva00091F2A(Int firstValue, Int secondValue);
private:
	char m_lead[0x14];
	Rva000664F4 *m_member;
};

// vtable 0x00BC80A0#24
Int Rva00091F2ANullForwarder::rva00091F2A(Int firstValue, Int secondValue)
{
	if (m_member)
		return (Int)m_member->rva0006819B((Drawable *)firstValue, (const BuffInfoView *)secondValue);
	return 0;
}

class Rva00091F51NullForwarder
{
public:
	Bool rva00091F51(Int firstValue, Int secondValue);
private:
	char m_lead[0x14];
	Rva000664F4 *m_member;
};

// vtable 0x00BC80A0#28
Bool Rva00091F51NullForwarder::rva00091F51(Int firstValue, Int secondValue)
{
	if (m_member)
		return m_member->rva000681AF((void *)firstValue, (const Coord3D *)secondValue);
	return false;
}

class Rva00091F62NullForwarder
{
public:
	Bool rva00091F62(Int firstValue, Int secondValue);
private:
	char m_lead[0x14];
	Rva000664F4 *m_member;
};

// vtable 0x00BC80A0#29
Bool Rva00091F62NullForwarder::rva00091F62(Int firstValue, Int secondValue)
{
	if (m_member)
		return m_member->rva000681D3((unsigned int)firstValue, secondValue);
	return false;
}

class Rva00091F73NullForwarder
{
public:
	Bool rva00091F73(Int firstValue, Bool secondValue);
private:
	char m_lead[0x14];
	Rva000664F4 *m_member;
};

// vtable 0x00BC80A0#30
Bool Rva00091F73NullForwarder::rva00091F73(Int firstValue, Bool secondValue)
{
	if (m_member)
		return m_member->rva000681E7(firstValue, secondValue);
	return false;
}

class Rva00091F84NullForwarder
{
public:
	Bool rva00091F84(Int firstValue);
private:
	char m_lead[0x14];
	Rva000664F4 *m_member;
};

// vtable 0x00BC80A0#31
Bool Rva00091F84NullForwarder::rva00091F84(Int firstValue)
{
	if (m_member)
		return m_member->rva000681FB((void *)firstValue);
	return false;
}

class Rva00068061NullTarget
{
public:
	void rva00068061(Int firstValue);
};

class Rva00091FABNullForwarder
{
public:
	void rva00091FAB(Int firstValue);
private:
	char m_lead[0x14];
	Rva00068061NullTarget *m_member;
};

// vtable 0x00BC80A0#27
void Rva00091FABNullForwarder::rva00091FAB(Int firstValue)
{
	if (m_member)
		m_member->rva00068061(firstValue);
}

class Rva0017FEC1NullForwarder
{
public:
	Int rva0017FEC1();
private:
	char m_lead[0x14];
	Gen009794F0 *m_member;
};

// vtable 0x00BD4F50#14
Int Rva0017FEC1NullForwarder::rva0017FEC1()
{
	if (m_member)
		return m_member->handle();
	return 0;
}

class Rva0018036CNullForwarder
{
public:
	Int rva0018036C();
private:
	char m_lead[0x14];
	Rva00149F20Holder *m_member;
};

// vtable 0x00BD4F90#14
Int Rva0018036CNullForwarder::rva0018036C()
{
	if (m_member)
		return m_member->get();
	return 0;
}

// rowed as ?rva001A3930@AggregateDefClass@@QBEHXZ (AggregateDefRva001A3930.cpp)
class AggregateDefClass
{
public:
	Int rva001A3930() const;
};

class Rva00180AA6NullForwarder
{
public:
	Int rva00180AA6();
private:
	char m_lead[0x14];
	AggregateDefClass *m_member;
};

// vtable 0x00BD5050#14
Int Rva00180AA6NullForwarder::rva00180AA6()
{
	if (m_member)
		return m_member->rva001A3930();
	return 0;
}

class Rva001E129BNullForwarder
{
public:
	void rva001E129B(Int firstValue, Int secondValue);
private:
	char m_lead[0x148];
	Rva001E11F8 *m_member;
};

// vtable 0x00BDD8F4#3
void Rva001E129BNullForwarder::rva001E129B(Int firstValue, Int secondValue)
{
	if (m_member)
		m_member->rva001E11F8(firstValue, secondValue);
}

class Rva001EB722NullForwarder
{
public:
	void rva001EB722();
private:
	char m_lead[0xC];
	Rva001EB3D1 *m_member;
};

// vtable 0x00BDF228#9
void Rva001EB722NullForwarder::rva001EB722()
{
	if (m_member)
		m_member->rva001EB3D1();
}

class Rva001F01B9NullForwarder
{
public:
	void rva001F01B9(Int firstValue, Int secondValue);
private:
	char m_lead[0x4];
	Rva002CA9CA *m_member;
};

// vtable 0x00BE09E8#4
void Rva001F01B9NullForwarder::rva001F01B9(Int firstValue, Int secondValue)
{
	if (m_member)
		m_member->rva002CAC6E(firstValue, secondValue);
}

// ConnectionManager methods rowed under their real names (ConnectionManager*.cpp,
// ConnectionManagerLocalSlot.cpp) that the Network forwarders below reach.
class GameInfo;
class ConnectionManager
{
public:
	void parseUserList(const GameInfo *game);	// 0x004D1616
	void initTransport();
	unsigned int getPacketRouterSlot();	// 0x004CF3B2
	unsigned int getLocalPlayerID();	// 0x004CF906
	Int getNumPlayers();	// 0x004CF926
	void updateLoadProgress(Int progress);	// 0x004CF940
	void loadProgressComplete();	// 0x004D02F6
	void requestLeave(Int firstValue);	// 0x004D00BB
};

// Network (vtable 0x00BF6040): WorldBuilder's Network.cpp:68-71 names these
// three null-checked forwards to the connection manager (m_pConMgr, +0xC)
// ParseUserList and the two InitTransport overloads. Retail reaches them
// only through slots 17, 20 and 19 of that vftable, which
// BFME2NativeNetwork::construct installs: they are virtual, as quitGame and
// startNewSession are in Network.cpp, and the vptr sits at +0.
class Network
{
public:
	virtual void ParseUserList(Int firstValue);
	virtual void InitTransport();
	virtual void InitTransport(Int firstValue);
private:
	char m_lead04[0x8];
	void *m_pConMgr;
};

// vtable 0x00BF6040#17
void Network::ParseUserList(Int firstValue)
{
	if (m_pConMgr)
		((ConnectionManager *)m_pConMgr)->parseUserList((const GameInfo *)firstValue);
}

// vtable 0x00BF6040#20
void Network::InitTransport()
{
	if (m_pConMgr)
		((ConnectionManager *)m_pConMgr)->initTransport();
}

// vtable 0x00BF6040#19
void Network::InitTransport(Int firstValue)
{
	if (m_pConMgr)
		((BFMEConnectionManager *)m_pConMgr)->attachTransport((Transport *)firstValue);
}

class Rva0025DC17NullForwarder
{
public:
	Int rva0025DC17();
private:
	char m_lead[0xC];
	Rva004CFC81 *m_member;
};

// vtable 0x00BF6040#23
Int Rva0025DC17NullForwarder::rva0025DC17()
{
	if (m_member)
		return (Int)m_member->rva004CFC81();
	return 0;
}

class Rva0025DC5ENullForwarder
{
public:
	void rva0025DC5E(Int firstValue);
private:
	char m_lead[0xC];
	ConnectionManager *m_member;
};

// vtable 0x00BF6040#35
void Rva0025DC5ENullForwarder::rva0025DC5E(Int firstValue)
{
	if (m_member)
		m_member->updateLoadProgress(firstValue);
}

class Rva0025DC6DNullForwarder
{
public:
	void rva0025DC6D();
private:
	char m_lead[0xC];
	ConnectionManager *m_member;
};

// vtable 0x00BF6040#36
void Rva0025DC6DNullForwarder::rva0025DC6D()
{
	if (m_member)
		m_member->loadProgressComplete();
}

class Rva0025DCE2NullForwarder
{
public:
	Int rva0025DCE2();
private:
	char m_lead[0xC];
	ConnectionManager *m_member;
};

// vtable 0x00BF6040#44
Int Rva0025DCE2NullForwarder::rva0025DCE2()
{
	if (m_member)
		return m_member->getPacketRouterSlot();
	return 0;
}

class Rva0025DCF1NullForwarder
{
public:
	Int rva0025DCF1();
private:
	char m_lead[0xC];
	ConnectionManager *m_member;
};

// vtable 0x00BF6040#45
Int Rva0025DCF1NullForwarder::rva0025DCF1()
{
	if (m_member)
		return m_member->getNumPlayers();
	return -1;
}

class Rva0025DD01NullForwarder
{
public:
	Int rva0025DD01();
private:
	char m_lead[0xC];
	ConnectionManager *m_member;
};

// vtable 0x00BF6040#46
Int Rva0025DD01NullForwarder::rva0025DD01()
{
	if (m_member)
		return m_member->getLocalPlayerID();
	return 0x31;
}

class Rva0025DEBBNullForwarder
{
public:
	Bool rva0025DEBB(Int firstValue);
private:
	char m_lead[0xC];
	BFMEConnectionManager *m_member;
};

// vtable 0x00BF6040#64: retail tail-jumps, passing the callee's al through.
Bool Rva0025DEBBNullForwarder::rva0025DEBB(Int firstValue)
{
	if (m_member)
		return (m_member->*reinterpret_cast<Bool (BFMEConnectionManager::*)(Int)>(
			&BFMEConnectionManager::isPlayerSlotActive))(firstValue);
	return false;
}

class Rva0025DECCNullForwarder
{
public:
	unsigned char rva0025DECC(Int firstValue);
private:
	char m_lead[0xC];
	BFMEConnectionManager *m_member;
};

// vtable 0x00BF6040#65
unsigned char Rva0025DECCNullForwarder::rva0025DECC(Int firstValue)
{
	if (m_member)
		return m_member->rva004CEF58(firstValue);
	return 0;
}

class Rva0025E27FNullForwarder
{
public:
	void rva0025E27F(Int firstValue);
private:
	char m_lead[0xC];
	ConnectionManager *m_member;
};

// vtable 0x00BF6040#39
void Rva0025E27FNullForwarder::rva0025E27F(Int firstValue)
{
	if (m_member)
		m_member->requestLeave(firstValue);
}

// The ICF-folded empty body at 0x000B3FD0 (EmptyFoldTwins.cpp).
class Rva000B3FD0
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
	Rva000B3FD0 *m_member;
};

// vtable 0x00C16208#1
void Rva0035BD00NullForwarder::rva0035BD00()
{
	if (m_member)
		m_member->rva000B3FD0();
}

class Rva00091F3BNullForwarder
{
public:
	void rva00091F3B(void *p);
private:
	char m_lead[0x14];
	Rva000664F4 *m_member;
};

// vtable 0x00BC80A0#25: also skips a null argument.
void Rva00091F3BNullForwarder::rva00091F3B(void *p)
{
	if (m_member && p)
		m_member->rva000682E1((Int)p);
}
