// ?resetPlayerTimeouts@DisconnectManager@@IAEXPAVConnectionManager@@@Z
// partial score=0.9 date=2026-10-04
// cl: /O1 /DNDEBUG /MD
//
// DisconnectManager::resetPlayerTimeouts, retail 0x004D3D2B (49 bytes),
// ported from Zero Hour's GameEngine/Source/GameNetwork/DisconnectManager.cpp
// (GeneralsMD tree vendored under reference/open-bfme-1/inputs/reference):
// every slot that translates to a remote player gets its timeout reset.
// translatedSlotPosition is the rowed helper 0x004D39DE (Rva004D39DEGet),
// resetPlayerTimeout the rowed 0x004D3A06 and getLocalPlayerID the rowed
// 0x004CF906.
typedef int Int;

int Rva004D39DEGet(int slot, int localSlot);
#define translatedSlotPosition Rva004D39DEGet

enum
{
	MAX_SLOTS = 8
};

class ConnectionManager
{
public:
	unsigned int getLocalPlayerID();
};

class DisconnectManager
{
protected:
	void resetPlayerTimeout(Int slot);
	void resetPlayerTimeouts(ConnectionManager *conMgr);
};

void DisconnectManager::resetPlayerTimeouts(ConnectionManager *conMgr) {
	for (Int i = 0; i < MAX_SLOTS; ++i) {
		Int slot = translatedSlotPosition(i, conMgr->getLocalPlayerID());
		if (slot != -1) {
			resetPlayerTimeout(slot);
		}
	}
}
