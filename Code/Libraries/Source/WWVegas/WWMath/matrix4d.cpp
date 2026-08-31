// cl: /O1 /arch:SSE2

extern "C" float __cdecl fabs(double value);

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
    Matrix4D(bool identity);
    Matrix4D(const Coord3D &translation);
    Matrix4D(const Matrix4D &that);
    Matrix4D(
        float m00, float m01, float m02, float m03,
        float m10, float m11, float m12, float m13,
        float m20, float m21, float m22, float m23,
        float m30, float m31, float m32, float m33);
    Matrix4D &operator*=(float scale);
    Matrix4D &operator/=(float divisor);
    Matrix4D &operator+=(const Matrix4D &that);
    Matrix4D &operator-=(const Matrix4D &that);
    Coord3D &GetTranslationVector(Coord3D &out) const;
    Coord3D &GetXVector(Coord3D &out) const;
    Coord3D &GetYVector(Coord3D &out) const;
    Coord3D &GetZVector(Coord3D &out) const;
    Coord3D &RotateCoord(const Coord3D &coord, Coord3D &out);
    Coord3D &TransformCoord(const Coord3D &coord, Coord3D &out);
    Matrix4D &SetIdentity();
    Matrix4D &Multiply(const Matrix4D &left, const Matrix4D &right);
    Matrix4D &Set(const Coord3D &translation);

    bool IsExactlyEqualTo(const Matrix4D &that);
    Matrix4D &Transpose();
    float Determinant() const;
    float Inverse();

    float values[16];
};

inline Matrix4D &Matrix4D::SetIdentity()
{
    values[0] = 1.0f;
    values[1] = 0.0f;
    values[2] = 0.0f;
    values[3] = 0.0f;
    values[4] = 0.0f;
    values[5] = 1.0f;
    values[6] = 0.0f;
    values[7] = 0.0f;
    values[8] = 0.0f;
    values[9] = 0.0f;
    values[10] = 1.0f;
    values[11] = 0.0f;
    values[12] = 0.0f;
    values[13] = 0.0f;
    values[14] = 0.0f;
    values[15] = 1.0f;

    return *this;
}

// Only the first component goes through the x87; the other two are integer
// moves. That mix is what MSVC emits for a float copy here, not a choice.
Coord3D &Matrix4D::GetTranslationVector(Coord3D &out) const
{
    out.x = values[3];
    out.y = values[7];
    out.z = values[11];

    return out;
}

// A raw bit comparison, four rows at a time: the sixteen slots are xored and
// ored together in groups of four and the group tested once, with an early out
// when the two are the same object.
bool Matrix4D::IsExactlyEqualTo(const Matrix4D &that)
{
    if (this == &that) {
        return true;
    }

    const int *a = (const int *)values;
    const int *b = (const int *)that.values;

    for (int row = 0; row < 4; ++row) {
        int diff = *a++ ^ *b++;

        diff |= *a++ ^ *b++;
        diff |= *a++ ^ *b++;
        diff |= *a++ ^ *b++;

        if (diff != 0) {
            return false;
        }
    }

    return true;
}

Matrix4D::Matrix4D(bool identity)
{
    if (identity) {
        SetIdentity();
    }
}

// The three translation slots are stored twice: MSVC hoists their zeroes out of
// the inlined SetIdentity to the top of the body and leaves them there, dead,
// ahead of the thirteen that are not overwritten.
Matrix4D::Matrix4D(const Coord3D &translation)
{
    SetIdentity();

    values[3] = translation.x;
    values[7] = translation.y;
    values[11] = translation.z;
}

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

Matrix4D &Matrix4D::operator/=(float divisor)
{
    float scale = 1.0f / divisor;
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

float Matrix4D::Inverse()
{
    float s0 = values[0] * values[5] - values[1] * values[4];
    float s1 = values[6] * values[0] - values[4] * values[2];
    float s2 = values[7] * values[0] - values[3] * values[4];
    float s3 = values[1] * values[6] - values[2] * values[5];
    float s4 = values[7] * values[1] - values[3] * values[5];
    float s5 = values[7] * values[2] - values[3] * values[6];
    float c0 = values[8] * values[13] - values[9] * values[12];
    float c1 = values[8] * values[14] - values[12] * values[10];
    float c2 = values[8] * values[15] - values[11] * values[12];
    float c3 = values[9] * values[14] - values[13] * values[10];
    float c4 = values[15] * values[9] - values[13] * values[11];
    float c5 = values[15] * values[10] - values[11] * values[14];

    float det = c5 * s0 - c4 * s1 + c2 * s3 + c3 * s2 - c1 * s4 + c0 * s5;
    if (fabs(det) <= 1.0e-4f) {
        return 0.0f;
    }

    struct ResultStorage
    {
        float values[16];
    } result;
    result.values[0] = (c5 * values[5] - c4 * values[6] + c3 * values[7]);
    result.values[4] = -(c5 * values[4] + c2 * values[6] - c1 * values[7]);
    result.values[8] = (c4 * values[4] - c2 * values[5] + c0 * values[7]);
    result.values[12] = -(c3 * values[4] + c1 * values[5] - c0 * values[6]);
    result.values[1] = -(c5 * values[1] + c4 * values[2] - c3 * values[3]);
    result.values[5] = (c5 * values[0] - c2 * values[2] + c1 * values[3]);
    result.values[9] = -(c2 * values[1] + c4 * values[0] - c0 * values[3]);
    result.values[13] = (c3 * values[0] - c1 * values[1] + c0 * values[2]);
    result.values[2] = (s5 * values[13] - s4 * values[14] + s3 * values[15]);
    result.values[6] = -(s5 * values[12] + s2 * values[14] - s1 * values[15]);
    result.values[10] = (s4 * values[12] - s2 * values[13] + s0 * values[15]);
    result.values[14] = -(s1 * values[13] + s3 * values[12] - s0 * values[14]);
    result.values[3] = -(s5 * values[9] + s4 * values[10] - s3 * values[11]);
    result.values[7] = (s5 * values[8] - s2 * values[10] + s1 * values[11]);
    result.values[11] = -(s4 * values[8] + s2 * values[9] - s0 * values[11]);
    result.values[15] = (s3 * values[8] - s1 * values[9] + s0 * values[10]);

    float recip = 1.0f / det;
    result.values[0] *= recip;
    result.values[1] *= recip;
    result.values[2] *= recip;
    result.values[3] *= recip;
    result.values[4] *= recip;
    result.values[5] *= recip;
    result.values[6] *= recip;
    result.values[7] *= recip;
    result.values[8] *= recip;
    result.values[9] *= recip;
    result.values[10] *= recip;
    result.values[11] *= recip;
    result.values[12] *= recip;
    result.values[13] *= recip;
    result.values[14] *= recip;
    result.values[15] *= recip;

    if ((void *)this != (void *)&result) {
        values[0] = result.values[0];
        values[1] = result.values[1];
        values[2] = result.values[2];
        values[3] = result.values[3];
        values[4] = result.values[4];
        values[5] = result.values[5];
        values[6] = result.values[6];
        values[7] = result.values[7];
        values[8] = result.values[8];
        values[9] = result.values[9];
        values[10] = result.values[10];
        values[11] = result.values[11];
        values[12] = result.values[12];
        values[13] = result.values[13];
        values[14] = result.values[14];
        values[15] = result.values[15];
    }
    return det;
}

// SetIdentity has to be inline for the two constructors to absorb it whole, the
// way retail does; taking its address is what still forces the standalone copy
// at 0x0000401C out.
Matrix4D &(Matrix4D::*g_matrix4dSetIdentity)() = &Matrix4D::SetIdentity;

// The full 4x4 product written out: sixteen dot products, row of left against
// column of right, straight into this.
Matrix4D &Matrix4D::Multiply(const Matrix4D &left, const Matrix4D &right)
{
    values[0] = left.values[0] * right.values[0] + left.values[1] * right.values[4] + left.values[2] * right.values[8] + left.values[3] * right.values[12];
    values[1] = left.values[0] * right.values[1] + left.values[1] * right.values[5] + left.values[2] * right.values[9] + left.values[3] * right.values[13];
    values[2] = left.values[0] * right.values[2] + left.values[1] * right.values[6] + left.values[2] * right.values[10] + left.values[3] * right.values[14];
    values[3] = left.values[0] * right.values[3] + left.values[1] * right.values[7] + left.values[2] * right.values[11] + left.values[3] * right.values[15];

    values[4] = left.values[4] * right.values[0] + left.values[5] * right.values[4] + left.values[6] * right.values[8] + left.values[7] * right.values[12];
    values[5] = left.values[4] * right.values[1] + left.values[5] * right.values[5] + left.values[6] * right.values[9] + left.values[7] * right.values[13];
    values[6] = left.values[4] * right.values[2] + left.values[5] * right.values[6] + left.values[6] * right.values[10] + left.values[7] * right.values[14];
    values[7] = left.values[4] * right.values[3] + left.values[5] * right.values[7] + left.values[6] * right.values[11] + left.values[7] * right.values[15];

    values[8] = left.values[8] * right.values[0] + left.values[9] * right.values[4] + left.values[10] * right.values[8] + left.values[11] * right.values[12];
    values[9] = left.values[8] * right.values[1] + left.values[9] * right.values[5] + left.values[10] * right.values[9] + left.values[11] * right.values[13];
    values[10] = left.values[8] * right.values[2] + left.values[9] * right.values[6] + left.values[10] * right.values[10] + left.values[11] * right.values[14];
    values[11] = left.values[8] * right.values[3] + left.values[9] * right.values[7] + left.values[10] * right.values[11] + left.values[11] * right.values[15];

    values[12] = left.values[12] * right.values[0] + left.values[13] * right.values[4] + left.values[14] * right.values[8] + left.values[15] * right.values[12];
    values[13] = left.values[12] * right.values[1] + left.values[13] * right.values[5] + left.values[14] * right.values[9] + left.values[15] * right.values[13];
    values[14] = left.values[12] * right.values[2] + left.values[13] * right.values[6] + left.values[14] * right.values[10] + left.values[15] * right.values[14];
    values[15] = left.values[12] * right.values[3] + left.values[13] * right.values[7] + left.values[14] * right.values[11] + left.values[15] * right.values[15];

    return *this;
}

// The same body as the translation constructor, folded onto it.
Matrix4D &Matrix4D::Set(const Coord3D &translation)
{
    SetIdentity();

    values[3] = translation.x;
    values[7] = translation.y;
    values[11] = translation.z;

    return *this;
}
