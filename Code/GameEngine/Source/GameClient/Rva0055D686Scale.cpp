// cl: /O1 /arch:SSE /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath
// ?Rva0055D686Compute@@YGXPAVCoord3D@@PAVCoord2D@@MM@Z at 0x0055D686 size 81
// Evidence: REF table slot 0x0081C7E8 neighbours EmissionVolumeInfo; cylinder emission helper normalizes Coord2D then scales by radius and sets Z.

#include "coord3d.h"

struct XY
{
    float x;
    float y;
};

void __stdcall Rva0055D686Compute(Coord3D *out, Coord2D *dir, float scale, float z)
{
    XY tmp;
    tmp.x = dir->x;
    tmp.y = dir->y;
    ((Coord2D *)&tmp)->normalize();
    XY p;
    p.x = tmp.x * scale;
    p.y = tmp.y * scale;
    out->x = p.x;
    out->y = p.y;
    out->z = z;
}
