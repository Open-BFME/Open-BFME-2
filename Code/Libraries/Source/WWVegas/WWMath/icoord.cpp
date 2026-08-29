// cl: /ICode/GameEngine/Source/Common

struct ICoord3D
{
    void zero();

    int x;
    int y;
    int z;
};

void ICoord3D::zero()
{
    x = 0;
    y = 0;
    z = 0;
}
