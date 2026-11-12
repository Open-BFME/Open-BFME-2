// cl: /DNDEBUG /MD /EHsc
//
// ?rva00581641@LANAPI@@QAEXPAULANMessage@@PBUBfmeNetAddress@@@Z, retail 0x00581641, 98 bytes.
// Chain via BfmeNetAddress compare 0x00248CBF plus holder +0x44 plus flag +0x11
// plus slot54 0xD8 guard plus inLobby +0x41 plus 8 slots stride 0x1D0 plus
// virtual slot 61 (0xF4) with msg+0x40 byte.

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

#include "../../Include/GameNetwork/BfmeNetAddress.h"

struct LANMessage
{
	char m_pad40[0x40];
	bool m_b40;
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

void LANAPI::rva00581641(LANMessage *msg, const BfmeNetAddress *addr)
{
	if (m_currentGame == 0)
		return;
	if (((LANGame *)m_currentGame)->m_flag11 != 0)
		return;
	if ((UnsignedByte)AmIHost())
		return;
	if (m_inLobby)
		return;
	SlotEntry *slot = ((LANGame *)m_currentGame)->m_slots;
	for (int i = 0; i < 8; ++i, ++slot)
	{
		if (slot->m_address.Rva00248CBF(addr))
		{
			rva00248E2F(msg->m_b40);
			return;
		}
	}
}
