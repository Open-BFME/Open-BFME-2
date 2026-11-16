// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX

#include "../../Include/GameNetwork/BFMEConnectionManager.h"

bool BFMEConnectionManager::isPacketRouter(void)
{
	return m_localSlot == m_packetRouterSlot;
}
