// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// Ported from Open-BFME-1's game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewWorldToScreenBfme.cpp
// (donor revision 6583b3c1ff21db4a561285717028fdafc780b7db) with /O1 /arch:SSE
// added to its flags, the settings W3DView.cpp's donor bodies match under.
// Searched by masked whole-.text search, the body places once on unclaimed
// game.dat .text at 0x0008619F (166B). BFME 2 changed the result logic (0.87
// against the donor): only OUTSIDE_NEAR_CLIP zeroes the point and returns
// WTS_INVALID; every other projection is converted and offset by the origin,
// and the return distinguishes inside from outside the frustum.

typedef int Int;

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct ICoord2D
{
	Int x;
	Int y;
};

class Vector3
{
public:
	Vector3() {}
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}

	float X;
	float Y;
	float Z;
};

class CameraClass
{
public:
	enum ProjectionResType
	{
		INSIDE_FRUSTUM,
		OUTSIDE_FRUSTUM,
		OUTSIDE_NEAR_CLIP,
		OUTSIDE_FAR_CLIP
	};

	ProjectionResType Project(Vector3 &destination, const Vector3 &source) const;
};

extern void W3DLogicalScreenToPixelScreen(float, float, Int *, Int *, Int, Int);

class View
{
public:
	enum WorldToScreenReturn
	{
		WTS_INSIDE_FRUSTUM,
		WTS_OUTSIDE_FRUSTUM,
		WTS_INVALID
	};
};

class W3DView
{
public:
	virtual void v00() = 0;
	virtual void v01() = 0;
	virtual void v02() = 0;
	virtual void v03() = 0;
	virtual void v04() = 0;
	virtual void v05() = 0;
	virtual void v06() = 0;
	virtual void v07() = 0;
	virtual void v08() = 0;
	virtual void v09() = 0;
	virtual void v10() = 0;
	virtual void v11() = 0;
	virtual void v12() = 0;
	virtual void v13() = 0;
	virtual void v14() = 0;
	virtual Int getWidth();
	virtual void v16() = 0;
	virtual Int getHeight();
	virtual View::WorldToScreenReturn worldToScreenTriReturn(const Coord3D *, ICoord2D *);

private:
	char m_pad04[0x1c];
	Int m_originX;
	Int m_originY;
	char m_pad28[0x104 - 0x28];
	CameraClass *m_3DCamera;
};

// ?worldToScreenTriReturn@W3DView@@UAE?AW4WorldToScreenReturn@View@@PBUCoord3D@@PAUICoord2D@@@Z
View::WorldToScreenReturn W3DView::worldToScreenTriReturn(const Coord3D *world,
	ICoord2D *screen)
{
	if (world == 0 || screen == 0 || m_3DCamera == 0)
		return View::WTS_INVALID;

	Vector3 worldVector(world->x, world->y, world->z);
	Vector3 screenVector;
	CameraClass::ProjectionResType projection = m_3DCamera->Project(screenVector, worldVector);
	if (projection == CameraClass::OUTSIDE_NEAR_CLIP)
	{
		screen->x = 0;
		screen->y = 0;
		return View::WTS_INVALID;
	}

	W3DLogicalScreenToPixelScreen(screenVector.X, screenVector.Y, &screen->x, &screen->y,
		getWidth(), getHeight());
	screen->x += m_originX;
	screen->y += m_originY;
	if (projection != CameraClass::INSIDE_FRUSTUM)
		return View::WTS_OUTSIDE_FRUSTUM;
	return View::WTS_INSIDE_FRUSTUM;
}
