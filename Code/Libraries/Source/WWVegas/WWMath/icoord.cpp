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
    bool operator==(const ICoord2DBase &that) const;
    bool operator!=(const ICoord2DBase &that) const;
};

struct ICoord3D
{
    ICoord3D &operator=(const ICoord3D &that);
    int length() const;
    void zero();

    int x;
    int y;
    int z;
};

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
