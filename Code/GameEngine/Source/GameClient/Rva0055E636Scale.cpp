// cl: /O1 /arch:SSE /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath
// ?Rva0055E636Compute@@YGXPAVCoord3D@@0MM@Z at 0x0055E636 size 97
// Evidence: sibling of 0x0055D686 81B XY trick; REF table slot; normalizes Coord3D then scales all three.

#include "coord3d.h"

struct XYZ
{
    float x;
    float y;
    float z;
};

void __stdcall Rva0055E636Compute(Coord3D *out, Coord3D *dir, float scale, float unused)
{
    XYZ tmp;
    tmp.x = dir->x;
    tmp.y = dir->y;
    tmp.z = dir->z;
    ((Coord3D *)&tmp)->normalize();
    XYZ p;
    p.x = tmp.x * scale;
    p.y = tmp.y * scale;
    p.z = tmp.z * scale;
    out->x = p.x;
    out->y = p.y;
    out->z = p.z;
}
