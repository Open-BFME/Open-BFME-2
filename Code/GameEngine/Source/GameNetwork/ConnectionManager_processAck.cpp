// cl: /ICode/GameEngine/Source/Common /G7 /O1 -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/GameNetwork

// BFMEConnectionManager::processAck, native 0x004D094C, 56 bytes.
//
// The reference's three-way dispatch: ACKBOTH runs both stages, ACKSTAGE1 the
// first, ACKSTAGE2 the second. Stage two is the ledger's
// ?processAckCommand@BFMEConnectionManager@@QAEXPAX@Z at native 0x004D0815; stage one
// is the existing out-of-line provider at native 0x004CFCD1.
//
// BFME's stage one is the reference's minus its latency bookkeeping: the
// reference checks whether the acknowledged command was a FRAMEINFO and feeds
// its frame to m_frameMetrics.processLatencyResponse. Retail does no such thing
// -- it deletes the returned reference and stops. That is one more piece of the
// adaptive-latency layer that FINDINGS already shows is absent.

#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

enum NetCommandType
{
	NETCOMMANDTYPE_ACKBOTH = 0,
	NETCOMMANDTYPE_ACKSTAGE1 = 1,
	NETCOMMANDTYPE_ACKSTAGE2 = 2
};

enum { NUM_CONNECTIONS = 8 };

void __cdecl operator delete(void *block) throw();

class NetCommandRef;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetCommandMsg
{
public:
	void attach();
	void detach();
	UnsignedInt getExecutionFrame() const { return m_executionFrame; }
	void setExecutionFrame(UnsignedInt frame) { m_executionFrame = frame; }
	void setTimestamp(UnsignedInt timestamp) { m_timestamp = timestamp; }
	UnsignedInt getTimestamp() { return m_timestamp; }
	Int getNetCommandType() { return m_commandType; }
	UnsignedInt getPlayerID() { return m_playerID; }

	void *m_vptr;
	UnsignedInt m_timestamp;						// this+0x04
	UnsignedInt m_executionFrame;					// this+0x08
	UnsignedInt m_playerID;							// this+0x0C
	UnsignedShort m_id;								// this+0x10
	Int m_commandType;								// this+0x14
	Int m_referenceCount; // target +0x18; allocation/ctor evidence
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandRef.h
class NetCommandRef
{
public:
	~NetCommandRef();
	UnsignedByte getRelay() { return relay; }
	NetCommandMsg *msg;
	NetCommandRef *next, *prev;
	UnsignedByte relay; // target +0x0C
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/Connection.h
class Connection
{
public:
	NetCommandRef *processAck(NetCommandMsg *msg);
	void sendNetCommandMsg(NetCommandMsg *msg, UnsignedByte relay);
};

class NetAckBothCommandMsg : public NetCommandMsg {
public:
    UnsignedShort getCommandID();
    unsigned char getOriginalPlayerID();
    unsigned int getOriginalExecutionFrame() { return originalFrame; }
private:
    UnsignedShort commandID;
    unsigned char originalPlayer;
    unsigned int originalTimestamp, originalFrame;
};
class NetAckStage2CommandMsg : public NetCommandMsg {
public:
    NetAckStage2CommandMsg(NetCommandMsg *);
    UnsignedShort getCommandID();
    unsigned char getOriginalPlayerID();
    unsigned int getOriginalExecutionFrame() { return originalFrame; }
private:
    UnsignedShort commandID;
    unsigned char originalPlayer;
    unsigned int originalTimestamp, originalFrame;
};
class NetCommandList {
public:
    NetCommandRef *findMessage(UnsignedShort, unsigned char, unsigned int);
    NetCommandRef *findMessage(UnsignedShort, unsigned char, NetCommandType, unsigned int);
    void removeMessage(NetCommandRef *);
};
class FrameDataManager {
public:
    NetCommandRef *addNetCommandMsg(NetCommandMsg *msg);
};
bool CommandRequiresDirectSend(NetCommandMsg *msg);

class ConnectionManager {
public:
    void sendLocalCommand(NetCommandMsg *, unsigned char);
    void sendLocalCommandDirect(NetCommandMsg *, unsigned char);
private:
    void *m_vptr;
    Connection *m_connections[8];
    unsigned char opaque24[0x12028-0x24];
    UnsignedInt m_localSlot, m_packetRouterSlot;
    unsigned char opaque12030[0x12104-0x12030];
    FrameDataManager *m_frameData[8];
};

class BFMEConnectionManager
{
public:
	void processAck(NetCommandMsg *msg);
	void processAckCommand(void *msg);

protected:
	void processAckStage1(NetCommandMsg *msg);

	void *m_vptr;
	Connection *m_connections[NUM_CONNECTIONS];		// this+0x04 .. +0x24
	unsigned char m_unreconstructed_24[0x12100];
	NetCommandList *m_pendingCommands; // target +0x12124
	NetCommandList *m_pendingRelays; // target +0x12128
};

// Called from both the ACKBOTH and ACKSTAGE1 paths of processAck below. Kept
// as a definition (not rowed) because removing it would change the caller's
// inlining and therefore its bytes.
void BFMEConnectionManager::processAckStage1(NetCommandMsg *msg) {
	UnsignedByte playerID = msg->getPlayerID();
	NetCommandRef *ref = 0;

	if (playerID < NUM_CONNECTIONS) {
		if (m_connections[playerID] != 0) {
			ref = m_connections[playerID]->processAck(msg);
		}
	}

	if (ref != 0) {
		delete ref;
	}
}

void BFMEConnectionManager::processAck(NetCommandMsg *msg) {
	if (msg->getNetCommandType() == NETCOMMANDTYPE_ACKBOTH) {
		processAckStage1(msg);
		processAckCommand(msg);
	} else if (msg->getNetCommandType() == NETCOMMANDTYPE_ACKSTAGE1) {
		processAckStage1(msg);
	} else if (msg->getNetCommandType() == NETCOMMANDTYPE_ACKSTAGE2) {
		processAckCommand(msg);
	}
}

// Native 4D0815..4D094C RET4: both acknowledgment kinds retire pending
// commands and clear relay recipients. BFME1 ba7ddda7 native_connection_timing
// supplies the clean C++ control flow; target proves list offsets12124/12128,
// message timestamp4, original frame24, and the existing 3/4-argument searches.
// Branch-local field assignments preserve target temporary/register lifetimes.
// NetAckStage2's 40-byte allocation and ctor4D570C independently prove its size.
void BFMEConnectionManager::processAckCommand(void *command)
{
	NetCommandMsg *msg = static_cast<NetCommandMsg *>(command);
	unsigned int commandTimestamp;
	UnsignedShort commandID;
	unsigned char originalPlayerID;
	unsigned int originalExecutionFrame;
	if (msg->getNetCommandType() == NETCOMMANDTYPE_ACKSTAGE2)
	{
		NetAckStage2CommandMsg *ack = static_cast<NetAckStage2CommandMsg *>(msg);
		commandID = ack->getCommandID();
		originalPlayerID = ack->getOriginalPlayerID();
		commandTimestamp = msg->getTimestamp();
		originalExecutionFrame = ack->getOriginalExecutionFrame();
	}
	else if (msg->getNetCommandType() == NETCOMMANDTYPE_ACKBOTH)
	{
		NetAckBothCommandMsg *ack = static_cast<NetAckBothCommandMsg *>(msg);
		commandID = ack->getCommandID();
		originalPlayerID = ack->getOriginalPlayerID();
		commandTimestamp = msg->getTimestamp();
		originalExecutionFrame = ack->getOriginalExecutionFrame();
	}
	else
		return;



	if (m_pendingCommands != 0)
	{
		NetCommandRef *ref = m_pendingCommands->findMessage(commandID, originalPlayerID, commandTimestamp);
		if (ref != 0)
		{
			m_pendingCommands->removeMessage(ref);
			delete ref;
		}
	}
	if (m_pendingRelays != 0)
	{
		NetCommandRef *ref = m_pendingRelays->findMessage(commandID, originalPlayerID, (NetCommandType)commandTimestamp, originalExecutionFrame);
		if (ref != 0)
		{
			unsigned char relay = ref->getRelay() & ~(1 << msg->getPlayerID());
			if (relay == 0)
			{
				m_pendingRelays->removeMessage(ref);
				NetAckStage2CommandMsg *ack = new NetAckStage2CommandMsg(ref->msg);
				reinterpret_cast<ConnectionManager *>(this)->sendLocalCommand(ack, (unsigned char)1 << ack->getOriginalPlayerID());
				delete ref;
				ack->detach();
			}
			else
				ref->relay = relay;
		}
	}
}

// Routed local command sender from the same native command-manager run.
void ConnectionManager::sendLocalCommand(NetCommandMsg *msg, unsigned char relay)
{
    if (CommandRequiresDirectSend(msg) || m_packetRouterSlot >= 8 || m_connections[m_packetRouterSlot] == 0) {
        sendLocalCommandDirect(msg, relay);
        return;
    }
    msg->attach();
    if (m_localSlot == m_packetRouterSlot) {
        GameLogic *logic = TheGameLogic;
        unsigned int frame = logic->getFrame();
        unsigned int timestamp = logic->getTimestamp();
        msg->setTimestamp(timestamp);
        msg->setExecutionFrame(frame + 1);
        for (int i=0; i<8; ++i) {
            if ((relay & (1 << i)) != 0 && m_connections[i] != 0)
                m_connections[i]->sendNetCommandMsg(msg, (unsigned char)(1 << i));
        }
        if (m_localSlot < 8 && (relay & (1 << m_localSlot)) != 0 && m_frameData[m_localSlot] != 0)
            m_frameData[m_localSlot]->addNetCommandMsg(msg);
    } else if (m_packetRouterSlot < 8 && m_connections[m_packetRouterSlot] != 0) {
        if (msg->getTimestamp() == (unsigned int)-1)
            msg->setTimestamp(TheGameLogic->getTimestamp());
        m_connections[m_packetRouterSlot]->sendNetCommandMsg(msg, relay);
    }
    msg->detach();
}
