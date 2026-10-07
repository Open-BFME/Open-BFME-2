// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_vector3 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// Native 0x00140C50..0x00140C60, RET0; const camera receiver.
// Source guide: ZH camera.h CameraClass::Get_Frustum_Corners and frustum.h
// at verified BFME1 donor ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f.
// The rowed world-frustum getter 0x0004CB06 returns receiver+100 after
// Update_Frustum 1340B0. Reference CameraTransform30 plus six 16-byte PlaneClass
// values puts Corners at Frustum+90; this body returns camera+190.
// The consumed prefixes below omit unrelated fields and are never allocated.
#include "vector3.h"
class FrustumClass {public:char unknown00[0x90];Vector3 Corners[8];};
class CameraClass {
public:
    const Vector3 *Get_Frustum_Corners() const;
protected:
    void Update_Frustum() const;
    char unknown00[0x100]; FrustumClass Frustum;
};
const Vector3 *CameraClass::Get_Frustum_Corners() const
{
    Update_Frustum();
    return Frustum.Corners;
}
