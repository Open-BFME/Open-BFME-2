// cl: /O1 /G7 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug
//
// ?Rotate_Z@Matrix3x3@@QAEXM@Z, retail 0x003fc4c2, 202 bytes. Banked partial (score 0.94) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
#include "vector3.h"
class Matrix3x3 {
public:
    void Rotate_Z(float theta);
    __forceinline void Rotate_Z(float s, float c);
private:
    Vector3 Row[3];
};
void Matrix3x3::Rotate_Z(float theta) {
    float s = sinf(theta);
    float c = cosf(theta);
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
