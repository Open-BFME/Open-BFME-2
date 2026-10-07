// ?ackCommand@ConnectionManager@@AAEXPAVNetCommandRef@@PBUBfmeNetAddress@@@Z
// partial score=0.8 date=2026-10-07
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ConnectionManager::ackCommand, retail 0x004D2F04's sibling 0x004CF40E,
// 362 bytes.
//
// Reference: Zero Hour ConnectionManager::ackCommand. The relay mask over
// the live connections picks an ack-both or ack-stage-1 reply, stamped with
// the local slot, and a direct-send command is acked straight back to its
// sender; anything else goes through the packet router, or straight to the
// sender when this machine is the router.
// BFME 2 differences read from this body: the second parameter is the
// sender's network address (BFME 1 declares the same ackCommand(ref, source)
// in native_connection_timing.cpp), not the local slot, which is read from
// the manager. Before the router fallback the ack goes to the connection
// whose address matches the source (BfmeNetAddress compare 0x00248CBF), and
// that path returns without detaching the ack. Zero Hour's
// CommandRequiresAck test is gone: only CommandRequiresDirectSend 0x005812C4
// is called. A connection is live while its +0 quit frame is -1.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;

enum
{
	MAX_SLOTS = 8
};

struct BfmeNetAddress
{
	bool Rva00248CBF(const BfmeNetAddress *other) const;

	UnsignedInt m_ip;
	UnsignedShort m_port;
};

class NetCommandMsg
{
public:
	UnsignedInt getPlayerID() const { return m_playerID; }
	void setPlayerID(UnsignedInt playerID) { m_playerID = playerID; }
	void detach();

protected:
	void *m_vptr;
	UnsignedInt m_timestamp;
	UnsignedInt m_executionFrame;
	UnsignedInt m_playerID;
	UnsignedShort m_id;
	Int m_commandType;
	Int m_referenceCount;
};

class NetAckBothCommandMsg : public NetCommandMsg
{
public:
	NetAckBothCommandMsg(NetCommandMsg *msg);
	UnsignedShort getCommandID() const { return m_commandID; }
	UnsignedByte getOriginalPlayerID() const { return m_originalPlayerID; }

private:
	UnsignedShort m_commandID;
	UnsignedByte m_originalPlayerID;
	UnsignedInt m_originalTimestamp;
	UnsignedInt m_originalExecutionFrame;
};

class NetAckStage1CommandMsg : public NetCommandMsg
{
public:
	NetAckStage1CommandMsg(NetCommandMsg *msg);
	UnsignedShort getCommandID() const { return m_commandID; }
	UnsignedByte getOriginalPlayerID() const { return m_originalPlayerID; }

private:
	UnsignedShort m_commandID;
	UnsignedByte m_originalPlayerID;
	UnsignedInt m_originalTimestamp;
	UnsignedInt m_originalExecutionFrame;
};

Bool CommandRequiresDirectSend(NetCommandMsg *msg);

class NetCommandRef
{
public:
	NetCommandMsg *getCommand() { return m_msg; }
	UnsignedByte getRelay() const { return m_relay; }

private:
	NetCommandMsg *m_msg;
	NetCommandRef *m_next;
	NetCommandRef *m_prev;
	UnsignedByte m_relay;
};

class Connection
{
public:
	void sendNetCommandMsg(NetCommandMsg *msg, UnsignedByte relay);
	Bool isQuitting() const { return m_quitFrame != -1; }
	BfmeNetAddress getAddress() const { return m_address; }

private:
	Int m_quitFrame;
	UnsignedInt m_quitTime;
	void *m_transport;
	BfmeNetAddress m_address;
};

class ConnectionManager
{
private:
	void ackCommand(NetCommandRef *ref, const BfmeNetAddress *source);

	void *m_vptr;
	Connection *m_connections[MAX_SLOTS];
	char m_pad00024[0x12028 - 0x24];
	UnsignedInt m_localSlot;
	UnsignedInt m_packetRouterSlot;
};

void ConnectionManager::ackCommand(NetCommandRef *ref, const BfmeNetAddress *source)
{
	NetCommandMsg *msg = ref->getCommand();
	NetCommandMsg *ackmsg;
	BfmeNetAddress address;
	UnsignedByte sendRelay = 0;

	for (Int i = 0; i < MAX_SLOTS; ++i)
	{
		if (m_connections[i] != 0 && m_connections[i]->isQuitting() == false)
			sendRelay = sendRelay | (1 << i);
	}

	sendRelay = sendRelay & ref->getRelay();
	if (sendRelay == 0)
		ackmsg = new NetAckBothCommandMsg(ref->getCommand());
	else
		ackmsg = new NetAckStage1CommandMsg(ref->getCommand());

	ackmsg->setPlayerID(m_localSlot);

	if (CommandRequiresDirectSend(msg))
	{
		if (msg->getPlayerID() < MAX_SLOTS && m_connections[msg->getPlayerID()] != 0)
			m_connections[msg->getPlayerID()]->sendNetCommandMsg(ackmsg, 1 << msg->getPlayerID());
	}
	else
	{
		for (UnsignedByte i = 0; i < MAX_SLOTS; ++i)
		{
			if (m_connections[i] != 0 && source != 0)
			{
				address = m_connections[i]->getAddress();
				if (address.Rva00248CBF(source))
				{
					m_connections[i]->sendNetCommandMsg(ackmsg, 1 << i);
					return;
				}
			}
		}

		if (m_packetRouterSlot < MAX_SLOTS)
		{
			if (m_connections[m_packetRouterSlot] != 0)
			{
				m_connections[m_packetRouterSlot]->sendNetCommandMsg(ackmsg, 1 << m_packetRouterSlot);
			}
			else if (m_localSlot == m_packetRouterSlot)
			{
				if (msg->getPlayerID() < MAX_SLOTS && m_connections[msg->getPlayerID()] != 0)
					m_connections[msg->getPlayerID()]->sendNetCommandMsg(ackmsg, 1 << msg->getPlayerID());
			}
		}
	}

	ackmsg->detach();
}
