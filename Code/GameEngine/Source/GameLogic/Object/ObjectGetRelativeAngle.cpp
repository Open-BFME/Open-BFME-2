// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?GetRelativeAngle@Object@@QBEMPBUCoord3D@@@Z  retail 0x000B4542..0x000B4653
// (273 bytes ret 4).  WorldBuilder twin Object::GetRelativeAngle (Object.h
// inline; wb 0x916680): the signed angle between the object's 2D facing
// (Thing::getUnitDirectionVector2D 0x0030A25F) and the direction from its
// cached position (+0x38) to a point.  The delta is normalised through the
// header's inline Coord3D::scale -- its address is taken -- which is what
// makes cl keep both facing components in registers for the dot and cross
// products; the dot product written as two statements orders its loads.
// ACos is 0x0002FB90; sqrt is the MSVCRT import.  Callers include
// AIFaceState::update 0x003548B7 and 0x0034AAC8.
#include <math.h>
#include "../../../../Libraries/Include/Lib/Coord3D.h"

typedef float Real;
extern Real ACos(Real);

class Thing {
public:
  const Coord3D *getUnitDirectionVector2D() const;
};

class Object : public Thing {
public:
  Real GetRelativeAngle(const Coord3D *pos) const;
private:
  unsigned char m_pad004[0x38];
  Coord3D m_cachedPos;
};

Real Object::GetRelativeAngle(const Coord3D *pos) const
{
  Coord3D delta;
  delta.x = pos->x - m_cachedPos.x;
  delta.y = pos->y - m_cachedPos.y;
  Real distance = (Real)sqrt(delta.x * delta.x + delta.y * delta.y);
  if (distance == 0.0f)
    return 0.0f;
  Coord3D *dir = &delta;  // inline Coord3D::scale( 1.0f / distance )
  Real scale = 1.0f / distance;
  dir->x *= scale;
  dir->y *= scale;
  const Coord3D *facing = getUnitDirectionVector2D();
  Real cosine = delta.x * facing->x;
  cosine += delta.y * facing->y;
  if (cosine < -1.0)
    cosine = -1.0f;
  else if (cosine > 1.0)
    cosine = 1.0f;
  Real angle = ACos(cosine);
  if (delta.y * facing->x - delta.x * facing->y < 0.0f)
    angle = -angle;
  return angle;
}
