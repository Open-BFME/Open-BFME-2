// cl: /ICode/Libraries/Include /O1 /G7 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
// Clean donor: BFME1 ba7ddda7 W3DTerrainLogicMaximumPathfindExtent.cpp,
// supported independently by ZH W3DTerrainLogic::getMaximumPathfindExtent.
// Native complete 62FFF..63082: one backward loop, RET4, then a separate EBP
// prologue at 63082. BFC5890 slot +30 and accepted runtime caller 266101
// establish the entry and receiver relationship. The existing table's named
// terrain slots support the subsystem; this is a borrowed observed prefix,
// not an assertion of the original class name or full allocation size.
// Target independently proves vector words +30/+34 (8-byte x/y entries),
// z limits +191C/+1920, and the float 10.0 at BC2428. The donor's loop and
// full 131-byte body match after those offsets and the normal SSE flags.
// Runtime archive SHA256 3d974bf055b14b83983430e6ed98de423a60901217b4b9cd815c5b1b401e41b9.

#include <vector>

typedef float Real;
typedef int Int;

#define MAP_XY_FACTOR 10.0f

struct ICoord2D
{
    Int x;
    Int y;
};

#include "Lib/Coord3D.h"

struct Region3D
{
    Coord3D lo;
    Coord3D hi;
};

typedef _STL::vector<ICoord2D> BoundaryVector;

class Rva00062FFFTerrainPrefix
{
public:
    void getMaximumPathfindExtent(Region3D *extent) const;
    void activeBoundaryExtent(Region3D *extent) const;
    float groundHeight(float x,float y,Coord3D *normal) const;
    void largestBoundaryExtent(Region3D *extent) const;

private:
    char m_pad00[0x30];
    BoundaryVector m_boundaries;
    int m_activeBoundary; // native active index +3C
    char m_pad40[0x191c - 0x40];
    Real m_mapMinZ;
    Real m_mapMaxZ;
};

void Rva00062FFFTerrainPrefix::getMaximumPathfindExtent(Region3D *extent) const
{
    extent->lo.x = 0.0f;
    extent->lo.y = 0.0f;
    extent->hi.x = 0.0f;
    extent->hi.y = 0.0f;

    for (Int i = 0; i < m_boundaries.size(); ++i)
    {
        if (extent->hi.x < m_boundaries[i].x * MAP_XY_FACTOR)
            extent->hi.x = m_boundaries[i].x * MAP_XY_FACTOR;
        if (extent->hi.y < m_boundaries[i].y * MAP_XY_FACTOR)
            extent->hi.y = m_boundaries[i].y * MAP_XY_FACTOR;
    }

    extent->lo.z = m_mapMinZ;
    extent->hi.z = m_mapMaxZ;
}

// Adjacent BFC5890 slots +20/+24 contain 62EF8/62F64. Native complete
// extents are 62EF8..62F64 (108B RET4) and 62F64..62FFF (155B RET4),
// independently disassembled. First uses target +3C to select one boundary;
// its pointer-equality empty test is the native form of ZH getExtent's guard.
// The second is the exact clean ba7ddda7 W3DTerrainLogicGetExtent.cpp body:
// unscaled floating extrema across all boundaries, then scale by 10 and copy
// z limits. Its original slot spelling remains unasserted. The same measured
// vector/z offsets and ordinary compiler flags reproduce each whole body.
void Rva00062FFFTerrainPrefix::activeBoundaryExtent(Region3D *extent) const {
 extent->lo.x=0.0f;
 extent->lo.y=0.0f;
 if(!m_boundaries.empty()) {
  extent->hi.x=m_boundaries[m_activeBoundary].x*MAP_XY_FACTOR;
  extent->hi.y=m_boundaries[m_activeBoundary].y*MAP_XY_FACTOR;
 }else {
  extent->hi.x=0.0f;
  extent->hi.y=0.0f;
 }
 extent->lo.z=m_mapMinZ;
 extent->hi.z=m_mapMaxZ;
}

void Rva00062FFFTerrainPrefix::largestBoundaryExtent(Region3D *extent) const
{
    extent->lo.x = 0.0f;
    extent->lo.y = 0.0f;

    struct Extrema
    {
        Real x;
        Real y;
    } extrema;

    if (!m_boundaries.empty())
    {
        extrema.x = m_boundaries[0].x;
        extrema.y = m_boundaries[0].y;

        for (Int i = 1; i < m_boundaries.size(); ++i)
        {
            if (m_boundaries[i].x > extrema.x)
                extrema.x = m_boundaries[i].x;
            if (m_boundaries[i].y > extrema.y)
                extrema.y = m_boundaries[i].y;
        }

        extent->hi.x = extrema.x * MAP_XY_FACTOR;
        extent->hi.y = extrema.y * MAP_XY_FACTOR;
    }
    else
    {
        extent->hi.x = 0.0f;
        extent->hi.y = 0.0f;
    }

    extent->lo.z = m_mapMinZ;
    extent->hi.z = m_mapMaxZ;
}

// Ground-height forwarder 62C45..62C95, RET12, terrain table slot +18.
// Primary source lead: ZH W3DTerrainLogic::getGroundHeight; BFME1 ba7ddda7
// getLayerHeight supplies the compatible renderer vtable slice. Target sets
// optional normal to (0,0,1) before testing the actual owned global, then calls
// renderer slot +244 with x/y/normal or returns float zero. That ordering,
// slot offset and the complete 80-byte body are independent native evidence.
// This declaration-only slice emits no vtable or implementations. Placeholder
// slots preserve only the witnessed dispatch offset, not their original names.
#define UNUSED_VIRTUALS_16(prefix) \
	virtual void prefix##0() = 0; virtual void prefix##1() = 0; \
	virtual void prefix##2() = 0; virtual void prefix##3() = 0; \
	virtual void prefix##4() = 0; virtual void prefix##5() = 0; \
	virtual void prefix##6() = 0; virtual void prefix##7() = 0; \
	virtual void prefix##8() = 0; virtual void prefix##9() = 0; \
	virtual void prefix##a() = 0; virtual void prefix##b() = 0; \
	virtual void prefix##c() = 0; virtual void prefix##d() = 0; \
	virtual void prefix##e() = 0; virtual void prefix##f() = 0

class Rva00062C45HeightMapVtableSlice
{
public:
	UNUSED_VIRTUALS_16(unused000_);
	UNUSED_VIRTUALS_16(unused040_);
	UNUSED_VIRTUALS_16(unused080_);
	UNUSED_VIRTUALS_16(unused0c0_);
	UNUSED_VIRTUALS_16(unused100_);
	UNUSED_VIRTUALS_16(unused140_);
	UNUSED_VIRTUALS_16(unused180_);
	UNUSED_VIRTUALS_16(unused1c0_);
	UNUSED_VIRTUALS_16(unused200_);
	virtual void unused240_0() = 0;
	virtual float getHeightMapHeight(float x, float y, Coord3D *normal) const;
};


class BaseHeightMapRenderObjClass;
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;
#undef UNUSED_VIRTUALS_16

float Rva00062FFFTerrainPrefix::groundHeight(float x,float y,Coord3D *normal) const {
 if(normal) {normal->x=0.0f;normal->y=0.0f;normal->z=1.0f;}
 if(TheTerrainRenderObject)
  return ((const Rva00062C45HeightMapVtableSlice *)TheTerrainRenderObject)->getHeightMapHeight(x,y,normal);
 return 0.0f;
}
