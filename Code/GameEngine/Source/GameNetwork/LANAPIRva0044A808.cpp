// cl: /O1 /G7 /DNDEBUG /MD /EHsc
//
// LANAPI::rva0044A808, retail 0x0044A808, 249 bytes.
// LANAPI vtable slot 25. Chain via BfmeNetAddress compare 0x00248CBF plus
// slot 57 message fill plus strncpy name plus pinned helper 0x004495A2 plus
// 8 slots stride 0x1D0 plus slot 64 address plus slot 45 notify.
// Retail's unwind map destroys the by-value name (state 0) and the
// AsciiString argument built for slot 45 (state 1, address kept at
// ebp-0x10), so that argument is a destructible AsciiString; the empty-name
// fallback is str()'s "" literal; the slot address is taken before the
// compare's argument is evaluated.

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

extern "C" __declspec(dllimport) char *__cdecl strncpy(char *dst, const char *src, UnsignedInt n);

template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

class AsciiString;

struct BfmeNetAddress
{
	bool Rva00248CBF(const BfmeNetAddress *other) const;
	UnsignedInt m_key0;
	UnsignedShort m_key4;
};

struct SlotEntry
{
	BfmeNetAddress m_address;
	char m_tail[0x1D0 - 8];
};

class LANGame
{
public:
	UnsignedByte m_pad[0x114];
	SlotEntry m_slots[8];
};

struct LANMessage
{
	int m_type;
	char m_pad1E[0x1E - 4];
	char m_name[0x186];
	UnsignedByte m_zero1A4;
	char m_tail[0x30];
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
	virtual void slot45(BfmeNetAddress *addr, int index, AsciiString str) = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void slot49() = 0;
	virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual void slot52() = 0;
	virtual void slot53() = 0;
	virtual void slot54() = 0;
	virtual void slot55() = 0;
	virtual void slot56() = 0;
	virtual void slot57(LANMessage *msg) = 0;
	virtual void slot58() = 0;
	virtual void slot59() = 0;
	virtual void slot60() = 0;
	virtual void slot61() = 0;
	virtual void slot62() = 0;
	virtual void slot63() = 0;
	virtual BfmeNetAddress *slot64() = 0;
	void Rva004495A2(LANMessage *msg, UnsignedInt val);
	void rva0044A808(AsciiString str, int, UnsignedInt val);

private:
	UnsignedByte m_beforeLobby[0x41 - 4];
	UnsignedByte m_inLobby;
	UnsignedByte m_beforeGame[0x44 - 0x42];
	LANGame *m_currentGame;
};


void LANAPI::rva0044A808(AsciiString str, int, UnsignedInt val)
{
	if (m_currentGame == 0)
		return;
	LANMessage msg;
	slot57(&msg);
	msg.m_type = 0x10;
	strncpy(msg.m_name, str.str(), 0x186);
	msg.m_zero1A4 = 0;
	Rva004495A2(&msg, val);
	for (int i = 0; i < 8; ++i)
	{
		BfmeNetAddress *addr = &m_currentGame->m_slots[i].m_address;
		if (addr->Rva00248CBF(slot64()))
		{
			slot45(slot64(), i, AsciiString(msg.m_name));
			break;
		}
	}
}
