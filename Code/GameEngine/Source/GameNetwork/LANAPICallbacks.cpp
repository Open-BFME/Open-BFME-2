// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O1
//
// LANAPI callbacks of the vtable 0x0083E680, Zero Hour's
// GameNetwork/LANAPICallbacks.cpp.
//
// LANAPI::OnPlayerLeave, retail 0x0024A0C7 (177 bytes), slot 37 (dispatched
// at +0x94 by RequestGameLeave). Zero Hour's body without the preferences
// save: out of the lobby, with a current game that is not in progress (+0x11),
// a leave by our own name (m_name +0x14) hands off to the LAN menu at VA
// 0x00E03354 (its 0x00444E8A, rowed under the class name GameEngine) or, with
// no menu, pops the shell (0x0035BEC7) and sets LANbuttonPushed -- the
// OnHostLeave pattern (LANAPILobbyMenuForwarders.cpp). Anyone else leaving a
// game we host (slot-0 address +0x114 equal to the local address, vslot 64)
// forces a resend (m_lastResendTime +0x3C), refreshes the slot list (the rowed
// 0x00248D84) and re-requests the game options through vslot 26 with a public
// flag and a zero address.

typedef int Int;
typedef bool Bool;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;

#include "unicode_string.h"

struct BfmeNetAddress
{
	Bool Rva00248CBF( const BfmeNetAddress *other ) const;

	UnsignedInt m_ip;
	UnsignedShort m_port;
};

class LANGameInfo
{
public:
	Bool isGameInProgress( void ) const { return m_inProgress; }
	const BfmeNetAddress *getHostAddress( void ) const { return &m_hostAddress; }

private:
	UnsignedByte m_pre11[0x11];
	Bool m_inProgress;				// +0x11
	UnsignedByte m_pre114[0x114 - 0x12];
	BfmeNetAddress m_hostAddress;			// +0x114, slot 0's address
};

class Shell
{
public:
	void rva0035BEC7( void );
};
extern Shell *TheShell;
extern Bool LANbuttonPushed;

struct Rva004469D1Receiver;
extern Rva004469D1Receiver *g_Va00E03354;

class GameEngine
{
public:
	void rva00444E8A( void );
};

void Rva00248D84Enable( void );

#define BFME_VSLOT(n) virtual void slot##n( void ) = 0;

class LANAPI
{
public:
	BFME_VSLOT(00) BFME_VSLOT(01) BFME_VSLOT(02) BFME_VSLOT(03) BFME_VSLOT(04)
	BFME_VSLOT(05) BFME_VSLOT(06) BFME_VSLOT(07) BFME_VSLOT(08) BFME_VSLOT(09)
	BFME_VSLOT(10) BFME_VSLOT(11) BFME_VSLOT(12) BFME_VSLOT(13) BFME_VSLOT(14)
	BFME_VSLOT(15) BFME_VSLOT(16) BFME_VSLOT(17) BFME_VSLOT(18) BFME_VSLOT(19)
	BFME_VSLOT(20) BFME_VSLOT(21) BFME_VSLOT(22) BFME_VSLOT(23) BFME_VSLOT(24)
	BFME_VSLOT(25)
	virtual void rva004497EC( Bool isPublic, BfmeNetAddress *ip ) = 0;
	BFME_VSLOT(27) BFME_VSLOT(28) BFME_VSLOT(29)
	BFME_VSLOT(30) BFME_VSLOT(31) BFME_VSLOT(32) BFME_VSLOT(33) BFME_VSLOT(34)
	BFME_VSLOT(35) BFME_VSLOT(36)
	virtual void OnPlayerLeave( UnicodeString player );
	BFME_VSLOT(38) BFME_VSLOT(39)
	BFME_VSLOT(40) BFME_VSLOT(41) BFME_VSLOT(42) BFME_VSLOT(43) BFME_VSLOT(44)
	BFME_VSLOT(45) BFME_VSLOT(46) BFME_VSLOT(47) BFME_VSLOT(48) BFME_VSLOT(49)
	BFME_VSLOT(50) BFME_VSLOT(51) BFME_VSLOT(52) BFME_VSLOT(53) BFME_VSLOT(54)
	BFME_VSLOT(55) BFME_VSLOT(56) BFME_VSLOT(57) BFME_VSLOT(58) BFME_VSLOT(59)
	BFME_VSLOT(60) BFME_VSLOT(61) BFME_VSLOT(62) BFME_VSLOT(63)
	virtual BfmeNetAddress *getLocalAddress( void ) = 0;

protected:
	UnsignedByte m_pre14[0x14 - 4];
	UnicodeString m_name;				// +0x14
	UnsignedByte m_pre3C[0x3C - 0x18];
	UnsignedInt m_lastResendTime;			// +0x3C
	UnsignedByte m_pre41[0x41 - 0x40];
	Bool m_inLobby;					// +0x41
	LANGameInfo *m_currentGame;			// +0x44
};

#undef BFME_VSLOT

void LANAPI::OnPlayerLeave( UnicodeString player )
{
	LANGameInfo *game;
	if( m_inLobby || ( game = m_currentGame ) == 0 || game->isGameInProgress() )
		return;

	if( m_name.compare( player ) == 0 )
	{
		if( !g_Va00E03354 )
		{
			TheShell->rva0035BEC7();
			LANbuttonPushed = true;
		}
		else
		{
			((GameEngine *)g_Va00E03354)->rva00444E8A();
		}
	}
	else
	{
		const BfmeNetAddress *host = game->getHostAddress();
		if( host->Rva00248CBF( getLocalAddress() ) )
		{
			m_lastResendTime = 0;
			Rva00248D84Enable();
			BfmeNetAddress noAddress;
			noAddress.m_ip = 0;
			noAddress.m_port = 0;
			rva004497EC( true, &noAddress );
		}
	}
}
