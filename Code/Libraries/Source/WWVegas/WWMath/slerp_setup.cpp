// cl: /DNDEBUG /G7 /arch:SSE2 /Ireference/shims/bfmerendobj /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug
/*
 * Recovered from the Open-BFME-1 GPLv3 math implementation and matched to the
 * BFME2 retail Slerp_Setup body.  The BFME2 target computes the quaternion dot
 * product in W,Z,Y,X order, flips the second quaternion for a negative dot,
 * then caches either the linear path or Acos(dot)/Sin(theta).
 */
#include "quat.h"
#include "wwmath.h"

#define SLERP_EPSILON 0.001

void Slerp_Setup(const Quaternion & p,const Quaternion & q,SlerpInfoStruct * slerpinfo)
{
    float cos_t;

    cos_t = p.X * q.X + p.Y * q.Y + p.Z * q.Z + p.W * q.W;

    if (cos_t < 0.0f) {
        cos_t = -cos_t;
        slerpinfo->Flip = true;
    } else {
        slerpinfo->Flip = false;
    }

    if (1.0f - cos_t < SLERP_EPSILON) {
        slerpinfo->Linear = true;
        slerpinfo->Theta = 0.0f;
        slerpinfo->SinT = 0.0f;
    } else {
        slerpinfo->Linear = false;
        slerpinfo->Theta = WWMath::Acos(cos_t);
        slerpinfo->SinT = WWMath::Sin(slerpinfo->Theta);
    }
}
