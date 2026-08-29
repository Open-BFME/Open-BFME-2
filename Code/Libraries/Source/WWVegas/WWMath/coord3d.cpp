// cl: /O1 /arch:SSE2 /ICode/GameEngine/Source/Common

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
    Coord3D &Add(const Coord2D &left, const Coord3DBase &right);
    Coord3D &Add(const Coord3DBase &left, const Coord2D &right);
    Coord3D &Sub(const Coord2D &left, const Coord3DBase &right);
    Coord3D &Sub(const Coord3DBase &left, const Coord2D &right);
    Coord3D &Add2D(const Coord3DBase &left, const Coord3DBase &right);
    Coord3D &Sub2D(const Coord3DBase &left, const Coord3DBase &right);
    Coord3D &Scale2D(const Coord3DBase &that, float scale);
    float GetLengthSqrd2D() const;
    Coord3D &Set2D(float x, float y);
    Coord3D &SetMaxVect();
    Coord3D &SetMinVect();
    Coord3D &SetXAxis();
    Coord3D &SetYAxis();
    Coord3D &SetZAxis();
    Coord3D &SetZero();

    float x;
    float y;
    float z;
};

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

Coord3D &Coord3D::Scale2D(const Coord3DBase &that, float scale)
{
    x = that.x * scale;
    y = that.y * scale;
    return *this;
}

float Coord3D::GetLengthSqrd2D() const
{
    float x_value = x;
    float y_value = y;

    return x_value * x_value + y_value * y_value;
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

Debug &operator<<(Debug &debug, const Coord3D &coord)
{
    debug << "(" << coord.x << ", " << coord.y << ", " << coord.z << ")";
    return debug;
}
