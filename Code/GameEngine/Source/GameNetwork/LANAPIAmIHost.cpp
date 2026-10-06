// cl: /DNDEBUG /MD /EHsc /O1
//
// Three small LANAPI virtuals of the vtable 0x0083E680 that Ghidra left
// without a function entry (each is reached only through its slot):
//
// LANAPI::LookupGameByListOffset, retail 0x004498F0 (35 bytes), slot 50 after
// the rowed LookupGame (slot 49), Zero Hour's slot order. Zero Hour's body:
// walk the game list (+0x10) through LANGameInfo's next link (+0xF5C).
//
// LANAPI::AmIHost, retail 0x004499FF (42 bytes), slot 54 between the
// SetLocalIP overloads (52, 53) and GetMyName (55), Zero Hour's order. As in
// BFME 1 (LANAPILocalAddress.cpp) the result fills eax (33 C0 40), so it is
// an Int: true when the current game's slot-0 address (+0x114) equals the
// local address (vslot 64) by the rowed BfmeNetAddress compare 0x00248CBF.
// Its false return is the tail 0x00449A26 (33 C0 C3) both je's reach; that
// tail was rowed on its own as ?Rva00449A26Get@@YAHXZ (ConstZeroGetters.cpp)
// and is retired into this row.
//
// Slot 60, retail 0x00449B79 (22 bytes): whether the local address (vslot 64)
// is the loopback 127.0.0.1. BFME 1 has the same body (its descriptive name
// isLoopbackAddress); Zero Hour has no counterpart, so the name is the address.

typedef int Int;
typedef bool Bool;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;

struct BfmeNetAddress
{
	Bool Rva00248CBF( const BfmeNetAddress *other ) const;

	UnsignedInt m_ip;
	UnsignedShort m_port;
};

class LANGameInfo
{
public:
	const BfmeNetAddress *getHostAddress( void ) const { return &m_hostAddress; }
	LANGameInfo *getNext( void ) { return m_next; }

private:
	UnsignedByte m_pre114[0x114];
	BfmeNetAddress m_hostAddress;			// +0x114, slot 0's address
	UnsignedByte m_preF5C[0xF5C - 0x11C];
	LANGameInfo *m_next;				// +0xF5C
};

#define BFME_VSLOT(n) virtual void slot##n( void ) = 0;

class LANAPI
{
public:
	BFME_VSLOT(00) BFME_VSLOT(01) BFME_VSLOT(02) BFME_VSLOT(03) BFME_VSLOT(04)
	BFME_VSLOT(05) BFME_VSLOT(06) BFME_VSLOT(07) BFME_VSLOT(08) BFME_VSLOT(09)
	BFME_VSLOT(10) BFME_VSLOT(11) BFME_VSLOT(12) BFME_VSLOT(13) BFME_VSLOT(14)
	BFME_VSLOT(15) BFME_VSLOT(16) BFME_VSLOT(17) BFME_VSLOT(18) BFME_VSLOT(19)
	BFME_VSLOT(20) BFME_VSLOT(21) BFME_VSLOT(22) BFME_VSLOT(23) BFME_VSLOT(24)
	BFME_VSLOT(25) BFME_VSLOT(26) BFME_VSLOT(27) BFME_VSLOT(28) BFME_VSLOT(29)
	BFME_VSLOT(30) BFME_VSLOT(31) BFME_VSLOT(32) BFME_VSLOT(33) BFME_VSLOT(34)
	BFME_VSLOT(35) BFME_VSLOT(36) BFME_VSLOT(37) BFME_VSLOT(38) BFME_VSLOT(39)
	BFME_VSLOT(40) BFME_VSLOT(41) BFME_VSLOT(42) BFME_VSLOT(43) BFME_VSLOT(44)
	BFME_VSLOT(45) BFME_VSLOT(46) BFME_VSLOT(47) BFME_VSLOT(48) BFME_VSLOT(49)
	virtual LANGameInfo *LookupGameByListOffset( Int offset );
	BFME_VSLOT(51) BFME_VSLOT(52) BFME_VSLOT(53)
	virtual Int AmIHost( void );
	BFME_VSLOT(55) BFME_VSLOT(56) BFME_VSLOT(57) BFME_VSLOT(58) BFME_VSLOT(59)
	virtual Bool rva00449B79( void );
	BFME_VSLOT(61) BFME_VSLOT(62) BFME_VSLOT(63)
	virtual BfmeNetAddress *getLocalAddress( void ) = 0;

protected:
	UnsignedByte m_pre10[0x10 - 4];
	LANGameInfo *m_games;				// +0x10
	UnsignedByte m_pre44[0x44 - 0x14];
	LANGameInfo *m_currentGame;			// +0x44
};

#undef BFME_VSLOT

LANGameInfo *LANAPI::LookupGameByListOffset( Int offset )
{
	LANGameInfo *theGame = m_games;

	if( offset < 0 )
		return 0;

	while( offset-- && theGame )
	{
		theGame = theGame->getNext();
	}

	return theGame;
}

Int LANAPI::AmIHost( void )
{
	if( m_currentGame && m_currentGame->getHostAddress()->Rva00248CBF( getLocalAddress() ) )
		return 1;
	return 0;
}

Bool LANAPI::rva00449B79( void )
{
	return getLocalAddress()->m_ip == 0x7F000001;
}
