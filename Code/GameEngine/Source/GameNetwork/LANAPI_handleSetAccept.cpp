// cl: /DNDEBUG /MD /EHsc
//
// ?handleSetAccept@LANAPI@@QAEXPAULANMessage@@PBUBfmeNetAddress@@@Z, retail 0x005815EA, 87 bytes.
// Chain via BfmeNetAddress compare 0x00248CBF plus LANAPI m_inLobby +0x41 plus
// m_currentGame +0x44 plus game flag +0x11 plus 8 slots stride 0x1D0 with address
// at slot+0 plus virtual slot 38 (0x98, OnAccept) with the msg+0x40 Bool.

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

#include "../../Include/GameNetwork/BfmeNetAddress.h"

struct LANMessage
{
	char m_pad40[0x40];
	bool m_isAccepted;
};

#include "../../Include/Common/SlotEntry.h"

class LANGame
{
public:
	UnsignedByte m_pre11[0x11];
	UnsignedByte m_flag11;
	UnsignedByte m_pre114[0x114 - 0x12];
	SlotEntry m_slots[8];
};

#include "../../Include/GameNetwork/LANAPI.h"

void LANAPI::handleSetAccept(LANMessage *msg, const BfmeNetAddress *addr)
{
	if (m_inLobby != 0)
		return;
	LANGame *game = reinterpret_cast<LANGame *>(m_currentGame);
	if (game == 0)
		return;
	if (game->m_flag11 != 0)
		return;
	SlotEntry *slot = game->m_slots;
	for (int i = 0; i < 8; ++i, ++slot)
	{
		if (slot->m_address.Rva00248CBF(addr))
		{
			OnAccept(addr, msg->m_isAccepted);
			return;
		}
	}
}
