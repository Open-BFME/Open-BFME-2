// cl: /O1 /ICode/GameEngine/Source/Common

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

struct ICoord2DBase
{
    int x;
    int y;
};

struct ICoord2D : public ICoord2DBase
{
    ICoord2D();
    ICoord2D(int x, int y);
    ICoord2D(const ICoord2DBase &that);

    ICoord2D &operator=(const ICoord2D &that);
    ICoord2D &operator=(const ICoord2DBase &that);

    ICoord2D &operator+=(const ICoord2DBase &that);
    ICoord2D &operator-=(const ICoord2DBase &that);
    ICoord2D &operator*=(int factor);
    ICoord2D &operator/=(int divisor);
    ICoord2D &MoveBy(int delta);
    bool operator==(const ICoord2DBase &that) const;
    bool operator!=(const ICoord2DBase &that) const;
};

struct ICoord3D
{
    ICoord3D();
    ICoord3D(int x, int y, int z);

    ICoord3D &operator=(const ICoord3D &that);
    int length() const;
    void zero();

    int x;
    int y;
    int z;
};

// The worker both integer IRegion expandBy members call, one axis at a time, as
// (&low, value, &high). It cannot share a translation unit with them: with the
// body visible MSVC 7.1 proves it leaves edx alone and parks `this` there
// across the calls, while retail saves esi and edi around them.
void expandRange(int *low, int value, int *high)
{
    if (value < *low) {
        *low = value;
    } else if (value > *high) {
        *high = value;
    }
}

ICoord3D::ICoord3D(int x, int y, int z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

ICoord2D &ICoord2D::operator+=(const ICoord2DBase &that)
{
    x += that.x;
    y += that.y;
    return *this;
}

ICoord2D &ICoord2D::operator-=(const ICoord2DBase &that)
{
    x -= that.x;
    y -= that.y;
    return *this;
}

ICoord2D &ICoord2D::operator*=(int factor)
{
    x *= factor;
    y *= factor;
    return *this;
}

ICoord2D &ICoord2D::operator/=(int divisor)
{
    x /= divisor;
    y /= divisor;
    return *this;
}

ICoord2D &ICoord2D::MoveBy(int delta)
{
    x += delta;
    y += delta;
    return *this;
}

bool ICoord2D::operator==(const ICoord2DBase &that) const
{
    return x == that.x && y == that.y;
}

bool ICoord2D::operator!=(const ICoord2DBase &that) const
{
    return x != that.x || y != that.y;
}

ICoord3D &ICoord3D::operator=(const ICoord3D &that)
{
    struct Raw
    {
        int x;
        int y;
        int z;
    };

    *(Raw *)this = *(const Raw *)&that;
    return *this;
}

int ICoord3D::length() const
{
    return (int)sqrt((double)(x * x + y * y + z * z));
}

void ICoord3D::zero()
{
    x = 0;
    y = 0;
    z = 0;
}

Debug &operator<<(Debug &debug, const ICoord2DBase &coord)
{
    debug << "(" << coord.x << ", " << coord.y << ")";
    return debug;
}

Debug &operator<<(Debug &debug, const ICoord3D &coord)
{
    debug << "(" << coord.x << ", " << coord.y << ", " << coord.z << ")";
    return debug;
}

// The empty pair: a bare `mov eax, ecx; ret`, ICF-folded across every default
// constructor in the math headers.
ICoord2D::ICoord2D()
{
}

ICoord3D::ICoord3D()
{
}

// Two integer stores from the stack, which is the same body as the float pair
// one register class over.
ICoord2D::ICoord2D(int x, int y)
{
    this->x = x;
    this->y = y;
}

ICoord2D::ICoord2D(const ICoord2DBase &that)
{
    x = that.x;
    y = that.y;
}

ICoord2D &ICoord2D::operator=(const ICoord2D &that)
{
    x = that.x;
    y = that.y;

    return *this;
}

ICoord2D &ICoord2D::operator=(const ICoord2DBase &that)
{
    x = that.x;
    y = that.y;

    return *this;
}
