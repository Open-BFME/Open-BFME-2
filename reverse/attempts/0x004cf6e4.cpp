// ?sendLocalCommandDirect@ConnectionManager@@QAEXPAVNetCommandMsg@@E@Z
// partial score=0.96 date=2026-10-08
// ?relayCommand@BFMEConnectionManager@@QAEXPAX@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX /O1 /G7 /ICode/GameEngine/Source/Common
//
// BFME2's client frame gate totals the command counts held by its eight
// per-player frame rings.  The local ring stores the expected total; the
// aggregate is complete only when those values agree for the requested frame.

enum NetCommandType
{
	NETCOMMANDTYPE_UNKNOWN = -1,
	NETCOMMANDTYPE_PLAYERLEAVE = 10
};

int IsCommandSynchronized(NetCommandType type);

typedef unsigned short UnsignedShort;

class NetCommandMsg
{
public:
	NetCommandMsg(void);
	virtual ~NetCommandMsg(void);
	virtual int getSortNumber(void);
	virtual void prepareForRelay(void);
	void attach(void);
	void detach(void);

	void setExecutionFrame(unsigned int frame) { m_executionFrame = frame; }
	unsigned int getExecutionFrame(void) { return m_executionFrame; }
	unsigned int getPlayerID(void) { return m_playerID; }
	NetCommandType getNetCommandType(void) { return m_commandType; }
	unsigned int getTimestamp(void) { return m_timestamp; }

	unsigned int m_timestamp;
	unsigned int m_executionFrame;
	unsigned int m_playerID;
	UnsignedShort m_id;
	char m_pad12[2];
	NetCommandType m_commandType;
	int m_referenceCount;
};

class NetCommandRef
{
public:
	NetCommandRef(NetCommandMsg *message);
	void setRelay(unsigned char value) { relay = value; }
	unsigned char getRelay(void) { return relay; }
	NetCommandMsg *getCommand(void) { return msg; }

	NetCommandMsg *msg;
	NetCommandRef *next;
	NetCommandRef *prev;
	unsigned char relay;
	unsigned int m_timeLastSent;
};

struct FrameDataManager
{
	bool getIsQuitting(void);
	unsigned int getCommandCount(unsigned int frame);
	unsigned int getFrameCommandCount(unsigned int frame);
	NetCommandRef *addNetCommandMsg(NetCommandMsg *msg);
};

class Connection
{
public:
	void sendNetCommandMsg(NetCommandMsg *msg, unsigned char relay);
};

#include "GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

class GlobalData
{
public:
	char m_pad000[0xC18];
	unsigned int m_networkRunAheadSlack;
};

extern GlobalData *TheWritableGlobalData;

class ConnectionManager {
public:
    void sendLocalCommandDirect(NetCommandMsg *, unsigned char);
    void sendLocalCommand(NetCommandMsg *, unsigned char);
private:
    void *vptr;
    Connection *m_connections[8];
    unsigned char opaque24[0x12028-0x24];
    unsigned int m_localSlot, m_packetRouterSlot;
    unsigned char opaque12030[0x12104-0x12030];
    FrameDataManager *m_frameData[8];
};
bool CommandRequiresDirectSend(NetCommandMsg *);

void ConnectionManager::sendLocalCommandDirect(NetCommandMsg *msg, unsigned char relay)
{
    msg->attach();
    unsigned int timestamp;
    if (msg->getExecutionFrame() == (unsigned int)-1) {
        GameLogic *logic = TheGameLogic;
        unsigned int frame = logic->getFrame();
        timestamp = logic->getTimestamp();
        msg->setExecutionFrame(frame + 1);
    } else if (msg->getTimestamp() == (unsigned int)-1) {
        timestamp = TheGameLogic->getTimestamp();
    } else goto stampDone;
    msg->m_timestamp = timestamp;
stampDone:
    if ((relay & (1 << m_localSlot)) != 0 &&
        (unsigned char)IsCommandSynchronized(msg->getNetCommandType()) &&
        m_localSlot < 8 && m_frameData[m_localSlot] != 0)
        m_frameData[m_localSlot]->addNetCommandMsg(msg);
    for (int i=0; i<8; ++i) {
        if ((relay & (1 << i)) != 0 && m_connections[i] != 0)
            m_connections[i]->sendNetCommandMsg(msg, (unsigned char)(1 << i));
    }
    msg->detach();
}

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
        msg->m_timestamp = timestamp;
        msg->setExecutionFrame(frame + 1);
        for (int i=0; i<8; ++i) {
            if ((relay & (1 << i)) != 0 && m_connections[i] != 0)
                m_connections[i]->sendNetCommandMsg(msg, (unsigned char)(1 << i));
        }
        if (m_localSlot < 8 && (relay & (1 << m_localSlot)) != 0 && m_frameData[m_localSlot] != 0)
            m_frameData[m_localSlot]->addNetCommandMsg(msg);
    } else if (m_packetRouterSlot < 8 && m_connections[m_packetRouterSlot] != 0) {
        if (msg->getTimestamp() == (unsigned int)-1)
            msg->m_timestamp = TheGameLogic->getTimestamp();
        m_connections[m_packetRouterSlot]->sendNetCommandMsg(msg, relay);
    }
    msg->detach();
}
