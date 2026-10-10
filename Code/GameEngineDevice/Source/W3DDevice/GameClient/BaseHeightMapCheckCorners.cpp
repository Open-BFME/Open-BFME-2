// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc

// BaseHeightMapRenderObjClass::CheckCorners, retail 0x00067494..0x000677CA
// (822 bytes, RET 0x20). WorldBuilder's debug build names it and places it in
// BaseHeightMap.cpp (ASSERT(heightIn && slopeIn) at line 1819; retail keeps the
// asserts out). For the four corners of one cell it samples the terrain through
// the virtual getHeightMapHeight (vtable +0x244, with the normal out-parameter):
// the truncated height must lie in [heightMin, heightMax] or *heightIn is
// cleared, and the slope angles away from the x and y axes
// (|90 - atan2(nz, nx)| and |90 - atan2(nz, ny)| in degrees) must lie in
// [slopeMin, slopeMax] or *slopeIn is cleared. Both flags start true.
// The debug body shows the float CRT overloads: the atan2 result and the fabs
// argument and result pass through float, and RAD_TO_DEGF multiplies by 180
// and divides by WWMATH_PI. Retail calls the statically linked _atan2f
// (0x000422CD) and the double fabs (0x00629210); the float fabs overload is
// MSVC 7.1 <math.h>'s, kept TU-local like the getHeightMapHeight sibling's
// float CRT wrapper.
#include "../../../../Libraries/Include/Lib/Coord3D.h"

typedef int Int;
typedef float Real;
typedef bool Bool;

extern "C" float __cdecl atan2f(float y, float x);
extern "C" double __cdecl fabs(double x);
inline float __cdecl fabs(float _X) { return ((float)fabs((double)_X)); }

#define MAP_XY_FACTOR 10.0f
#define WWMATH_PI 3.141592654f
#define RAD_TO_DEGF(x) (((float)x) * 180.0f / WWMATH_PI)

#define CHECK_CORNERS_V(n) virtual void slot##n();
#define CHECK_CORNERS_V10(n) CHECK_CORNERS_V(n##0) CHECK_CORNERS_V(n##1) CHECK_CORNERS_V(n##2) \
	CHECK_CORNERS_V(n##3) CHECK_CORNERS_V(n##4) CHECK_CORNERS_V(n##5) CHECK_CORNERS_V(n##6) \
	CHECK_CORNERS_V(n##7) CHECK_CORNERS_V(n##8) CHECK_CORNERS_V(n##9)

class BaseHeightMapRenderObjClass
{
public:
	CHECK_CORNERS_V(0) CHECK_CORNERS_V(1) CHECK_CORNERS_V(2) CHECK_CORNERS_V(3) CHECK_CORNERS_V(4)
	CHECK_CORNERS_V(5) CHECK_CORNERS_V(6) CHECK_CORNERS_V(7) CHECK_CORNERS_V(8) CHECK_CORNERS_V(9)
	CHECK_CORNERS_V10(1) CHECK_CORNERS_V10(2) CHECK_CORNERS_V10(3) CHECK_CORNERS_V10(4)
	CHECK_CORNERS_V10(5) CHECK_CORNERS_V10(6) CHECK_CORNERS_V10(7) CHECK_CORNERS_V10(8)
	CHECK_CORNERS_V10(9) CHECK_CORNERS_V10(10) CHECK_CORNERS_V10(11) CHECK_CORNERS_V10(12)
	CHECK_CORNERS_V10(13)
	CHECK_CORNERS_V(140) CHECK_CORNERS_V(141) CHECK_CORNERS_V(142) CHECK_CORNERS_V(143)
	CHECK_CORNERS_V(144)
	virtual Real getHeightMapHeight(Real x, Real y, Coord3D *normal) const;	// slot 145 (+0x244)
	void CheckCorners(Int x, Int y, Int heightMax, Int heightMin, Int slopeMax, Int slopeMin, Bool *heightIn, Bool *slopeIn);
};

#undef CHECK_CORNERS_V10
#undef CHECK_CORNERS_V

void BaseHeightMapRenderObjClass::CheckCorners(Int x, Int y, Int heightMax, Int heightMin, Int slopeMax, Int slopeMin, Bool *heightIn, Bool *slopeIn)
{
	*heightIn = true;
	*slopeIn = true;

	Coord3D normal;
	Real py = y * MAP_XY_FACTOR;
	Real px = x * MAP_XY_FACTOR;
	Int height = (Int)getHeightMapHeight(px, py, &normal);
	if (height < heightMin || height > heightMax)
		*heightIn = false;
	Real slopeX = fabs(90.0f - RAD_TO_DEGF(atan2f(normal.z, normal.x)));
	Real slopeY = fabs(90.0f - RAD_TO_DEGF(atan2f(normal.z, normal.y)));
	if (slopeMin > slopeX || slopeX > slopeMax || slopeMin > slopeY || slopeY > slopeMax)
		*slopeIn = false;

	x++;
	Real px2 = x * MAP_XY_FACTOR;
	height = (Int)getHeightMapHeight(px2, py, &normal);
	if (height < heightMin || height > heightMax)
		*heightIn = false;
	slopeX = fabs(90.0f - RAD_TO_DEGF(atan2f(normal.z, normal.x)));
	slopeY = fabs(90.0f - RAD_TO_DEGF(atan2f(normal.z, normal.y)));
	if (slopeMin > slopeX || slopeX > slopeMax || slopeMin > slopeY || slopeY > slopeMax)
		*slopeIn = false;

	y++;
	Real py2 = y * MAP_XY_FACTOR;
	height = (Int)getHeightMapHeight(px2, py2, &normal);
	if (height < heightMin || height > heightMax)
		*heightIn = false;
	slopeX = fabs(90.0f - RAD_TO_DEGF(atan2f(normal.z, normal.x)));
	slopeY = fabs(90.0f - RAD_TO_DEGF(atan2f(normal.z, normal.y)));
	if (slopeMin > slopeX || slopeX > slopeMax || slopeMin > slopeY || slopeY > slopeMax)
		*slopeIn = false;

	height = (Int)getHeightMapHeight(px, py2, &normal);
	if (height < heightMin || height > heightMax)
		*heightIn = false;
	slopeX = fabs(90.0f - RAD_TO_DEGF(atan2f(normal.z, normal.x)));
	slopeY = fabs(90.0f - RAD_TO_DEGF(atan2f(normal.z, normal.y)));
	if (slopeMin > slopeX || slopeX > slopeMax || slopeMin > slopeY || slopeY > slopeMax)
		*slopeIn = false;
}
