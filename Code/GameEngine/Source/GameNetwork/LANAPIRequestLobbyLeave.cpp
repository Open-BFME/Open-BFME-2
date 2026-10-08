// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x004498A4, 76 bytes. OnGameCreate at 0x00249430 dispatches
// vtable offset +0x78, and the pointer at the corresponding .rdata table
// entry is 0x008498A4. The body stores message type 7, calls the virtual
// helper at +0xE4, and reaches address-derived target helpers at 0x4495A2 and
// 0x4D54C1. The latter receives a null receiver and returns an ignored Bool. The message
// object extent/layout and both helper identities remain target-derived.

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;

struct LANMessage
{
	Int type;
	unsigned char bytes[0x1D4];
};

#include "../../Include/GameNetwork/Transport.h"

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
	virtual void RequestLobbyLeave( Bool forced );
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
	unsigned char m_beforeTransport[0x50 - 4];
	Transport *m_transport;
};

void LANAPI::RequestLobbyLeave( Bool forced )
{
	LANMessage message;
	message.type = 7;
	fillInLANMessage( &message );
	Rva004495A2( &message, 0 );

	if( forced )
		m_transport->update( 0 );
}
