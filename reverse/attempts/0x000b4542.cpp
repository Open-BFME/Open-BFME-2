// ?bfmeRelativeAngleTo@Thing@@QBEMPBUCoord3D@@@Z
// partial score=0.98 date=2026-10-09
// cl: /O1 /arch:SSE2
// ?bfmeRelativeAngleTo@Thing@@QBEMPBUCoord3D@@@Z @0x000B4542 273B
// BFME1 donor Code/GameEngine/Source/Common/Thing/Thing_bfmeRelativeAngleTo.cpp
// (matched 214B at 0x00150510): the signed angle between the unit's 2D facing
// (pinned getUnitDirectionVector2D 0x0030A25F) and the direction to a point,
// from the cached position at +0x38. Callers 0x000B788A 0x000CC9A8 0x001E9BFC.
// The sqrt declaration is math.h's: with a bare extern "C" prototype MSVC
// schedules the result store between the argument pops (the banked 0.99).
#include <math.h>
#include "../../../../Libraries/Include/Lib/Coord3D.h"
typedef float Real;
extern Real ACos(Real);
class Thing {
public:
  const Coord3D *getUnitDirectionVector2D() const;
  Real bfmeRelativeAngleTo(const Coord3D *point) const;
private:
  unsigned char m_pad000[0x38];
  Coord3D m_cachedPos;
};
Real Thing::bfmeRelativeAngleTo(const Coord3D *point) const
{
  Coord3D delta;
  delta.x = point->x - m_cachedPos.x;
  delta.y = point->y - m_cachedPos.y;
  Real distance = (Real)sqrt(delta.x * delta.x + delta.y * delta.y);
  if (distance == 0.0f)
    return 0.0f;
  Real scale = 1.0f / distance;
  delta.x *= scale;
  delta.y *= scale;
  const Coord3D *direction = getUnitDirectionVector2D();
  Real cosine = direction->x * delta.x;
  cosine += direction->y * delta.y;
  if (cosine < -1.0)
    cosine = -1.0f;
  else if (cosine > 1.0)
    cosine = 1.0f;
  Real angle = ACos(cosine);
  if (direction->x * delta.y - direction->y * delta.x < 0.0f)
    angle = -angle;
  return angle;
}
