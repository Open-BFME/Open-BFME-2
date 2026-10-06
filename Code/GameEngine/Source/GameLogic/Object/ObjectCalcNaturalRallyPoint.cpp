// cl: /G7 /arch:SSE /DNDEBUG /MD /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep
//
// ?calcNaturalRallyPoint@Object@@QAEXPAUCoord2D@@@Z retail 0x0028B65F, 67
// bytes: the Zero Hour Object.cpp body, placed by masked whole-.text search of
// a /G7 /arch:SSE build (single hit). The Thing transform it reads sits at
// Object +0x08, as the retail loads [ecx+0x08..0x24] show.

#include "matrix3d.h"

#include "../../../../Libraries/Include/Lib/Coord2D.h"

class Object
{
public:
	void calcNaturalRallyPoint(Coord2D *pt);
	const Matrix3D *getTransformMatrix() const { return &m_transform; }

private:
	void *m_thingHead[2];
	Matrix3D m_transform;
};

void Object::calcNaturalRallyPoint(Coord2D *pt)
{
	const Matrix3D *transform = getTransformMatrix();
	Vector3 v;

	v.Set( 0, 0, 0 );

	// transform the point into world space
	transform->Transform_Vector( *transform, v, &v );

	// we're only concerned with the 2D elements for now
	pt->x = v.X;
	pt->y = v.Y;

}
