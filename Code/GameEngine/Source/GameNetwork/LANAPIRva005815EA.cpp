// cl: /DNDEBUG /MD /EHsc
//
// ?rva005815EA@LANAPI@@QAEXPAULANMessage@@PBUBfmeNetAddress@@@Z, retail 0x005815EA, 87 bytes.
// Chain via BfmeNetAddress compare 0x00248CBF plus LANAPI m_inLobby +0x41 plus
// m_currentGame +0x44 plus game flag +0x11 plus 8 slots stride 0x1D0 with address
// at slot+0 plus virtual slot 38 (0x98) with msg+0x40 byte.

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

struct BfmeNetAddress
{
	bool Rva00248CBF(const BfmeNetAddress *other) const;
	UnsignedInt ip;
	UnsignedShort port;
};

struct LANMessage
{
	char m_pad40[0x40];
	UnsignedByte m_b40;
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
	virtual void slot38(const BfmeNetAddress *addr, UnsignedByte val) = 0;
	void rva005815EA(LANMessage *msg, const BfmeNetAddress *addr);

private:
	UnsignedByte m_pad04[0x41 - 4];
	UnsignedByte m_inLobby;
	UnsignedByte m_pad42[0x44 - 0x42];
	LANGame *m_currentGame;
};

void LANAPI::rva005815EA(LANMessage *msg, const BfmeNetAddress *addr)
{
	if (m_inLobby != 0)
		return;
	if (m_currentGame == 0)
		return;
	if (m_currentGame->m_flag11 != 0)
		return;
	SlotEntry *slot = m_currentGame->m_slots;
	for (int i = 0; i < 8; ++i, ++slot)
	{
		if (slot->m_address.Rva00248CBF(addr))
		{
			slot38(addr, msg->m_b40);
			return;
		}
	}
}
