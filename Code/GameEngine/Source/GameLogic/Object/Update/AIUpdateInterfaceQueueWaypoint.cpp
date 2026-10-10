// cl: -O1 -arch:SSE -G7 -DNDEBUG -MD
// Reference: BFME 1 1399ad37d42ea52a63829e417c46a1ba9ed2cd20,
// AIUpdate.cpp::queueWaypoint and BfmeOneHundredFiftySeven.cpp list copy.
// Target: queue entries start at +0x74, stride 12, capacity 16; count +0x134.
// The adjacent rowed AIUpdateInterface methods at 26293E and 26295E execute
// and clear this same queue. Native 262912..26293E is a closed 44-byte body.
// Coord3D comes from the canonical POD contract. The reference establishes
// the operation's name; the target bytes establish these offsets and ABI.
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

struct Rva00331ED1Record;
class Rva00331ED1
{
public:
    void rva00331ED1(int key, void *argument2, void *argument3);
private:
    unsigned char prefix[4];
    Rva00331ED1Record *begin;
    Rva00331ED1Record *end;
};


class AIUpdateInterface
{
    char m_unmodelled00[0x74];
    Coord3D m_waypointQueue[16];
    int m_waypointCount;
    char m_unmodelled138[0x224 - 0x138];
    Rva00331ED1 spyDispatch;
public:
    bool queueWaypoint(const Coord3D *position);
    void processSpies(int key, void *argument2, void *argument3);
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

// WB E3B450 independently names processSpies at AIUpdate.cpp1584. Native
//262907..262912 is a complete11B tail wrapper to the established92B
//331ED1 dispatcher at receiver-relative224. The queued55B boundary also
//includes the separately rowed44B queueWaypoint method, not part of this
//body. Original pointer roles and full-object base adjustment are unknown;
//the existing dispatcher int/void*/void* ABI is preserved without a new pin.
void AIUpdateInterface::processSpies(int key, void *argument2, void *argument3)
{
    spyDispatch.rva00331ED1(key, argument2, argument3);
}
