// cl: /O1 /DNDEBUG /MD /EHsc
// ??0NetGameCommandMsg@@QAE@PAVGameMessage@@@Z @0x004D5CBE 151B: NetGameCommandMsg from GameMessage copy ctor.
// Target evidence: base ??0NetCommandMsg 0x004D5593 then vtable RVA 0x008601E4 plus +0x14=4 plus +0x24 from [arg+0x10] plus loop getArgument 0x0030F4EA plus getArgumentDataType 0x0030F50C plus addArgument 0x004D5A7A; caller 0x004D0E06; donor reference/open-bfme-1/game/GameEngine/Source/GameNetwork/NetGameCommandMsgFromGameMessage.cpp.
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef int Int;

enum NetCommandType
{
	NETCOMMANDTYPE_UNKNOWN = -1,
	NETCOMMANDTYPE_GAMECOMMAND = 4
};

enum GameMessageArgumentDataType
{
	ARGUMENTDATATYPE_UNKNOWN = 12
};

union GameMessageArgumentType
{
	int integer;
	float real;
	int pixelRegion[4];
};

class GameMessage
{
public:
	int getType() const { return m_type; }
	unsigned char getArgumentCount() const { return m_argCount; }
	const GameMessageArgumentType *getArgument(int index) const;
	GameMessageArgumentDataType getArgumentDataType(int index);
private:
	char m_unknown00[0x10];
	int m_type;
	char m_unknown14[4];
	unsigned char m_argCount;
};

class NetCommandMsg
{
public:
	NetCommandMsg();
protected:
	virtual ~NetCommandMsg();
protected:
	UnsignedInt m_timestamp;
	UnsignedInt m_executionFrame;
	UnsignedInt m_playerID;
	UnsignedShort m_id;
	NetCommandType m_commandType;
	Int m_referenceCount;
};

class GameMessageArgument;

class NetGameCommandMsg : public NetCommandMsg
{
public:
	NetGameCommandMsg(GameMessage *msg);
	virtual ~NetGameCommandMsg();
	void addArgument(GameMessageArgumentDataType type, GameMessageArgumentType arg);
private:
	Int m_numArgs;
	Int m_argSize;
	Int m_type;
	GameMessageArgument *m_argList;
	GameMessageArgument *m_argTail;
};

NetGameCommandMsg::NetGameCommandMsg(GameMessage *msg) : NetCommandMsg()
{
	m_numArgs = 0;
	m_argSize = 0;
	m_argList = 0;
	m_argTail = 0;
	m_commandType = NETCOMMANDTYPE_GAMECOMMAND;
	m_type = msg->getType();
	int count = msg->getArgumentCount();
	for (int i = 0; i < count; ++i)
		addArgument(msg->getArgumentDataType(i), *msg->getArgument(i));
}
