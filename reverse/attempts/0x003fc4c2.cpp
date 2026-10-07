// ?Rotate_Z@Matrix3x3@@QAEXM@Z
// partial score=0.94 date=2026-10-07
// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// ?Rotate_Z@Matrix3x3@@QAEXM@Z @0x003FC4C2 202B
// The target body is a thiscall rotation over Row[0..2][0..1]: its boundary,
// float angle, direct sin/cos imports, and row offsets match this operation.
// Donor semantic/layout source: BFME 1 matrix3.h::Matrix3x3::Rotate_Z(float)
// at submodule revision 6583b3c1ff21db4a561285717028fdafc780b7db. The donor
// uses sinf/cosf; target disassembly proves double sin/cos followed by float
// stores, so the implementation below follows that target-specific difference.

extern "C" double __cdecl sin(double angle);
extern "C" double __cdecl cos(double angle);

class Vector3 {
public:
    float &operator[](int index) { return (&X)[index]; }
    float X;
    float Y;
    float Z;
};

class Matrix3x3 {
public:
    void Rotate_Z(float theta);

private:
    Vector3 Row[3];
};

void Matrix3x3::Rotate_Z(float theta)
{
    float sine = (float)sin((double)theta);
    float cosine = (float)cos((double)theta);
    float tmp1, tmp2;

    tmp1 = Row[0][0]; tmp2 = Row[0][1];
    Row[0][0] = (float)(cosine * tmp1 + sine * tmp2);
    Row[0][1] = (float)(-sine * tmp1 + cosine * tmp2);

    tmp1 = Row[1][0]; tmp2 = Row[1][1];
    Row[1][0] = (float)(cosine * tmp1 + sine * tmp2);
    Row[1][1] = (float)(-sine * tmp1 + cosine * tmp2);

    tmp1 = Row[2][0]; tmp2 = Row[2][1];
    Row[2][0] = (float)(cosine * tmp1 + sine * tmp2);
    Row[2][1] = (float)(-sine * tmp1 + cosine * tmp2);
}
