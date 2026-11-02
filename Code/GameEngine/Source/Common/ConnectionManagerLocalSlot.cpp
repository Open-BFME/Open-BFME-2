// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
//
// BFME2 ConnectionManager local-slot getter, transferred from the exact
// BFME1 reconstruction (Code/GameEngine/Source/GameNetwork/ConnectionManager.cpp).
// Retail BFME2 keeps m_localSlot at the same offset (+0x12028); the layout
// authority is reference/shims/connectionmanager/GameNetwork/ConnectionManager.h.

typedef unsigned int UnsignedInt;

#include "../../Include/GameNetwork/ConnectionManager.h"

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
