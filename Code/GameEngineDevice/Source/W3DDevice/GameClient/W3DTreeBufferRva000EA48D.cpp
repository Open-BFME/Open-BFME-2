// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// W3DTreeBuffer method at retail 0x000EA48D (439 bytes, ret 0xC): finds the tree record of a drawable key and
// starts a topple in the given direction at the given height. Open-BFME-1 twin:
// W3DTreeBufferRva007331F0.cpp (0x007331F0). BFME2 layout read from retail: 1200 records of 0xE8 at +0x5C0
// (count +0x44540, changed byte +0x44545), 64 types of 0x5C at +0x44558 with the type data at +0x20, terrain
// height override at TheTerrainLogic+0x1918; the effect is played without the BFME1 block test.
#include "matrix3d.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"

typedef bool Bool;
typedef int Int;
typedef float Real;

class FXList
{
public:
    static void doFXPos(const FXList *list, const Coord3D *position, const Matrix3D *transform,
        Real speed, const Coord3D *direction);
};

class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;

struct Rva000EA48DTypeData
{
    unsigned char pad00[0x20];
    FXList *fx;
    unsigned char pad24[8];
    Real factor2c;
    Real factor30;
    unsigned char pad34[4];
    Real defaultHeight;
    unsigned char pad3c[0x20];
};

struct Rva000EA48DType
{
    unsigned char pad00[0x20];
    Rva000EA48DTypeData *data;
    unsigned char pad24[0x38];
};

struct Rva000EA48DRecord
{
    Vector3 location;
    unsigned char pad0c[0x34];
    Int type;
    unsigned char pad44[0x14];
    void *key;
    unsigned char pad5c[0x10];
    Real height6c;
    Real height70;
    Coord3D direction;
    Int guard80;
    Real field84;
    Int field88;
    Int field8c;
    Matrix3D matrix;
    unsigned char padc0[8];
    void *guardc8;
    unsigned char padcc[0x1c];
};

class W3DTreeBuffer
{
public:
    Bool rva000EA48D(void *key, const Coord3D *direction, Real height);

    __forceinline Rva000EA48DRecord *find(void *key)
    {
        for (Int i = 0; i < count; ++i)
        {
            if (records[i].key == key)
                return records + i;
        }
        return 0;
    }

private:
    unsigned char pad000[0x5c0];
    Rva000EA48DRecord records[1200];
    Int count;
    unsigned char pad44544[1];
    unsigned char changed;
    unsigned char pad44546[0x44558 - 0x44546];
    Rva000EA48DType types[64];
};

Bool W3DTreeBuffer::rva000EA48D(void *key, const Coord3D *direction, Real height)
{
    if (!key)
        return false;

    Rva000EA48DRecord *record = 0;
    for (Int i = 0; i < count; ++i)
    {
        if (records[i].key == key)
        {
            record = records + i;
            break;
        }
    }
    if (!record)
        return false;
    if (record->guard80)
        return false;
    if (record->guardc8)
        return false;

    const Rva000EA48DTypeData *typeData = types[record->type].data;
    Real terrainHeight = *(Real *)((unsigned char *)TheTerrainLogic + 0x1918);
    if (terrainHeight > 0.0f)
        height = terrainHeight;
    else if (height < typeData->defaultHeight)
        height = typeData->defaultHeight;

    record->direction = *direction;
    record->direction.normalize();
    record->field84 = 0.0f;
    record->height6c = height * typeData->factor2c;
    record->height70 = height * typeData->factor30;
    record->guard80 = 1;
    record->field8c = 0;

    Coord3D position;
    position.x = record->location.X;
    position.y = record->location.Y;
    position.z = record->location.Z;
    FXList::doFXPos(typeData->fx, &position, 0, 0.0f, 0);

    changed = 1;
    record->matrix.Make_Identity();
    record->matrix.Set_Translation(record->location);
    return true;
}
