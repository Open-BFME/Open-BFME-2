// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x00449A29, 88 bytes. The pointer table at 0x83E680 places this
// body in slot 14; the target body independently uses LANAPI offsets +0x41,
// +0x44 and +0x5C. It sends a type-0x11 LANMessage only on the transition to
// inactive while out of the lobby with a current game, then stores the new
// active flag. The send helper is the address-derived target helper pinned at
// 0x4495A2.

typedef int Int;
typedef bool Bool;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;

struct LANMessage
{
	Int type;
	unsigned char bytes[0x1D4];
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
	virtual void setIsActive( Bool active );
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
	virtual void fillInLANMessage( LANMessage *message ) = 0;

	void Rva004495A2( LANMessage *message, UnsignedInt address );

protected:
	unsigned char m_beforeLobby[0x41 - 4];
	Bool m_inLobby;
	unsigned char m_beforeGame[0x44 - 0x42];
	void *m_currentGame;
	unsigned char m_beforeActive[0x5C - 0x48];
	Bool m_isActive;
};

void LANAPI::setIsActive( Bool active )
{
	if( active != m_isActive )
	{
		if( !active && !m_inLobby && m_currentGame )
		{
			LANMessage message;
			fillInLANMessage( &message );
			message.type = 0x11;
			Rva004495A2( &message, 0 );
		}
	}
	m_isActive = active;
}
