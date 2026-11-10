// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// Retail 0x0009B28C..0x0009B510: primary light direction/color and shadow position.
// The same-this caller 0x0009CD9B supplies the manager's two angles at +0x44;
// the rowed setup 0x0009D862 calls that initializer on Rva0009D55BProduct.
// Retail proves light +0xC8, position +0x1A0, colors +0xD4/+0xE0/+0xEC,
// transform slot 21, manager color +0x60 and the shadow-setter call 0x0009A587.
// Vector arithmetic follows ZH WWMath vector3.h from pinned BFME 1 a7c38d3b25;
// the angles, layouts and call relationships are independently retail-derived.
// Keep the trig expressions float-valued without an extra cast of their result:
// that cast changes MSVC 7.1's x87 argument cleanup/normalization scheduling.
// Keep MSVC's float overloads local; the matched trig operations inline.
#define inline static inline
#include <math.h>
#undef inline
#include "../../../../Libraries/Include/Lib/Coord2D.h"

#include "../../../../Libraries/Source/WWVegas/WWMath/WWMathClass.h"

#include "../../../../Libraries/Source/WWVegas/WWMath/Vector3Data.h"

// Zero Hour's inline Vector3 negate and Normalize bodies and a scalar scale;
// retail inlines them here.
static __forceinline Vector3 bfmeNegateV3(const Vector3 &vec) { return Vector3(-vec.X, -vec.Y, -vec.Z); }
static __forceinline void bfmeNormalizeV3(Vector3 &vec)
{
    float length2 = vec.X*vec.X + vec.Y*vec.Y + vec.Z*vec.Z;
    if (length2 != 0.0f)
    {
        float reciprocal = WWMath::Inv_Sqrt(length2);
        vec.X *= reciprocal; vec.Y *= reciprocal; vec.Z *= reciprocal;
    }
}
static __forceinline void bfmeScaleV3(Vector3 &vec, float factor) { vec.X *= factor; vec.Y *= factor; vec.Z *= factor; }

#include "../../../../Libraries/Source/WWVegas/WWMath/Matrix3DData.h"

#define LIGHT_SLOTS4(p) virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3();
#define LIGHT_SLOTS16(p) LIGHT_SLOTS4(p##0) LIGHT_SLOTS4(p##1) LIGHT_SLOTS4(p##2) LIGHT_SLOTS4(p##3)
class Light9B28C
{
public:
    LIGHT_SLOTS16(s0) LIGHT_SLOTS4(s1) virtual void s20();
    virtual void Set_Transform(const Matrix3D &);
    char pad04[0xD4 - 4];
    Vector3 ambient, diffuse, specular;
};
#undef LIGHT_SLOTS16
#undef LIGHT_SLOTS4

class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;
struct Color9B28C { float X, Y, Z; };
struct Light9B28CManagerView { char pad[0x60]; Color9B28C color; };
class W3DShadowManager;
extern W3DShadowManager *TheW3DShadowManager;
class W3DGameClientShadowShim { public: void setLightPosition(int, float, float, float); };

// Layout view of the established factory-product owner; no new class identity.
class Rva0009D55BProduct
{
public:
    void rva0009B28C(const Coord2D *);
    char pad00[0xC8];
    Light9B28C *light;
    char padCC[0x1A0 - 0xCC];
    Vector3 position;
};

void Rva0009D55BProduct::rva0009B28C(const Coord2D *angles)
{
    if (light)
    {
        Color9B28C color = ((Light9B28CManagerView *)TheLivingWorldManager)->color;
        Vector3 direction;
        direction.X = sin((float)angles->x * .017453292f + 1.5707964f) * (float)cos(angles->y * .017453292f);
        direction.Y = sin((float)angles->x * .017453292f + 1.5707964f) * (float)sin(angles->y * .017453292f);
        direction.Z = cos((float)angles->x * .017453292f + 1.5707964f);
        position = bfmeNegateV3(direction);
        bfmeNormalizeV3(position);
        bfmeScaleV3(position, 10000.0f);
        light->ambient.Set(0.0f, 0.0f, 0.0f);
        light->specular.Set(0.0f, 0.0f, 0.0f);
        light->diffuse.Set(color.X, color.Y, color.Z);
        Matrix3D tm(true);
        tm.Row[0][0]=1.0f; tm.Row[0][1]=0.0f; tm.Row[0][2]=direction.X; tm.Row[0][3]=0.0f;
        tm.Row[1][0]=0.0f; tm.Row[1][1]=1.0f; tm.Row[1][2]=direction.Y; tm.Row[1][3]=0.0f;
        tm.Row[2][0]=0.0f; tm.Row[2][1]=0.0f; tm.Row[2][2]=direction.Z; tm.Row[2][3]=0.0f;
        light->Set_Transform(tm);
    }
    ((W3DGameClientShadowShim *)TheW3DShadowManager)->setLightPosition(0, position.X, position.Y, position.Z);
}
