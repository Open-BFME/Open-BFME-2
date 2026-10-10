// ?rva0004DF6F@@YAXXZ
// partial score=0.98 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
// ?rva0004DF6F@@YAXPBVObject@@PAXHHMM@Z  Native 0x0004DF6F..0x0004E1A8 (569 bytes)
// Radar footprint fill: locks the radar surface over the object's bounding
// circle and blends every pixel whose world point lies inside the object's
// geometry against two radar probe geometries (full alpha / half alpha).
// Static helper: its only retail caller 0x00050125 passes the object in EBX.
#include "Coord3D.h"

typedef int Int;
typedef int Color;
typedef float Real;
typedef unsigned char UnsignedByte;

class Member0C00739C70 { public: void clear(); };
class Rva0004D729 {
public:
	Rva0004D729(void *surface, void **bits, int *pitch, int left, int top, int right, int bottom) {
		rva0004D729(surface, bits, pitch, left, top, right, bottom);
	}
	~Rva0004D729() { m_surface->clear(); }
	Rva0004D729 *rva0004D729(void *surface, void **bits, int *pitch, int left, int top, int right, int bottom);
	Member0C00739C70 *m_surface;
};

struct ICoord2D { Int x, y; };

class GeometryInfo {
public:
	bool bfmeIntersects(const Coord3D &pos, Real angle, const GeometryInfo &other,
		const Coord3D &otherPos, Real otherAngle) const;
	Real getBoundingCircleRadius() const { return m_boundingCircleRadius; }
	char m_pad00[0x10];
	Real m_boundingCircleRadius;
};

class Object {
public:
	Color getIndicatorColor() const;
	const Coord3D *getPosition() const { return &m_pos; }
	Real getOrientation() const { return m_angle; }
	const GeometryInfo &getGeometryInfo() const { return m_geometryInfo; }
	char m_pad00[0x38];
	Coord3D m_pos;
	Real m_angle;
	char m_pad48[0xa8 - 0x48];
	GeometryInfo m_geometryInfo;
};

Color Rva0004DE72Blend(Color *color, Color source, UnsignedByte alpha);
extern unsigned int g_Va00DE1D00;
extern unsigned int g_Va00DE1D60;

static void rva0004DF6F(const Object *obj, void *surface, Int width, Int height,
	Real scaleX, Real scaleY)
{
	if (obj == 0)
		return;

	const Coord3D *pos = obj->getPosition();
	Int radius = (Int)obj->getGeometryInfo().getBoundingCircleRadius();
	ICoord2D center;
	center.x = (Int)(pos->x * scaleX);
	center.y = (Int)(pos->y * scaleY);
	Int x0 = (Int)(center.x - radius * scaleX);
	Int y0 = (Int)(center.y - radius * scaleY);
	Int x1 = (Int)(center.x + radius * scaleX);
	Int y1 = (Int)(center.y + radius * scaleY);
	Int left = (x0 > 0) ? x0 : 0;
	Int top = (y0 > 0) ? y0 : 0;
	Int right = (x1 < width) ? x1 : width;
	Int bottom = (y1 < height) ? y1 : height;

	int pitch;
	void *bits;
	Rva0004D729 lock(surface, &bits, &pitch, left, top, right, bottom);
	if (bits)
	{
		Color color = obj->getIndicatorColor();
		Coord3D pt;
		pt.x = pos->x;
		pt.y = pos->y;
		pt.z = pos->z;
		for (Int y = top; y < bottom; ++y)
		{
			Color *row = (Color *)((char *)bits + (y - top) * pitch);
			pt.y = (center.y - y) * (1.0f / scaleY) + pos->y;
			for (Int x = left; x < right; ++x)
			{
				pt.x = (center.x - x) * (1.0f / scaleX) + pos->x;
				if (obj->getGeometryInfo().bfmeIntersects(*pos, obj->getOrientation(),
					reinterpret_cast<const GeometryInfo &>(g_Va00DE1D00), pt, 0.0f))
				{
					if (obj->getGeometryInfo().bfmeIntersects(*pos, obj->getOrientation(),
						reinterpret_cast<const GeometryInfo &>(g_Va00DE1D60), pt, 0.0f))
						Rva0004DE72Blend(&row[x - left], color, 0xff);
					else
						Rva0004DE72Blend(&row[x - left], color, 0x80);
				}
			}
		}
	}
}


// ?rva0004DF6FCaller absent-from-retail
void rva0004DF6FCaller(const Object *const *objs, Int n, void *surface, Int width, Int height, Real sx, Real sy)
{
	for (Int i = 0; i < n; ++i)
	{
		const Object *obj = objs[i];
		if (obj->getOrientation() > 0.0f)
			rva0004DF6F(obj, surface, width, height, sx, sy);
	}
}
