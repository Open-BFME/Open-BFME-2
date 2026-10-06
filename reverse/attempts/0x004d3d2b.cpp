// ?resetPlayerTimeouts@DisconnectManager@@IAEXPAVConnectionManager@@@Z
// partial score=0.9117 date=2026-10-06
// ?resetPlayerTimeouts@DisconnectManager@@IAEXPAVConnectionManager@@@Z
// partial score=0.97 date=2026-10-05
// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?resetPlayerTimeouts@DisconnectManager@@IAEXPAVConnectionManager@@@Z @ 0x004D3D2B (49B).
// ZH donor DisconnectManager::resetPlayerTimeouts loops MAX_SLOTS calling the
// slot translation and skipping -1 into resetPlayerTimeout; BFME2 retail calls
// the translation as the rowed free function Rva004D39DEGet (0x4D39DE, no ecx
// setup) with conMgr->getLocalPlayerID() (0x4CF906, rowed) and the member
// resetPlayerTimeout (0x4D3A06, rowed). Sibling /O1 bodies in this family pop
// call arguments, but retail cleans with add-esp here, so this unit pairs /O1
// allocation with /Ot cleanup.

typedef int Int;

int Rva004D39DEGet(int a, int b);

class ConnectionManager
{
public:
	unsigned int getLocalPlayerID();
};

class DisconnectManager
{
protected:
	__declspec(noinline) void resetPlayerTimeout(Int slot);
	void resetPlayerTimeouts(ConnectionManager *conMgr);
};

void DisconnectManager::resetPlayerTimeouts(ConnectionManager *conMgr)
{
	// reset the player timeouts.
	for (Int i = 0; i < 8; ++i) {
		Int slot = Rva004D39DEGet(i, conMgr->getLocalPlayerID());
		if (slot == -1)
			continue;
		resetPlayerTimeout(slot);
	}
}
