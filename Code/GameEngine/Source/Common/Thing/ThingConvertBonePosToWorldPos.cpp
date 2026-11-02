// cl: /O1 /Oy- /arch:SSE /G7 /MD /DNDEBUG /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /ICode/Libraries/Include
// Thing::convertBonePosToWorldPos; target 0x0030A528/746.
// Reference semantics: BF1 f98983a7d ZH GeneralsMD Common/Thing/Thing.cpp341.
// Target native and WB0xCEE0D0 independently show the optional matrix product
// and optional point transformation; WB's inline assertion is Matrix3D.h1562.
// Native this+8 is the transform (the reference's layout differs).
// Keep the reference member-method form: static matrix helpers perturb SSE
// allocation. The target-proven matrix association and ordinary Transform_Vector
// alias handling together reproduce all746 bytes with O1/SSE/G7/Oy-.
// Coord3D's canonical trivial copy restores the native12B temporary and MOVSDs.
// The Matrix3D view contains exactly three four-float rows; no own data or vptr.
#include "Lib/Coord3D.h"
#include "vector3.h"
#include "vector4.h"
// LINK: file-static helpers and direct Row fields replace Vector3's MMM ctor and
// operator=, Vector4/Matrix3D operator[] and Matrix3D::mul: identical inlined
// bytes, but this TU no longer emits their loser COMDAT copies. No flags touched.
static __forceinline void bfmeCopyV3(Vector3 &destinationVector,const Vector3 &sourceVector) {destinationVector.X=sourceVector.X;destinationVector.Y=sourceVector.Y;destinationVector.Z=sourceVector.Z;}
static __forceinline void bfmeSetV3(Vector3 &targetVector,float x,float y,float z) {targetVector.X=x;targetVector.Y=y;targetVector.Z=z;}
static __forceinline float boneSubmul(const Vector4 &row,float x,float y,float z) {return row.Z*z+row.Y*y+row.X*x;}
class Matrix3D {public:
 Vector4 Row[3];
 __forceinline void bfme_mul_bp(const Matrix3D &matrix3D,const Matrix3D &b) {
  float x,y,z;
  x=b.Row[0].X;y=b.Row[1].X;z=b.Row[2].X;
  Row[0].X=boneSubmul(matrix3D.Row[0],x,y,z);
  Row[1].X=boneSubmul(matrix3D.Row[1],x,y,z);
  Row[2].X=boneSubmul(matrix3D.Row[2],x,y,z);
  x=b.Row[0].Y;y=b.Row[1].Y;z=b.Row[2].Y;
  Row[0].Y=boneSubmul(matrix3D.Row[0],x,y,z);
  Row[1].Y=boneSubmul(matrix3D.Row[1],x,y,z);
  Row[2].Y=boneSubmul(matrix3D.Row[2],x,y,z);
  x=b.Row[0].Z;y=b.Row[1].Z;z=b.Row[2].Z;
  Row[0].Z=boneSubmul(matrix3D.Row[0],x,y,z);
  Row[1].Z=boneSubmul(matrix3D.Row[1],x,y,z);
  Row[2].Z=boneSubmul(matrix3D.Row[2],x,y,z);
  x=b.Row[0].W;y=b.Row[1].W;z=b.Row[2].W;
  Row[0].W=boneSubmul(matrix3D.Row[0],x,y,z)+matrix3D.Row[0].W;
  Row[1].W=boneSubmul(matrix3D.Row[1],x,y,z)+matrix3D.Row[1].W;
  Row[2].W=boneSubmul(matrix3D.Row[2],x,y,z)+matrix3D.Row[2].W;
  }
 static __forceinline void Transform_Vector(const Matrix3D &matrix3D,const Vector3 &in,Vector3 *out) {
  Vector3 tmp;
  Vector3 *v;
  if(out==&in) {bfmeCopyV3(tmp,in);v=&tmp;} else v=(Vector3 *)&in;
  out->X=matrix3D.Row[0].X*v->X+matrix3D.Row[0].Y*v->Y+matrix3D.Row[0].Z*v->Z+matrix3D.Row[0].W;
  out->Y=matrix3D.Row[1].X*v->X+matrix3D.Row[1].Y*v->Y+matrix3D.Row[1].Z*v->Z+matrix3D.Row[1].W;
  out->Z=matrix3D.Row[2].X*v->X+matrix3D.Row[2].Y*v->Y+matrix3D.Row[2].Z*v->Z+matrix3D.Row[2].W;
 }
};
class Thing {public:
 void convertBonePosToWorldPos(const Coord3D *,const Matrix3D *,Coord3D *,Matrix3D *) const;
 char prefix[8];Matrix3D transform;
};
void Thing::convertBonePosToWorldPos(const Coord3D *bonePos,const Matrix3D *boneTransform,Coord3D *worldPos,Matrix3D *worldTransform) const {
 if(worldTransform) worldTransform->bfme_mul_bp(transform,*boneTransform);
 if(worldPos) {
  Vector3 vector;bfmeSetV3(vector,bonePos->x,bonePos->y,bonePos->z);
  Matrix3D::Transform_Vector(transform,vector,&vector);
  *worldPos=*reinterpret_cast<const Coord3D *>(&vector);
 }
}
