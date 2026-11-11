// cl: /DNDEBUG /MD /O1
//
// Retail 0x00449693, 169 bytes: LANAPI vtable 0x0083E680 slot 23, between
// RequestAccept (slot 19) and the game-start-timer request 0x00449745 (slot
// 24). It is Zero Hour's LANAPI::RequestGameStart with a BFME Bool argument:
// it bails in the lobby (+0x41), without a current game (+0x44), or when the
// game's host address at +0x114 differs from the local address (vslot 64
// getLocalAddress, rowed compare 0x00248CDD); else it builds a 0x1D8-byte message of type
// 14 (argument set) or 13, fills it through vslot 57, loads its payload from
// +0x1E with 0x0044802D, sends it with the rowed 0x004495A2, flushes the
// transport (+0x50, rowed 0x004D54C1) and calls vslot 43 (OnWOTRGameStart)
// or 42 (OnGameStart).
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

#include "../../Include/Common/Rva00248CDD.h"

#include <string.h>
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

#include "../../Include/GameNetwork/LANAPI.h"

extern LANAPI *TheLAN;

void GameInfoToByteBuffer( LANGameInfo *game, char *buffer, Int size );

void Rva0044802D( char *buffer, Int size )
{
	if( TheLAN->GetMyGame() && TheLAN->GetMyGame()->amIHost() )
		GameInfoToByteBuffer( TheLAN->GetMyGame(), buffer, size );
	else
		memset( buffer, 0, size );
}

void LANAPI::RequestGameStart( Bool arg )
{
	if( m_inLobby || !m_currentGame )
		return;
	Rva00248CDD *host = &m_currentGame->m_hostAddress;
	if( host->rva00248CDD( *reinterpret_cast<Rva00248CDD *>( getLocalAddress() ) ) )
		return;

	LANMessage msg;
	msg.m_type = arg ? 14 : 13;
	fillInLANMessage( &msg );
	Rva0044802D( msg.m_payload, sizeof( msg.m_payload ) );
	Rva004495A2( &msg, 0 );
	m_transport->update( 0 );
	if( arg )
		OnWOTRGameStart();
	else
		OnGameStart();
}
