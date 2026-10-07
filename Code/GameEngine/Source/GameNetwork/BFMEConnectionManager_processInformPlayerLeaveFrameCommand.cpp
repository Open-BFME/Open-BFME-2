// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?processInformPlayerLeaveFrameCommand@BFMEConnectionManager@@QAEXPAX@Z,
// retail 0x004CFD06 286 bytes through RET 4.
// Donor: Open-BFME-1 game/GameEngine/Source/GameNetwork/native_connection_timing.cpp
// BFMEConnectionManager::processInformPlayerLeaveFrameCommand (names, frameMaximum
// and the request-frame-data reply). Target evidence: leave frame and leaving
// player read through the folded +0x1C/+0x20 getters 0x0030F2C7/0x0030D377 (held
// in the ledger under NetWrapperCommandMsg's names), TheGameLogic+0x40 frame plus
// TheWritableGlobalData+0xC18 run-ahead slack, m_playerLatestFrame at +0x12060,
// m_localSlot at +0x12028, operator new 0x24 + the request-frame-data ctor
// 0x004D5A30, its first/last frame set through the folded setters 0x00318B09 and
// 0x00317B9B, DoesCommandRequireACommandID 0x005811B5, GenerateNextCommandID
// 0x005811A8, sendLocalCommandDirect 0x004CF6E4 and NetCommandMsg::detach
// 0x004D55BC. BFME 2 also stamps the request's timestamp from TheGameLogic+0x38,
// and loads frame and slack into registers before adding them (the locals).

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

enum NetCommandType
{
	NETCOMMANDTYPE_UNKNOWN = -1
};

class NetCommandMsg
{
public:
	void detach();
	UnsignedInt getPlayerID() const { return m_playerID; }
	void setPlayerID(UnsignedInt playerID) { m_playerID = playerID; }
	void setTimestamp(UnsignedInt timestamp) { m_timestamp = timestamp; }
	void setExecutionFrame(UnsignedInt frame) { m_executionFrame = frame; }
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

// Folded getters at 0x0030F2C7 (+0x1C) and 0x0030D377 (+0x20).
class NetWrapperCommandMsg : public NetCommandMsg
{
public:
	UnsignedByte *getData();
	UnsignedInt getDataLength();
};

// Folded setters at 0x00318B09 (+0x1C) and 0x00317B9B (+0x20).
class Rva004D57AE : public NetCommandMsg
{
public:
	void setPlayerIndex(UnsignedInt value);
};

class BFMENetInformPlayerLeaveFrameCommandMsg : public NetCommandMsg
{
public:
	void setLeavingPlayerID(Int value);
};

// BFME's request-frame-data command (type 9), constructed at 0x004D5A30.
class Rva004D5A30 : public NetCommandMsg
{
public:
	Rva004D5A30();

private:
	UnsignedInt m_firstFrame;
	UnsignedInt m_lastFrame;
};

class GlobalData
{
public:
	char m_pad000[0xc18];
	UnsignedInt m_networkRunAheadSlack;
};

class GameLogic
{
public:
	char m_pad00[0x38];
	UnsignedInt m_timestampFrame;
	char m_pad3C[4];
	UnsignedInt m_frame;
};

extern GlobalData *TheWritableGlobalData;
extern GameLogic *TheGameLogic;
Int DoesCommandRequireACommandID(NetCommandType type);
UnsignedShort GenerateNextCommandID();

class ConnectionManager
{
public:
	void sendLocalCommandDirect(NetCommandMsg *msg, UnsignedByte relay);
};

template <class T> inline const T &frameMaximum(const T &a, const T &b)
{
	return b > a ? b : a;
}

class BFMEConnectionManager
{
public:
	void processInformPlayerLeaveFrameCommand(void *command);

private:
	char m_pad00000[0x12028];
	UnsignedInt m_localSlot;
	char m_pad1202C[0x12060 - 0x1202c];
	UnsignedInt m_playerLatestFrame[8];
};

void BFMEConnectionManager::processInformPlayerLeaveFrameCommand(void *command)
{
	NetWrapperCommandMsg *msg = static_cast<NetWrapperCommandMsg *>(command);
	if (msg == 0)
		return;
	UnsignedInt leaveFrame = (UnsignedInt)msg->getData();
	UnsignedShort leavingPlayer = (UnsignedShort)msg->getDataLength();
	UnsignedInt frame = TheGameLogic->m_frame;
	UnsignedInt slack = TheWritableGlobalData->m_networkRunAheadSlack;
	if (leaveFrame < slack + frame)
	{
		if (msg->getPlayerID() < 8)
			m_playerLatestFrame[msg->getPlayerID()] = frameMaximum(leaveFrame, m_playerLatestFrame[msg->getPlayerID()]);
	}
	if (TheGameLogic->m_frame < leaveFrame && leavingPlayer != m_localSlot)
	{
		Rva004D5A30 *request = new Rva004D5A30;
		request->setPlayerID(m_localSlot);
		request->setTimestamp(TheGameLogic->m_timestampFrame);
		request->setExecutionFrame((UnsignedInt)-1);
		((Rva004D57AE *)request)->setPlayerIndex(TheGameLogic->m_frame + 1);
		((BFMENetInformPlayerLeaveFrameCommandMsg *)request)->setLeavingPlayerID(leaveFrame);
		if ((UnsignedByte)DoesCommandRequireACommandID(request->getNetCommandType()))
			request->setID(GenerateNextCommandID());
		if (msg->getPlayerID() < 8)
			reinterpret_cast<ConnectionManager *>(this)->sendLocalCommandDirect(request, (UnsignedByte)1 << msg->getPlayerID());
		request->detach();
	}
}
