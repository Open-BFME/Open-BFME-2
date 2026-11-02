// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/GameNetwork

// ConnectionManager::setFrameGrouping, 0x00663530, 129 bytes.
//
// This is the only thing in the image that can move a Connection off its
// initialised m_frameGrouping of 1, and nothing calls it.
//
// Connection::doSend gates every send on
//     if ((curtime - m_lastTimeSent) < m_frameGrouping) return 0;
// with m_frameGrouping at Connection+0x344 and m_lastTimeSent at +0x348. Two
// sites initialise that field to 1 (0x00661E99 and 0x006623E2), and the eight
// stores below are the only other writes to +0x344 anywhere in the image. An
// exhaustive scan of every section for a call or jump reaching either this body
// or its incremental-link thunk at 0x00049DB4 finds exactly one reference: the
// thunk's own jump here. Nothing calls the thunk.
//
// So the egress pacer is inert in the shipped game -- frameGrouping stays at 1ms
// for every connection, and the gate above is never taken. That leaves the
// packet router's QueryPerformanceFrequency/5 (200ms) quantum as the sole
// steady-state source of command delay, rather than one of two.
//
// The halving is BFME's own and has no reference counterpart: when this machine
// IS the packet router it takes half the interval everyone else gets, so the
// host would flush twice as often. Dead along with the rest of the function.
//
// Declared locally rather than through the ConnectionManager shim on purpose:
// the shim models this class for a different TU and does not carry +0x344, and
// touching any shim header forces the full gate.

typedef int Int;
typedef unsigned int UnsignedInt;

enum { MAX_SLOTS = 8 };

// Only the one field retail writes here is modelled; everything before it is
// opaque. Connection is not a MemoryPoolObject in BFME, so there is no vptr.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/Connection.h
class Connection
{
public:
	char m_padToFrameGrouping[0x344];
	UnsignedInt m_frameGrouping;					// this+0x344
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/ConnectionManager.h
#include "../../Include/GameNetwork/ConnectionManager.h"

void ConnectionManager::setFrameGrouping( UnsignedInt frameGrouping )
{
	// shr, not sar: retail halves this with a logical shift, so the parameter is
	// unsigned rather than the reference's signed time_t.
	if (m_localSlot == m_packetRouterSlot) {
		frameGrouping /= 2;
	}

	for (Int i = 0; i < MAX_SLOTS; ++i) {
		if (m_connections[i] != 0) {
			m_connections[i]->m_frameGrouping = frameGrouping;
		}
	}
}
