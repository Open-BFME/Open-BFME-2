// cl: /O1 /DNDEBUG /MD
//
// Vtable-slot bodies of the network object (vtable VA 0x00BF6040, class
// Rva0025E4CD after its destructor) that had no ledger owner, plus the one
// ConnectionManager forwarder two of them call. Each slot reads the
// ConnectionManager at +0x0C (the member Rva0025E4CDSlot47.cpp already calls
// ConnectionManager::getPlayerName through) and, when it is set, forwards to
// it or reads one of its fields. Field offsets follow the BFME2
// ConnectionManager view in reference/shims/connectionmanager; the object at
// ConnectionManager+0x12100 is the one ConnectionManagerCtor.cpp creates and
// initialises through DisconnectManager::init. Method names stay address
// derived: the bytes prove the hops, offsets and argument counts only.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class ConnectionManager;

class Rva0057429ADwordField
{
public:
	Int get() const;
};
class Rva0028A65EDwordField
{
public:
	Int get() const;
};
class Rva004E05E9DwordField
{
public:
	Int get() const;
};

class DisconnectManager
{
public:
	void rva004D3DF4(Int slot, ConnectionManager *conMgr);
private:
	char m_pad00[0x270];
public:
	Bool m_270;
};

// The 0x2000-byte per-slot records at ConnectionManager+0x24; the method the
// slot query calls is the ICF-folded `xor eax,eax; ret` at 0x000D43D0.
class Rva0025DE76Slot
{
public:
	Int rva000D43D0();
private:
	char m_pad[0x2000];
};

struct Rva0025DBDCPair
{
	UnsignedInt m_first;
	UnsignedInt m_second;
};

class ConnectionManager
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void rva0025DBAESlot(Bool flag, Int value);

	void rva004CF90D(Int slot);
	void rva004D0AA9(Int value);

	char m_pad04[0x20];
	Rva0025DE76Slot m_slots[9];			// +0x24
	char m_pad12024[0x12050 - 0x12024];
	Rva0025DBDCPair m_12050;			// +0x12050
	UnsignedInt m_12058;
	UnsignedInt m_frameCeiling;			// +0x1205C
	UnsignedInt m_playerLatestFrame[8];	// +0x12060
	char m_pad12080[0x12100 - 0x12080];
	DisconnectManager *m_12100;			// +0x12100
};

class GameLogic
{
public:
	void rva0023D201(Int a, Int b);
	UnsignedInt getFrame() const { return m_frame; }
private:
	char m_pad00[0x40];
	UnsignedInt m_frame; // +0x40
};
extern GameLogic *TheGameLogic;

class Rva0025E4CD
{
public:
	virtual ~Rva0025E4CD();

	void rva0025DBAE(Int value);
	void rva0025DBDC(const Rva0025DBDCPair &pair);
	Int rva0025DC7A();
	Int rva0025DC95();
	Int rva0025DCB0();
	Int rva0025DD25();
	Int rva0025DE5C();
	Int rva0025DE76(Int slot);
	Int rva0025DEA2(Int slot);
	void rva0025E20F(Int slot);
	void rva0025E28E();
private:
	char m_pad04[8];
	ConnectionManager *m_conMgr;	// +0x0C
	Int m_10;
};

// ConnectionManager+0x12100's 0x004D3DF4 with this manager, when that object exists.
void ConnectionManager::rva004CF90D(Int slot)
{
	if (m_12100)
		m_12100->rva004D3DF4(slot, this);
}

// vtable 0x00BF6040#15
void Rva0025E4CD::rva0025DBAE(Int value)
{
	if (m_conMgr)
		m_conMgr->rva0025DBAESlot(m_10 == 1, value);
}

// vtable 0x00BF6040#18
void Rva0025E4CD::rva0025DBDC(const Rva0025DBDCPair &pair)
{
	if (m_conMgr)
		m_conMgr->m_12050 = pair;
}

// vtable 0x00BF6040#40
Int Rva0025E4CD::rva0025DC7A()
{
	if (m_conMgr && m_conMgr->m_12100)
		return ((Rva0057429ADwordField *)m_conMgr->m_12100)->get();
	return 0;
}

// vtable 0x00BF6040#41
Int Rva0025E4CD::rva0025DC95()
{
	if (m_conMgr && m_conMgr->m_12100)
		return ((Rva0028A65EDwordField *)m_conMgr->m_12100)->get();
	return 0;
}

// vtable 0x00BF6040#42
Int Rva0025E4CD::rva0025DCB0()
{
	if (m_conMgr && m_conMgr->m_12100)
		return ((Rva004E05E9DwordField *)m_conMgr->m_12100)->get();
	return 0;
}

// vtable 0x00BF6040#52
Int Rva0025E4CD::rva0025DD25()
{
	if (m_conMgr)
		return (unsigned char)(m_conMgr->m_12100 ? m_conMgr->m_12100->m_270 : 0);
	return 0;
}

// vtable 0x00BF6040#59
Int Rva0025E4CD::rva0025DE5C()
{
	if (m_conMgr)
		return m_conMgr->m_frameCeiling - TheGameLogic->getFrame();
	return 0;
}

// vtable 0x00BF6040#61
Int Rva0025E4CD::rva0025DE76(Int slot)
{
	if (m_conMgr)
	{
		if (slot < 0 || slot >= 9)
			return -1;
		return m_conMgr->m_slots[slot].rva000D43D0();
	}
	return 0;
}

// vtable 0x00BF6040#62
Int Rva0025E4CD::rva0025DEA2(Int slot)
{
	if (m_conMgr)
		return m_conMgr->m_playerLatestFrame[slot];
	return 0;
}

// vtable 0x00BF6040#38
void Rva0025E4CD::rva0025E20F(Int slot)
{
	if (m_conMgr)
	{
		m_conMgr->rva004CF90D(slot);
		TheGameLogic->rva0023D201(slot, 2);
	}
}

// vtable 0x00BF6040#25
void Rva0025E4CD::rva0025E28E()
{
	if (m_conMgr)
		m_conMgr->rva004D0AA9(0);
}
