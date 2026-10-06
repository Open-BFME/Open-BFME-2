// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O1
//
// LANAPI::RequestGameJoin, retail 0x00449E9A (334 bytes), slot 16 of the
// LANAPI vtable 0x0083E680 (OnGameJoin's headless timeout retry dispatches
// it at +0x40). Open-BFME-1's RequestGameJoin (lanapi.cpp), which is Zero
// Hour's: busy unless idle or joining by direct connect (+0x28 0 or 2),
// RET_GAME_GONE without a game, otherwise a MSG_REQUEST_JOIN (3) message
// filled by fillInLANMessage (slot 57) carrying the host's IP (slot 0's
// address +0x38), the global data's CRCs and the "\ergc" serial truncated to
// 0x17 bytes, sent through the ledger's 0x004495A2 to the given address,
// then ACT_JOIN with the action timeout. BFME 2's exe CRC is the 16-byte
// block at TheGlobalData +0xB08, copied by the rowed 0x00237E28 into msg
// +0x22; the ini CRC (+0xB04) and BFME's extra CRC (+0xB38) follow at +0x32
// and +0x36, the serial at +0x3A. The CRC names are the donor's.

typedef int Int;
typedef bool Bool;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;

extern "C" __declspec(dllimport) char *__cdecl strncpy( char *dest, const char *source, UnsignedInt count );
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime( void );

#include "ascii_string.h"

Bool GetStringFromRegistry( AsciiString path, AsciiString key, AsciiString &val );

// The 16-byte exe CRC block and its copy (0x00237E28), under the ledger's
// class name.
class Rva00237E28
{
public:
	void rva00237E28( Rva00237E28 *dest );

private:
	UnsignedInt m_words[4];
};

class GlobalData
{
public:
	UnsignedByte m_preB04[0xB04];
	UnsignedInt m_iniCRC;				// +0xB04
	Rva00237E28 m_exeCRC;				// +0xB08
	UnsignedByte m_preB38[0xB38 - 0xB18];
	UnsignedInt m_bfmeExtraCRC;			// +0xB38
};
extern GlobalData *TheWritableGlobalData;

struct BfmeNetAddress
{
	UnsignedInt m_ip;
	UnsignedShort m_port;
};

class GameSlot
{
public:
	UnsignedByte m_pre38[0x38];
	BfmeNetAddress m_address;			// +0x38
};

class GameInfo
{
public:
	GameSlot *getSlot( Int slotNum );
};

class LANGameInfo : public GameInfo
{
};

enum
{
	SERIAL_LENGTH = 0x17
};

#pragma pack(push, 1)
struct LANMessage
{
	enum
	{
		MSG_REQUEST_JOIN = 3
	};

	Int LANMessageType;
	UnsignedByte m_header[0x1E - 4];
	struct
	{
		UnsignedInt gameIP;			// +0x1E
		Rva00237E28 exeCRC;			// +0x22
		UnsignedInt iniCRC;			// +0x32
		UnsignedInt bfmeExtraCRC;		// +0x36
		char serial[SERIAL_LENGTH];		// +0x3A
	} GameToJoin;
	UnsignedByte m_rest[0x1D8 - 0x51];
};
#pragma pack(pop)

class LANAPIInterface
{
public:
	enum ReturnType
	{
		RET_OK = 0,
		RET_TIMEOUT,
		RET_GAME_FULL,
		RET_DUPLICATE_NAME,
		RET_CRC_MISMATCH,
		RET_SERIAL_DUPE,
		RET_GAME_STARTED,
		RET_GAME_EXISTS,
		RET_GAME_GONE,
		RET_BUSY
	};
};

#define BFME_VSLOT(n) virtual void slot##n( void ) = 0;

class LANAPI
{
public:
	enum PendingAction
	{
		ACT_NONE = 0,
		ACT_JOIN,
		ACT_JOINDIRECTCONNECT
	};

	BFME_VSLOT(00) BFME_VSLOT(01) BFME_VSLOT(02) BFME_VSLOT(03) BFME_VSLOT(04)
	BFME_VSLOT(05) BFME_VSLOT(06) BFME_VSLOT(07) BFME_VSLOT(08) BFME_VSLOT(09)
	BFME_VSLOT(10) BFME_VSLOT(11) BFME_VSLOT(12) BFME_VSLOT(13) BFME_VSLOT(14)
	BFME_VSLOT(15)
	virtual void RequestGameJoin( LANGameInfo *game, const BfmeNetAddress &ip );
	BFME_VSLOT(17) BFME_VSLOT(18) BFME_VSLOT(19)
	BFME_VSLOT(20) BFME_VSLOT(21) BFME_VSLOT(22) BFME_VSLOT(23) BFME_VSLOT(24)
	BFME_VSLOT(25) BFME_VSLOT(26) BFME_VSLOT(27) BFME_VSLOT(28) BFME_VSLOT(29)
	BFME_VSLOT(30) BFME_VSLOT(31) BFME_VSLOT(32) BFME_VSLOT(33)
	virtual void OnGameJoin( LANAPIInterface::ReturnType ret, LANGameInfo *theGame, LANMessage *msg ) = 0;
	BFME_VSLOT(35) BFME_VSLOT(36) BFME_VSLOT(37) BFME_VSLOT(38) BFME_VSLOT(39)
	BFME_VSLOT(40) BFME_VSLOT(41) BFME_VSLOT(42) BFME_VSLOT(43) BFME_VSLOT(44)
	BFME_VSLOT(45) BFME_VSLOT(46) BFME_VSLOT(47) BFME_VSLOT(48) BFME_VSLOT(49)
	BFME_VSLOT(50) BFME_VSLOT(51) BFME_VSLOT(52) BFME_VSLOT(53) BFME_VSLOT(54)
	BFME_VSLOT(55) BFME_VSLOT(56)
	virtual void fillInLANMessage( LANMessage *msg ) = 0;

	// sendMessage, under the ledger's name; it takes the address as a word.
	void Rva004495A2( LANMessage *msg, UnsignedInt ip );

protected:
	UnsignedByte m_pre28[0x28 - 4];
	Int m_pendingAction;				// +0x28
	UnsignedInt m_expiration;			// +0x2C
	UnsignedInt m_actionTimeout;			// +0x30
};

#undef BFME_VSLOT

// StringBase<char>::str(): an empty serial reads the function-local
// TheNullChr, which the compiler cannot fold into RequestGameJoin's "" literals.
static inline const char *serialText( const AsciiString &s )
{
	return ((const StringBase<char> *)&s)->str();
}

void LANAPI::RequestGameJoin( LANGameInfo *game, const BfmeNetAddress &ip )
{
	if( ( m_pendingAction != ACT_NONE ) && ( m_pendingAction != ACT_JOINDIRECTCONNECT ) )
	{
		OnGameJoin( LANAPIInterface::RET_BUSY, 0, 0 );
		return;
	}

	if( !game )
	{
		OnGameJoin( LANAPIInterface::RET_GAME_GONE, 0, 0 );
		return;
	}

	LANMessage msg;
	msg.LANMessageType = LANMessage::MSG_REQUEST_JOIN;
	fillInLANMessage( &msg );
	msg.GameToJoin.gameIP = game->getSlot( 0 )->m_address.m_ip;
	TheWritableGlobalData->m_exeCRC.rva00237E28( &msg.GameToJoin.exeCRC );
	msg.GameToJoin.iniCRC = TheWritableGlobalData->m_iniCRC;
	msg.GameToJoin.bfmeExtraCRC = TheWritableGlobalData->m_bfmeExtraCRC;

	AsciiString s = "";
	GetStringFromRegistry( "\\ergc", "", s );
	strncpy( msg.GameToJoin.serial, serialText( s ), SERIAL_LENGTH );
	msg.GameToJoin.serial[SERIAL_LENGTH - 1] = '\0';

	Rva004495A2( &msg, (UnsignedInt)&ip );

	m_pendingAction = ACT_JOIN;
	m_expiration = timeGetTime() + m_actionTimeout;
}
