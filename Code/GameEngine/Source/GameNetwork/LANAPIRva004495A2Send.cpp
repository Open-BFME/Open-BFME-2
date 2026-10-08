// cl: /DNDEBUG /MD /EHsc
//
// ?Rva004495A2@LANAPI@@QAEXPAULANMessage@@I@Z, retail 0x004495A2 (184 bytes;
// Ghidra split it at +0x0D, the true end is the ret 8 at 0x00449659).
// Zero Hour's LANAPI::sendMessage(msg, ip) reworked for BFME 2's
// address+port destinations: the second argument (declared unsigned int by
// the callers' pinned spelling) is really a pointer to an {ip, port} pair.
//   - a non-null destination with a non-zero ip or port: send there;
//   - else, in a direct-connect game (+0x44, flag byte +0xF68): send to the
//     {ip, port} at GameSlot+0x38 of every human slot but the local one;
//   - else: broadcast to m_broadcastAddr (+0x54) on each of the eight lobby
//     ports 0x1F96..0x1F9D.
// Every send goes through the transport at +0x50 (queueSend at 0x004D4EC6) with
// the 0x1D8-byte LANMessage. Native queueSend reads the same ip/port
// pair as the local address view; it copies the message as bytes. Callee identities beyond the rowed
// GameInfo::getSlot / GameSlot::isHuman stay address-derived.

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;

enum { MAX_SLOTS = 8 };

struct LANMessage
{
	Int type;
	unsigned char bytes[0x1D4];
};

struct Rva004495A2Addr
{
	UnsignedInt ip;
	UnsignedShort port;
};

#include "../../Include/GameNetwork/Transport.h"

class GameSlot
{
public:
	Bool isHuman( void ) const;
	unsigned char m_pad00[0x38];
	Rva004495A2Addr m_addr; // +0x38
};

class GameInfo
{
public:
	virtual void slot00( void ) = 0;
	virtual void slot01( void ) = 0;
	virtual void slot02( void ) = 0;
	virtual void slot03( void ) = 0;
	virtual void slot04( void ) = 0;
	virtual void slot05( void ) = 0;
	virtual void slot06( void ) = 0;
	virtual void slot07( void ) = 0;
	virtual void slot08( void ) = 0;
	virtual void slot09( void ) = 0;
	virtual void slot10( void ) = 0;
	virtual void slot11( void ) = 0;
	virtual void slot12( void ) = 0;
	virtual Int getLocalSlotNum( void ) const = 0; // vtable +0x34

	GameSlot *getSlot( Int index );
	Bool getIsDirectConnect( void ) const { return m_isDirectConnect; }

	unsigned char m_pad004[0xF68 - 4];
	Bool m_isDirectConnect; // +0xF68
};

class LANAPI
{
public:
	void Rva004495A2( LANMessage *msg, UnsignedInt ip );

	unsigned char m_pad00[0x44];
	GameInfo *m_currentGame; // +0x44
	unsigned char m_pad48[0x50 - 0x48];
	Transport *m_transport; // +0x50
	UnsignedInt m_broadcastAddr; // +0x54
};

void LANAPI::Rva004495A2( LANMessage *msg, UnsignedInt ip )
{
	const Rva004495A2Addr *to = (const Rva004495A2Addr *)ip;
	if (to != 0 && (to->ip != 0 || to->port != 0))
	{
		m_transport->queueSend((NetPacketAddress *)to, (const unsigned char *)msg, sizeof(LANMessage));
	}
	else if (m_currentGame != 0 && m_currentGame->getIsDirectConnect())
	{
		Int localSlot = m_currentGame->getLocalSlotNum();
		for (Int i = 0; i < MAX_SLOTS; ++i)
		{
			if (i != localSlot)
			{
				GameSlot *slot = m_currentGame->getSlot(i);
				if (slot != 0 && slot->isHuman())
					m_transport->queueSend((NetPacketAddress *)&slot->m_addr, (const unsigned char *)msg, sizeof(LANMessage));
			}
		}
	}
	else
	{
		for (UnsignedShort port = 0x1F96; port < 0x1F9E; ++port)
		{
			Rva004495A2Addr broadcast;
			broadcast.ip = m_broadcastAddr;
			broadcast.port = port;
			m_transport->queueSend((NetPacketAddress *)&broadcast, (const unsigned char *)msg, sizeof(LANMessage));
		}
	}
}
