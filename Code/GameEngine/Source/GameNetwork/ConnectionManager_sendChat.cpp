// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ConnectionManager::sendChat, retail 0x004D17C5, 182 bytes.
//
// Reference: Zero Hour GameEngine/Source/GameNetwork/ConnectionManager.cpp
// sendChat (a chat command carrying the text and the recipient mask, sent to
// every other player and shown locally through processChat).
// BFME 2 differences read from this body: there is no execution-frame
// argument and no setID(0); the chat command is the type-14 message built by
// 0x004D6134, its text set through 0x004D6187 (ZH setText) and its mask
// through the folded +0x20 dword setter 0x00317B9B (the same pairing as
// NetPacket's chat reader 0x00592123); the send is sendLocalCommandDirect
// 0x004CF6E4 and the local echo processChat 0x004D10F1.

#include "unicode_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;

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

// The type-14 chat command (ZH's NetChatCommandMsg), held in the ledger under
// its constructor's address name.
class Rva004D6134 : public NetCommandMsg
{
public:
	Rva004D6134();

private:
	char m_pad1C[0x24 - 0x1c];
};

// ZH's setText(UnicodeString), rowed on the type-13 class.
class Rva004D60CA
{
public:
	void rva004D6187(UnicodeString text);
};

// The folded +0x20 dword setter 0x00317B9B.
class BFMENetInformPlayerLeaveFrameCommandMsg
{
public:
	void setLeavingPlayerID(Int playerID);
};

class NetChatCommandMsg;

Bool DoesCommandRequireACommandID(NetCommandType type);
UnsignedShort GenerateNextCommandID();

class ConnectionManager
{
public:
	void sendChat(UnicodeString text, Int playerMask);
	void sendLocalCommandDirect(NetCommandMsg *msg, UnsignedByte relay);

private:
	void processChat(NetChatCommandMsg *msg);

	char m_pad00000[0x12028];
	Int m_localSlot;
};

void ConnectionManager::sendChat(UnicodeString text, Int playerMask)
{
	Rva004D6134 *msg = new Rva004D6134;
	((Rva004D60CA *)msg)->rva004D6187(text);
	((BFMENetInformPlayerLeaveFrameCommandMsg *)msg)->setLeavingPlayerID(playerMask);
	msg->setPlayerID(m_localSlot);
	if (DoesCommandRequireACommandID(msg->getNetCommandType()))
	{
		msg->setID(GenerateNextCommandID());
	}

	sendLocalCommandDirect(msg, 0xff ^ (1 << m_localSlot));
	processChat((NetChatCommandMsg *)msg);

	msg->detach();
}
