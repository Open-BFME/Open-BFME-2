// cl:  /O1 /G7 /arch:SSE /DNDEBUG /MD
// Native 0x00265514..0x00265596 (130B), RET8.
// WB 0x00BB5F00 establishes a user-constructed Coord3D return and a common
// zero/scale then return. This unnamed method keeps its neutral name.
// Native Object radius +0xB8 and planar worker 0x2654FC
// establish these access views independently of donor layouts.
// WB zero/scale/common-return order and the shared user-written constructors
// preserve the return buffer's scalar stores and native SIMD allocation.
#define COORD3D_VIEW_INLINE
#include "../../../../Libraries/Include/Lib/Coord3DCtorView.h"

class Object {
public:
    // Existing provider ABI views of their hidden/result buffers.
    Coord3D *getPlanarDirectionTo(Coord3D *, const Object *) const;
    void Get2DCenterVectorTo(Coord3D *, const Coord3D *) const;
    Coord3D rva00265514(const Object *) const;
    Coord3D Get2DBorderVectorTo(const Coord3D *) const;
private:
    char m_pad000[0xB8];
    float m_radius;
};

// ?rva00265514@Object@@QBE?AUCoord3D@@PBV1@@Z
Coord3D Object::rva00265514(const Object *that) const {
    Coord3D direction;
    getPlanarDirectionTo(&direction, that);
    float distance = direction.length();
    float radiusSum = that->m_radius + m_radius;
    if (radiusSum >= distance)
        direction.zero();
    else
        direction.scaleInlined((distance - radiusSum) / distance);
    return direction;
}


// Native 0x002C986B..0x002C98E2 (119B); WB 0x00BB6180 names the method.
// ?Get2DBorderVectorTo@Object@@QBE?AUCoord3D@@PBU2@@Z
Coord3D Object::Get2DBorderVectorTo(const Coord3D *position) const {
    Coord3D direction;
    Get2DCenterVectorTo(&direction, position);
    float distance = direction.length();
    float radius = m_radius;
    if (radius >= distance)
        direction.zero();
    else
        direction.scaleInlined((distance - radius) / distance);
    return direction;
}
