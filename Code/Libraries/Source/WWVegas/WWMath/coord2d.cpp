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

// The two floats live in a base: retail's constructors and assignments take
// ABUCoord2DBase, and the same seventeen-byte body serves Coord2DBase,
// Coord3DBase and Coord2D itself, because all three start with the same pair.
struct Coord2DBase
{
    float x;
    float y;
};

struct Coord3DBase
{
    float x;
    float y;
    float z;
};

class Coord2D : public Coord2DBase
{
public:
    Coord2D();
    ~Coord2D();

    Coord2D(const Coord2D &that);
    Coord2D(const Coord2DBase &that);
    Coord2D(const Coord3DBase &that);
    Coord2D(float x, float y);
    Coord2D(int x, int y);

    Coord2D &operator=(const Coord2D &that);
    Coord2D &operator=(const Coord2DBase &that);
    Coord2D &operator=(const Coord3DBase &that);

    Coord2D &Set(float x, float y);
    Coord2D &Add(const Coord2D &that);
    Coord2D &Add(const Coord3DBase &that);
    Coord2D &Sub(const Coord2D &that);
    Coord2D &Sub(const Coord3DBase &that);
    Coord2D &Scale(float scale);
    Coord2D &operator+=(const Coord2D &that);
    Coord2D &operator+=(const Coord3DBase &that);
    Coord2D &operator-=(const Coord2D &that);
    Coord2D &operator-=(const Coord3DBase &that);
    Coord2D &operator*=(float scale);
    float operator*(const Coord2D &that) const;
    float operator*(const Coord3DBase &that) const;
    bool IsExactlyEqualTo(const Coord2D &that) const;
    float length() const;
    void normalize();
    Coord2D &Negate();
    Coord2D &operator/=(float divisor);
    Coord2D &Rotate(float sine, float cosine);
    Coord2D &Rotate(Coord2D &coord, float sine, float cosine);
    Coord2D &SetMaxVect();
    Coord2D &SetMinVect();
    Coord2D &SetXAxis();
    Coord2D &SetYAxis();
    Coord2D &SetZero();

    float GetLength() const;
    float GetLengthSqrd() const;
    float Normalize();

    float GetLengthEstimate() const;
};

// Out of line, because an in-class body is implicitly inline and MSVC folds it
// into its callers instead of emitting the COMDAT.
Coord2D::Coord2D()
{
}

Coord2D::~Coord2D()
{
}

// Two loads and two stores of the base pair, whatever the argument is nominally
// declared as - which is why one body carries six names.
Coord2D::Coord2D(const Coord2D &that)
{
    x = that.x;
    y = that.y;
}

Coord2D::Coord2D(const Coord2DBase &that)
{
    x = that.x;
    y = that.y;
}

Coord2D::Coord2D(const Coord3DBase &that)
{
    x = that.x;
    y = that.y;
}

Coord2D &Coord2D::operator=(const Coord2D &that)
{
    x = that.x;
    y = that.y;

    return *this;
}

Coord2D &Coord2D::operator=(const Coord2DBase &that)
{
    x = that.x;
    y = that.y;

    return *this;
}

Coord2D &Coord2D::operator=(const Coord3DBase &that)
{
    x = that.x;
    y = that.y;

    return *this;
}

Coord2D::Coord2D(float x, float y)
{
    this->x = x;
    this->y = y;
}

Coord2D &Coord2D::Set(float x, float y)
{
    this->x = x;
    this->y = y;

    return *this;
}

Coord2D &Coord2D::Add(const Coord2D &that)
{
    x += that.x;
    y += that.y;

    return *this;
}

Coord2D &Coord2D::Add(const Coord3DBase &that)
{
    x += that.x;
    y += that.y;

    return *this;
}

Coord2D &Coord2D::operator+=(const Coord2D &that)
{
    x += that.x;
    y += that.y;

    return *this;
}

Coord2D &Coord2D::operator+=(const Coord3DBase &that)
{
    x += that.x;
    y += that.y;

    return *this;
}

Coord2D &Coord2D::Sub(const Coord2D &that)
{
    x -= that.x;
    y -= that.y;

    return *this;
}

Coord2D &Coord2D::Sub(const Coord3DBase &that)
{
    x -= that.x;
    y -= that.y;

    return *this;
}

Coord2D &Coord2D::operator-=(const Coord2D &that)
{
    x -= that.x;
    y -= that.y;

    return *this;
}

Coord2D &Coord2D::operator-=(const Coord3DBase &that)
{
    x -= that.x;
    y -= that.y;

    return *this;
}

Coord2D &Coord2D::Scale(float scale)
{
    x *= scale;
    y *= scale;

    return *this;
}

Coord2D &Coord2D::operator*=(float scale)
{
    x *= scale;
    y *= scale;

    return *this;
}

// x87, not SSE: the dot product returns a float, and a float return leaves the
// value on the x87 stack whatever the rest of the file is built with.
float Coord2D::operator*(const Coord2D &that) const
{
    return x * that.x + y * that.y;
}

float Coord2D::operator*(const Coord3DBase &that) const
{
    return x * that.x + y * that.y;
}

Coord2D::Coord2D(int x, int y)
{
    this->x = (float)x;
    this->y = (float)y;
}

bool Coord2D::IsExactlyEqualTo(const Coord2D &that) const
{
    return x == that.x && y == that.y;
}

float Coord2D::length() const
{
    return (float)sqrt(x * x + y * y);
}

void Coord2D::normalize()
{
    float len = length();
    if (len != 0.0f) {
        x /= len;
        y /= len;
    }
}

Coord2D &Coord2D::Negate()
{
    x = -x;
    y = -y;
    return *this;
}

Coord2D &Coord2D::operator/=(float divisor)
{
    float scale = 1.0f / divisor;
    x *= scale;
    y *= scale;
    return *this;
}

Coord2D &Coord2D::Rotate(float sine, float cosine)
{
    float new_x = cosine * x - sine * y;

    y = cosine * y + sine * x;
    x = new_x;
    return *this;
}

Coord2D &Coord2D::Rotate(Coord2D &coord, float sine, float cosine)
{
    x = cosine * coord.x - sine * coord.y;
    y = cosine * coord.y + sine * coord.x;
    return *this;
}

Coord2D &Coord2D::SetMaxVect()
{
    y = 3.4028234663852886e38f;
    x = 3.4028234663852886e38f;
    return *this;
}

Coord2D &Coord2D::SetMinVect()
{
    y = -3.4028234663852886e38f;
    x = -3.4028234663852886e38f;
    return *this;
}

Coord2D &Coord2D::SetXAxis()
{
    x = 1.0f;
    y = 0.0f;
    return *this;
}

Coord2D &Coord2D::SetYAxis()
{
    x = 0.0f;
    y = 1.0f;
    return *this;
}

Coord2D &Coord2D::SetZero()
{
    y = 0.0f;
    x = 0.0f;
    return *this;
}

Debug &operator<<(Debug &debug, const Coord2D &coord)
{
    debug << "(" << coord.x << ", " << coord.y << ")";
    return debug;
}

// The larger component plus a quarter of the smaller - a cheap length that
// never underestimates by more than about a tenth. fabs is called twice for the
// comparison and twice again for the result, which is what the source says.
float Coord2D::GetLengthEstimate() const
{
    if (fabs(x) > fabs(y)) {
        return (float)(fabs(x) + fabs(y) * 0.25f);
    }

    return (float)(fabs(y) + fabs(x) * 0.25f);
}

// The two components have to be read into named locals first. Written as
// `x * x + y * y` straight off the members MSVC loads y before x; hoisting them
// is what puts the loads in retail's order, and coord3d.cpp's identical 2D pair
// - the same bodies, ICF-folded - is where that shape came from.
float Coord2D::GetLength() const
{
    float x_value = x;
    float y_value = y;

    return (float)sqrt(x_value * x_value + y_value * y_value);
}

float Coord2D::GetLengthSqrd() const
{
    float x_value = x;
    float y_value = y;

    return x_value * x_value + y_value * y_value;
}

static const float one = 1.0f;

// Same shape as Coord3D::Normalize2D: the length through GetLength, one
// reciprocal, two scales, and the length back.
float Coord2D::Normalize()
{
    float x_value = x;
    float y_value = y;
    float len = (float)sqrt(x_value * x_value + y_value * y_value);
    float scale = one / len;

    x *= scale;
    y *= scale;

    return len;
}
