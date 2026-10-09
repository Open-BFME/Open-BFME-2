// ?rotateLocalTransformZ@ParticleSystem@@QAEXM@Z
// partial score=0.9 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /Oi- /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
#include "matrix3d.h"
class ParticleSystem {public: void rotateLocalTransformX(float);void rotateLocalTransformY(float);void rotateLocalTransformZ(float);private:char before[0xBC];Matrix3D m_localTransform;char after[0x1A0-0xEC];unsigned char m_isLocalIdentity;};
void ParticleSystem::rotateLocalTransformX(float theta){float s=(float)sin((double)theta);float c=(float)cos((double)theta);m_localTransform.Rotate_X(s,c);m_isLocalIdentity=false;}
void ParticleSystem::rotateLocalTransformY(float theta){float s=(float)sin((double)theta);float c=(float)cos((double)theta);m_localTransform.Rotate_Y(s,c);m_isLocalIdentity=false;}
void ParticleSystem::rotateLocalTransformZ(float theta){float c=(float)cos((double)theta);float s=(float)sin((double)theta);m_localTransform.Rotate_Z(s,c);m_isLocalIdentity=false;}
