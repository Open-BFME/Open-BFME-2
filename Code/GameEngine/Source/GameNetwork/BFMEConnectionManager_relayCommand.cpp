// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX /O1 /G7 /ICode/GameEngine/Source/Common
// ?relayCommand@BFMEConnectionManager@@QAEXPAX@Z @0x004CF578 236B
//
// BFME2's client frame gate totals the command counts held by its eight
// per-player frame rings.  The local ring stores the expected total; the
// aggregate is complete only when those values agree for the requested frame.

enum NetCommandType
{
	NETCOMMANDTYPE_UNKNOWN = -1,
	NETCOMMANDTYPE_PLAYERLEAVE = 10
};

bool IsCommandSynchronized(NetCommandType type);

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

class BFMEConnectionManager
{
public:
	bool areFrameCommandsComplete(unsigned int frame, bool debugSpewage);
	void relayCommand(void *ref);

private:
	char unknown0[4];
	Connection *m_connections[8];
	char unknown24[0x12004];
	unsigned int m_localSlot;
	char unknown1202c[0xd8];
	FrameDataManager *m_frameData[8];
};

// areFrameCommandsComplete (0x004CF799) is rowed and defined in
// ConnectionManagerFrameCommands.cpp; declared here only.

// Evidence: donor BFME1 relayCommand game/GameEngine/Source/GameNetwork/native_connection_timing.cpp (NetCommandRef msg+0 relay+0xC; prepareForRelay slot+8; PLAYERLEAVE 10; IsCommandSynchronized/addNetCommandMsg/sendNetCommandMsg rows); BFME2 repairs: GameLogic m_timestampFrame+0x38 m_frame+0x40 (doSend.cpp) exec frame+1 plus timestamp stamp; GlobalData m_networkRunAheadSlack+0xC18; caller 0x004D320B.
void BFMEConnectionManager::relayCommand(void *ref)
{
	NetCommandRef *commandRef = (NetCommandRef *)ref;
	NetCommandMsg *msg = (commandRef?commandRef:commandRef)->msg;
	if (!msg)
		return;
	unsigned int timestamp;
	if ((msg?msg:msg)->getExecutionFrame() == (unsigned int)-1)
	{
		GameLogic *logic = TheGameLogic;
		unsigned int frame = (logic?logic:logic)->getFrame();
		timestamp = (logic?logic:logic)->getTimestamp();
		(msg?msg:msg)->setExecutionFrame(frame + 1);
	}
	else if ((msg?msg:msg)->getTimestamp() == (unsigned int)-1)
	{
		timestamp = (TheGameLogic?TheGameLogic:TheGameLogic)->getTimestamp();
	}
	else goto afterStamp;
	(msg?msg:msg)->m_timestamp = timestamp;
afterStamp:
	if ((msg?msg:msg)->getExecutionFrame() + (TheWritableGlobalData?TheWritableGlobalData:TheWritableGlobalData)->m_networkRunAheadSlack < (TheGameLogic?TheGameLogic:TheGameLogic)->getFrame())
		return;
	unsigned char relay = (commandRef?commandRef:commandRef)->relay;
	if ((relay & (1 << m_localSlot)) == 0)
		return;
	if (m_frameData[(msg?msg:msg)->getPlayerID()] == 0 ||
		!(unsigned char)IsCommandSynchronized((msg?msg:msg)->getNetCommandType()))
		return;
	if ((msg?msg:msg)->getPlayerID() == m_localSlot &&
		(msg?msg:msg)->getNetCommandType() != NETCOMMANDTYPE_PLAYERLEAVE)
		(msg?msg:msg)->prepareForRelay();
	if (m_frameData[(msg?msg:msg)->getPlayerID()]->addNetCommandMsg(msg) == 0)
		return;
	for (int i = 0; i < 8; ++i)
	{
		if ((relay & (1u << i)) != 0 && m_connections[i] != 0)
			m_connections[i]->sendNetCommandMsg(msg, (unsigned char)(1u << i));
	}
}
