// BFME1 Aries lobby record constructor, trimmed donor.
// Source: reference/open-bfme-1/Code/GameEngine/Source/GameNetwork/V2FeslAriesRecords.cpp
// b1 0x007F4EF0 158B; b2 0x00661920. Immediate-only drift is a DIR32 string
// literal (push 0x112b500 vs 0xce2d1c) the patcher fills, so the body below
// is the donor verbatim.

typedef __int64 FeslInt64;

#include "../../Include/GameNetwork/Rva007E8810Message.h"

// -------------------------------------------------------------------- lobby
class Rva007F4EF0Lobby
{
public:
	Rva007F4EF0Lobby( Rva007E8810Message *msg );
	int m_lid;
	int m_passing;
	int m_favoriteGames;
	int m_favoritePlayers;
	int m_maxGames;
	int m_numGames;
	char m_name[ 0x80 ];
	char m_locale[ 8 ];
};

Rva007F4EF0Lobby::Rva007F4EF0Lobby( Rva007E8810Message *msg )
{
	m_lid = msg->getInt( "LID", 0 );
	msg->getString( "NAME", m_name, 0x80 );
	m_passing = msg->getInt( "PASSING", 0 );
	m_favoriteGames = msg->getInt( "FAVORITE-GAMES", 0 );
	m_favoritePlayers = msg->getInt( "FAVORITE-PLAYERS", 0 );
	msg->getString( "LOCALE", m_locale, 8 );
	m_maxGames = msg->getInt( "MAX-GAMES", 0 );
	m_numGames = msg->getInt( "NUM-GAMES", 0 );
}
