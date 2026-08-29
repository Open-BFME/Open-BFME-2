// cl: /O1 /ICode/GameEngine/Source/Common

struct ICoord3D
{
    ICoord3D &operator=(const ICoord3D &that);
    void zero();

    int x;
    int y;
    int z;
};

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
