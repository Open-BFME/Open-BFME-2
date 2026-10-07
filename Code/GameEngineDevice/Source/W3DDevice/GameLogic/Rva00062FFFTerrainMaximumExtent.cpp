// cl: /ICode/Libraries/Include /O1 /G7 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
// Clean donor: BFME1 ba7ddda7 W3DTerrainLogicMaximumPathfindExtent.cpp,
// supported independently by ZH W3DTerrainLogic::getMaximumPathfindExtent.
// Native complete 62FFF..63082: one backward loop, RET4, then a separate EBP
// prologue at 63082. BFC5890 slot +30 and accepted runtime caller 266101
// establish the entry and receiver relationship. The existing table's named
// terrain slots support the subsystem; this is a borrowed observed prefix,
// not an assertion of the original class name or full allocation size.
// Target independently proves vector words +30/+34 (8-byte x/y entries),
// z limits +191C/+1920, and the float 10.0 at BC2428. The donor's loop and
// full 131-byte body match after those offsets and the normal SSE flags.
// Runtime archive SHA256 3d974bf055b14b83983430e6ed98de423a60901217b4b9cd815c5b1b401e41b9.

#include <vector>

typedef float Real;
typedef int Int;

#define MAP_XY_FACTOR 10.0f

struct ICoord2D
{
    Int x;
    Int y;
};

#include "Lib/Coord3D.h"

struct Region3D
{
    Coord3D lo;
    Coord3D hi;
};

typedef _STL::vector<ICoord2D> BoundaryVector;

class Rva00062FFFTerrainPrefix
{
public:
    void getMaximumPathfindExtent(Region3D *extent) const;

private:
    char m_pad00[0x30];
    BoundaryVector m_boundaries;
    char m_pad3c[0x191c - 0x3c];
    Real m_mapMinZ;
    Real m_mapMaxZ;
};

void Rva00062FFFTerrainPrefix::getMaximumPathfindExtent(Region3D *extent) const
{
    extent->lo.x = 0.0f;
    extent->lo.y = 0.0f;
    extent->hi.x = 0.0f;
    extent->hi.y = 0.0f;

    for (Int i = 0; i < m_boundaries.size(); ++i)
    {
        if (extent->hi.x < m_boundaries[i].x * MAP_XY_FACTOR)
            extent->hi.x = m_boundaries[i].x * MAP_XY_FACTOR;
        if (extent->hi.y < m_boundaries[i].y * MAP_XY_FACTOR)
            extent->hi.y = m_boundaries[i].y * MAP_XY_FACTOR;
    }

    extent->lo.z = m_mapMinZ;
    extent->hi.z = m_mapMaxZ;
}
