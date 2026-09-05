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
    Matrix4D(const Coord3D &axis, float angle);

    float values[16];
};

Matrix4D::Matrix4D(const Coord3D &axis, float angle)
{
    float cosine;
    float sine;

    __asm
    {
        fld angle
        fsincos
        fstp cosine
        fstp sine
    }

    values[0] = axis.x * axis.x + cosine * (1.0f - axis.x * axis.x);
    float value1 = axis.y * axis.x * (1.0f - cosine);
    value1 -= axis.z * sine;
    values[1] = value1;
    values[2] = axis.x * (1.0f - cosine) * axis.z + axis.y * sine;
    values[3] = 0.0f;
    values[4] = axis.y * axis.x * (1.0f - cosine) + axis.z * sine;
    values[5] = axis.y * axis.y + cosine * (1.0f - axis.y * axis.y);
    values[6] = axis.y * (1.0f - cosine) * axis.z - axis.x * sine;
    values[7] = 0.0f;
    values[8] = axis.x * (1.0f - cosine) * axis.z - axis.y * sine;
    values[9] = axis.y * (1.0f - cosine) * axis.z + axis.x * sine;
    values[10] = axis.z * axis.z + cosine * (1.0f - axis.z * axis.z);
    values[11] = 0.0f;
    values[12] = 0.0f;
    values[13] = 0.0f;
    values[14] = 0.0f;
    values[15] = 1.0f;
}
