// cl: /O1 /ICode/GameEngine/Source/Common

struct ICoord2DBase
{
    int x;
    int y;
};

struct ICoord2D : public ICoord2DBase
{
    bool operator==(const ICoord2DBase &that) const;
};

struct ICoord3D
{
    ICoord3D &operator=(const ICoord3D &that);
    void zero();

    int x;
    int y;
    int z;
};

bool ICoord2D::operator==(const ICoord2DBase &that) const
{
    return x == that.x && y == that.y;
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

void ICoord3D::zero()
{
    x = 0;
    y = 0;
    z = 0;
}
