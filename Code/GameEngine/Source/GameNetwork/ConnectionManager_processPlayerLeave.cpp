// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ConnectionManager::processPlayerLeave, retail 0x004D1D37, 378 bytes.
//
// Reference: Zero Hour GameEngine/Source/GameNetwork/ConnectionManager.cpp
// processPlayerLeave (mark the leaving player's connection and frame data as
// quitting, or every connection when the local player leaves; disconnect the
// player and act on the leave code).
// BFME 2 differences read from this body: the leaving slot arrives as a byte
// rather than inside the command (Network's player-leave handler 0x0025E5F4
// pushes the byte and tests the result against PLAYERLEAVECODE_LOCAL, as Zero
// Hour's Network::processPlayerLeaveCommand does); Connection::setQuitting
// takes the quit frame, the next logic frame; the frame data quits the
// GlobalData +0xC18 frames later; and when the packet router left, instead of
// resendPendingCommands, a leave-frame command (type 8, built by 0x004D59D1)
// carrying the current frame and the leaving slot goes to every other
// connected player through sendLocalCommandDirect.
// isPlayerConnected (0x004CF083, rowed as BFMEConnectionManager's in
// ConnectionManagerPlayerPredicates.cpp) is defined here too: retail keeps the
// local slot in EBX and the connection pointer in EDX across the call, which
// MSVC does only when it has compiled the callee in the same unit.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;

enum PlayerLeaveCode
{
	PLAYERLEAVECODE_CLIENT = 0,
	PLAYERLEAVECODE_LOCAL,
	PLAYERLEAVECODE_PACKETROUTER,
	PLAYERLEAVECODE_UNKNOWN
};

enum NetCommandType
{
	NETCOMMANDTYPE_UNKNOWN = -1
};

enum
{
	MAX_SLOTS = 8
};

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }
	UnsignedInt getTimestamp() const { return m_timestamp; }

private:
	char m_pad00[0x38];
	UnsignedInt m_timestamp;
	char m_pad3C[0x40 - 0x3c];
	UnsignedInt m_frame;
};

class GlobalData
{
public:
	char m_pad000[0xc18];
	Int m_quitFrameDelay;
};

class Connection
{
public:
	void clearCommandsExceptFrom(Int playerID);
	void setQuitting(UnsignedInt quitFrame);
	Int getQuitState() const { return m_quitState; }

private:
	Int m_quitState;
};

class FrameDataManager
{
public:
	Bool getIsQuitting();
	void setQuitFrame(UnsignedInt quitFrame);
};

class NetCommandMsg
{
public:
	void detach();
	void setTimestamp(UnsignedInt timestamp) { m_timestamp = timestamp; }
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

// The type-8 leave-frame command (BFMENetInformPlayerLeaveFrameCommandMsg),
// held in the ledger under its constructor's address name.
class Rva004D59D1 : public NetCommandMsg
{
public:
	Rva004D59D1();

private:
	char m_pad1C[0x24 - 0x1c];
};

class BFMENetInformPlayerLeaveFrameCommandMsg
{
public:
	void setLeaveFrame(UnsignedInt frame);
	void setLeavingPlayerID(Int playerID);
};

Bool DoesCommandRequireACommandID(NetCommandType type);
UnsignedShort GenerateNextCommandID();

extern GameLogic *TheGameLogic;
extern GlobalData *TheGlobalData;

class ConnectionManager
{
public:
	PlayerLeaveCode processPlayerLeave(UnsignedByte playerID);
	PlayerLeaveCode disconnectPlayer(Int slot);
	Bool isPlayerConnected(Int playerID);
	void sendLocalCommandDirect(NetCommandMsg *msg, UnsignedByte relay);

private:
	void *m_vptr;
	Connection *m_connections[MAX_SLOTS];
	char m_pad00024[0x12028 - 0x24];
	Int m_localSlot;
	char m_pad1202C[0x12104 - 0x1202c];
	FrameDataManager *m_frameData[MAX_SLOTS];
};

// ?isPlayerConnected@ConnectionManager@@QAE_NH@Z present-unmatched
Bool ConnectionManager::isPlayerConnected(Int playerID)
{
	return playerID == m_localSlot ||
		(m_connections[playerID] != 0 && m_connections[playerID]->getQuitState() == -1);
}

PlayerLeaveCode ConnectionManager::processPlayerLeave(UnsignedByte playerID)
{
	if (playerID == m_localSlot)
	{
		// we're leaving, so mark our connections to go away.
		for (Int i = 0; i < MAX_SLOTS; ++i)
		{
			if (m_connections[i])
			{
				m_connections[i]->clearCommandsExceptFrom(m_localSlot);
				m_connections[i]->setQuitting(TheGameLogic->getFrame() + 1);
			}
		}
	}
	else
	{
		UnsignedInt quitFrame = TheGameLogic->getFrame() + 1;
		if (m_connections[playerID] != 0)
			m_connections[playerID]->setQuitting(quitFrame);
		if ((m_frameData[playerID] != 0) && (m_frameData[playerID]->getIsQuitting() == false))
			m_frameData[playerID]->setQuitFrame(TheGlobalData->m_quitFrameDelay + quitFrame);
	}

	PlayerLeaveCode code = disconnectPlayer(playerID);
	if (code == PLAYERLEAVECODE_PACKETROUTER)
	{
		UnsignedByte mask = 0;
		for (Int i = 0; i < MAX_SLOTS; ++i)
		{
			if ((i != m_localSlot) && (m_connections[i] != 0) && isPlayerConnected(i))
				mask |= 1 << i;
		}

		if (mask != 0)
		{
			Rva004D59D1 *msg = new Rva004D59D1;
			msg->setPlayerID(m_localSlot);
			msg->setTimestamp(TheGameLogic->getTimestamp());
			msg->setExecutionFrame(-1);
			if (DoesCommandRequireACommandID(msg->getNetCommandType()))
				msg->setID(GenerateNextCommandID());
			((BFMENetInformPlayerLeaveFrameCommandMsg *)msg)->setLeaveFrame(TheGameLogic->getFrame());
			((BFMENetInformPlayerLeaveFrameCommandMsg *)msg)->setLeavingPlayerID(playerID);
			sendLocalCommandDirect(msg, mask);
			msg->detach();
		}
	}
	return code;
}
