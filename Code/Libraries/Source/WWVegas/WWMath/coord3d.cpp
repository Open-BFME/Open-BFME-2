// cl: /O1 /arch:SSE2 /ICode/GameEngine/Source/Common

#include <math.h>

#include "../../../../GameEngine/Source/Common/debug.h"

struct Coord3DBase
{
    Coord3DBase &operator=(const Coord3DBase &that);

    float x;
    float y;
    float z;
};

#include "Coord2DBase.h"

#include "../../../Include/Lib/Coord2D.h"

// The three floats live in a base, which is what splits the two assignments:
// from another Coord3D the compiler block-copies the base with three movsd,
// while from a bare Coord3DBase it copies field by field.
class Coord3D : public Coord3DBase
{
public:
    // The default constructor is what the free operator- below needs for its
    // named return value, and the copy constructor is what makes MSVC 7.1 apply
    // NRV to it at all: with the implicit trivial one the return value is built
    // in a stack temporary and blockcopied out, frame pointer and all.
    Coord3D();
    Coord3D(const Coord3D &that)
    {
        x = that.x;
        y = that.y;
        z = that.z;
    }
    Coord3D(const Coord2D &that);
    Coord3D(int x, int y, int z);
    static void crossProduct(const Coord3D *left, const Coord3D *right, Coord3D *result);
    Coord3D &Add(const Coord2D &left, const Coord3DBase &right);
    Coord3D &Add(const Coord3DBase &left, const Coord2D &right);
    Coord3D &Add(const Coord3DBase &left, const Coord3DBase &right);
    Coord3D &Sub(const Coord2D &left, const Coord3DBase &right);
    Coord3D &Sub(const Coord3DBase &left, const Coord2D &right);
    Coord3D &Sub(const Coord3DBase &left, const Coord3DBase &right);
    Coord3D &Add2D(const Coord3DBase &left, const Coord3DBase &right);
    Coord3D &Sub2D(const Coord3DBase &left, const Coord3DBase &right);
    Coord3D &Scale(float scale);
    Coord3D &Scale(const Coord3DBase &that, float scale);
    Coord3D &Scale2D(float scale);
    Coord3D &Scale2D(const Coord3DBase &that, float scale);
    float GetLength() const;
    float GetLength2D() const;
    float GetLengthEstimate2D() const;
    float GetLengthSqrd() const;
    float GetLengthSqrd2D() const;
    float length() const;
    Coord3D &Negate();
    void add(const Coord3DBase *that);
    void set(const Coord3DBase *that);
    float lengthSqr() const;
    void normalize();
    float Normalize();
    float Normalize2D();
    Coord3D &operator+=(const Coord2D &that);
    Coord3D &operator+=(const Coord3DBase &that);
    Coord3D &operator-=(const Coord2D &that);
    Coord3D &operator*=(float scale);
    Coord3D &operator/=(float divisor);
    bool operator==(const Coord3D &that) const;
    float operator*(const Coord2D &that) const;
    float operator*(const Coord3DBase &that) const;
    Coord3D &Set2D(float x, float y);
    Coord3D &SetMaxVect();
    Coord3D &SetMinVect();
    Coord3D &SetXAxis();
    Coord3D &SetYAxis();
    Coord3D &SetZAxis();
    Coord3D &SetZero();
    void set(float x, float y, float z);
    void sub(const Coord3DBase *that);
    void zero();

    ~Coord3D();

    Coord3D(const Coord3DBase &that);
    Coord3D(float x, float y, float z);
    Coord3D &operator=(const Coord3DBase &that);
    Coord3D &operator=(const Coord2DBase &that);
    Coord3D &operator=(const Coord2D &that);
    Coord3D &Set(float x, float y, float z);
    Coord3D &Add(const Coord2D &that);
    Coord3D &Add2D(const Coord3DBase &that);
    Coord3D &Add(const Coord3DBase &that);
    Coord3D &Sub(const Coord2D &that);
    Coord3D &Sub2D(const Coord3DBase &that);
    Coord3D &Sub(const Coord3DBase &that);
    Coord3D &operator-=(const Coord3DBase &that);
    bool IsExactlyEqualTo(const Coord3D &that) const;
};


static const float one = 1.0f;

// The 12-byte block copy folded with the integer-coordinate and random-variable
// assignments: three movsd rather than three field stores.
Coord3DBase &Coord3DBase::operator=(const Coord3DBase &that)
{
    struct Raw
    {
        unsigned int x;
        unsigned int y;
        unsigned int z;
    };

    *(Raw *)this = *(const Raw *)&that;
    return *this;
}

inline Coord3D::Coord3D()
{
}

inline Coord3D::~Coord3D()
{
}

Coord3D::Coord3D(const Coord3DBase &that)
{
    x = that.x;
    y = that.y;
    z = that.z;
}

Coord3D &Coord3D::operator=(const Coord3DBase &that)
{
    x = that.x;
    y = that.y;
    z = that.z;

    return *this;
}

inline Coord3D::Coord3D(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Coord3D &Coord3D::Set(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;

    return *this;
}

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline Coord3D &Coord3D::operator-=(const Coord3DBase &that)
{
    x -= that.x;
    y -= that.y;
    z -= that.z;

    return *this;
}

// ?bfmeAnchorCoord3DSubAssign absent-from-retail
Coord3D &bfmeAnchorCoord3DSubAssign(Coord3D *pos, const Coord3DBase &that)
{
	return *pos -= that;
}


Coord3D &Coord3D::Sub(const Coord3DBase &that)
{
    x -= that.x;
    y -= that.y;
    z -= that.z;

    return *this;
}

Coord3D::Coord3D(const Coord2D &that)
{
    x = that.x;
    y = that.y;
    z = 0.0f;
}

Coord3D::Coord3D(int x, int y, int z)
{
    this->x = (float)x;
    this->y = (float)y;
    this->z = (float)z;
}

void Coord3D::crossProduct(const Coord3D *left, const Coord3D *right, Coord3D *result)
{
    result->x = left->y * right->z - left->z * right->y;
    result->y = left->z * right->x - left->x * right->z;
    result->z = left->x * right->y - left->y * right->x;
}

Coord3D &Coord3D::Add(const Coord2D &left, const Coord3DBase &right)
{
    x = left.x + right.x;
    y = left.y + right.y;
    z = right.z;
    return *this;
}

Coord3D &Coord3D::Add(const Coord3DBase &left, const Coord2D &right)
{
    x = left.x + right.x;
    y = left.y + right.y;
    z = left.z;
    return *this;
}

Coord3D &Coord3D::Add(const Coord3DBase &left, const Coord3DBase &right)
{
    x = left.x + right.x;
    y = left.y + right.y;
    z = left.z + right.z;
    return *this;
}

Coord3D &Coord3D::Sub(const Coord2D &left, const Coord3DBase &right)
{
    x = left.x - right.x;
    y = left.y - right.y;
    z = -right.z;
    return *this;
}

Coord3D &Coord3D::Sub(const Coord3DBase &left, const Coord2D &right)
{
    x = left.x - right.x;
    y = left.y - right.y;
    z = left.z;
    return *this;
}

Coord3D &Coord3D::Sub(const Coord3DBase &left, const Coord3DBase &right)
{
    x = left.x - right.x;
    y = left.y - right.y;
    z = left.z - right.z;
    return *this;
}

Coord3D &Coord3D::Add2D(const Coord3DBase &left, const Coord3DBase &right)
{
    x = left.x + right.x;
    y = left.y + right.y;
    return *this;
}

Coord3D &Coord3D::Sub2D(const Coord3DBase &left, const Coord3DBase &right)
{
    x = left.x - right.x;
    y = left.y - right.y;
    return *this;
}

Coord3D &Coord3D::Scale(float scale)
{
    x *= scale;
    y *= scale;
    z *= scale;
    return *this;
}

Coord3D &Coord3D::Scale(const Coord3DBase &that, float scale)
{
    x = that.x * scale;
    y = that.y * scale;
    z = that.z * scale;
    return *this;
}

Coord3D &Coord3D::Scale2D(float scale)
{
    x *= scale;
    y *= scale;
    return *this;
}

Coord3D &Coord3D::Scale2D(const Coord3DBase &that, float scale)
{
    x = that.x * scale;
    y = that.y * scale;
    return *this;
}

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline float Coord3D::GetLength() const
{
    float x_value = x;
    float y_value = y;
    float z_value = z;

    return (float)sqrt(x_value * x_value + y_value * y_value + z_value * z_value);
}

// ?bfmeAnchorCoord3DGetLength absent-from-retail
float bfmeAnchorCoord3DGetLength(const Coord3D *pos)
{
	return pos->GetLength();
}


inline __declspec(noinline) float Coord3D::GetLength2D() const
{
    float x_value = x;
    float y_value = y;

    return (float)sqrt(x_value * x_value + y_value * y_value);
}

inline __declspec(noinline) float Coord3D::GetLengthEstimate2D() const
{
    if (fabs(x) > fabs(y)) {
        return (float)(fabs(x) + 0.25f * fabs(y));
    }
    return (float)(fabs(y) + 0.25f * fabs(x));
}

float Coord3D::GetLengthSqrd() const
{
    float x_value = x;
    float y_value = y;
    float z_value = z;

    return x_value * x_value + y_value * y_value + z_value * z_value;
}

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline float Coord3D::GetLengthSqrd2D() const
{
    float x_value = x;
    float y_value = y;

    return x_value * x_value + y_value * y_value;
}

// ?bfmeAnchorCoord3DGetLengthSqrd2D absent-from-retail
float bfmeAnchorCoord3DGetLengthSqrd2D(const Coord3D *pos)
{
	return pos->GetLengthSqrd2D();
}


inline float Coord3D::length() const
{
    return (float)sqrt(x * x + y * y + z * z);
}

// Takes its operand by value: retail reads all three floats straight off the
// argument slots at [esp+8], [esp+0x0C] and [esp+0x10] and writes the result
// through the hidden return pointer at [esp+4], with no copy in between.
Coord3D operator-(Coord3D that)
{
    Coord3D result;

    result.x = -that.x;
    result.y = -that.y;
    result.z = -that.z;

    return result;
}

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline void Coord3D::add(const Coord3DBase *that)
{
    x += that->x;
    y += that->y;
    z += that->z;
}

// ?bfmeAnchorCoord3DAdd absent-from-retail
void bfmeAnchorCoord3DAdd(Coord3D *pos, const Coord3DBase *that)
{
	pos->add(that);
}


inline float Coord3D::lengthSqr() const
{
    return (float)((double)x * x + (double)y * y + (double)z * z);
}

inline void Coord3D::set(const Coord3DBase *that)
{
    x = that->x;
    y = that->y;
    z = that->z;
}

Coord3D &Coord3D::Negate()
{
    x = -x;
    y = -y;
    z = -z;
    return *this;
}

inline void Coord3D::normalize()
{
    float len = length();
    if (len != 0.0f) {
        float scale = 1.0f / len;
        x *= scale;
        y *= scale;
        z *= scale;
    }
}

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline float Coord3D::Normalize()
{
    float len = GetLength();
    float scale = one / len;
    x *= scale;
    y *= scale;
    z *= scale;
    return len;
}

// ?bfmeAnchorCoord3DNormalize absent-from-retail
float bfmeAnchorCoord3DNormalize(Coord3D *pos)
{
	return pos->Normalize();
}


inline __declspec(noinline) float Coord3D::Normalize2D()
{
    float len = GetLength2D();
    float scale = one / len;
    x *= scale;
    y *= scale;
    return len;
}

Coord3D &Coord3D::operator+=(const Coord2D &that)
{
    x += that.x;
    y += that.y;
    return *this;
}

Coord3D &Coord3D::operator+=(const Coord3DBase &that)
{
    x += that.x;
    y += that.y;
    z += that.z;
    return *this;
}

Coord3D &Coord3D::operator*=(float scale)
{
    x *= scale;
    y *= scale;
    z *= scale;

    return *this;
}

// Divides once and multiplies three times: the reciprocal is taken up front,
// which is also why the first component is scheduled apart from the other two.
Coord3D &Coord3D::operator/=(float divisor)
{
    const float scale = 1.0f / divisor;

    x *= scale;
    y *= scale;
    z *= scale;

    return *this;
}

Coord3D &Coord3D::operator-=(const Coord2D &that)
{
    x -= that.x;
    y -= that.y;
    return *this;
}

bool Coord3D::operator==(const Coord3D &that) const
{
    return x == that.x && y == that.y && z == that.z;
}

float Coord3D::operator*(const Coord2D &that) const
{
    return x * that.x + y * that.y;
}

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline float Coord3D::operator*(const Coord3DBase &that) const
{
    return x * that.x + y * that.y + z * that.z;
}

// ?bfmeAnchorCoord3DDot absent-from-retail
float bfmeAnchorCoord3DDot(const Coord3D *pos, const Coord3DBase &that)
{
	return *pos * that;
}


Coord3D &Coord3D::Set2D(float x, float y)
{
    this->x = x;
    this->y = y;
    return *this;
}

Coord3D &Coord3D::SetMaxVect()
{
    z = 3.4028234663852886e38f;
    y = 3.4028234663852886e38f;
    x = 3.4028234663852886e38f;
    return *this;
}

Coord3D &Coord3D::SetMinVect()
{
    z = -3.4028234663852886e38f;
    y = -3.4028234663852886e38f;
    x = -3.4028234663852886e38f;
    return *this;
}

Coord3D &Coord3D::SetXAxis()
{
    x = 1.0f;
    y = 0.0f;
    z = 0.0f;
    return *this;
}

Coord3D &Coord3D::SetYAxis()
{
    x = 0.0f;
    y = 1.0f;
    z = 0.0f;
    return *this;
}

Coord3D &Coord3D::SetZAxis()
{
    x = 0.0f;
    y = 0.0f;
    z = 1.0f;
    return *this;
}

Coord3D &Coord3D::SetZero()
{
    z = 0.0f;
    y = 0.0f;
    x = 0.0f;
    return *this;
}

inline void Coord3D::set(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline void Coord3D::sub(const Coord3DBase *that)
{
    x -= that->x;
    y -= that->y;
    z -= that->z;
}

// ?bfmeAnchorCoord3DSub absent-from-retail
void bfmeAnchorCoord3DSub(Coord3D *pos, const Coord3DBase *that)
{
	pos->sub(that);
}


inline void Coord3D::zero()
{
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}

Debug &operator<<(Debug &debug, const Coord3D &coord)
{
    debug << "(" << coord.x << ", " << coord.y << ", " << coord.z << ")";
    return debug;
}

Coord3D &Coord3D::operator=(const Coord2DBase &that)
{
    x = that.x;
    y = that.y;
    z = 0.0f;

    return *this;
}

Coord3D &Coord3D::operator=(const Coord2D &that)
{
    x = that.x;
    y = that.y;
    z = 0.0f;

    return *this;
}

Coord3D &Coord3D::Add(const Coord2D &that)
{
    x += that.x;
    y += that.y;

    return *this;
}

Coord3D &Coord3D::Add2D(const Coord3DBase &that)
{
    x += that.x;
    y += that.y;

    return *this;
}

Coord3D &Coord3D::Sub(const Coord2D &that)
{
    x -= that.x;
    y -= that.y;

    return *this;
}

Coord3D &Coord3D::Sub2D(const Coord3DBase &that)
{
    x -= that.x;
    y -= that.y;

    return *this;
}

Coord3D &Coord3D::Add(const Coord3DBase &that)
{
    x += that.x;
    y += that.y;
    z += that.z;

    return *this;
}

bool Coord3D::IsExactlyEqualTo(const Coord3D &that) const
{
    return x == that.x && y == that.y && z == that.z;
}

// The retail-identical inline Coord3D::equals body is owned by
// FiringTrackerXfer.cpp; an exclusive copy here collided with that emitter.

// The generated assignment, which is the one that block-copies the base; the
// declared overloads above hide it, so a member pointer is what names it.
typedef Coord3D &(Coord3D::*Coord3DAssign)(const Coord3D &);

Coord3DAssign g_coord3dAssign = &Coord3D::operator=;

// These eleven are header inlines: the units that include Coord3D's header
// emit them as select-any copies, which plain definitions here collided with.
// The anchor keeps this unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeCoord3DInlineAnchor@@YAXPAVCoord3D@@@Z absent-from-retail
void _bfmeCoord3DInlineAnchor(Coord3D *c)
{
    c->Coord3D::Coord3D();
    c->Coord3D::Coord3D(0.0f, 0.0f, 0.0f);
    c->zero();
    c->set(c->length(), c->lengthSqr(), 0.0f);
    c->set((const Coord3DBase *)0);
    c->normalize();
    c->GetLength2D();
    c->GetLengthEstimate2D();
    c->Normalize2D();
    c->Coord3D::~Coord3D();
}
#pragma inline_depth()
