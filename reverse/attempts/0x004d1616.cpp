// ?parseUserList@ConnectionManager@@QAEXPBVGameInfo@@@Z
// partial score=0.95 date=2026-10-07
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O1 /arch:SSE /G7
// ConnectionManager::parseUserList, retail 0x004D1616, 431 bytes.
//
// Reference: Zero Hour GameEngine/Source/GameNetwork/ConnectionManager.cpp
// parseUserList (local slot from the game, a Connection and a remote
// FrameDataManager for every other human slot, a local FrameDataManager for
// this machine's slot, reset of each, and the packet router fallback plan in
// slot order). Name: Network::ParseUserList 0x0025DBCD tail-jumps here with
// the GameInfo. Shape follows Open-BFME-1's
// game/GameEngine/Source/GameNetwork/ConnectionManagerAttachPlayers.cpp.
// BFME 2 differences read from this body: getLocalSlotNum is GameInfo's +0x34
// virtual and seeds the command IDs (0x00581194); the local player's name is
// copied from GameSlot +0x30; a Connection (0x358 bytes, constructor
// 0x0058BDA0) is set up through 0x0058BAA7 with the slot's address record at
// +0x38, its name and the transport, and again with the address taken from the
// two AsciiStrings at 0x00E02D90/0x00E02D94 (resolved host, atoi port) when the
// byte at 0x00E02D8B is set; the entries are only reset (no init call).
// The three globals are written only by the command-line handler at
// 0x003B9F8C (argv[1] and argv[2]), which no live parameter table references,
// so they keep their address names.

#include "ascii_string.h"
#include "unicode_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;

enum
{
	MAX_SLOTS = 8
};

extern "C" __declspec(dllimport) int __cdecl atoi(const char *text);

struct InitAddrs
{
	InitAddrs(UnsignedInt ip, UnsignedShort port) : m_ip(ip), m_port(port) {}

	UnsignedInt m_ip;
	UnsignedShort m_port;
};

class Connection
{
public:
	Connection();
	void rva0058BAA7(InitAddrs *addrs, const UnicodeString &name, Int transport);

private:
	char m_pad000[0x358];
};

class FrameDataManager
{
public:
	FrameDataManager(Bool isLocal);
	void reset();

private:
	char m_pad00[0x10];
};

class GameSlot
{
public:
	Bool isHuman() const;
	const UnicodeString &getName() const { return m_name; }
	InitAddrs *getAddress() const { return const_cast<InitAddrs *>(&m_address); }

	char m_pad00[0x30];
	UnicodeString m_name;
	char m_pad34[0x38 - 0x34];
	InitAddrs m_address;
};

class GameInfo
{
public:
#define GI_SLOT(n) virtual void slot##n();
	GI_SLOT(00) GI_SLOT(01) GI_SLOT(02) GI_SLOT(03) GI_SLOT(04)
	GI_SLOT(05) GI_SLOT(06) GI_SLOT(07) GI_SLOT(08) GI_SLOT(09)
	GI_SLOT(10) GI_SLOT(11) GI_SLOT(12)
#undef GI_SLOT
	virtual Int getLocalSlotNum() const; // +0x34
	const GameSlot *getConstSlot(Int index) const;
};

extern bool g_Va00E02D8B;
extern unsigned g_Va00E02D90;
extern unsigned g_Va00E02D94;

UnsignedInt ResolveIP(AsciiString host);
void SeedNextCommandIDFromPlayerCount(Int localSlot);

class ConnectionManager
{
public:
	void parseUserList(const GameInfo *game);

private:
	void *m_vptr;
	Connection *m_connections[MAX_SLOTS];
	char m_pad00024[0x12024 - 0x24];
	Int m_transport;
	Int m_localSlot;
	UnsignedInt m_packetRouterSlot;
	Int m_packetRouterFallback[MAX_SLOTS];
	char m_pad12050[0x12058 - 0x12050];
	UnicodeString m_localPlayerName;
	char m_pad1205C[0x12104 - 0x1205C];
	FrameDataManager *m_frameData[MAX_SLOTS];
};

void ConnectionManager::parseUserList(const GameInfo *game)
{
	if (!game)
		return;

	m_localSlot = game->getLocalSlotNum();
	SeedNextCommandIDFromPlayerCount(m_localSlot);

	Int numUsers = 0;
	for (Int i = 0; i < MAX_SLOTS; ++i)
	{
		GameSlot *slot = const_cast<GameSlot *>(game->getConstSlot(i));
		if (slot && slot->isHuman())
		{
			if (i == m_localSlot)
			{
				const UnicodeString &name = slot->getName();
				m_localPlayerName = name;
				m_frameData[i] = new FrameDataManager(true);
			}
			else
			{
				m_connections[i] = new Connection;
				m_connections[i]->rva0058BAA7(slot->getAddress(), slot->getName(), m_transport);
				if (g_Va00E02D8B)
				{
					m_connections[i]->rva0058BAA7(&InitAddrs(ResolveIP(*(AsciiString *)&g_Va00E02D90),
						(UnsignedShort)atoi(((AsciiString *)&g_Va00E02D94)->str())), slot->getName(), m_transport);
				}
				m_frameData[i] = new FrameDataManager(false);
			}
			m_frameData[i]->reset();
			m_packetRouterFallback[numUsers++] = i;
		}
	}
}
