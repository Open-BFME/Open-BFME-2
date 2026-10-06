// cl: /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath
// Transferred unchanged from Open-BFME-1 5cae4bdff game/Libraries/Source/WWVegas/WWMath/Rva009F40A0DistanceSquared.cpp;
// bfme1_sweep places the same masked body: Rva009F40A0DistanceSquared at BFME2 0x00626A60. Addresses in the donor text are BFME1.
#include "coord3d.h"
class Rva009F40A0PositionProvider {
public:
 virtual void slot0();
 virtual const Coord3DBase *position();
};
float Rva009F40A0DistanceSquared(const Coord3DBase *a,
 Rva009F40A0PositionProvider *provider)
{
 const Coord3DBase *b = provider->position();
 float dz = b->z - a->z;
 float dy = b->y - a->y;
 float dx = b->x - a->x;
 return dx * dx + dy * dy + dz * dz;
}
