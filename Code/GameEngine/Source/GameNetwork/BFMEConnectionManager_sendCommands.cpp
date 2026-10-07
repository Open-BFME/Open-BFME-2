// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BFMEConnectionManager's periodic senders: the keep-alive pass, the two
// FRAMEINFO builders and the packet-router fallback broadcast.
//
// Donor: Open-BFME-1 game/GameEngine/Source/GameNetwork/native_connection_timing.cpp
// (sendKeepAliveCommand, sendFrameInfo, the naked FRAMEINFO body it calls
// sendFrameInfoToPlayer, broadcastRouterFallbackPlan): names, control flow and
// the router-score list are carried from the donor source.
//
// Target evidence: the bodies sit in BFME 2's connection-manager run between
// setFrameGrouping 0x004CF7F5 and processDisconnectChat 0x004D1023, read
// m_connections at +4, m_localSlot/m_packetRouterSlot at +0x12028/+0x1202C,
// m_frameCeiling at +0x1205C, m_playerLatestFrame at +0x12060,
// m_playerClientFrame at +0x120C0 and the FrameDataManager ring pointers at
// +0x12104, and call the NetKeepAliveCommandMsg (0x004D57C7), NetFrameCommandMsg
// (0x004CEEC3) and router-fallback (0x004CEEE8, held in the ledger as
// Rva004CEEE8) constructors, sendLocalCommandDirect 0x004CF6E4,
// sendLocalCommand 0x004CFF21 and NetCommandMsg::detach 0x004D55BC.
// BFME 2's sendFrameInfo takes a flag that sends the next logic frame instead
// of the current one (callers Network 0x0025E297 and the update pass
// 0x004D34C0); the donor's has no parameter. The second FRAMEINFO builder
// (0x004D0BE5, no direct caller in the image) takes no slot argument despite
// the donor's name for it, so it keeps an address name here.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;
typedef float Real;

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

enum NetCommandType
{
	NETCOMMANDTYPE_UNKNOWN = -1
};

class NetCommandMsg
{
public:
	void detach();
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

class NetKeepAliveCommandMsg : public NetCommandMsg
{
public:
	NetKeepAliveCommandMsg();
};

class NetFrameCommandMsg : public NetCommandMsg
{
public:
	NetFrameCommandMsg();
	UnsignedInt getFrame() const { return m_frame; }
	void setFrame(UnsignedInt frame) { m_frame = frame; }
	void setPlayerFrame(UnsignedInt frame) { m_playerFrame = frame; }
	void setCommandCount(UnsignedInt count) { m_commandCount = count; }

private:
	UnsignedInt m_frame;
	UnsignedInt m_playerFrame;
	UnsignedInt m_commandCount;
};

class BFMENetRouterFallbackCommandMsg : public NetCommandMsg
{
public:
	void setPlayerOrder(const Int *order);
};

// The router-fallback command (type 0x17), constructed at 0x004CEEE8.
class Rva004CEEE8 : public NetCommandMsg
{
public:
	Rva004CEEE8();

private:
	Int m_playerOrder[8];
};

class FrameDataManager
{
public:
	UnsignedInt getCommandCount(UnsignedInt frame);
	void setFrameCommandCount(UnsignedInt frame, UnsignedInt count);
	Bool getIsQuitting();
};

class Connection
{
public:
	Real getAverageLatency() const { return m_averageLatency; }
	UnsignedInt getLastTimeSent() const { return m_lastTimeSent; }

private:
	char m_pad000[0x20];
	Real m_averageLatency;
	char m_pad024[0x348 - 0x24];
	UnsignedInt m_lastTimeSent;
};

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }

private:
	char m_pad00[0x40];
	UnsignedInt m_frame;
};

class GameClient
{
public:
#define CLIENT_SLOT(n) virtual void slot##n();
	CLIENT_SLOT(00) CLIENT_SLOT(01) CLIENT_SLOT(02) CLIENT_SLOT(03) CLIENT_SLOT(04)
	CLIENT_SLOT(05) CLIENT_SLOT(06) CLIENT_SLOT(07) CLIENT_SLOT(08) CLIENT_SLOT(09)
	CLIENT_SLOT(10) CLIENT_SLOT(11) CLIENT_SLOT(12) CLIENT_SLOT(13) CLIENT_SLOT(14)
	CLIENT_SLOT(15) CLIENT_SLOT(16) CLIENT_SLOT(17) CLIENT_SLOT(18) CLIENT_SLOT(19)
	CLIENT_SLOT(20) CLIENT_SLOT(21) CLIENT_SLOT(22) CLIENT_SLOT(23) CLIENT_SLOT(24)
	CLIENT_SLOT(25) CLIENT_SLOT(26) CLIENT_SLOT(27) CLIENT_SLOT(28) CLIENT_SLOT(29)
	CLIENT_SLOT(30)
#undef CLIENT_SLOT
	virtual UnsignedInt getFrame(); // slot 0x7C
};

extern GameLogic *TheGameLogic;
extern GameClient *TheGameClient;
Bool DoesCommandRequireACommandID(NetCommandType type);
UnsignedShort GenerateNextCommandID();

class ConnectionManager
{
public:
	void sendLocalCommandDirect(NetCommandMsg *msg, UnsignedByte relay);
	void sendLocalCommand(NetCommandMsg *msg, UnsignedByte relay);
};

// Router succession list node: latency score, player and next.
struct BFMEPlayerRouterScore
{
	Real score;
	Int player;
	BFMEPlayerRouterScore *next;
};

class BFMEConnectionManager
{
public:
	void sendKeepAliveCommand();
	void sendFrameInfo(Bool nextFrame);
	void rva004D0BE5();
	void broadcastRouterFallbackPlan();

private:
	ConnectionManager *base() { return reinterpret_cast<ConnectionManager *>(this); }

	void *m_vptr;
	Connection *m_connections[8];
	char m_pad00024[0x12028 - 0x24];
	UnsignedInt m_localSlot;
	UnsignedInt m_packetRouterSlot;
	char m_pad12030[0x1205c - 0x12030];
	UnsignedInt m_frameCeiling;
	UnsignedInt m_playerLatestFrame[8];
	char m_pad12080[0x120c0 - 0x12080];
	UnsignedInt m_playerClientFrame[8];
	char m_pad120E0[0x12104 - 0x120e0];
	FrameDataManager *m_frameData[8];
};

// Queues a direct keep-alive to every connection silent for over a second.
void BFMEConnectionManager::sendKeepAliveCommand()
{
	UnsignedInt now = timeGetTime();
	for (Int player = 0; player < 8; ++player)
	{
		if (m_connections[player] && now - m_connections[player]->getLastTimeSent() > 1000)
		{
			NetKeepAliveCommandMsg *msg = new NetKeepAliveCommandMsg;
			msg->setPlayerID(m_localSlot);
			if (DoesCommandRequireACommandID(msg->getNetCommandType()) == true)
				msg->setID(GenerateNextCommandID());
			base()->sendLocalCommandDirect(msg, (UnsignedByte)(1 << player));
			msg->detach();
		}
	}
}

void BFMEConnectionManager::sendFrameInfo(Bool nextFrame)
{
	Int commandCount = -1;
	NetFrameCommandMsg *msg = new NetFrameCommandMsg;
	msg->setFrame(nextFrame ? TheGameLogic->getFrame() + 1 : TheGameLogic->getFrame());
	msg->setPlayerFrame(TheGameClient->getFrame());
	msg->setPlayerID(m_localSlot);
	if (DoesCommandRequireACommandID(msg->getNetCommandType()))
		msg->setID(GenerateNextCommandID());

	if (m_frameData[m_localSlot] != 0 && m_localSlot == m_packetRouterSlot)
	{
		commandCount = 0;
		for (Int i = 0; i < 8; ++i)
		{
			if (m_frameData[i] != 0 && !m_frameData[i]->getIsQuitting())
				commandCount += m_frameData[i]->getCommandCount(
					nextFrame ? TheGameLogic->getFrame() + 1 : TheGameLogic->getFrame());
		}
		m_frameData[m_localSlot]->setFrameCommandCount(msg->getFrame(), commandCount);
	}
	msg->setCommandCount(commandCount);

	if (m_localSlot == m_packetRouterSlot)
	{
		base()->sendLocalCommand(msg, (UnsignedByte)~(1 << m_localSlot));
		m_frameCeiling = msg->getFrame();
	}
	else
	{
		base()->sendLocalCommand(msg, (UnsignedByte)(1 << m_packetRouterSlot));
	}
	msg->detach();
}

void BFMEConnectionManager::rva004D0BE5()
{
	NetFrameCommandMsg *msg = new NetFrameCommandMsg;
	msg->setFrame(TheGameLogic->getFrame());
	msg->setPlayerFrame(TheGameClient->getFrame());
	if (DoesCommandRequireACommandID(msg->getNetCommandType()))
		msg->setID(GenerateNextCommandID());
	msg->setPlayerID(m_localSlot);
	if (m_localSlot == m_packetRouterSlot)
		base()->sendLocalCommand(msg, (UnsignedByte)~(1 << m_localSlot));
	else
		base()->sendLocalCommand(msg, (UnsignedByte)(1 << m_packetRouterSlot));
	msg->detach();
}

// Builds the router succession list: local player first, then remote players
// ordered by latency with a penalty for the client/logic frame ratio.
void BFMEConnectionManager::broadcastRouterFallbackPlan()
{
	BFMEPlayerRouterScore *head = 0;
	for (Int player = 0; player < 8; ++player)
	{
		if (m_connections[player])
		{
			Real score = m_connections[player]->getAverageLatency();
			Real frameRatio = (Real)m_playerClientFrame[player] / (Real)m_playerLatestFrame[player];
			if (frameRatio <= 20.0f)
				score += 1000.0f;
			BFMEPlayerRouterScore *node = new BFMEPlayerRouterScore;
			node->score = score;
			node->player = player;
			BFMEPlayerRouterScore *previous = 0;
			BFMEPlayerRouterScore *current = head;
			while (current)
			{
				if (current->score > score)
					break;
				previous = current;
				current = current->next;
			}
			node->next = current;
			if (previous)
				previous->next = node;
			else
				head = node;
		}
	}
	Int players[8];
	UnsignedInt count = 1;
	players[0] = m_localSlot;
	if (head)
	{
		while (head)
		{
			if (count < 8)
				players[count++] = head->player;
			BFMEPlayerRouterScore *next = head->next;
			delete head;
			head = next;
		}
		if (count > 2)
		{
			for (UnsignedInt i = count; i < 8; ++i)
				players[i] = -1;
			Rva004CEEE8 *msg = new Rva004CEEE8;
			((BFMENetRouterFallbackCommandMsg *)msg)->setPlayerOrder(players);
			msg->setPlayerID(m_localSlot);
			if (DoesCommandRequireACommandID(msg->getNetCommandType()))
				msg->setID(GenerateNextCommandID());
			base()->sendLocalCommand(msg, 0xFF);
			msg->detach();
		}
	}
}
