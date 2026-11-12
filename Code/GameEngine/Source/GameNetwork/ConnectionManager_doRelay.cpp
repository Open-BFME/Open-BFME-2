// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ConnectionManager::doRelay, retail 0x004D3221, 521 bytes, and the command
// loop it runs over each received list, retail 0x004D316A, 183 bytes.
//
// Reference: Zero Hour ConnectionManager::doRelay (read every non-empty
// transport in-buffer into a NetPacket, then process its commands, then the
// commands the wrapper list has finished reassembling) and Open-BFME-1
// native_connection_timing.cpp runRelayPass (BFME 1 0x0066AE60), which adds the
// router's player-leave broadcast in front of the same two loops.
// BFME 2 differences read from these bodies: the per-command work moved out to
// 0x004D316A, called with the list and the packet's source address (null for
// the wrapper list); the leave broadcast keys on isPlayerInGame 0x004CF0A6,
// stamps the leave with the logic timestamp, and sends the destroy only for a
// slot whose request-player-leave value (+0x120A0, stored by 0x004CF35D) is
// zero. The loop skips a command stamped past the current timestamp and an
// older one unless 0x00581318 accepts its type, before the duplicate filter
// 0x004D2667 and the dispatcher 0x004D2F04.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;

enum NetCommandType
{
	NETCOMMANDTYPE_FRAMEINFO = 3
};

enum
{
	MAX_SLOTS = 8,
	MAX_MESSAGES = 128
};

#include "../Common/GameLogicObjectLookupView.h"
#include "../../Include/GameNetwork/Transport.h"

extern GameLogic *TheGameLogic;

class NetworkInterface;
struct RelayNetworkVTable
{
	void *unknown[63];
	Bool (__fastcall *isRouterLeavePending)(NetworkInterface *network);
};

class NetworkInterface
{
public:
	Bool isRouterLeavePending() { return m_vtable->isRouterLeavePending(this); }

private:
	RelayNetworkVTable *m_vtable;
};

extern NetworkInterface *TheNetwork;

#include "../../Include/GameNetwork/NetCommandMsg.h"

inline void NetCommandMsg::setID(unsigned short id)
{
	m_id = id;
}

// Zero Hour's NetPlayerLeaveCommandMsg (type 10), held in the ledger under its
// constructor's address name.
class Rva004D5795 : public NetCommandMsg
{
public:
	Rva004D5795();

private:
	UnsignedByte m_leavingPlayerID;
};

// The folded byte setter at +0x1C the leave message shares.
class NetDisconnectPlayerCommandMsg
{
public:
	void setDisconnectSlot(UnsignedByte slot);
};

// The existing native type-11 constructor and +0x1C setter are both
// owned under Rva004D57AE. Use that same identity for this relay view.
class Rva004D57AE : public NetCommandMsg
{
public:
	Rva004D57AE();
	void setPlayerIndex(UnsignedInt playerIndex);

private:
	UnsignedInt m_playerIndex;
};

Bool DoesCommandRequireACommandID(NetCommandType type);
UnsignedShort GenerateNextCommandID();
Bool CommandRequiresAck(NetCommandMsg *msg);
Bool Rva00581318Get(NetCommandMsg *msg);

class NetCommandRef
{
public:
	NetCommandMsg *getCommand() { return m_msg; }
	NetCommandRef *getNext() { return m_next; }

private:
	NetCommandMsg *m_msg;
	NetCommandRef *m_next;
	NetCommandRef *m_prev;
	UnsignedByte m_relay;
};

#include "../../Include/GameNetwork/NetCommandListClass.h"

#include "../../Include/GameNetwork/NetCommandWrapperListClass.h"

#include "../../Include/GameNetwork/BfmeNetAddress.h"

class NetPacket
{
public:
	NetPacket(TransportMessage *msg);
	virtual ~NetPacket();
	NetCommandList *getCommandList();
	BfmeNetAddress getAddress() const { return m_address; }

private:
	UnsignedByte m_packet[0x1DC];
	Int m_packetLen;
	BfmeNetAddress m_address;
	Int m_numCommands;
	NetCommandRef *m_lastCommand;
	UnsignedInt m_lastFrame;
	UnsignedInt m_lastTimestamp;
	UnsignedShort m_lastCommandID;
	UnsignedByte m_lastPlayerID;
	UnsignedByte m_lastCommandType;
	UnsignedByte m_lastRelay;
};

#include "../../Include/GameNetwork/BFMEConnectionManager.h"

#include "../../Include/GameNetwork/ConnectionManager.h"

void ConnectionManager::rva004D316A(NetCommandList *list, const BfmeNetAddress *source)
{
	if (list == 0)
		return;
	for (NetCommandRef *ref = list->getFirstMessage(); ref != 0; ref = ref->getNext())
	{
		if (TheNetwork != 0 && TheNetwork->isRouterLeavePending() &&
			m_localSlot == m_packetRouterSlot &&
			ref->getCommand()->getNetCommandType() != NETCOMMANDTYPE_FRAMEINFO)
			continue;
		UnsignedInt timestamp = ref->getCommand()->getTimestamp();
		if (timestamp > TheGameLogic->getTimestamp())
			continue;
		if (CommandRequiresAck(ref->getCommand()))
			ackCommand(ref, source);
		if (timestamp < TheGameLogic->getTimestamp() && !Rva00581318Get(ref->getCommand()))
			continue;
		if (!((BFMEConnectionManager *)this)->isDuplicateCommand(ref->getCommand()) &&
			processNetCommand(ref))
			((BFMEConnectionManager *)this)->relayCommand(ref);
	}
}

void ConnectionManager::doRelay()
{
	if (m_localSlot == m_packetRouterSlot)
	{
		for (UnsignedInt i = 0; i < MAX_SLOTS; ++i)
		{
			if (!((BFMEConnectionManager *)this)->isPlayerInGame(i))
				continue;
			Rva004D5795 *leave = new Rva004D5795;
			((NetDisconnectPlayerCommandMsg *)leave)->setDisconnectSlot(i);
			leave->setTimestamp(TheGameLogic->getTimestamp());
			leave->setExecutionFrame(-1);
			if (DoesCommandRequireACommandID(leave->getNetCommandType()))
				leave->setID(GenerateNextCommandID());
			leave->setPlayerID(m_localSlot);
			sendLocalCommand(leave, 0xff);
			leave->detach();
			if (field120A0[i] == 0)
			{
				Rva004D57AE *destroy = new Rva004D57AE;
				if (DoesCommandRequireACommandID(destroy->getNetCommandType()))
					destroy->setID(GenerateNextCommandID());
				destroy->setPlayerID(m_localSlot);
				destroy->setPlayerIndex(i);
				sendLocalCommand(destroy, 0xff);
				destroy->detach();
			}
			field12080[i] = 2;
		}
	}

	for (UnsignedInt i = 0; i < MAX_MESSAGES; ++i)
	{
		if (m_transport->m_inBuffer[i].m_length != 0)
		{
			NetPacket packet(&m_transport->m_inBuffer[i]);
			m_transport->m_inBuffer[i].m_length = 0;
			NetCommandList *cmdList = packet.getCommandList();
			BfmeNetAddress source = packet.getAddress();
			rva004D316A(cmdList, &source);
			::delete cmdList;
		}
	}

	if (m_netCommandWrapperList != 0)
	{
		NetCommandList *cmdList = m_netCommandWrapperList->getReadyCommands();
		rva004D316A(cmdList, 0);
		::delete cmdList;
	}
}
