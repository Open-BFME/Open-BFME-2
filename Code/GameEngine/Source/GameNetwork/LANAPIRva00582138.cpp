// cl: /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
//
// ?rva00582138@LANAPI@@QAEXPAULANMessage@@PBUBfmeNetAddress@@@Z, retail 0x00582138, 101 bytes. Banked partial (score 0.95) closed by tools/permute.py;
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

struct BfmeNetAddress
{
	bool Rva00248CBF(const BfmeNetAddress *other) const;
	UnsignedInt ip;
	UnsignedShort port;
};

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

class LANAPI
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45(const BfmeNetAddress *addr, int index, AsciiString str) = 0;
	void rva00582138(LANMessage *msg, const BfmeNetAddress *addr);

private:
	UnsignedByte m_pad04[0x41 - 4];
	UnsignedByte m_inLobby;
	UnsignedByte m_pad42[0x44 - 0x42];
	LANGame *m_currentGame;
};

void LANAPI::rva00582138(LANMessage *msg, const BfmeNetAddress *addr)
{
	if (m_inLobby != 0)
		return;
	LANGame *game = m_currentGame;
	if (0 == game)
		return;
	if (game->m_flag11 != 0)
		return;
	for (int i = 0; i < 8; ++i)
	{
		if (game->m_slots[i].m_address.Rva00248CBF(addr))
		{
			slot45(addr, i, AsciiString((const char *)msg + 0x1E));
			return;
		}
	}
}
