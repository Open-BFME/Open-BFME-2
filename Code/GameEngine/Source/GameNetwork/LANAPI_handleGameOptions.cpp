// cl: /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
//
// ?handleGameOptions@LANAPI@@QAEXPAULANMessage@@PBUBfmeNetAddress@@@Z, retail 0x00582138, 101 bytes. Banked partial (score 0.95) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
//
// Chain via BfmeNetAddress compare 0x00248CBF plus LANAPI m_inLobby +0x41 plus
// m_currentGame +0x44 plus game flag +0x11 plus 8 slots stride 0x1D0 with address
// at slot+0 plus virtual slot 45 (0xB4) with addr plus index plus narrow
// StringBase temp from msg+0x1E.

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

#include "ascii_string.h"


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


void LANAPI::handleGameOptions(LANMessage *msg, const BfmeNetAddress *addr)
{
	if (m_inLobby != 0)
		return;
	LANGame *game = (LANGame *)m_currentGame;
	if (0 == game)
		return;
	if (game->m_flag11 != 0)
		return;
	for (int i = 0; i < 8; ++i)
	{
		if (game->m_slots[i].m_address.Rva00248CBF(addr))
		{
			OnGameOptions(*addr, i, AsciiString((const char *)msg + 0x1E));
			return;
		}
	}
}
