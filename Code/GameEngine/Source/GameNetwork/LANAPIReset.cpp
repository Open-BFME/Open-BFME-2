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

#include "../../Include/GameNetwork/BfmeNetAddress.h"

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

#include <new>

#include "unicode_string.h"

#include "../../Include/GameNetwork/LANPlayerClass.h"

// ??1LANPlayer@@QAE@XZ @0x00447ACA
LANPlayer::~LANPlayer()
{
}

// The current game slot at VA 0xE02EEC is the owned global TheGameInfo.
class GameInfo;
extern GameInfo *TheGameInfo;

#include "../../Include/GameNetwork/LANAPI.h"

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
	if ((LANGameInfo *)TheGameInfo == m_currentGame)
		TheGameInfo = 0;
	m_currentGame = 0;
}

