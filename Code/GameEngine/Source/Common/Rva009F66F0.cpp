// cl: /O2 /Ob1 /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/GameEngine/Include/Precompiled /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// Provenance: Open-BFME-1 game/GameEngine/Source/Common/Rva009F66F0.cpp at 5cae4bdf (BFME1 byte-identical donor, b1 0x009F66F0); include paths repointed at the reference checkout for coord.h.
// Retail 009F66F0..009F67EC. INT3 before entry. Three cdecl arguments;
// the data xref at VA012DBD70 points to this entry. The following function
// starts at 009F67ED with an independent SEH prologue.
// Keep MSVC's float math overloads local; the matched sqrt operation inlines.
#pragma push_macro("inline")
#define inline static inline
#include <math.h>
#pragma pop_macro("inline")
#include <float.h>
#include "coord.h"

#include "../../../../reference/open-bfme-1/game/GameEngine/Include/Common/Enums/GeometryType.h"
struct Rva009F66F0Shape {
    int type;
    float height, majorRadius;
    char rest[0x18];
};
class GeometryInfo {
public:
    GeometryInfo(GeometryType, bool, float, float, float);
    virtual ~GeometryInfo();
    bool CollidesWith(const Coord3D &, float, const GeometryInfo &,
        const Coord3D &, float) const;
    void recompute() { calcBoundingStuff(); }
    char pad04[0x28];
    Rva009F66F0Shape *first, *last, *limit;
    char pad38[0x24];
private:
    void calcBoundingStuff();
};
class Rva009F66F0Provider {
public:
    virtual const GeometryInfo *geometry();
    virtual const Coord3D *position();
    virtual float angle();
};

float Rva009F66F0(const Coord3D *position, Rva009F66F0Provider *provider, float radiusSquared)
{
    static GeometryInfo geometry(GEOMETRY_SPHERE, true, 2.0f, 2.0f, 2.0f);
    if (geometry.last - geometry.first != 0)
        geometry.first->majorRadius = (float)sqrt(radiusSquared);
    geometry.recompute();
    const GeometryInfo *target = provider->geometry();
    if (target->CollidesWith(*provider->position(), provider->angle(),
        geometry, *position, 0.0f))
        return 0.0f;
    return FLT_MAX;
}
