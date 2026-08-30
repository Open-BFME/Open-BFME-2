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
    Coord3D &GetYVector(Coord3D &out) const;
    Coord3D &GetZVector(Coord3D &out) const;
    Coord3D &RotateCoord(const Coord3D &coord, Coord3D &out);
    Matrix4D &Transpose();
    float Determinant() const;

    float values[16];
};

Coord3D &Matrix4D::GetXVector(Coord3D &out) const
{
    out.x = values[0];
    out.y = values[4];
    out.z = values[8];
    return out;
}

Coord3D &Matrix4D::GetYVector(Coord3D &out) const
{
    out.x = values[1];
    out.y = values[5];
    out.z = values[9];
    return out;
}

Coord3D &Matrix4D::GetZVector(Coord3D &out) const
{
    out.x = values[2];
    out.y = values[6];
    out.z = values[10];
    return out;
}

Coord3D &Matrix4D::RotateCoord(const Coord3D &coord, Coord3D &out)
{
    float y = values[4] * coord.x;
    y += values[6] * coord.z;
    y += values[5] * coord.y;

    float z = values[8] * coord.x;
    z += values[10] * coord.z;
    z += values[9] * coord.y;

    float x = values[2] * coord.z;
    x += values[1] * coord.y;
    x += values[0] * coord.x;

    out.x = x;
    out.y = y;
    out.z = z;
    return out;
}

Matrix4D &Matrix4D::Transpose()
{
    *(unsigned int *)&values[1] ^= *(unsigned int *)&values[4];
    *(unsigned int *)&values[4] ^= *(unsigned int *)&values[1];
    *(unsigned int *)&values[1] ^= *(unsigned int *)&values[4];

    *(unsigned int *)&values[2] ^= *(unsigned int *)&values[8];
    *(unsigned int *)&values[8] ^= *(unsigned int *)&values[2];
    *(unsigned int *)&values[2] ^= *(unsigned int *)&values[8];

    *(unsigned int *)&values[3] ^= *(unsigned int *)&values[12];
    *(unsigned int *)&values[12] ^= *(unsigned int *)&values[3];
    *(unsigned int *)&values[3] ^= *(unsigned int *)&values[12];

    *(unsigned int *)&values[6] ^= *(unsigned int *)&values[9];
    *(unsigned int *)&values[9] ^= *(unsigned int *)&values[6];
    *(unsigned int *)&values[6] ^= *(unsigned int *)&values[9];

    *(unsigned int *)&values[7] ^= *(unsigned int *)&values[13];
    *(unsigned int *)&values[13] ^= *(unsigned int *)&values[7];
    *(unsigned int *)&values[7] ^= *(unsigned int *)&values[13];

    *(unsigned int *)&values[14] ^= *(unsigned int *)&values[11];
    *(unsigned int *)&values[11] ^= *(unsigned int *)&values[14];
    *(unsigned int *)&values[14] ^= *(unsigned int *)&values[11];
    return *this;
}

float Matrix4D::Determinant() const
{
    float a5 = values[8] * values[13] - values[12] * values[9];
    float b5 = values[7] * values[2] - values[6] * values[3];
    return (values[10] * values[15] - values[14] * values[11]) * (values[0] * values[5] - values[4] * values[1])
         - (values[6] * values[0] - values[4] * values[2]) * (values[15] * values[9] - values[11] * values[13])
         + (values[8] * values[15] - values[12] * values[11]) * (values[6] * values[1] - values[2] * values[5])
         + (values[7] * values[0] - values[4] * values[3]) * (values[14] * values[9] - values[10] * values[13])
         - (values[14] * values[8] - values[10] * values[12]) * (values[7] * values[1] - values[3] * values[5])
         + a5 * b5;
}
