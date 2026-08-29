// cl: /O1 /arch:SSE2 /ICode/GameEngine/Source/Common

struct IRegion2D
{
    bool operator==(const IRegion2D &that) const;
    bool operator!=(const IRegion2D &that) const;
    int width() const;
    int height() const;

    int x_min;
    int y_min;
    int x_max;
    int y_max;
};

struct IRegion3D
{
    int width() const;
    int height() const;
    int depth() const;

    int x_min;
    int y_min;
    int z_min;
    int x_max;
    int y_max;
    int z_max;
};

class Coord3D
{
public:
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

struct Region2D
{
    float width() const;
    bool isInside(const Coord2D &point) const;

    float x_min;
    float y_min;
    float x_max;
    float y_max;
};

struct Region3D
{
    float width() const;
    float height() const;
    float depth() const;
    void zero();
    bool isInRegionNoZ(const Coord3D *point) const;
    bool isInRegionWithZ(const Coord3D *point) const;

    float x_min;
    float y_min;
    float z_min;
    float x_max;
    float y_max;
    float z_max;
};

bool IRegion2D::operator==(const IRegion2D &that) const
{
    return x_min == that.x_min &&
        y_min == that.y_min &&
        x_max == that.x_max &&
        y_max == that.y_max;
}

float Region2D::width() const
{
    return x_max - x_min;
}

bool Region2D::isInside(const Coord2D &point) const
{
    return point.x > x_min &&
        point.x < x_max &&
        point.y > y_min &&
        point.y < y_max;
}

bool IRegion2D::operator!=(const IRegion2D &that) const
{
    return !(*this == that);
}

int IRegion2D::width() const
{
    return x_max - x_min;
}

int IRegion2D::height() const
{
    return y_max - y_min;
}

int IRegion3D::width() const
{
    return x_max - x_min;
}

int IRegion3D::height() const
{
    return y_max - y_min;
}

int IRegion3D::depth() const
{
    return z_max - z_min;
}

float Region3D::width() const
{
    return x_max - x_min;
}

float Region3D::height() const
{
    return y_max - y_min;
}

float Region3D::depth() const
{
    return z_max - z_min;
}

void Region3D::zero()
{
    x_min = 0.0f;
    y_min = 0.0f;
    z_min = 0.0f;
    x_max = 0.0f;
    y_max = 0.0f;
    z_max = 0.0f;
}

bool Region3D::isInRegionNoZ(const Coord3D *point) const
{
    return x_min < point->x &&
        point->x < x_max &&
        y_min < point->y &&
        point->y < y_max;
}

bool Region3D::isInRegionWithZ(const Coord3D *point) const
{
    return x_min < point->x &&
        point->x < x_max &&
        y_min < point->y &&
        point->y < y_max &&
        z_min < point->z &&
        point->z < z_max;
}
