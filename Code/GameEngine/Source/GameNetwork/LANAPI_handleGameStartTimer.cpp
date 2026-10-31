// cl: /DNDEBUG /MD /EHsc
//
// ?handleGameStartTimer@LANAPI@@QAEXPAULANMessage@@PBUBfmeNetAddress@@@Z, retail 0x005816A3, 64 bytes.
// Chain via BfmeNetAddress compare 0x00248CBF plus LANAPI m_inLobby +0x41 plus
// m_currentGame +0x44 plus game flag +0x11 plus slot0 address +0x114 plus
// virtual slot 44 (0xB0) with msg+0x1E dword.

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;


#include "../../Include/GameNetwork/LANAPI.h"

struct LANMessage
{
	char m_pad[0x1E];
};

struct SlotEntry
{
	BfmeNetAddress m_address;
	char m_tail[0x1D0 - 8];
};

class LANGame
{
public:
	UnsignedByte m_pre11[0x11];
	UnsignedByte m_flag11;
	UnsignedByte m_pre114[0x114 - 0x12];
	SlotEntry m_slots[8];
};


void LANAPI::handleGameStartTimer(LANMessage *msg, const BfmeNetAddress *addr)
{
	if (m_inLobby != 0)
		return;
	LANGame *game = (LANGame *)m_currentGame;
	if (game == 0)
		return;
	if (!game->m_slots[0].m_address.Rva00248CBF(addr))
		return;
	if (game->m_flag11 != 0)
		return;
	OnGameStartTimer(*(UnsignedInt *)((char *)msg + 0x1E));
}
