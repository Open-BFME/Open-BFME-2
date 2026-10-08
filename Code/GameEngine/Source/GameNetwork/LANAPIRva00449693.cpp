// cl: /DNDEBUG /MD /O1
//
// Retail 0x00449693, 169 bytes: LANAPI vtable 0x0083E680 slot 23, between
// RequestAccept (slot 19) and the game-start-timer request 0x00449745 (slot
// 24). It is Zero Hour's LANAPI::RequestGameStart with a BFME Bool argument:
// it bails in the lobby (+0x41), without a current game (+0x44), or when the
// game's host address at +0x114 differs from the local address (vslot 64,
// rowed compare 0x00248CDD); else it builds a 0x1D8-byte message of type
// 14 (argument set) or 13, fills it through vslot 57, loads its payload from
// +0x1E with 0x0044802D, sends it with the rowed 0x004495A2, flushes the
// transport (+0x50, rowed 0x004D54C1) and calls vslot 43 or 42.
//
// Retail 0x0044802D, 92 bytes: that cdecl (buffer, size) payload fill, its
// only caller. When TheLAN's current game (vslot 56) exists and is in game
// (rowed LANGameInfo 0x004477C7), the game is serialized into the buffer by
// the unrowed 812-byte writer 0x00447CA9, which takes the game, the buffer
// and its size; otherwise the buffer is cleared with memset.
// Names are address-derived: no donor body is known for either.
typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;

extern "C" void * __cdecl memset( void *, int, unsigned int );

class Rva00248CDD
{
public:
	Bool rva00248CDD( const Rva00248CDD &other ) const;
private:
	UnsignedInt m_key0;
	UnsignedShort m_key4;
};

#include "../../Include/GameNetwork/Transport.h"

class LANGameInfo
{
public:
	Bool amIHost( void ) const;
	char m_pre114[0x114];
	Rva00248CDD m_hostAddress;
};

#pragma pack(push, 1)
struct LANMessage
{
	UnsignedInt m_type;
	char m_pad[0x1E - 4];
	char m_payload[0x186];
	char m_rest[0x1D8 - 0x1A4];
};
#pragma pack(pop)

template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap( char (*)[N] ) = 0;
};
template <> class VSlots<0>
{
};

class LANAPI : public VSlots<23>
{
public:
	virtual void rva00449693( Bool arg );
	virtual void slot24( void ) = 0;
	virtual void slot25( void ) = 0;
	virtual void slot26( void ) = 0;
	virtual void slot27( void ) = 0;
	virtual void slot28( void ) = 0;
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
	virtual LANGameInfo *GetMyGame( void ) = 0;
	virtual void fillInLANMessage( LANMessage *msg ) = 0;
	virtual void slot58( void ) = 0;
	virtual void slot59( void ) = 0;
	virtual void slot60( void ) = 0;
	virtual void slot61( void ) = 0;
	virtual void slot62( void ) = 0;
	virtual void slot63( void ) = 0;
	virtual Rva00248CDD *slot64( void ) = 0;
	void Rva004495A2( LANMessage *msg, UnsignedInt flags );

protected:
	char m_pre41[0x41 - 4];
	Bool m_inLobby;
	char m_pad42[2];
	LANGameInfo *m_currentGame;
	char m_pre50[8];
	Transport *m_transport;
};

extern LANAPI *TheLAN;

void Rva00447CA9( LANGameInfo *game, char *buffer, Int size );

void Rva0044802D( char *buffer, Int size )
{
	if( TheLAN->GetMyGame() && TheLAN->GetMyGame()->amIHost() )
		Rva00447CA9( TheLAN->GetMyGame(), buffer, size );
	else
		memset( buffer, 0, size );
}

void LANAPI::rva00449693( Bool arg )
{
	if( m_inLobby || !m_currentGame )
		return;
	Rva00248CDD *host = &m_currentGame->m_hostAddress;
	if( host->rva00248CDD( *slot64() ) )
		return;

	LANMessage msg;
	msg.m_type = arg ? 14 : 13;
	fillInLANMessage( &msg );
	Rva0044802D( msg.m_payload, sizeof( msg.m_payload ) );
	Rva004495A2( &msg, 0 );
	m_transport->update( 0 );
	if( arg )
		slot43();
	else
		slot42();
}
