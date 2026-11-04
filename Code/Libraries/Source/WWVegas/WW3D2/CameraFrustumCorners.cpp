// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_vector3 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// Native 0x00140C50..0x00140C60, RET0; const camera receiver.
// Source guide: ZH camera.h CameraClass::Get_Frustum_Corners and frustum.h
// at verified BFME1 donor ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f.
// The rowed world-frustum getter 0x0004CB06 returns receiver+100 after
// Update_Frustum 1340B0. Reference CameraTransform30 plus six 16-byte PlaneClass
// values puts Corners at Frustum+90; this body returns camera+190.
// The canonical header keeps the frustum as raw storage at +0x100.
#include "CameraClass.h"
inline const Vector3 *CameraClass::Get_Frustum_Corners() const
{
    Update_Frustum();
    return (const Vector3 *)(field100 + 0x90);
}
const Vector3 *(CameraClass::*_bfmeInlineAnchor_CameraFrustumCorners_0)() const = &CameraClass::Get_Frustum_Corners;

