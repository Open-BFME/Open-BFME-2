// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// W3DShrubBuffer method at retail 0x000E7140 (371 bytes, ret 0x14): moves the shrub record of a drawable key to a new
// position and transform and rebuilds its bounding sphere from the type. Open-BFME-1 twin:
// W3DShrubBufferRva00733000.cpp (0x00733000). BFME2 layout read from retail: 2000 records of 0xA0 at +0x1958
// (count +0x4FB58, changed byte +0x4FB5C), 64 types of 0x5C at +0x4FB70. Opaque identity.
#include "matrix3d.h"
#include "sphere.h"

typedef int Int;
typedef float Real;

struct Rva000E7140Record
{
    Vector3 position;
    Real scale;
    Matrix3D transform;
    Int type;
    unsigned char reserved44[4];
    SphereClass bounds;
    void *key;
    unsigned char reserved5c[0x44];
};

struct Rva000E7140Type
{
    unsigned char reserved00[0x10];
    SphereClass bounds;
    unsigned char reserved20[0x3c];
};

class W3DShrubBuffer
{
public:
    char rva000E7140(void *key, Vector3 position, const Matrix3D *transform);

private:
    unsigned char reserved000[0x1958];
    Rva000E7140Record records[2000];
    Int count;
    unsigned char changed;
    unsigned char reserved4fb5d[0x4fb70 - 0x4fb5d];
    Rva000E7140Type types[64];
};

char W3DShrubBuffer::rva000E7140(void *key, Vector3 position,
    const Matrix3D *transform)
{
    for (Int index = 0; index < count; ++index)
    {
        if (records[index].key == key)
        {
            records[index].position = position;
            records[index].transform = *transform;

            Rva000E7140Type *type = types + records[index].type;
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
