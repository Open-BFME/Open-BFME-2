// cl: /O1 /G7 /arch:SSE /MD /EHsc
#include "../../../../../Libraries/Include/Lib/Coord2D.h"

float __cdecl ACos(float);

// Existing rowed module-chain update, called on the two words at particle +94.
class Rva001FA795
{
public:
    void rva001FA795();
};

// Unnamed completion predicate: retail 1F4E2D..1F4E82, WB B0D730.
// Its whole-particle receiver, bool result and zero arguments are established
// by this caller and WB. The original method name remains unknown.
class Rva001F4E2D
{
public:
    bool rva001F4E2D();
};

// Declaration-only view; this unit creates no vtable. Retail and WB both call
// +24 with one float. The earlier slots are outside this body's evidence.
class ParticleAngleModuleView
{
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void setAngle(float angle);
};

namespace FXParticleSystem
{
// Identity: WB B0D4B0 explicitly names FXParticleSystem::CPUParticle::update
// and asserts m_lifetimeLeft at FXParticleSystem.cpp:918. Target 1FA971..1FAA8D
// establishes the consumed prefix below, including position/previous-position
// pairs and module fields. Unused bytes and original member names stay unknown.
class CPUParticle
{
public:
    bool update();

private:
    char unknown00[0x1C];
    float x, y, z;
    float previousX, previousY, previousZ;
    char unknown34[4];
    bool orientWithMovement;
    char unknown39[0x1B];
    unsigned lifetimeLeft;
    char unknown58[0x3C];
    void *modules[2];
    ParticleAngleModuleView *angleModule;
};

bool CPUParticle::update()
{
    reinterpret_cast<Rva001FA795 *>(&modules)->rva001FA795();
    if (orientWithMovement && angleModule)
    {
        Coord2D direction;
        direction.x = x - previousX;
        direction.y = y - previousY;
        if (direction.y < 1.1920929e-7f && direction.y > -1.1920929e-7f)
        {
            angleModule->setAngle(direction.x > 0.0f ? 6.2831855f : 3.1415927f);
        }
        else
        {
            float length = direction.length();
            if (length < 1.1920929e-7f)
            {
                angleModule->setAngle(3.1415927f);
            }
            else
            {
                float angle = ACos(direction.y / length);
                angleModule->setAngle(direction.x > 0.0f
                    ? angle + 3.1415927f : 3.1415927f - angle);
            }
        }
    }
    if (lifetimeLeft && --lifetimeLeft == 0)
        return false;
    return !reinterpret_cast<Rva001F4E2D *>(this)->rva001F4E2D();
}
}
