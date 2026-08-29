// cl: /O1 /arch:SSE2

class Coord3D
{
public:
    float x;
    float y;
    float z;
};

class Matrix4D
{
public:
    Coord3D &GetXVector(Coord3D &out) const;

    float values[16];
};

Coord3D &Matrix4D::GetXVector(Coord3D &out) const
{
    out.x = values[0];
    out.y = values[4];
    out.z = values[8];
    return out;
}
