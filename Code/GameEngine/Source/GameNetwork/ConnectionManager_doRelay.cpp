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

class GameLogic
{
public:
	UnsignedInt getTimestamp() const { return m_timestamp; }

private:
	char m_pad00[0x38];
	UnsignedInt m_timestamp;
};

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

class NetCommandMsg
{
public:
	void detach();
	void setTimestamp(UnsignedInt timestamp) { m_timestamp = timestamp; }
	UnsignedInt getTimestamp() const { return m_timestamp; }
	void setExecutionFrame(UnsignedInt frame) { m_executionFrame = frame; }
	void setPlayerID(UnsignedInt playerID) { m_playerID = playerID; }
	void setID(UnsignedShort id) { m_id = id; }
	NetCommandType getNetCommandType() const { return m_commandType; }

protected:
	void *m_vptr;
	UnsignedInt m_timestamp;
	UnsignedInt m_executionFrame;
	UnsignedInt m_playerID;
	UnsignedShort m_id;
	NetCommandType m_commandType;
	Int m_referenceCount;
};

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

class NetDestroyPlayerCommandMsg : public NetCommandMsg
{
public:
	NetDestroyPlayerCommandMsg();
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

class NetCommandList
{
public:
	virtual ~NetCommandList();
	NetCommandRef *getFirstMessage() { return m_first; }

private:
	NetCommandRef *m_first;
};

class NetCommandWrapperList
{
public:
	NetCommandList *getReadyCommands();
};

struct BfmeNetAddress
{
	UnsignedInt m_ip;
	UnsignedInt m_port;
};

#pragma pack(push, 1)
struct TransportMessage
{
	UnsignedInt crc;
	UnsignedByte data[0x400];
	Int length;
	UnsignedInt addr;
	UnsignedShort port;
};
#pragma pack(pop)

class Transport
{
public:
	TransportMessage m_outBuffer[MAX_MESSAGES];
	TransportMessage m_inBuffer[MAX_MESSAGES];
};

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

class BFMEConnectionManager
{
public:
	Bool isPlayerInGame(Int slot);
	Bool isDuplicateCommand(NetCommandMsg *msg);
	void relayCommand(void *ref);
};

class ConnectionManager
{
public:
	void doRelay();
	void sendLocalCommand(NetCommandMsg *msg, UnsignedByte relay);
	void rva004D316A(NetCommandList *list, const BfmeNetAddress *source);

private:
	void ackCommand(NetCommandRef *ref, const BfmeNetAddress *source);
	Bool processNetCommand(NetCommandRef *ref);

	void *m_vptr;
	void *m_connections[MAX_SLOTS];
	char m_pad00024[0x12024 - 0x24];
	Transport *m_transport;
	Int m_localSlot;
	Int m_packetRouterSlot;
	char m_pad12030[0x12080 - 0x12030];
	Int m_playerState[MAX_SLOTS];
	UnsignedInt m_playerLeaveValue[MAX_SLOTS];
	char m_pad120C0[0x1212c - 0x120c0];
	NetCommandWrapperList *m_netCommandWrapperList;
};

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
			if (m_playerLeaveValue[i] == 0)
			{
				NetDestroyPlayerCommandMsg *destroy = new NetDestroyPlayerCommandMsg;
				if (DoesCommandRequireACommandID(destroy->getNetCommandType()))
					destroy->setID(GenerateNextCommandID());
				destroy->setPlayerID(m_localSlot);
				destroy->setPlayerIndex(i);
				sendLocalCommand(destroy, 0xff);
				destroy->detach();
			}
			m_playerState[i] = 2;
		}
	}

	for (UnsignedInt i = 0; i < MAX_MESSAGES; ++i)
	{
		if (m_transport->m_inBuffer[i].length != 0)
		{
			NetPacket packet(&m_transport->m_inBuffer[i]);
			m_transport->m_inBuffer[i].length = 0;
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
