// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /GX
//
// BFME2 ConnectionManager local-slot getter, transferred from the exact
// BFME1 reconstruction (Code/GameEngine/Source/GameNetwork/ConnectionManager.cpp).
// Retail BFME2 keeps m_localSlot at the same offset (+0x12028); the layout
// authority is reference/shims/connectionmanager/GameNetwork/ConnectionManager.h.

typedef unsigned int UnsignedInt;

class ConnectionManager
{
public:
	UnsignedInt getLocalPlayerID();
	UnsignedInt getPacketRouterSlot();

private:
	unsigned char m_pre[0x12028];
	UnsignedInt m_localSlot;	// +0x12028
	UnsignedInt m_packetRouterSlot;	// +0x1202C
};

// ?getLocalPlayerID@ConnectionManager@@QAEIXZ
UnsignedInt ConnectionManager::getLocalPlayerID()
{
	return m_localSlot;
}

// ?getPacketRouterSlot@ConnectionManager@@QAEIXZ
UnsignedInt ConnectionManager::getPacketRouterSlot()
{
	return m_packetRouterSlot;
}
