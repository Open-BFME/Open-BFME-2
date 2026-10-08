// ?followToNextPointNow@GiantBirdFollowPathState@@QAE_NXZ
// partial score=0.93 date=2026-10-08
// cl: /O1 /arch:SSE /G7 /Oy- /DNDEBUG /MD /ICode/Libraries/Include/Lib
// WB f334d0 names followToNextPointNow; retail 368662..368793 supplies
// its boundaries, offsets and calls. The path's twelve-byte point accessor
// and movement helper have independently verified address-derived names.
// WB carries the giant bird purpose; the partial storage views below claim
// only the target accesses, not the complete Object or AIUpdate layouts.
#include "Coord3D.h"

class Rva00346FA5 {
public:
    void *rva00346FA5(int index) const;
};
class Rva00368C7A {
public:
    void rva003681F2(const Coord3D *, const unsigned char *, int, int);
    char unknown00[0x30];
    Rva00346FA5 *path;
    char unknown34[0x1f0 - 0x34];
    void *locomotor;
    char unknown1F4[0x4b8 - 0x1f4];
    unsigned int movementFlags;
    char unknown4BC[0x540 - 0x4bc];
    float flightHeight;
    char unknown544[0x550 - 0x544];
    bool loopPath;
};
struct GiantBirdFollowObject {
    char unknown00[0x258];
    Rva00368C7A *update;
};
struct GiantBirdFollowOwner {
    char unknown00[0x14];
    GiantBirdFollowObject *object;
};
class TerrainLogic {
public:
    virtual void slot0(); virtual void slot1(); virtual void slot2();
    virtual void slot3(); virtual void slot4(); virtual void slot5();
    virtual float getGroundHeight(float, float, Coord3D *) const;
};
extern TerrainLogic *TheTerrainLogic;
extern unsigned char g_00E01EC0[4];

struct GiantBirdPosition : Coord3D {
    GiantBirdPosition(const Coord3D &point) {
        x = point.x;
        y = point.y;
        z = point.z;
    }
};

class GiantBirdFollowPathState {
public:
    bool followToNextPointNow();
private:
    char unknown00[0x18];
    GiantBirdFollowOwner *owner;
    char unknown1C[0x58 - 0x1c];
    int nextPoint;
};

// ?followToNextPointNow@GiantBirdFollowPathState@@QAE_NXZ present-unmatched
bool GiantBirdFollowPathState::followToNextPointNow()
{
    GiantBirdFollowObject *object = owner->object;
    if (!object)
        return false;
    Rva00368C7A *update = object->update;
    if (!update)
        return false;
    if (!update->locomotor)
        return false;
    const Coord3D *current = static_cast<const Coord3D *>(update->path->rva00346FA5(nextPoint++));
    if (!current) {
        if (!update->loopPath)
            return false;
        nextPoint = 0;
        current = static_cast<const Coord3D *>(update->path->rva00346FA5(nextPoint++));
        if (!current)
            return false;
    }
    Coord3D nextPosition;
    const Coord3D *next = static_cast<const Coord3D *>(update->path->rva00346FA5(nextPoint));
    if (next) {
        update->movementFlags |= 0x80;
        nextPosition = *next;
        float height = update->flightHeight;
        nextPosition.z = TheTerrainLogic->getGroundHeight(nextPosition.x, nextPosition.y, 0) + height;
        next = &nextPosition;
    } else {
        update->movementFlags &= ~0x80;
    }
    GiantBirdPosition position(*current);
    float height = update->flightHeight;
    position.z = TheTerrainLogic->getGroundHeight(position.x, position.y, 0) + height;
    update->rva003681F2(&position, g_00E01EC0, (int)next, next == 0);
    return true;
}
