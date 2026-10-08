// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ConnectionManager::update, retail 0x004D342A, 802 bytes: vtable 0x008601C0
// slot 3, called with the in-game flag and the frame-advance flag.
//
// Reference: Zero Hour ConnectionManager::update (return without a local
// address, receive, update the disconnect manager in game, relay, then send
// every connection, drop a quitting connection whose queue has drained and a
// quitting slot's frame data on its quit frame, and send the transport).
// BFME 2 differences read from this body: the address test returns only when
// both address and port are zero; the transport and disconnect manager are
// null-checked; on a frame advance the router waiting on a pending leave
// raises the frame ceiling (+0x1205C) to the next logic frame and everyone
// else sends frame info 0x004D0AA9; the keep-alive is
// sendKeepAliveCommand 0x004CF828; a connection quits once its +0 quit frame
// is not after the logic frame. New is a one-shot GameSpy stats step behind
// the +0x12135 flag: in a game with a stats handle (staging room +0xFF4,
// handle +0x101C) whose challenge is not "NULLGAME", broadcast the challenge
// in a type-5 request 0x004D64F5 to every other slot, answer it locally with
// GenerateAuthA over the buddy queue's secret, and fill the local slot's
// login name and locale if the login is still empty; then clear the flag.
// The flag is left set while the stats game is unnamed.
// Connection's destructor is rowed under its address name 0x004D060B.

#include "ascii_string.h"
#include "../Common/GameLogicObjectLookupView.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;

enum NetCommandType
{
	NETCOMMANDTYPE_UNKNOWN = -1
};

enum
{
	MAX_SLOTS = 8
};

extern GameLogic *TheGameLogic;

class NetworkInterface;
struct UpdateNetworkVTable
{
	void *unknown[63];
	Bool (__fastcall *isRouterLeavePending)(NetworkInterface *network);
};

class NetworkInterface
{
public:
	Bool isRouterLeavePending() { return m_vtable->isRouterLeavePending(this); }

private:
	UpdateNetworkVTable *m_vtable;
};

extern NetworkInterface *TheNetwork;

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

// The GameSpy stats auth key request (type 5), held in the ledger under its
// constructor's address name, with its +0x1C challenge setter 0x004D65F9.
class Rva004D64F5 : public NetCommandMsg
{
public:
	Rva004D64F5();
	void rva004D65F9(AsciiString text);

private:
	AsciiString m_text1C;
};

Bool DoesCommandRequireACommandID(NetCommandType type);
UnsignedShort GenerateNextCommandID();

// GameSpyGameSlot's login name getter 0x004CFB6D and setter 0x004CFB8B, and
// its locale setter 0x004CFBC2, held in the ledger under address names.
class Rva004CFB6DAsciiField
{
public:
	AsciiString get() const;
	void rva004CFB8B(AsciiString text);
};

class Rva004CFBC2AsciiField
{
public:
	void rva004CFBC2(AsciiString text);
};

class GameSpyGameSlot;

class GameSpyStagingRoom
{
public:
	virtual void unknown00(); virtual void unknown04(); virtual void unknown08();
	virtual void unknown0C(); virtual void unknown10(); virtual void unknown14();
	virtual void unknown18(); virtual void unknown1C(); virtual void unknown20();
	virtual void unknown24(); virtual void unknown28(); virtual void unknown2C();
	virtual void unknown30();
	virtual Int getLocalSlotNum() const;
	GameSpyGameSlot *getGameSpySlot(Int index);

	char m_pad004[0xff4 - 4];
	Bool m_hasStatsGame;
	char m_padFF5[0x101c - 0xff5];
	void *m_statsGame;
};

extern GameSpyStagingRoom *TheGameSpyGame;

class GameSpyBuddyMessageQueueInterface
{
public:
	virtual void unknown00(); virtual void unknown04(); virtual void unknown08();
	virtual void unknown0C(); virtual void unknown10(); virtual void unknown14();
	virtual void unknown18(); virtual void unknown1C(); virtual void unknown20();
	virtual void unknown24(); virtual void unknown28();
	virtual const char *getReplyIdentityText();
	virtual const char *getAuthSecretText();
};

extern GameSpyBuddyMessageQueueInterface *TheGameSpyBuddyMessageQueue;

extern "C" char *GetChallenge(void *game);
extern "C" char *GenerateAuthA(char *challenge, char *password, char *response);
extern "C" int strcmp(const char *a, const char *b);
extern "C" char *strdup(const char *text);
void free(void *memory);

#include "../../Include/GameNetwork/Transport.h"

class Connection
{
public:
	UnsignedInt doSend(Bool throttle);
	Bool isQueueEmpty();
	Int getQuitFrame() const { return m_quitFrame; }

private:
	Int m_quitFrame;
};

class Rva004D060B
{
public:
	~Rva004D060B();
};

class FrameDataManager
{
public:
	virtual ~FrameDataManager();
	Bool getIsQuitting();
	UnsignedInt getQuitFrame();
};

class ConnectionManager;

class DisconnectManager
{
public:
	void update(ConnectionManager *conMgr);
};

class BFMEConnectionManager
{
public:
	void sendFrameInfo(Bool flag);
	void sendKeepAliveCommand();
};

struct ConnectionManagerAddress
{
	Bool isEmpty() const { return m_ip == 0 && m_port == 0; }

	UnsignedInt m_ip;
	UnsignedShort m_port;
};

class ConnectionManager
{
public:
	virtual ~ConnectionManager();
	virtual void init();
	virtual void reset();
	virtual void update(Bool isInGame, Int frameAdvanced);
	void doRelay();
	void sendLocalCommandDirect(NetCommandMsg *msg, UnsignedByte relay);

private:
	Connection *m_connections[MAX_SLOTS];
	char m_pad00024[0x12024 - 0x24];
	Transport *m_transport;
	Int m_localSlot;
	Int m_packetRouterSlot;
	char m_pad12030[0x12050 - 0x12030];
	ConnectionManagerAddress m_localAddress;
	char m_pad12058[0x1205c - 0x12058];
	UnsignedInt m_frameCeiling;
	char m_pad12060[0x12100 - 0x12060];
	DisconnectManager *m_disconnectManager;
	FrameDataManager *m_frameData[MAX_SLOTS];
	char m_pad12124[0x12134 - 0x12124];
	Bool m_throttleSend;
	Bool m_statsAuthPending;
};

void ConnectionManager::update(Bool isInGame, Int frameAdvanced)
{
	if (m_localAddress.isEmpty())
		return;

	if (m_transport != 0)
		m_transport->doRecv(0);

	if (isInGame)
	{
		if (m_disconnectManager != 0)
			m_disconnectManager->update(this);
		doRelay();
		if (frameAdvanced)
		{
			if (TheNetwork != 0 && TheNetwork->isRouterLeavePending() &&
				m_localSlot == m_packetRouterSlot)
				m_frameCeiling = TheGameLogic->getFrame() + 1;
			else
				((BFMEConnectionManager *)this)->sendFrameInfo(true);
		}
	}

	if (TheGameSpyGame != 0 && TheGameSpyBuddyMessageQueue != 0 && m_statsAuthPending)
	{
		if (TheGameSpyGame->m_hasStatsGame)
		{
			if (strcmp(GetChallenge(TheGameSpyGame->m_statsGame), "NULLGAME") != 0)
			{
			char *challenge = strdup(GetChallenge(TheGameSpyGame->m_statsGame));
			Rva004D64F5 *msg = new Rva004D64F5;
			msg->setPlayerID(m_localSlot);
			msg->setTimestamp(TheGameLogic->getTimestamp());
			msg->setExecutionFrame((UnsignedInt)-1);
			if (DoesCommandRequireACommandID(msg->getNetCommandType()))
				msg->setID(GenerateNextCommandID());
			msg->rva004D65F9(AsciiString(challenge));
			sendLocalCommandDirect(msg, (UnsignedByte)~(1 << m_localSlot));
			msg->detach();

			char *secret = strdup(TheGameSpyBuddyMessageQueue->getAuthSecretText());
			char response[64];
			GenerateAuthA(challenge, secret, response);
			GameSpyGameSlot *slot = TheGameSpyGame->getGameSpySlot(TheGameSpyGame->getLocalSlotNum());
			if (slot != 0 && ((Rva004CFB6DAsciiField *)slot)->get().getLength() == 0)
			{
				((Rva004CFB6DAsciiField *)slot)->rva004CFB8B(AsciiString(response));
				((Rva004CFBC2AsciiField *)slot)->rva004CFBC2(
					AsciiString(TheGameSpyBuddyMessageQueue->getReplyIdentityText()));
			}
			free(challenge);
			free(secret);
			m_statsAuthPending = false;
			}
		}
		else
			m_statsAuthPending = false;
	}

	((BFMEConnectionManager *)this)->sendKeepAliveCommand();

	for (Int i = 0; i < MAX_SLOTS; ++i)
	{
		if (m_connections[i] != 0)
		{
			m_connections[i]->doSend(m_throttleSend);
			if ((UnsignedInt)m_connections[i]->getQuitFrame() <= TheGameLogic->getFrame() &&
				m_connections[i]->isQueueEmpty())
			{
				delete (Rva004D060B *)m_connections[i];
				m_connections[i] = 0;
			}
		}
		if (m_frameData[i] != 0 && m_frameData[i]->getIsQuitting() &&
			m_frameData[i]->getQuitFrame() == TheGameLogic->getFrame())
		{
			::delete m_frameData[i];
			m_frameData[i] = 0;
		}
	}

	if (m_transport != 0)
		m_transport->doSend();
}
