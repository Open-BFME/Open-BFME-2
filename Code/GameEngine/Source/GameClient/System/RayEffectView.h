// TU-local view shared by the rowed ray-effect helpers and constructor/init.
// Existing retail evidence: 128 records of 28 bytes after the 12-byte subsystem.
#ifndef BFME_RAY_EFFECT_VIEW_H
#define BFME_RAY_EFFECT_VIEW_H

#include <stddef.h>
#include "../../../../Libraries/Include/Lib/Coord3D.h"

class Drawable;

#include "../../../../Libraries/Source/subsystem/SubsystemInterface.h"

struct RayEffectData
{
    __declspec(noinline) RayEffectData() {}
    __declspec(noinline) ~RayEffectData() {}

    const Drawable *draw;
    Coord3D startLoc;
    Coord3D endLoc;
};

class RayEffectSystem : public SubsystemInterface
{
public:
    RayEffectSystem();
    void addRayEffect(const Drawable *draw, const Coord3D *startLoc, const Coord3D *endLoc);
    void deleteRayEffect(const Drawable *draw);
    void getRayEffectData(const Drawable *draw, RayEffectData *effectData);
    // Compiler-generated destruction (members, then the rowed base dtor), the
    // body retail's vtable slot 0 reaches.
    virtual ~RayEffectSystem() {}
    virtual __declspec(noinline) void init();

private:
    RayEffectData m_effectData[128];
};

#endif
