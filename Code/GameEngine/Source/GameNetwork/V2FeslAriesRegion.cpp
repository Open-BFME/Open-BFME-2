// EA FESL Aries region records: the two bodies immediately preceding the
// lobby ctor (0x00661920) in game.dat.
// 0x00661870 30B = Rva007F4E20RegionCount (donor verbatim; NUM-REGIONS key
//   imm32 + {msg,int} shape prove it).
// 0x00661890 110B = Rva007F4E50Region (donor verbatim; RID key imm32 plus
//   {rid,games,players,name[0x80],locale[8]} layout prove it; hand-split of
//   the address cluster first misread its start as 0x006618B0 -- the true
//   prologue is the push-esi/push-edi pair at 0x00661890).
// The 27B single-int body at 0x00661900 is deliberately unclaimed (no donor
// class matches its shape). Callees pre-pinned, zero new pins.

typedef __int64 FeslInt64;

#include "../../Include/GameNetwork/Rva007E8810Message.h"

class Rva007F4E20RegionCount
{
public:
	Rva007F4E20RegionCount( Rva007E8810Message *msg );
	Rva007E8810Message *m_msg;
	int m_numRegions;
};

Rva007F4E20RegionCount::Rva007F4E20RegionCount( Rva007E8810Message *msg )
{
	m_msg = msg;
	m_numRegions = m_msg->getInt( "NUM-REGIONS", 0 );
}

class Rva007F4E50Region
{
public:
	Rva007F4E50Region( Rva007E8810Message *msg );
	int m_rid;
	int m_numGames;
	int m_numPlayers;
	char m_name[ 0x80 ];
	char m_locale[ 8 ];
};

Rva007F4E50Region::Rva007F4E50Region( Rva007E8810Message *msg )
{
	m_rid = msg->getInt( "RID", 0 );
	msg->getString( "NAME", m_name, 0x80 );
	msg->getString( "LOCALE", m_locale, 8 );
	m_numGames = msg->getInt( "NUM-GAMES", 0 );
	m_numPlayers = msg->getInt( "NUM-PLAYERS", 0 );
}
