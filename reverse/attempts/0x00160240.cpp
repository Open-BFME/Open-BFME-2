// ?evaluate@Rva00160240@@QAEXAAURva00160240Pose@@MAAMMPAPAE@Z
// partial score=0.4 date=2026-10-09
// cl: /O2 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
#include "quat.h"
// Semantic lead: ZH/BFME1 9cbfb551fe20 quaternion Rotate_Vector/product,
// hrawanim translation/orientation/fade evaluation. Native160240..1606E0
// uses compact channels at0/4/8/C/10; scalar vslotC and quaternion vslot14
// have the independently rowed BFME2MotionChannel three-argument ABI.
// The transform's measured prefix is Quaternion0 and Vector3+10. Target
// evaluates translation, scales it, accumulates it in the rotated basis,
// composes the optional quaternion, then writes fade (default1). Owner and
// original function name remain unknown; only the observed prefix is used.
class ChunkLoadClass;
class BFME2MotionChannel {
public:
 virtual bool Load(ChunkLoadClass &);
 virtual ~BFME2MotionChannel();
 virtual int UnknownSlot2();
 virtual void UnknownSlot3(float,float *,unsigned char **);
 virtual void UnknownSlot4(float,Vector3 *,unsigned char **);
 virtual void UnknownSlot5(float,Quaternion *,unsigned char **);
 virtual int UnknownSlot6();
 int Type,Pivot,Count,Components;
};
struct Rva00160240Pose {
 Quaternion Rotation;
 Vector3 Position;
 __forceinline Vector3 rotate(const Vector3 &v) const {
  float a=(Rotation.Y*v.Z-v.Y*Rotation.Z)+Rotation.W*v.X;
  float b=Rotation.W*v.Y-(Rotation.X*v.Z-v.X*Rotation.Z);
  float c=(Rotation.X*v.Y-v.X*Rotation.Y)+Rotation.W*v.Z;
  float d=0.0f-(Rotation.X*v.X+Rotation.Y*v.Y+Rotation.Z*v.Z);
  return Vector3((Rotation.Y*c-Rotation.Z*b)+(Rotation.W*a-Rotation.X*d),
    Rotation.W*b-Rotation.Y*d-(Rotation.X*c-Rotation.Z*a),
    (Rotation.X*b-Rotation.Y*a)+(Rotation.W*c-Rotation.Z*d));
 }
 __forceinline void Translate(const Vector3 &v){ Position+=rotate(v); }
 __forceinline void Rotate(const Quaternion &q,Quaternion &saved){
  saved=Rotation;
  Rotation.X=(saved.Y*q.Z-q.Y*saved.Z)+q.W*saved.X+saved.W*q.X;
  Rotation.Y=q.W*saved.Y+saved.W*q.Y-(saved.X*q.Z-q.X*saved.Z);
  Rotation.Z=(saved.X*q.Y-q.X*saved.Y)+q.W*saved.Z+saved.W*q.Z;
  Rotation.W=q.W*saved.W-(q.Z*saved.Z+q.Y*saved.Y+q.X*saved.X);
 }
};
class Rva00160240 {
public:
 void evaluate(Rva00160240Pose &pose,float scale,float &fade,float frame,unsigned char **cursor);
 BFME2MotionChannel *X,*Y,*Z,*Q,*Fade;
};
void Rva00160240::evaluate(Rva00160240Pose &pose,float scale,float &fade,float frame,unsigned char **cursor)
{
 struct Scratch { Quaternion saved,rotation;Vector3 translation; } scratch;
 Quaternion &rotation=scratch.rotation;
 Vector3 &translation=scratch.translation;
 if(X)X->UnknownSlot3(frame,&translation.X,cursor);else translation.X=0;
 if(Y)Y->UnknownSlot3(frame,&translation.Y,cursor);else translation.Y=0;
 if(Z)Z->UnknownSlot3(frame,&translation.Z,cursor);else translation.Z=0;
 translation*=scale;
 if(Q){
  Q->UnknownSlot5(frame,&rotation,cursor);
  pose.Translate(translation);
  pose.Rotate(rotation,scratch.saved);
 }else pose.Translate(translation);
 if(Fade)Fade->UnknownSlot3(frame,&fade,cursor);else fade=1.0f;
}
