// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x0044998E, 57 bytes. The LANAPI table points to this body at slot
// 63. Its list walk matches BFME1 LookupPlayer, with the target taking a full
// BfmeNetAddress pointer: it first compares IP and port, then treats port 0
// as an IP-only lookup. LANAPI head is +0x0C; LANPlayer next and address are
// +0x10 and +0x14. The address comparison helper is pinned at 0x248CBF.

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;
typedef unsigned char UnsignedByte;

struct BfmeNetAddress
{
	UnsignedInt ip;
	UnsignedShort port;
	Bool Rva00248CBF( const BfmeNetAddress *other ) const;
};

class LANPlayer
{
public:
	UnsignedByte m_prefix[0x10];
	LANPlayer *m_next;
	BfmeNetAddress m_address;
};

class LANAPI
{
public:
	virtual void slot00( void ) = 0;
	virtual void slot01( void ) = 0;
	virtual void slot02( void ) = 0;
	virtual void slot03( void ) = 0;
	virtual void slot04( void ) = 0;
	virtual void slot05( void ) = 0;
	virtual void slot06( void ) = 0;
	virtual void slot07( void ) = 0;
	virtual void slot08( void ) = 0;
	virtual void slot09( void ) = 0;
	virtual void slot10( void ) = 0;
	virtual void slot11( void ) = 0;
	virtual void slot12( void ) = 0;
	virtual void slot13( void ) = 0;
	virtual void slot14( void ) = 0;
	virtual void slot15( void ) = 0;
	virtual void slot16( void ) = 0;
	virtual void slot17( void ) = 0;
	virtual void slot18( void ) = 0;
	virtual void slot19( void ) = 0;
	virtual void slot20( void ) = 0;
	virtual void slot21( void ) = 0;
	virtual void slot22( void ) = 0;
	virtual void slot23( void ) = 0;
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
	virtual void slot56( void ) = 0;
	virtual void slot57( void ) = 0;
	virtual void slot58( void ) = 0;
	virtual void slot59( void ) = 0;
	virtual void slot60( void ) = 0;
	virtual void slot61( void ) = 0;
	virtual void slot62( void ) = 0;
	virtual LANPlayer *LookupPlayer( const BfmeNetAddress *address );

protected:
	UnsignedByte m_beforePlayers[0x0C - 4];
	LANPlayer *m_lobbyPlayers;
};

LANPlayer *LANAPI::LookupPlayer( const BfmeNetAddress *address )
{
	LANPlayer *player = m_lobbyPlayers;
	if( player )
	{
		do
		{
			if( player->m_address.Rva00248CBF( address ) ||
				( address->port == 0 && address->ip == player->m_address.ip ) )
				break;
			player = player->m_next;
		} while( player );
	}
	return player;
}
