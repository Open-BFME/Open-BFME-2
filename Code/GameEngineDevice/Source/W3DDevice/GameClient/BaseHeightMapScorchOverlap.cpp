// cl: /O1 /G7 /MD /arch:SSE /EHsc /DNDEBUG /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// Native69C5F..69CE6 full135 RET16; original method name remains unknown.
// Owner: W3DGameClient::addScorch calls67EA3 on TheTerrainRenderObject.
// That native sibling proves arrayE0 stride1C capacity500, position4/radius10,
// type14/flag18, count3790 and cached3794. This loop marks overlaps.
// Ref: BF1@575ba2b BaseHeightMap addScorch is a subsystem/layout guide;
// the overlap algorithm and every accessed target offset come from retail.
// Native uses x87 FSQRT between SSE vector length and SSE radius comparison.
// This narrow WWMath-style primitive preserves that proven x87 codegen shape.
// The location is a by-value Vector3 (W3DTerrainVisual's forwarder 0x00091EEC
// pushes its 12-byte position then the radius), WWMath's Vector3.
static __forceinline float scorchSqrt(float value)
{
    float result;
    __asm { fld value
            fsqrt
            fstp result }
    return result;
}
#include "../../../Include/W3DDevice/GameClient/WorldHeightMap.h"

// Use the canonical RefCountClass instead of the donor refcount.h.
#define REFCOUNT_H

#include "../../../Include/W3DDevice/GameClient/BaseHeightMap.h"

struct TerrainScorchEntry
{
    void *snapshotView; // untouched leading word; no original field name asserted
    Vector3 position;
    float radius;
    int type;
    bool active;
    char padding[3];
};

// The canonical header leaves the 500-entry scorch array at +0xE0 untyped.
static __forceinline TerrainScorchEntry *terrainScorches(BaseHeightMapRenderObjClass *self)
{
    return reinterpret_cast<TerrainScorchEntry *>(self->unknown00E0);
}

void BaseHeightMapRenderObjClass::rva00069C5F(Vector3 location, float radius)
{
    for (int i=0; i<m_numScorches; ++i)
    {
        TerrainScorchEntry &scorch=terrainScorches(this)[i];
        const Vector3 &position=scorch.position;
        float dx=location.X-position.X;
        float dy=location.Y-position.Y;
        float dz=location.Z-position.Z;
        float distance=scorchSqrt(dz*dz + dy*dy + dx*dx);
        if (scorch.radius+radius > distance) scorch.active=true;
    }
    m_scorchesInBuffer=0;
}
