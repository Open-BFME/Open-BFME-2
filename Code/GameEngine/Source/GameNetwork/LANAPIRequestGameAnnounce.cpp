// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs-c- /O1
//
// Retail 0x0044A214, 283 bytes: LANAPI vtable 0x0083E680 slot 28, the slot
// before RequestSetName (slot 29) where Zero Hour's LANAPIInterface puts
// RequestGameAnnounce. Ported from BFME 1's LANAPI::RequestGameAnnounce
// (LANAPISendPath.cpp, retail 0x00685FC0): a host, or the packet router of a
// game in progress, of a current game that is not direct-connect fills a
// type-1 announce, serializes the game into the options at +0x42 (0x186
// bytes) with the unrowed writer 0x00447CA9 (BFME 1's writeLANGameInfo),
// copies the game's name (LANGameInfo vslot 23) to +0x1E, its in-progress
// (+0x11) and direct-connect (+0xF68) flags to +0x40 and +0x41, and sends it.
// BFME 2 differences from the donor: the host test calls the rowed address
// compare 0x00248CBF on the game's host address (+0x114) and the local
// address (vslot 64), and 16 bytes from the game at +0xCC are copied into
// the message tail at +0x1C8 before sending.

typedef int Int;
typedef bool Bool;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned short WideChar;

extern "C" __declspec(dllimport) WideChar * __cdecl wcsncpy(
	WideChar *, const WideChar *, unsigned int );
extern "C" void * __cdecl memcpy( void *, const void *, unsigned int );
#pragma function(memcpy)

class UnicodeStringData
{
public:
	UnsignedByte m_prefix[8];
	WideChar m_data[1];
};

#include "unicode_string.h"

enum
{
	g_lanGameNameLength = 16,
	g_lanMaxOptionsLength = 0x186
};

struct BfmeNetAddress
{
	Bool Rva00248CBF( const BfmeNetAddress *other ) const;
	UnsignedInt ip;
	UnsignedShort port;
};

template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap( char (*)[N] ) = 0;
};
template <> class VSlots<0>
{
};

class LANGameInfo : public VSlots<23>
{
public:
	virtual UnicodeString getName( void ) = 0;

	UnsignedByte m_pre11[0x11 - 4];
	Bool m_inProgress;				// +0x11
	UnsignedByte m_preCC[0xCC - 0x12];
	UnsignedByte m_bfmeCC[16];		// +0xCC
	UnsignedByte m_pre114[0x114 - 0xDC];
	BfmeNetAddress m_hostAddress;	// +0x114
	UnsignedByte m_preF68[0xF68 - 0x11C];
	Bool m_isDirectConnect;			// +0xF68
};

struct LANMessage
{
	Int LANMessageType;
	UnsignedByte m_header[0x1E - 4];
	WideChar gameName[g_lanGameNameLength + 1];
	Bool inProgress;
	Bool isDirectConnect;
	char options[g_lanMaxOptionsLength];
	UnsignedByte m_bfmeTail[16];
};

class NetworkInterface : public VSlots<43>
{
public:
	virtual Bool isPacketRouter( void ) = 0;
};

extern NetworkInterface *TheNetwork;

void Rva00447CA9( LANGameInfo *game, char *buffer, Int size );

class LANAPI : public VSlots<28>
{
public:
	virtual void RequestGameAnnounce( void );
	virtual void slot29( void ) = 0;
	virtual void slot30( void ) = 0;
	virtual void slot31( void ) = 0;
	virtual void slot32( void ) = 0;
	virtual void slot33( void ) = 0;
	virtual void slot34( void ) = 0;
	virtual void slot35( void ) = 0;
	virtual void slot36( void ) = 0;
	virtual void slot37( void ) = 0;
	virtual void slot38( void ) = 0;
	virtual void slot39( void ) = 0;
	virtual void slot40( void ) = 0;
	virtual void slot41( void ) = 0;
	virtual void slot42( void ) = 0;
	virtual void slot43( void ) = 0;
	virtual void slot44( void ) = 0;
	virtual void slot45( void ) = 0;
	virtual void slot46( void ) = 0;
	virtual void slot47( void ) = 0;
	virtual void slot48( void ) = 0;
	virtual void slot49( void ) = 0;
	virtual void slot50( void ) = 0;
	virtual void slot51( void ) = 0;
	virtual void slot52( void ) = 0;
	virtual void slot53( void ) = 0;
	virtual void slot54( void ) = 0;
	virtual void slot55( void ) = 0;
	virtual void slot56( void ) = 0;
	virtual void fillInLANMessage( LANMessage *msg ) = 0;
	virtual void slot58( void ) = 0;
	virtual void slot59( void ) = 0;
	virtual void slot60( void ) = 0;
	virtual void slot61( void ) = 0;
	virtual void slot62( void ) = 0;
	virtual void slot63( void ) = 0;
	virtual BfmeNetAddress *slot64( void ) = 0;
	void Rva004495A2( LANMessage *msg, UnsignedInt address );

protected:
	UnsignedByte m_pre44[0x44 - 4];
	LANGameInfo *m_currentGame;
};

void LANAPI::RequestGameAnnounce( void )
{
	// In game - are we a game host?
	if( m_currentGame && !m_currentGame->m_isDirectConnect )
	{
		BfmeNetAddress *host = &m_currentGame->m_hostAddress;

		// if we are in game we should reply if we are the packet router
		if( host->Rva00248CBF( slot64() )
			|| ( m_currentGame->m_inProgress && TheNetwork && TheNetwork->isPacketRouter() ) )
		{
			LANMessage reply;
			fillInLANMessage( &reply );
			reply.LANMessageType = 1;

			Rva00447CA9( m_currentGame, reply.options, g_lanMaxOptionsLength );
			wcsncpy( reply.gameName, m_currentGame->getName().str(), g_lanGameNameLength );
			reply.gameName[g_lanGameNameLength] = 0;
			reply.inProgress = m_currentGame->m_inProgress;
			reply.isDirectConnect = m_currentGame->m_isDirectConnect;
			memcpy( reply.m_bfmeTail, m_currentGame->m_bfmeCC, sizeof( reply.m_bfmeTail ) );

			Rva004495A2( &reply, 0 );
		}
	}
}
