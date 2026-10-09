// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// W3DTreeBuffer method at retail 0x000EA327 (358 bytes, ret 0x14): moves the tree record of a drawable key to a new
// position and transform and rebuilds its bounding sphere from the type. Open-BFME-1 twin:
// W3DTreeBufferRva00733000.cpp (0x00733000). BFME2 layout read from retail: 1200 records of 0xE8 at +0x5C0
// (count +0x44540, changed byte +0x44544), 64 types of 0x5C at +0x44558. Opaque identity.
#include "matrix3d.h"
#include "sphere.h"

typedef int Int;
typedef float Real;

struct Rva000EA327Record
{
    Vector3 position;
    Real scale;
    Matrix3D transform;
    Int type;
    unsigned char reserved44[4];
    SphereClass bounds;
    void *key;
    unsigned char reserved5c[0x8c];
};

struct Rva000EA327Type
{
    unsigned char reserved00[0x10];
    SphereClass bounds;
    unsigned char reserved20[0x3c];
};

class W3DTreeBuffer
{
public:
    char rva000EA327(void *key, Vector3 position, const Matrix3D *transform);

private:
    unsigned char reserved000[0x5c0];
    Rva000EA327Record records[1200];
    Int count;
    unsigned char changed;
    unsigned char reserved44541[0x44558 - 0x44545];
    Rva000EA327Type types[64];
};

char W3DTreeBuffer::rva000EA327(void *key, Vector3 position,
    const Matrix3D *transform)
{
    for (Int index = 0; index < count; ++index)
    {
        if (records[index].key == key)
        {
            records[index].position = position;
            records[index].transform = *transform;

            Rva000EA327Type *type = types + records[index].type;
            records[index].bounds = type->bounds;
            Real scale = records[index].scale;
            records[index].bounds.Center *= scale;
            records[index].bounds.Radius *= records[index].scale;
            records[index].bounds.Center += records[index].position;

            changed = 1;
            return 1;
        }
    }
    return 0;
}
