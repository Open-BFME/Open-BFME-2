// cl: /O1 /arch:SSE /G7 /MD /Oi- /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// ?rva0009AE98@Rva0009AE98@@UAE_NPBVVector3@@PAH@Z @0x0009AE98 248B.
// Target evidence: vtable 0x007C89C8 slot 15; the body projects the input point and converts it to screen coordinates. Class identity remains unresolved, so the address-based class name is used.
#include "vector3.h"

#include "../../../Libraries/Source/WWVegas/WW3D2/CameraClass.h"

#include "../../Include/GameClient/Display.h"
void __cdecl W3DLogicalScreenToPixelScreen(float, float, int *, int *, int, int);

class Rva0009AE98
{
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14)
#undef V
	virtual bool rva0009AE98(const Vector3 *point, int *screen);

private:
	char m_pad00[0xbc];
	CameraClass *m_camera;
};

bool Rva0009AE98::rva0009AE98(const Vector3 *point, int *screen)
{
	if (point == 0 || screen == 0)
		return false;

	Vector3 source;
	source.X = point->X;
	source.Y = point->Y;
	source.Z = point->Z;
	Vector3 projected;
	CameraClass::ProjectionResType result = m_camera->Project(projected, source);
	float width = (float)TheDisplay->getWidth();
	float height = (float)TheDisplay->getHeight();
	W3DLogicalScreenToPixelScreen(projected.X, projected.Y, &screen[0], &screen[1], width, height);
	if (projected.X > 2.0f)
		return false;
	if (projected.Y > 2.0f)
		return false;
	if (-2.0f > projected.X)
		return false;
	if (-2.0f > projected.Y)
		return false;
	if (result != CameraClass::OUTSIDE_NEAR_CLIP && result != CameraClass::OUTSIDE_FAR_CLIP)
		return true;
	return false;
}
