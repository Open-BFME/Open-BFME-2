// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs-c-
//
// Retail 0x0044A32F, 144 bytes. The target body is the BFME1 LANAPI
// RequestAccept operation with a target Bool parameter: it exits when in the
// lobby or without a current game, fills a type-9 message, copies the current
// game's name, and sends it. The LANAPI message name begins at +0x1E and the
// accepted byte is at +0x40; LANGameInfo::getName is called through +0x5C.

typedef int Int;
typedef bool Bool;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef unsigned short WideChar;

extern "C" __declspec(dllimport) WideChar * __cdecl wcsncpy(
	WideChar *, const WideChar *, unsigned int );

class UnicodeStringData
{
public:
	UnsignedByte m_prefix[8];
	WideChar m_data[1];
};

#include "unicode_string.h"

class LANGameInfo
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
	virtual UnicodeString getName( void ) = 0;
};

struct LANMessage
{
	Int type;
	UnsignedByte m_prefix[0x1E - 4];
	WideChar gameName[17];
	Bool accepted;
	UnsignedByte m_remainder[0x1D8 - 0x42];
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
	virtual void RequestAccept( Bool accepted );
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
	UnsignedByte m_beforeLobby[0x41 - 4];
	Bool m_inLobby;
	UnsignedByte m_beforeGame[0x44 - 0x42];
	LANGameInfo *m_currentGame;
};

void LANAPI::RequestAccept( Bool accepted )
{
	if( m_inLobby || !m_currentGame )
		return;

	LANMessage message;
	fillInLANMessage( &message );
	message.type = 9;
	message.accepted = accepted;
	wcsncpy( message.gameName, m_currentGame->getName().str(), 0x10 );
	message.gameName[0x10] = 0;
	Rva004495A2( &message, 0 );
}
