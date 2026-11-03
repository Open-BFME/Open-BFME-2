// cl: /O1 /arch:SSE /G7 /Oy- /MD
// Native 002F600C..002F6075, framed ECX member and RET 16: the per-cell
// callback the rowed walker 002F6D22 calls as Rva002F600CInfo::cellCallback.
// EAX is zero on every exit. From the second cell on (a previous cell given),
// it compares the cell's layer bits 4..9 with +14, passes thirteen arguments
// to 002F52A7 (RET 52, AL result) and, on success with the out word zero, sets
// byte +18 and copies +1C's XYZ to +28. The out word lives in the dead first
// argument slot. The original class and query are unknown; field names are
// descriptive.
struct Rva002F600CCoord { float x, y, z; };
class Rva002F52A7Query;

// LINK: 0x002F52A7 is rowed as Pathfinder::CheckForAdjust (pathfinder.cpp); the query object is the pathfinder and the old
// all-integer call shape stays through a member-pointer cast.
class Object;
class LocomotorSet;
struct Coord3D;
enum PathfindLayerEnum { BFME_LAYER_GROUND };
#include "../../../Include/GameLogic/AIPathfind.h"
typedef bool (PathfindServicesInterface::*Rva002F52A7Shape)(unsigned int, unsigned int, unsigned char, unsigned int, unsigned int, unsigned int,
    unsigned int, unsigned char, Rva002F600CCoord *, unsigned int, float, unsigned int *, unsigned int);
#include "../../../Include/GameLogic/PathfindCell.h"
struct Rva002F600CInfo
{
    int cellCallback(PathfindCell *from, PathfindCell *to, int x, int y);
    Rva002F52A7Query *query;
    unsigned int word04, word08, word0C;
    unsigned char option10;
    unsigned char padding11[3];
    unsigned int kind14;
    bool success18;
    unsigned char padding19[3];
    Rva002F600CCoord position1C, position28;
};

// ?cellCallback@Rva002F600CInfo@@QAEHPAVPathfindCell@@0HH@Z
int Rva002F600CInfo::cellCallback(PathfindCell *from, PathfindCell *to, int x, int y)
{
    if (from)
    {
        unsigned int kind = (to->m_0C >> 4) & 63;
        unsigned int adjust;
        if (kind14 == kind &&
            (static_cast<PathfindServicesInterface *>((Pathfinder *)query)->*reinterpret_cast<Rva002F52A7Shape>(
                static_cast<bool(PathfindServicesInterface::*)(Object *, const LocomotorSet &, bool, int, int, PathfindLayerEnum, int, bool, Coord3D *, const Coord3D *, float, int *, int)>(
                    &Pathfinder::CheckForAdjust)))(word04, word08, 1, x, y, kind, word0C,
                option10, &position1C, 0, 0.0f, &adjust, 0) && !adjust)
        {
            success18 = true;
            position28 = position1C;
        }
    }
    return 0;
}
