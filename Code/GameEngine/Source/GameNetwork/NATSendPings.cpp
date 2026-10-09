// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /EHsc /MD
//
// ?sendPings@NAT@@QAEXXZ
// retail 0x005A6EF2..0x005A7171 (640 bytes) thiscall RET 0.
//
// NAT::sendPings (WorldBuilder name 0x014E3EE0, NAT.cpp; one caller
// 0x005A8FAA). For every other human slot whose port negotiation is done
// (PortNegotiationSchema::isConnectionDone 0x005DBBC1) and whose ping is
// due (getTimeToSendPing past, or a peeked ping with +0x0C at least 1 and
// +0x08 below 2), it records the ping (sentAPingPacket) and queues
// "PING%d %X %X" (our slot, getActionID, the time) to that slot's address
// (+0x90C table) through Transport::queueSend. Sent to the host slot (+0x0C)
// the ping carries " %X %3.0f" latency entries for every connected human
// slot; otherwise only the target's own entry. The latency entry is gated
// by the out-of-line 0x005A66BF and valued by 0x005DB95B. The WorldBuilder
// debug log of the target address is compiled out of retail. Layout follows
// the NAT siblings (Rva005A69C0Box.cpp and NATSendNegotiationRequests.cpp).
#include "ascii_string.h"
#include "../../Include/GameNetwork/Transport.h"

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

class GameSlot
{
public:
	bool isHuman() const;		// 0x003FF0F1
};

// The schema's ping record (peekPing's result).
struct Elem005DB98E
{
	int m_00;
	float m_04;
	float m_08;
	float m_0C;
	float rva005A66BF();		// 0x005A66BF: 1 when +0x08 and +0x04 are positive
	float rva005DB95B();		// 0x005DB95B: the latency estimate
	float getOutstanding() const { return m_0C; }
	float getFailures() const { return m_08; }
};

class PortNegotiationSchema
{
public:
	bool isConnectionDone(unsigned short slot1, unsigned short slot2);	// 0x005DBBC1
	int getTimeToSendPing(unsigned short slot);				// 0x005DBBA5
	void *peekPing(unsigned short slot1, unsigned short slot2);		// 0x005DB98E
	bool sentAPingPacket(unsigned short slot1, unsigned short slot2);	// 0x005DBF2D
	int getActionID(unsigned short slot1, unsigned short slot2);		// 0x005DBCA6

	unsigned char m_pad[1];
};


class NAT
{
public:
	void sendPings();

private:
	int m_00;
	Transport *m_transport;			// +0x04
	GameSlot **m_slotList;			// +0x08
	int m_hostSlot;				// +0x0C
	int m_10;
	int m_localSlot;			// +0x14
	unsigned char m_pad18[0x28 - 0x18];
	PortNegotiationSchema m_schema;		// +0x28
	unsigned char m_pad29[0x90C - 0x29];
	NetPacketAddress *m_addresses[8];	// +0x90C
};

void NAT::sendPings()
{
	unsigned int now = timeGetTime();

	for (int i = 0; i < 8; ++i)
	{
		if (i == m_localSlot)
			continue;

		GameSlot *slot = m_slotList[i];
		if (!slot || !slot->isHuman())
			continue;
		if (!m_schema.isConnectionDone(m_localSlot, i))
			continue;

		if (now <= (unsigned int)m_schema.getTimeToSendPing(i))
		{
			Elem005DB98E *ping = (Elem005DB98E *)m_schema.peekPing(m_localSlot, i);
			if (!ping || !(ping->getOutstanding() >= 1.0 && ping->getFailures() < 2.0))
				continue;
		}

		if (!m_schema.sentAPingPacket(m_localSlot, i))
			continue;

		AsciiString pingStr;
		AsciiString tempStr;
		pingStr.format("PING%d %X %X", m_localSlot, m_schema.getActionID(m_localSlot, i), now);

		if (i == m_hostSlot)
		{
			for (unsigned char j = 0; j < 8; ++j)
			{
				if (j == m_localSlot)
					continue;
				GameSlot *other = m_slotList[j];
				if (!other || !other->isHuman())
					continue;
				if (!m_schema.isConnectionDone(m_localSlot, j))
					continue;
				Elem005DB98E *ping = (Elem005DB98E *)m_schema.peekPing(m_localSlot, j);
				if (!ping)
					continue;
				if (ping->rva005A66BF() == 0.0f)
					continue;
				tempStr.format(" %X %3.0f", j, ping->rva005DB95B());
				pingStr.concat(tempStr);
			}
		}
		else if (slot && slot->isHuman() && m_schema.isConnectionDone(m_localSlot, i))
		{
			Elem005DB98E *ping = (Elem005DB98E *)m_schema.peekPing(m_localSlot, i);
			if (ping && ping->rva005A66BF() != 0.0f)
			{
				tempStr.format(" %X %3.0f", i, ping->rva005DB95B());
				pingStr.concat(tempStr);
			}
		}

		m_transport->queueSend(m_addresses[i], (const unsigned char *)pingStr.str(), pingStr.getLength() + 1);
	}
}
