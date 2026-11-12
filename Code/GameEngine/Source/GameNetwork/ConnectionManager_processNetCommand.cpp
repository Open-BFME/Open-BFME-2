// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// platformsdk
// ConnectionManager::processNetCommand, retail 0x004D2F04, 614 bytes: the
// 518-byte body and its 24-entry jump table 0x004D310A.
//
// Reference: Open-BFME-1 native_connection_timing.cpp processIncomingCommand
// (BFME 1 0x0066A3F0), the same switch over the command type in the same case
// order. Zero Hour's ConnectionManager::processNetCommand is the if-chain this
// replaced: doRelay's loop (here 0x004D316A) acks the command, then calls this
// once per command. In BFME 2 a TRUE result is what sends the command on
// (0x004CF578), the reverse of Zero Hour's sense, as in BFME 1.
// BFME 2 differences read from this body: command type 20 is new (its handler
// 0x004CF1AD loads a slot's hero data), so FILEANNOUNCE, FILEPROGRESS and
// ROUTERFALLBACK move to 21-23, and the disconnect commands to 25-28. Chat
// goes to processChat 0x004D10F1. Frame info takes a count only for a frame
// past the current one. The latest and client frames are at +0x12060 and
// +0x120C0, the frame ceiling at +0x1205C, and the router fallback order at
// +0x12030.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;

enum NetCommandType
{
	NETCOMMANDTYPE_ACKBOTH = 0,
	NETCOMMANDTYPE_ACKSTAGE1 = 1,
	NETCOMMANDTYPE_ACKSTAGE2 = 2,
	NETCOMMANDTYPE_FRAMEINFO = 3,
	NETCOMMANDTYPE_REQUEST_GAMESPY_STATS_AUTHKEY = 5,
	NETCOMMANDTYPE_GAMESPY_STATS_AUTHKEY = 6,
	NETCOMMANDTYPE_REQUESTPLAYERLEAVE = 7,
	NETCOMMANDTYPE_INFORMPLAYERLEAVEFRAME = 8,
	NETCOMMANDTYPE_REQUESTFRAMEDATA = 9,
	NETCOMMANDTYPE_KEEPALIVE = 12,
	NETCOMMANDTYPE_DISCONNECTCHAT = 13,
	NETCOMMANDTYPE_CHAT = 14,
	NETCOMMANDTYPE_PROGRESS = 15,
	NETCOMMANDTYPE_LOADCOMPLETE = 16,
	NETCOMMANDTYPE_TIMEOUTSTART = 17,
	NETCOMMANDTYPE_WRAPPER = 18,
	NETCOMMANDTYPE_FILE = 19,
	NETCOMMANDTYPE_HERODATA = 20,
	NETCOMMANDTYPE_FILEANNOUNCE = 21,
	NETCOMMANDTYPE_FILEPROGRESS = 22,
	NETCOMMANDTYPE_ROUTERFALLBACK = 23,
	NETCOMMANDTYPE_DISCONNECTSTART = 24,
	NETCOMMANDTYPE_DISCONNECTEND = 29
};

enum
{
	MAX_SLOTS = 8
};

#include <windows.h>
#include <string.h>
#include "../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

// GameLogic's timeOutGameStart, held in the ledger as a folded byte setter.
class Rva0023CF83ByteOneSetter
{
public:
	void enable();
};

#include "../../Include/GameNetwork/NetCommandMsg.h"

#include "../../Include/GameNetwork/NetFrameCommandMsg.h"

class NetWrapperCommandMsg;
class NetProgressCommandMsg;
class NetDisconnectChatCommandMsg;
class NetChatCommandMsg;
class NetFileCommandMsg;
class NetFileAnnounceCommandMsg;
class NetFileProgressCommandMsg;

class NetCommandRef
{
public:
	NetCommandMsg *getCommand() { return m_msg; }

	NetCommandMsg *m_msg;
	NetCommandRef *m_next;
	NetCommandRef *m_prev;
	UnsignedByte m_relay;
};

class Connection
{
public:
	void setLastHeardFrom(UnsignedInt time) { m_lastHeardFrom = time; }

private:
	char m_pad000[0x34c];
	UnsignedInt m_lastHeardFrom;
};

#include "../../Include/GameNetwork/FrameDataManagerClass.h"

class ConnectionManager;

class DisconnectManager
{
public:
	void processDisconnectCommand(void *ref, ConnectionManager *conMgr);
};

#include "../../Include/GameNetwork/BFMEConnectionManager.h"

#include "../../Include/GameNetwork/ConnectionManager.h"

Bool ConnectionManager::processNetCommand(NetCommandRef *ref)
{
	NetCommandMsg *msg = ref->getCommand();
	UnsignedInt playerID = msg->getPlayerID();
	if (playerID >= MAX_SLOTS)
		goto ignored;
	if (playerID != (UnsignedInt)m_localSlot)
	{
		Connection *connection = m_connections[playerID];
		if (connection == 0)
			goto ignored;
		connection->setLastHeardFrom(timeGetTime());
	}

	switch (msg->getNetCommandType())
	{
	case NETCOMMANDTYPE_ACKBOTH:
	case NETCOMMANDTYPE_ACKSTAGE1:
	case NETCOMMANDTYPE_ACKSTAGE2:
		((BFMEConnectionManager *)this)->processAck(msg);
		return true;
	case NETCOMMANDTYPE_WRAPPER:
		processWrapper(ref);
		return true;
	case NETCOMMANDTYPE_FRAMEINFO:
	{
		NetFrameCommandMsg *frameMsg = (NetFrameCommandMsg *)msg;
		if (m_localSlot == m_packetRouterSlot)
		{
			if (frameMsg->getFrame() > field12060[playerID])
			{
				field12060[playerID] = frameMsg->getFrame();
				field120C0[playerID] = frameMsg->getPlayerFrame();
			}
		}
		else
		{
			if (frameMsg->getFrame() > field12060[playerID])
			{
				field12060[playerID] = frameMsg->getFrame();
				field120C0[playerID] = frameMsg->getPlayerFrame();
			}
			if (field1205C < frameMsg->getFrame())
				field1205C = frameMsg->getFrame();
			if (frameMsg->getFrame() > TheGameLogic->getFrame() &&
				frameMsg->getCommandCount() != -1)
				m_frameData[m_localSlot]->setFrameCommandCount(
					frameMsg->getFrame(), frameMsg->getCommandCount());
		}
		return false;
	}
	case NETCOMMANDTYPE_INFORMPLAYERLEAVEFRAME:
		((BFMEConnectionManager *)this)->processInformPlayerLeaveFrameCommand(msg);
		return false;
	case NETCOMMANDTYPE_REQUEST_GAMESPY_STATS_AUTHKEY:
		((BFMEConnectionManager *)this)->sendGameSpyStatsAuthKey(msg);
		return false;
	case NETCOMMANDTYPE_GAMESPY_STATS_AUTHKEY:
		((BFMEConnectionManager *)this)->processGameSpyStatsAuthKeyCommand(msg);
		return false;
	case NETCOMMANDTYPE_REQUESTFRAMEDATA:
		((BFMEConnectionManager *)this)->processRequestFrameDataCommand(msg);
		return false;
	case NETCOMMANDTYPE_REQUESTPLAYERLEAVE:
		rva004CF35D((NetWrapperCommandMsg *)msg);
		return false;
	case NETCOMMANDTYPE_ROUTERFALLBACK:
		memcpy(m_packetRouterFallback, (char *)msg + 0x1c, sizeof(m_packetRouterFallback));
		return true;
	case NETCOMMANDTYPE_PROGRESS:
		processProgress((NetProgressCommandMsg *)msg);
		ref->m_relay &= (UnsignedByte)~(1 << m_localSlot);
		return true;
	case NETCOMMANDTYPE_TIMEOUTSTART:
		((Rva0023CF83ByteOneSetter *)TheGameLogic)->enable();
		return true;
	case NETCOMMANDTYPE_DISCONNECTCHAT:
		processDisconnectChat((NetDisconnectChatCommandMsg *)msg);
		return true;
	case NETCOMMANDTYPE_LOADCOMPLETE:
		TheGameLogic->processProgressComplete(playerID);
		return true;
	case NETCOMMANDTYPE_CHAT:
		processChat((NetChatCommandMsg *)msg);
		return true;
	case NETCOMMANDTYPE_HERODATA:
		processHero(msg);
		return true;
	case NETCOMMANDTYPE_FILE:
		processFile((NetFileCommandMsg *)msg);
		return true;
	case NETCOMMANDTYPE_FILEANNOUNCE:
		processFileAnnounce((NetFileAnnounceCommandMsg *)msg);
		return true;
	case NETCOMMANDTYPE_FILEPROGRESS:
		processFileProgress((NetFileProgressCommandMsg *)msg);
		return true;
	case NETCOMMANDTYPE_KEEPALIVE:
		return false;
	default:
		if (msg->getNetCommandType() > NETCOMMANDTYPE_DISCONNECTSTART &&
			msg->getNetCommandType() < NETCOMMANDTYPE_DISCONNECTEND)
		{
			if (m_disconnectManager != 0)
				m_disconnectManager->processDisconnectCommand(ref, this);
			goto ignored;
		}
		return true;
	}
ignored:
	return false;
}
