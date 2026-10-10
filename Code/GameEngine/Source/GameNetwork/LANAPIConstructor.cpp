// ??0LANAPI@@QAE@XZ
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned short WideChar;
typedef unsigned char UnsignedByte;
typedef bool Bool;

#include "ascii_string.h"


#include "unicode_string.h"

class SubsystemInterface
{
public:
	SubsystemInterface(void);
	virtual ~SubsystemInterface(void);

private:
	UnsignedByte m_baseFields[8];
};

class LANAPIInterface : public SubsystemInterface
{
public:
	LANAPIInterface(void) {}
	virtual ~LANAPIInterface(void) {}
};

#include "../../Include/GameNetwork/Transport.h"

struct BfmeNetAddress
{
	UnsignedInt ip;
	UnsignedShort port;
};

struct LANMessage
{
	UnsignedInt type;
	UnsignedByte payload[0x1D8 - sizeof(UnsignedInt)];
};

class LANGameInfo;
class LANPlayer;

class LANAPI : public LANAPIInterface
{
public:
	LANAPI(void);
	virtual ~LANAPI(void);
	virtual void reset(void);

	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual void slot17(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot19(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot21(void) = 0;
	virtual void slot22(void) = 0;
	virtual void slot23(void) = 0;
	virtual void slot24(void) = 0;
	virtual void slot25(void) = 0;
	virtual void slot26(void) = 0;
	virtual void slot27(void) = 0;
	virtual void slot28(void) = 0;
	virtual void slot29(void) = 0;
	virtual void slot30(void) = 0;
	virtual void slot31(void) = 0;
	virtual void slot32(void) = 0;
	virtual void slot33(void) = 0;
	virtual void slot34(void) = 0;
	virtual void slot35(void) = 0;
	virtual void slot36(void) = 0;
	virtual void slot37(void) = 0;
	virtual void slot38(void) = 0;
	virtual void slot39(void) = 0;
	virtual void slot40(void) = 0;
	virtual void slot41(void) = 0;
	virtual void slot42(void) = 0;
	virtual void slot43(void) = 0;
	virtual void slot44(void) = 0;
	virtual void slot45(void) = 0;
	virtual void slot46(void) = 0;
	virtual void slot47(void) = 0;
	virtual void slot48(void) = 0;
	virtual void slot49(void) = 0;
	virtual void slot50(void) = 0;
	virtual void slot51(void) = 0;
	virtual void slot52(void) = 0;
	virtual void slot53(void) = 0;
	virtual void slot54(void) = 0;
	virtual void slot55(void) = 0;
	virtual void slot56(void) = 0;
	virtual void fillInLANMessage(LANMessage *message);	// slot 57

protected:
	LANPlayer *m_lobbyPlayers;		// +0x0C
	LANGameInfo *m_games;		// +0x10
	UnicodeString m_name;		// +0x14
	AsciiString m_userName;		// +0x18
	AsciiString m_hostName;		// +0x1C
	UnsignedInt m_gameStartTime;	// +0x20
	UnsignedInt m_gameStartSeconds;	// +0x24
	UnsignedInt m_pendingAction;	// +0x28
	UnsignedInt m_expiration;		// +0x2C
	UnsignedInt m_actionTimeout;	// +0x30
	BfmeNetAddress m_directConnectAddress;	// +0x34
	UnsignedInt m_lastResendTime;	// +0x3C
	Bool m_isInLANMenu;		// +0x40
	Bool m_inLobby;			// +0x41
	UnsignedByte m_beforeCurrentGame[0x44 - 0x42];
	LANGameInfo *m_currentGame;	// +0x44
	BfmeNetAddress m_localAddress;	// +0x48
	Transport *m_transport;		// +0x50
	UnsignedInt m_broadcastAddress;	// +0x54
	UnsignedInt m_unused58;		// +0x58
	Bool m_isActive;			// +0x5C
	Bool m_unused5D;			// +0x5D
};

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
extern "C" __declspec(dllimport) char * __cdecl getenv( const char *name );

// ??0LANAPI@@QAE@XZ @0x00449AB8 (193B). Zero Hour's constructor with BFME's
// member order: lists and names empty, no pending action or expiry, in the
// lobby and the LAN menu, no current game, a Transport at +0x50, active. The
// action timeout is 5000 ms, or 50000 ms when the _EA_RTS_HEADLESS
// environment variable is set (the same variable LANAPI::init reads).
LANAPI::LANAPI(void) : m_lobbyPlayers(0), m_games(0)
{
	m_gameStartTime = 0;
	m_gameStartSeconds = 0;
	m_pendingAction = 0;
	m_expiration = 0;
	m_actionTimeout = getenv("_EA_RTS_HEADLESS") ? 50000 : 5000;
	m_directConnectAddress.ip = 0;
	m_directConnectAddress.port = 0;
	m_lastResendTime = 0;
	m_isInLANMenu = true;
	m_inLobby = true;
	m_currentGame = 0;
	m_localAddress.ip = 0;
	m_localAddress.port = 0;
	_ReadWriteBarrier();
	m_broadcastAddress = (UnsignedInt)-1;
	m_transport = 0;
	m_unused58 = 0;
	m_isActive = true;
	m_unused5D = false;
	m_transport = new Transport;
}
