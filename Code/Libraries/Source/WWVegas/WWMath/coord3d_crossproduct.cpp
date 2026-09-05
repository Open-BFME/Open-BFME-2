// cl: /O2 /arch:SSE /DNDEBUG /MD

struct Coord3DBase
{
    float x;
    float y;
    float z;
};

class Coord3D : public Coord3DBase
{
public:
    Coord3D &CrossProduct(const Coord3DBase &left, const Coord3DBase &right);
};

Coord3D &Coord3D::CrossProduct(const Coord3DBase &left, const Coord3DBase &right)
{
    const float xt = left.y * right.z;
    x = xt - left.z * right.y;
    const float yt = left.z * right.x;
    y = yt - (volatile const float &)left.x * right.z;
    const float zt = (volatile const float &)left.x * right.y;
    z = zt - left.y * right.x;
    return *this;
}
