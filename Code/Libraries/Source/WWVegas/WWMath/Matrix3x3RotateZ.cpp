// cl: /O1 /G7 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug
// Open-BFME-1 donor ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f:
// sphereobj.cpp emits Matrix3x3::Rotate_Z from the GeneralsMD matrix3.h.
// Native 0x3FBF50..0x3FBFF3 is the complete 163B two-float thiscall body:
// each 12B row rotates X/Y and leaves Z unchanged; RET 8 ends immediately
// before the next prologue. Both compiler profiles O1/G6 and O1/G7 place it.
// Vector3 indexing preserves the verified donor alias and scheduling shape.
#include "vector3.h"
class Matrix3x3 {
public:
    __forceinline Matrix3x3(const Vector3 &r0, const Vector3 &r1, const Vector3 &r2)
    {
        Row[0] = r0;
        Row[1] = r1;
        Row[2] = r2;
    }
    friend Matrix3x3 operator*(const Matrix3x3 &a, const Matrix3x3 &b);
    void Rotate_Z(float s, float c);
private:
    Vector3 Row[3];
};

// Clean reference: Open-BFME-1 34f59164f6, Matrix3x3_Multiply_Address.cpp
// and GeneralsMD matrix3.h. The reference names the mathematical type;
// native 0x005629B7..0x00562BB1 independently proves all nine row-column
// products, the 36-byte hidden return object, and its Vector3 array lifetime.
Matrix3x3 operator*(const Matrix3x3 &a, const Matrix3x3 &b)
{
#define ROWCOL(i,j) a.Row[i][0]*b.Row[0][j] + a.Row[i][1]*b.Row[1][j] + a.Row[i][2]*b.Row[2][j]
    // Set preserves the same arithmetic and temporary evaluation order while
    // avoiding a conflicting out-of-line three-float Vector3 constructor.
    Vector3 r2;
    r2.Set(ROWCOL(2,0), ROWCOL(2,1), ROWCOL(2,2));
    Vector3 r1;
    r1.Set(ROWCOL(1,0), ROWCOL(1,1), ROWCOL(1,2));
    Vector3 r0;
    r0.Set(ROWCOL(0,0), ROWCOL(0,1), ROWCOL(0,2));
    return Matrix3x3(r0, r1, r2);
#undef ROWCOL
}

void Matrix3x3::Rotate_Z(float s, float c) {
    float tmp1, tmp2;
    tmp1 = Row[0][0]; tmp2 = Row[0][1];
    Row[0][0] = (float)(c * tmp1 + s * tmp2);
    Row[0][1] = (float)(-s * tmp1 + c * tmp2);
    tmp1 = Row[1][0]; tmp2 = Row[1][1];
    Row[1][0] = (float)(c * tmp1 + s * tmp2);
    Row[1][1] = (float)(-s * tmp1 + c * tmp2);
    tmp1 = Row[2][0]; tmp2 = Row[2][1];
    Row[2][0] = (float)(c * tmp1 + s * tmp2);
    Row[2][1] = (float)(-s * tmp1 + c * tmp2);
}
