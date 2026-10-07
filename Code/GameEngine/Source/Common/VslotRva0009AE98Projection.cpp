// cl: /O1 /arch:SSE /G7 /MD /Oi-
// ?rva0009AE98@Rva0009AE98@@UAE_NPBVVector3@@PAH@Z @0x0009AE98 248B.
// Target evidence: vtable 0x007C89C8 slot 15; the body projects the input point and converts it to screen coordinates. Class identity remains unresolved, so the address-based class name is used.
class Vector3
{
public:
	float X;
	float Y;
	float Z;
};

class CameraClass
{
public:
	enum ProjectionResType
	{
		PROJECTION_ORTHO = 0,
		PROJECTION_PERSPECTIVE = 1,
		PROJECTION_INVALID_2 = 2,
		PROJECTION_INVALID_3 = 3
	};
	ProjectionResType Project(Vector3 &dest, const Vector3 &source) const;
};

class Display
{
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
#undef V
	virtual unsigned int GetWidth();
	virtual unsigned int GetHeight();
};

extern Display *TheDisplay;
void __cdecl Rva00101E1EConvert(float, float, int *, int *, int, int);

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
	float width = (float)TheDisplay->GetWidth();
	float height = (float)TheDisplay->GetHeight();
	Rva00101E1EConvert(projected.X, projected.Y, &screen[0], &screen[1], width, height);
	if (projected.X > 2.0f)
		return false;
	if (projected.Y > 2.0f)
		return false;
	if (-2.0f > projected.X)
		return false;
	if (-2.0f > projected.Y)
		return false;
	if (result != CameraClass::PROJECTION_INVALID_2 && result != CameraClass::PROJECTION_INVALID_3)
		return true;
	return false;
}
