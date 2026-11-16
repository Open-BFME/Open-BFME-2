// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
//
// Replaces the connection manager's transport, releasing the previous
// transport through its reset path and the game allocator before installing
// the new pointer.

#include "../../Include/GameNetwork/Transport.h"
#include <new>

#include "../../Include/GameNetwork/BFMEConnectionManager.h"

void BFMEConnectionManager::attachTransport(Transport *transport)
{
	if (m_transport != 0)
	{
		delete m_transport;
		m_transport = 0;
	}
	m_transport = transport;
}
