// cl: /O1 /arch:SSE2 /ICode/GameEngine/Source/Common

#include <math.h>

class Debug
{
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual Debug &operator<<(const char *value);
    virtual Debug &operator<<(int value);
    virtual Debug &operator<<(unsigned int value);
    virtual Debug &operator<<(unsigned char value);
    virtual Debug &operator<<(short value);
    virtual Debug &operator<<(unsigned short value);
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual Debug &operator<<(float value);
};

struct Coord3DBase
{
    float x;
    float y;
    float z;
};

class Coord2D
{
public:
    float x;
    float y;
};

class Coord3D
{
public:
    Coord3D(int x, int y, int z);
    Coord3D &Add(const Coord2D &left, const Coord3DBase &right);
    Coord3D &Add(const Coord3DBase &left, const Coord2D &right);
    Coord3D &Add(const Coord3DBase &left, const Coord3DBase &right);
    Coord3D &Sub(const Coord2D &left, const Coord3DBase &right);
    Coord3D &Sub(const Coord3DBase &left, const Coord2D &right);
    Coord3D &Sub(const Coord3DBase &left, const Coord3DBase &right);
    Coord3D &Add2D(const Coord3DBase &left, const Coord3DBase &right);
    Coord3D &Sub2D(const Coord3DBase &left, const Coord3DBase &right);
    Coord3D &Scale(const Coord3DBase &that, float scale);
    Coord3D &Scale2D(const Coord3DBase &that, float scale);
    float GetLength() const;
    float GetLength2D() const;
    float GetLengthSqrd() const;
    float GetLengthSqrd2D() const;
    Coord3D &Negate();
    float Normalize();
    float Normalize2D();
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

    float x;
    float y;
    float z;
};

static const float one = 1.0f;

Coord3D::Coord3D(int x, int y, int z)
{
    this->x = (float)x;
    this->y = (float)y;
    this->z = (float)z;
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

Coord3D &Coord3D::Scale(const Coord3DBase &that, float scale)
{
    x = that.x * scale;
    y = that.y * scale;
    z = that.z * scale;
    return *this;
}

Coord3D &Coord3D::Scale2D(const Coord3DBase &that, float scale)
{
    x = that.x * scale;
    y = that.y * scale;
    return *this;
}

float Coord3D::GetLength() const
{
    float x_value = x;
    float y_value = y;
    float z_value = z;

    return (float)sqrt(x_value * x_value + y_value * y_value + z_value * z_value);
}

float Coord3D::GetLength2D() const
{
    float x_value = x;
    float y_value = y;

    return (float)sqrt(x_value * x_value + y_value * y_value);
}

float Coord3D::GetLengthSqrd() const
{
    float x_value = x;
    float y_value = y;
    float z_value = z;

    return x_value * x_value + y_value * y_value + z_value * z_value;
}

float Coord3D::GetLengthSqrd2D() const
{
    float x_value = x;
    float y_value = y;

    return x_value * x_value + y_value * y_value;
}

Coord3D &Coord3D::Negate()
{
    x = -x;
    y = -y;
    z = -z;
    return *this;
}

float Coord3D::Normalize()
{
    float len = GetLength();
    float scale = one / len;
    x *= scale;
    y *= scale;
    z *= scale;
    return len;
}

float Coord3D::Normalize2D()
{
    float len = GetLength2D();
    float scale = one / len;
    x *= scale;
    y *= scale;
    return len;
}

float Coord3D::operator*(const Coord3DBase &that) const
{
    return x * that.x + y * that.y + z * that.z;
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

void Coord3D::set(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Coord3D::sub(const Coord3DBase *that)
{
    x -= that->x;
    y -= that->y;
    z -= that->z;
}

Debug &operator<<(Debug &debug, const Coord3D &coord)
{
    debug << "(" << coord.x << ", " << coord.y << ", " << coord.z << ")";
    return debug;
}
