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
    void Rotate_Z(float s, float c);
private:
    Vector3 Row[3];
};
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
