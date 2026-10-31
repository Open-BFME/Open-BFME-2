// cl: /D__PLACEMENT_VEC_NEW_INLINE /FIzh_ascii.h /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/sweep_bfme1_outofline /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Include/Lib /ICode/Libraries/Include /Ireference/shims/moduledata /Ireference/shims/subsystem_bfme2
// stlport
// ?rva0004DF6F@@YAXPBVObject@@PAXHHMM@Z  Native 0x0004DF6F..0x0004E1A8 (569 bytes)
// W3DRadar footprint fill static (object in EBX); standalone fallback with a
// dummy caller marked absent-from-retail (same practice as 4E55B / 4E704).
// Exact including EH .xdata. Preferred home is the combined object-list unit.
#include "always.h"
#undef W3DMPO_GLUE
#define W3DMPO_GLUE(ARGCLASS)
#define Matrix4x4 Matrix4  // BFME renamed it
#include "Common/Geometry.h"
#include "GameLogic/Object.h"
#include "W3DDevice/Common/W3DRadar.h"

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
// The bank bodies of 0x0004F037 / 0x0004F29B spell the same lock this way.
class NativeRadarSurfaceLock : public Rva0004D729 {
public:
	NativeRadarSurfaceLock(void *surface, void *&bits, int *pitch, int left, int top, int right, int bottom)
		: Rva0004D729(surface, &bits, pitch, left, top, right, bottom) {}
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
	Int radius = (Int)obj->getGeometryInfo().getMajorRadius();	// GeometryInfo +0x10
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
	if (!bits)
		return;
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
				if (obj->getGeometryInfo().CollidesWith(*pos, obj->getOrientation(),
					reinterpret_cast<const GeometryInfo &>(g_Va00DE1D00), pt, 0.0f))
				{
					if (obj->getGeometryInfo().CollidesWith(*pos, obj->getOrientation(),
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
void rva0004DF6FCaller(const Object *obj, void *surface, Int width, Int height, Real scaleX, Real scaleY)
{
	rva0004DF6F(obj, surface, width, height, scaleX, scaleY);
}
