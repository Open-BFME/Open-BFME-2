// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /GX
//
// These two small predicates sit directly on the BFME2 frame-stall and
// command-routing paths.  The state predicate accepts states 1 through 3;
// the connection predicate treats the local slot as connected and otherwise
// requires the peer's open-state sentinel.

struct Connection
{
	int m_openState;
};

class BFMEConnectionManager
{
public:
	bool isPlayerConnected(int slot);
	int isPlayerSlotActive(int slot);

private:
	char unknown0[4];
	Connection *m_connections[8];
	char unknown24[0x12004];
	int m_localSlot;
	int m_packetRouterSlot;
	char unknown12030[0x50];
	int m_playerState[8];
};

bool BFMEConnectionManager::isPlayerConnected(int slot)
{
	return slot == m_localSlot ||
		(m_connections[slot] != 0 && m_connections[slot]->m_openState == -1);
}

int BFMEConnectionManager::isPlayerSlotActive(int slot)
{
	if ((unsigned int)slot >= 8 || m_playerState[slot] < 1 ||
		m_playerState[slot] > 3 || !isPlayerConnected(slot))
		return 0;
	return 1;
}
