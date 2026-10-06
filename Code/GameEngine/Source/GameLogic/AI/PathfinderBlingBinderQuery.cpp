// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// ?rva002EF663@Pathfinder@@QAE_NPBUCoord3D@@W4PathfindLayerEnum@@0I@Z @0x002EF663 41B: caller at 0x00363FA4; adjacent member forwards to Pathfinder::rva002EED41; class identity follows the preserved Pathfinder this pointer.
#include "../../../../Libraries/Include/Lib/Coord3D.h"

enum PathfindLayerEnum {
    LAYER_INVALID = 0
};

class Pathfinder;
struct Rva002E93A7Info {
    Pathfinder *pathfinder;
    unsigned int value;
};

class Pathfinder {
public:
    int rva002EED41(const Coord3D *, const Coord3D *, PathfindLayerEnum, Rva002E93A7Info *);
    bool rva002EF663(const Coord3D *, PathfindLayerEnum, const Coord3D *, unsigned int);
};

bool Pathfinder::rva002EF663(const Coord3D *start, PathfindLayerEnum layer, const Coord3D *end, unsigned int value)
{
    Rva002E93A7Info info;
    info.value = value;
    info.pathfinder = this;
    return !rva002EED41(start, end, layer, &info);
}
