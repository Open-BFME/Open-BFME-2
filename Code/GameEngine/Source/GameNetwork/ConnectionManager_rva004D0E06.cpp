// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc /Os -Ireference/open-bfme-1/game/GameEngine/Source/GameNetwork

// ?rva004D0E06@ConnectionManager@@QAEXPAVGameMessage@@@Z @0x004D0E06 133B: ConnectionManager send GameMessage as NetGameCommandMsg via TheGameLogic frame and local player slot then sendLocalCommand relay 0xff and detach.
// Target evidence: new NetGameCommandMsg(GameMessage*) 0x004D5CBE then TheGameLogic+0x38 timestamp plus this+0x12028 playerID plus DoesCommandRequireACommandID 0x005811B5 plus GenerateNextCommandID 0x005811A8 plus sendLocalCommand 0x004CFF21 plus detach 0x004D55BC; caller 0x0025E75F.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

void *__cdecl operator new(UnsignedInt size);
void __cdecl operator delete(void *block) throw();

enum NetCommandType
{
	NETCOMMANDTYPE_UNKNOWN = -1,
	NETCOMMANDTYPE_GAMECOMMAND = 4
};

class GameMessage
{
public:
	int getType() const { return m_type; }
	unsigned char getArgumentCount() const { return m_argCount; }
private:
	char m_unknown00[0x10];
	int m_type;
	char m_unknown14[4];
	unsigned char m_argCount;
};

class NetCommandMsg
{
public:
	void detach();
public:
	void *m_vptr;
	UnsignedInt m_timestamp;
	UnsignedInt m_executionFrame;
	UnsignedInt m_playerID;
	UnsignedShort m_id;
	char m_pad11[2];
	NetCommandType m_commandType;
	Int m_referenceCount;
};

class NetGameCommandMsg : public NetCommandMsg
{
public:
	NetGameCommandMsg(GameMessage *msg);
private:
	Int m_numArgs;
	Int m_argSize;
	Int m_type;
	void *m_argList;
	void *m_argTail;
};

class GameLogic
{
public:
	char m_pad00[0x38];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

Int DoesCommandRequireACommandID(NetCommandType type);
UnsignedShort GenerateNextCommandID();

class ConnectionManager
{
public:
	void rva004D0E06(GameMessage *msg);
	void sendLocalCommand(NetCommandMsg *msg, UnsignedByte relay);
private:
	void *m_vptr;
	char m_pad04[0x12028 - 4];
	UnsignedInt m_localPlayerID;
};

void ConnectionManager::rva004D0E06(GameMessage *msg)
{
	NetGameCommandMsg *cmd = new NetGameCommandMsg(msg);
	cmd->m_timestamp = TheGameLogic->m_frame;
	cmd->m_executionFrame = (UnsignedInt)-1;
	cmd->m_playerID = m_localPlayerID;
	if ((UnsignedByte)DoesCommandRequireACommandID(cmd->m_commandType))
		cmd->m_id = GenerateNextCommandID();
	sendLocalCommand(cmd, 0xff);
	cmd->detach();
}
