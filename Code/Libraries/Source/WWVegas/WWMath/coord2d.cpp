// cl: /O1 /arch:SSE2 /ICode/GameEngine/Source/Common

#include <math.h>

class Coord2D
{
public:
    Coord2D(int x, int y);
    bool IsExactlyEqualTo(const Coord2D &that) const;
    float length() const;
    Coord2D &Negate();
    Coord2D &operator/=(float divisor);
    Coord2D &Rotate(float sine, float cosine);
    Coord2D &Rotate(Coord2D &coord, float sine, float cosine);
    Coord2D &SetMaxVect();
    Coord2D &SetMinVect();
    Coord2D &SetXAxis();
    Coord2D &SetYAxis();
    Coord2D &SetZero();

    float x;
    float y;
};

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
