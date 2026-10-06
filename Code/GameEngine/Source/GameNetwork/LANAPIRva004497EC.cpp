// cl: /DNDEBUG /MD /O1
//
// Retail 0x004497EC, 184 bytes: LANAPI vtable 0x0083E680 slot 26, between
// the game-options request (slot 25, rowed 0x0044A808) and slot 27. Ported
// from BFME 1's LANAPI::_bfme_requestSerializedGameInfo (LANAPILocalAddress
// .cpp, retail 0x00685000, the BFME-only slot after RequestGameOptions): an
// unused Bool and a destination address; without a current game (+0x44) it
// does nothing, else it fills a 0x1D8-byte message through vslot 57, types it
// 19, serializes the current game into its payload at +0x1E (0x186 bytes) with
// rowed 0x0044802D (BFME 1's fillCurrentLANGameInfo), sends it to the
// destination with rowed 0x004495A2, then finds the local slot -- the first
// of the game's eight 0x1D0-byte slots from +0x114 whose address equals the
// local address (vslot 64, rowed compare 0x00248CBF) -- and hands the local
// address, slot index and payload to vslot 46.
// BFME 2 differences from the donor: the slot test calls the rowed address
// compare instead of comparing ip and port inline.
typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;

struct BfmeNetAddress
{
	Bool Rva00248CBF( const BfmeNetAddress *other ) const;
	UnsignedInt ip;
	UnsignedShort port;
};

enum
{
	LAN_MAX_SLOTS = 8
};

struct LANGameSlotView
{
	BfmeNetAddress m_address;
	char m_tail[0x1D0 - sizeof( BfmeNetAddress )];
};

class LANGameInfo
{
public:
	char m_pre114[0x114];
	LANGameSlotView m_slots[LAN_MAX_SLOTS];
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

void Rva0044802D( char *buffer, Int size );

template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap( char (*)[N] ) = 0;
};
template <> class VSlots<0>
{
};

class LANAPI : public VSlots<26>
{
public:
	virtual void rva004497EC( Bool unused, BfmeNetAddress *destination );
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
	virtual void slot46( BfmeNetAddress *from, Int playerSlot, char *buffer,
		UnsignedInt size ) = 0;
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
	char m_pre44[0x44 - 4];
	LANGameInfo *m_currentGame;
};

void LANAPI::rva004497EC( Bool unused, BfmeNetAddress *destination )
{
	if( !m_currentGame )
		return;

	LANMessage message;
	fillInLANMessage( &message );
	message.m_type = 19;
	Rva0044802D( message.m_payload, sizeof( message.m_payload ) );
	Rva004495A2( &message, (UnsignedInt)destination );

	Int playerSlot;
	for( playerSlot = 0; playerSlot < LAN_MAX_SLOTS; ++playerSlot )
	{
		BfmeNetAddress *slotAddress = &m_currentGame->m_slots[playerSlot].m_address;
		if( slotAddress->Rva00248CBF( slot64() ) )
		{
			slot46( slot64(), playerSlot, message.m_payload,
				sizeof( message.m_payload ) );
			break;
		}
	}
}
