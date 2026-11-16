// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
//
// BFME2 keeps a fallback packet-router order at +0x12030.  This helper returns
// the entry following the supplied router slot, matching the BFME1
// ConnectionManager::getNextPacketRouterSlot operation.

#include "../../Include/GameNetwork/BFMEConnectionManager.h"

unsigned int BFMEConnectionManager::getNextPacketRouterSlot(unsigned int playerID)
{
	int index = 0;
	while (index < 7 && m_packetRouterFallback[index] != playerID)
		++index;
	++index;
	return m_packetRouterFallback[index];
}
