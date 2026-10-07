// cl: -O1 -arch:SSE -G7 -DNDEBUG -MD
// Reference: BFME 1 1399ad37d42ea52a63829e417c46a1ba9ed2cd20,
// AIUpdate.cpp::queueWaypoint and BfmeOneHundredFiftySeven.cpp list copy.
// Target: queue entries start at +0x74, stride 12, capacity 16; count +0x134.
// The adjacent rowed AIUpdateInterface methods at 26293E and 26295E execute
// and clear this same queue. Native 262912..26293E is a closed 44-byte body.
// Coord3D comes from the canonical POD contract. The reference establishes
// the operation's name; the target bytes establish these offsets and ABI.
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

class AIUpdateInterface
{
    char m_unmodelled00[0x74];
    Coord3D m_waypointQueue[16];
    int m_waypointCount;
public:
    bool queueWaypoint(const Coord3D *position);
};

bool AIUpdateInterface::queueWaypoint(const Coord3D *position)
{
    if (m_waypointCount < 16)
    {
        m_waypointQueue[m_waypointCount] = *position;
        ++m_waypointCount;
        return true;
    }
    return false;
}
