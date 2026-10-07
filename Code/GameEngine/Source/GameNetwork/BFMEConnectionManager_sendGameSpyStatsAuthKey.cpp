// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs
// BFMEConnectionManager::sendGameSpyStatsAuthKey, retail 0x004D12B2, 312 bytes.
//
// Donor: Open-BFME-1 game/GameEngine/Source/GameNetwork/native_connection_timing.cpp
// BFMEConnectionManager::sendGameSpyStatsAuthKey (name, the challenge/secret
// copies handed to GenerateAuthA, the reply command carrying the response and
// the reply identity, and the direct send back to the requesting player).
// Target evidence: the request's +0x1C text read through the folded getter
// 0x002D9BA6 (rowed as CDDrive::getPath), _strdup 0x006C4C70, the buddy
// queue's +0x30/+0x2C C-string virtuals on TheGameSpyBuddyMessageQueue,
// _GenerateAuthA 0x00606E20 into a 256-byte stack buffer, _free 0x00030830,
// operator new 0x24 and the reply constructor 0x004D65DC, its +0x1C/+0x20
// AsciiString setters 0x004D65F9/0x004D662D, m_localSlot at +0x12028,
// DoesCommandRequireACommandID 0x005811B5, GenerateNextCommandID 0x005811A8,
// sendLocalCommandDirect 0x004CF6E4 and NetCommandMsg::detach 0x004D55BC.
// BFME 2 also stamps the reply's timestamp from TheGameLogic+0x38.
// Built /EHs: retail keeps the getter temporary's unwind state live across
// the extern "C" _strdup call, which /EHsc would treat as unable to throw.
// free is the C++-linkage declaration that reaches GameMemory's _free.

#include "ascii_string.h"

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

// The folded +0x1C AsciiString getter at 0x002D9BA6.
class CDDrive
{
public:
	virtual AsciiString getPath();
};

// The request's +0x1C AsciiString setter 0x004D65F9, shared by the reply.
class Rva004D64F5 : public NetCommandMsg
{
public:
	void rva004D65F9(AsciiString text);
};

// The GameSpy stats auth key reply (BFME 1's BFMENetGameSpyStatsAuthKeyCommandMsg).
class Rva004D65DC : public NetCommandMsg
{
public:
	Rva004D65DC();
	void rva004D662D(AsciiString text);

private:
	AsciiString m_text1C;
	AsciiString m_text20;
};

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

class GameLogic
{
public:
	char m_pad00[0x38];
	UnsignedInt m_timestampFrame;
};

extern GameSpyBuddyMessageQueueInterface *TheGameSpyBuddyMessageQueue;
extern GameLogic *TheGameLogic;
extern "C" char *strdup(const char *text);
void free(void *memory);
extern "C" char *GenerateAuthA(char *challenge, char *password, char *response);
Bool DoesCommandRequireACommandID(NetCommandType type);
UnsignedShort GenerateNextCommandID();

class ConnectionManager
{
public:
	void sendLocalCommandDirect(NetCommandMsg *msg, UnsignedByte relay);
};

class BFMEConnectionManager
{
public:
	void sendGameSpyStatsAuthKey(void *command);

private:
	char m_pad00000[0x12028];
	UnsignedInt m_localSlot;
};

// Replies to the request's challenge using the GameSpy authentication helper.
void BFMEConnectionManager::sendGameSpyStatsAuthKey(void *command)
{
	NetCommandMsg *request = static_cast<NetCommandMsg *>(command);
	char *challenge = strdup(((CDDrive *)request)->CDDrive::getPath().str());
	char *secret = strdup(TheGameSpyBuddyMessageQueue->getAuthSecretText());
	char response[256];
	GenerateAuthA(challenge, secret, response);
	free(challenge);
	free(secret);
	Rva004D65DC *msg = new Rva004D65DC;
	msg->setPlayerID(m_localSlot);
	msg->setTimestamp(TheGameLogic->m_timestampFrame);
	msg->setExecutionFrame((UnsignedInt)-1);
	if (DoesCommandRequireACommandID(msg->getNetCommandType()))
		msg->setID(GenerateNextCommandID());
	((Rva004D64F5 *)msg)->rva004D65F9(AsciiString(response));
	msg->rva004D662D(AsciiString(TheGameSpyBuddyMessageQueue->getReplyIdentityText()));
	if (request->getPlayerID() < 8)
		reinterpret_cast<ConnectionManager *>(this)->sendLocalCommandDirect(msg,
			(UnsignedByte)(1 << request->getPlayerID()));
	msg->detach();
}
