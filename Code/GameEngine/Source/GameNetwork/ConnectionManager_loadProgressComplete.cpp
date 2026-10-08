// cl: /O1 /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ConnectionManager::loadProgressComplete, retail 0x004D02F6, 139 bytes.
//
// Donor: Zero Hour GameNetwork/ConnectionManager.cpp
// ConnectionManager::loadProgressComplete, with processLoadComplete inlined.
// Target evidence: operator new 0x1C and the NetCommandMsg constructor
// 0x004D5593 (BFME 2 allocates with new rather than the memory pool), the
// command type 0x10 stored before the player id from m_localSlot (+0x12028),
// DoesCommandRequireACommandID 0x005811B5 and GenerateNextCommandID
// 0x005811A8, GameLogic::processProgressComplete 0x0023D76E with the
// player id, then sendLocalCommand 0x004CFF21 to every other slot and
// NetCommandMsg::detach 0x004D55BC. BFME 2 sets the type first, so the id
// test reads the constant.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;

enum NetCommandType
{
	NETCOMMANDTYPE_UNKNOWN = -1,
	NETCOMMANDTYPE_LOADCOMPLETE = 0x10
};

class NetCommandMsg
{
public:
	NetCommandMsg();
	void detach();
	UnsignedInt getPlayerID() const { return m_playerID; }
	void setPlayerID(UnsignedInt playerID) { m_playerID = playerID; }
	void setID(UnsignedShort id) { m_id = id; }
	NetCommandType getNetCommandType() const { return m_commandType; }
	void setNetCommandType(NetCommandType type) { m_commandType = type; }

protected:
	void *m_vptr;
	UnsignedInt m_timestamp;
	UnsignedInt m_executionFrame;
	UnsignedInt m_playerID;
	UnsignedShort m_id;
	NetCommandType m_commandType;
	Int m_referenceCount;
};

#include "../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

Bool DoesCommandRequireACommandID(NetCommandType type);
UnsignedShort GenerateNextCommandID();

class ConnectionManager
{
public:
	void loadProgressComplete();
	void sendLocalCommand(NetCommandMsg *msg, UnsignedByte relay);

private:
	__forceinline void processLoadComplete(NetCommandMsg *msg)
	{
		TheGameLogic->processProgressComplete(msg->getPlayerID());
	}

	char m_pad00000[0x12028];
	UnsignedInt m_localSlot;
};

void ConnectionManager::loadProgressComplete()
{
	NetCommandMsg *msg = new NetCommandMsg;
	msg->setNetCommandType(NETCOMMANDTYPE_LOADCOMPLETE);
	msg->setPlayerID(m_localSlot);
	if (DoesCommandRequireACommandID(msg->getNetCommandType()))
		msg->setID(GenerateNextCommandID());
	processLoadComplete(msg);
	sendLocalCommand(msg, 0xff ^ (1 << m_localSlot));

	msg->detach();
}
