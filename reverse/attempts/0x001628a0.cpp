// ?Base_Update@HTreeClass@@QAEXABVMatrix3D@@@Z
// partial score=0.13210039630118892 date=2026-09-08
// cl: /G7 /arch:SSE /EHsc- /MD /DNDEBUG /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// Full retail body769B ends562BA1 after three-byte RET4 at562B9E.
// Candidate remains unverified; Apply_Captured_Bone is a descriptive dependency.
#include "matrix3d.h"
#include "quat.h"
#include "vector3.h"

struct PivotClass {
    char Name[16];
    PivotClass *Parent;
    Quaternion BaseRotation;
    Vector3 BaseTranslation;
    Quaternion TransformRotation;
    Vector3 TransformTranslation;
    int Index;
    bool IsVisible;
    float PivotFade;
};
typedef char PivotClassMustBe88[(sizeof(PivotClass) == 88) ? 1 : -1];

class HTreeClass {
    struct CapturedBone { int Index; Quaternion Rotation; Vector3 Translation; bool WorldSpaceTranslation; };
    char Name[16]; int NumPivots; PivotClass *Pivot; float ScaleFactor;
    CapturedBone *CaptureBegin,*CaptureEnd,*CaptureCapacity;
    unsigned int Unknown28,Unknown2C,Unknown30;
public:
    void Base_Update(const Matrix3D &root);
    int Apply_Captured_Bone(int);
};


void HTreeClass::Base_Update(const Matrix3D &root)
{
    PivotClass *root_pivot = Pivot;
    root_pivot->TransformRotation = Build_Quaternion(root);
    root_pivot->TransformTranslation = root.Get_Translation();
    root_pivot->IsVisible = true;
    root_pivot->PivotFade = 1.0f;
    int captured_index;
    if (CaptureBegin == CaptureEnd) captured_index = -1;
    else captured_index = CaptureBegin->Index;
    int pivot_offset = 0x58;
    for (int piv_idx=1; piv_idx<NumPivots; ++piv_idx, pivot_offset += 0x58) {
        PivotClass *pivot=(PivotClass*)((char*)Pivot + pivot_offset);
        PivotClass *parent=pivot->Parent;
        parent->TransformRotation.Rotate_Vector(pivot->BaseTranslation,&pivot->TransformTranslation);
        pivot->TransformTranslation += parent->TransformTranslation;
        pivot->TransformRotation = parent->TransformRotation * pivot->BaseRotation;
        pivot->IsVisible=true;
        pivot->PivotFade=1.0f;
        if (piv_idx == captured_index) captured_index = Apply_Captured_Bone(captured_index);
    }
}
