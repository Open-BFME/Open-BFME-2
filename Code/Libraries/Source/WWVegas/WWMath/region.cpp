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

struct ICoord2D;
struct ICoord3D;

struct IRegion2D
{
    bool operator==(const IRegion2D &that) const;
    bool operator!=(const IRegion2D &that) const;
    void expandBy(const ICoord2D &point);
    int width() const;
    int height() const;

    int x_min;
    int y_min;
    int x_max;
    int y_max;
};

struct IRegion3D
{
    void expandBy(const ICoord3D &point);
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

struct ICoord2DBase
{
    int x;
    int y;
};

struct ICoord2D : public ICoord2DBase
{
};

// Both integer expandBy members widen one axis at a time through this shared
// three-argument worker rather than inlining the comparison pair. It is only
// DECLARED here: with the body in front of them MSVC 7.1 sees that it leaves
// edx alone and parks `this` there across the calls, while retail saves esi and
// edi like a caller that has only seen the declaration.
void expandRange(int *low, int value, int *high);

Debug &operator<<(Debug &debug, const ICoord2DBase &coord);

struct ICoord3D
{
    int x;
    int y;
    int z;
};

Debug &operator<<(Debug &debug, const ICoord3D &coord);

class Coord3D
{
public:
    void scale(float scale);

    float x;
    float y;
    float z;
};

void Coord3D::scale(float scale)
{
    x *= scale;
    y *= scale;
    z *= scale;
}

Debug &operator<<(Debug &debug, const Coord3D &coord);

class Coord2D
{
public:
    float x;
    float y;
};

Debug &operator<<(Debug &debug, const Coord2D &coord);

struct RealRange
{
    void combine(RealRange &that);

    float min;
    float max;
};

void RealRange::combine(RealRange &that)
{
    // Both selections bind a reference to the ternary rather than assigning its
    // value: that is what makes MSVC 7.1 conditional-move the ADDRESS and then
    // copy the float as a raw dword, which is the retail shape. Which side each
    // ternary is written from decides the comiss operand order and the cmov
    // condition, and only this pair reproduces cmovbe then cmova.
    const float &low = that.min > min ? min : that.min;
    min = low;

    const float &high = that.max < max ? max : that.max;
    max = high;
}

struct IntRange
{
    void combine(IntRange &that);

    int min;
    int max;
};

void IntRange::combine(IntRange &that)
{
    const int &low = min < that.min ? min : that.min;
    min = low;

    const int &high = max > that.max ? max : that.max;
    max = high;
}

struct Region2D
{
    Region2D(const Coord2D &lower_left, const Coord2D &upper_right);
    float width() const;
    bool isInside(const Coord2D &point) const;
    bool IsExactlyEqualTo(const Region2D &that) const;
    void expandBy(const Coord2D &point);

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
    void expandBy(const Coord3D &point);
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

Region2D::Region2D(const Coord2D &lower_left, const Coord2D &upper_right)
{
    x_min = lower_left.x;
    y_min = lower_left.y;
    x_max = upper_right.x;
    y_max = upper_right.y;
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

bool Region2D::IsExactlyEqualTo(const Region2D &that) const
{
    return that.x_min == x_min &&
        that.y_min == y_min &&
        that.x_max == x_max &&
        that.y_max == y_max;
}

void Region2D::expandBy(const Coord2D &point)
{
    float x = point.x;

    if (x < x_min) {
        x_min = x;
    } else if (x > x_max) {
        x_max = x;
    }

    float y = point.y;

    if (y < y_min) {
        y_min = y;
    } else if (y > y_max) {
        y_max = y;
    }
}

void IRegion2D::expandBy(const ICoord2D &point)
{
    expandRange(&x_min, point.x, &x_max);
    expandRange(&y_min, point.y, &y_max);
}

void IRegion3D::expandBy(const ICoord3D &point)
{
    expandRange(&x_min, point.x, &x_max);
    expandRange(&y_min, point.y, &y_max);
    expandRange(&z_min, point.z, &z_max);
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

void Region3D::expandBy(const Coord3D &point)
{
    float x = point.x;

    if (x < x_min) {
        x_min = x;
    } else if (x > x_max) {
        x_max = x;
    }

    float y = point.y;

    if (y < y_min) {
        y_min = y;
    } else if (y > y_max) {
        y_max = y;
    }

    float z = point.z;

    if (z < z_min) {
        z_min = z;
    } else if (z > z_max) {
        z_max = z;
    }
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

Debug &operator<<(Debug &debug, const IRegion3D &region)
{
    debug << *(const ICoord3D *)&region.x_min << " - " << *(const ICoord3D *)&region.x_max;
    return debug;
}

Debug &operator<<(Debug &debug, const Region3D &region)
{
    debug << *(const Coord3D *)&region.x_min << " - " << *(const Coord3D *)&region.x_max;
    return debug;
}

Debug &operator<<(Debug &debug, const RealRange &range)
{
    debug << "[" << range.min << ", " << range.max << "]";
    return debug;
}

Debug &operator<<(Debug &debug, const Region2D &region)
{
    debug << *(const Coord2D *)&region.x_min << " - " << *(const Coord2D *)&region.x_max;
    return debug;
}

Debug &operator<<(Debug &debug, const IRegion2D &region)
{
    debug << *(const ICoord2DBase *)&region.x_min << " - " << *(const ICoord2DBase *)&region.x_max;
    return debug;
}
