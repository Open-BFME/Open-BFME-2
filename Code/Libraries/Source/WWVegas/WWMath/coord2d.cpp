// cl: /O1 /arch:SSE2 /ICode/GameEngine/Source/Common

class Coord2D
{
public:
    Coord2D(int x, int y);
    bool IsExactlyEqualTo(const Coord2D &that) const;
    Coord2D &Negate();
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

Coord2D &Coord2D::Negate()
{
    x = -x;
    y = -y;
    return *this;
}

Coord2D &Coord2D::SetZero()
{
    y = 0.0f;
    x = 0.0f;
    return *this;
}
