// cl: /O1 /DNDEBUG /DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/GameNetwork -ICode/GameEngine/Source/Common
// ?rva004D00BB@ConnectionManager@@QAEXH@Z @0x004D00BB 179B: ConnectionManager local disconnect-player send.
// Target evidence: new 0x24 Rva004D5A10 (0x004D5A10) whose +0x1C slot is set through the Rva004D57AE setter
// 0x00318B09 and +0x20 through the folded dword setter 0x00317B9B (argument), TheGameLogic+0x38 frame at +4,
// execution frame -1, DoesCommandRequireACommandID 0x005811B5 plus GenerateNextCommandID 0x005811A8,
// sendLocalCommandDirect 0x004CF6E4 to all, the connection flush 0x004CF8D5 and detach 0x004D55BC, then the
// m_lastTime stamp at +0x12130 through timeGetTime only when it is still zero. The only direct caller is the
// null-checked forwarder 0x004D0E8B/0x0025E27F; the own name stays an address name.

#include "GameLogicObjectLookupView.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

void *__cdecl operator new(UnsignedInt size);
void __cdecl operator delete(void *block) throw();

enum NetCommandType
{
	NETCOMMANDTYPE_UNKNOWN = -1
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

class Rva004D5A10 : public NetCommandMsg
{
public:
	Rva004D5A10();
private:
	char m_pad1C[0x24 - 0x1C];
};

class Rva004D57AE
{
public:
	void setPlayerIndex(UnsignedInt v);
};

class BFMENetInformPlayerLeaveFrameCommandMsg
{
public:
	void setLeavingPlayerID(Int playerID);
};

class BfmeOwnerFY
{
public:
	void bfmeShutdownFY();
};

extern GameLogic *TheGameLogic;

bool DoesCommandRequireACommandID(NetCommandType type);
UnsignedShort GenerateNextCommandID();

extern "C" __declspec(dllimport) UnsignedInt __stdcall timeGetTime(void);

class ConnectionManager
{
public:
	void rva004D00BB(Int arg);
	void sendLocalCommandDirect(NetCommandMsg *msg, UnsignedByte relay);
private:
	void *m_vptr;
	char m_pad04[0x12028 - 4];
	UnsignedInt m_localPlayerID;
	char m_pad1202C[0x12130 - 0x12028 - 4];
	UnsignedInt m_lastTime;
};

void ConnectionManager::rva004D00BB(Int arg)
{
	Rva004D5A10 *cmd = new Rva004D5A10();
	((Rva004D57AE *)cmd)->setPlayerIndex(m_localPlayerID);
	cmd->m_playerID = m_localPlayerID;
	((BFMENetInformPlayerLeaveFrameCommandMsg *)cmd)->setLeavingPlayerID(arg);
	if (DoesCommandRequireACommandID(cmd->m_commandType))
		cmd->m_id = GenerateNextCommandID();
	cmd->m_timestamp = TheGameLogic->getTimestamp();
	cmd->m_executionFrame = (UnsignedInt)-1;
	sendLocalCommandDirect(cmd, 0xff);
	((BfmeOwnerFY *)this)->bfmeShutdownFY();
	cmd->detach();
	if (m_lastTime == 0)
		m_lastTime = timeGetTime();
}
