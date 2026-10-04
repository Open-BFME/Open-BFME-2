// ?RequestGameLeave@LANAPI@@UAEXXZ
// partial score=0.98 date=2026-10-04
// ?RequestGameLeave@LANAPI@@UAEXXZ
// partial score=0.97 date=2026-09-29
// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?RequestGameLeave@LANAPI@@UAEXXZ, retail 0x0044A0CF, 325 bytes.
// BFME2 RequestGameLeave via BFME1 donor LANAPIRequestGameLeave.cpp retail 0x00687CE0.
// Evidence: slot 18 of 0x0083E680 plus type 8/6 via BfmeNetAddress compare at game+0x114
// plus wcsncpy gameName plus sendMessage 0 plus transport false plus OnPlayerLeave
// plus removeGame plus delete plus pending 3 plus timeGetTime.

typedef int Int;
typedef bool Bool;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef unsigned short WideChar;

extern "C" __declspec(dllimport) WideChar * __cdecl wcsncpy(
	WideChar *, const WideChar *, unsigned int );
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime( void );

extern "C" void _WriteBarrier( void );
extern "C" void _ReadWriteBarrier( void );
#pragma intrinsic( _WriteBarrier, _ReadWriteBarrier )

void __cdecl operator delete( void *memory );

template <typename T> class StringBase
{
	friend class UnicodeString;
private:
	StringBase( const StringBase<T> &other );
	void releaseBuffer( void );
	~StringBase() { releaseBuffer(); }
	void *m_data;
};

class UnicodeString : private StringBase<WideChar>
{
public:
	__forceinline UnicodeString( const UnicodeString &other )
		: StringBase<WideChar>( other ) {}
	~UnicodeString() {}
	const WideChar *str( void ) const
	{
		const StringBase<WideChar> *base = (const StringBase<WideChar> *)this;
		void *data = base->m_data;
		if( data )
			return (const WideChar *)((const char *)data + 8);
		_ReadWriteBarrier();
		return L"";
	}
};

struct BfmeNetAddress
{
	Bool Rva00248CBF( const BfmeNetAddress *other ) const;
	UnsignedInt m_ip;
	unsigned short m_port;
};

class LANGameInfo
{
public:
	virtual void *slot00( Bool flag ) = 0;
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
	virtual UnicodeString getName( void ) = 0;

	UnsignedByte m_beforeAddress[0x114 - 4];
	BfmeNetAddress m_address;
};

struct LANMessage
{
	Int type;
	UnsignedByte m_prefix[0x1E - 4];
	WideChar gameName[17];
	Bool accepted;
	UnsignedByte m_remainder[0x1D8 - 0x42];
};

class Transport
{
public:
	Bool Rva004D54C1( Bool active );
};

class LANPlayer
{
public:
	UnsignedByte m_pad[0x10];
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
	virtual void RequestGameLeave( void );
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
	virtual void OnPlayerLeave( UnicodeString name ) = 0;
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
	virtual void fillInLANMessage( LANMessage *message ) = 0;
	virtual void slot58( void ) = 0;
	virtual void slot59( void ) = 0;
	virtual void slot60( void ) = 0;
	virtual void slot61( void ) = 0;
	virtual void slot62( void ) = 0;
	virtual void slot63( void ) = 0;
	virtual BfmeNetAddress *localAddress( void ) = 0;
	void Rva004495A2( LANMessage *message, UnsignedInt address );
	void removeGame( LANGameInfo *game );

private:
	UnsignedByte m_beforePlayers[0x0C - 4];
	LANPlayer *m_lobbyPlayers;
	LANGameInfo *m_games;
	UnicodeString m_name;
	UnsignedByte m_afterName[0x28 - 0x18];
	UnsignedInt m_pendingAction;
	UnsignedInt m_expiration;
	UnsignedInt m_actionTimeout;
	BfmeNetAddress m_directConnectAddress;
	UnsignedByte m_beforeFlags[0x40 - 0x3C];
	Bool m_isInLANMenu;
	Bool m_inLobby;
	UnsignedByte m_beforeCurrentGame[0x44 - 0x42];
	LANGameInfo *m_currentGame;
	UnsignedByte m_beforeTransport[0x50 - 0x48];
	Transport *m_transport;
};

void LANAPI::RequestGameLeave( void )
{
	LANMessage message;

	if( m_currentGame != 0 )
	{
		BfmeNetAddress *gameAddr = &m_currentGame->m_address;
		BfmeNetAddress *local = localAddress();
		message.type = 8;
		if( !gameAddr->Rva00248CBF( local ) )
			message.type = 6;
	}
	else
	{
		message.type = 6;
	}

	fillInLANMessage( &message );

	LANGameInfo *game = m_currentGame;
	wcsncpy( message.gameName, game ? game->getName().str() : ( _WriteBarrier(), L"" ), 0x10 );
	message.gameName[0x10] = 0;

	Rva004495A2( &message, 0 );
	m_transport->Rva004D54C1( false );

	if( m_currentGame != 0 )
	{
		BfmeNetAddress *gameAddr = &m_currentGame->m_address;
		BfmeNetAddress *local = localAddress();
		if( gameAddr->Rva00248CBF( local ) )
		{
			OnPlayerLeave( m_name );
			removeGame( m_currentGame );
			LANGameInfo *cur = m_currentGame;
			void *memory;
			if( cur != 0 )
				memory = cur->slot00( false );
			else
				memory = 0;
			::operator delete( memory );
			m_currentGame = 0;
			m_inLobby = true;
			return;
		}
	}

	m_pendingAction = 3;
	m_expiration = timeGetTime() + m_actionTimeout;
}
