// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// Retail 0x0044B49B, 191 bytes. BFME1 LANAPI::reset supplies the operation;
// target body evidence sets the list heads at +0x0C/+0x10, LANGameInfo::next
// at +0xF5C, player next at +0x10, pending/expiration at +0x28/+0x2C, the
// address pair at +0x34, flags at +0x40/+0x41, current game at +0x44, and
// transport at +0x50. Target Transport update takes a null receiver, unlike the
// BFME1 no-argument method.
//
// ??1LANPlayer@@QAE@XZ, retail 0x00447ACA, 68 bytes. Non-virtual dtor over
// three UnicodeString members at +0/+4/+8 (releaseBuffer 0x00036E70 in
// reverse order with EH states 1/0/-1), then next at +0x10 for reset's walk.
// Callers: reset 0x0044B50D and ??_G in this file, plus Rva00447B0E 0x00447B3B.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;

struct BfmeNetAddress
{
	UnsignedInt ip;
	UnsignedShort port;
};

struct LANMessage
{
	Int type;
	UnsignedByte payload[0x1D8 - sizeof(Int)];
};

#include "../../Include/GameNetwork/Transport.h"

class LANGameInfo
{
public:
	// Retail calls slot 0 with flag 0, then frees the returned object pointer.
	virtual LANGameInfo *slot00(Bool deleteStorage);
	LANGameInfo *getNext(void) const { return m_next; }

private:
	UnsignedByte m_beforeNext[0xF5C - 4];
	LANGameInfo *m_next;
};

void __cdecl operator delete(void *memory);

#include "unicode_string.h"

class LANPlayer
{
public:
	~LANPlayer();
	LANPlayer *getNext(void) const { return m_next; }

private:
	UnicodeString m_s00; // +0x00
	UnicodeString m_s04; // +0x04
	UnicodeString m_s08; // +0x08
	UnsignedByte m_pad0C[4]; // +0x0C
	LANPlayer *m_next; // +0x10
};

// ??1LANPlayer@@QAE@XZ @0x00447ACA
LANPlayer::~LANPlayer()
{
}

extern LANGameInfo *g_Rva00E02EEC;

class LANAPI
{
public:
	virtual void reset(void);
	virtual void slot01(void) = 0;
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
	void Rva004495A2(LANMessage *message, UnsignedInt address);

private:
	UnsignedByte m_beforePlayers[0x0C - 4];
	LANPlayer *m_lobbyPlayers;		// +0x0C
	LANGameInfo *m_games;		// +0x10
	UnsignedByte m_beforePending[0x28 - 0x14];
	UnsignedInt m_pendingAction;	// +0x28
	UnsignedInt m_expiration;		// +0x2C
	UnsignedByte m_beforeAddress[0x34 - 0x30];
	BfmeNetAddress m_directConnectAddress;	// +0x34
	UnsignedByte m_beforeFlags[0x40 - 0x3C];
	Bool m_isInLANMenu;		// +0x40
	Bool m_inLobby;			// +0x41
	UnsignedByte m_beforeCurrentGame[0x44 - 0x42];
	LANGameInfo *m_currentGame;	// +0x44
	UnsignedByte m_beforeTransport[0x50 - 0x48];
	Transport *m_transport;		// +0x50
};

void LANAPI::reset(void)
{
	if (m_inLobby)
	{
		LANMessage message;
		fillInLANMessage(&message);
		message.type = 7;
		Rva004495A2(&message, 0);
	}

	m_transport->update(0);

	LANGameInfo *game = m_games;
	while (game)
	{
		LANGameInfo *deletable = game;
		game = game->getNext();
		void *memory = deletable->slot00(false);
		::operator delete(memory);
	}

	LANPlayer *player = m_lobbyPlayers;
	while (player)
	{
		LANPlayer *deletable = player;
		player = player->getNext();
		delete deletable;
	}

	m_games = 0;
	m_lobbyPlayers = 0;
	BfmeNetAddress noAddress = { 0, 0 };
	m_directConnectAddress = noAddress;
	m_pendingAction = 0;
	m_expiration = 0;
	m_inLobby = true;
	m_isInLANMenu = true;
	if (g_Rva00E02EEC == m_currentGame)
		g_Rva00E02EEC = 0;
	m_currentGame = 0;
}

// ?g_Rva00E02EEC@@3PAVLANGameInfo@@A: the global at this VA is ?TheGameInfo@@3PAVGameInfo@@A; this name is an alias for it.
#pragma comment(linker, "/alternatename:?g_Rva00E02EEC@@3PAVLANGameInfo@@A=?TheGameInfo@@3PAVGameInfo@@A")
#pragma comment(linker, "/alternatename:?g_00E02EEC@@3PAVRva00E02EECObj@@A=?TheGameInfo@@3PAVGameInfo@@A")
#pragma comment(linker, "/alternatename:?g_Rva0023D30FFlag@@3HA=?TheGameInfo@@3PAVGameInfo@@A")
// ?g_Rva00E02EEC@@3PAVLANGameInfo@@A: the global at VA 0xe02eec is ?TheGameInfo@@3PAVGameInfo@@A.
#pragma comment(linker, "/alternatename:?g_Rva00E02EEC@@3PAVLANGameInfo@@A=?TheGameInfo@@3PAVGameInfo@@A")
