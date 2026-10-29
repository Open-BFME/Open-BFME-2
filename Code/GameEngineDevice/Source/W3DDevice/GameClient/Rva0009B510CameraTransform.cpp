// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// ?buildCameraTransform@Rva0009C134Host@@QAEXAAVMatrix3D@@MM@Z retail 0x0009B510..0x0009B7EA
// (730 bytes, ret 0xC): the camera transform builder the rowed refresh
// 0x0009BAA4 calls on the factory product (pinned there under the
// Rva0009C134Host view). Target facts from retail: an eye offset
// (0, -sin(pitch) * distance, cos(pitch) * distance) whose Y becomes -0.5
// when zero; the +0x110 look-at point lerped from +0xF8 towards +0x104 by
// the rowed ease 0x0009AAA8 of the +0x134 zoom, then its X/Y towards the
// base's +0x1C/+0x20 by the +0x198 fade; with a +0x188 object, a translation
// matrix (0x00BC8978, 0x00BC8974, 2 * distance * ease) handed to its slot 21;
// a yaw eased from +0x11C towards 0 (and on by the fade) rotating the offset
// about Z; an identity transform and the rowed Matrix3D::Look_At 0x00712150
// with roll 0. Member meanings and the class name remain unresolved.
// Static Vector3::Add keeps the original operand relationship across the member
// interpolation; the vector and matrix come from the real WWMath headers (BFME1
// vector3.h / matrix3d.h), whose inlines give retail's x87 pop placement that the
// earlier private Vector3/Matrix3D views could not (reverse/attempt_support/
// 0x0009b510-20261019.md). Sibling 0x9B7EA uses the same headers and flags.
// The sin/cos float overloads inline here; dllimport keeps <math.h> from
// emitting their out-of-line copies, which differ from retail's fsin/fcos
// ones (0x2FBB0/0x2FBC0). Same wrap as wwmath.cpp.
#pragma push_macro("inline")
#define inline __declspec(dllimport) __forceinline
#include <math.h>
#pragma pop_macro("inline")

#include "matrix3d.h"
#define B510_SLOTS4(p) virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3();
#define B510_SLOTS16(p) B510_SLOTS4(p##0) B510_SLOTS4(p##1) B510_SLOTS4(p##2) B510_SLOTS4(p##3)
class Rva0009B510Object
{
public:
    B510_SLOTS16(s0) B510_SLOTS4(s1) virtual void s20();
    virtual void Set_Transform(const Matrix3D &m);	// slot 21
};
#undef B510_SLOTS16
#undef B510_SLOTS4

float __cdecl Rva0009AAA8Get(float x);

static inline float Rva0009B510Lerp(float startValue, float endValue, float fraction) { return (endValue - startValue) * fraction + startValue; }

// Layout view of the established factory product (see Rva0009D55BProductCtor.cpp).
class Rva0009C134Host
{
public:
    void buildCameraTransform(Matrix3D &tm, float distance, float pitch);

    char m_pad00[0x1C];
    float m_1C;
    float m_20;
    char m_pad24[0xF8 - 0x24];
    Vector3 m_F8;
    Vector3 m_104;
    Vector3 m_110;
    float m_11C;
    char m_pad120[0x134 - 0x120];
    float m_134;
    char m_pad138[0x188 - 0x138];
    Rva0009B510Object *m_188;
    char m_pad18C[0x198 - 0x18C];
    float m_198;
};

void Rva0009C134Host::buildCameraTransform(Matrix3D &tm, float distance, float pitch)
{
    float sinPitch = sin(pitch);
    float cosPitch = cos(pitch);
    Vector3 offset(0.0f, 0.0f - sinPitch * distance, cosPitch * distance);
    if (offset.Y == 0.0f)
        offset.Y = -0.5f;
    float ease = Rva0009AAA8Get(m_134);
    Vector3::Lerp(m_F8, m_104, ease, &m_110);
    m_110.X = Rva0009B510Lerp(m_110.X, m_1C, m_198);
    m_110.Y = Rva0009B510Lerp(m_110.Y, m_20, m_198);
    Vector3::Add(m_110, offset, &offset);
    if (m_188)
    {
        Matrix3D translate(true);
        translate.Set_Translation(Vector3(192.43f, 569.88f, (2.0f * distance) * ease));
        m_188->Set_Transform(translate);
    }
    offset -= m_110;
    float yaw = Rva0009B510Lerp(Rva0009B510Lerp(m_11C, 0.0f, ease), 0.0f, m_198);
    offset.Rotate_Z(sin(yaw), cos(yaw)); offset += m_110; tm.Make_Identity(); tm.Look_At(offset, m_110, 0.0f);
}
