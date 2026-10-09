// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /Oi- /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// Native full247B ranges1F392E..1F3A25 /1F3A25..1F3B1C /1F3B1C..1F3C13.
// BFME1 ParticleSystemRotateLocalTransformX/Y/Z (874e38488) and its full
// WWMath Matrix3D header supply the axis-rotation algorithms and names.
// Target transform setters1F38C1/1F3899 and FX callers1E2099/1E20CB/1E20FD
// independently establish Matrix3D+BC and identity byte+1A0. Full class
// extent and the intervening fields remain unresolved; this is a borrowed prefix.
// Reference adapters let trig evaluation occur in a sequenced comma expression
// while the other float is passed by reference and read only after all call
// arguments finish. This keeps the C++ evaluation defined and schedules the
// second x87 float spill after the first row's SSE loads, as retail does.
#include "matrix3d.h"
static __forceinline void particleRotateX(Matrix3D&matrix,const float& s,float c){matrix.Rotate_X(s,c);}
static __forceinline void particleRotateY(Matrix3D&matrix,const float&s,float c){matrix.Rotate_Y(s,c);}
static __forceinline void particleRotateZ(Matrix3D&matrix,float s,const float&c){matrix.Rotate_Z(s,c);}
class ParticleSystem {public: void rotateLocalTransformX(float);void rotateLocalTransformY(float);void rotateLocalTransformZ(float);private:char before[0xBC];Matrix3D m_localTransform;char after[0x1A0-0xEC];unsigned char m_isLocalIdentity;};
void ParticleSystem::rotateLocalTransformX(float theta){float s;particleRotateX(m_localTransform,s,(s=(float)sin((double)theta),(float)cos((double)theta)));m_isLocalIdentity=false;}
void ParticleSystem::rotateLocalTransformY(float theta){float s;particleRotateY(m_localTransform,s,(s=(float)sin((double)theta),(float)cos((double)theta)));m_isLocalIdentity=false;}
void ParticleSystem::rotateLocalTransformZ(float theta){float c;particleRotateZ(m_localTransform,(c=(float)cos((double)theta),(float)sin((double)theta)),c);m_isLocalIdentity=false;}
