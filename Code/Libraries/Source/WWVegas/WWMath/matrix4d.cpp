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
    Matrix4D(const Matrix4D &that);
    Matrix4D(
        float m00, float m01, float m02, float m03,
        float m10, float m11, float m12, float m13,
        float m20, float m21, float m22, float m23,
        float m30, float m31, float m32, float m33);
    Matrix4D &operator*=(float scale);
    Matrix4D &operator+=(const Matrix4D &that);
    Matrix4D &operator-=(const Matrix4D &that);
    Coord3D &GetXVector(Coord3D &out) const;
    Coord3D &GetYVector(Coord3D &out) const;
    Coord3D &GetZVector(Coord3D &out) const;
    Coord3D &RotateCoord(const Coord3D &coord, Coord3D &out);
    Coord3D &TransformCoord(const Coord3D &coord, Coord3D &out);
    Matrix4D &Transpose();
    float Determinant() const;

    float values[16];
};

Matrix4D::Matrix4D(const Matrix4D &that)
{
    if (this != &that) {
        values[0] = that.values[0];
        values[1] = that.values[1];
        values[2] = that.values[2];
        values[3] = that.values[3];
        values[4] = that.values[4];
        values[5] = that.values[5];
        values[6] = that.values[6];
        values[7] = that.values[7];
        values[8] = that.values[8];
        values[9] = that.values[9];
        values[10] = that.values[10];
        values[11] = that.values[11];
        values[12] = that.values[12];
        values[13] = that.values[13];
        values[14] = that.values[14];
        values[15] = that.values[15];
    }
}

Matrix4D::Matrix4D(
    float m00, float m01, float m02, float m03,
    float m10, float m11, float m12, float m13,
    float m20, float m21, float m22, float m23,
    float m30, float m31, float m32, float m33)
{
    values[0] = m00;
    values[1] = m01;
    values[2] = m02;
    values[3] = m03;
    values[4] = m10;
    values[5] = m11;
    values[6] = m12;
    values[7] = m13;
    values[8] = m20;
    values[9] = m21;
    values[10] = m22;
    values[11] = m23;
    values[12] = m30;
    values[13] = m31;
    values[14] = m32;
    values[15] = m33;
}

Matrix4D &Matrix4D::operator*=(float scale)
{
    values[0] *= scale;
    values[1] *= scale;
    values[2] *= scale;
    values[3] *= scale;
    values[4] *= scale;
    values[5] *= scale;
    values[6] *= scale;
    values[7] *= scale;
    values[8] *= scale;
    values[9] *= scale;
    values[10] *= scale;
    values[11] *= scale;
    values[12] *= scale;
    values[13] *= scale;
    values[14] *= scale;
    values[15] *= scale;
    return *this;
}

Matrix4D &Matrix4D::operator+=(const Matrix4D &that)
{
    values[0] += that.values[0];
    values[1] += that.values[1];
    values[2] += that.values[2];
    values[3] += that.values[3];
    values[4] += that.values[4];
    values[5] += that.values[5];
    values[6] += that.values[6];
    values[7] += that.values[7];
    values[8] += that.values[8];
    values[9] += that.values[9];
    values[10] += that.values[10];
    values[11] += that.values[11];
    values[12] += that.values[12];
    values[13] += that.values[13];
    values[14] += that.values[14];
    values[15] += that.values[15];
    return *this;
}

Matrix4D &Matrix4D::operator-=(const Matrix4D &that)
{
    values[0] -= that.values[0];
    values[1] -= that.values[1];
    values[2] -= that.values[2];
    values[3] -= that.values[3];
    values[4] -= that.values[4];
    values[5] -= that.values[5];
    values[6] -= that.values[6];
    values[7] -= that.values[7];
    values[8] -= that.values[8];
    values[9] -= that.values[9];
    values[10] -= that.values[10];
    values[11] -= that.values[11];
    values[12] -= that.values[12];
    values[13] -= that.values[13];
    values[14] -= that.values[14];
    values[15] -= that.values[15];
    return *this;
}

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

Coord3D &Matrix4D::TransformCoord(const Coord3D &coord, Coord3D &out)
{
    float y = values[4] * coord.x;
    y += values[6] * coord.z;
    y += values[5] * coord.y;
    y += values[7];

    float z = values[8] * coord.x;
    z += values[10] * coord.z;
    z += values[9] * coord.y;
    z += values[11];

    float x = values[2] * coord.z;
    x += values[1] * coord.y;
    x += values[0] * coord.x;
    x += values[3];

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
