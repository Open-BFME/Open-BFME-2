// ?rva004D0A0A@ConnectionManager@@QAEXXZ
// partial score=0.97 date=2026-10-04
// cl: /O1 /DNDEBUG /DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/GameNetwork

// ?rva004D0A0A@ConnectionManager@@QAEXXZ @0x004D0A0A 154B: ConnectionManager keepalive-style send via Rva004D5795 plus slot byte plus TheGameLogic frame plus Does plus sendLocalCommand plus timeGetTime.
// Target evidence: new Rva004D5795 0x004D5795 then setter 0x0006EDE3 via setDisconnectSlot pin plus TheGameLogic+0x38 plus DoesCommandRequireACommandID 0x005811B5 plus GenerateNextCommandID 0x005811A8 plus sendLocalCommand 0x004CFF21 plus detach 0x004D55BC plus timeGetTime IAT; caller 0x0025E75F.

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

class Rva004D5795 : public NetCommandMsg
{
public:
	Rva004D5795();
private:
	bool m_1c;
	char m_pad1D[0x20 - 0x1D];
};

class Script
{
public:
	void setActive(bool active);
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

extern "C" __declspec(dllimport) UnsignedInt __stdcall timeGetTime(void);

class ConnectionManager
{
public:
	void rva004D0A0A();
	void sendLocalCommand(NetCommandMsg *msg, UnsignedByte relay);
private:
	void *m_vptr;
	char m_pad04[0x12028 - 4];
	union
	{
		bool m_slotBool;
		UnsignedInt m_localPlayerID;
	};
	char m_pad1202C[0x12130 - 0x12028 - 4];
	UnsignedInt m_lastTime;
};

// ?rva004D0A0A@ConnectionManager@@QAEXXZ present-unmatched
void ConnectionManager::rva004D0A0A()
{
	Rva004D5795 *cmd = new Rva004D5795();
	((Script *)cmd)->setActive(m_slotBool);
	cmd->m_timestamp = TheGameLogic->m_frame;
	cmd->m_executionFrame = (UnsignedInt)-1;
	if ((UnsignedByte)DoesCommandRequireACommandID(cmd->m_commandType))
		cmd->m_id = GenerateNextCommandID();
	cmd->m_playerID = m_localPlayerID;
	sendLocalCommand(cmd, 0xff);
	cmd->detach();
	m_lastTime = timeGetTime();
}
