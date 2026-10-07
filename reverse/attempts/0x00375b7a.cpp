// ?rva00375B7A@AerialPathfinder@@QAEMMM@Z
// partial score=0.97 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /Oy- /DNDEBUG /MD
// Native 00375B7A..00375BFF: framed member, RET 8, ST0 result. It takes
// terrain height, raises it to the no-fly-zone query result, then applies
// the AI-data float at +B0 unless that float is FLT_MAX. Field meaning and
// this method's original name remain unknown. The AerialPathfinder owner
// is inferred from its same-receiver 00375AF7 call and BFME1's named
// AerialPathfinder_getNoFlyZoneHeight.cpp at ba7ddda7e8.
#include <float.h>

class TerrainLogic
{
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual float getGroundHeight(float x, float y, void *normal);
};
extern TerrainLogic *TheTerrainLogic;

class AI;
extern AI *TheAI;
struct AerialAIDataView
{
    unsigned char prefixB0[0xB0];
    float floor;
};
struct AerialAIView
{
    unsigned char prefix18[0x18];
    AerialAIDataView *data;
};

class AerialPathfinder
{
public:
    float getNoFlyZoneHeight(float x, float y);
    float rva00375B7A(float x, float y);
};

// ?rva00375B7A@AerialPathfinder@@QAEMMM@Z
float AerialPathfinder::rva00375B7A(float x, float y)
{
    float height = TheTerrainLogic->getGroundHeight(x, y, 0);
    float noFlyHeight = getNoFlyZoneHeight(x, y);
    if (noFlyHeight > height)
        height = noFlyHeight;
    float floor = reinterpret_cast<AerialAIView *>(TheAI)->data->floor;
    if (floor != FLT_MAX && floor > height)
        height = floor;
    return height;
}
