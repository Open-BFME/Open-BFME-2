// cl: /O1 /Oy- /arch:SSE /G7 /MD /DNDEBUG /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /ICode/Libraries/Include
// Thing::convertBonePosToWorldPos; target 0x0030A528/746.
// Reference semantics: BF1 f98983a7d ZH GeneralsMD Common/Thing/Thing.cpp341.
// Target native and WB0xCEE0D0 independently show the optional matrix product
// and optional point transformation; WB's inline assertion is Matrix3D.h1562.
// Native this+8 is the transform (the reference's layout differs).
// The target-proven matrix association and Transform_Vector alias handling
// reproduce all 746 bytes with O1/SSE/G7/Oy-. The helpers below operate on
// canonical Matrix3D storage and retain the original expression order.
// Coord3D's canonical trivial copy restores the native12B temporary and MOVSDs.
#include "Lib/Coord3D.h"
#include "vector3.h"
#include "thing.h"
// LINK: file-static helpers and direct Row fields replace Vector3's MMM ctor and
// operator=, Vector4/Matrix3D operator[] and Matrix3D::mul: identical inlined
// bytes, but this TU no longer emits their loser COMDAT copies. No flags touched.
static __forceinline void bfmeCopyV3(Vector3 &destinationVector,const Vector3 &sourceVector) {destinationVector.X=sourceVector.X;destinationVector.Y=sourceVector.Y;destinationVector.Z=sourceVector.Z;}
static __forceinline void bfmeSetV3(Vector3 &targetVector,float xComponent,float yComponent,float zComponent) {targetVector.X=xComponent;targetVector.Y=yComponent;targetVector.Z=zComponent;}
static __forceinline float boneSubmul(const Vector4 &row,float pointX,float pointY,float pointZ) {return row.Z*pointZ+row.Y*pointY+row.X*pointX;}
static __forceinline void bfmeMultiplyBoneTransform(Matrix3D &result,const Matrix3D &matrix3D,const Matrix3D &boneTransform) {
  float x,y,z;
  x=boneTransform.Row[0].X;y=boneTransform.Row[1].X;z=boneTransform.Row[2].X;
  result.Row[0].X=boneSubmul(matrix3D.Row[0],x,y,z);
  result.Row[1].X=boneSubmul(matrix3D.Row[1],x,y,z);
  result.Row[2].X=boneSubmul(matrix3D.Row[2],x,y,z);
  x=boneTransform.Row[0].Y;y=boneTransform.Row[1].Y;z=boneTransform.Row[2].Y;
  result.Row[0].Y=boneSubmul(matrix3D.Row[0],x,y,z);
  result.Row[1].Y=boneSubmul(matrix3D.Row[1],x,y,z);
  result.Row[2].Y=boneSubmul(matrix3D.Row[2],x,y,z);
  x=boneTransform.Row[0].Z;y=boneTransform.Row[1].Z;z=boneTransform.Row[2].Z;
  result.Row[0].Z=boneSubmul(matrix3D.Row[0],x,y,z);
  result.Row[1].Z=boneSubmul(matrix3D.Row[1],x,y,z);
  result.Row[2].Z=boneSubmul(matrix3D.Row[2],x,y,z);
  x=boneTransform.Row[0].W;y=boneTransform.Row[1].W;z=boneTransform.Row[2].W;
  result.Row[0].W=boneSubmul(matrix3D.Row[0],x,y,z)+matrix3D.Row[0].W;
  result.Row[1].W=boneSubmul(matrix3D.Row[1],x,y,z)+matrix3D.Row[1].W;
  result.Row[2].W=boneSubmul(matrix3D.Row[2],x,y,z)+matrix3D.Row[2].W;
  }
static __forceinline void bfmeTransformBoneVector(const Matrix3D &matrix3D,const Vector3 &in,Vector3 *out) {
  Vector3 inputCopy;
  Vector3 *inputVector;
  if(out==&in) {bfmeCopyV3(inputCopy,in);inputVector=&inputCopy;} else inputVector=(Vector3 *)&in;
  out->X=matrix3D.Row[0].X*inputVector->X+matrix3D.Row[0].Y*inputVector->Y+matrix3D.Row[0].Z*inputVector->Z+matrix3D.Row[0].W;
  out->Y=matrix3D.Row[1].X*inputVector->X+matrix3D.Row[1].Y*inputVector->Y+matrix3D.Row[1].Z*inputVector->Z+matrix3D.Row[1].W;
  out->Z=matrix3D.Row[2].X*inputVector->X+matrix3D.Row[2].Y*inputVector->Y+matrix3D.Row[2].Z*inputVector->Z+matrix3D.Row[2].W;
 }

void Thing::convertBonePosToWorldPos(const Coord3D *bonePos,const Matrix3D *boneTransform,Coord3D *worldPos,Matrix3D *worldTransform) const {
 if(worldTransform) bfmeMultiplyBoneTransform(*worldTransform,m_transform,*boneTransform);
 if(worldPos) {
  Vector3 vector;bfmeSetV3(vector,bonePos->x,bonePos->y,bonePos->z);
  bfmeTransformBoneVector(m_transform,vector,&vector);
  *worldPos=*reinterpret_cast<const Coord3D *>(&vector);
 }
}
