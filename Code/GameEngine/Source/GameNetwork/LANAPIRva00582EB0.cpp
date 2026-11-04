// ?rva00582EB0@LANAPI@@QAEXPAULANMessage@@PBUBfmeNetAddress@@_N@Z
// partial score=0.99 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O1 /arch:SSE /G7
//
// ?rva00582EB0@LANAPI@@QAEXPAULANMessage@@PBUBfmeNetAddress@@_N@Z
// Retail 0x00582EB0, 273 bytes. The target reads LANAPI fields at +0x41/+0x44;
// its caller invokes this on the same LANAPI object as two matched handlers.
// Keep the address-based name: donor semantics are not established.

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef int Int;
typedef bool Bool;

#include "ascii_string.h"
#include "unicode_string.h"

#include "../../Include/GameNetwork/BfmeNetAddress.h"

struct LANMessage
{
	Int type;
	UnsignedByte payload[0x1D8 - sizeof(Int)];
};

class LANGameInfo
{
public:
	virtual void *slot00(Bool deleteStorage) = 0;
	Bool inProgress(void) const { return m_inProgress; }
	const BfmeNetAddress *getAddress(void) const { return &m_address; }

private:
	UnsignedByte m_beforeInProgress[0x11 - 4];
	Bool m_inProgress;
	UnsignedByte m_beforeAddress[0x114 - 0x12];
	BfmeNetAddress m_address;
};

#include "../../Include/GameNetwork/LANAPI.h"

extern AsciiString __cdecl GenerateGameOptionsString(void);
#include <new>

void LANAPI::rva00582EB0(LANMessage *message, const BfmeNetAddress *address, Bool flag)
{
	if (m_inLobby)
		return;

	LANGameInfo *game = m_currentGame;
	if (!game || !game->getAddress()->Rva00248CBF(address) || game->inProgress())
		return;

	AsciiString gameOptions = GenerateGameOptionsString();
	UnsignedByte no = 0;
	UnsignedByte reply = OnGameOptionsPacked(*address, no, message->payload + 0x1A, 0x186);
	if (reply != no)
	{
		{
			AsciiString receivedOptions = GenerateGameOptionsString();
			gameOptions.compare(receivedOptions);
		}
		rva00248E2F(false);
		if (flag)
		{
			OnWOTRGameStart();
		}
		else
			OnGameStart();
		return;
	}

	OnPlayerLeave(m_name);
	removeGame(m_currentGame);
	LANGameInfo *gameToDelete = m_currentGame;
	void *memory = gameToDelete ? gameToDelete->slot00(false) : 0;
	::operator delete(memory);
	m_currentGame = 0;
	m_inLobby = true;
}
