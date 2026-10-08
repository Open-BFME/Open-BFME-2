// cl: /O1 /arch:SSE2 /MD /EHsc
// BFME 1 semantic donor: RayEffect.cpp at ba7ddda7e8, RayEffectSystem::init.
// Target identity: W3DGameClient::createRayEffectByTemplate at 0x0004C7F0
// calls addRayEffect at 0x002CED84; that body and findEntry at 0x002CED59
// access 128 records of 28 bytes at +0x0C. The constructor at 0x002CEE96
// calls this helper after constructing that same array.
// Target vtable RVA 0x00802244 slot 1 also points to this 51-byte helper.
// The eight bytes after the vptr belong to the 12-byte subsystem prefix;
// their member identities are not needed by this recovery.
#include "../../../../Libraries/Include/Lib/Coord3D.h"

class Drawable;

class SubsystemInterface
{
public:
    SubsystemInterface();
    virtual ~SubsystemInterface();

private:
    char m_baseFields[8];
};

struct RayEffectData
{
    // ??0RayEffectData@@QAE@XZ present-unmatched
    __declspec(noinline) RayEffectData() {}
    // ??1RayEffectData@@QAE@XZ present-unmatched
    __declspec(noinline) ~RayEffectData() {}

    const Drawable *draw;
    Coord3D startLoc;
    Coord3D endLoc;
};

class RayEffectSystem : public SubsystemInterface
{
public:
    RayEffectSystem();
    virtual ~RayEffectSystem();
    virtual __declspec(noinline) void init();

private:
    RayEffectData m_effectData[128];
};

static inline void clearCoordinates(Coord3D *loc)
{
    loc->x = 0.0f;
    loc->y = 0.0f;
    loc->z = 0.0f;
}

// BFME 1 donor RayEffectSystemConstructor.cpp uses the same empty record
// callbacks. Target 0x002CEE96 constructs the array at +0x0C and calls init
// rather than inlining it; init's visible body proves it cannot throw.
RayEffectSystem::RayEffectSystem()
{
    init();
}

void RayEffectSystem::init()
{
    for (int i = 0; i < 128; ++i)
    {
        m_effectData[i].draw = 0;
        clearCoordinates(&m_effectData[i].startLoc);
        clearCoordinates(&m_effectData[i].endLoc);
    }
}
