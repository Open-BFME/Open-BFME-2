// cl: /O1 /G7 /arch:SSE /Oy- /MD /DNDEBUG /D_STLP_USE_STATIC_LIB
// stlport
// ?rva00311B70@Rva00311DD9@@QAEXXZ, retail 0x00311B70 (617 B), ends where draw 0x00311DD9 begins.
// Spline end-point extension (WB twin 0xEB38C0): the first and last control points of the
// 184-byte records at +0x2C are pushed outward along the end directions by the length of the
// neighbouring segment. WB-literal separate locals; canonical Coord3D with set/scale and the
// coord3d.cpp length/normalize bodies visible inline (/O1 still calls 0x3571/0x35B6), plus a
// by-reference subtract like WB MathCoord3D.h Coord3D::Sub. Kept apart from the draw unit so its
// non-retail inline helper COMDAT copies do not cost that unit its link. Address-derived name.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
// math.h's float sqrt/sqrtf overloads take wwmath.cpp's dllimport forceinline form, so the
// visible length body below calls _sqrt as retail's 0x00003571 does and no _sqrtf copy is
// emitted.
#pragma push_macro("inline")
#define inline __declspec(dllimport) __forceinline
#include <math.h>
#pragma pop_macro("inline")
#include "../../../../Libraries/Include/Lib/Coord3DBase.h"
struct SplineRecord {float duration;float steps[10];Coord3D samples[10];Coord3D point;unsigned tail[2];};
struct SplineState {char pad[0x18];float time,segmentBegin;unsigned segment;bool enabled;char pad25[7];_STL::vector<SplineRecord> records;unsigned pad38;float sampleBegin;int sample;unsigned pad44;Coord3D result;};
class View;extern View *TheTacticalView;
#include "../../../Include/Common/Rva0022B3F6Subsystem.h"
extern Rva0022B3F6Subsystem *TheSplineService;
class TerrainLogic;extern TerrainLogic *TheTerrainLogic;
float Rva000930C0(float,float);
class Rva00311DD9:public SplineState {public:void rva00311B70();void draw(float);};

// Out-of-line rowed owners (coord3d.cpp 0x00003571/0x000035B6); visible here as
// the inline header bodies, which /O1 keeps as calls.
inline float Coord3D::length() const
{
    return (float)sqrt(x * x + y * y + z * z);
}

inline void Coord3D::normalize()
{
    float len = length();
    if (len != 0.0f) {
        float scale = 1.0f / len;
        x *= scale;
        y *= scale;
        z *= scale;
    }
}

// Coord3D::set and ::scale as TU-local helpers: as /Oy- inline members this unit emitted framed
// copies of them against retail's frameless 0x000DFCB6 and 0x000036D1.
static inline void set(Coord3D &that, const Coord3DBase *other)
{
    that.x = other->x;
    that.y = other->y;
    that.z = other->z;
}

static inline void scale(Coord3D &that, float s)
{
    that.x *= s;
    that.y *= s;
    that.z *= s;
}

// Coord3D::Sub(const Coord3DBase &) of the BFME 2 math header, which the canonical Coord3D lacks.
// ?subtract absent-from-retail
inline Coord3D &subtract(Coord3D &that, const Coord3D &other)
{
    that.x -= other.x;
    that.y -= other.y;
    that.z -= other.z;
    return that;
}

// Extends the curve's end segments: the first and last control points are
// pushed out along the end directions by the length of the neighbouring segment.
void Rva00311DD9::rva00311B70()
{
    Coord3D point;
    set(point, &asBase(records[1].point));
    Coord3D second;
    set(second, &asBase(records[2].point));
    Coord3D delta;
    set(delta, &asBase(point));
    subtract(delta, second);
    float length = delta.length();
    Coord3D first;
    set(first, &asBase(records[0].point));
    delta = point;
    subtract(delta, first);
    delta.normalize();
    scale(delta, length);
    subtract(point, delta);
    records[0].point = point;

    int count = records.size();
    Coord3D endPoint;
    set(endPoint, &asBase(records[count - 2].point));
    Coord3D beforeLast;
    set(beforeLast, &asBase(records[count - 3].point));
    delta = endPoint;
    subtract(delta, beforeLast);
    float endLength = delta.length();
    Coord3D last;
    set(last, &asBase(records[count - 1].point));
    delta = endPoint;
    subtract(delta, last);
    delta.normalize();
    scale(delta, endLength);
    subtract(endPoint, delta);
    records[count - 1].point = endPoint;
}
