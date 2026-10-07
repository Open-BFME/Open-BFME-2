// cl: /O1 /arch:SSE /G7 /MD /Oy-
// Ghidra FUN_00775b7a, RVA 0x00375B7A, 133 bytes. The preceding
// polygon-list query returns ST(0) and pops the two float arguments.
// Only the accessed prefixes are represented; the owner's name is unknown.

struct Coord3D;
class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;

class Rva00375B7ATerrainDispatch
{
public:
    virtual void slot0() = 0;
    virtual void slot1() = 0;
    virtual void slot2() = 0;
    virtual void slot3() = 0;
    virtual void slot4() = 0;
    virtual void slot5() = 0;
    virtual float getGroundHeight(float x, float y, Coord3D *normal) const = 0;
};

class AI;
extern AI *TheAI;
struct Rva00375B7AData
{
    char unknown[0xB0];
    float lowerBound;
};
struct Rva00375B7AAIView
{
    char unknown[0x18];
    Rva00375B7AData *data;
};

class Rva00375AF7
{
public:
    float rva00375AF7(float x, float y);
    float rva00375B7A(float x, float y);
};

// ?rva00375B7A@Rva00375AF7@@QAEMMM@Z
float Rva00375AF7::rva00375B7A(float x, float y)
{
    float height = reinterpret_cast<Rva00375B7ATerrainDispatch *>(TheTerrainLogic)
        ->getGroundHeight(x, y, 0);
    // Retail rounds the x87 result to a float and reloads it for comparison.
    volatile float polygonHeight = rva00375AF7(x, y);
    if (polygonHeight > height)
        height = polygonHeight;
    float lowerBound = reinterpret_cast<Rva00375B7AAIView *>(TheAI)->data->lowerBound;
    if (lowerBound != 3.402823466e+38f && lowerBound > height)
        height = lowerBound;
    return height;
}
