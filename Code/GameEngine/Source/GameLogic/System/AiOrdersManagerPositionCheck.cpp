// cl: /O1 /G7 /arch:SSE /MD /GX /DNDEBUG
#include "../../../../Libraries/Include/Lib/Coord3D.h"
// Native354EB9..354EF6 computes strict XY distance-squared <200. The two
// callers35538C/355472 compare object+38 with destination; the helper's
// original name and public return type remain unknown (full EAX 0/1).
bool Rva00354EB9(const Coord3D *position,const Coord3D *destination) {
    float dx=position->x-destination->x;
    float dy=position->y-destination->y;
    return dy*dy+dx*dx<200.0f;
}
