// ?isPlayerInGame@DisconnectManager@@QAE_NHPAVConnectionManager@@@Z
// partial score=0.3 date=2026-10-06
// cl: /O1 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// DisconnectManager in-game and packet-router queries recovered from
// WorldBuilder leads (reverse/wb_name_leads.csv): WB's debug build names both
// (DisconnectManager.cpp); the bodies are Zero Hour's
// (GameNetwork/DisconnectManager.cpp). Dedicated /O1 unit like
// DisconnectManagerO1.cpp; DisconnectManager.cpp's flags do not reproduce
// these frames. BFME2's packet-router scan also stops at a router whose slot
// is still active.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

int Rva004D39DEGet(int slot, int localSlot);	// 0x004D39DE, translatedSlotPosition
int rva0066b3e0(int slot, int localSlot);		// 0x004D39F0, untranslatedSlotPosition

enum { MAX_SLOTS = 8 };

class ConnectionManager
{
public:
	UnsignedInt getLocalPlayerID();				// 0x004CF906
	UnsignedInt getPacketRouterSlot();			// 0x004CF3B2
	Bool isPlayerConnected(Int playerID);			// 0x004CF083
};

// BFME2's connection-manager additions are rowed under this class name.
class BFMEConnectionManager : public ConnectionManager
{
public:
	UnsignedInt getNextPacketRouterSlot(UnsignedInt slot);	// 0x004CFAC0
};

// The bool-returning spelling of the active-slot predicate at 0x004CF0CD.
class Rva004CF0CDNullTarget
{
public:
	Bool rva004CF0CD(Int slot);
};

class DisconnectManager
{
public:
	Bool isPlayerInGame(Int slot, ConnectionManager *conMgr);
	Bool isLocalPlayerNextPacketRouter(ConnectionManager *conMgr);

private:
	Bool isPlayerVotedOut(Int slot, ConnectionManager *conMgr);	// 0x004D3ECF
	unsigned char rva004D3AB2(Int slot);			// 0x004D3AB2, hasPlayerTimedOut
};

// DisconnectManager::isPlayerInGame, retail 0x004D3F1B.
Bool DisconnectManager::isPlayerInGame(Int slot, ConnectionManager *conMgr)
{
	Int transSlot = rva0066b3e0(slot, conMgr->getLocalPlayerID());
	if (((transSlot < 0) || (transSlot >= MAX_SLOTS)) || conMgr->isPlayerConnected(transSlot) == false)
		return false;
	if (isPlayerVotedOut(slot, conMgr) == true)
		return false;
	if (rva004D3AB2(slot) == true)
		return false;
	return true;
}

// DisconnectManager::isLocalPlayerNextPacketRouter, retail 0x004D4330.
Bool DisconnectManager::isLocalPlayerNextPacketRouter(ConnectionManager *conMgr)
{
	UnsignedInt localSlot = conMgr->getLocalPlayerID();
	UnsignedInt packetRouterSlot = conMgr->getPacketRouterSlot();
	Int transSlot = Rva004D39DEGet(packetRouterSlot, localSlot);

	while ((transSlot != -1) && (isPlayerInGame(transSlot, conMgr) == false
		|| ((Rva004CF0CDNullTarget *)conMgr)->rva004CF0CD(packetRouterSlot)))
	{
		packetRouterSlot = ((BFMEConnectionManager *)conMgr)->getNextPacketRouterSlot(packetRouterSlot);
		if (packetRouterSlot >= MAX_SLOTS)
			return false;
		transSlot = Rva004D39DEGet(packetRouterSlot, localSlot);
	}

	if (packetRouterSlot == localSlot)
		return true;
	return false;
}
